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
int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();

	const int NB = 1000000;
	std::vector<e3ga::vector> A(NB);
	std::vector<e3ga::bivector> B(NB);
	std::vector<e3ga::trivector> Co(NB);
	std::vector<e3ga::mv> Cj(NB);

	// generate 'NB' random vectors, and 'NB' random bivectors
	for (int i = 0; i < NB; i++) {
		A[i] = _vector(randomBlade(1));
		B[i] = _bivector(randomBlade(2));
	}

	// time the outer product
	double tOuter = u_timeGet();
	for (int i = 0; i < NB; i++) {
		Co[i] = _trivector(B[i] ^ A[i]);
	}
	tOuter = u_timeGet() - tOuter;

	double tJoin = u_timeGet();
	for (int i = 0; i < NB; i++) {
		Cj[i] = join(A[i], B[i]);
	}
	tJoin = u_timeGet() - tJoin;

	printf("%d outer products: %f seconds\n", NB, tOuter);
	printf("%d joins: %f seconds\n", NB, tJoin);


	return 0;
}

