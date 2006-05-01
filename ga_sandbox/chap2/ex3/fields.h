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

#ifndef _MRS_FIELDS_H_
#define _MRS_FIELDS_H_

#include <libgasandbox/e3ga.h>
using namespace e3ga;

extern double g_fieldsCurrentTime; // should be set to current time before calling the eval functions


extern float g_dx;
extern float g_dy;
extern float g_dz;
extern float g_omega;
extern float g_gamma;
extern float g_Rcore;
  
vector &vortex(const vector& p, vector& v);
vector &vortexS(const vector &p, vector &v);
vector &vortexA(const vector &p, vector &v);
vector &vortexO(const vector &p, vector &v);
vector &point3(const vector &p, vector &v);
vector &line3(const vector &p, vector &v);
vector &testFunc3(const vector &p, vector &v);
vector &testFunc4(const vector &p, vector &v);
vector &testFunc5(const vector &p, vector &v);
vector &testFunc6(const vector &p, vector &v);
vector &testFunc7(const vector &p, vector &v);
vector &testFunc8(const vector &p, vector &v);
vector &testFunc9(const vector &p, vector &v);
vector &testFunc10(const vector &p, vector &v);
vector &testFunc11(const vector &p, vector &v);
vector &testFunc12(const vector &p, vector &v);
vector &testFunc13(const vector &p, vector &v);
vector &testFunc14(const vector &p, vector &v);
vector &testFunc15(const vector &p, vector &v);
vector &testFunc16(const vector &p, vector &v);
vector &testFunc16a(const vector &p, vector &v);
vector &testFunc17(const vector &p, vector &v);
vector &testFunc18(const vector &p, vector &v);
vector &helix3(const vector &p, vector &v);
vector &const3(const vector &p, vector &v);
vector &circ3(const vector &p, vector &v);
vector &sphere3(const vector &p, vector &v);
vector &eight2(const vector &p, vector &v);


#endif /* _MRS_FIELDS_H_ */
