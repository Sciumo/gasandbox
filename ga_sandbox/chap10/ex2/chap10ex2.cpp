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

#include <string>

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_draw.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>

using namespace e3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 10, Example 2: Crystallography";

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
rotor g_modelRotor(_rotor(1.0f));

// when dragging vectors: which one, and at what depth:
float g_dragDistance = -1.0f;
int g_dragObject = -1;

// the 7 crystal configurations
const int CUBIC = 1;
const int HEXAGONAL = 2;
const int TETRAGONAL = 3;
const int ORTHORHOMBRIC = 4;
const int TRICLINIC = 5;
const int MONOCLINIC = 6;
const int TRIGONAL = 7;

/*
These 3 vectors are used as input to generate the operators.
The user can drag them around, and they can also be set to
pre-programmed settings using the popup menu.
*/
const int NB_INPUT_VECTORS = 3;
e3ga::vector g_inputVectors[NB_INPUT_VECTORS] = {
	_vector(e1),
	_vector(e2),
	_vector(e3)
};

// when either of these booleans is true, the operators are initialized in a special way
bool g_ac = false; // op 1 = a c, op 2 = b
bool g_abc = false; // op 1 = a b c

// the draggable point that is used as input for the `drawing the crystal'
e3ga::vector g_point = _vector(e1 + e2 + e3);

std::vector<mv> m_ops;

// *!*HTML_TAG*!* crystal

