#include <math.h>

/*
This file contains all the field evaluators 
that came with the original matlab code
and some extra simple ones
*/

#include "fields.h"
#include "timing.h"

double g_fieldsCurrentTime = 0;

e3ga & vortex(const e3ga& p, e3ga& v) {
  const float *c = p[GRADE1];
  extern float g_dx;
  extern float g_dy;
  extern float g_dz;
  extern float g_omega;
  extern float g_gamma;
  extern float g_Rcore;
  float r;

  r = sqrt(g_dx*g_dx + g_dy*g_dy + g_dz*g_dz);
  e3ga axis;
  axis.set(GRADE1,g_dx/r,g_dy/r,g_dz/r);

  v = g_omega*axis+g_gamma*((p^axis/axis)*(axis/e3ga::I));
  return v;	
}

/* Vortex field with varying perp component that may put a point singularity
   in the field */
e3ga & vortexS(const e3ga& p, e3ga& v) {
  const float *c = p[GRADE1];
  extern float g_dx;
  extern float g_dy;
  extern float g_dz;
  extern float g_omega;
  extern float g_gamma;
  extern float g_Rcore;
  float r;

  r = sqrt(g_dx*g_dx + g_dy*g_dy + g_dz*g_dz);
  e3ga axis;
  axis.set(GRADE1,g_dx/r,g_dy/r,g_dz/r);

  v = g_omega*((p<<axis)/axis)+g_gamma*((p^axis/axis)*(axis/e3ga::I));
  return v;	
}

/* simple z-axis aligned vortex field */
e3ga & vortexA(const e3ga& p, e3ga& v) {
  const float *c = p[GRADE1];
  extern float g_dx;
  extern float g_dy;
  extern float g_dz;
  extern float g_Rcore;
  float r;

  r = sqrt(c[0]*c[0] + c[1]*c[1]);
  v.set(GRADE1,-c[1]/r,c[0]/r,g_Rcore);
  return v;	
}

/* vortex field from paper */
e3ga & vortexO(const e3ga& p, e3ga& v) {
	const float *c = p[GRADE1];
	extern float g_omega;
	extern float g_gamma;
	extern float g_Rcore;
	float r;
	float z;
	r = sqrt(c[0]*c[0] + c[1]*c[1]);
	z = g_omega*(1.-g_Rcore/r);
	v.set(GRADE1, 
	      -g_gamma*c[1]/r - g_omega*c[2]*c[0]/(r*r),
	      g_gamma*c[0]/r - g_omega*c[2]*c[1]/(r*r),
	      z);
	return v;
}

e3ga & point3(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
		-c[0],
		-c[1], 
		-c[2]);
	return v;
}

e3ga & line3(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
		2.0f * (c[0]),
		2.0f * (c[1]), 
		0);
	return v;
}

e3ga & testFunc3(const e3ga &p, e3ga &v) {
	const float *ctmp = p[GRADE1];
	float c[3] = {ctmp[0] + 0.05, ctmp[1] + 0.05, ctmp[2] + 0.05};
	v.set(GRADE1, 
		0,
		0, 
		5.0f * (c[0] * c[0] + c[1] * c[1]));
	return v;
}


e3ga & testFunc4(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      3*c[0]*c[0]*c[1]*c[1]*c[1]*c[2]*c[2],
	      3*c[0]*c[0]*c[0]*c[1]*c[1]*c[2]*c[2],
	      2*c[0]*c[0]*c[0]*c[1]*c[1]*c[1]*c[2]);
	return v;
}


e3ga & testFunc5(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      3*c[0]*c[0],
	      3*c[1]*c[1],
	      2*c[2]);
	return v;
}


e3ga & testFunc6(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      3*c[0]*c[0]+2*c[0],
	      3*c[1]*c[1],
	      0);
	return v;
}

e3ga & testFunc7(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      3*c[0]*c[0]*c[1]*c[1]*c[1],
	      3*c[0]*c[0]*c[0]*c[1]*c[1],
	      0);
	return v;
}

e3ga & testFunc8(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	e3ga ii;
	ii = (e3ga)e3ga::e1 ^ (e3ga)e3ga::e2;
	e3ga z;
	z = c[0]+c[1]*ii;
	e3ga f;
	f = z*z / (z+2) / (z-.8);
	const float* cc = f[GRADE0];
	const float* ccc = f[GRADE2];
	//	printf("cc %g ccc %g %g %g\n",cc[0], ccc[0],ccc[1],ccc[2]);
	v.set(GRADE1, cc[0], ccc[2], 0);
	return v;
}

