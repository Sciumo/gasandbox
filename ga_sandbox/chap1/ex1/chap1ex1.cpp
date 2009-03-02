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
#include <string>

#include <libgasandbox/common.h>
#include <libgasandbox/c3ga.h>
#include <libgasandbox/c3ga_draw.h>
#include <libgasandbox/c3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/mv_analyze.h>

using namespace c3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 1, Example 1: An Example in Geometric Algebra";

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

// the points:
const int NB_POINTS = 6;
normalizedPoint g_points[NB_POINTS] = {
	_normalizedPoint(c3gaPoint(_vectorE3GA(- 0.356756f*e1 - 0.881980f*e2))),
	_normalizedPoint(c3gaPoint(_vectorE3GA(- 0.725786f*e1 + 0.934177f*e2 - 0.366154f*e3))),
	_normalizedPoint(c3gaPoint(_vectorE3GA(2.612482f*e1 + 1.495455f*e2 - 2.704073f*e3))),
	_normalizedPoint(c3gaPoint(_vectorE3GA(2.218644f*e1 + 0.425753f*e2 - 1.780935f*e3))),
	_normalizedPoint(c3gaPoint(_vectorE3GA(0.865897f*e1 + 0.629159f*e2 - 1.438985f*e3))),
	_normalizedPoint(c3gaPoint(_vectorE3GA(2.846445f*e1 - 1.112365f*e2 - 0.366769f*e3)))
};


const int LINE_POINT_IDX = 0;
const int CIRCLE_POINT_IDX = 2;
const int PLANE_POINT_IDX = 5;


// point dragging info:
int g_dragPoint = -1;
float g_dragDistance = -1.0f;

// *!*HTML_TAG*!* display
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
	glTranslatef(0.0f, 0.0f, -14.0f);


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

	g_drawState.pushDrawModeOff(OD_MAGNITUDE);
	g_drawState.m_pointSize = 0.005f;

	glColor3fm(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < NB_POINTS; i++) {
		glLoadName((GLuint)i);
		draw(g_points[i]);
		//printf("p%d = %s\n", i, _vectorE3GA(g_points[i]).c_str_f());
	}

	if (!GLpick::g_pickActive) {
		// get labeled references to all the points
		const normalizedPoint &l1 = g_points[LINE_POINT_IDX + 0];
		const normalizedPoint &l2 = g_points[LINE_POINT_IDX + 1];
		const normalizedPoint &c1 = g_points[CIRCLE_POINT_IDX + 0];
		const normalizedPoint &c2 = g_points[CIRCLE_POINT_IDX + 1];
		const normalizedPoint &c3 = g_points[CIRCLE_POINT_IDX + 2];
		const normalizedPoint &p1 = g_points[PLANE_POINT_IDX + 0];
		const vectorE3GA n = _vectorE3GA(e2);

		// l1, l2, c1, c2, c3, p1 are points, n is a direction vector
		line L = _line(unit_r(l1 ^ l2 ^ ni)); // ni = einf = point at infinity
		circle C = _circle(c1 ^ c2 ^ c3);
		dualPlane p = _dualPlane(p1 << (n^ni));
//		sphere p = _sphere(p1 - 5.0f * ni); // use this line to create a sphere instead of a plane

		// draw line (red)
		glColor3fm(1.0f, 0.0f, 0.0f);
		draw(L);
		// draw cicle (green)
		glColor3fm(0.0f, 1.0f, 0.0f);
		draw(C);

		// draw reflected line (magenta)
		glColor3fm(1.0f, 0.0f, 1.0f);
		draw(-p * L * inverse(p));

		// draw reflected circle (blue)
		glColor3fm(0.0f, 0.0f, 1.0f);
		draw(-p * C * inverse(p));

		// compute rotation versor:
		const float phi = (float)(M_PI / 2.0);
		TRversor R = _TRversor(exp(0.5f * phi * dual(L)));

		// draw rotated cicle (green)
		glColor3fm(0.0f, 1.0f, 0.0f);
		draw(R * C * inverse(R));

		// draw reflected, rotated circle (blue)
		glColor3fm(0.0f, 0.0f, 1.0f);
		draw(-p * R * C * inverse(R) * inverse(p));

		// draw interpolated circles
		dualLine LR = log(R); // get log of R
		for (float alpha = 0; alpha < 1.0; alpha += 0.1f)
		{
			// compute interpolated rotor
			TRversor iR = _TRversor(exp(alpha * LR));

			// draw rotated circle (light green)
			glColor3fm(0.5f, 1.0f, 0.5f);
			draw(iR * C * inverse(iR));

			// draw reflected, rotated circle (light blue)
			glColor3fm(0.5f, 0.5f, 1.0f);
			draw(-p * iR * C * inverse(iR) * inverse(p));
		}

		// draw plane (yellow)
		glColor4fm(1.0f, 1.0f, 0.0f, 0.5f);
		draw(p);
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
		glColor3f(1.0f, 1.0f, 1.0f);
		void *font = GLUT_BITMAP_HELVETICA_12;
		renderBitmapString(20, 20, font, "Yada!");
	}

	if (!GLpick::g_pickActive) {
		glutSwapBuffers();
	}
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


vectorE3GA vectorAtDepth(double depth, const vectorE2GA &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return vectorE3GA();
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

	g_dragPoint = pick(x, g_viewportHeight - y, display, &g_dragDistance);

	if (g_dragPoint < 0) {
		vectorE2GA mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	vectorE2GA mousePos = mousePosToVector(x, y);
	vectorE2GA motion = _vectorE2GA(mousePos - g_prevMousePos);
	if (g_rotateModel) {
		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(exp(_bivectorE3GA(0.005f * (motion ^ e3))) * g_modelRotor);
		else g_modelRotor = _rotor(exp(_bivectorE3GA(0.00001f * (motion ^ mousePos))) * g_modelRotor);
	}
	else if (g_dragPoint >= 0) {
		vectorE3GA t = vectorAtDepth(g_dragDistance, motion);
		normalizedTranslator T = exp(_freeVector(-0.5f * inverse(g_modelRotor) * (t ^ ni) * g_modelRotor));

		g_points[g_dragPoint] =
				_point(T * g_points[g_dragPoint] * inverse(T));

		mv_analyze::mvAnalysis A(g_points[g_dragPoint]);

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
