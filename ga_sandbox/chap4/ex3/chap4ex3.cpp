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
#endif WIN32

#include <GL/gl.h>
#include <GL/glut.h>
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
std::vector<vector> g_vertices3D;
// indices into the g_vertices3D vector:
std::vector<std::vector<int> > g_polygons3D;
// normal of each polygon:
std::vector<vector> g_normals3D;
// bivector attitude of each polygon:
std::vector<bivector> g_attitude3D;

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


/*
Maybe animate scene?
Or have 'scretch' bar? Only stretch 'x'

Create OM from strectched vectors

Transform model using OM
Draw normals of polygon

--switch between normal vector and bivector rep.

*/



void getGLUTmodel3D(const std::string &modelName);

void display() {
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


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLineWidth(2.0f);

	
	om M(_vector(3 * e1), _vector(e2), _vector(e3));
	

	// render model
	for (unsigned int i = 0; i < g_polygons3D.size(); i++) {
		vector normal = _vector(unit_e(dual(apply_om(M, g_attitude3D[i]))));
		glNormal3fv(normal.getC(vector_e1_e2_e3));

		// get 3D vertices of the polygon:
		vector v1 = g_vertices3D[g_polygons3D[i][0]];
		vector v2 = g_vertices3D[g_polygons3D[i][1]];
		vector v3 = g_vertices3D[g_polygons3D[i][2]];

		v1 = _vector(apply_om(M, v1));
		v2 = _vector(apply_om(M, v2));
		v3 = _vector(apply_om(M, v3));

		// draw polygon
		glColor3fm(1.0, 1.0, 1.0);
		glEnable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		for (unsigned int j = 0; j < g_polygons3D[i].size(); j++) {
			vector v = g_vertices3D[g_polygons3D[i][j]];
			v = _vector(apply_om(M, v));

			glVertex3fv(v.getC(vector_e1_e2_e3));
		}
		glEnd();

		// draw normal vector only if 'visible'
		// (this test for visibility is not 100% correct, but good enough for this example)
//		if (_vector(g_modelRotor * g_normals3D[i] * inverse(g_modelRotor)).e3() > 0) {
		glDisable(GL_LIGHTING);

			// compute the normals
			vector badNormal, goodNormal;
			
			badNormal = unit_e(apply_om(M, g_normals3D[i]));
			goodNormal = unit_e(dual(apply_om(M, g_attitude3D[i])));

			// get center of polygon
			vector center = _vector(0.3333f * (v1 + v2 + v3));

			// get center of polygon + bad / good normal
			vector centerPlusBadNormal = _vector(center + 0.4f * badNormal);
			vector centerPlusGoodNormal = _vector(center + 0.4f * goodNormal);

			// draw a little 'spike' that signifies the normal
			if (g_drawGoodNormal) {
				glColor3f(0.0f, 1.0f, 0.0f);
				glBegin(GL_LINES);
				glVertex3fv(center.getC(vector_e1_e2_e3));
				glVertex3fv(centerPlusGoodNormal.getC(vector_e1_e2_e3));
				glEnd();
			}
			if (g_drawBadNormal) {
				glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_LINES);
				glVertex3fv(center.getC(vector_e1_e2_e3));
				glVertex3fv(centerPlusBadNormal.getC(vector_e1_e2_e3));
				glEnd();
			}
//		}


	}

	glLineWidth(1.0f);

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
//		g_initModelRequired = true;

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
			float x = bufferXY[idx];
			float y = bufferXY[idx+1];
			float z = bufferZY[idx+0]; 
			x -= g_viewportWidth / 2;
			y -= g_viewportHeight / 2;
			z -= g_viewportWidth / 2;
//			printf("%f %f %f\n", x, y, z);
			g_vertices3D.push_back(vector(vector_e1_e2_e3, x, y, z));
			idx += 2;
		}

		g_polygons3D.push_back(vtxIdx);
	}

	// compute normals & attitudes of all polygons
	g_attitude3D.resize(g_polygons3D.size());
	g_normals3D.resize(g_polygons3D.size());
	for (unsigned int i = 0; i < g_polygons3D.size(); i++) {
		// get 3D vertices of the polygon:
		const vector &v1 = g_vertices3D[g_polygons3D[i][0]];
		const vector &v2 = g_vertices3D[g_polygons3D[i][1]];
		const vector &v3 = g_vertices3D[g_polygons3D[i][2]];

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
