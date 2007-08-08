
// Generated on 2007-08-08 10:15:15 by G2 0.1 from 'E:\gasandbox\ga_sandbox\libgasandbox\e3ga.gs2'

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


#include "e3ga.h"

namespace e3ga {

	namespace {
		// 1.0*e1
		void projectE1ontoG2(const float *c, float *v) {
			v[0] = 0.0f;
			v[1] = 1.0f * c[0];
			v[2] = -1.0f * c[2];
		}
		// 1.0*e2
		void projectE2ontoG2(const float *c, float *v) {
			v[0] = -1.0f * c[0];
			v[1] = 0.0f;
			v[2] = 1.0f * c[1];
		}
		// 1.0*e3
		void projectE3ontoG2(const float *c, float *v) {
			v[0] = 1.0f * c[2];
			v[1] = -1.0f * c[1];
			v[2] = 0.0f;
		}
		typedef void (*projectFuncfloat)(const float*, float*);
		projectFuncfloat g_projectFuncTable_float[8] = {
			NULL, 
				projectE1ontoG2, 
				projectE2ontoG2, 
				NULL, 
				projectE3ontoG2, 
				NULL, 
				NULL, 
				NULL
		};
	} // end of anonymous namespace

	namespace {
		inline unsigned int bitCount(unsigned int i) {
			i = i - ((i >> 1) & 0x55555555);
			i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
			i = (i + (i >> 4)) & 0x0F0F0F0F;
			i = i + (i >> 8);
			i = i + (i >> 16);
			return i & 0x0000003F;
		}

		inline unsigned int lowestOneBit(unsigned int i) {
			return bitCount(~i & (i - 1));
		}


	} // end of anonymous namespace

	/**
	Factorizes blades. Input coordinates as defined by general multivector type.
	Return of vectors as defined by vector type.

	Input:
	k = grade of input
	c = coordinates of input
	ortho = orthogonalize factors (if not orthogonalized, scale will not have the correct value

	Output:
	scale: used to return scale of blade
	factors: array of points to arrays of float [3][3]

	*/
	int fastFactor(
	int k,
		const float *c,
		float **factors,
		float &scale,
		bool ortho) {
		const int N = 3;

		if (k == 0) {
			scale = 0.0f;
			return 0;
		}

		// pseudoscalar?
		if (k == N) {
			factors[0][1] = factors[0][2] = 			
				factors[1][0] = factors[1][2] = 			
				factors[2][0] = factors[2][1] = 			
				0.0f;
			factors[0][0] = factors[1][1] = factors[2][2] =  1.0f;

			scale = c[0] * 1.0f;
			return N;
		}

		float inputScale = c[0] * c[0];
		{
			int nbBlades = mv_gradeSize[k];
			for (int i = 1; i < nbBlades; i++) inputScale += c[i] * c[i];	
			inputScale = sqrt(inputScale);
		}

		// zero input?:
		if (inputScale == 0.0f) {
			scale = 0.0f;
			return 0;
		}

		// vector?
		if (k == 1) {
			// copy all vector coords to first factor:
			factors[0][0] = c[0] / inputScale;
			factors[0][1] = c[1] / inputScale;
			factors[0][2] = c[2] / inputScale;
			scale = inputScale; 
			return 1;  
		}

		// find largest basis blade:
		int baseIndex = mv_size[(1 << k) - 1]; // get base index for grade 'k'
		int bmE = mv_basisElementBitmapByIndex[baseIndex + 0];
		float scE = c[0] * (float)mv_basisElementSignByIndex[baseIndex + 0];
		{
			float scC = (c[0] < 0.0f) ? -c[0] : c[0];
			for (int i = 1; i < mv_gradeSize[k]; i++) {
				float ciAbs = (c[i] < 0.0f) ? -c[i] : c[i];
				if (ciAbs > scC) {
					scC = ciAbs;
					bmE = mv_basisElementBitmapByIndex[baseIndex + i];
					scE = c[i] * (float)mv_basisElementSignByIndex[baseIndex + i];
				}
			}
		}

		// compute scale (sign)
		scale = inputScale;
		if (scE < 0) {
			scale *= -1.0f;

			// take care of orientation of blade:
			if ((k & 1) == 1) scale *= -1.0f;
		}

		// fix sign issues (see Leo's notes)
		if ((k % 4) == 2) scale *= -1.0f;


		// `project' each of the basis vectors onto the blade
		int fIdx = 0;
		for (int i = 0; i < 3; i++) {
			int bvM = 1 << i;
			if ((bmE & bvM) == 0) continue;

			// compute inner product of (bmE ^ bvM) . bmE
			int bm = bmE ^ bvM;
			g_projectFuncTable_float[bm](c, factors[fIdx]);

			fIdx++;
			if (fIdx == k) break;
		}


		if (ortho) { // do a gram-schmidt of the factors
			for (int i = 0; i < k; i++) {
				float *Fi = factors[i];

				// subtract all ortho factor so far:
				for (int j = 0; j < i; j++) {
					const float *Fj = factors[j];

					// inner product with ortho factors so far:
					float s = Fi[0] * Fj[0] + Fi[1] * Fj[1] + Fi[2] * Fj[2] ;

					// subtract s * factors[j] from factors[i]:
					Fi[0] -= s * Fj[0];
					Fi[1] -= s * Fj[1];
					Fi[2] -= s * Fj[2];
				}

				// normalize each factor
				float n = sqrtf(Fi[0] * Fi[0] + Fi[1] * Fi[1] + Fi[2] * Fi[2] );
				if (n != 0.0f) {
					Fi[0] /= n;
					Fi[1] /= n;
					Fi[2] /= n;
				}
			}
		}

		return k;
	}

