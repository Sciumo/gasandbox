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
#include <set>
#include <string>
#include <utility>

#include <libgasandbox/common.h>
#include <libgasandbox/c2ga.h>
#include <libgasandbox/c2ga_draw.h>
#include <libgasandbox/c2ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace c2ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 15, Example 2: Affine Combinations of Points";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

// what point to drag (or -1 for none)
int g_dragPoint = -1;

// mouse position on last call to MouseButton() / MouseMotion()
c2ga::vectorE2GA g_prevMousePos;

const int NB_POINTS = 2;
normalizedPoint g_points[NB_POINTS] = {
	c2gaPoint(350, 300),
	c2gaPoint(450, 300)
};

void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	pickLoadMatrix();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLineWidth(1.0f);

	g_drawState.m_pointSize	= 4.0f;
	// draw the points:
	for (unsigned int i = 0; i < NB_POINTS; i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		if (i == 0) glColor3f(1.0f, 0.0f, 0.0f);
		else glColor3f(0.0f, 0.0f, 1.0f);
		draw(g_points[i]);
	}

// *!*HTML_TAG*!* draw
	if (!GLpick::g_pickActive) {
		// draw line between the two points:
		g_drawState.pushDrawModeOff(OD_ORIENTATION);
		g_drawState.m_lineLength = 1000.0f;
		glColor3f(0.0f, 1.0f, 0.0f);
		draw( g_points[0] - g_points[1]);
		g_drawState.popDrawMode();

		glLineStipple(1, 0x0F0F);
		// draw the circles:
		const mv::Float STEP = 0.1f;
		for (mv::Float lambda = -1.0f; lambda <= 2.0f; lambda += STEP) {
			// set color, stipples:
			if ((lambda < 1.0f) && (lambda > 0.0f)) {
				// draw imaginary circles stippled
				glEnable(GL_LINE_STIPPLE);
				glColor3f(1.0f, 0.0f, 1.0f);
			}
			else {
				if (lambda > 1.0f) glColor3f(1.0f, 0.0f, 0.0f);
				else glColor3f(0.0f, 0.0f, 1.0f);

				glDisable(GL_LINE_STIPPLE);
			}

			// draw the circle:
			draw(lambda * g_points[0] + (1.0f - lambda) * g_points[1]);
		}
		glDisable(GL_LINE_STIPPLE);
	}


	glPopMatrix();

	if (!GLpick::g_pickActive) {
		glColor3f(0.0, 0.0, 0.0);
		void *font = GLUT_BITMAP_HELVETICA_12;
		renderBitmapString(20, 60, font, "Use the mouse buttons to drag the blue and red points.");
		renderBitmapString(20, 40, font, "The circles are the affine combinations (sums) of the two points.");
		renderBitmapString(20, 20, font, "The green line is the difference of the two points (pt1 - pt2).");
	}

	if (!GLpick::g_pickActive) {
		glutSwapBuffers();
	}
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

}

c2ga::vectorE2GA mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return _vectorE2GA((float)x * e1 - (float)y * e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_dragPoint = pick(x, g_viewportHeight - y, display, NULL); // NULL = pointer to distance

	g_prevMousePos = mousePosToVector(x, y);

	// redraw viewport
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	c2ga::vectorE2GA mousePos = mousePosToVector(x, y);
	c2ga::vectorE2GA motion = _vectorE2GA(mousePos - g_prevMousePos);

	if (g_dragPoint >= 0) {
		// translate point
		normalizedTranslator T = _normalizedTranslator(1.0f - (0.5f * motion ^ ni));
		g_points[g_dragPoint] = _normalizedPoint(T * g_points[g_dragPoint] * inverse(T));
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	c2ga::g2Profiling::init();

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
