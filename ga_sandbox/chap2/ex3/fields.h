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
