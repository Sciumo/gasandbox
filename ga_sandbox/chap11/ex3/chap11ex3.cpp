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

#include <libgasandbox/h3ga.h>
#include <libgasandbox/h3ga_draw.h>
#include <libgasandbox/h3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>
#include <libgasandbox/mvtypebase.h>

using namespace h3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 11, Example 3: Don't Add Lines";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;

// mouse position on last call to MouseButton() / MouseMotion()
h3ga::vector g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// what point to drag (or -1 for none)
int g_dragPoint = -1;
float g_dragDistance = -1.0f;

// rotation of the model
h3ga::rotor g_modelRotor(_rotor(1.0f));

const int NB_POINTS = 4;

// the normalized points:
normalizedPoint g_points[NB_POINTS] = {
	_normalizedPoint(-e1 + e2 + e0),
	_normalizedPoint(e1 + e2 + e0),
	_normalizedPoint(-e1 - e2 + e0),
	_normalizedPoint(e1 - e2 + e0),
};



void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	// copy points to local array:
	normalizedPoint pt[NB_POINTS];
	for (int i = 0; i < NB_POINTS; i++) {
		pt[i] = g_points[i];
	}

	{
		// `snap' the points (for POSITION)
		const float CLOSE_POINTS = 0.1f;
		for (int i = 0; i < NB_POINTS; i++) {
			for (int j = 0; j < NB_POINTS; j++) {
				if (_Float(norm_e(pt[i] - pt[j])) < CLOSE_POINTS)
					pt[i] = pt[j]; // snap!
			}
		}

		// `snap' the points (for DIRECTION)
		const float CLOSE_DIRECTIONS = 0.1f;
		if (_Float(norm_e(unit_e(pt[1] - pt[0]) ^ unit_e(pt[3] - pt[2]))) < CLOSE_DIRECTIONS) {
			// snap!
			h3ga::vector dir = _vector(unit_e(pt[1] - pt[0]));
			mv::Float l = _Float(dir << (pt[3] - pt[2]));
			pt[3] = _normalizedPoint(pt[2] + l * dir);
		}
	}

