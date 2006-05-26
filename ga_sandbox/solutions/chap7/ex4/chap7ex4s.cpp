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

// Daniel Fontijne -- fontijne@science.uva.nl

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/timing.h>

#include <vector>

using namespace e3ga;

void rotorToMatrixClassic(const rotor &R, float M[9]) {
	float qw = _Float(R);
	float qx = -R.e2e3(); 
	float qy = -R.e3e1(); 
	float qz = -R.e1e2(); 

	M[0 * 3 + 0] = 1.0f - 2.0f * qy * qy - 2.0f * qz * qz;
	M[1 * 3 + 0] = 2.0f * (qx * qy + qz * qw);
	M[2 * 3 + 0] = 2.0f * (qx * qz - qy * qw);

	M[0 * 3 + 1] = 2.0f * (qx * qy - qz * qw);
	M[1 * 3 + 1] = 1.0f - 2.0f * qx * qx - 2.0f * qz * qz;
	M[2 * 3 + 1] = 2.0f * (qy * qz + qx * qw);

	M[0 * 3 + 2] = 2.0f * (qx * qz + qy * qw);
	M[1 * 3 + 2] = 2.0f * (qy * qz - qx * qw);
	M[2 * 3 + 2] = 1.0f - 2.0f * qx * qx - 2.0f * qy * qy;
}


rotor matrixToRotorClassic(const float M[9]) {
	float trace = M[0 * 3 + 0] + M[1 * 3 + 1] + M[2 * 3 + 2] + 1.0f;
	float qw; // scalar coordinate
	float qx; // coordinate for -e2^e3
	float qy; // coordinate for -e3^e1
	float qz; // coordinate for -e1^e2
	if (trace > 0.00001f) {
	    float s = 0.5f / (float)sqrt(trace);
	    qw = 0.25f / s;
	    qw = sqrt(trace) * (0.5f);
	    qx = (M[2 * 3 + 1] - M[1 * 3 + 2]) * s;
	    qy = (M[0 * 3 + 2] - M[2 * 3 + 0]) * s;
	    qz = (M[1 * 3 + 0] - M[0 * 3 + 1]) * s;
	}
	else {
	    if (M[0 * 3 + 0] > M[1 * 3 + 1] && M[0 * 3 + 0] > M[2 * 3 + 2]) {
			float s = 2.0f * (float)sqrt( 1.0f + M[0 * 3 + 0] - M[1 * 3 + 1] - M[2 * 3 + 2]);
			qx = 0.25f * s;
			qy = (M[0 * 3 + 1] + M[1 * 3 + 0]) / s;
			qz = (M[0 * 3 + 2] + M[2 * 3 + 0]) / s;
			qw = (M[1 * 3 + 2] - M[2 * 3 + 1]) / s;
	    }
	    else if (M[1 * 3 + 1] > M[2 * 3 + 2]) {
			float s = 2.0f * (float)sqrt( 1.0f + M[1 * 3 + 1] - M[0 * 3 + 0] - M[2 * 3 + 2]);
			qx = (M[0 * 3 + 1] + M[1 * 3 + 0]) / s;
			qy = 0.25f * s;
			qz = (M[1 * 3 + 2] + M[2 * 3 + 1]) / s;
			qw = (M[0 * 3 + 2] - M[2 * 3 + 0]) / s;
	    }
	    else {
			float s = 2.0f * (float)sqrt( 1.0f + M[2 * 3 + 2] - M[0 * 3 + 0] - M[1 * 3 + 1] );
			qx = (M[0 * 3 + 2] + M[2 * 3 + 0]) / s;
			qy = (M[1 * 3 + 2] + M[2 * 3 + 1]) / s;
			qz = 0.25f * s;
			qw = (M[0 * 3 + 1] - M[1 * 3 + 0]) / s;
	    }
	}

	float s = sqrt(qw *qw + qx * qx + qy * qy + qz * qz);
	
	
	return rotor(rotor_scalar_e1e2_e2e3_e3e1, qw / s, -qz / s, -qx / s, -qy / s);
}


void rotorToMatrixGeo(const rotor &R, float M[9]) {
	// compute images of the basis vectors:
	rotor Ri = _rotor(inverse(R));
	e3ga::vector image[3] = {
		_vector(unit_e(_vector(R * e1 * Ri))), // image of e1
		_vector(unit_e(_vector(R * e2 * Ri))), // image of e2
		_vector(unit_e(_vector(R * e3 * Ri))) // image of e3
	};

	// copy coordinates to matrix:
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			M[j * 3 + i] = image[i].getC(vector_e1_e2_e3)[j];
}

