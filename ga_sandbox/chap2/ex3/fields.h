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
  
e3ga::vector &vortex(const e3ga::vector& p, e3ga::vector& v);
e3ga::vector &vortexS(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &vortexA(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &vortexO(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &point3(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &line3(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc3(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc4(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc5(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc6(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc7(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc8(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc9(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc10(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc11(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc12(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc13(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc14(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc15(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc16(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc16a(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc17(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &testFunc18(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &helix3(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &const3(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &circ3(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &sphere3(const e3ga::vector &p, e3ga::vector &v);
e3ga::vector &eight2(const e3ga::vector &p, e3ga::vector &v);


#endif /* _MRS_FIELDS_H_ */
