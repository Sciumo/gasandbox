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

#include <math.h>

#include <libgasandbox/timing.h>

/*
This file contains all the field evaluators 
that came with the original matlab code
and some extra simple ones
*/

#include "fields.h"

extern float g_dx;
extern float g_dy;
extern float g_dz;
extern float g_omega;
extern float g_gamma;
extern float g_Rcore;

double g_fieldsCurrentTime = 0;

  
vector &vortex(const vector& p, vector& v) {
  
  float r;

  r = sqrtf(g_dx*g_dx + g_dy*g_dy + g_dz*g_dz);
  vector axis(vector_e1_e2_e3, g_dx/r,g_dy/r,g_dz/r);

  v = g_omega*axis+g_gamma*(((p^axis)*inverse(axis))*(axis*I3i));
  return v;	
}

/* Vortex field with varying perp component that may put a point singularity
   in the field */
vector &vortexS(const vector &p, vector &v) {
  float r;

  r = sqrtf(g_dx*g_dx + g_dy*g_dy + g_dz*g_dz);
  vector axis(vector_e1_e2_e3, g_dx/r,g_dy/r,g_dz/r);

  v = g_omega*((p<<axis)*inverse(axis))+g_gamma*(((p^axis)*inverse(axis))*(axis*I3i));
  return v;	
}

/* simple z-axis aligned vortex field */
vector &vortexA(const vector &p, vector &v) {
  float r;

  r = sqrtf(p.e1()*p.e1() + p.e2()*p.e2());
  v.set(vector_e1_e2_e3,-p.e2()/r,p.e1()/r,g_Rcore);
  return v;	
}

/* vortex field from paper */
vector &vortexO(const vector &p, vector &v) {
	float r;
	float z;
	r = sqrtf(p.e1()*p.e1() + p.e2()*p.e2());
	z = (float)(g_omega*(1.-g_Rcore/r));
	v.set(vector_e1_e2_e3, 
	      -g_gamma*p.e2()/r - g_omega*p.e3()*p.e1()/(r*r),
	      g_gamma*p.e1()/r - g_omega*p.e3()*p.e2()/(r*r),
	      z);
	return v;
}

vector &point3(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
		-p.e1(),
		-p.e2(), 
		-p.e3());
	return v;
}

vector &line3(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
		2.0f * (p.e1()),
		2.0f * (p.e2()), 
		0);
	return v;
}

vector &testFunc3(const vector &p, vector &v) {
	float c[3] = {p.e1() + 0.05f, p.e2() + 0.05f, p.e3() + 0.05f};
	v.set(vector_e1_e2_e3, 
		0,
		0, 
		5.0f * (p.e1() * p.e1() + p.e2() * p.e2()));
	return v;
}


vector &testFunc4(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      3*p.e1()*p.e1()*p.e2()*p.e2()*p.e2()*p.e3()*p.e3(),
	      3*p.e1()*p.e1()*p.e1()*p.e2()*p.e2()*p.e3()*p.e3(),
	      2*p.e1()*p.e1()*p.e1()*p.e2()*p.e2()*p.e2()*p.e3());
	return v;
}


vector &testFunc5(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      3*p.e1()*p.e1(),
	      3*p.e2()*p.e2(),
	      2*p.e3());
	return v;
}


vector &testFunc6(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      3*p.e1()*p.e1()+2*p.e1(),
	      3*p.e2()*p.e2(),
	      0);
	return v;
}

vector &testFunc7(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      3*p.e1()*p.e1()*p.e2()*p.e2()*p.e2(),
	      3*p.e1()*p.e1()*p.e1()*p.e2()*p.e2(),
	      0);
	return v;
}

vector &testFunc8(const vector &p, vector &v) {
	
	bivector ii = _bivector(e1 ^ e2);
	rotor z =  _rotor(p.e1()+p.e2()*ii);
	rotor f = _rotor(z*z * inverse(z + 2) * inverse(z - 0.8f));
	v.set(vector_e1_e2_e3, _Float(f), f.e1e2(), 0.0f);
	return v;
}

vector &testFunc9(const vector &p, vector &v) {
	
	bivector ii = _bivector(e1 ^ e2);
	rotor z = _rotor(p.e1()+p.e2()*ii);
	rotor f = _rotor(inverse(z));
	v.set(vector_e1_e2_e3, _Float(f), f.e1e2(), 0.0f);
	return v;
}

vector &testFunc10(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      3*p.e1()*p.e1(),
	      3*p.e2()*p.e2(),
	      3*p.e3()*p.e3());
	return v;
}

