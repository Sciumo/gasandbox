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
#include <libgasandbox/timing.h>
#include <libgasandbox/mv_analyze.h>

#include <vector>

using namespace c3ga;

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	c3ga::g2Profiling::init();

	// get the basis vectors:
	mv bv[5] = {no, e1, e2, e3, ni};

	// print out the metric:
	printf("Metric:\n");
	printf("    ");
	for (int i = 0; i < 5; i++)
		printf(" %s  ", mv_basisVectorNames[i]);
	printf("\n");
	
	for (int i = 0; i < 5; i++) {
		printf("%s ", mv_basisVectorNames[i]);
		for (int j = 0; j < 5; j++) {
			printf(" % 1.1f", _Float(bv[i] << bv[j]));
		}
		printf("\n");
	}

	printf("\n");

	// create 'e+' and 'e-'
	dualSphere ep = _dualSphere(no - 0.5f * ni);
	dualSphere em = _dualSphere(no + 0.5f * ni);

	// print ep and em
	printf("e+ and e-:\n");
	printf("e+ = %s\n", ep.c_str());
	printf("e- = %s\n", em.c_str());
	printf("\n");
	printf("The metric of e+ and e-:\n");
	printf("e+ . e+ = %f\n", _Float(ep << ep));
	printf("e- . e- = %f\n", _Float(em << em));
	printf("e+ . e- = %f\n", _Float(ep << em));





	return 0;
}

