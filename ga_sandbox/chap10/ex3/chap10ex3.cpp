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
	#include <CoreServices/CoreServices.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_draw.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>

#include "readcalibrationdata.h"

using namespace e3ga;
using namespace extCalibRefine;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 10, Example 3: External Camera Calibration";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

// mouse position on last call to MouseButton() / MouseMotion()
e3ga::vector g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// rotation of the model
e3ga::rotor g_modelRotor(_rotor(1.0f));

#define REFINE_1X -1
#define REFINE_10X -2
#define REFINE_1_SEC - 3

#define DRAW_MARKERS 1
#define DRAW_ERRORS 2
#define DRAW_RAYS 4
#define DRAW_CAMERAS 8
#define DRAW_PATH 16

#define RELOAD_DATA -4

int g_draw = DRAW_MARKERS | DRAW_CAMERAS;


// the calibration state:
extCalibRefine::State g_extCalibState;

void drawCamera();


void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

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
	glTranslatef(0.0f, 0.0f, -4.0f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glLineWidth(1.0f);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);

	if (g_draw & DRAW_CAMERAS) {
		// draw all cameras
		for (unsigned int c = 0; c < g_extCalibState.m_cam.size(); c++) {
			const Camera &C = g_extCalibState.m_cam[c];
			glPushMatrix();
			// translate / rotate to camera pos/ori
			glTranslatef(C.m_t.e1(), C.m_t.e2(), C.m_t.e3());
			rotorGLMult(C.m_R);

			// draw the camera:
			glColor3f(1.0, 0.0, 0.0);
			drawCamera();

			glPopMatrix();
		}
	}

	if (g_draw & DRAW_MARKERS) {
		// draw all markers
		glColor3f(0.0f, 0.0f, 0.0f);
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		for (unsigned int f = 0; f < g_extCalibState.m_pt.size(); f++) {
			if (g_extCalibState.m_ptValid[f]) {
				glVertex3fv(g_extCalibState.m_pt[f].getC(vector_e1_e2_e3));
			}
		}
		glEnd();
	}

	if (g_draw & DRAW_ERRORS) {
		// draw errors for all markers
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		for (unsigned int f = 0; f < g_extCalibState.m_pt.size(); f++) {
			if (g_extCalibState.m_ptValid[f]) {
				for (unsigned int c = 0; c < g_extCalibState.m_cam.size(); c++) {
					const Camera &C = g_extCalibState.m_cam[c];
					if (!C.m_visible[f]) continue;

					// compute point as reconstructed by single camera:
					vector camPt = _vector(C.m_t + apply_om(C.m_Rom, _vector(C.m_X3[f] * C.m_pt[f])));

					// draw line from fully reconstructed point to point as reconstructed by single camera:
					glVertex3fv(g_extCalibState.m_pt[f].getC(vector_e1_e2_e3));
					glVertex3fv(camPt.getC(vector_e1_e2_e3));
				}
			}
		}
		glEnd();
	}

	if (g_draw & DRAW_RAYS) {
		// draw rays from camera to marker, for all markers
		glColor3f(0.0f, 1.0f, 0.0f);

		glBegin(GL_LINES);
		for (unsigned int c = 0; c < g_extCalibState.m_cam.size(); c++) {
			const Camera &C = g_extCalibState.m_cam[c];
			for (unsigned int f = 0; f < g_extCalibState.m_pt.size(); f++) {
				if (!C.m_visible[f]) continue;

				// draw line from camera center, out into the scene:
				glVertex3fv(C.m_t.getC(vector_e1_e2_e3));
				glVertex3fv(_vector(C.m_t + 4.0f * C.m_pt[f]).getC(vector_e1_e2_e3));
			}
		}
		glEnd();
	}

	if (g_draw & DRAW_PATH) {
		// draw path that connects all markers (but stipple it when frames are missing)
		glLineStipple(1, 0x0F0F);

		glColor3f(0.5f, 0.5f, 0.5f);
		const e3ga::vector *lastValidPt = NULL;
		bool contMode = true; // continuous mode
		glBegin(GL_LINE_STRIP);
		for (unsigned int f = 0; f < g_extCalibState.m_pt.size(); f++) {
			if (g_extCalibState.m_ptValid[f]) {
				glVertex3fv(g_extCalibState.m_pt[f].getC(vector_e1_e2_e3));
				lastValidPt = &(g_extCalibState.m_pt[f]);
				if (!contMode) {
					glEnd(); // end GL_LINES
					glDisable(GL_LINE_STIPPLE);
					contMode = true;
					glBegin(GL_LINE_STRIP); // start new GL_LINE_STRIP
					glVertex3fv(g_extCalibState.m_pt[f].getC(vector_e1_e2_e3));
				}
			}
			else {
				if (contMode) {
					contMode = false;
					glEnd();
					glEnable(GL_LINE_STIPPLE);
					glBegin(GL_LINES); // start new GL_LINES
					if (lastValidPt)
						glVertex3fv(lastValidPt->getC(vector_e1_e2_e3));
				}
			}
		}
		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}




	glPopMatrix();

	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 0.0f, 0.0f);
	void *font = GLUT_BITMAP_HELVETICA_12;
	{
		char buf[1024];
		sprintf(buf, "Current cost function: %e", g_extCalibState.costFunction());
		renderBitmapString(20, 80, font, buf);
	}
	renderBitmapString(20, 60, font, "Use left mouse button to orbit scene.");
	renderBitmapString(20, 40, font, "Use other mouse buttons to access popup-menu.");
	renderBitmapString(20, 20, font, "In popup-menu, use \"Refine ...\" to refine the calibration.");

	glutSwapBuffers();
}


