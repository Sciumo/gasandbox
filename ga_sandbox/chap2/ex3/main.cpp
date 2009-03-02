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

/*
Gaigen 2 HP Index

Detects singularities in vector fields.
(C) 2001-2006 Daniel Fontijne - University of Amsterdam & Stephen Mann - University of Waterloo
Algorithm and original matlab code by Stephen Mann & Alyn Rockwood

*/

#include <stdio.h>
#include <stdlib.h>


#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined (OSX)
	#include <OpenGL/gl.h>
	#include <OpenGL/glext.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string>

#include <libgasandbox/common.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/e3ga_util.h>

#include "fields.h"
#include "render.h"

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 2, Example 3: Vector Field Singularity Detection";

// GLUT state information 
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;
// mouse position on last call to MouseButton() / MouseMotion()
e3ga::vector g_prevMousePos;
e3ga::rotor g_modelRotor(_rotor(1.0f));;
float g_modelDistance = 11.0f;
// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;
bool g_translateModel = false;

// (FORMERLY-ui) controlled globals:
float g_cx=0.05f, g_cy=0.05f, g_cz=0.05f;
int g_showField = 0, g_showOctree = 0,  g_showResult = 1, g_unitField=0,
  g_bottom=0;
int g_gs = 8, g_maxDepth = 7;
int g_adap=0;
int g_vgs = 10;
float g_vectorSize = 1.0f;
float g_cubeSize = 5.0f;
float g_lratio = 10.0f;
float g_sratio = 10.0f;
float g_lsing = 0.10f;
float g_psing = 0.10f;
float g_refine = 0.10f;
float g_lrefine = 0.10f;
double g_lastTiming = 0.0f;
int g_boxes=0;
int g_refines=0;
int g_lineSing = 1;
int g_surfSing = 1;
int g_lighting = 1;
int g_falseLineSing = 1; 
int g_falseSurfSing=1;
int g_pushGo = 0;

int g_Dcube = 0;
int g_showSphere=1;
int g_showPSphere=1;
int g_showNSphere=1;
int g_showCirc=0;
int g_USphere=1;
int g_ISphere=0;
float g_hpvalue=0.0;

/* Constants used in vortex field */
float g_omega=1.0;
float g_gamma=1.0;
float g_Rcore=1.0;

float g_dx=0.;
float g_dy=0.;
float g_dz=1.;

// what function are we using currently 
e3ga::vector & (*g_evalFunc)(const e3ga::vector &p, e3ga::vector &v) = (e3ga::vector & (*)(const e3ga::vector &p, e3ga::vector &v))eight2;

// the fields (names + evaluation functions)
// The dull ones are commented out
struct fieldFunctionStruct {
		const char *fieldName;
		e3ga::vector & (*func)(const e3ga::vector &p, e3ga::vector &v);
} g_fieldFunctions[] = {
//{"constant", const3},
//{"vortex", vortex},
{"point", point3},
{"line", line3},
{"line (helix field)", helix3},
{"circle", circ3},
{"eight", eight2},
{"sphere", sphere3},
//{"testFunc3", testFunc3},
{"x^3*y^3*z^2", testFunc4},
//{"x^3+y^3+z^2", testFunc5},
//{"x^3+y^3+x^2", testFunc6},
{"x^3*y^3", testFunc7},
//{"Z^2/(Z+2)/(Z-4/5)", testFunc8},
//{"1/Z", testFunc9},
//{"x^3+y^3+z^3", testFunc10},
//{"x^4+y^4+z^4", testFunc11},
{"(x^2+y^2-z)^2 (cup)", testFunc12},
{"sphere union cyl", testFunc13},
{"sphere int cyl", testFunc14},
{"helix", testFunc15},
//{"double line", testFunc16},
//{"double point", testFunc16a},
//{"x^3/3 - xy^2 + z^2", testFunc17},
//{"x^3/3 - xy^2", testFunc18},
{NULL, NULL},
};


void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(0, 0, -g_modelDistance);
	rotorGLMult(g_modelRotor);

	// all drawing code is inside render.cpp
	drawAll();

	glPopMatrix();

	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glColor3f(1.0, 0.0, 0.0);
		void *font = GLUT_BITMAP_HELVETICA_12;
		renderBitmapString(20, 80, font, "Left mouse button: rotate");
		renderBitmapString(20, 60, font, "Middle mouse button: select vector field");
		renderBitmapString(20, 40, font, "Right mouse button: translate");
		renderBitmapString(20, 20, font, "Detected singulaties are drawn in RED (points), GREEN (lines), BLUE (surfaces)");
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	glutSwapBuffers();	
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// setup projection & transform for the model:
	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	const float screenWidth = 1600.0f;
	glFrustum(
		-(float)g_viewportWidth / screenWidth, (float)g_viewportWidth / screenWidth, 
		-(float)g_viewportHeight / screenWidth, (float)g_viewportHeight / screenWidth, 
		1.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// redraw viewport
	glutPostRedisplay();	
}

e3ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return e3ga::_vector((float)x * e3ga::e1 - (float)y * e3ga::e2);
}


void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;
	g_translateModel = false;
	if (button == GLUT_LEFT_BUTTON) {
		e3ga::vector mousePos = mousePosToVector(x, y);
		g_prevMousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		g_translateModel = true;
		g_prevMousePos = mousePosToVector(x, y);
	}
}

void MouseMotion(int x, int y) {
	// get mouse position, motion 
	e3ga::vector mousePos = mousePosToVector(x, y);
	e3ga::vector motion = _vector(mousePos - g_prevMousePos);

	if (g_rotateModel) {
		
		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(e3ga::exp(0.005f * (motion ^ e3ga::e3)) * g_modelRotor);
		else g_modelRotor = _rotor(e3ga::exp(0.00001f * (motion ^ mousePos)) * g_modelRotor);
		
		
	}
	else if (g_translateModel) {
		g_modelDistance -= motion.e2() / 10.0f;
		if (g_modelDistance < 1.0f) g_modelDistance = 1.0f;
		if (g_modelDistance > 100.0f) g_modelDistance = 100.0f;
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;
	
	// redraw viewport
	glutPostRedisplay();	
}


void menuCallback(int value) {

	// first check for fields:
	int i = 0;
	while (g_fieldFunctions[i].fieldName) {
		if (i == value) {
			printf("New field: %s\n", g_fieldFunctions[i].fieldName);
			g_evalFunc = g_fieldFunctions[i].func;
		}
		i++;
	}

	value -= i;

	// now check for extra options:
	if (value == 0) {
		// show / hide field:
		g_showField = !g_showField;
	}
	
	g_makeNewList = true;
	glutPostRedisplay();
}


int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();

	// GLUT Window Initialization:
	glutInit (&argc, argv);
	glutInitWindowSize(g_viewportWidth, g_viewportHeight);
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(WINDOW_TITLE);
	
	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	
	
	g_GLUTmenu = glutCreateMenu(menuCallback);
	int i = 0;
	for (; g_fieldFunctions[i].fieldName; i++)
		glutAddMenuEntry(g_fieldFunctions[i].fieldName, i);
	glutAddMenuEntry("show/hide vector field", i);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	

	glutMainLoop();
	
	return 0;	
}
