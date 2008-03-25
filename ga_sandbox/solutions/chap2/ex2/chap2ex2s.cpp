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

#include <vector>
#include <string>

#include <libgasandbox/common.h>
#include <libgasandbox/e2ga.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace e2ga;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 2, Example 2: Hidden Surface Removal (SOLUTION)";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;
// mouse position on last call to MouseButton() / MouseMotion()
e3ga::vector g_prevMousePos;
// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// model info:
bool g_initModelRequired = true;
const char *g_modelName = "sphere";

// vertex positions: 2d vectors
std::vector<e2ga::vector> g_vertices2D;
// indices into the g_vertices2D vector:
std::vector<std::vector<int> > g_polygons2D;

e3ga::rotor g_modelRotor(e3ga::_rotor(1.0f));
std::string g_prevStatisticsModelName = "";

// model names:
const char *g_modelNames[] = {
"teapot",
"cube",
"sphere",
"cone",
"torus",
"dodecahedron",
"octahedron",
"tetrahedron",
"icosahedron",
NULL
};



void getGLUTmodel2D(const std::string &modelName);



// *!*HTML_TAG*!* display
// SPOILER WARNING: below is the solution to Chapter 2, exercise 2.
void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get model, if required:
	if (g_initModelRequired) {
		g_initModelRequired = false;
		getGLUTmodel2D(g_modelName);
	}

	glEnable(GL_DEPTH_TEST);

	// DONT cull faces (we will do this ourselves!)
	glDisable(GL_CULL_FACE);
	// fill all polygons (otherwise they get turned into LINES)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor3f(0.0f, 0.0f, 0.0f);

	bivector B;

	// render model
	for (unsigned int i = 0; i < g_polygons2D.size(); i++) {
		// get 2D vertices of the polygon:
		const e2ga::vector &v1 = g_vertices2D[g_polygons2D[i][0]];
		const e2ga::vector &v2 = g_vertices2D[g_polygons2D[i][1]];
		const e2ga::vector &v3 = g_vertices2D[g_polygons2D[i][2]];

		// Exercise:
		// Insert code to remove back-facing polygons here.
		// You can extract the e1^e2 coordinate of a bivector 'B' using:
		// float c = B.e1e2();
		B = (v2 - v1) ^ (v3 - v1);
		if (B.e1e2() <= 0.0) continue;

		// draw polygon
		glBegin(GL_POLYGON);
		for (unsigned int j = 0; j < g_polygons2D[i].size(); j++)
			glVertex2f(
				g_vertices2D[g_polygons2D[i][j]].e1(),
				g_vertices2D[g_polygons2D[i][j]].e2());
		glEnd();
	}

	glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// refresh model on next redraw
	g_initModelRequired = true;

	// redraw viewport
	glutPostRedisplay();
}

e3ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return e3ga::_vector((float)x * e3ga::e1 - (float)y * e3ga::e2);
}


void MouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		e3ga::vector mousePos = mousePosToVector(x, y);
		g_prevMousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}
	else g_rotateModel = false;
}

void MouseMotion(int x, int y) {
	if (g_rotateModel) {
		// get mouse position, motion
		e3ga::vector mousePos = mousePosToVector(x, y);
		e3ga::vector motion = _vector(mousePos - g_prevMousePos);

		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(e3ga::exp(0.005f * (motion ^ e3ga::e3)) * g_modelRotor);
		else g_modelRotor = _rotor(e3ga::exp(0.00001f * (motion ^ mousePos)) * g_modelRotor);


		// remember mouse pos for next motion:
		g_prevMousePos = mousePos;

		// refresh model on next redraw
		g_initModelRequired = true;

		// redraw viewport
		glutPostRedisplay();
	}
}

void Keyboard(unsigned char key, int x, int y) {

}


void menuCallback(int value) {
	g_modelName = g_modelNames[value];
	g_initModelRequired = true;
	glutPostRedisplay();
}


int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e2ga::g2Profiling::init();
	e3ga::g2Profiling::init();

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
	for (int i = 0; g_modelNames[i]; i++)
		glutAddMenuEntry(g_modelNames[i], i);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

	return 0;
}

void getGLUTmodel2D(const std::string &modelName) {
	// DONT cull faces (we will do this ourselves!)
	glDisable(GL_CULL_FACE);
	// fill all polygons (otherwise they get turned into LINES
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// setup projection & transform for the model:
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	const float screenWidth = 1600.0f;
	glFrustum(
		-(float)g_viewportWidth / screenWidth, (float)g_viewportWidth / screenWidth,
		-(float)g_viewportHeight / screenWidth, (float)g_viewportHeight / screenWidth,
		1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0f);

	rotorGLMult(g_modelRotor);


	glColor3f(0.0f, 0.0f, 0.0f);

	// buffer for OpenGL feedback.
	// Format will be:
	// GL_POLYGON_TOKEN
	// n (= 3)
	// vertex 0 x, vertex 0 y
	// vertex 1 x, vertex 1 y
	// vertex 2 x, vertex 2 y
	// GL_POLYGON_TOKEN etc etc
	std::vector<GLfloat> buffer(300000); // more than enough for the GLUT primitives

	// switch into feedback mode:
	glFeedbackBuffer((GLsizei)buffer.size(), GL_2D, &(buffer[0]));
	glRenderMode(GL_FEEDBACK);

	// render model
	if (modelName == "teapot")
		glutSolidTeapot(1.0);
	else if (modelName == "cube")
		glutSolidCube(1.0);
	else if (modelName == "sphere")
		glutSolidSphere(1.0, 16, 8);
	else if (modelName == "cone")
		glutSolidCone(1.0, 2.0, 16, 8);
	else if (modelName == "torus")
		glutSolidTorus(0.5, 1.0, 8, 16);
	else if (modelName == "dodecahedron")
		glutSolidDodecahedron();
	else if (modelName == "octahedron")
		glutSolidOctahedron();
	else if (modelName == "tetrahedron")
		glutSolidTetrahedron();
	else if (modelName == "icosahedron")
		glutSolidIcosahedron();

	int nbFeedback = glRenderMode(GL_RENDER);

	// parse the buffer:
	g_polygons2D.clear();
	g_vertices2D.clear();

	int idx = 0;
	while (idx < nbFeedback) {
		// check for polygon:
		if (buffer[idx] != GL_POLYGON_TOKEN) {
			fprintf(stderr, "Error parsing the feedback buffer!");
			break;
		}
		idx++;

		// number of vertices (3)
		int n = (int)buffer[idx];
		idx++;
		std::vector<int> vtxIdx(n);

		// get vertices:
		// Maybe todo later: don't duplicate identical vertices  . . .
		for (int i = 0; i < n; i++) {
			vtxIdx[i] = (int)g_vertices2D.size();
			g_vertices2D.push_back(_vector(buffer[idx] * e1 + buffer[idx+1] * e2));
			idx += 2;
		}

		g_polygons2D.push_back(vtxIdx);
	}

	if (g_prevStatisticsModelName != modelName) {
		printf("Model: %s, #polygons: %d, #vertices: %d\n", modelName.c_str(), g_polygons2D.size(), g_vertices2D.size());
		g_prevStatisticsModelName = modelName;
	}

	// restore transform & projection:
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}