e3ga & testFunc9(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	e3ga ii;
	ii = (e3ga)e3ga::e1 ^ (e3ga)e3ga::e2;
	e3ga z;
	z = c[0]+c[1]*ii;
	e3ga f;
	f = 1./z;
	const float* cc = f[GRADE0];
	const float* ccc = f[GRADE2];
	//	printf("cc %g ccc %g %g %g\n",cc[0], ccc[0],ccc[1],ccc[2]);
	v.set(GRADE1, cc[0], ccc[2], 0);
	return v;
}

e3ga & testFunc10(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      3*c[0]*c[0],
	      3*c[1]*c[1],
	      3*c[2]*c[2]);
	return v;
}

e3ga & testFunc11(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      4*c[0]*c[0]*c[0],
	      4*c[1]*c[1]*c[1],
	      4*c[2]*c[2]*c[2]);
	return v;
}

e3ga & testFunc12(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      4*c[0]*(c[0]*c[0]+c[1]*c[1]-c[2]),
	      4*c[1]*(c[0]*c[0]+c[1]*c[1]-c[2]),
	      -2*(c[0]*c[0]+c[1]*c[1]-c[2]));
	return v;
}

// ((c[0]-0.5)*(c[0]-0.5)+c[1]*c[1]-1)^2*(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]-1)^2
e3ga & testFunc13(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	double A =((c[0]-0.5)*(c[0]-0.5)+c[1]*c[1]-1);
	double B = (c[0]*c[0]+c[1]*c[1]+c[2]*c[2]-1);
	v.set(GRADE1, 
	      4*(c[0]-0.5)*A*B*B + 4*c[0]*A*A*B,
	      4*c[1]*A*B*B + 4*c[1]*A*A*B,
	      4*c[2]*A*A*B);
	return v;
}

// ((c[0]-0.5)*(c[0]-0.5)+c[1]*c[1]-1)^2 + (c[0]*c[0]+c[1]*c[1]+c[2]*c[2]-1)^2
e3ga & testFunc14(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	double A =((c[0]-0.5)*(c[0]-0.5)+c[1]*c[1]-1);
	double B = (c[0]*c[0]+c[1]*c[1]+c[2]*c[2]-1);
	v.set(GRADE1, 
	      4*(c[0]-0.5)*A + 4*c[0]*B,
	      4*c[1]*A + 4*c[1]*B,
	      4*c[2]*B);
	return v;
}

// helix - 1 / [(x-cos(z))^2 + (y-sin(z))^2] = 1/A
e3ga & testFunc15(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	double cz = cos(c[2]*2.0f); double sz = sin(c[2]*2.0f);
	double A = (c[0]-cz)*(c[0]-cz) + (c[1]-sz)*(c[1]-sz);
	v.set(GRADE1, 
	      -2*(c[0]-cz)/(A*A),
	      -2*(c[1]-sz)/(A*A),
	      -2*(-(c[0]-cz)*sz+(c[1]-sz)*cz)/(A*A));
	      
	return v;
}

e3ga & testFunc16(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	e3ga A;
	A = (c[0]*(e3ga)e3ga::e1 + c[1]* (e3ga)e3ga::e2);
	e3ga B;
	B = sqrt(c[0]*c[0]+c[1]*c[1])*(e3ga)e3ga::e1;
	e3ga C;
	C = (A/B)*A;
	const float* cc = C[GRADE1];
	v.set(GRADE1, 2*cc[0], 2*cc[1], 0);
	return v;
}

e3ga & testFunc16a(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	e3ga A;
	A = (c[0]*(e3ga)e3ga::e1 + c[1]* (e3ga)e3ga::e2);
	e3ga B;
	B = sqrt(c[0]*c[0]+c[1]*c[1])*(e3ga)e3ga::e1;
	e3ga C;
	C = (A/B)*A;
	const float* cc = C[GRADE1];
	v.set(GRADE1, 2*cc[0], 2*cc[1], 2*c[2]);
	if ( 0 && fabs(cc[0])+fabs(cc[1])+fabs(cc[2]) < 1e-1 ) {
	  printf("*** p %g %g %g, cc %g %g %g\n",c[0],c[1],c[2],cc[0],cc[1],cc[2]);
	  printf("    A = %g e1 + %g e2,   B = %g e1\n",
		 c[0], c[1], sqrt(c[0]*c[0]+c[1]*c[1]));
	}
	return v;
}

