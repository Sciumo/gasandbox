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

#include <stdio.h>
#include <stdlib.h>
#include <libgasandbox/c2ga.h>
#include <libgasandbox/c2ga_util.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <../../qhull-2003.1/src/qhull_a.h>
#ifdef __cplusplus
}
#endif /* __cplusplus */

using namespace c2ga;


int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	c2ga::g2Profiling::init();

	// init qhull
	qh_init_A (stdin, stdout, stderr, 0, NULL);
	if (setjmp (qh errexit)) {
		fprintf(stderr, "qhull generated error\n");
		return -1;
	}

	qh_initflags("qhull Qx i s Tcv C-0");
	

	/* setup geometry for qhull */
	const int NB_VERTICES = 4;
	coordT *qhCoord = new coordT[4 * 3];
	qhCoord[0 * 3 + 0] = 1.0;
	qhCoord[0 * 3 + 1] = -2.0;
	qhCoord[0 * 3 + 2] = 1.0;
	qhCoord[1 * 3 + 0] = 2.0;
	qhCoord[1 * 3 + 1] = 1.0;
	qhCoord[1 * 3 + 2] = 4.0;
	qhCoord[2 * 3 + 0] = 0.0;
	qhCoord[2 * 3 + 1] = 1.0;
	qhCoord[2 * 3 + 2] = 1.0;
	qhCoord[3 * 3 + 0] = 1.0;
	qhCoord[3 * 3 + 1] = 1.0;
	qhCoord[3 * 3 + 2] = -1.0;
	
	/* do the qhull */
	qh_init_B(qhCoord, NB_VERTICES, 3, 0);
	qh_qhull();
	qh_check_output();

	{
		facetT *facet;
		vertexT *vertex;
		vertexT **vertexp;
		int qhCurlong, qhTotlong;
		FORALLfacets {
			setT *vertices = vertices = qh_facet3vertex (facet);
			FOREACHvertex_(vertices) {
			
				/* get idindex of this vertex */
				int idx = qh_pointid(vertex->point);
				printf("idx: %d, pos: %f %f %f\n", idx, vertex->point[0], vertex->point[1], vertex->point[2]);
			}

			qh_settempfree(&vertices);
			
		}


		/* free resources */
		qh_freeqhull(!qh_ALL);
		qh_memfreeshort(&qhCurlong, &qhTotlong);
		delete[] qhCoord;
	}



	return 0;
}

