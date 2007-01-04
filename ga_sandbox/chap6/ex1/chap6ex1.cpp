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

using namespace e3ga;

// exercise 1a: complete in this function
mv outerProduct_1a(const e3ga::vector &a, const mv &B) {
	printf("Warning: outerProduct_1a() not implemented yet!\n");
	return 0.0f;
}

// exercise 1a: complete in this function
mv leftContraction_1a(const e3ga::vector &a, const mv &B) {
	printf("Warning: leftContraction_1a() not implemented yet!\n");
	return 0.0f;
}

// exercise 1b: complete in this function
mv outerProduct_1b(const mv &A, const mv &B) {
	printf("Warning: outerProduct_1b() not implemented yet!\n");
	return 0.0f;
}

// exercise 1b: complete in this function
mv leftContraction_1b(const mv &A, const mv &B) {
	printf("Warning: leftContraction_1b() not implemented yet!\n");
	return 0.0f;
}

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();

	const int NB_TESTS = 100000;

	// A test for Exercise 1a
	// We generate random vectors and random multivectors, and use
	// the regular outer product/left contraction functions to verify the results:
	bool OK1a = true;
	for (int i = 0; i < NB_TESTS; i++) {
		e3ga::vector a = _vector(randomBlade(1));
		mv B = randomMultivector(GRADE_1 | GRADE_2 | GRADE_3);

		// test outer product
		{
			mv X = op(a, B);
			mv Y = outerProduct_1a(a, B);

			if (_Float(norm_e2(X - Y)) > 1e-7f) {
				// Not equal: complain
				printf("\n\nouterProduct_1a() failed for\n%s\nand\n%s\n", a.toString_f().c_str(), B.toString_f().c_str());
				OK1a = false;
			}
		}

		// test left contraction
		{
			mv X = lcont(a, B);
			mv Y = leftContraction_1a(a, B);
			/*intf("a  = %s\n", a.toString_e().c_str());
			printf("B  = %s\n", B.toString_e().c_str());
			printf("X  = %s\n", X.toString_e().c_str());
			printf("Y  = %s\n", Y.toString_e().c_str());*/

			if (_Float(norm_e2(X - Y)) > 1e-7f) {
				// Not equal: complain
				printf("\n\nleftContraction_1a() failed for\n%s\nand\n%s\n", a.toString_f().c_str(), B.toString_f().c_str());
			}
		}
	}
	if (OK1a)
		printf("outerProduct_1a() and leftContraction_1a() seem to be OK.\n");

	
	// A test for Exercise 1b
	// We generate pairs of random multivector, and use
	// the regular outer product/left contraction functions to verify the results:
	bool OK1b = true;
	for (int i = 0; i < NB_TESTS; i++) {
		mv A = randomMultivector();
		mv B = randomMultivector();

		// test outer product
		{
			mv X = op(A, B);
			mv Y = outerProduct_1b(A, B);
			if (_Float(norm_e2(X - Y)) > 1e-7f) {
				// Not equal: complain
				printf("\n\nouterProduct_1b() failed for\n%s\nand\n%s\n", A.toString().c_str(), B.toString().c_str());
				OK1b = false;
			}
		}

		// test left contraction
	{
			mv X = lcont(A, B);
			mv Y = leftContraction_1b(A, B);
			if (_Float(norm_e2(X - Y)) > 1e-7f) {
				// Not equal: complain
				printf("\n\nleftContraction_1b() failed for\n%s\nand\n%s\n", A.toString().c_str(), B.toString().c_str());
				OK1b = false;
			}
		}
	}

	if (OK1b)
		printf("outerProduct_1b() and leftContraction_1b() seem to be OK.\n");


	return 0;
}

