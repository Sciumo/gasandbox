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
#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace e3ga;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 4, Example 3: Transforming Normals Vectors";

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
const char *g_modelName = "dodecahedron";

// vertex positions: 3d vectors
std::vector<e3ga::vector> g_vertices3D;
// indices into the g_vertices3D vector:
std::vector<std::vector<int> > g_polygons3D;
// normal of each polygon:
std::vector<e3ga::vector> g_normals3D;
// bivector attitude of each polygon:
std::vector<e3ga::bivector> g_attitude3D;

// draw the 'bad' normals? (red)
bool g_drawBadNormal = true;
// draw the 'good' normals? (green)
bool g_drawGoodNormal = true;

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

// the scaling in the e1-, e2-, e3-directions
mv::Float g_scale[3] = {2.0f, 1.0f, 1.0f};
const mv::Float g_maxScale = 2.5f;

// locations of the ad hoc slider widgets:
int g_scaleSliderLeft[3];
int g_scaleSliderRight[3];
int g_scaleSliderTop[3];
int g_scaleSliderBottom[3];
bool g_scaleSlide[3] = {false, false, false};


void getGLUTmodel3D(const std::string &modelName);

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
	glTranslatef(0.0f, 0.0f, -12.0f);
	rotorGLMult(g_modelRotor);


	// clear viewport
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup other GL stuff
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLineWidth(2.0f);

	// initialize the outermorphism
	om M(
		_vector(g_scale[0] * e1),
		_vector(g_scale[1] * e2),
		_vector(g_scale[2] * e3));

	// render model
	for (unsigned int i = 0; i < g_polygons3D.size(); i++) {
		// set the normal of the polygon (required for correct lighting)
		e3ga::vector normal = _vector(unit_e(dual(apply_om(M, g_attitude3D[i]))));
		glNormal3fv(normal.getC(vector_e1_e2_e3));

		// the approx. center of the polygon
		e3ga::vector center;

		// draw polygon & compute center of polygon
//		glColor3fm(1.0f, 1.0f, 1.0f);
		glColor3fm(0.8f, 0.8f, 0.8f);
		glEnable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		for (unsigned int j = 0; j < g_polygons3D[i].size(); j++) {
			// get vertex, apply transform:
			e3ga::vector v = g_vertices3D[g_polygons3D[i][j]];
			v = _vector(apply_om(M, v));

			center += v; // also compute center

			glVertex3fv(v.getC(vector_e1_e2_e3));
		}
		glEnd();

		center *= 1.0f / (mv::Float)g_polygons3D[i].size();

		// draw normal vector only if 'visible'
		// (this test for visibility is not 100% correct, but good enough for this example)
//		if (_vector(g_modelRotor * g_normals3D[i] * inverse(g_modelRotor)).e3() > 0) {
		glDisable(GL_LIGHTING);

// *!*HTML_TAG*!* normals

		// compute the normals
		e3ga::vector badNormal, goodNormal;

		badNormal = unit_e(apply_om(M, g_normals3D[i]));
		goodNormal = unit_e(dual(apply_om(M, g_attitude3D[i])));


		// get center of polygon + bad / good normal
		e3ga::vector centerPlusBadNormal = _vector(center + 0.4f * badNormal);
		e3ga::vector centerPlusGoodNormal = _vector(center + 0.4f * goodNormal);

		// draw a little 'spike' that signifies the normal
		if (g_drawGoodNormal) {
			glColor3f(0.0f, 1.0f, 0.0f); // green = good normal
			glBegin(GL_LINES);
			glVertex3fv(center.getC(vector_e1_e2_e3));
			glVertex3fv(centerPlusGoodNormal.getC(vector_e1_e2_e3));
			glEnd();
		}
		if (g_drawBadNormal &&
			(_Float(norm_e(centerPlusBadNormal - centerPlusGoodNormal)) > 0.01f)) {
			glColor3f(1.0f, 0.0f, 0.0f); // red = bad normal
			glBegin(GL_LINES);
			glVertex3fv(center.getC(vector_e1_e2_e3));
			glVertex3fv(centerPlusBadNormal.getC(vector_e1_e2_e3));
			glEnd();
		}
	}

	glLineWidth(1.0f);


	// draw the instructions and the sliders:
	{
		glViewport(0, 0, g_viewportWidth, g_viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);

		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.0f, 0.0f);
		void *font = GLUT_BITMAP_HELVETICA_12;
		renderBitmapString(20, 100, font, "-use left mouse button to orbit scene");
		renderBitmapString(20, 80, font, "-use other mouse buttons to select model and normal visibility");
		renderBitmapString(5, 45, font, "Scale e1:");
		renderBitmapString(5, 25, font, "Scale e2:");
		renderBitmapString(5, 5, font, "Scale e3:");


		const int height = 20;
		const int baseY = 40;
		glBegin(GL_QUADS);
		for (int i = 0; i < 3; i++) {
			int left = 65;
			glColor3f(0.8f, 0.8f, 0.8f);
			g_scaleSliderLeft[i] = left;
			g_scaleSliderRight[i] = g_viewportWidth-1;
			g_scaleSliderTop[i] = baseY - i * height + 1 + height - 2;
			g_scaleSliderBottom[i] = baseY - i * height + 1;

			glVertex2i(g_scaleSliderLeft[i], g_scaleSliderBottom[i]);
			glVertex2i(g_scaleSliderRight[i], g_scaleSliderBottom[i]);
			glVertex2i(g_scaleSliderRight[i], g_scaleSliderTop[i]);
			glVertex2i(g_scaleSliderLeft[i], g_scaleSliderTop[i]);

			left++;
			glColor3f(0.2f, 0.2f, 0.8f);
			glVertex2i(left, baseY - i * height + 2);
			glVertex2i(left + (int)(g_scale[i] * (g_viewportWidth-1-left) / g_maxScale), baseY - i * height + 2);
			glVertex2i(left + (int)(g_scale[i] * (g_viewportWidth-1-left) / g_maxScale), baseY - i * height + 2 + height - 4);
			glVertex2i(left, baseY - i * height + 2 + height - 4);
		}
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

