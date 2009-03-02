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

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_draw.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace e3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 5, Example 1: Meet & Join";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

// mouse position on last call to MouseButton() / MouseMotion()
e3ga::vector g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// rotation of the model
e3ga::rotor g_modelRotor(_rotor(1.0f));

// when dragging vectors: which one, and at what depth:
float g_dragDistance = -1.0f;
int g_dragObject = -1;


const int g_nbVectors = 3;

// the multivectors (initially set to bivectors)
mv g_M1 = e1 ^ e2;
mv g_M2 = unit_e((e1 + e3) ^ e2);

// what to draw:
#define DRAW_JOIN 1
#define DRAW_MEET 2
int g_draw = DRAW_MEET;

// returns 'c', rounded to multiples of 'M'
inline float round(float c, float M) {
	c = c / M;
	return (float)((c < 0) ? (int)(c - 0.5f) : (int)(c + 0.5f)) * M;
}

// rounds coordinates of 'X' to multiples of 'M'
mv round(const mv &X, float M) {
	// ugly hack, making use of internals of Gaigen 2:
	float R[8];
	int s = mv_size[X.gu()];
	for (int i = 0; i < s; i++) {
		R[i] = round(X.m_c[i], M);
	}
	return mv(X.gu(), R);
}


void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	// setup projection & transform for the vectors:
	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	const float screenWidth = 1600.0f;
	glLoadIdentity();
	pickLoadMatrix();
	GLpick::g_frustumWidth = 2.0 *  (double)g_viewportWidth / screenWidth;
	GLpick::g_frustumHeight = 2.0 *  (double)g_viewportHeight / screenWidth;
	glFrustum(
		-GLpick::g_frustumWidth / 2.0, GLpick::g_frustumWidth / 2.0,
		-GLpick::g_frustumHeight / 2.0, GLpick::g_frustumHeight / 2.0,
		GLpick::g_frustumNear, GLpick::g_frustumFar);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -6.0f);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLineWidth(2.0f);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);


// *!*HTML_TAG*!* display

	mv M1 = g_M1;
	mv M2 = g_M2;

	// 'Round' the coordinates, to get a step-wise motion of the bivectors:
	// This simplifies manipulating the bivectors such that they are equal.
	M1 = unit_e(round(M1, 0.2f));
	M2 = unit_e(round(M2, 0.2f));

	g_drawState.pushDrawModeOff(OD_ORIENTATION);

	// red: multivector 1
	glColor3fm(1.0f, 0.0f, 0.0f);
	if (GLpick::g_pickActive) glLoadName(1);
	draw(M1);

	// green: multivector 2
	glColor3fm(0.0f, 1.0f, 0.0f);
	if (GLpick::g_pickActive) glLoadName(2);
	draw(M2);

	// translate a bit (to prevent depth buffer artifacts)
	glTranslatef(0.0f, 0.0f, 0.01f);

	// draw the meet / join, in blue
	try {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	if (!GLpick::g_pickActive) {
		mv X;
		if (g_draw == DRAW_MEET) X = meet(M1, M2);
		else X = join(M1, M2);

		// a little hack to draw everthing in the 'right' size:
		double scale = 1.2f;
		if (X.e1e2e3() != 0.0) scale = 0.5f;

		glColor3fm(0.0f, 0.0f, 1.0f);
		X = scale * unit_e(X);
		draw(X);
	}
	} catch(std::string &str) {
		printf("%s!\n", str.c_str());
	}
	g_drawState.popDrawMode();



	glPopMatrix();

	if (!GLpick::g_pickActive) {
		glViewport(0, 0, g_viewportWidth, g_viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.0f, 0.0f);
		void *font = GLUT_BITMAP_HELVETICA_12;
		renderBitmapString(20, 40, font, "-use left mouse button to rotate the red and green multivectors and to orbit scene");
		renderBitmapString(20, 20, font, "-use other mouse buttons to access popup menu");

		char buf[1024];
		sprintf(buf, "The %s(red multivector, green multivector) is drawn in blue", (g_draw == DRAW_MEET) ? "meet" : "join");
		//renderBitmapString(20, g_viewportHeight - 20, font, buf);

	}

	if (!GLpick::g_pickActive) {
		glutSwapBuffers();
	}
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// redraw viewport
	glutPostRedisplay();
}


