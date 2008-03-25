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
#include <libgasandbox/h3ga_util.h>
#include <libgasandbox/h3ga_draw.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

#include <libgasandbox/h3ga.h>

using namespace h3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 11, Example 4: ORTHOGONAL Projection (SOLUTION)";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;
// mouse position on last call to MouseButton() / MouseMotion()
h3ga::vector g_prevMousePos;
// when true, MouseMotion() will rotate the model
bool g_rotateModel = false;
bool g_rotateModelOutOfPlane = false;

// model info:
bool g_initModelRequired = true;
const char *g_modelName = "dodecahedron";

// vertex positions: points
std::vector<h3ga::normalizedPoint> g_vertices3D;
// indices into the g_vertices3D vector:
std::vector<std::vector<int> > g_polygons3D;

h3ga::rotor g_modelRotor(h3ga::_rotor(1.0f));
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

// when true, rays are drawn through frame camera point, vertex & projected vertex
bool g_drawRays = false;


// camera, image plane point 1, image plane point 2, image plane point 3
const int NB_POINTS = 4;
normalizedPoint g_points[NB_POINTS] = {
	_normalizedPoint(6.0f *  e1 + e0),
	_normalizedPoint(4.0f * e1 + e2 + e0),
	_normalizedPoint(4.0f * e1 - e2 + e0),
	_normalizedPoint(4.0f * e1 - e3 + e0)
};

// what point to drag (or -1 for none)
int g_dragPoint = -1;
float g_dragDistance = -1.0f;

const int CAMERA_PT_IDX = 0;
const int IMAGE_PLANE_PT_IDX = 1;




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

	if (false) {
		// use this type of perspective projection to set OpenGL projection:
		// allow toggle for this one?
		h3ga::point camPt = h3ga::_point(h3ga::e0);
		h3ga::point screenPt = h3ga::_point(h3ga::e3 + h3ga::e0);
		h3ga::plane screenPlane = h3ga::_plane(screenPt ^ h3ga::e1 ^ h3ga::e2);
		h3ga::point imageOfE0 = h3ga::_point(h3ga::dual(camPt ^ screenPt) << screenPlane);
		h3ga::point imageOfE1 = h3ga::_point(h3ga::dual(camPt ^ h3ga::e1) << screenPlane);
		h3ga::point imageOfE2 = h3ga::_point(h3ga::dual(camPt ^ h3ga::e2) << screenPlane);
		h3ga::point imageOfE3 = h3ga::_point(h3ga::dual(camPt ^ h3ga::e3) << screenPlane);

		h3ga::omPoint omPt(imageOfE1, imageOfE2, imageOfE3, imageOfE0);
		glLoadMatrixf(omPt.m_c);
	}


	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -20.0f);
	rotorGLMult(g_modelRotor);


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

	// draw camera, image plane points (maybe allow camera to be moved (one point))
	glColor3fm(1.0f, 0.0f, 0.0f);
	g_drawState.m_pointSize = 0.005f;
	for (int i = 0; i < NB_POINTS; i++) {
		glLoadName(i);
		draw(g_points[i]);
	}

	if (!GLpick::g_pickActive) {
		glDisable(GL_LIGHTING);
		// render model
		for (unsigned int i = 0; i < g_polygons3D.size(); i++) {
			// draw polygon & compute center of polygon
			glColor3fm(0.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			for (unsigned int j = 0; j < g_polygons3D[i].size(); j++) {
				// get vertex:
				const normalizedPoint &v = g_vertices3D[g_polygons3D[i][j]];

				glVertex3fv(v.getC(normalizedPoint_e1_e2_e3_e0f1_0));
			}
			glEnd();
		}
		glEnable(GL_LIGHTING);


		// we store the original & projected points here (we not culled), so we can easily draw the rays
		std::vector<normalizedPoint> originalVertices;
		std::vector<point> projectedVertices;

		// draw projection of model
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE); // we do our own back-face culling!
		normalizedPoint cameraPoint = g_points[CAMERA_PT_IDX];
		plane imagePlane = _plane(g_points[IMAGE_PLANE_PT_IDX + 0] ^
			g_points[IMAGE_PLANE_PT_IDX + 1] ^
			g_points[IMAGE_PLANE_PT_IDX + 2]);
		// render model
		for (unsigned int i = 0; i < g_polygons3D.size(); i++) {
			// draw polygon & compute center of polygon
			glColor3fm(0.0, 0.0, 0.0);

			// first compute the projected vertices
			std::vector<point> PV; // PV = projectedVertices
			for (unsigned int j = 0; j < g_polygons3D[i].size(); j++) {
				const normalizedPoint &vertex = g_vertices3D[g_polygons3D[i][j]];
				// project (perspective):
				//point pv = _point(dual(vertex ^ cameraPoint) << imagePlane);

				// project (orthogonal):
				// Form line through cameraPoint, in direction of plane normal
				// Intersect that line with the image plane
				point pv = _point(dual(vertex ^ _vector(dual(imagePlane))) << imagePlane);
				if (pv.e0() < 0.0f) pv = -pv; // I don't understand why this is required (OpenGL doesn't like vertices with negative 'w'?)

				// store
				PV.push_back(pv);
			}

			// perform back-face culling:
			// Compute the plane spanned by the first three vertices,
			// compare it's orientation to the image plane
			mv::Float ori = _Float((PV[0] ^ PV[1] ^ PV[2]) * inverse(imagePlane));

			if (ori > 0.0f) {
				glBegin(GL_POLYGON);
				for (unsigned int j = 0; j < PV.size(); j++) {
					glVertex4fv(PV[j].getC(point_e1_e2_e3_e0));

					if (g_drawRays) {
						const normalizedPoint &vertex = g_vertices3D[g_polygons3D[i][j]];
						originalVertices.push_back(vertex);
						projectedVertices.push_back(PV[j]);
					}
				}
				glEnd();
			}
		}

		if (g_drawRays) {
			// draw rays:
			glColor3f(0.5f, 0.5f, 0.5f);
			for (unsigned int i = 0; i < projectedVertices.size(); i++) {
				glBegin(GL_LINE_STRIP);
				glVertex3fv(cameraPoint.getC(normalizedPoint_e1_e2_e3_e0f1_0));
				glVertex3fv(originalVertices[i].getC(normalizedPoint_e1_e2_e3_e0f1_0));
				glVertex4fv(projectedVertices[i].getC(point_e1_e2_e3_e0));
				glEnd();
			}
		}

		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);

		// draw image plane (transparent?) (maybe allow camera to be moved (one point))
		g_drawState.pushDrawModeOff(OD_MAGNITUDE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4fm(0.5f, 0.5f, 1.0f, 0.5f);
		draw(g_points[IMAGE_PLANE_PT_IDX + 0] ^
			g_points[IMAGE_PLANE_PT_IDX + 1] ^
			g_points[IMAGE_PLANE_PT_IDX + 2]);
		glDisable(GL_BLEND);
		g_drawState.popDrawMode();
	}

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
		renderBitmapString(20, 60, font, "Three red points span the imaging plane and the fourth represents the camera.");
		renderBitmapString(20, 40, font, "Use the left mouse button to drag the red points, and to orbit the scene.");
		renderBitmapString(20, 20, font, "Use the other mouse buttons access the popup menu (to select a different model, and to toggle rays on/off).");
	}

	if (!GLpick::g_pickActive) {
		glutSwapBuffers();
	}
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