rotor matrixToRotorStable(const float M[9]) {
	e3ga::vector imageOfE1(vector_e1_e2_e3, M[0 * 3 + 0], M[1 * 3 + 0], M[2 * 3 + 0]);
	e3ga::vector imageOfE2(vector_e1_e2_e3, M[0 * 3 + 1], M[1 * 3 + 1], M[2 * 3 + 1]);
	e3ga::vector imageOfE3(vector_e1_e2_e3, M[0 * 3 + 2], M[1 * 3 + 2], M[2 * 3 + 2]);

	if (M[0 * 3 + 0] > -0.9f) {
		rotor R1 = rotorFromVectorToVector(_vector(e1), imageOfE1);
		rotor R2 = rotorFromVectorToVector(_vector(R1 * e2 * inverse(R1)), imageOfE2, _bivector(dual(imageOfE1)));
		return _rotor(unit_e(R2 * R1));
	}
	else if (M[1 * 3 + 1] > -0.9f) {
		rotor R1 = rotorFromVectorToVector(_vector(e2), imageOfE2);
		rotor R2 = rotorFromVectorToVector(_vector(R1 * e3 * inverse(R1)), imageOfE3, _bivector(dual(imageOfE2)));
		return _rotor(unit_e(R2 * R1));
	}
	else {
		rotor R1 = rotorFromVectorToVector(_vector(e3), imageOfE3);
		rotor R2 = rotorFromVectorToVector(_vector(R1 * e1 * inverse(R1)), imageOfE1, _bivector(dual(imageOfE3)));
		return _rotor(unit_e(R2 * R1));
	}
}


using namespace e3ga;
int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();


	const int NB = 1000000;

	// create rotors, convert them to matrices
	std::vector<rotor> R(NB);
	for (int i = 0; i < NB; i++) {
		e3ga::vector v1 = _vector(randomBlade(1));
		e3ga::vector v2 = _vector(randomBlade(1));

		R[i] = _rotor(unit_r(v1 * v2));
	}

	// time classic rotor->matrix
	std::vector<float> Mc(NB*9);
	double classicRMT = u_timeGet();
	for (int i = 0; i < NB; i++) {
		rotorToMatrixClassic(R[i], &(Mc[i * 9]));
	}
	classicRMT = u_timeGet() - classicRMT;

	// time geometric rotor->matrix
	std::vector<float> Mg(NB*9);
	double geometricRMT = u_timeGet();
	for (int i = 0; i < NB; i++) {
		rotorToMatrixClassic(R[i], &(Mg[i * 9]));
	}
	geometricRMT = u_timeGet() - geometricRMT;

	// time classic matrix->rotor
	std::vector<rotor> classicR(NB);
	double classicMRT = u_timeGet();
	for (int i = 0; i < NB; i++) {
		classicR[i] = matrixToRotorClassic(&(Mc[i * 9]));
	}
	classicMRT = u_timeGet() - classicMRT;

	// time geometric matrix->rotor
	std::vector<rotor> geometricR(NB);
	double geometricMRT = u_timeGet();
	for (int i = 0; i < NB; i++) {
		geometricR[i] = matrixToRotorStable(&(Mg[i * 9]));
	}
	geometricMRT = u_timeGet() - geometricMRT;

	printf("Rotor -> Matrix time:\nClassic  : %f secs\nGeometric: %f secs\n", classicRMT, geometricRMT);
	printf("Matrix -> Rotor time:\nClassic  : %f secs\nGeometric: %f secs\n", classicMRT, geometricMRT);


	// check results (classic):
	double classicError = 0.0;
	for (int i = 0; i < NB; i++) {
		rotor R2 = classicR[i];
		float check1 = _Float(norm_e(R[i] * inverse(R2)));
		float check2 = fabs(_Float(R[i] * inverse(R2)));
		classicError += fabs(check1 - 1.0f) + fabs(check2 - 1.0f);

		if ((fabs(check1 - 1.0f) > 1e-5) || (fabs(check2 - 1.0f) > 1e-5)) {
			printf("Error in conversion (%e %e)!\n", check1 - 1.0f, check2 - 1.0f);
			printf("R  = %s\n", R[i].c_str_e());
			if (_Float(R[i]) / _Float(R2) < 0.0)
				R2 = -R2;
			printf("R2 = %s\n", R2.c_str_e());
		}
	}

	// check results (geometric):
	double geometricError = 0.0;
	for (int i = 0; i < NB; i++) {
		rotor R2 = geometricR[i];

		float check1 = _Float(norm_e(R[i] * inverse(R2)));
		float check2 = fabs(_Float(R[i] * inverse(R2)));
		geometricError += fabs(check1 - 1.0f) + fabs(check2 - 1.0f);

		if ((fabs(check1 - 1.0f) > 1e-5) || (fabs(check2 - 1.0f) > 1e-5)) {
			printf("Error in conversion (%e %e)!\n", check1 - 1.0f, check2 - 1.0f);
			printf("R  = %s\n", R[i].c_str_e());
			if (_Float(R[i]) / _Float(R2) < 0.0)
				R2 = -R2;
			printf("R2 = %s\n", R2.c_str_e());
		}
	}

	printf("Error: Classic: %f secs, Geometric: %f secs\n", classicError, geometricError);
	


	return 0;
}

