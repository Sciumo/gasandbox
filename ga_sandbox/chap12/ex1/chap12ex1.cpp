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

// Daniel Fontijne -- fontijne@science.uva.nl

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glut.h>
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

#include "readopticaldata.h"


using namespace h3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 12, Example 1: Marker Reconstruction in Optical Motion Capture";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

// mouse position on last call to MouseButton() / MouseMotion()
h3ga::vector g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

/// rotation of the model
h3ga::rotor g_modelRotor(_rotor(1.0f));


/// the raw marker data:
OpticalCaptureData g_opticalCaptureData;

/// what frame are we displaying currently?
double g_currentFrameIdx = 10.0f;

/// What was the last time we changed frames?
double g_prevFrameTime = -1.0;

/// when true, the idle() function auto-updates 'g_currentFrameIdx' and m_prevFrameTime'
bool g_playing = false;

/// how many cameras make a marker?
int g_minNbCams = 3;

const double FPS = 60.0;

#define DRAW_MARKERS 1
#define DRAW_RAYS 2
#define DRAW_CAMERAS 4
#define DRAW_IMAGE_PLANES 8

int g_draw = DRAW_MARKERS | DRAW_CAMERAS;

#define PLAYBACK -1
#define MIN_NB_CAMS_2 -2
#define MIN_NB_CAMS_3 -3
#define MIN_NB_CAMS_4 -4


void drawCamera();


void display() {
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
	glTranslatef(0.0f, 0.0f, -8.0f);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glLineWidth(1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);

	int frameIdx = (int)g_currentFrameIdx;
	if (frameIdx >= (int)g_opticalCaptureData.m_cameraData[0].m_2Dmarkers.size())
		frameIdx = 0;

	if (g_draw & DRAW_CAMERAS) {
		// draw all cameras
		for (unsigned int c = 0; c < g_opticalCaptureData.m_cameraData.size(); c++) {
			const OpticalCaptureCameraData &C = g_opticalCaptureData.m_cameraData[c];
			glPushMatrix();
			// translate / rotate to camera pos/ori
			versorGLMult(C.m_XF);

			// draw the camera:
			glColor3f(1.0, 0.0, 0.0);
			drawCamera();

			glPopMatrix();
		}
	}

	if (g_draw & DRAW_RAYS) {
		// draw rays from camera to marker, for all markers
		glColor3f(0.0f, 1.0f, 0.0f);

		glBegin(GL_LINES);
		for (unsigned int c = 0; c < g_opticalCaptureData.m_cameraData.size(); c++) {
			const OpticalCaptureCameraData &C = g_opticalCaptureData.m_cameraData[c];
			for (unsigned int m = 0; m < C.m_2Dmarkers[frameIdx].size(); m++) {
				// todo: position = point, and longer rays
				// next up: write recon function
				const normalizedPoint &pt = C.m_2Dmarkers[frameIdx][m]

				// draw line from camera center, out into the scene:
				glVertex3fv(C.m_position.getC(h3ga::vector_e1_e2_e3));
				glVertex3fv(_vector(C.m_2Dmarkers[frameIdx][m] + 3.0f * ()).getC(vector_e1_e2_e3));
			}
		}
		glEnd();
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
	renderBitmapString(20, 40, font, "Yada ");
	renderBitmapString(20, 20, font, "Yada ");

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

	h3ga::vector mousePos = mousePosToVector(x, y);
	g_rotateModel = true;
	if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
		g_rotateModelOutOfPlane = true;
	else g_rotateModelOutOfPlane = false;

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

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void menuCallback(int value) {
	if (value < 0) {
		if (value == PLAYBACK) {
			g_playing = !g_playing;
			if (g_playing) g_prevFrameTime = u_timeGet();
		}
		else if (value == MIN_NB_CAMS_2) g_minNbCams = 2;
		else if (value == MIN_NB_CAMS_3) g_minNbCams = 3;
		else if (value == MIN_NB_CAMS_4) g_minNbCams = 4;
	}
	else {
		// toggle the DRAW_XXX constant
		g_draw ^= value;
	}

	// redraw viewport
	glutPostRedisplay();
}

void Idle() {
	printf("IDle!\n");
	if (g_playing) {
		// update the current frame:
		double t = u_timeGet();
		if (g_prevFrameTime >= 0.0) {
			g_currentFrameIdx += (t - g_prevFrameTime) * FPS;
			double nbFrames = (double)g_opticalCaptureData.m_cameraData[0].m_2Dmarkers.size();
			while ((int)g_currentFrameIdx > nbFrames)
				g_currentFrameIdx -= nbFrames;
			printf("Frame %f\n", g_currentFrameIdx);
		}
		g_prevFrameTime = t;

		// redraw viewport
		glutPostRedisplay();
	}
}

int LoadData() {
	try {
		g_opticalCaptureData = readOpticalData("chap12data.txt");
	} catch (const std::string &str) {
		printf("Error: %s\n", str.c_str());
		return -1;
	}
	return 0;
}


int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	h3ga::g2Profiling::init();

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
	glutIdleFunc(Idle);


	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry("Draw Reconstructed Markers", DRAW_MARKERS);
	glutAddMenuEntry("Draw Rays", DRAW_RAYS);
	glutAddMenuEntry("Draw Cameras", DRAW_CAMERAS);
	glutAddMenuEntry("Draw Image Planes", DRAW_IMAGE_PLANES);
	glutAddMenuEntry("-------------------", 0);
	glutAddMenuEntry("Playback data", PLAYBACK);
	glutAddMenuEntry("-------------------", 0);
	glutAddMenuEntry(">= 2 cams / marker", MIN_NB_CAMS_2);
	glutAddMenuEntry(">= 3 cams / marker", MIN_NB_CAMS_3);
	glutAddMenuEntry(">= 4 cams / marker", MIN_NB_CAMS_4);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}
