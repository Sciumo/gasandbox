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

// not sure whether this should be <opencv/cxcore.h> or just <cxcore.h>
//#include <cxcore.h>
#include <opencv/cxcore.h>

#include <vector>

#include <libgasandbox/c3ga.h>
#include <libgasandbox/c3ga_draw.h>
#include <libgasandbox/c3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>
#include <libgasandbox/mv_analyze.h>

using namespace c3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 14, Example 4: Fitting a Sphere";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

// mouse position on last call to MouseButton() / MouseMotion()
vectorE2GA g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

const float g_modelDistance = -16.0f;

const int FLATTEN = -2;
const int NONE = -1;
const int MODE_DRAG = 0;
const int MODE_CREATE_POINTS = 1;

const char *g_modeName[] = {
	"Drag points",
	"Create points (no scene orbit available)",
};


int g_mouseMode = MODE_DRAG;


// what point to drag (or -1 for none)
int g_dragPoint = -1;
float g_dragDistance = 4.0f;

// rotation of the model
rotor g_modelRotor(_rotor(1.0f));

// the points:
std::vector<point> g_points;

vectorE3GA vectorAtDepth(double depth, const vectorE2GA &v2d);

// *!*HTML_TAG*!* fitSphere
dualSphere fitSphere(const std::vector<point> &points) {
	float P[5 * 5];
	{ // compute matrix P = sum_i (points[i] . points[i]^T)
		// first clear all entries:
		for (int i = 0; i < 5 * 5; i++) P[i] = 0.0f;

		// fill the matrix:
		for (unsigned int p = 0; p < points.size(); p++) {
			// get coordinates of point 'p':
			const mv::Float *pc = points[p].getC(point_no_e1_e2_e3_ni);

			for (int i = 0; i < 5; i++)
				for (int j = i; j < 5; j++) {
					P[i * 5 + j] += pc[i] * pc[j];
					P[j * 5 + i] = P[i * 5 + j];
				}
		}
	}

	// initialize the metric matrix:
	float M[5 * 5] = {
	//  no    e1    e2    e3     ni
		 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // no
		 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, // e1
		 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, // e2
		 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, // e3
		-1.0f, 0.0f, 0.0f, 0.0f,  0.0f  // ni
	};

	// construct OpenCV matrices (on stack)
	CvMat matrixP = cvMat(5, 5, CV_32F, P);
	CvMat matrixM = cvMat(5, 5, CV_32F, M);

	// use OpenCV to multiply matrices
	float PM[5 * 5];
	CvMat matrixPM = cvMat(5, 5, CV_32F, PM); // create matrix P * M (on stack)
	cvMatMul(&matrixP, &matrixM, &matrixPM);

	// use OpenCV to compute SVD
	float S[5 * 5], U[5 * 5], V[5 * 5];
	CvMat matrixS = cvMat(5, 5, CV_32F, S); // create matrix S (on stack)
	CvMat matrixU = cvMat(5, 5, CV_32F, U); // create matrix U (on stack)
	CvMat matrixV = cvMat(5, 5, CV_32F, V); // create matrix V (on stack)
	int flags = 0;
	cvSVD(&matrixPM, &matrixS, &matrixU, &matrixV, flags); // compute SVD

	// extract last column of V (coordinates of dual sphere);
	dualSphere DS(dualSphere_no_e1_e2_e3_ni,
		V[0 * 5 + 4], V[1 * 5 + 4], V[2 * 5 + 4], V[3 * 5 + 4], V[4 * 5 + 4]);

	return DS;
}



