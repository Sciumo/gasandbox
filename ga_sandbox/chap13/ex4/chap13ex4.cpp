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

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 13, Example 4: Interpolation of Rigid Body Motions";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;

// mouse position on last call to MouseButton() / MouseMotion()
vectorE3GA g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// rotation of the model
rotor g_modelRotor(_rotor(1.0f));

// when did the current interpolation start?
double g_startTime = -1.0;

// how long does one interpolation take:
const double interpolationTime = 1.0f;

// interpolate from:
TRversor g_sourceVersor;
// interpolate to:
TRversor g_destVersor;

// we show a trail of previous frames:
double g_prevTrailTime = -1;
std::vector<circle> g_circleTrail;


void copyDestToSource() {
	g_sourceVersor = g_destVersor;
}

void initRandomDest() {
	normalizedTranslator T1 =  exp(_freeVector(randomBlade(2, 3.0f)));
	normalizedTranslator T2 =  exp(_freeVector(randomBlade(2, 3.0f)));
	rotor R = exp(_bivectorE3GA(randomBlade(2, 100.0f)));

	g_destVersor = _TRversor(T1 * T2 * R * inverse(T2));
}

// *!*HTML_TAG*!* interpolate

// interpolate between 'src' and 'dst', as determined by 'alpha' (alpha is in range [0 1])
TRversor interpolateTRversor(const TRversor &src, const TRversor &dst, mv::Float alpha) {
	// return src * exp(alpha * log(inverse(src) * dst));
	return _TRversor(src * exp(_dualLine(alpha * log(_TRversor(inverse(src) * dst)))));
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
	TRversor V = interpolateTRversor(g_sourceVersor, g_destVersor, alpha);

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

	circle C = _circle((e1^e2^no) + (e1^e2^ni));
	circle imageOfC = _circle(V * C * inverse(V));

	// draw the circle
	glColor3fm(0.0f, 0.0f, 0.0f);
	draw(imageOfC);

	// draw trail:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (unsigned int i = 0; i < g_circleTrail.size(); i++) {
		float a = 0.7f * (float)i / (float)(g_circleTrail.size());

		// draw the frame
		glColor4fm(1.0f - a, 1.0f - a, 1.0f - a, a);
		draw(g_circleTrail[i]);
	}

	glDisable(GL_BLEND);

	// update the trail:
	if (((currentTime - g_prevTrailTime) / interpolationTime) > 0.15) {
		g_prevTrailTime = currentTime;
		g_circleTrail.push_back(imageOfC);

		// trim trail to length 20:
		if (g_circleTrail.size() > 20) {
			g_circleTrail.erase(g_circleTrail.begin());
		}
	}



	glPopMatrix();

/*
	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	void *font = GLUT_BITMAP_HELVETICA_12;
	renderBitmapString(20, 20, font, ". . .");
*/

	glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// redraw viewport
	glutPostRedisplay();
}

vectorE3GA mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return _vectorE3GA((float)x * e1 - (float)y * e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	vectorE3GA mousePos = mousePosToVector(x, y);
	g_rotateModel = true;
	if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
		g_rotateModelOutOfPlane = true;
	else g_rotateModelOutOfPlane = false;
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	vectorE3GA mousePos = mousePosToVector(x, y);
	vectorE3GA motion = _vectorE3GA(mousePos - g_prevMousePos);
	if (g_rotateModel) {
		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(exp(_bivectorE3GA(0.005f * (motion ^ e3))) * g_modelRotor);
		else g_modelRotor = _rotor(exp(_bivectorE3GA(0.00001f * (motion ^ mousePos))) * g_modelRotor);
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


