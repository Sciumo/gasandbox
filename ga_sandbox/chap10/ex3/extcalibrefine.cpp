// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2007, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/timing.h>

#define USE_OPENCV

#ifdef USE_OPENCV
// not sure whether this should be <opencv/cxcore.h> or just <cxcore.h>
//#include <cxcore.h>
#include <opencv/cxcore.h>
#else
#include <mkl_lapack.h>
#include <mkl_blas.h>

#endif /* USE_OPENCV */

#include "extcalibrefine.h"

using namespace e3ga;

namespace extCalibRefine {

Camera::Camera() {
}

Camera::Camera(const e3ga::rotor &R, const e3ga::vector &t,
		const std::vector<bool> &visible,
		const std::vector<vector> &pt) :
	m_R(R), m_t(t),
	m_visible(visible), m_pt(pt), m_X3(pt.size()) {
	initRom();
}

Camera::Camera(const Camera&C) :
	m_R(C.m_R), m_t(C.m_t), m_Rom(C.m_Rom),
	m_visible(C.m_visible), m_pt(C.m_pt), m_X3(C.m_X3) {
}

Camera &Camera::operator=(const Camera&C) {
	if (&C != this) {
		m_R = C.m_R;
		m_t = C.m_t;
		m_Rom = C.m_Rom;
		m_visible = C.m_visible;
		m_pt = C.m_pt;
		m_X3 = C.m_X3;
	}
	return *this;
}


void Camera::initRom() {
	rotor Ri = _rotor(inverse(m_R));
	m_Rom.set(_vector(m_R * e1 * Ri),
		_vector(m_R * e2 * Ri),
		_vector(m_R * e3 * Ri));
}

State::State() : m_nbRefinements(0) {
}

State::State(const std::vector<Camera> &cam) : m_cam(cam), m_nbRefinements(0) {
	// determine max frame nb:
	int maxNbF = -1;
	for (unsigned int c = 0; c < m_cam.size(); c++) {
		if ((int)m_cam[c].m_visible.size() > maxNbF)
			maxNbF = (int)m_cam[c].m_visible.size();
	}

	// make sure all cams have same number of frames:
	for (unsigned int c = 0; c < m_cam.size(); c++) {
		m_cam[c].setNbFrames(maxNbF);
	}

	// make room for points:
	m_pt.resize(maxNbF);
	m_ptValid.resize(maxNbF);

	init();
}

State::State(const State &S) : m_cam(S.m_cam), m_pt(S.m_pt),
	m_ptValid(S.m_ptValid), m_nbRefinements(S.m_nbRefinements) {

}

State &State::operator=(const State &S) {
	if (this != &S) {
		m_cam = S.m_cam;
		m_pt = S.m_pt;
		m_nbRefinements = S.m_nbRefinements;
		m_ptValid = S.m_ptValid;
	}
	return *this;
}

/// refine estimates for 'nb' loops
void State::refineLoops(int nb) {
	for (int i = 0; i < nb; i++)
		refineOnce();
}

/// refine estimates for 't' seconds
void State::refineSeconds(double t) {
	double endT = u_timeGet() + t;
	while (u_timeGet() < endT) {
		refineOnce();
	}
}

void State::init() {
	normalizeTranslation(false); // false means: dont' update points
	reconstructPoints();
	updateX3();
}

void State::refineOnce() {
//	printf("Refine!\n");
	updateTranslation();
	normalizeTranslation(false); // false = don't update points
	updateRotation();
	updatePoints();
	updateX3();
	m_nbRefinements++;
}

// *!*HTML_TAG*!* update
void State::updateTranslation() {
	for (unsigned int c = 1; c < m_cam.size(); c++) { // start at '1' because translation of first camera is always 0
		Camera &C = m_cam[c];

		vector sum;
		int nbVisible = 0;
		for (unsigned int i = 0; i < m_pt.size(); i++) {
			if ((C.m_visible[i]) && m_ptValid[i]) {
				sum += _vector(m_pt[i] - C.m_X3[i] * (apply_om(C.m_Rom, C.m_pt[i])));
				nbVisible++;
			}
		}
		C.m_t = sum * (1.0f / (mv::Float)nbVisible);
	}
}

void State::updateX3() {
	for (unsigned int c = 0; c < m_cam.size(); c++) {
		for (unsigned int i = 0; i < m_pt.size(); i++) {
			if ((m_cam[c].m_visible[i]) && m_ptValid[i]) {
				m_cam[c].m_X3[i] =
					_Float((m_pt[i] - m_cam[c].m_t) % apply_om(m_cam[c].m_Rom, m_cam[c].m_pt[i])) /
					_Float(m_cam[c].m_pt[i] % m_cam[c].m_pt[i]);
			}
		}
	}
}

void State::updatePoints() {
	for (unsigned int i = 0; i < m_pt.size(); i++) {
		if (m_ptValid[i]) {
			vector sum;
			int nbVisible = 0;
			for (unsigned int c = 0; c < m_cam.size(); c++) {
				if (m_cam[c].m_visible[i]) {
					sum += _vector(m_cam[c].m_t +
						m_cam[c].m_X3[i] * apply_om(m_cam[c].m_Rom, m_cam[c].m_pt[i]));
					nbVisible++;
				}
			}
			m_pt[i] = _vector(sum * (1.0f / (mv::Float)nbVisible));
		}
	}
}

void State::normalizeTranslation(bool updatePoints) {
	mv::Float  sum = 0;

	sum += _Float(norm_e(m_cam[1].m_t));

	// scale all translations
	for (unsigned int c = 1; c < m_cam.size(); c++) { // start at '1' because translation of first camera is always 0
		m_cam[c].m_t *= 1.0f / sum;
	}

	// scale all points
	if (updatePoints) {
		for (unsigned int i = 0; i < m_pt.size(); i++) {
			for (unsigned int c = 0; c < m_cam.size(); c++) {
				m_cam[c].m_X3[i] /= sum;
			}
			m_pt[i] *= 1.0f / sum;
		}
	}
}

void printMatrix(double *M) {
	printf("%f %f %f\n", M[0 * 3 + 0], M[0 * 3 + 1], M[0 * 3 + 2]);
	printf("%f %f %f\n", M[1 * 3 + 0], M[1 * 3 + 1], M[1 * 3 + 2]);
	printf("%f %f %f\n", M[2 * 3 + 0], M[2 * 3 + 1], M[2 * 3 + 2]);
}

void computeSVD(const double *_a, double *svd_u, double *svd_s, double *svd_vt) {
#ifdef USE_OPENCV

	CvMat A = cvMat(3, 3, CV_64F, (void*)_a);
	CvMat W = cvMat(3, 3, CV_64F, svd_s);
	CvMat U = cvMat(3, 3, CV_64F, svd_vt);
	CvMat V = cvMat(3, 3, CV_64F, svd_u);

	int flags=CV_SVD_V_T;
	cvSVD(&A, &W, &U, &V, flags);

#else
	// MKL / LAPACK:
	const int size = 3;
	double a[9];
	memcpy(a,_a, 9*sizeof(double));
	double pt[9], q[9], lap_d[3], lap_e[3], tauq[3], taup[3], work[1000];
	int lwork = 1000;

	memset(lap_d, 0, 3 * sizeof(double));
	memset(lap_e, 0, 3 * sizeof(double));

	// a -> bidiagonal form
	int lap_m = size, lap_n = size, lap_lda = size, lap_info;
	DGEBRD(&lap_m, &lap_n, a, &lap_lda, lap_d, lap_e, tauq, taup,  work, &lwork, &lap_info);

	// get the matrices orthogonal p and q
	char vect = 'P';
	memcpy(pt, a, 9 * sizeof(double));
	DORGBR(&vect, &lap_m, &lap_n, &lap_lda, pt, &lap_lda, taup, work, &lwork, &lap_info);
	vect = 'Q';
	memcpy(q, a, 9 * sizeof(double));
	DORGBR(&vect, &lap_m, &lap_n, &lap_lda, q, &lap_lda, tauq, work, &lwork, &lap_info);

	// compute the svd
	char uplo = 'U';
	int lap_order = 3, lap_zero = 0;
	double svd_c[9];
	memcpy(svd_vt, pt, 9 * sizeof(double));
	memcpy(svd_u, q, 9 * sizeof(double));
	memset(svd_c, 0, 9 * sizeof(double));
	DBDSQR(&uplo, &lap_order, &lap_m, &lap_n, &lap_zero,
		lap_d, lap_e,
		svd_vt, &lap_lda,
		svd_u, &lap_lda,
		NULL, &lap_lda,
		work, &lap_info);

	memset(svd_s, 0, sizeof(double) * 9);
	svd_s[0 * 3 + 0] = lap_d[0];
	svd_s[1 * 3 + 1] = lap_d[1];
	svd_s[2 * 3 + 2] = lap_d[2];
	}
#endif
}

