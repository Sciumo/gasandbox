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

#include <GL/gl.h>
#include <GL/glut.h>
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
#include <libgasandbox/mv_analyze.h>

using namespace c3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 14, Example 3: Conformal Primitives and Intersections";

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

float g_modelDistance = -16.0f;

const int MODE_DRAG = 0;
const int MODE_CREATE_POINTS = 1;
const int MODE_CREATE_LINES_CIRCLES = 2;
const int MODE_CREATE_PLANES_SPHERES = 3;

const char *g_modeName[] = {
	"Drag red points",
	"Create points (no scene orbit available)",
	"Create lines or circles (select three points)",
	"Create planes or spheres (select four points)",
};


int g_mouseMode = MODE_DRAG;


// what point to drag (or -1 for none)
int g_dragPoint = -1; 
float g_dragDistance = 12.0f;


// the points:
std::vector<point> g_points;

// the lines (triplets of indices into g_points)
std::vector<std::vector<int> > g_lines;

// the planes (quadlets of indices into g_points)
std::vector<std::vector<int> > g_planes;

// used for construction of new lines:
std::vector<int> g_createLinePtList;
// used for construction of new planes:
std::vector<int> g_createPlanePtList;

bool isSelected(int ptIdx) {
	for (unsigned int j = 0; j < g_createLinePtList.size(); j++)
		if (g_createLinePtList[j] == ptIdx) return true;
	for (unsigned int j = 0; j < g_createPlanePtList.size(); j++)
		if (g_createPlanePtList[j] == ptIdx) return true;
	return false;
}