e3ga::vector vectorAtDepth(double depth, const e3ga::vector &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return e3ga::vector();
	}

	return _vector((depth * (double)v2d.e1() * GLpick::g_frustumWidth) / (g_viewportWidth * GLpick::g_frustumNear) * e1 +
		(depth * (double)v2d.e2() * GLpick::g_frustumHeight) / (g_viewportHeight * GLpick::g_frustumNear) * e2);
}


e3ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return e3ga::_vector((float)x * e3ga::e1 - (float)y * e3ga::e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	GLpick::g_pickWinSize = 1;
	g_dragObject = pick(x, g_viewportHeight - y, display, &g_dragDistance);
	if (g_dragObject < 0) {
		e3ga::vector mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
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
	else if ((g_dragObject >= 1) && (g_dragObject <= 2)) {
		//rotor R = _rotor(inverse(g_modelRotor) * e3ga::exp(0.005f * (motion ^ e3ga::e3)) * g_modelRotor);
		rotor R = _rotor(inverse(g_modelRotor) * e3ga::exp(0.00005f * (motion ^ mousePos)) * g_modelRotor);
		if (g_dragObject == 1) {
			g_M1 = largestGradePart(R * g_M1 * inverse(R));
		}
		else if (g_dragObject == 2) {
			g_M2 = largestGradePart(R * g_M2 * inverse(R));
		}
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();

}

void menuCallback(int value) {
	if ((value >= 1) && (value <= 3)) {
		g_M1 = unit_e(randomBlade(value));
	}
	else if ((value >= 1 + 4) && (value <= 3 + 4)) {
		g_M2 = unit_e(randomBlade(value-4));
	}
	else if (value == 10) {
		g_draw = DRAW_MEET;
	}
	else if (value == 11) {
		g_draw = DRAW_JOIN;
	}

	glutPostRedisplay();
}

void testMeetJoin() {
	/*
	for (int i = 0; i < 100000; i++) {
		mv X = randomBlade();

		int gradeIdxY, gradeIdxZ;
		mv Y = largestGradePart(X, &gradeIdxY);
		mv Z = highestGradePart(X, 1e-7, &gradeIdxZ);

//		printf("\n%s\n", X.c_str());
		printf("%d %d\n", gradeIdxY, gradeIdxZ);
		printf("%s\n", (X - Y).c_str_e());
		printf("%s\n", (X - Z).c_str_e());

	}*/

/*
	for (int i = 0; i < 100000; i++) {
		mv X = randomBlade();
		mv Y = randomBlade();
		int gradeIdxX, gradeIdxY, gradeIdxZ;
		largestGradePart(X, &gradeIdxX);
		largestGradePart(Y, &gradeIdxY);
		mv Z = deltaProduct(X, Y, 1e-7f, &gradeIdxZ);
		printf("%d %d %d\n", gradeIdxX, gradeIdxY, gradeIdxZ);
	}*/
/*
	for (int i = 0; i < 1000000; i++) {
		mv X = randomBlade();
		mv Y = randomBlade();
		X = unit_e(X);
		Y = unit_e(Y);
		mv M, J;
		try {
			meetJoin(X, Y, M, J);
		} catch(std::string &str) {
			printf("Error with the following:\n");
			printf("%s\n", X.c_str_e());
			printf("%s\n", Y.c_str_e());
			//meetJoin(X, Y, M, J);
		}
		M = unit_e(M);
		J = unit_e(J);
		if (_Float(norm_e2(X << J)) < 0.5f)
			printf("Ah 1!\n");
		if (_Float(norm_e2(Y << J)) < 0.5f)
			printf("Ah 2!\n");

		if (_Float(norm_e2(M << X)) < 0.5f)
			printf("Ah 3!\n");
		if (_Float(norm_e2(M << Y)) < 0.5f)
			printf("Ah 4!\n");
	}
*/

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
	glutAddMenuEntry("Red = Vector", 0 + 1);
	glutAddMenuEntry("Red = Bivector", 0 + 2);
//	glutAddMenuEntry("Red = Trivector", 0 + 3);
	glutAddMenuEntry("Green = Vector", 4 + 1);
	glutAddMenuEntry("Green = Bivector", 4 + 2);
//	glutAddMenuEntry("Green = Trivector", 4 + 3);
	glutAddMenuEntry("Draw Meet", 10);
	glutAddMenuEntry("Draw Join", 11);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

	return 0;
}

