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

#ifndef _C3GA_DRAW_H_
#define _C3GA_DRAW_H_

#include "c3ga_analyze.h"

namespace c3ga {

namespace drawConst {
extern const double POINT_SIZE;
extern const double LINE_LENGTH;
extern const double PLANE_SIZE;
}


/// uses OpenGL to draw a analyzed multivector
void draw(const mvAnalysis &A);

/**
Returns the position where a label can be drawn for multivector 'A'
Thows -1 when no position can be generated (e.g., a scalar)
*/
normalizedPoint labelPosition(const mvAnalysis &A, int labelGenerator = 0);

}


#endif 
/* _C3GA_DRAW_H_ */