e3ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return e3ga::_vector((mv::Float)x * e3ga::e1 - (mv::Float)y * e3ga::e2);
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

		// redraw viewport
		glutPostRedisplay();
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (g_scaleSlide[i]) {
				g_scale[i] = g_maxScale * (mv::Float)(x - g_scaleSliderLeft[i]) / (mv::Float)(g_scaleSliderRight[i] - g_scaleSliderLeft[i]);

				if (g_scale[i] < 0.01f) g_scale[i] = 0.01f;
				if (g_scale[i] > g_maxScale) g_scale[i] = g_maxScale;

				// redraw viewport
				glutPostRedisplay();
			}
		}
	}
}

void MouseButton(int button, int state, int x, int y) {
	g_scaleSlide[0] = g_scaleSlide[1] = g_scaleSlide[2] = false;
	g_rotateModel = false;

	// first check sliders:
	for (int i = 0; i < 3; i++) {
		int _y  = g_viewportHeight - y;
		if ((x >= g_scaleSliderLeft[i]) && (x <= g_scaleSliderRight[i]) &&
			(_y >= g_scaleSliderBottom[i]) && (_y <= g_scaleSliderTop[i])) {
				g_scaleSlide[i] = true;
				MouseMotion(x, y); // to immediately set the slider position
				return;
			}
	}

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


void menuCallback(int value) {
	if (value == -1) {
		g_drawBadNormal = !g_drawBadNormal;
	}
	else if (value == -2) {
		g_drawGoodNormal = !g_drawGoodNormal;
	}
	else {
		g_modelName = g_modelNames[value];
		g_initModelRequired = true;
	}
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
	for (int i = 0; g_modelNames[i]; i++)
		glutAddMenuEntry(g_modelNames[i], i);
	glutAddMenuEntry("Draw bad normals (red)", -1);
	glutAddMenuEntry("Draw good normals (green)", -2);
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
			g_vertices3D.push_back(e3ga::vector(vector_e1_e2_e3, x, y, z));
			idx += 2;
		}

		g_polygons3D.push_back(vtxIdx);
	}

	// compute normals & attitudes of all polygons
	g_attitude3D.resize(g_polygons3D.size());
	g_normals3D.resize(g_polygons3D.size());
	for (unsigned int i = 0; i < g_polygons3D.size(); i++) {
		// get 3D vertices of the polygon:
		const e3ga::vector &v1 = g_vertices3D[g_polygons3D[i][0]];
		const e3ga::vector &v2 = g_vertices3D[g_polygons3D[i][1]];
		const e3ga::vector &v3 = g_vertices3D[g_polygons3D[i][2]];

		// compute bivector attitude & normalize if non-null
		g_attitude3D[i] = (v2 - v1) ^ (v3 - v1);
		if (_Float(norm_e2(g_attitude3D[i]))  != 0.0)
			g_attitude3D[i] = unit_e(g_attitude3D[i]);

		// compute normal vector:
		 g_normals3D[i] = dual(g_attitude3D[i]);
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
