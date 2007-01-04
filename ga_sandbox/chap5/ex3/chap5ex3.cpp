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
#include <libgasandbox/mv_analyze.h>

#include <vector>

using namespace e3ga;
using namespace mv_analyze;


int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();

	// get two vectors, initialize them to 'e1'
	vector a, b;
	a = e1;
//	b = e1;

	float probeEpsilon = 1e-10f;
	
	while (true) {// the loop will be broken when the join is a bivector;
		// add a tiny bit of 'e2' to b:
		b = e1 + probeEpsilon * e2;

		// compute the join
		mv X = join(a, b);

		// get analysis of 'X'
		mvAnalysis AX(X);

		// check if blade, and if a blade, then is it a 2-blade or a vector?
		if (!AX.isBlade()) {
			// this should never happen
			printf("Error: the join of a and b is not a blade!\n");
			return -1;
		}
		else {
			// compute string "join(..., ...)"
			std::string str = "join(" + a.toString_e() + ", " + b.toString_e() + ")";

			if (AX.bladeSubclass() == mvAnalysis::BIVECTOR) {
				printf("%s is a 2-blade\n", str.c_str());
				return 0; // terminate
			}
			else printf("%s is a vector\n", str.c_str());
		}
		
		// Grow 'probeEpsilon' a little such that it won't take forever to reach 
		// the point where join(a, b) is a 2-blade:
		probeEpsilon *= 1.01f;
	};

	return 0;
}

