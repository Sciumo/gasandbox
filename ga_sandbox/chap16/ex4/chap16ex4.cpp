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

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 16, Example 4: The Sea Shell";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;

// mouse position on last call to MouseButton() / MouseMotion()
vectorE3GA g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// rotation of the model (initial value gives a good view of the shell)
rotor g_modelRotor(_rotor( 0.573281f - 0.440218f*(e1^e2) + 0.320870f*(e2^e3) + 0.612044f*(e1^e3)));

circle g_circle;
sphere g_sphere;

// for picking
int g_dragWhat = -1;
float g_dragDistance;
const int CIRCLE_NAME = 1;
const int SPHERE_NAME = 2;

void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	double currentTime = u_timeGet();

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
	glTranslatef(0.7f, 0.2f, -6.0f);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glLineWidth(1.0f);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);
	glTranslatef(0.0, 0.0, -4.0f);

	g_drawState.pushDrawModeOff(OD_ORIENTATION);
	g_drawState.pushDrawModeOff(OD_MAGNITUDE);


// *!*HTML_TAG*!* draw

	// Create versor that generates the sea shell:
	TRSversor V = _TRSversor((1.0f - 0.25f * e3ni) * exp(_bivectorE3GA((e1^e2) * 0.4f)) * exp(_noni_t(-0.05f  * noni)));
	// Take 1/5st of the versor:
 	V = exp(0.2f * log(V));

	// precompute inverse of the versor:
	TRSversor Vi = _TRSversor(inverse(V));

	// get the circle:
	circle C = g_circle;

	if (GLpick::g_pickActive) glLoadName(CIRCLE_NAME);

	// draw the circles:
	glColor3fm(0.0f, 0.6f, 0.0f);
	const int NB_ITER = 200;
	for (int i = 0; i < NB_ITER; i++) {
		draw(C);
		// update circle such that we draw a 'trail' of circles
		C = V * C * Vi;
		if (GLpick::g_pickActive) glLoadName((GLuint)-1); // ignore all circles beyond the first one
	}

	// get the sphere:
	sphere S  = g_sphere;

	if (GLpick::g_pickActive) glLoadName(SPHERE_NAME);

	// draw spheres:
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4fm(0.6f, 0.0f, 0.0f, 0.5f);
	for (int i = 0; i < NB_ITER; i++) {
		draw(S);
		// update sphere such that we draw a 'trail' of spheres
		S = V * S * Vi;
		if (GLpick::g_pickActive) glLoadName((GLuint)-1); // ignore all spheres beyond the first one
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	g_drawState.popDrawMode();
	g_drawState.popDrawMode();

	glPopMatrix();

	if (!GLpick::g_pickActive)
		glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// redraw viewport
	glutPostRedisplay();
}

vectorE2GA mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return _vectorE2GA((float)x * e1 - (float)y * e2);
}

vectorE3GA vectorAtDepth(double depth, const vectorE2GA &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return c3ga::vectorE3GA();
	}

	return _vectorE3GA((depth * (double)v2d.e1() * GLpick::g_frustumWidth) / (g_viewportWidth * GLpick::g_frustumNear) * e1 +
		(depth * (double)v2d.e2() * GLpick::g_frustumHeight) / (g_viewportHeight * GLpick::g_frustumNear) * e2);
}

void MouseButton(int button, int state, int x, int y) {
	if (state != GLUT_DOWN) return; // don't respond when button goes up . . .

	g_dragWhat = pick(x, g_viewportHeight - y, display, &g_dragDistance);
	g_rotateModel = (g_dragWhat < 0);

	vectorE2GA mousePos = mousePosToVector(x, y);
	if (g_rotateModel) {
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}

	g_prevMousePos = mousePos;

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
	else if (g_dragWhat > 0)  {
		vectorE3GA t = vectorAtDepth(g_dragDistance, motion);
		t = _vectorE3GA(inverse(g_modelRotor) * t * g_modelRotor);
		normalizedTranslator T = exp(_freeVector(-0.5f * (t ^ ni)));

		if (g_dragWhat == CIRCLE_NAME)
			g_circle = T * g_circle * inverse(T);
		else g_sphere = T * g_sphere * inverse(T);
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

	mv::Float e = 2.71828182845904523536f;

	// create a circle at the right position:
	g_circle = dual( no<<((no+e2)^ni) ^e1);
	normalizedTranslator TC = exp(_freeVector(-0.5f * e * e3ni));
	g_circle = TC * g_circle * inverse(TC);

	// create a sphere at the right position:
	g_sphere = dual(no- 0.005f * ni);
	normalizedTranslator TS = exp(_freeVector(-0.5f * (e * e3ni + 2.0f * e2ni)));
	g_sphere = TS * g_sphere * inverse(TS);

	glutMainLoop();

	return 0;
}


