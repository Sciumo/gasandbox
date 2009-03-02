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

#include <string>

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_draw.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>

using namespace e3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 7, Example 1: Reflecting in Vectors";

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
rotor g_modelRotor(_rotor(1.0f));

// when dragging vectors: which one, and at what depth:
float g_dragDistance = -1.0f;
int g_dragObject = -1;


// the vector in which we reflect (red)
e3ga::vector g_reflectionVector = _vector(e2);

// the vectors which we reflect (green)
e3ga::vector g_inputVector1 = _vector(e1 + e2);
e3ga::vector g_inputVector2 = _vector(e3);

// the reflected vectors (blue)
e3ga::vector g_reflectedVector1;
e3ga::vector g_reflectedVector2;

// what vectors to draw (bitmap):
int g_drawVectors = 1;


// *!*HTML_TAG*!* reflect

e3ga::vector reflectVector(const e3ga::vector &a, const e3ga::vector &x) {
	// we use a _line_ reflection for this example
	return _vector(a * x * inverse(a));
}

void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	// update the reflected vectors
	g_reflectedVector1 = reflectVector(g_reflectionVector, g_inputVector1);
	g_reflectedVector2 = reflectVector(g_reflectionVector, g_inputVector2);

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
	glTranslatef(0.0f, 0.0f, -8.0f);


	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glLineWidth(2.0f);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);

	// draw reflection vector
	if (GLpick::g_pickActive) glLoadName(1);
	glColor3fm(1.0f, 0.0f, 0.0f);
	draw(g_reflectionVector);

	if (g_drawVectors & 1) {
		// draw input vector 1
		if (GLpick::g_pickActive) glLoadName(2);
		glColor3fm(0.0f, 1.0f, 0.0f);
		draw(g_inputVector1);
	}

	if (g_drawVectors & 2) {
		// draw input vector 2
		if (GLpick::g_pickActive) glLoadName(3);
		glColor3fm(0.0f, 1.0f, 0.0f);
		draw(g_inputVector2);
	}

	if (!GLpick::g_pickActive) {
		if ((g_drawVectors & 3) == 3) {
			g_drawState.pushDrawModeOff(OD_ORIENTATION);

			glColor3fm(0.0f, 1.0f, 0.0f);
			draw(g_inputVector1 ^ g_inputVector2);
			glColor3fm(0.0f, 0.0f, 1.0f);
			draw(g_reflectedVector1 ^ g_reflectedVector2);
			g_drawState.popDrawMode();
		}


		if (g_drawVectors & 1) {
			// draw reflected vector 1
			glColor3fm(0.0f, 0.0f, 1.0f);
			draw(g_reflectedVector1);
		}

		if (g_drawVectors & 2) {
			// draw reflected vector 2
			glColor3fm(0.0f, 0.0f, 1.0f);
			draw(g_reflectedVector2);
		}

		// draw stippled line between input and reflection:
		glDisable(GL_LIGHTING);
		glEnable(GL_LINE_STIPPLE);
		int ST = 0xFF00FF >> ((int)(u_timeGet() * 25) % 16);
		glLineStipple(1, ( GLushort)(ST & 0xFFFF));
		glColor3fm(0.5f, 0.5f, 0.5f);

		if (g_drawVectors & 1) {
			glBegin(GL_LINES);
			glVertex3fv(g_reflectedVector1.getC(vector_e1_e2_e3));
			glVertex3fv(g_inputVector1.getC(vector_e1_e2_e3));
			glEnd();
		}

		if (g_drawVectors & 2) {
			glBegin(GL_LINES);
			glVertex3fv(g_reflectedVector2.getC(vector_e1_e2_e3));
			glVertex3fv(g_inputVector2.getC(vector_e1_e2_e3));
			glEnd();
		}

		glDisable(GL_LINE_STIPPLE);
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
		glColor3f(1.0f, 1.0f, 1.0f);
		void *font = GLUT_BITMAP_HELVETICA_12;
		renderBitmapString(20, 60, font, "The green vector(s) are reflected in plane orthogonal to the red vector.");
		renderBitmapString(20, 40, font, "Use the left mouse button to drag the (green or red) vectors and orbit the scene.");
		renderBitmapString(20, 20, font, "Use the other mouse buttons to access the popup menu.");
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
		if (g_dragObject == 1) {
			g_reflectionVector += T;
		}
		else if (g_dragObject == 2) {
			g_inputVector1	+= T;
		}
		else if (g_dragObject == 3) {
			g_inputVector2	+= T;
		}
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void menuCallback(int value) {
	g_drawVectors = value;

	// redraw viewport
	glutPostRedisplay();
}

void Idle() {
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
	glutIdleFunc(Idle);

	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry("vector mode", 1);
	glutAddMenuEntry("bivector mode", 3);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

	return 0;
}