vector &testFunc11(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      4*p.e1()*p.e1()*p.e1(),
	      4*p.e2()*p.e2()*p.e2(),
	      4*p.e3()*p.e3()*p.e3());
	return v;
}

vector &testFunc12(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      4*p.e1()*(p.e1()*p.e1()+p.e2()*p.e2()-p.e3()),
	      4*p.e2()*(p.e1()*p.e1()+p.e2()*p.e2()-p.e3()),
	      -2*(p.e1()*p.e1()+p.e2()*p.e2()-p.e3()));
	return v;
}

// ((p.e1()-0.5)*(p.e1()-0.5)+p.e2()*p.e2()-1)^2*(p.e1()*p.e1()+p.e2()*p.e2()+p.e3()*p.e3()-1)^2
vector &testFunc13(const vector &p, vector &v) {
	
	float A =(float)((p.e1()-0.5)*(p.e1()-0.5)+p.e2()*p.e2()-1.0f);
	float B = (float)(p.e1()*p.e1()+p.e2()*p.e2()+p.e3()*p.e3()-1.0f);
	v.set(vector_e1_e2_e3, 
	      4.0f*(p.e1()-0.5f)*A*B*B + 4*p.e1()*A*A*B,
	      4.0f*p.e2()*A*B*B + 4*p.e2()*A*A*B,
	      4.0f*p.e3()*A*A*B);
	return v;
}

// ((p.e1()-0.5)*(p.e1()-0.5)+p.e2()*p.e2()-1)^2 + (p.e1()*p.e1()+p.e2()*p.e2()+p.e3()*p.e3()-1)^2
vector &testFunc14(const vector &p, vector &v) {
	
	float A =((p.e1()-0.5f)*(p.e1()-0.5f)+p.e2()*p.e2()-1.0f);
	float B = (p.e1()*p.e1()+p.e2()*p.e2()+p.e3()*p.e3()-1.0f);
	v.set(vector_e1_e2_e3, 
	      4.0f*(p.e1()-0.5f)*A + 4.0f*p.e1()*B,
	      4.0f*p.e2()*A + 4.0f*p.e2()*B,
	      4.0f*p.e3()*B);
	return v;
}

// helix - 1 / [(x-cos(z))^2 + (y-sin(z))^2] = 1/A
vector &testFunc15(const vector &p, vector &v) {
	
	float cz = cos(p.e3()*2.0f); float sz = sin(p.e3()*2.0f);
	float A = (p.e1()-cz)*(p.e1()-cz) + (p.e2()-sz)*(p.e2()-sz);
	v.set(vector_e1_e2_e3, 
	      -2.0f*(p.e1()-cz)/(A*A),
	      -2.0f*(p.e2()-sz)/(A*A),
	      -2.0f*(-(p.e1()-cz)*sz+(p.e2()-sz)*cz)/(A*A));
	      
	return v;
}

vector &testFunc16(const vector &p, vector &v) {
	
	vector A = _vector(p.e1() * e1 + p.e2() * e2);
	vector B = _vector(sqrtf(p.e1()*p.e1()+p.e2()*p.e2())*e1);
	vector C = _vector(A * inverse(B) * A);
	v.set(vector_e1_e2_e3, 2.0f*C.e1(), 2.0f*C.e2(), 0.0f);
	return v;
}

vector &testFunc16a(const vector &p, vector &v) {
	vector A = _vector(p.e1()*e1 + p.e2()* e2);
	vector B = _vector(sqrtf(p.e1()*p.e1()+p.e2()*p.e2())*e1);
	vector C = _vector(A * inverse(B) * A);
	v.set(vector_e1_e2_e3, 2*C.e1(), 2*C.e2(), 2*p.e3());
	if ( 0 && fabs(C.e1())+fabs(C.e2())+fabs(C.e3()) < 1e-1 ) {
	  printf("*** p %g %g %g, cc %g %g %g\n",p.e1(),p.e2(),p.e3(), C.e1(), C.e2(), C.e3());
	  printf("    A = %g e1 + %g e2,   B = %g e1\n",
		 p.e1(), p.e2(), sqrtf(p.e1()*p.e1()+p.e2()*p.e2()));
	}
	return v;
}

// x^3/3 - xy^2 + z^2
vector &testFunc17(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      p.e1()*p.e1()-p.e2()*p.e2(),
	      -2*p.e1()*p.e2(),
	      2*p.e3());
	return v;
}

// x^3/3 - xy^2
vector &testFunc18(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
	      p.e1()*p.e1()-p.e2()*p.e2(),
	      -2*p.e1()*p.e2(),
	      0.0f);
	return v;
}