	mv::Float fastFactorBlade(const mv &X, vector factor[3], int gradeOfX /* = -1 */) {
		int k = gradeOfX;
		if (k < 0) {
			// only for single grade usage: find first non-zero grade part:
			k = lowestOneBit(X.m_gu);
			if (k > 3) return 0.0; // invalid input
		}

		// collect arguments to fastFactor()
		const mv::Float *c = X.m_c;
		mv::Float *factors[3] = {factor[0].m_c, factor[1].m_c , factor[2].m_c };
		mv::Float scale;
		const bool ortho = true;

		k = fastFactor(k, c, factors, scale, ortho);

		return scale;
	}




	namespace {
		float popEG1(const float *A, const float *B, float *R) {
			R[0] =  + -1.0f * A[1] * B[0] + 1.0f * A[0] * B[1];
			R[1] =  + -1.0f * A[2] * B[1] + 1.0f * A[1] * B[2];
			R[2] =  + 1.0f * A[2] * B[0] + -1.0f * A[0] * B[2];
			return B[0] * B[0] + B[1] * B[1] + B[2] * B[2];
		}
		float popEG2(const float *A, const float *B, float *R) {
			R[0] =  + 1.0f * A[1] * B[0] + 1.0f * A[2] * B[1] + 1.0f * A[0] * B[2];
			return B[0] * B[0] + B[1] * B[1] + B[2] * B[2];
		}
		float popE1G2(const float *A, const float *B, float *R) {
			R[0] =  + 1.0f * A[2] * B[0] + -1.0f * A[0] * B[2];
			return B[0] * B[0] + B[2] * B[2];
		}
		float popE2G2(const float *A, const float *B, float *R) {
			R[0] =  + -1.0f * A[1] * B[0] + 1.0f * A[0] * B[1];
			return B[0] * B[0] + B[1] * B[1];
		}
		float popE3G2(const float *A, const float *B, float *R) {
			R[0] =  + -1.0f * A[2] * B[1] + 1.0f * A[1] * B[2];
			return B[1] * B[1] + B[2] * B[2];
		}
		typedef float (*popFunc)(const float*, const float*, float*);
		popFunc g_popFuncTable_float[3][8] = {
			{ // grade 0
				NULL, 
				NULL, 
					NULL, 
					NULL, 
					NULL, 
					NULL, 
					NULL, 
					NULL
			},
			{ // grade 1
				popEG1, 
				NULL, 
					NULL, 
					NULL, 
					NULL, 
					NULL, 
					NULL, 
					NULL
			},
			{ // grade 2
				popEG2, 
				popE1G2, 
					popE2G2, 
					NULL, 
					popE3G2, 
					NULL, 
					NULL, 
					NULL
			}
		};
		void meetFromJoin_A1_B1_J1(const float *A, const float *B, const float *J, float *M) {
			M[0] = 1.0f * A[0] * B[0] * J[0] + 1.0f * A[0] * B[1] * J[1] + 1.0f * A[0] * B[2] * J[2];
			M[1] = 1.0f * A[1] * B[0] * J[0] + 1.0f * A[1] * B[1] * J[1] + 1.0f * A[1] * B[2] * J[2];
			M[2] = 1.0f * A[2] * B[0] * J[0] + 1.0f * A[2] * B[1] * J[1] + 1.0f * A[2] * B[2] * J[2];
		}
		void meetFromJoin_A1_B1_J2(const float *A, const float *B, const float *J, float *M) {
			M[0] = 1.0f * A[0] * B[1] * J[0] + -1.0f * A[0] * B[2] * J[2] + -1.0f * A[1] * B[0] * J[0] + 1.0f * A[1] * B[2] * J[1] + 1.0f * A[2] * B[0] * J[2] + -1.0f * A[2] * B[1] * J[1];
		}
		void meetFromJoin_A2_B1_J1(const float *A, const float *B, const float *J, float *M) {
			M[0] = 1.0f * A[0] * B[0] * J[0] + 1.0f * A[0] * B[1] * J[1] + 1.0f * A[0] * B[2] * J[2];
			M[1] = 1.0f * A[1] * B[0] * J[0] + 1.0f * A[1] * B[1] * J[1] + 1.0f * A[1] * B[2] * J[2];
			M[2] = 1.0f * A[2] * B[0] * J[0] + 1.0f * A[2] * B[1] * J[1] + 1.0f * A[2] * B[2] * J[2];
		}
		void meetFromJoin_A2_B1_J2(const float *A, const float *B, const float *J, float *M) {
			M[0] = 1.0f * A[0] * B[0] * J[0] + -1.0f * A[0] * B[2] * J[1] + 1.0f * A[2] * B[0] * J[2] + -1.0f * A[2] * B[1] * J[1];
			M[1] = 1.0f * A[0] * B[1] * J[0] + -1.0f * A[0] * B[2] * J[2] + -1.0f * A[1] * B[0] * J[2] + 1.0f * A[1] * B[1] * J[1];
			M[2] = -1.0f * A[1] * B[0] * J[0] + 1.0f * A[1] * B[2] * J[1] + -1.0f * A[2] * B[1] * J[0] + 1.0f * A[2] * B[2] * J[2];
		}
		void meetFromJoin_A2_B1_J3(const float *A, const float *B, const float *J, float *M) {
			M[0] = 1.0f * A[0] * B[2] * J[0] + 1.0f * A[1] * B[0] * J[0] + 1.0f * A[2] * B[1] * J[0];
		}
		void meetFromJoin_A2_B2_J2(const float *A, const float *B, const float *J, float *M) {
			M[0] = 1.0f * A[0] * B[0] * J[0] + 1.0f * A[0] * B[1] * J[1] + 1.0f * A[0] * B[2] * J[2];
			M[1] = 1.0f * A[1] * B[0] * J[0] + 1.0f * A[1] * B[1] * J[1] + 1.0f * A[1] * B[2] * J[2];
			M[2] = 1.0f * A[2] * B[0] * J[0] + 1.0f * A[2] * B[1] * J[1] + 1.0f * A[2] * B[2] * J[2];
		}
		void meetFromJoin_A2_B2_J3(const float *A, const float *B, const float *J, float *M) {
			M[0] = -1.0f * A[0] * B[2] * J[0] + 1.0f * A[2] * B[0] * J[0];
			M[1] = 1.0f * A[0] * B[1] * J[0] + -1.0f * A[1] * B[0] * J[0];
			M[2] = 1.0f * A[1] * B[2] * J[0] + -1.0f * A[2] * B[1] * J[0];
		}
		typedef void (*meetFromJoinFunc_float)(const float*, const float*, const float*, float*);
		meetFromJoinFunc_float meetFromJoinTable_float[4][4][4]  = {
			{
				{NULL,NULL,NULL,NULL},
				{NULL,NULL,NULL,NULL},
				{NULL,NULL,NULL,NULL},
				{NULL,NULL,NULL,NULL}
			},
			{
				{NULL,NULL,NULL,NULL},
				{NULL,meetFromJoin_A1_B1_J1,meetFromJoin_A1_B1_J2,NULL},
				{NULL,NULL,NULL,NULL},
				{NULL,NULL,NULL,NULL}
			},
			{
				{NULL,NULL,NULL,NULL},
				{NULL,meetFromJoin_A2_B1_J1,meetFromJoin_A2_B1_J2,meetFromJoin_A2_B1_J3},
				{NULL,NULL,meetFromJoin_A2_B2_J2,meetFromJoin_A2_B2_J3},
				{NULL,NULL,NULL,NULL}
			},
			{
				{NULL,NULL,NULL,NULL},
				{NULL,NULL,NULL,NULL},
				{NULL,NULL,NULL,NULL},
				{NULL,NULL,NULL,NULL}
			}
		};
	} // end of anonymous namespace


