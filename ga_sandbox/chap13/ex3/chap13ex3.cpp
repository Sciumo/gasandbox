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

#include <vector>
#include <string>

#include <libgasandbox/common.h>
#include <libgasandbox/c3ga.h>
#include <libgasandbox/c3ga_util.h>
#include <libgasandbox/c3ga_draw.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>


using namespace c3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 13, Example 3: Loading Transformations into OpenGL, Again";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;
// mouse position on last call to MouseButton() / MouseMotion()
c3ga::vectorE3GA g_prevMousePos;
// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// model info:
bool g_initModelRequired = true;
const char *g_modelName = "dodecahedron";

// vertex positions: points
std::vector<c3ga::normalizedPoint> g_vertices3D;
// indices into the g_vertices3D vector:
std::vector<std::vector<int> > g_polygons3D;

c3ga::rotor g_modelRotor(c3ga::_rotor(1.0f));
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

// what point to drag (or -1 for none)
int g_dragPoint = -1;
float g_dragDistance = -1.0f;

#define TOGGLE_GL_GA -1
// toggle to switch between GL and GA applying the transform
bool g_useGL = false;

void getGLUTmodel3D(const std::string &modelName);

// todo: add normals & lighting?
void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	// get model, if required:
	if (g_initModelRequired) {
		g_initModelRequired = false;
		getGLUTmodel3D(g_modelName);
	}

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

	float distance = -20.0f;
	if (g_useGL) {
		// direct OpenGL:
		glTranslatef(0.0f, 0.0f, distance);
		rotor R = g_modelRotor;
		rotorGLMult(R);
	}
	else {
// *!*HTML_TAG*!* glLoadMatrix
		// compose transform through GA:

		// get translator and rotor
		vectorE3GA t = _vectorE3GA(distance * e3);
		normalizedTranslator T = exp(_freeVector(-0.5f * (t ^ ni)));
		rotor &R = g_modelRotor;

		// combine 'T' and 'R' to form translation-rotation versor:
		TRversor TR = _TRversor(T * R);
		TRversor TRi = _TRversor(inverse(TR)); // compute inverse

		// compute images of basis blades e1^ni, e2^ni, e3^ni, no^ni:
		flatPoint imageOfE1NI = _flatPoint(TR * e1ni * TRi);
		flatPoint imageOfE2NI = _flatPoint(TR * e2ni * TRi);
		flatPoint imageOfE3NI = _flatPoint(TR * e3ni * TRi);
		flatPoint imageOfNONI = _flatPoint(TR * noni * TRi);

		// create matrix representation:
		omFlatPoint M(imageOfE1NI, imageOfE2NI, imageOfE3NI, imageOfNONI);

		// load matrix representation into GL:
		glLoadMatrixf(M.m_c);
	}


	// clear viewport
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup other GL stuff
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLineWidth(1.0f);

	glDisable(GL_LIGHTING);
	// render model
	for (unsigned int i = 0; i < g_polygons3D.size(); i++) {
		// draw polygon
		glColor3fm(0.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		for (unsigned int j = 0; j < g_polygons3D[i].size(); j++) {
			// get vertex:
			const normalizedPoint &v = g_vertices3D[g_polygons3D[i][j]];

			glVertex3fv(v.getC(normalizedPoint_e1_e2_e3_ni_nof1_0));
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);

	{
		glViewport(0, 0, g_viewportWidth, g_viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.0f,  0.0f);
		void *font = GLUT_BITMAP_HELVETICA_12;
		renderBitmapString(20, 40, font, "This example demonstrates loading conformal transformations into OpenGL");
		renderBitmapString(20, 20, font, "(see the source code).");
	}

	glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-g_viewportWidth/2, g_viewportWidth - g_viewportWidth/2,
		-g_viewportHeight/2, g_viewportHeight - g_viewportHeight/2,
		-100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// refresh model on next redraw
//	g_initModelRequired = true;

	// redraw viewport
	glutPostRedisplay();
}

c3ga::vectorE3GA mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return c3ga::_vectorE3GA((mv::Float)x * e1 - (mv::Float)y * e2);
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	c3ga::vectorE3GA mousePos = mousePosToVector(x, y);
	c3ga::vectorE3GA motion = _vectorE3GA(mousePos - g_prevMousePos);

	if (g_rotateModel) {
		// update rotor
		if (g_rotateModelOutOfPlane)
			g_modelRotor = _rotor(c3ga::exp(0.005f * (motion ^ e3)) * g_modelRotor);
		else g_modelRotor = _rotor(c3ga::exp(0.00001f * (motion ^ mousePos)) * g_modelRotor);
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	if (button == GLUT_LEFT_BUTTON) {
		g_prevMousePos = mousePosToVector(x, y);

		c3ga::vectorE3GA mousePos = mousePosToVector(x, y);
		g_rotateModel = true;
		if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
			g_rotateModelOutOfPlane = true;
		else g_rotateModelOutOfPlane = false;
	}
}


void menuCallback(int value) {
	if (value < 0) {
		if (value == TOGGLE_GL_GA)
			g_useGL = !g_useGL;
	}
	else {
		g_modelName = g_modelNames[value];
		g_initModelRequired = true;
	}

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


	g_GLUTmenu = glutCreateMenu(menuCallback);
	for (int i = 0; g_modelNames[i]; i++)
		glutAddMenuEntry(g_modelNames[i], i);
	glutAddMenuEntry("Toggle GL/GA", TOGGLE_GL_GA);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

	return 0;
}

void renderModel(const std::string &modelName) {
	// render model
	if (modelName == "teapot")
		glutSolidTeapot(1.0);
	else if (modelName == "cube")
		glutSolidCube(1.0);
	else if (modelName == "sphere")
		glutSolidSphere(1.0, 12, 6);
	else if (modelName == "cone")
		glutSolidCone(1.0, 2.0, 12, 4);
	else if (modelName == "torus")
		glutSolidTorus(0.5, 1.0, 6, 12);
	else if (modelName == "dodecahedron")
		glutSolidDodecahedron();
	else if (modelName == "octahedron")
		glutSolidOctahedron();
	else if (modelName == "tetrahedron")
		glutSolidTetrahedron();
	else if (modelName == "icosahedron")
		glutSolidIcosahedron();
}

void getGLUTmodel3D(const std::string &modelName) {
	// DONT cull faces
	glDisable(GL_CULL_FACE);
	// fill all polygons (otherwise they get turned into LINES
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// setup projection & transform for the model:
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-g_viewportWidth/2, g_viewportWidth - g_viewportWidth/2,
		-g_viewportHeight/2, g_viewportHeight - g_viewportHeight/2,
		-100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);

	// buffer for OpenGL feedback.
	// Format will be:
	// GL_POLYGON_TOKEN
	// n (= 3)
	// vertex 0 x, vertex 0 y
	// vertex 1 x, vertex 1 y
	// vertex 2 x, vertex 2 y
	// GL_POLYGON_TOKEN etc etc
	std::vector<GLfloat> bufferXY(300000); // more than enough for the GLUT primitives
	std::vector<GLfloat> bufferZY(bufferXY.size()); // more than enough for the GLUT primitives

	// switch into feedback mode:
	glFeedbackBuffer((GLsizei)bufferXY.size(), GL_2D, &(bufferXY[0]));
	glRenderMode(GL_FEEDBACK);
	renderModel(modelName);
	int nbFeedbackXY = glRenderMode(GL_RENDER);

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // rotate 90 degrees to get a different viewport
	glFeedbackBuffer((GLsizei)bufferZY.size(), GL_2D, &(bufferZY[0]));
	glRenderMode(GL_FEEDBACK);
	renderModel(modelName);
	int nbFeedbackZY = glRenderMode(GL_RENDER);

	// parse the buffer:
	g_polygons3D.clear();
	g_vertices3D.clear();

	if (nbFeedbackZY != nbFeedbackXY) {
		printf("Error extracting model from GLUT!\n");
		return;
	}


	int idx = 0;
	while (idx < nbFeedbackXY) {
		// check for polygon:
		if (bufferXY[idx] != GL_POLYGON_TOKEN) {
			fprintf(stderr, "Error parsing the feedback buffer!");
			break;
		}
		idx++;

		// number of vertices (3)
		int n = (int)bufferXY[idx];
		idx++;
		std::vector<int> vtxIdx(n);

		// get vertices:
		// Maybe todo later: don't duplicate identical vertices  . . .
		for (int i = 0; i < n; i++) {
			vtxIdx[i] = (int)g_vertices3D.size();
			mv::Float x = bufferXY[idx];
			mv::Float y = bufferXY[idx+1];
			mv::Float z = bufferZY[idx+0];
			x -= (mv::Float)g_viewportWidth / 2;
			y -= (mv::Float)g_viewportHeight / 2;
			z -= (mv::Float)g_viewportWidth / 2;
			g_vertices3D.push_back(c3gaPoint(x, y, z));
			idx += 2;
		}

		g_polygons3D.push_back(vtxIdx);
	}

	if (g_prevStatisticsModelName != modelName) {
		printf("Model: %s, #polygons: %d, #vertices: %d\n", modelName.c_str(), g_polygons3D.size(), g_vertices3D.size());
		g_prevStatisticsModelName = modelName;
	}

	// restore transform & projection:
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}
