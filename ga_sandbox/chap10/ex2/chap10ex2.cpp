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

#include <string>

#include <libgasandbox/e2ga.h>
#include <libgasandbox/e2ga_draw.h>
#include <libgasandbox/e2ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>

using namespace e2ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 10, Example 2: Crystallography";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
//int g_GLUTmenu;

// mouse position on last call to MouseButton() / MouseMotion()
e2ga::vector g_prevMousePos;

// when dragging vectors: which one, and at what depth:
float g_dragDistance = -1.0f;
int g_dragObject = -1;


const float VEC_LENGTH = 200.0f;
const int NB_INPUT_VECTORS = 3;
e2ga::vector g_inputVectors[NB_INPUT_VECTORS] = {
	_vector(VEC_LENGTH * e2),
	_vector(VEC_LENGTH * unit_e(e2 + 0.2f * e1)),
	_vector(VEC_LENGTH * unit_e(e2 - 0.2f * e1))
};


e2ga::vector reflectVector(const e2ga::vector &a, const e2ga::vector &x) {
	return _vector(a * x * inverse(a));
}


void display() {
	// initialize array of vectors:
	std::vector<e2ga::vector> V;
	for (int i = 0; i < NB_INPUT_VECTORS; i++) {
		V.push_back(g_inputVectors[i]);
	}

	// repeatedly reflect every vector in every vector (very brute force)
	double tStart = u_timeGet();
	const double NB_VEC_LIMIT = 1000;
	while (V.size() < NB_VEC_LIMIT) {
		unsigned int nbVec = V.size();
		for (unsigned int i = 0; i < nbVec; i++) {
			for (unsigned int j = 0; j < nbVec; j++) {
				if (i != j) {
					e2ga::vector v = reflectVector(V[j], V[i]);
					bool newVector = true;
					for (unsigned int k = 0; k < V.size(); k++) {
						const float CLOSE = 0.001;
						if (_Float(norm_e2(v - V[k])) < CLOSE*CLOSE) {
							newVector = false;
							break;
						}
					}
					if (newVector) {
						V.push_back(v);
						if (V.size() == NB_VEC_LIMIT) {
							i = j = nbVec;
							break;
						}
					}
				}
			}
		}
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	pickLoadMatrix();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef((float)g_viewportWidth/2.0f, (float)g_viewportHeight / 2.0f, 0.0f);

	if (!GLpick::g_pickActive) {
		glColor3f(0.5f, 0.5f, 0.5f);
		glLineWidth(1.0f);
		glBegin(GL_LINES);
		for (unsigned int i = 3; i < V.size(); i++) {
			glVertex2f(0.0f, 0.0f);
			glVertex2f(V[i].e1() , V[i].e2());
		}
		glEnd();
	}

	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	for (unsigned int i = 0; i < NB_INPUT_VECTORS; i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(V[i].e1() , V[i].e2());
		glEnd();
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
		renderBitmapString(20, 60, font, "BLAH.");
		renderBitmapString(20, 40, font, "BLAH.");
		renderBitmapString(20, 20, font, "BLAH.");
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


e2ga::vector vectorAtDepth(double depth, const e2ga::vector &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return e2ga::vector();
	}

	return _vector((depth * (double)v2d.e1() * GLpick::g_frustumWidth) / (g_viewportWidth * GLpick::g_frustumNear) * e1 +
		(depth * (double)v2d.e2() * GLpick::g_frustumHeight) / (g_viewportHeight * GLpick::g_frustumNear) * e2);
}


e2ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return e2ga::_vector((float)x * e2ga::e1 - (float)y * e2ga::e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_prevMousePos = mousePosToVector(x, y);
	g_dragObject = pick(x, g_viewportHeight - y, display, &g_dragDistance);
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	e2ga::vector mousePos = mousePosToVector(x, y);
	e2ga::vector motion = _vector(mousePos - g_prevMousePos);
	if (g_dragObject >= 0) {
		g_inputVectors[g_dragObject] += motion;
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void menuCallback(int value) {
	// redraw viewport
	glutPostRedisplay();
}

int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e2ga::g2Profiling::init();

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

/*	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry("vector mode", 1);
	glutAddMenuEntry("bivector mode", 3);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);*/


	glutMainLoop();

	return 0;
}
