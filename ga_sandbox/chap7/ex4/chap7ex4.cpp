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

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/timing.h>

#include <vector>

using namespace e3ga;

// exercise: fill in this function
void rotorToMatrixClassic(const rotor &R, float M[9]) {
	printf("Warning: rotorToMatrixClassic() not implemented.\n");
}


// exercise: fill in this function
rotor matrixToRotorClassic(const float M[9]) {
	printf("Warning: matrixToRotorClassic() not implemented.\n");
	return _rotor(1.0f);
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

rotor matrixToRotorGeo(const float M[9]) {
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

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();

	const int NB = 1000000;
	printf("Sample of size  %d \n", NB);

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
		rotorToMatrixGeo(R[i], &(Mg[i * 9]));
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
		geometricR[i] = matrixToRotorGeo(&(Mg[i * 9]));
	}
	geometricMRT = u_timeGet() - geometricMRT;

	printf("Rotor -> Matrix time:\nClassic  : %f secs\nGeometric: %f secs\n", classicRMT, geometricRMT);
	printf("Matrix -> Rotor time:\nClassic  : %f secs\nGeometric: %f secs\n", classicMRT, geometricMRT);


    // check results (classic):
	double classicError = 0.0;
	double classicMaxError = 0;
	for (int i = 0; i < NB; i++) {
		rotor R2 = classicR[i];

		mv dR = R[i] * inverse(R2);
		float check1 = _Float(norm_e(dR-1));
		float check2 = _Float(norm_e(dR+1));
		bool unitR=(check1<check2);
		if(!unitR)check1=check2;
 		if(classicMaxError<check1)classicMaxError=check1;
		classicError += check1;
		if (check1 > 1e-5) {
			printf("Error matrix->rotor (classic) in conversion (%e)!\n", check1);
			printf("R  = %s\n", R[i].c_str_e());
			printf("R2 = %s\n", (unitR?R2:-R2).c_str_e());
		}
    }

    // check results (geometric):
	double geometricError = 0.0;
	double geometricMaxError = 0;
	for (int i = 0; i < NB; i++) {
		rotor R2 = geometricR[i];

		mv dR = R[i] * inverse(R2);
		float check1 = _Float(norm_e(dR-1));
		float check2 = _Float(norm_e(dR+1));
		bool unitR=(check1<check2);
		if(!unitR)check1=check2;
		if(geometricMaxError<check1)geometricMaxError=check1;
		geometricError += check1;
		if (check1 > 1e-5) {
			printf("Error matrix->rotor (classic) in conversion (%e)!\n", check1);
			printf("R  = %s\n", R[i].c_str_e());
			printf("R2 = %s\n", (unitR?R2:-R2).c_str_e());
		}

    }

	printf("Mean relative error matrix->rotor: Classic: %.2e , Geometric: %.3e \n", classicError/NB, geometricError/NB);
	printf("Max relative error matrix->rotor: Classic: %.2g , Geometric: %.3g \n", classicMaxError, geometricMaxError);
	return 0;
}

