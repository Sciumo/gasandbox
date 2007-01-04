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

#include <libgasandbox/c3ga.h>
#include <libgasandbox/c3ga_util.h>

#include <vector>

using namespace c3ga;


TRSversor generateRandomTRSversor() {
	vectorE3GA tv = _vectorE3GA(randomBlade(1));
	vectorE3GA rv1 = _vectorE3GA(randomBlade(1));
	vectorE3GA rv2 = _vectorE3GA(randomBlade(1));
	mv::Float s = (mv::Float)(1 + rand()) / (mv::Float)RAND_MAX;

	return _TRSversor(exp(_freeVector(tv ^ ni)) * exp(_bivectorE3GA(rv1 ^ rv2)) * exp(_noni_t(s * noni)));
}



int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	c3ga::g2Profiling::init();

	const int NB_CHECKS = 100000;
	printf("Checking that exp(log(V)) == V for %d random translate-rotate-scale versors\n", NB_CHECKS);
	
	int nbErrors = 0;
	for (int i = 0; i < NB_CHECKS; i++) {
		TRSversor V = _TRSversor(generateRandomTRSversor() * generateRandomTRSversor());
		
		TRSversorLog P = log(V);
		
		mv X = exp(P);
		
		mv dif1 = X * inverse(V);
		mv dif2 = inverse(V) * X;
		
		if ((fabs(_Float(norm_e(dif1)) - 1.0f) > 1e-4f) || (fabs(_Float(norm_e(dif2)) - 1.0f) > 1e-4f)) {
			printf("Error for V = %s\n", V.c_str_e20());
			nbErrors++;
		}
	}
	printf("Done (%d errors)!\n", nbErrors);

	return 0;
}