	namespace {
		/// returns true when input blade is zero
		inline bool zero(int grade, const float *coord) {
			int nb = mv_gradeSize[grade];
			for (int i = 0; i < nb; i++)
			if (coord[i] != 0.0f) return false;
			return true;
		}

		/// sets a blade to zero
		inline void setBladeZero(int &grade, float *coord) {
			grade = 0;
			coord[0] = 0.0f;
		}

		inline void setBladeScalar(int &grade, float *coord, float val = 1.0f) {
			grade = 0;
			coord[0] = val;
		}

		inline void setBladePseudo(int &grade, float *coord, float val = 1.0f) {
			grade = 3;
			coord[0] = val;
		}

		inline void copyBlade(int gradeSrc, const float *coordSrc, int &gradeDst, float *coordDst) {
			gradeDst = gradeSrc;

			coordDst[0] = coordSrc[0];
			if ((gradeSrc == 0) || (gradeSrc == 3)) return;
			coordDst[1] = coordSrc[1];
			coordDst[2] = coordSrc[2];

			/*
			int nb = mv_gradeSize[gradeSrc];
			for (int i = 0; i < nb; i++)
			coordDst[i] = coordSrc[i];
			*/
		}

		/// computes the Euclidean norm, squared
		inline float norm_e2(int grade, const float *coord) {
			float n2 = coord[0] * coord[0];
			int nb = mv_gradeSize[grade];
			for (int i = 1; i < nb; i++) n2 += coord[i] * coord[i];
			return n2;
		}