/**
Constructs the rotor which (in a Least Squares sense) is the optimal rotor to rotate the
vectors in u to v.
*/
e3ga::rotor constructFrame2FrameRotorLS(const std::vector<e3ga::vector> &u,
										const std::vector<e3ga::vector> &v) {
	// compute the outermorphism representing the function 'f'
	vector e[3];
	for (unsigned int i = 0; i < u.size(); i++) {
		e[0] += _vector(v[i].e1() * u[i]);
		e[1] += _vector(v[i].e2() * u[i]);
		e[2] += _vector(v[i].e3() * u[i]);
	}

	e3ga::om fom(e);


	// initialize the LAPACK input matrix 'a'
	int lwork = 1000;
	double a[9];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			a[i * 3 + j] = fom.m_c[j * 3 + i]; // transpose for LAPACK input

	// compute the svd of 'a'
	double svd_vt[9], svd_u[9], svd_s[9];
	computeSVD(a, svd_u, svd_s, svd_vt);

	// multiply the matrices svd_u and svd_vt to give the matrix representation of the rotation
	mv::Float resultMatrix[9];
#ifdef USE_OPENCV
	double _resultMatrix[9];
	CvMat VT = cvMat(3, 3, CV_64F, svd_vt);
	CvMat U = cvMat(3, 3, CV_64F, svd_u);
	CvMat R = cvMat(3, 3, CV_64F, _resultMatrix);
	cvMatMul(&VT, &U, &R);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			resultMatrix[i * 3 + j] = (mv::Float)_resultMatrix[i * 3 + j];
#else
	int lap_m = 3, lap_n = 3, lap_lda = 3;
	char transa = 'T', transb = 'T';
	double lap_tmp1[9];
	memset(lap_tmp1, 0, sizeof(double) * 9);
	double alpha = 1.0f, beta = 0.0f;
	DGEMM(&transa, &transb, &lap_n, &lap_n, &lap_n, &alpha, svd_vt, &lap_n, svd_u, &lap_n, &beta, lap_tmp1, &lap_n);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			resultMatrix[i * 3 + j] = (mv::Float)lap_tmp1[j * 3 + i]; // transpose for LAPACK output
#endif



	// convert to rotor
	return matrixToRotor(resultMatrix);
}


