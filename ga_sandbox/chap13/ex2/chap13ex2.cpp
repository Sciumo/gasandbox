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

using namespace c3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 13, Example 2: The Distance Between Points";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
//int g_GLUTmenu;

// mouse position on last call to MouseButton() / MouseMotion()
c3ga::vectorE3GA g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// what point to drag (or -1 for none)
int g_dragPoint = -1; 
float g_dragDistance = 12.0f;

// rotation of the model
c3ga::rotor g_modelRotor(_rotor(1.0f));

// the points:
std::vector<normalizedPoint> g_points;

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
	glTranslatef(0.0f, 0.0f, -10.0f);

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

	// we collect labels string and positions here
	std::vector<std::string> labelString;
	std::vector<vectorE2GA> labelPos;

	// draw the points
	glColor3fm(1.0f, 0.0f, 0.0f);
	g_drawState.m_pointSize = 0.1f;
	for (unsigned int i = 0; i < g_points.size(); i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		draw(g_points[i]);
	}

	if (!GLpick::g_pickActive) {
		// draw lines between points, remember positions for labels
		glDisable(GL_LIGHTING);
		glColor3f(0.0, 1.0, 0.0);
		for (unsigned int i = 0; i < g_points.size(); i++) {	
			const normalizedPoint &pt1 = g_points[i];
			for (unsigned int j = i+1; j < g_points.size(); j++) {	
				const normalizedPoint &pt2 = g_points[j];

				// draw the line:
				glBegin(GL_LINES);
				glVertex3f(pt1.e1(), pt1.e2(), pt1.e3());
				glVertex3f(pt2.e1(), pt2.e2(), pt2.e3());
				glEnd();

				// compute distance
				float distance = 0.0; // EXERCISE: fill in the code to compute the distance between pt1 and pt2

				// create the label:
				char buf[256];
				sprintf(buf, "%2.2f", distance);
				labelString.push_back(buf);

				// get label position:
				mv::Float ptViewport[2];
				viewportCoordinates( _vectorE3GA(0.5f * (pt1 + pt2)).getC(vectorE3GA_e1_e2_e3), ptViewport);
				labelPos.push_back(vectorE2GA(vectorE2GA_e1_e2, ptViewport));
			}
		}
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
		void *font = GLUT_BITMAP_HELVETICA_12;

		// draw the labels:
		glColor3f(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < labelPos.size(); i++) {
			renderBitmapString(labelPos[i].e1(), labelPos[i].e2(), font, labelString[i].c_str());
		}


		// draw UI description
		glColor3f(0.0f, 0.0f, 0.0f);
		renderBitmapString(20, 20, font, "Use the left mouse button to manipulate the scene, and to orbit it.");
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

c3ga::vectorE3GA vectorAtDepth(double depth, const c3ga::vectorE3GA &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return c3ga::vectorE3GA();
	}

	return _vectorE3GA((depth * (double)v2d.e1() * GLpick::g_frustumWidth) / (g_viewportWidth * GLpick::g_frustumNear) * e1 +
		(depth * (double)v2d.e2() * GLpick::g_frustumHeight) / (g_viewportHeight * GLpick::g_frustumNear) * e2);
}

c3ga::vectorE3GA mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return _vectorE3GA((float)x * e1 - (float)y * e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	g_dragPoint = pick(x, g_viewportHeight - y, display, &g_dragDistance);
	g_rotateModel = (g_dragPoint < 0);

	if (g_rotateModel) {
		c3ga::vectorE3GA mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}

	// redraw viewport
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	c3ga::vectorE3GA mousePos = mousePosToVector(x, y);
	c3ga::vectorE3GA motion = _vectorE3GA(mousePos - g_prevMousePos);
	if (g_rotateModel) {
		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(c3ga::exp(0.005f * (motion ^ c3ga::e3)) * g_modelRotor);
		else g_modelRotor = _rotor(c3ga::exp(0.00001f * (motion ^ mousePos)) * g_modelRotor);
	}
	else if (g_dragPoint >= 0) {
		// translate point
		c3ga::vectorE3GA t = _vectorE3GA(inverse(g_modelRotor) * vectorAtDepth(g_dragDistance, motion) * g_modelRotor);
		normalizedTranslator T = _normalizedTranslator(1.0f - (0.5f * t ^ ni));
		g_points[g_dragPoint] = c3gaPoint(_vectorE3GA(T * g_points[g_dragPoint] * inverse(T))); // note hack due to 32 bit FP inprecision
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

	// create the initial points
	g_points.push_back(c3gaPoint(3.759879f, -1.404804f, 0.000000f));
	g_points.push_back(c3gaPoint(1.242272f, 2.631137f, 0.000000f));
	g_points.push_back(c3gaPoint(1.476579f, -2.886040f, 1.000000f));
	g_points.push_back(c3gaPoint(-3.424791f, 1.417571f, 0.000000f));
	g_points.push_back(c3gaPoint(-1.646863f, -1.932975f, 0.000000f));


	glutMainLoop();

	return 0;
}
