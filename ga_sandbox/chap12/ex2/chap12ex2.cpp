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

#include <libgasandbox/h3ga.h>
#include <libgasandbox/h3ga_draw.h>
#include <libgasandbox/h3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>
#include <libgasandbox/mv_analyze.h>

using namespace h3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 12, Example 2: Transforming Primitives with OpenGL Matrices";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

// mouse position on last call to MouseButton() / MouseMotion()
h3ga::vector g_prevMousePos;

// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

const int MODE_DRAG = 0;
const int MODE_CREATE_POINTS = 1;
const int MODE_CREATE_LINES = 2;
const int MODE_CREATE_PLANES = 3;

const char *g_modeName[] = {
	"Drag red points",
	"Create points (no scene orbit available)",
	"Create lines (select two points)",
	"Create planes (select three points)",
};


int g_mouseMode = MODE_DRAG;


// what point to drag (or -1 for none)
int g_dragPoint = -1;
float g_dragDistance = 16.0f;

// rotation of the model
h3ga::rotor g_modelRotor(_rotor(1.0f));

// the points:
std::vector<normalizedPoint> g_points;

// the lines (pairs of indices into g_points)
std::vector<std::vector<int> > g_lines;

// the planes (triplets of indices into g_points)
std::vector<std::vector<int> > g_planes;

// used for construction of new lines:
std::vector<int> g_createLinePtList;
// used for construction of new planes:
std::vector<int> g_createPlanePtList;


h3ga::vector vectorAtDepth(double depth, const h3ga::vector &v2d);

