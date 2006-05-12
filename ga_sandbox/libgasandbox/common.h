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

#ifndef _COMMON_H_
#define _COMMON_H_
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

#define U_RAD2DEG( x ) ( (x) * (float)180.0 / (float)M_PI)
#define U_DEG2RAD( x ) ( (x) * (float)M_PI / (float)180.0)


#endif
/* _COMMON_H_ */