// *!*HTML_TAG*!* addLines

	// compute the lines
	line L1 = _line(pt[0] ^ pt[1]);
	line L2 = _line(pt[2] ^ pt[3]);
	line L1plusL2 = _line(L1 + L2);

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

	// draw points
	glColor3fm(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < NB_POINTS; i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		draw(pt[i]);
	}

	if (!GLpick::g_pickActive) {
		g_drawState.pushDrawModeOff(OD_ORIENTATION);

		// draw the lines
		glColor3fm(0.0f, 1.0f, 0.0f);
		draw(L1);
		draw(L2);
		glColor3fm(1.0f, 1.0f, 1.0f);
		draw(L1plusL2);

		g_drawState.popDrawMode();
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

		int y = g_viewportHeight - 20;
		char buf[1024];

		// is L1plusL2 a blade?
		mv::Float epsilon = 1e-7f;
		h3ga::mvType T(L1plusL2, epsilon);
		sprintf(buf, "pt1^pt2 + pt3^pt4 is a blade: %s\n", (T.m_type == mvTypeBase::BLADE) ? "true" : "false");
		renderBitmapString(20, y, font, buf);
		y -= 20;

		/*
		// compute the conditions for being a blade:

		// Check: versor inverse == inverse
		mv VI = reverse(L1plusL2) * inverse(L1plusL2 * reverse(L1plusL2));

		mv check1 = gradeInvolution(L1plusL2) * VI;
		bool check1OK = _Float(norm_e(check1 - _Float(check1))) < 0.01f;

		sprintf(buf, "grade(gi(L1 + L2) * inverse(L1 + L2)) == 0: %s\n", (check1OK) ? "OK" : "FAILED");
		renderBitmapString(20, y, font, buf);
		y -= 20;

		mv check2 = gradeInvolution(L1plusL2) * VI - VI * gradeInvolution(L1plusL2);
		bool check2OK = _Float(norm_e(check2)) < 0.01f;

		sprintf(buf, "gi(L1 + L2) * inverse(L1 + L2) == inverse(L1 + L2) * gi(L1 + L2): %s\n", (check2OK) ? "OK" : "FAILED");
		renderBitmapString(20, y, font, buf);
		y -= 20;

		// Check: apply L1 + L2 to the basis vectors, check if result is vector
		mv checkE1 = gradeInvolution(L1plusL2) * e1 * reverse(L1plusL2);
		mv checkE2 = gradeInvolution(L1plusL2) * e2 * reverse(L1plusL2);
		mv checkE3 = gradeInvolution(L1plusL2) * e3 * reverse(L1plusL2);
		mv checkE0 = gradeInvolution(L1plusL2) * e0 * reverse(L1plusL2);

		bool checkE1OK = _Float(norm_e(checkE1 - _point(checkE1))) < 0.01f;
		bool checkE2OK = _Float(norm_e(checkE2 - _point(checkE2))) < 0.01f;
		bool checkE3OK = _Float(norm_e(checkE3 - _point(checkE3))) < 0.01f;
		bool checkE0OK = _Float(norm_e(checkE0 - _point(checkE0))) < 0.01f;

		sprintf(buf, "grade(gi(L1 + L2) * e1 * reverse(L1 + L2)) == 1: %s\n", (checkE1OK) ? "OK" : "FAILED");
		renderBitmapString(20, y, font, buf);
		y -= 20;

		sprintf(buf, "grade(gi(L1 + L2) * e2 * reverse(L1 + L2)) == 1: %s\n", (checkE2OK) ? "OK" : "FAILED");
		renderBitmapString(20, y, font, buf);
		y -= 20;

		sprintf(buf, "grade(gi(L1 + L2) * e3 * reverse(L1 + L2)) == 1: %s\n", (checkE3OK) ? "OK" : "FAILED");
		renderBitmapString(20, y, font, buf);
		y -= 20;

		sprintf(buf, "grade(gi(L1 + L2) * e0 * reverse(L1 + L2)) == 1: %s\n", (checkE0OK) ? "OK" : "FAILED");
		renderBitmapString(20, y, font, buf);
		y -= 20;
*/

		renderBitmapString(20, 80, font, "Use the mouse buttons to drag the red points and orbit the scene.");
		renderBitmapString(20, 60, font, "The white line (when drawn) is the sum of the two green lines.");
		renderBitmapString(20, 40, font, "When the white line is not drawn, the sum of the green lines is not a blade.");
		renderBitmapString(20, 20, font, "NOTE: You need to orbit the scene before this situation can arise!");
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

h3ga::vector vectorAtDepth(double depth, const h3ga::vector &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return h3ga::vector();
	}

	return _vector((depth * (double)v2d.e1() * GLpick::g_frustumWidth) / (g_viewportWidth * GLpick::g_frustumNear) * e1 +
		(depth * (double)v2d.e2() * GLpick::g_frustumHeight) / (g_viewportHeight * GLpick::g_frustumNear) * e2);
}

h3ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return h3ga::_vector((float)x * h3ga::e1 - (float)y * h3ga::e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	g_dragPoint = pick(x, g_viewportHeight - y, display, &g_dragDistance);

	if (g_dragPoint < 0) {
		h3ga::vector mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	h3ga::vector mousePos = mousePosToVector(x, y);
	h3ga::vector motion = _vector(mousePos - g_prevMousePos);
	if (g_rotateModel) {
		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(h3ga::exp(0.005f * (motion ^ h3ga::e3)) * g_modelRotor);
		else g_modelRotor = _rotor(h3ga::exp(0.00001f * (motion ^ mousePos)) * g_modelRotor);
	}
	else if (g_dragPoint >= 0) {
		h3ga::vector T = vectorAtDepth(g_dragDistance, motion);
		T = _vector(inverse(g_modelRotor) * T * g_modelRotor);

		int idx = g_dragPoint;
		g_points[idx] = _point(g_points[idx] + (T ^ (e0 << g_points[idx])));
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	h3ga::g2Profiling::init();

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