h3ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return h3ga::_vector((mv::Float)x * h3ga::e1 - (mv::Float)y * h3ga::e2);
}

h3ga::vector vectorAtDepth(double depth, const h3ga::vector &v2d) {
	if ((GLpick::g_frustumWidth <= 0) || (GLpick::g_frustumHeight <= 0) ||
		(GLpick::g_frustumNear <= 0) || (GLpick::g_frustumFar <= 0)) {
		return h3ga::vector();
	}

	return _vector((depth * (double)v2d.e1() * GLpick::g_frustumWidth) / (g_viewportWidth * GLpick::g_frustumNear) * e1 +
		(depth * (double)v2d.e2() * GLpick::g_frustumHeight) / (g_viewportHeight * GLpick::g_frustumNear) * e2);
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

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	if (button == GLUT_LEFT_BUTTON) {
		g_prevMousePos = mousePosToVector(x, y);

		g_dragPoint = pick(x, g_viewportHeight - y, display, &g_dragDistance);

		if (g_dragPoint < 0) {
			h3ga::vector mousePos = mousePosToVector(x, y);
			g_rotateModel = true;
			if ((_Float(norm_e(mousePos)) / _Float(norm_e(g_viewportWidth * e1 + g_viewportHeight * e2))) < 0.2)
				g_rotateModelOutOfPlane = true;
			else g_rotateModelOutOfPlane = false;
		}
	}
	else g_rotateModel = false;
}


void Keyboard(unsigned char key, int x, int y) {

}


void menuCallback(int value) {
	if (value == -1)
		g_drawRays ^= true;
	else {
		g_modelName = g_modelNames[value];
		g_initModelRequired = true;
	}

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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);


	g_GLUTmenu = glutCreateMenu(menuCallback);
	for (int i = 0; g_modelNames[i]; i++)
		glutAddMenuEntry(g_modelNames[i], i);
	glutAddMenuEntry("Draw rays", -1);
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
			g_vertices3D.push_back(normalizedPoint(normalizedPoint_e1_e2_e3_e0f1_0, x, y, z));
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
