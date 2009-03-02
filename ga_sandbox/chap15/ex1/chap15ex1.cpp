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
#include <time.h>

#include <vector>

#include <libgasandbox/c3ga.h>
#include <libgasandbox/c3ga_draw.h>
#include <libgasandbox/c3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>
#include <libgasandbox/mv_analyze.h>

using namespace c3ga;
using namespace mv_draw;

// Everybody takes the plunge the first time.
const char *WINDOW_TITLE = "Geometric Algebra, Chapter 15, Example 1: The Plunge";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

// mouse position on last call to MouseButton() / MouseMotion()
vectorE2GA g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// rotation of the model
rotor g_modelRotor(_rotor(1.0f));

// what point to drag (or -1 for none)
int g_dragPrimitive = -1;
float g_dragDistance = 0.0f;

// the primitives:
const int NB_PRIMITIVES = 3;
mv g_primitives[NB_PRIMITIVES] = {
		c3gaPoint(-1.0f, 1.5f, 0.0f), // point
		3.25f * e1 + 2.68f * e2 -0.34f * e3 + 1.00f * no + 8.43f * ni, // dual sphere
		-e2 + 2.0f * ni, // dual plane
};

vectorE3GA vectorAtDepth(double depth, const vectorE2GA &v2d);

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
	glTranslatef(0.0f, 0.0f, -16.0f);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

// *!*HTML_TAG*!* plunge

	// draw the plunge
	glColor3fm(0.0f, 1.0f, 0.0f);
	draw(g_primitives[0] ^ g_primitives[1] ^ g_primitives[2]);

	// draw the primitives
	glColor3fm(1.0f, 0.0f, 0.0f);
	g_drawState.m_pointSize = 0.1f;
	g_drawState.pushDrawModeOff(OD_ORIENTATION);
	g_drawState.pushDrawModeOff(OD_MAGNITUDE);
	for (unsigned int i = 0; i < NB_PRIMITIVES; i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		if (i == 2) glLoadName((GLuint)-1); // do not allow for dragging the plane!

		if (i > 0) { // draw the sphere and plane transparent
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4fm(1.0f, 0.0f, 0.0f, 0.5f);
		}

		draw(g_primitives[i], (i > 0) ? 1e-5 : 1e-3);
	}
	glDisable(GL_BLEND); // blending off
	glDepthMask(GL_TRUE); // enable depth buffer writes
	g_drawState.popDrawMode();
	g_drawState.popDrawMode();


	if (GLpick::g_pickActive) glLoadName((GLuint)-1);

	glPopMatrix();

	{
		glViewport(0, 0, g_viewportWidth, g_viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		pickLoadMatrix();
		glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.0f, 0.0f);
		void *font = GLUT_BITMAP_HELVETICA_12;

		if (!GLpick::g_pickActive) {

			renderBitmapString(20, 40, font, "Use the mouse buttons to drag the point or sphere, or to orbit the scene.");
			renderBitmapString(20, 20, font, "Notice how the circle always intersects the other primitives orthogonally");
		}
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

vectorE3GA vectorAtDepth(double depth, const vectorE2GA &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return c3ga::vectorE3GA();
	}

	return _vectorE3GA((depth * (double)v2d.e1() * GLpick::g_frustumWidth) / (g_viewportWidth * GLpick::g_frustumNear) * e1 +
		(depth * (double)v2d.e2() * GLpick::g_frustumHeight) / (g_viewportHeight * GLpick::g_frustumNear) * e2);
}

vectorE2GA mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return _vectorE2GA((float)x * e1 - (float)y * e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	g_dragPrimitive = pick(x, g_viewportHeight - y, display, &g_dragDistance);
	g_rotateModel = (g_dragPrimitive < 0);

	if (g_rotateModel) {
		vectorE2GA mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2f)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}


	// redraw viewport
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	vectorE2GA mousePos = mousePosToVector(x, y);
	vectorE2GA motion = _vectorE2GA(mousePos - g_prevMousePos);
	if (g_rotateModel) {
		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(c3ga::exp(0.005f * (motion ^ e3)) * g_modelRotor);
		else g_modelRotor = _rotor(c3ga::exp(0.00001f * (motion ^ mousePos)) * g_modelRotor);
	}
	else if (g_dragPrimitive >= 0) {
		vectorE3GA t = vectorAtDepth(g_dragDistance, motion);
		t = _vectorE3GA(inverse(g_modelRotor) * t * g_modelRotor);
		normalizedTranslator T = exp(_freeVector(-0.5f * (t ^ ni)));

		g_primitives[g_dragPrimitive] =
				T * g_primitives[g_dragPrimitive] * inverse(T);
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	c3ga::g2Profiling::init();

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