// *!*HTML_TAG*!* apply
void applyTransformAndDraw(const om &M, const mv &X) {
	// apply the outermorphism:
	mv MX = apply_om(M, X);

	// determine the new origin (used as probe)
	point origin = _point(apply_om(M, e0));
	origin = origin * (1.0f / origin.e0());

	//  analyze with custom probe:
	int flags = 0;
	mv_analyze::mvAnalysis A(MX, flags, mv_analyze::DEFAULT_EPSILON, _normalizedPoint(origin));

	// draw the analysis
	drawH3GA(A);
}

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
	glTranslatef(0.0f, 0.0f, -16.0f);


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
	g_drawState.m_planeSize = 5.0f;


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);

	// extract OpenGL modelview matrix
	float MVM[16];
	glMatrixMode(GL_MODELVIEW);
	glGetFloatv(GL_MODELVIEW_MATRIX, MVM);

	// reset OpenGL modelview matrix (we will apply the transform ourselves)
	glLoadIdentity();

	// initialize the images of the basis vectors:
	point images[4];
	for (int i = 0; i < 4; i++) {
		images[i].set(point_e1_e2_e3_e0, &(MVM[i * 4]));
		// or:
		// images[i].set(point_e1_e2_e3_e0, MVM[i * 4 + 0], MVM[i * 4 + 1], MVM[i * 4 + 2], MVM[i * 4 + 3]);
	}

	// initialized matrix representation of outer morphism
	om M(images);

	// we collect all lines and planes in this list:
	std::vector<mv> primitives;

	// draw the points
	glColor3fm(1.0f, 0.0f, 0.0f);
	g_drawState.m_pointSize = 0.005f;
	for (unsigned int i = 0; i < g_points.size(); i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		applyTransformAndDraw(M, g_points[i]);
//		primitives.push_back(g_points[i]);
	}

	if (GLpick::g_pickActive) glLoadName((GLuint)-1);

	if (!GLpick::g_pickActive) {

		// draw the lines
		g_drawState.pushDrawModeOff(OD_ORIENTATION);
		glColor3fm(0.0f, 1.0f, 0.0f);
		for (unsigned int i = 0; i < g_lines.size(); i++) {
			int pointIdx1 = g_lines[i][0];
			int pointIdx2 = g_lines[i][1];

			// compute the line from the points:
			line L = _line(g_points[pointIdx1] ^ g_points[pointIdx2]);
			// draw it:
			applyTransformAndDraw(M, L);

			primitives.push_back(unit_r(L));
		}
		g_drawState.popDrawMode();

		// COMPUTE the planes (they are drawn last, because they are transparent
		for (unsigned int i = 0; i < g_planes.size(); i++) {
			int pointIdx1 = g_planes[i][0];
			int pointIdx2 = g_planes[i][1];
			int pointIdx3 = g_planes[i][2];

			// compute the plane from the points:
			plane P = _plane(g_points[pointIdx1] ^ g_points[pointIdx2] ^ g_points[pointIdx3]);
			primitives.push_back(unit_r(P));
		}

		// we collect all intersection primitives here (if they are lines):
		std::vector<mv> iPrimitives;

		// draw intersections of primitives:
		glPushMatrix();

		{
			// translate a little bit so intersections are drawn ON TOP of the other primitives
			// This is used instead of using polygon offset)
			vector T = _vector(inverse(g_modelRotor) * 0.01f * e3 * g_modelRotor);
			glTranslatef(T.e1(), T.e2(), T.e3());
		}

		g_drawState.pushDrawModeOff(OD_ORIENTATION);
		g_drawState.pushDrawModeOff(OD_MAGNITUDE);
		glColor3fm(1.0f, 1.0f, 1.0f);
		for (int x = 0; x < 2; x++) { // loop twice (the second loop brings up intersections of intersections)
			for (unsigned int i = 0; i < primitives.size(); i++) {
				for (unsigned int j = i + 1; j < primitives.size(); j++) {
					mv P1, P2;

					// get the primitives such that grade(P1) <= grade(P2)
					if (primitives[i].gu() < primitives[j].gu()) {
						P1 = primitives[i];
						P2 = primitives[j];
					}
					else {
						P2 = primitives[i];
						P1 = primitives[j];
					}

					// make primitive 'snap' to each other
					{
						mv projection = (P1 << inverse(P2)) << P2;

						// check if projection of P1 onto P2 is 'close' to P1
						const float CLOSE = 0.02f;
						if (_Float(norm_e(projection - P1)) < CLOSE) {
							// yes: P1 = projection of P1 onto P2
							P1 = projection;
						}
					}

					// compute 'pseudoscalar' of the space spanned by P1 and P2
					mv I = unit_e(join(P1, P2));

					// compute P1* . P2
					mv intersection = (P1 << inverse(I)) << P2;

					// draw intersection
					applyTransformAndDraw(M, intersection);

					// if intersection is a line, then add to list of new intersection primitives:
					 if (intersection.gu() == GRADE_2)
						iPrimitives.push_back(intersection);
				}
			}
			primitives = iPrimitives;
		}
		g_drawState.popDrawMode();
		g_drawState.popDrawMode();

		// draw (GRAY) lines between mouse and points selected as lines / planes
		{
			std::vector<int> L = g_createLinePtList;
			glColor3f(0.5f, 0.5f, 0.5f);
			for (int x = 0; x < 2; x++) { // first loop: LINES, second loop: PLANES
				if (L.size()) {
					for (unsigned int i = 0; i < L.size(); i++) {
						applyTransformAndDraw(M, g_points[L[i]]);
					}
					glEnd();
				}

				L = g_createPlanePtList;
			}
		}

		glPopMatrix();

		// draw the planes LAST! because they are transparent . . .
		g_drawState.pushDrawModeOff(OD_MAGNITUDE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4fm(0.0f, 0.0f, 1.0f, 0.5f);
		for (unsigned int i = 0; i < g_planes.size(); i++) {
			// compute the plane from the points:
			plane P = _plane(g_points[g_planes[i][0]] ^
				g_points[g_planes[i][1]] ^
				g_points[g_planes[i][2]]);
			applyTransformAndDraw(M, P);
		}
		glDisable(GL_BLEND);
		g_drawState.popDrawMode();

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
		{
			renderBitmapString(20, g_viewportHeight - 20, font, "NOTE: THIS EXAMPLE IS NEARLY IDENTICAL TO EXAMPLE 11.2!");
			renderBitmapString(20, g_viewportHeight - 40, font, "The difference is in the point where transformation get applied to the primitives.");

			char buf[256];
			sprintf(buf, "MODE: %s\n", g_modeName[g_mouseMode]);
			renderBitmapString(20, g_viewportHeight - 60, font, buf);
		}

		renderBitmapString(20, 60, font, "Use the left mouse button to manipulate the scene, and to orbit it.");
		renderBitmapString(20, 40, font, "Use the other mouse buttons to access the popup menu, and select different manipulation modes.");
		renderBitmapString(20, 20, font, "The intersections of the primitives are drawn in white.");
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

void invert4x4Matrix(const float _M[16], float _M_inverse[16]) {
	// use OpenCV to invert matrix:
	CvMat M = cvMat(4, 4, CV_32F, (void*)_M);
	CvMat M_inverse = cvMat(4, 4, CV_32F, (void*)_M_inverse);

	cvInvert(&M, &M_inverse);
}

void addPtToList(std::vector<int> &list, int idx) {
	for (unsigned int i = 0; i < list.size(); i++)
		if (list[i] == idx) return;
	list.push_back(idx);
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
		// create a new point at g_dragDistance from camera
		normalizedPoint pt = _normalizedPoint(vectorAtDepth(g_dragDistance, g_prevMousePos) - e3 * g_dragDistance);

		// get modelview matrix (as used for drawing the scene) from OpenGL:
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -16.0f);
		rotorGLMult(g_modelRotor);
		float modelviewMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
		glPopMatrix();

		// invert matrix, then try again . . .
		float inverseModelviewMatrix[16];
		invert4x4Matrix(modelviewMatrix, inverseModelviewMatrix);

		// use it to initialize an outermorphism; apply it to the point
		omPoint M(inverseModelviewMatrix);
		pt = apply_om(M, pt);

		// add point to list of points:
		g_points.push_back(_normalizedPoint(pt));

		g_dragPoint = (int)g_points.size()-1;

	}
	else if (g_mouseMode == MODE_CREATE_LINES) {
		int ptIdx = pick(x, g_viewportHeight - y, display, &g_dragDistance);
		if (ptIdx >= 0) {
			addPtToList(g_createLinePtList, ptIdx);
			if (g_createLinePtList.size() == 2) {
				g_lines.push_back(g_createLinePtList);
				g_createLinePtList.clear();
			}
		}
		else g_rotateModel = true;
	}
	else if (g_mouseMode == MODE_CREATE_PLANES) {
		int ptIdx = pick(x, g_viewportHeight - y, display, &g_dragDistance);
		if (ptIdx >= 0) {
			addPtToList(g_createPlanePtList, ptIdx);
			if (g_createPlanePtList.size() == 3) {
				g_planes.push_back(g_createPlanePtList);
				g_createPlanePtList.clear();
			}
		}
		else g_rotateModel = true;
	}

	if (g_rotateModel) {
		h3ga::vector mousePos = mousePosToVector(x, y);
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

		g_points[g_dragPoint] =
				_normalizedPoint(g_points[g_dragPoint] + (T ^ (e0 << g_points[g_dragPoint])));
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void PassiveMouseMotion(int x, int y) {
	// remember mouse pos for next motion:
	g_prevMousePos = mousePosToVector(x, y);

	// redraw viewport
	glutPostRedisplay();
}

void menuCallback(int value) {
	g_mouseMode = value;

	g_createLinePtList.clear();
	g_createPlanePtList.clear();

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
	glutPassiveMotionFunc(PassiveMouseMotion);

	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry(g_modeName[MODE_DRAG], MODE_DRAG);
	glutAddMenuEntry(g_modeName[MODE_CREATE_POINTS], MODE_CREATE_POINTS);
	glutAddMenuEntry(g_modeName[MODE_CREATE_LINES], MODE_CREATE_LINES);
	glutAddMenuEntry(g_modeName[MODE_CREATE_PLANES], MODE_CREATE_PLANES);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// create the initial points
	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, -1.0f, 1.0f, 0.0f));
	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, 1.0f, 1.0f, 0.0f));
	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, 1.0f, 0.0f, 0.0f));

	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, 1.0f, 1.0f, 1.0f));
	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, -1.0f, -1.0f, -1.0f));

	// create initial line
	g_lines.push_back(std::vector<int>());
	g_lines[0].push_back(3);
	g_lines[0].push_back(4);

	// create initial plane
	g_planes.push_back(std::vector<int>());
	g_planes[0].push_back(0);
	g_planes[0].push_back(1);
	g_planes[0].push_back(2);


	glutMainLoop();

	return 0;
}