		inline void makeUnit(int g, float *c, float n2) {
			float n = sqrtf(n2);
			int nb = mv_gradeSize[g];
			for (int i = 0; i < nb; i++) c[i] /= n;
		}

		inline void makeUnit(int g, float *c) {
			makeUnit(g, c, norm_e2(g, c));
		}


		inline void copyAndMakeUnit(int gradeSrc, const float *coordSrc, int &gradeDst, float *coordDst, float mul = 1.0f) {
			gradeDst = gradeSrc;
			float n = mul * sqrtf(norm_e2(gradeSrc, coordSrc));
			int nb = mv_gradeSize[gradeSrc];
			for (int i = 0; i < nb; i++) 
			coordDst[i] = coordSrc[i] / n;
		}

		inline float largestCoordSign(int grade, const float *coord) {
			int nb = mv_gradeSize[grade];
			float lcSign = (coord[0] < 0.0f) ? -1.0f : 1.0f;
			float lc = (coord[0] < 0.0f) ? -coord[0] : coord[0];
			for (int i = 1; i < nb; i++) {
				float c = (coord[i] < 0.0f) ? -coord[i] : coord[i];
				if (c > lc) {
					lc = c;
					lcSign = (coord[i] < 0.0f) ? -1.0f : 1.0f;
				}
			}
			return lcSign;
		}


		inline float computeSwapSignFix(int gradeA, int gradeB) {
			// the fix for swapping arguments is described in Stolfi (Ch 5?), ask Leo
			return ((gradeA * gradeB) & 1) ? -1.0f : 1.0f; 
		}

		inline void swp(int &a, int &b) {
			int tmp = a;
			a = b;
			b = tmp;
		}

		inline void swp(const float *&a, const float *&b) {
			const float *tmp = a;
			a = b;
			b = tmp;
		}

		inline void swp(float *&a, float *&b) {
			float *tmp = a;
			a = b;
			b = tmp;
		}
	}

