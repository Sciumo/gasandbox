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

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 15, Example 3: Euclidean Projections";

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
int g_dragPoint = -1;
float g_dragDistance = 0.0f;

// the points:
const int NB_POINTS = 6;
normalizedPoint g_points[NB_POINTS] = {
	c3gaPoint(1, 2, 2),
	c3gaPoint(-1, 2, 2),
	c3gaPoint(1, -2, 2),
	c3gaPoint(-1, -2, -2),
	c3gaPoint(1, 2, -2),
	c3gaPoint(-1, 2, -2)
};

const int MODE_LINE = 1;
const int MODE_CIRCLE = 2;
const int MODE_DRAW_PLUNGE = 4;
const int MODE_CIRCLE_WITH_SPHERE = MODE_CIRCLE | MODE_DRAW_PLUNGE;
const int MODE_LINE_WITH_PLANE = MODE_LINE | MODE_DRAW_PLUNGE;

int g_mode = MODE_CIRCLE;

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

	// draw the points
	glColor3fm(1.0f, 0.0f, 0.0f);
	g_drawState.m_pointSize = 0.1f;
	for (unsigned int i = 0; i < NB_POINTS; i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		draw(g_points[i]);
	}

	if (GLpick::g_pickActive) glLoadName((GLuint)-1);

	g_drawState.pushDrawModeOff(OD_MAGNITUDE);
	if (!GLpick::g_pickActive) {
		// compute circle or line, depending on mode
		circle CL;
		if (g_mode & MODE_CIRCLE)
			CL =_circle(g_points[0] ^ g_points[1] ^ g_points[2]); // compute circle
		else CL =_circle(g_points[0] ^ g_points[1] ^ ni); // compute line

		// draw the circle or the line:
		glColor3fm(0.0f, 1.0f, 0.0f);
		draw(CL);

// *!*HTML_TAG*!* project

		// compute the plane:
		plane PL = _plane(g_points[3] ^ g_points[4] ^ g_points[5] ^ ni);

		// draw the projected circle / line:
		glColor3fm(0.0f, 1.0f, 1.0f);
		draw((CL << inverse(PL)) << PL);

		g_drawState.pushDrawModeOff(OD_ORIENTATION);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// compute/draw the plane:
		glColor4fm(0.0f, 0.0f, 1.0f, 0.5f);
		draw(PL);

		if (g_mode & 4) {
			// Draw the sphere (CL ^ PL*)
			// That is: the sphere that contains both the circle and its projection.
			glColor4fm(0.0f, 1.0f, 1.0f, 0.5f);
			draw(CL ^ dual(PL));
		}

		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		g_drawState.popDrawMode();


	}

	g_drawState.popDrawMode();


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
			renderBitmapString(20, 40, font, "Use the left mouse button to manipulate the points, and to orbit the scene.");
			renderBitmapString(20, 20, font, "Use the other mouse buttons to access the popup menu.");
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
	if (state != GLUT_DOWN) return; // don't respond when button goes up . . .

	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	g_dragPoint = pick(x, g_viewportHeight - y, display, &g_dragDistance);
	g_rotateModel = (g_dragPoint < 0);
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
	else if (g_dragPoint >= 0) {
		vectorE3GA t = vectorAtDepth(g_dragDistance, motion);
		t = _vectorE3GA(inverse(g_modelRotor) * t * g_modelRotor);
		normalizedTranslator T = exp(_freeVector(-0.5f * (t ^ ni)));

		// note the hack required here (repeated application of translators turns points into spheres, at least, with 32-bit floats  :(     )
		g_points[g_dragPoint] =
				c3gaPoint(_vectorE3GA(T * g_points[g_dragPoint] * inverse(T)));
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void menuCallback(int value) {
	g_mode = value;

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

	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry("line mode", MODE_LINE);
	glutAddMenuEntry("circle mode", MODE_CIRCLE);
	glutAddMenuEntry("line mode + plunge", MODE_LINE_WITH_PLANE);
	glutAddMenuEntry("circle mode + plunge", MODE_CIRCLE_WITH_SPHERE);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}