// x^3/3 - xy^2 + z^2
e3ga & testFunc17(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      c[0]*c[0]-c[1]*c[1],
	      -2*c[0]*c[1],
	      2*c[2]);
	return v;
}

// x^3/3 - xy^2
e3ga & testFunc18(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
	      c[0]*c[0]-c[1]*c[1],
	      -2*c[0]*c[1],
	      0.0f);
	return v;
}

e3ga & helix3(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 
		-c[1], c[0],
		(c[0] * c[0] + c[1] * c[1]) * c[2]);
	return v;
}

e3ga & const3(const e3ga &p, e3ga &v) {
	const float *c = p[GRADE1];
	v.set(GRADE1, 1.0, 1.0, 1.0);
	return v;
}


/*
function [vx,vy,vz]=circ3(x,y,z)
	vx = 4*(x^2+y^2-1)*x*e1;
	vy = 4*(x^2+y^2-1)*y*e2;
	vz = 2*z*e3;
*/
e3ga & circ3(const e3ga &p, e3ga &v) {
	// fastest method:
	const float *c = p[GRADE1];
	v.set(GRADE1,
		4 * (c[0] * c[0] + c[1] * c[1] - 1) * c[0], // e1 coordinate
		4 * (c[0] * c[0] + c[1] * c[1] - 1) * c[1], // e2 coordinate
		2 * c[2]); // e3 coordinates

	/* less efficient alternative:
	v = 4 * (c[0] * c[0] + c[1] * c[1] - 1) * c[0] * e3ga::e1 + 
		4 * (c[0] * c[0] + c[1] * c[1] - 1) * c[1] * e3ga::e2 + 
		2 * c[2] * e3ga::e3;
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
e3ga & sphere3(const e3ga &p, e3ga &v) {
	// fastest method:
	const float *c = p[GRADE1];
	v.set(GRADE1,
		4 * (c[0] * c[0] + c[1] * c[1] + c[2] * c[2] - 1) * c[0], // e1 coordinate
		4 * (c[0] * c[0] + c[1] * c[1] + c[2] * c[2] - 1) * c[1], // e2 coordinate
		4 * (c[0] * c[0] + c[1] * c[1] + c[2] * c[2] - 1) * c[2]); // e3 coordinate
	return v;
}

/*
function [vx,vy,vz]=eight2(x,y,z)
vx = (2*((x-1)^2+y^2-1)*x*(((x+1)^2+y^2-1)^2+z^2) + 2*((x+1)^2+y^2-1)*x*(((x-1)^2+y^2-1)^2+z^2))*e1;
vy = (2*((x-1)^2+y^2-1)*y*(((x+1)^2+y^2-1)^2+z^2) + 2*((x+1)^2+y^2-1)*y*(((x-1)^2+y^2-1)^2+z^2))*e2;
vz = (2*z*(((x+1)^2+y^2-1)^2+z^2)+2*z*(((x-1)^2+y^2-1)^2+z^2))*e3;
*/
e3ga & eight2(const e3ga &p, e3ga &v) {
	// fastest method:
	const float *c = p[GRADE1];
	float tmp1, tmp2;

	tmp1 = (c[0]+1) * (c[0]+1)+c[1] * c[1]-1;
	tmp2 = (c[0]-1) * (c[0]-1)+c[1] * c[1]-1;
	tmp1 *= 2.0f;
	tmp2 *= 2.0f;


	v.set(GRADE1,
		(2*((c[0]-1) * (c[0]-1)+c[1] * c[1]-1)*c[0]*(tmp1 +c[2] * c[2]) + 
		2*((c[0]+1) * (c[0]+1)+c[1] * c[1]-1)*c[0]*(tmp2 +c[2] * c[2])),
		(2*((c[0]-1) * (c[0]-1)+c[1] * c[1]-1)*c[1]*(tmp1 +c[2] * c[2]) +
		2*((c[0]+1) * (c[0]+1)+c[1] * c[1]-1)*c[1]*(tmp2 +c[2] * c[2])),
		(2*c[2]*( tmp1+c[2] * c[2])+2*c[2]*( tmp2+c[2] * c[2])));
	return v;
}