vector &helix3(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 
		-p.e2(), p.e1(),
		(p.e1() * p.e1() + p.e2() * p.e2()) * p.e3());
	return v;
}

vector &const3(const vector &p, vector &v) {
	
	v.set(vector_e1_e2_e3, 1.0, 1.0, 1.0);
	return v;
}


/*
function [vx,vy,vz]=circ3(x,y,z)
	vx = 4*(x^2+y^2-1)*x*e1;
	vy = 4*(x^2+y^2-1)*y*e2;
	vz = 2*z*e3;
*/
vector &circ3(const vector &p, vector &v) {
	// fastest method:
	
	v.set(vector_e1_e2_e3,
		4 * (p.e1() * p.e1() + p.e2() * p.e2() - 1) * p.e1(), // e1 coordinate
		4 * (p.e1() * p.e1() + p.e2() * p.e2() - 1) * p.e2(), // e2 coordinate
		2 * p.e3()); // e3 coordinates

	/* less efficient alternative:
	v = 4 * (p.e1() * p.e1() + p.e2() * p.e2() - 1) * p.e1() * e3ga::e1 + 
		4 * (p.e1() * p.e1() + p.e2() * p.e2() - 1) * p.e2() * e3ga::e2 + 
		2 * p.e3() * e3ga::e3;
	*/

	/* (even less efficient) alternative:
	float e1c = p << e3ga::e1;
	float e2c = p << e3ga::e2;
	float e3c = p << e3ga::e3;
	v = 4 * (e1c * e1c + e2c * e2c - 1) * e1c * e3ga::e1 + 
		4 * (e1c * e1c + e2c * e2c - 1) * e2c * e3ga::e2 + 
		2 * e3c * e3ga::e3;
	*/
	return v;
}


/*
function [vx,vy,vz]=sphere3(x,y,z)
	vx = 4*(x^2+y^2+z^2-1)*x*e1;
	vy = 4*(x^2+y^2+z^2-1)*y*e2;
	vz = 4*(x^2+y^2+z^2-1)*z*e3;
*/
vector &sphere3(const vector &p, vector &v) {
	// fastest method:
	
	v.set(vector_e1_e2_e3,
		4 * (p.e1() * p.e1() + p.e2() * p.e2() + p.e3() * p.e3() - 1) * p.e1(), // e1 coordinate
		4 * (p.e1() * p.e1() + p.e2() * p.e2() + p.e3() * p.e3() - 1) * p.e2(), // e2 coordinate
		4 * (p.e1() * p.e1() + p.e2() * p.e2() + p.e3() * p.e3() - 1) * p.e3()); // e3 coordinate
	return v;
}

/*
function [vx,vy,vz]=eight2(x,y,z)
vx = (2*((x-1)^2+y^2-1)*x*(((x+1)^2+y^2-1)^2+z^2) + 2*((x+1)^2+y^2-1)*x*(((x-1)^2+y^2-1)^2+z^2))*e1;
vy = (2*((x-1)^2+y^2-1)*y*(((x+1)^2+y^2-1)^2+z^2) + 2*((x+1)^2+y^2-1)*y*(((x-1)^2+y^2-1)^2+z^2))*e2;
vz = (2*z*(((x+1)^2+y^2-1)^2+z^2)+2*z*(((x-1)^2+y^2-1)^2+z^2))*e3;
*/
vector &eight2(const vector &p, vector &v) {
	// fastest method:
	
	float tmp1, tmp2;

	tmp1 = (p.e1()+1) * (p.e1()+1)+p.e2() * p.e2()-1;
	tmp2 = (p.e1()-1) * (p.e1()-1)+p.e2() * p.e2()-1;
	tmp1 *= 2.0f;
	tmp2 *= 2.0f;


	v.set(vector_e1_e2_e3,
		(2*((p.e1()-1) * (p.e1()-1)+p.e2() * p.e2()-1)*p.e1()*(tmp1 +p.e3() * p.e3()) + 
		2*((p.e1()+1) * (p.e1()+1)+p.e2() * p.e2()-1)*p.e1()*(tmp2 +p.e3() * p.e3())),
		(2*((p.e1()-1) * (p.e1()-1)+p.e2() * p.e2()-1)*p.e2()*(tmp1 +p.e3() * p.e3()) +
		2*((p.e1()+1) * (p.e1()+1)+p.e2() * p.e2()-1)*p.e2()*(tmp2 +p.e3() * p.e3())),
		(2*p.e3()*( tmp1+p.e3() * p.e3())+2*p.e3()*( tmp2+p.e3() * p.e3())));
	return v;
}

