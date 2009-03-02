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

#include <vector>

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_draw.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace e3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 3, Example 3: Reciprocal Frame";

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

// the three vectors:
e3ga::vector g_vectors[g_nbVectors] = {
	_vector(e1 - e2 - 0.3f * e3),
	_vector(e1 + 0.3f * e2 - 0.1f * e3),
	_vector(e1 + e3)
};

// the three reciprocal vectors:
e3ga::vector g_recipVectors[g_nbVectors];

// *!*HTML_TAG*!* display
void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	// Update the reciprocal vectors
	// The reciprocalFrame() function is in libgasandbox/e3ga_util.cpp
	reciprocalFrame(g_vectors, g_recipVectors, g_nbVectors);

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
	glTranslatef(0.0f, 0.0f, -10.0f);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	const float horDistance = 2.5f;

	glTranslatef(-horDistance, 0.0f, 0.0f);

	glPushMatrix();
	rotorGLMult(g_modelRotor);

	// draw vector 1
	if (GLpick::g_pickActive) glLoadName(1);
	glColor3fm(1.0f, 0.0f, 0.0f);
	draw(g_vectors[0]);

	// draw vector 2
	if (GLpick::g_pickActive) glLoadName(2);
	glColor3fm(0.0f, 1.0f, 0.0f);
	draw(g_vectors[1]);

	// draw vector 3
	if (GLpick::g_pickActive) glLoadName(3);
	glColor3fm(0.0f, 0.0f, 1.0f);
	draw(g_vectors[2]);

	glPopMatrix();


	if (!GLpick::g_pickActive) {
		glTranslatef(2.0f * horDistance, 0.0f, 0.0f);

		glPushMatrix();
		rotorGLMult(g_modelRotor);

		// draw reciprocal vector 1
		glColor3fm(1.0f, 0.0f, 0.0f);
		draw(g_recipVectors[0]);

		// draw reciprocal vector 2
		glColor3fm(0.0f, 1.0f, 0.0f);
		draw(g_recipVectors[1]);

		// draw reciprocal vector 3
		glColor3fm(0.0f, 0.0f, 1.0f);
		draw(g_recipVectors[2]);

		glPopMatrix();
	}


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
		renderBitmapString(g_viewportWidth / 4 - 50, g_viewportHeight - 20, font, "Input Frame:");
		renderBitmapString(g_viewportWidth * 3 / 4 - 50, g_viewportHeight - 20, font, "Reciprocal Frame");

		renderBitmapString(20, 20, font, "-use mouse to drag (Input Frame) vectors and to orbit scene");
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
	else if ((g_dragObject >= 1) && (g_dragObject <= 3)) {
		// add motion to vector:
		e3ga::vector T = vectorAtDepth(g_dragDistance, motion);
		T = _vector(inverse(g_modelRotor) * T * g_modelRotor);
		g_vectors[g_dragObject-1] += T;
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

		// redraw viewport
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

	glutMainLoop();

	return 0;
}

/*	std::vector<e3ga::vector> IF(3);
	IF[0] = _vector(e1 + e2);
	IF[1] = _vector(e1 - e3);
	IF[2] = _vector(0.1 * e1 - 0.1 * e3 + 0.1 * e2);
	std::vector<e3ga::vector> RF;*/
