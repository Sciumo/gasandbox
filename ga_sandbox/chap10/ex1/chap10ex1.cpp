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

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_draw.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>

using namespace e3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 10, Example 1: Interpolation of Rotations";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;

// mouse position on last call to MouseButton() / MouseMotion()
e3ga::vector g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// rotation of the model
e3ga::rotor g_modelRotor(_rotor(1.0f));

// when did the current interpolation start?
double g_startTime = -1.0;

// how long does one interpolation take:
const double interpolationTime = 1.5f;

// interpolate from:
e3ga::vector g_sourcePosition;
rotor g_sourceOrientation;
// interpolate to:
e3ga::vector g_destPosition;
rotor g_destOrientation;

// we show a trail of previous frames:
double g_prevTrailTime = -1;
std::vector<e3ga::vector> g_positionTrailE1;
std::vector<e3ga::vector> g_positionTrailE2;
std::vector<e3ga::vector> g_positionTrailE3;
std::vector<e3ga::vector> g_posTrail;


void copyDestToSource() {
	g_sourcePosition = g_destPosition;
	g_sourceOrientation = g_destOrientation;
}

void initRandomDest() {
	// set new position to random vector (max length 6.0f)
	g_destPosition = _vector(randomBlade(1, 6.0f));
	// set new orientation to exp() of random bivector
	g_destOrientation = exp(_bivector(randomBlade(2, 100.0f)));
}

// *!*HTML_TAG*!* interpolate
e3ga::vector interpolateVector(const e3ga::vector &src, const e3ga::vector &dst, mv::Float alpha) {
	return _vector((1.0f - alpha) * src + alpha * dst);
}

rotor interpolateRotor(const rotor &src, const rotor &dst, mv::Float alpha) {
	// return src * exp(alpha * log(inverse(src) * dst));
	return _rotor(src * exp(_bivector(alpha * log(_rotor(inverse(src) * dst)))));
}



void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	double currentTime = u_timeGet();

	// check if we should get new random dest
	if (currentTime - g_startTime > interpolationTime) {
		g_startTime = g_startTime + interpolationTime;

		// when the process has been 'asleep' for a long time, simply skip:
		if (currentTime - g_startTime > interpolationTime)
			g_startTime = currentTime;

		// start new interpolation
		copyDestToSource();
		initRandomDest();
	}

	// interpolate:
	mv::Float alpha = (mv::Float)(currentTime - g_startTime) / (mv::Float)interpolationTime;
	e3ga::vector pos = interpolateVector(g_sourcePosition, g_destPosition, alpha);
	rotor ori = interpolateRotor(g_sourceOrientation, g_destOrientation, alpha);

	// setup projection & transform for the vectors:
	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	const float screenWidth = 1600.0f;
	glLoadIdentity();
	GLpick::g_frustumWidth = 2.0 *  (double)g_viewportWidth / screenWidth;
	GLpick::g_frustumHeight = 2.0 *  (double)g_viewportHeight / screenWidth;
	glFrustum(
		-GLpick::g_frustumWidth / 2.0, GLpick::g_frustumWidth / 2.0,
		-GLpick::g_frustumHeight / 2.0, GLpick::g_frustumHeight / 2.0,
		GLpick::g_frustumNear, GLpick::g_frustumFar);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -12.0f);


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

	e3ga::vector imageOfE1 = _vector(ori * e1 * inverse(ori));
	e3ga::vector imageOfE2 = _vector(ori * e2 * inverse(ori));
	e3ga::vector imageOfE3 = _vector(ori * e3 * inverse(ori));

	// draw the frame
	glPushMatrix();
		// translate to origin:
		glTranslatef(pos.e1(), pos.e2(), pos.e3());

		// draw the frame
		glColor3fm(1.0f, 0.0f, 0.0f);
		draw(imageOfE1);
		glColor3fm(0.0f, 1.0f, 0.0f);
		draw(imageOfE2);
		glColor3fm(0.0f, 0.0f, 1.0f);
		draw(imageOfE3);
	glPopMatrix();

	// draw trail:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (unsigned int i = 0; i < g_positionTrailE1.size(); i++) {
		float a = 0.7f * (float)i / (float)(g_positionTrailE1.size());
		glPushMatrix();
			// translate to origin:
			glTranslatef(g_posTrail[i].e1(), g_posTrail[i].e2(), g_posTrail[i].e3());

			// draw the frame
			glColor4fm(a, 0.0f, 0.0f, a);
			draw(g_positionTrailE1[i]);
			glColor4fm(0.0f, a, 0.0f, a);
			draw(g_positionTrailE2[i]);
			glColor4fm(0.0f, 0.0f, a, a);
			draw(g_positionTrailE3[i]);
		glPopMatrix();
	}

	glDisable(GL_BLEND);

	// update the trail:
	if (((currentTime - g_prevTrailTime) / interpolationTime) > 0.1) {
		g_prevTrailTime = currentTime;
		g_positionTrailE1.push_back(imageOfE1);
		g_positionTrailE2.push_back(imageOfE2);
		g_positionTrailE3.push_back(imageOfE3);
		g_posTrail.push_back(pos);

		// trim trail to length 10:
		if (g_positionTrailE1.size() > 10) {
			g_positionTrailE1.erase(g_positionTrailE1.begin());
			g_positionTrailE2.erase(g_positionTrailE2.begin());
			g_positionTrailE3.erase(g_positionTrailE3.begin());
			g_posTrail.erase(g_posTrail.begin());
		}

	}



	glPopMatrix();

	glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// redraw viewport
	glutPostRedisplay();
}

e3ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return e3ga::_vector((float)x * e3ga::e1 - (float)y * e3ga::e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	e3ga::vector mousePos = mousePosToVector(x, y);
	g_rotateModel = true;
	if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
		g_rotateModelOutOfPlane = true;
	else g_rotateModelOutOfPlane = false;
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

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

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

	// initialize the interpolation data:
	srand(time(NULL));
	g_startTime = u_timeGet();
	initRandomDest();
	copyDestToSource();
	initRandomDest();


	glutMainLoop();

	return 0;
}