vectorE3GA vectorAtDepth(double depth, const vectorE2GA &v2d);

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
	
	g_drawState.m_pointSize = 0.1f;
	for (unsigned int i = 1; i < g_points.size(); i++) { // start at i = 1 because first point is NI!
		if (GLpick::g_pickActive) glLoadName(i);
	
		// draw 'selected' points in dark grey:
		if (isSelected((int)i)) glColor3fm(0.3f, 0.3f, 0.3f);
		else glColor3fm(1.0f, 0.0f, 0.0f); // red otherwise

		draw(g_points[i]);
	}

	if (GLpick::g_pickActive) glLoadName((GLuint)-1);

	if (!GLpick::g_pickActive) {
		// draw the lines
		g_drawState.pushDrawModeOff(OD_ORIENTATION);
		glColor3fm(0.0f, 1.0f, 0.0f);
		for (unsigned int i = 0; i < g_lines.size(); i++) {
			int pointIdx1 = g_lines[i][0];
			int pointIdx2 = g_lines[i][1];
			int pointIdx3 = g_lines[i][2];

			// compute the line from the points:
			circle C = _circle(g_points[pointIdx1] ^ g_points[pointIdx2] ^ g_points[pointIdx3]);
			// draw it:
			draw(C);

			primitives.push_back(unit_e(C));
		}
		g_drawState.popDrawMode();

		// COMPUTE the planes/spheres (they are drawn last, because they are transparent)
		for (unsigned int i = 0; i < g_planes.size(); i++) {
			int pointIdx1 = g_planes[i][0];
			int pointIdx2 = g_planes[i][1];
			int pointIdx3 = g_planes[i][2];
			int pointIdx4 = g_planes[i][3];

			// compute the plane from the points:
			sphere S = _sphere(g_points[pointIdx1] ^ g_points[pointIdx2] ^ g_points[pointIdx3] ^ g_points[pointIdx4]);

			primitives.push_back(unit_e(S));
		}

		// we collect all intersection primitives here (if they are lines):
		std::vector<mv> iPrimitives;

		// draw intersections of primitives:
		glPushMatrix();

		{
			// translate a little bit so intersections are drawn ON TOP of the other primitives
			// This is used instead of using polygon offset)
			freeVector T = _freeVector(inverse(g_modelRotor) * 0.01f * e3ni * g_modelRotor);
			glTranslatef(T.e1ni(), T.e2ni(), T.e3ni());
		}

		g_drawState.pushDrawModeOff(OD_ORIENTATION);
		g_drawState.pushDrawModeOff(OD_MAGNITUDE);
		glColor3fm(0.8f, 0.8f, 0.8f);
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

					// make primitive 'snap' to each other (this is done in Euclidean metric)
					// keep this? It only works well for flats . . . 
					if (true) {
						mv projection = (P1 << inverse(P2)) << P2;

						// check if projection of P1 onto P2 is 'close' to P1
						const float CLOSE = 0.02f;
						if (_Float(norm_e(projection - P1)) < CLOSE) {
							// yes: P1 = projection of P1 onto P2
							P1 = projection;
						}
					}

					// compute 'pseudoscalar' of the space spanned by P1 and P2
					mv I = I5;
					try {
						I = unit_e(join(P1, P2));
					} catch (const std::string &str) {
						printf("%s\n", str.c_str());
					}

					// NOTE: intersection in Eucliden metric (else it doesn't work for flats, in degenerate cases)
					// compute P1* . P2
					mv intersection = (P1 <<  I) << P2;

					// do not draw 'imaginary' intersections:
					mv_analyze::mvAnalysis A(intersection);
					if (A.isBlade() && (A.bladeClass() == mv_analyze::mvAnalysis::ROUND) && (A.m_sc[0] < 0.0f)) continue;  // A.m_sc[0] is the signed radius
					if (A.isBlade() && (A.bladeClass() == mv_analyze::mvAnalysis::ROUND) && (A.bladeSubclass() == mv_analyze::mvAnalysis::SPHERE)) continue;  // no spheres as intersections!

					// draw intersection
					draw(intersection);

					// if intersection is a line, then add to list of new intersection primitives:
					 if (intersection.gu() == GRADE_2) 
						iPrimitives.push_back(intersection);
				}
			}
			primitives = iPrimitives;
		}
		g_drawState.popDrawMode();
		g_drawState.popDrawMode();

		glPopMatrix();

		// draw the planes LAST! because they are transparent . . . 
		g_drawState.pushDrawModeOff(OD_MAGNITUDE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4fm(0.0f, 0.0f, 1.0f, 0.5f);
		for (unsigned int i = 0; i < g_planes.size(); i++) {
			// compute the plane from the points:
			sphere S = _sphere(g_points[g_planes[i][0]] ^ 
				g_points[g_planes[i][1]] ^ 
				g_points[g_planes[i][2]] ^ 
				g_points[g_planes[i][3]]);
			if (fabs(S.e1e2e3no()) > 0.001) g_drawState.pushDrawModeOff(OD_ORIENTATION);
			draw(S);
			if (fabs(S.e1e2e3no()) > 0.001) g_drawState.popDrawMode();
		}
		glDisable(GL_BLEND);
		g_drawState.popDrawMode();

	}


	glPopMatrix();

	{
		glViewport(0, 0, g_viewportWidth, g_viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		pickLoadMatrix();
		glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.0f, 0.0f);
		void *font = GLUT_BITMAP_HELVETICA_12;

		if (!GLpick::g_pickActive) {
			{
				char buf[256];
				sprintf(buf, "MODE: %s\n", g_modeName[g_mouseMode]);
				renderBitmapString(20, g_viewportHeight - 20, font, buf);
			}

			renderBitmapString(20, 60, font, "Use the left mouse button to manipulate the scene, and to orbit it.");
			renderBitmapString(20, 40, font, "Use the other mouse buttons to access the popup menu, and select different manipulation modes.");
			renderBitmapString(20, 20, font, "The intersections of the primitives are drawn in light grey.");
		}

		{
			if (GLpick::g_pickActive) glLoadName(0);

			char *str = "The point at infinity -> O";

			int w = (int)getBitmapStringWidth(font, str);
			int h = 20;
			int x = g_viewportWidth - 20 - w;
			int y = g_viewportHeight - 20;

			glDisable(GL_CULL_FACE);

			if (isSelected(0)) glColor3f(0.3f, 0.3f, 0.3f);
			else glColor3f(0.8f, 0.8f, 0.8f);
			
			glBegin(GL_QUADS);
			glVertex3i(x-2, y+13,-1);
			glVertex3i(x+w+2, y+13,-1);
			glVertex3i(x+w+2, y+13-h,-1);
			glVertex3i(x-2, y+13-h,-1);
			glEnd();
			glEnable(GL_CULL_FACE);


			glColor3f(1.0f, 0.0f, 0.0f);
			renderBitmapString(x, y, font, str);

			if (GLpick::g_pickActive) glLoadName((GLuint)-1);
		}


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


void addPtToList(std::vector<int> &list, int idx) {
	for (unsigned int i = 0; i < list.size(); i++)
		if (list[i] == idx) return; // do not allow for double entries (because then outer product is always 0)
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
		point pt = _point(c3gaPoint(_vectorE3GA(vectorAtDepth(g_dragDistance, g_prevMousePos) - e3 * g_dragDistance)));

		// get modelview matrix (as used for drawing the scene) from OpenGL:
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, g_modelDistance);
		rotorGLMult(g_modelRotor);
		float modelviewMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
		glPopMatrix();

		// convert modelview matrix to versor:
		bool transpose = true;
		TRversor V = _TRversor(matrix4x4ToVersorPS(modelviewMatrix, transpose));

		// use OpenGL transform to create a point at the right location (`under' the mouse)
		pt = inverse(V) * pt * V;

		// add point to list:
		g_points.push_back(pt); // c3gaPoint(_vectorE3GA(-no << fpt))));

		g_dragPoint = (int)g_points.size()-1;

	}
	else if (g_mouseMode == MODE_CREATE_LINES_CIRCLES) {
		int ptIdx = pick(x, g_viewportHeight - y, display, &g_dragDistance);
		if (ptIdx >= 0) {
			addPtToList(g_createLinePtList, ptIdx);
			if (g_createLinePtList.size() == 3) {
				g_lines.push_back(g_createLinePtList);
				g_createLinePtList.clear();
			}
		}
		else g_rotateModel = true;
	}
	else if (g_mouseMode == MODE_CREATE_PLANES_SPHERES) {
		int ptIdx = pick(x, g_viewportHeight - y, display, &g_dragDistance);
		if (ptIdx >= 0) {
			addPtToList(g_createPlanePtList, ptIdx);
			if (g_createPlanePtList.size() == 4) {
				g_planes.push_back(g_createPlanePtList);
				g_createPlanePtList.clear();
			}
		}
		else g_rotateModel = true;
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

	// redraw viewport
//	glutPostRedisplay();
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
	glutAddMenuEntry(g_modeName[MODE_CREATE_LINES_CIRCLES], MODE_CREATE_LINES_CIRCLES);
	glutAddMenuEntry(g_modeName[MODE_CREATE_PLANES_SPHERES], MODE_CREATE_PLANES_SPHERES);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// create the initial points
	g_points.push_back(_point(ni));

	g_points.push_back(_point(c3gaPoint(1.0f, 1.0f, 0.0f)));
	g_points.push_back(_point(c3gaPoint(-1.0f, 1.0f, 0.0f)));
	g_points.push_back(_point(c3gaPoint(1.0f, 0.0f, 0.0f)));

	g_points.push_back(_point(c3gaPoint(1.0f, 1.0f, 1.0f)));
	g_points.push_back(_point(c3gaPoint(-1.0f, -1.0f, -1.0f)));

	// create initial line
	g_lines.push_back(std::vector<int>());
	g_lines[0].push_back(4);
	g_lines[0].push_back(5);
	g_lines[0].push_back(0); // 0 = ni

	// create initial plane
	g_planes.push_back(std::vector<int>());
	g_planes[0].push_back(1);
	g_planes[0].push_back(2);
	g_planes[0].push_back(3);
	g_planes[0].push_back(0); // 0 = ni


	glutMainLoop();

	return 0;
}