void recomputeOps() {
	m_ops.clear();

	// initialize array of operators:
	std::vector<mv> &V = m_ops;
	if (g_ac) {
		V.push_back(g_inputVectors[0] ^ g_inputVectors[2]);
		V.push_back(g_inputVectors[1]);
	}
	else if (g_abc) {
		V.push_back(g_inputVectors[0] ^ g_inputVectors[1] ^ g_inputVectors[2]);
	}
	else {
		for (int i = 0; i < NB_INPUT_VECTORS; i++)
			V.push_back(g_inputVectors[i]);
	}

	// repeatedly apply every op to every op (very brute force)
	double tStart = u_timeGet();
	const double NB_VEC_LIMIT = 200; // limit on number of ops (48 is the actual limit, but we use 200 to visualize bad configurations)
	while (V.size() < NB_VEC_LIMIT) {
		unsigned int nbVec = (unsigned int)V.size();
		for (unsigned int i = 0; i < nbVec; i++) {
			for (unsigned int j = 0; j < nbVec; j++) {
				mv v = V[j] * V[i];
				bool newVersor = true;
				for (unsigned int k = 0; k < V.size(); k++) {
					const float CLOSE = 0.001f;
					mv dif = v * inverse(V[k]);
					if (_Float(norm_e(dif - _Float(dif))) < CLOSE) {
						newVersor = false;
						break;
					}
				}
				if (newVersor) {
					V.push_back(v);
					if (V.size() == NB_VEC_LIMIT) {
						i = j = nbVec;
						break;
					}
				}
			}
		}
		// stop when no new vectors have been discovered
		if (nbVec == V.size()) break;
	}
//	printf("%d operators\n", V.size());

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
	glTranslatef(0.0f, 0.0f, -8.0f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glLineWidth(2.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);

	// draw the reflected points
	if (!GLpick::g_pickActive) {
		glColor3f(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < (int)m_ops.size(); i++) {
			glBegin(GL_POINTS);
			glVertex3fv(_vector(gradeInvolution(m_ops[i]) * g_point * inverse(m_ops[i])).getC(vector_e1_e2_e3));
			glEnd();
		}
	}

	// draw the 3 input vectors
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	for (unsigned int i = 0; i < NB_INPUT_VECTORS; i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3fv(g_inputVectors[i].getC(vector_e1_e2_e3));
		glEnd();
	}

	// draw the input points
	glPointSize(5.0);
	if (GLpick::g_pickActive) glLoadName(NB_INPUT_VECTORS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex3fv(g_point.getC(vector_e1_e2_e3));
	glEnd();


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
		renderBitmapString(20, 40, font, "Use the left mouse button to drag the red point and the black lines (or to orbit).");
		renderBitmapString(20, 20, font, "Use the other mouse buttons to access the popup menu which contains pre-programmed configurations.");
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
	return e3ga::_vector((float)x * e1 - (float)y * e2);
}

void MouseButton(int button, int state, int x, int y) {
	if (state == GLUT_UP) return;
	g_rotateModel = false;
	g_prevMousePos = mousePosToVector(x, y);
	g_dragObject = pick(x, g_viewportHeight - y, display, &g_dragDistance);
	//printf("Drag %d, %f\n", g_dragObject, g_dragDistance);
	if (g_dragObject < 0) {
		e3ga::vector mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}
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
	else if (g_dragObject >= 0) {
		// add motion to vector:
		e3ga::vector T = vectorAtDepth(g_dragDistance, motion);
		T = _vector(inverse(g_modelRotor) * T * g_modelRotor);
		if (g_dragObject == NB_INPUT_VECTORS) g_point += T;
		else {
			g_inputVectors[g_dragObject] += T;
			recomputeOps();
		}
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void menuCallback(int value) {
	g_ac = g_abc = false;
	switch (value) {
	case 	CUBIC:
		{
			g_inputVectors[0] = _vector(e1);
			g_inputVectors[1] = _vector(unit_e(e1 + e2));
			g_inputVectors[2] = _vector(unit_e(e2 + e3));
		}
		break;
	case HEXAGONAL:
		{
			g_inputVectors[0] = _vector(e1);
			g_inputVectors[1] = _vector(e1 * exp(e1 ^ e2 * ((float)M_PI / 6.0f)));
			g_inputVectors[2] = _vector(e3);
		}
		break;
	case TETRAGONAL:
		{
			g_inputVectors[0] = _vector(e1);
			g_inputVectors[1] = _vector(e1 * exp(e1 ^ e2 * ((float)M_PI / 4.0f)));
			g_inputVectors[2] = _vector(e3);
		}
		break;
	case ORTHORHOMBRIC:
		{
			g_inputVectors[0] = _vector(e1);
			g_inputVectors[1] = _vector(e2);
			g_inputVectors[2] = _vector(e3);
		}
		break;
	case TRIGONAL:
		{
			g_ac = true;
			g_inputVectors[0] = _vector(e1);
			g_inputVectors[1] = _vector(g_inputVectors[0] * exp((e1^e2) * ((float)M_PI / 6.0f)));
			g_inputVectors[2] = _vector(unit_e(e1 + e3));
		}
		break;
	case MONOCLINIC:
		{
			g_ac = true;
			g_inputVectors[0] = _vector(e1);
			g_inputVectors[1] = _vector(e2);
			g_inputVectors[2] = _vector(unit_e(e3 + 3.0f * e1));
		}
		break;
	case TRICLINIC:
		{
			g_abc = true;
			g_inputVectors[0] = _vector(e1);
			g_inputVectors[1] = _vector(unit_e(e1 + e2 + e3));
			g_inputVectors[2] = _vector(unit_e(e1 + -4.0f * e2));
		}
		break;

	}
	recomputeOps();

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

	g_GLUTmenu = glutCreateMenu(menuCallback);

	glutAddMenuEntry("Cubic", CUBIC);
	glutAddMenuEntry("Hexagonal", HEXAGONAL);
	glutAddMenuEntry("Tetragonal", TETRAGONAL);
	glutAddMenuEntry("Orthohombric", ORTHORHOMBRIC);
	glutAddMenuEntry("Triclinic", TRICLINIC);
	glutAddMenuEntry("Monoclinic", MONOCLINIC);
	glutAddMenuEntry("Trigonal", TRIGONAL);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	menuCallback(HEXAGONAL);

	glutMainLoop();

	return 0;
}