	/**
	Computes the join of 'A' and 'B'.
	Coordinates of blades are in order defined by general multivector

	Input:
	gradeA, gradeB: grade of A and B range [0 ... 3]
	coordA, coordB: coordinates of A and B (size of array defined by grade)

	Returns:
	gradeJ: grade of join
	coordJ: coordinates of join
	if (gradeM != NULL) also returns:
	gradeM: grade of the meet
	coordM: coordinates of meet

	*/
	void fastJoin(
	int gradeA, const float *coordA, 
		int gradeB, const float *coordB, 
		int &gradeJ, float *coordJ,
		int *gradeM /* = NULL */, float *coordM /* = NULL */
		) {
		// filter out trivial cases:
		if (zero(gradeA, coordA) || zero(gradeB, coordB)) { // null arguments?
			setBladeZero(gradeJ, coordJ);
			if (gradeM != NULL) setBladeZero(*gradeM, coordM);
			return;
		}
		else if (gradeA == 0) { // A is scalar?
			copyAndMakeUnit(gradeB, coordB, gradeJ, coordJ);
			if (gradeM != NULL) setBladeScalar(*gradeM, coordM);
			return;
		}
		else if (gradeB == 0) { // B is scalar?
			copyAndMakeUnit(gradeA, coordA, gradeJ, coordJ);
			if (gradeM != NULL) setBladeScalar(*gradeM, coordM);
			return;
		}
		else if (gradeA == 3) { // A is pseudoscalar?
			setBladePseudo(gradeJ, coordJ);
			if (gradeM != NULL) copyAndMakeUnit(gradeB, coordB, *gradeM, coordM); // todo: get orientation right w.r.t. Join?
			return;
		}
		else if (gradeB == 3) { // B is pseudoscalar?
			setBladePseudo(gradeJ, coordJ, computeSwapSignFix(gradeA, gradeB));
			if (gradeM != NULL) copyAndMakeUnit(gradeA, coordA, *gradeM, coordM, computeSwapSignFix(gradeA, gradeB)); // todo: get orientation right w.r.t. Join?
			return;
		}

		// swap A and B, if required, such that gradeA >= gradeB
		float swapSignFix = 1.0f;
		if (gradeA < gradeB) {
			swapSignFix = computeSwapSignFix(gradeA, gradeB);
			swp(coordA, coordB);
			swp(gradeA, gradeB);
		}

		int M;
		{ // rate the basis blades of B, find the best one, store it in 'M'
			int nbCoordB = mv_gradeSize[gradeB];
			float bestB = -1.0f;
			int baseIndex = mv_size[(1 << gradeB) - 1]; // get base index for gradeB
			for (int i = 0; i < nbCoordB; i++) {
				// get the coordinate, bitmap
				float b = (coordB[i] < 0.0f) ? -coordB[i] : coordB[i];
				// if scale is highest so far, store it:
				if (b > bestB) {bestB = b; M = mv_basisElementBitmapByIndex[baseIndex + i];}
			}
			if (bestB == 0.0f) { // B is 0, so join is 0
				setBladeZero(gradeJ, coordJ);
				if (gradeM != NULL) setBladeZero(*gradeM, coordM);
				return;
			}
		}

		// copy A to J
		copyBlade(gradeA, coordA, gradeJ, coordJ);
		float *coordJoriginal = coordJ; // remember the pointer which the user supplied

		{ // project basis vectors bvM onto B, wedge to A
			const float EPS = 1e-6f;
			int i = 0;
			float tmp1[8]; // an array of n choose floor(n/2) would be large enough
			float *Jtmp = tmp1;
			for (int i = 1; i <= M; i <<= 1) {
				if ((M & i) == 0) continue;

				// project basis blade (M xor i) onto  B, and compute outer product with J:
				float n2 = g_popFuncTable_float[gradeJ][M ^ i](coordJ, coordB, Jtmp);

				// if the result (Atmp) is not 0, then accept:
				n2 = norm_e2(gradeJ + 1, Jtmp) / n2;
				if (n2 > EPS * EPS) {
					gradeJ++;
					swp(Jtmp, coordJ);
					makeUnit(gradeJ, coordJ, n2);
					if (gradeJ == 3) break; // terminate when J is pseudoscalar
				}
			}
		}

		// swap and optionally apply sign fix due to swapping:
		swapSignFix *= largestCoordSign(gradeJ, coordJ);
		if (coordJ != coordJoriginal) {
			int nb = mv_gradeSize[gradeJ];
			for (int i = 0; i < nb; i++)
			coordJoriginal[i] = swapSignFix * coordJ[i];
		}
		else {
			int nb = mv_gradeSize[gradeJ];
			for (int i = 0; i < nb; i++)
			coordJ[i] = swapSignFix * coordJ[i];
		}

		// if requested also compute the meet
		if (gradeM != 0) {
			*gradeM = gradeA + gradeB - gradeJ;
			meetFromJoinTable_float[gradeA][gradeB][gradeJ](coordA, coordB, coordJ, coordM);
			makeUnit(*gradeM, coordM);
		}

	}



	void fastJoinBlades(const mv &A, const mv &B, mv &J, mv *M /* = NULL */) {

		// collect arguments to fastJoin()
		int gradeA = lowestOneBit(A.m_gu);
		const mv::Float *coordA = A.m_c;
		int gradeB = lowestOneBit(B.m_gu);
		const mv::Float *coordB = B.m_c;	
		mv::Float *coordJ = J.m_c; // this assumes memory is allocated (which it is, since it is an array)
		int gradeJ;

		if (M != NULL) {
			// compute the meet, too
			int gradeM;
			mv::Float *coordM = M->m_c;
			fastJoin(gradeA, coordA, gradeB, coordB, gradeJ, coordJ, &gradeM, coordM);
			M->m_gu = 1 << gradeM;
		}
		else {
			// compute just the join
			fastJoin(gradeA, coordA, gradeB, coordB, gradeJ, coordJ, NULL, NULL);
		}

		// set grade usage of join
		J.m_gu = 1 << gradeJ;

	}







} // end of namespace e3ga

