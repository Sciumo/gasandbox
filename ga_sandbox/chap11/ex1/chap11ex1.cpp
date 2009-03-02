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

using namespace h3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 11, Example 1: Working with Points";

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

const int NB_POINTS = 3;
const int NB_NORMALIZED_POINTS = 3;

// the regular points:
point g_points[NB_POINTS] = {
// note that we deliberately give weights to the points (1.0, 2.0, 3.0)
	_point(1.0f * (e1 + e2 + e0)),
	_point(2.0f * (2.0f * e1 + 0.5f * e2 + e0)),
	_point(3.0f * (e1 + 0.5f * e3 + e0)),
};
// the normalized points:
normalizedPoint g_normalizedPoints[NB_NORMALIZED_POINTS] = {
// note the hack here: because normalizedPoints have a
// constant 'e0' coordinate, no need to do '+ e0' for each point.
// You can initialize a normalizedPoint straight for a '3D vector'
	_normalizedPoint(-e1 + e2),
	_normalizedPoint(-1.5f * e1 + 0.5f * e2),
	_normalizedPoint(-e1 + 0.5f * e3),
};



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
		draw(g_points[i]);
	}

	// draw normalized points
	glColor3fm(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < NB_NORMALIZED_POINTS; i++) {
		if (GLpick::g_pickActive) glLoadName(NB_POINTS + i);
		draw(g_normalizedPoints[i]);
	}

	if (!GLpick::g_pickActive) {

// *!*HTML_TAG*!* glVertex

		// draw loops through the points:
		glDisable(GL_LIGHTING);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < NB_POINTS; i++) {
			const point &P = g_points[i];
			glVertex4fv(P.getC(point_e1_e2_e3_e0));
			// or:
			// glVertex4f(P.e1(), P.e2(), P.e3(), P.e0());
		}
		glEnd();

		// draw loops through the normalized points:
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < NB_NORMALIZED_POINTS; i++) {
			const normalizedPoint &P = g_normalizedPoints[i];
			glVertex3fv(P.getC(normalizedPoint_e1_e2_e3_e0f1_0)); //note e0 'fixed' at 1.0
			// or:
			// glVertex3f(P.e1(), P.e2(), P.e3());
		}
		glEnd();
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
		renderBitmapString(20, 40, font, "This simple example demonstrates using (normalized) points with OpenGL.");
		renderBitmapString(20, 20, font, "Use the mouse buttons to drag the red/green points.");
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
//		printf("T = %s\n", T.c_str());

		if (g_dragPoint < NB_POINTS) {
			int idx = g_dragPoint;
			g_points[idx] = _point(g_points[idx] + (T ^ (e0 << g_points[idx])));
		}
		else {
			int idx = g_dragPoint - NB_POINTS;
			g_normalizedPoints[idx] =
				_normalizedPoint(g_normalizedPoints[idx] + (T ^ (e0 << g_normalizedPoints[idx])));
		}
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
