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

#ifndef _HP_INDEX_H_
#define _HP_INDEX_H_

#include <libgasandbox/e3ga.h>

int sumFace(const vector &p, const vector &v1, const vector &v2, 
	    const int gsi, vector &sum3d, int &lineSing, int &surfSing,
	    vector & (*evalFunc)(const vector &p, vector &v), int depth, 
	    int maxDepth, int face);

int sumCube(const vector &p, const vector dir[3],
		 const int gsi, int &pointSing, int &lineSing, int &surfSing,
		 vector & (*evalFunc)(const vector &p, vector &v), int depth, int maxDepth);

int	findSingularities(const vector &p, const vector dir[3],
		 const int gsi, vector & (*evalFunc)(const vector &p, vector &v), int depth, int maxDepth);

	// simple function to draw sphere of vectors around one cube
	void drawSphere(int gs, int type);
	void drawCirc(int gs, int type);

#endif /* _HP_INDEX_H_ */