void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	 dualSphere DS = fitSphere(g_points);

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
	glTranslatef(0.0f, 0.0f, g_modelDistance);


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

	// we collect all lines and planes in this list:
	std::vector<mv> primitives;

	// draw the points
	glColor3fm(1.0f, 0.0f, 0.0f);
	g_drawState.m_pointSize = 0.1f;
	for (unsigned int i = 0; i < g_points.size(); i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		draw(g_points[i]);
	}

	if (GLpick::g_pickActive) glLoadName((GLuint)-1);

	g_drawState.pushDrawModeOff(OD_ORIENTATION);
	g_drawState.pushDrawModeOff(OD_MAGNITUDE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4fm(0.0f, 0.0f, 1.0f, 0.5f);
	draw(dual(DS));
	glDisable(GL_BLEND);
	g_drawState.popDrawMode();
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
		glColor3f(0.0f, 0.0f, 0.0f);
		void *font = GLUT_BITMAP_HELVETICA_12;


		{
			char buf[256];
			sprintf(buf, "MODE: %s\n", g_modeName[g_mouseMode]);
			renderBitmapString(20, g_viewportHeight - 20, font, buf);
		}

		renderBitmapString(20, 60, font, "Use the left mouse button to manipulate the scene, and to orbit it.");
		renderBitmapString(20, 40, font, "Use the other mouse buttons to access the popup menu, and select different manipulation modes.");
		renderBitmapString(20, 20, font, "The intersections of the primitives are drawn in light grey.");
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

vectorE3GA vectorAtDepth(double depth, const vectorE2GA &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return c3ga::vectorE3GA();
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
	if (state != GLUT_DOWN) return; // don't respond when button goes up . . .

	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	if (g_mouseMode == MODE_DRAG) {
		g_dragPoint = pick(x, g_viewportHeight - y, display, &g_dragDistance);
		g_rotateModel = (g_dragPoint < 0);
	}
	else if (g_mouseMode == MODE_CREATE_POINTS) {

		// get modelview matrix (as used for drawing the scene) from OpenGL:
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, g_modelDistance);
		rotorGLMult(g_modelRotor);
		mv::Float modelviewMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
		glPopMatrix();

		// convert modelview matrix to versor:
		bool transpose = true;
		TRversor V = _TRversor(matrix4x4ToVersorPS(modelviewMatrix, transpose));

		// create a new point at g_dragDistance from camera
		float dis = g_dragDistance;
		if (dis > 20.0) dis = 20.0;
		point pt = _point(c3gaPoint(_vectorE3GA(vectorAtDepth(dis, g_prevMousePos) - e3 * dis)));

		// use OpenGL transform to create a point at the right location (`under' the mouse)
		pt = inverse(V) * pt * V;

		// add point to list:
		g_points.push_back(pt); // c3gaPoint(_vectorE3GA(-no << fpt))));

		g_dragPoint = (int)g_points.size()-1;
	}

	if (g_rotateModel) {
		vectorE2GA mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2f)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}

	// redraw viewport
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	vectorE2GA mousePos = mousePosToVector(x, y);
	vectorE2GA motion = _vectorE2GA(mousePos - g_prevMousePos);
	if (g_rotateModel) {
		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(c3ga::exp(0.005f * (motion ^ e3)) * g_modelRotor);
		else g_modelRotor = _rotor(c3ga::exp(0.00001f * (motion ^ mousePos)) * g_modelRotor);
	}
	else if (g_dragPoint >= 0) {
		vectorE3GA t = vectorAtDepth(g_dragDistance, motion);
		t = _vectorE3GA(inverse(g_modelRotor) * t * g_modelRotor);
		normalizedTranslator T = exp(_freeVector(-0.5f * (t ^ ni)));

		// note the hack required here (repeated application of translators turns points into spheres, at least, with 32-bit floats  :(     )
		g_points[g_dragPoint] =
				_point(c3gaPoint(_vectorE3GA(T * g_points[g_dragPoint] * inverse(T))));
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void PassiveMouseMotion(int x, int y) {
	// remember mouse pos for next motion:
	g_prevMousePos = mousePosToVector(x, y);
}

void menuCallback(int value) {
	if (value >= 0) {
		g_mouseMode = value;
	}
	else if (value == FLATTEN) {
		// project all onto e3:
		for (unsigned int i = 0; i < g_points.size(); i++) {
			g_points[i] = _point(c3gaPoint(g_points[i].e1(), g_points[i].e2(), 0.0f));
		}
	}

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
	glutPassiveMotionFunc(PassiveMouseMotion);

	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry(g_modeName[MODE_DRAG], MODE_DRAG);
	glutAddMenuEntry(g_modeName[MODE_CREATE_POINTS], MODE_CREATE_POINTS);
	glutAddMenuEntry("--------------------------------------------", NONE);
	glutAddMenuEntry("Project points onto the plane dual(e3)", FLATTEN);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// create the initial points
	g_points.push_back(_point(c3gaPoint(1.0f, 1.0f, 0.0f)));
	g_points.push_back(_point(c3gaPoint(-1.0f, 1.0f, 0.0f)));
	g_points.push_back(_point(c3gaPoint(1.0f, 0.0f, 0.0f)));
	g_points.push_back(_point(c3gaPoint(0.0f, 1.0f, 2.0f)));


	glutMainLoop();

	return 0;
}
