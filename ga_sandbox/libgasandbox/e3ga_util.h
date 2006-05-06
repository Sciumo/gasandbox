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

#ifndef _E3GA_UTIL_H_
#define _E3GA_UTIL_H_

#include "e3ga.h"
#include "common.h"
#include <vector>

namespace e3ga {

rotor rotorFromVectorToVector(const vector &v1, const vector &v2);
mv exp(const mv &x, int order = 9);
mv::Float factorizeBlade(const mv &X, vector factor[], int gradeOfX = -1);


/**
Computes the reciprocal frame 'RF' of input frame 'IF'
Throws std::string when vectors in 'IF' are not independent, 
or if one of the IF[i] is null.
*/
void reciprocalFrame(const e3ga::vector *IF, e3ga::vector *RF, int nbVectors);

} /* end of namespace e3ga */

#endif /* _E3GA_UTIL_H_ */
