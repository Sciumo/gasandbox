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

using namespace e3ga;

// *!*HTML_TAG*!* rotorToMatrix
void rotorToMatrixGeo(const rotor &R, float M[9]) {
	// compute images of the basis vectors:
	rotor Ri = _rotor(inverse(R));
	e3ga::vector image[3] = {
		_vector(unit_e(R * e1 * Ri)), // image of e1
		_vector(unit_e(R * e2 * Ri)), // image of e2
		_vector(unit_e(R * e3 * Ri)) // image of e3
	};

	// copy coordinates to matrix:
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			M[j * 3 + i] = image[i].getC(vector_e1_e2_e3)[j];
}

// note: very inprecise in some situations; do NOT use this function
rotor matrixToRotorGeoInprecise(const float M[9]) {
	e3ga::vector imageOfE1(vector_e1_e2_e3, M[0 * 3 + 0], M[1 * 3 + 0], M[2 * 3 + 0]);
	e3ga::vector imageOfE2(vector_e1_e2_e3, M[0 * 3 + 1], M[1 * 3 + 1], M[2 * 3 + 1]);

	rotor R1 = rotorFromVectorToVector(_vector(e1), imageOfE1);
	rotor R2 = rotorFromVectorToVector(_vector(R1 * e2 * inverse(R1)), imageOfE2, _bivector(dual(imageOfE1)));

	return _rotor(R2 * R1);
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

	printf("This example program converts rotors to matrices and back again.\n");
	printf("The results are checked for errors.\n\n");

	const int NB = 10000000;
	printf("Going to perform %d iterations . . .\n", NB);

	int nbErrors = 0;
	float check0 = 0;
	
	for (int i = 0; i < NB; i++) {
		if (i && ((i % (NB/10)) == 0))
			printf("Performed %d iterations . . .\n", i);

		// make up random rotor:
		e3ga::vector v1 = _vector(randomBlade(1));
		e3ga::vector v2 = _vector(randomBlade(1));
		rotor R = _rotor(unit_r(v1 * v2));

		// convert to matrix 'M' and back to rotor 'R2' again
		float M[9];
		rotorToMatrixGeo(R, M);
		rotor R2 = matrixToRotorGeo(M);

		// check results: (error check improved by Allan Cortzen)
		mv dR = R * inverse(R2);
		float check1 = _Float(norm_e(dR-1));
		float check2 = _Float(norm_e(dR+1));
		if(check1 > check2) check1 = check2;
 		if(check0 < check1) check0 = check1;

		if (check1 > 1e-5) {
			nbErrors++;
			printf("Iteration %d: error in conversion (%e)!\n", i, check1);
			printf("R = %s\n", R.c_str_e());
			printf("R2 = %s\n", R2.c_str_e());
		}

	}
	printf("Sample of size  %d  has max relative error  %e !\n", NB, check0);

	printf("Performed %d iterations, %d errors\n", NB, nbErrors);


	return 0;
}

