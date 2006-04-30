#ifndef _MRS_FIELDS_H_
#define _MRS_FIELDS_H_

#include "e3ga.h"

extern double g_fieldsCurrentTime; // should be set to current time before calling the eval functions

e3ga & vortex(const e3ga &p, e3ga &v);
e3ga & const3(const e3ga &p, e3ga &v);
e3ga & point3(const e3ga &p, e3ga &v);
e3ga & line3(const e3ga &p, e3ga &v);
e3ga & circ3(const e3ga &p, e3ga &v);
e3ga & sphere3(const e3ga &p, e3ga &v);
e3ga & eight2(const e3ga &p, e3ga &v);
e3ga & helix3(const e3ga &p, e3ga &v);


e3ga & testFunc3(const e3ga &p, e3ga &v);
e3ga & testFunc4(const e3ga &p, e3ga &v);
e3ga & testFunc5(const e3ga &p, e3ga &v);
e3ga & testFunc6(const e3ga &p, e3ga &v);
e3ga & testFunc7(const e3ga &p, e3ga &v);
e3ga & testFunc8(const e3ga &p, e3ga &v);
e3ga & testFunc9(const e3ga &p, e3ga &v);
e3ga & testFunc10(const e3ga &p, e3ga &v);
e3ga & testFunc11(const e3ga &p, e3ga &v);
e3ga & testFunc12(const e3ga &p, e3ga &v);
e3ga & testFunc13(const e3ga &p, e3ga &v);
e3ga & testFunc14(const e3ga &p, e3ga &v);
e3ga & testFunc15(const e3ga &p, e3ga &v);
e3ga & testFunc16(const e3ga &p, e3ga &v);
e3ga & testFunc16a(const e3ga &p, e3ga &v);
e3ga & testFunc17(const e3ga &p, e3ga &v);
e3ga & testFunc18(const e3ga &p, e3ga &v);


#endif /* _MRS_FIELDS_H_ */