void drawCamera() {
	float rect[4][2] =
	{
		-1.0f, 0.75f,
		1.0f, 0.75f,
		1.0f, -0.75f,
		-1.0f, -0.75f,
	};
	float f = 0.5;
	int i;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < 4; i++) {
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(f * rect[i][0], f * rect[i][1], -1.0f);
		glVertex3f(f * rect[(i+1)%4][0], f * rect[(i+1)%4][1], -1.0f);
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -4.0f);
	glEnd();
	glPopMatrix();
}


void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// redraw viewport
	glutPostRedisplay();
}


e3ga::vector vectorAtDepth(double depth, const e3ga::vector &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return e3ga::vector();
	}

	return _vector((depth * (double)v2d.e1() * GLpick::g_frustumWidth) / (g_viewportWidth * GLpick::g_frustumNear) * e1 +
		(depth * (double)v2d.e2() * GLpick::g_frustumHeight) / (g_viewportHeight * GLpick::g_frustumNear) * e2);
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

void getfilename(const char *name, char *filename, int n) {
	filename[0] = '\0';
	#if defined (__APPLE__) || defined (OSX)
		FSRef fileref;
		Boolean isDir;
		FSPathMakeRef((const UInt8 *)name, &fileref, &isDir);
		
		FSRefMakePath(&fileref, (UInt8 *)filename, n);
	#else
		strcpy(filename, name);
	#endif
}


int LoadData() {
	try {
		char filename[512];
		getfilename("calibration_data.txt", filename, 512);
		g_extCalibState = readCalibrationData(filename);
	} catch (const std::string &) {
		try {
			// try alternative path, when called from inside visual studio:
			g_extCalibState = readCalibrationData("../chap10/ex3/calibration_data.txt");
		} catch (const std::string &str) {
			printf("Error: %s\n", str.c_str());
			return -1;
		}
	}
	return 0;
}

void menuCallback(int value) {
	if (value < 0) {
		if (value == REFINE_1X)
			g_extCalibState.refineLoops(1);
		else if (value == REFINE_10X)
			g_extCalibState.refineLoops(10);
		else if (value == REFINE_1_SEC)
			g_extCalibState.refineSeconds(1.0);
		else if (value == RELOAD_DATA)
			LoadData();
	}
	else {
		// toggle the DRAW_XXX constant
		g_draw ^= value;
	}

	// redraw viewport
	glutPostRedisplay();
}

/*
void Idle() {
	// redraw viewport
	glutPostRedisplay();
}
*/

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();

	// load calibration data
	if (LoadData() < 0) return -1;

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
//	glutIdleFunc(Idle);

	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry("Refine 1x", REFINE_1X);
	glutAddMenuEntry("Refine 10x", REFINE_10X);
	glutAddMenuEntry("Refine for One Second", REFINE_1_SEC);
	glutAddMenuEntry("-------------------", 0);
	glutAddMenuEntry("Draw Markers", DRAW_MARKERS);
	glutAddMenuEntry("Draw Errors", DRAW_ERRORS);
	glutAddMenuEntry("Draw Rays", DRAW_RAYS);
	glutAddMenuEntry("Draw Cameras", DRAW_CAMERAS);
	glutAddMenuEntry("Draw Marker Path", DRAW_PATH);
	glutAddMenuEntry("-------------------", 0);
	glutAddMenuEntry("Reload data (restart)", RELOAD_DATA);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}
