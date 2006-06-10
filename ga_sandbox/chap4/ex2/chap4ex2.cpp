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

#include <vector>

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_draw.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>
#include <libgasandbox/timing.h>

using namespace e3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 4, Example 2: Projection, Matrix Representation";

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
e3ga::rotor g_modelRotor(_rotor(1.0f));

// when dragging vectors: which one, and at what depth:
float g_dragDistance = -1.0f;
int g_dragObject = -1;


const int g_nbVectors = 3;

// the three vectors:
e3ga::vector g_vectors[g_nbVectors] = {
	_vector(e1 - e2 - 0.3 * e3),
	_vector(e1 + 0.3 * e2 - 0.1 * e3),
	_vector(e1 + e3)
};

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
	glTranslatef(0.0f, 0.0f, -10.0f);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLineWidth(2.0f);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	rotorGLMult(g_modelRotor);

	// compute bivector (*4 to make it a bit larger):
	bivector B = _bivector(4.0f * g_vectors[0] ^ g_vectors[1]);

	// we need the images of the 3 basis vectors under the projection:
	e3ga::vector imageOfE1 = _vector((e1 << inverse(B)) << B);
	e3ga::vector imageOfE2 = _vector((e2 << inverse(B)) << B);
	e3ga::vector imageOfE3 = _vector((e3 << inverse(B)) << B);
	// initialize the matrix representation
	om M(imageOfE1, imageOfE2, imageOfE3);

	// apply the matrix to the vector:
	e3ga::vector P = _vector(apply_om(M, g_vectors[2]));


	// project g_vectors[2] onto the bivector
	// The symbol '<<' is the left contraction
	//vector P = _vector((g_vectors[2] << inverse(B)) << B);

	// draw vector 1 ^ vector 2
	if (GLpick::g_pickActive) glLoadName((GLuint)-1);
	glColor3fm(0.5f, 0.5f, 0.5f);
	g_drawState.pushDrawModeOff(OD_ORIENTATION);
	draw(B);
	g_drawState.popDrawMode();

	// draw vector 1
	if (GLpick::g_pickActive) glLoadName(1);
	glColor3fm(1.0f, 0.0f, 0.0f);
	draw(g_vectors[0]);

	// draw vector 2
	if (GLpick::g_pickActive) glLoadName(2);
	glColor3fm(0.0f, 1.0f, 0.0f);
	draw(g_vectors[1]);

	// draw vector 3
	if (GLpick::g_pickActive) glLoadName(3);
	glColor3fm(0.0f, 0.0f, 1.0f);
	draw(g_vectors[2]);

	// draw projection of vector 3 onto v
	if (GLpick::g_pickActive) glLoadName((GLuint)-1);
	glColor3fm(0.5f, 0.5f, 0.5f);
	draw(P);

	glDisable(GL_LIGHTING);
	glEnable(GL_LINE_STIPPLE);
	int ST = 0xFF00FF >> ((int)(u_timeGet() * 25) % 16);
	glLineStipple(1, ( GLushort)(ST & 0xFFFF));
	glBegin(GL_LINES);
	glVertex3fv(P.getC(vector_e1_e2_e3));
	glVertex3fv(g_vectors[2].getC(vector_e1_e2_e3));
	glEnd();
	glDisable(GL_LINE_STIPPLE);


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
		renderBitmapString(20, 20, font, "-use mouse buttons to drag (red, green, blue) vectors and to orbit the scene");
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
	return e3ga::_vector((float)x * e3ga::e1 - (float)y * e3ga::e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_rotateModel = false;

	g_prevMousePos = mousePosToVector(x, y);

	GLpick::g_pickWinSize = 1;
	g_dragObject = pick(x, g_viewportHeight - y, display, &g_dragDistance);
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
	else if ((g_dragObject >= 1) && (g_dragObject <= 3)) {
		// add motion to vector:
		e3ga::vector T = vectorAtDepth(g_dragDistance, motion);
		T = _vector(inverse(g_modelRotor) * T * g_modelRotor);
		g_vectors[g_dragObject-1] += T;
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;
		
		// redraw viewport
		glutPostRedisplay();	

}

void Idle() {
	// redraw viewport
	glutPostRedisplay();
}

void benchmarkProjection() {
	// compute bivector (*4 to make it a bit larger):
	bivector B = _bivector(4.0f * g_vectors[0] ^ g_vectors[1]);

	// we need the images of the 3 basis vectors under the projection:
	e3ga::vector imageOfE1 = _vector((e1 << inverse(B)) << B);
	e3ga::vector imageOfE2 = _vector((e2 << inverse(B)) << B);
	e3ga::vector imageOfE3 = _vector((e3 << inverse(B)) << B);
	// initialize the matrix representation
	om M(imageOfE1, imageOfE2, imageOfE3);


	const int nbLoops = 10000000;

	// benchmark 
	double tMatrix = 10e10, tRegularGA = 10e10;
	for (int j = 0; j < 5; j++) { // best of 5
		double tM, tG;
		// matrix:
		tM = u_timeGet();
		e3ga::vector P = g_vectors[2];
		for (int i = 0; i < nbLoops; i++) {
			P = _vector(apply_om(M, P));
		}
		tM = u_timeGet() - tM;

		// regular GA:
		tG = u_timeGet();
		P = g_vectors[2];
		for (int i = 0; i < nbLoops; i++) {
			P = _vector((P << inverse(B)) << B);
		}
		tG = u_timeGet() - tG;

		if (tM < tMatrix) tMatrix = tM;
		if (tG < tRegularGA) tRegularGA = tG;
	}

	printf("%d projections using matrix representation: %f secs\n", nbLoops, tMatrix);
	printf("%d projections using regular GA: %f secs\n", nbLoops, tRegularGA);


}


int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();

	// first do the timing test:
	benchmarkProjection();


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
	glutIdleFunc(Idle);

	glutMainLoop();

	return 0;
}