void State::updateRotation() {
	std::vector<e3ga::vector> &u(m_u);
	std::vector<e3ga::vector> &v(m_v);


	for (unsigned int c = 1; c < m_cam.size(); c++) { // start at '1' because rotation of first camera is always 1
		u.resize(m_pt.size());
		v.resize(m_pt.size());

		Camera &C = m_cam[c];

		vector tmp;
		int nbVisible = 0;
		for (unsigned int i = 0; i < m_pt.size(); i++) {
			if (C.m_visible[i] && m_ptValid[i]) {
				tmp += m_pt[i];
				nbVisible++;
			}
		}
		tmp *= 1.0f / (mv::Float)nbVisible;

		int idx = 0;
		for (unsigned int i = 0; i < m_pt.size(); i++) {
			if (C.m_visible[i] && m_ptValid[i]) {
				v[idx] = _vector(C.m_X3[i]  * C.m_pt[i]);
				u[idx] = _vector(m_pt[i] - tmp);
				idx++;
			}
		}
		v.resize(idx);
		u.resize(idx);

//		printf("OldR = %s,\n", e3ga::string(C.m_R));
		C.setR(constructFrame2FrameRotorLS(v, u));
//		printf("visallR = %s,\n", e3ga::string(C.m_R));

//		int xxxx = 1;
	}
}
double State::costFunction() {
	double cost = 0.0;
	int nb = 0;

	for (unsigned int c = 0; c < m_cam.size(); c++) {
		const rotor &R = m_cam[c].m_R;
		rotor Ri = _rotor(inverse(R));
		const vector &t = m_cam[c].m_t;
		for (unsigned int i = 0; i < m_pt.size(); i++) {
			if (!(m_cam[c].m_visible[i] && m_ptValid[i])) continue;
			vector C = _vector(m_cam[c].m_X3[i] * m_cam[c].m_pt[i] -
				_vector(Ri * (m_pt[i] - t) * R));
			double cc = _double(norm_e2(C));

			cost += cc;
			nb++;
		}
	}

	return cost / nb;
}

