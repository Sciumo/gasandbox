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

#include <cv.h>

#include <vector>

#include <libgasandbox/h3ga.h>
#include <libgasandbox/h3ga_draw.h>
#include <libgasandbox/h3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>

using namespace h3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 11, Example 2: Primitives and Intersections";

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
	"Drag points",
	"Create points",
	"Create lines (select two points)",
	"Create planes (select three points)",
};


int g_mouseMode = MODE_DRAG;


// what point to drag (or -1 for none)
int g_dragPoint = -1; 
float g_dragDistance = 12.0f;

// rotation of the model
h3ga::rotor g_modelRotor(_rotor(1.0f));

// the points:
std::vector<normalizedPoint> g_points;

// the lines (pairs of indices into g_points)
std::vector<std::vector<int> > g_lines;

// the planes (triplets of indices into g_points)
std::vector<std::vector<int> > g_planes;

void display() {
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


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);


	// draw the points
	glColor3fm(1.0f, 0.0f, 0.0f);
	g_drawState.m_pointSize = 0.005f;
	for (unsigned int i = 0; i < g_points.size(); i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		draw(g_points[i]);
	}

	if (GLpick::g_pickActive) glLoadName((GLuint)-1);

	if (!GLpick::g_pickActive) {
		// draw the lines
		glColor3fm(0.0f, 1.0f, 0.0f);
		for (unsigned int i = 0; i < g_lines.size(); i++) {
			// compute the line from the points:
			line L = _line(g_points[g_lines[i][0]] ^ g_points[g_lines[i][1]]);
			// draw it:
			draw(L);
		}

		// draw the planes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4fm(0.0f, 0.0f, 1.0f, 0.5f);
		for (unsigned int i = 0; i < g_planes.size(); i++) {
			// compute the plane from the points:
			plane P = _plane(g_points[g_planes[i][0]] ^ 
				g_points[g_planes[i][1]] ^ 
				g_points[g_planes[i][2]]);
			draw(P);
		}
		glDisable(GL_BLEND);

		// compute intersection of lines & lines, lines & planes, planes & planes
		// todo....
		// lines & lines: use meet (large epsilon)
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
		glColor3f(1,1,1);
		void *font = GLUT_BITMAP_HELVETICA_12;
		{
			char buf[256];
			sprintf(buf, "MODE: %s\n", g_modeName[g_mouseMode]);
			renderBitmapString(20, g_viewportHeight - 20, font, buf);
		}

		renderBitmapString(20, 40, font, "Use the left mouse button to manipulate the scene, and to orbit it.");
		renderBitmapString(20, 20, font, "Use the other mouse buttons to access the popup menu, and select different manipulation modes.");
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

void MouseButton(int button, int state, int x, int y) {
	if (state != GLUT_DOWN) return;

	g_rotateModel = false;

	printf("State: %d\n", state);

	g_prevMousePos = mousePosToVector(x, y);

	if (g_mouseMode == MODE_DRAG) {
		g_dragPoint = pick(x, g_viewportHeight - y, display, &g_dragDistance);
		g_rotateModel = (g_dragPoint < 0);
	}
	else if (g_mouseMode == MODE_CREATE_POINTS) {
		// create a new point at g_dragDistance from camera
		normalizedPoint pt = _normalizedPoint(vectorAtDepth(g_dragDistance, g_prevMousePos) - e3 * g_dragDistance);
		printf("Create new point at %s\n", pt.c_str());

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
		{
			// use OpenCV to invert matrix:
			CvMat M = cvMat(4, 4, CV_32F, modelviewMatrix);
			CvMat M_inverse = cvMat(4, 4, CV_32F, inverseModelviewMatrix);

			cvInvert(&M, &M_inverse);
		}

		// use it to initialize an outermorphism; apply it to the point
		omPoint M(inverseModelviewMatrix);
		pt = apply_om(M, pt);

		printf("After transform: %s\n", pt.c_str());

		// add point to list of points:
		g_points.push_back(_normalizedPoint(pt));

		g_dragPoint = (int)g_points.size()-1;

		glutPostRedisplay();
	}

/*const int MODE_CREATE_POINTS = 1;
const int MODE_CREATE_LINES = 2;
const int MODE_CREATE_PLANES = 3;*/

//	printf("Drag point = %d %f\n", g_dragPoint, g_dragDistance);
	if (g_rotateModel) {
		h3ga::vector mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}
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

void Keyboard(unsigned char key, int x, int y) {

}

void menuCallback(int value) {
	g_mouseMode = value;

	// redraw viewport
	glutPostRedisplay();
}

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	h3ga::g2Profiling::init();

	// GLUT Window Initialization:
	glutInit (&argc, argv);
	glutInitWindowSize(g_viewportWidth, g_viewportHeight);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(WINDOW_TITLE);

	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);

	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry(g_modeName[MODE_DRAG], MODE_DRAG);
	glutAddMenuEntry(g_modeName[MODE_CREATE_POINTS], MODE_CREATE_POINTS);
	glutAddMenuEntry(g_modeName[MODE_CREATE_LINES], MODE_CREATE_LINES);
	glutAddMenuEntry(g_modeName[MODE_CREATE_PLANES], MODE_CREATE_PLANES);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// create the initial points
	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, 1.0f, 1.0f, 0.0f));
	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, -1.0f, 1.0f, 0.0f));
	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, 0.0f, 1.0f, 0.0f));

	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, 1.0f, 1.0f, 1.0f));
	g_points.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, -1.0f, -1.0f, -.0f));

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