namespace {
	template<class E> inline double computeEqns(
		const e3ga::vector **camPt,
		const e3ga::vector **dir,
		e3ga::vector &lhs, E e, int nb) {
		double rhs = 0.0;

		for (int i = 0; i < nb; i++) {
			mv::Float x2 = _Float(norm_e2(*(dir[i]))); // x2 = length of dir squared

			lhs += _vector((_Float(*(dir[i]) % e)/ x2) * *(dir[i]));

			rhs += _double(*(camPt[i]) % e) -
				_double(scp(*(dir[i]), *(camPt[i]))) * _double(*(dir[i]) % e) / x2;
		}

		lhs = _vector(e - lhs * (1.0f / (mv::Float)nb));
		return rhs / nb;
	}

e3ga::vector reconstructSingleMarkerFrom2D(
	const e3ga::vector *camPt[],
	const e3ga::vector *dir[], int nb) {

	double rhs;
	vector lhs;
	double eqMatrix[3 * 3], b[3];

	// e1 direction
	rhs = computeEqns(camPt, dir, lhs, e1, nb);
	eqMatrix[0 * 3 + 0] = lhs.e1();
	eqMatrix[1 * 3 + 0] = lhs.e2();
	eqMatrix[2 * 3 + 0] = lhs.e3();
	b[0] = rhs;

	// e2 direction
	lhs.set(); // set to 0
	rhs = computeEqns(camPt, dir, lhs, e2, nb);
	eqMatrix[0 * 3 + 1] = lhs.e1();
	eqMatrix[1 * 3 + 1] = lhs.e2();
	eqMatrix[2 * 3 + 1] = lhs.e3();
	b[1] = rhs;

	// e3 direction
	lhs.set(); // set to 0
	rhs = computeEqns(camPt, dir, lhs, e3, nb);
	eqMatrix[0 * 3 + 2] = lhs.e1();
	eqMatrix[1 * 3 + 2] = lhs.e2();
	eqMatrix[2 * 3 + 2] = lhs.e3();
	b[2] = rhs;

	// compute LU factorization (IPP)
/*	Ipp32u dstIndex[3];
	Ipp64f LU[9], R[3];
	ippmLUDecomp_m_64f_3x3(eqMatrix, 3 * sizeof(double), dstIndex, LU, 3 * sizeof(double));
	ippmLUBackSubst_mv_64f_3x3(LU, 3 * sizeof(double), dstIndex, b, R);
	normalizedPoint pt = c3gaPoint(R[0], R[1], R[2]);
	return e3ga::vector(vector_e1_e2_e3, (mv::Float)R[0], (mv::Float)R[1], (mv::Float)R[2]);*/

#ifdef USE_OPENCV
	double tmp[3] = {b[0], b[1], b[2]};
	CvMat A= cvMat(3, 3, CV_64F, eqMatrix);
	CvMat X = cvMat(3, 1, CV_64F, b);
	CvMat B = cvMat(3, 1, CV_64F, tmp);

	cvSolve(&A, &B, &X, CV_SVD);
#else
	// compute LU factorization (MKL)
	char trans = 'n';
	int lap_m = 3, lap_n = 3, ipiv[3], lda = 3, ldb = 3, info = 0, nrhs = 1;
	DGETRF(&lap_m, &lap_n, eqMatrix, &lda, ipiv, &info);
	//  DGETRS solves A * X = B given A in LU factorization
	DGETRS(&trans, &lap_n, &nrhs, eqMatrix, &lda, ipiv, b, &ldb, &info);
#endif

	return e3ga::vector(vector_e1_e2_e3, (mv::Float)b[0], (mv::Float)b[1], (mv::Float)b[2]);
}
} // end of anon. namespace


void State::reconstructPoints() {
	std::vector<e3ga::vector> _camPt(m_cam.size());
	std::vector<e3ga::vector> _dir(m_cam.size());

	// init camera positions:
	for (unsigned int c = 0; c < m_cam.size(); c++) {
		_camPt[c] = m_cam[c].m_t;
	}


	// reconstruct each point
	const e3ga::vector** camPt = new const e3ga::vector*[m_cam.size()];
	const e3ga::vector** dir = new const e3ga::vector*[m_cam.size()];
	for (unsigned int i = 0; i < m_pt.size(); i++) {
		int idx = 0;
		for (unsigned int c = 0; c < m_cam.size(); c++) {
			if (!m_cam[c].m_visible[i]) continue;
			camPt[idx] = &(_camPt[c]);
			_dir[c] = _vector(m_cam[c].m_R * m_cam[c].m_pt[i] * inverse(m_cam[c].m_R));
			dir[idx] = &(_dir[c]);

			idx++;
		}

		if (idx >= 2) {
			m_pt[i] = reconstructSingleMarkerFrom2D(camPt, dir, idx);
			m_ptValid[i] = true;
		}
	}

	delete[] camPt;
	delete[] dir;
}


} // end of namespace extCalibRefine
