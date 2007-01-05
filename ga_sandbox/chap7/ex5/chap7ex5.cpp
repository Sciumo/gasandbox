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

#include <libgasandbox/e2ga.h>
#include <libgasandbox/glut_util.h>

using namespace e2ga;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 7, Example 5: Fractals";

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

int g_mouseButton = -1;
e2ga::vector g_position;
mv::Float g_zoom = 0.007f;
int g_maxIter = 30;
e2ga::vector g_c(vector_e1_e2, -0.835f, -0.2321f);

// mouse position on last call to MouseButton() / MouseMotion()
e2ga::vector g_prevMousePos;

// *!*HTML_TAG*!* fractal
void computeFractal(const e2ga::vector &translation, const e2ga::vector &c, mv::Float zoom, int maxIter,
					std::vector<unsigned char> &rgbBuffer, int width, int height) {
	int idx = 0;

	// we use e = e1 ('__e1_ct__' stands for 'e1 constant type')
	__e1_ct__ e;

	// for each pixel in the image, evaluate fractal function:
	for (int imageY = 0; imageY < height; imageY++) {
		for (int imageX = 0; imageX < width; imageX++) {
			float imageXf = (float)(imageX-width/2);
			float imageYf = (float)(imageY-height/2);
			e2ga::vector p(vector_e1_e2, imageXf, imageYf);
			e2ga::vector x = _vector(zoom * p - translation);

			for (int i = 0; i < maxIter; i++) {
				x = _vector(x * e * x + c); // n = 2
		        if (_Float(norm_e2(x)) > 1e4f) break; // 1e4 = 'infinity'
			}

			// convert to grey-scale value:
			float valF = _Float(norm_e(x)) / 10.0f;
			unsigned char val = (valF > 255) ? 255 : (unsigned char)(valF + 0.5f);

			rgbBuffer[idx + 0] = rgbBuffer[idx + 1] = rgbBuffer[idx + 2] = val;

			idx += 3;
		}
	}
}

void display() {
	// setup projection & transform
	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// render fractal:
	int width = g_viewportWidth ^ (g_viewportWidth & 3);
	int height = g_viewportHeight;
	std::vector<unsigned char>buf(width * height * 3);
	computeFractal(g_position, g_c, g_zoom, g_maxIter, buf, width, height);

	glRasterPos2f(0.0f, 0.0f);
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, &buf[0]);


	glColor3f(0.5f, 0.5f, 1.0f);
	void *font = GLUT_BITMAP_HELVETICA_18;
	renderBitmapString(20, 20, font, "Press 1 .. 9 to set number of iterations.");
	renderBitmapString(20, 40, font, "Use mouse buttons to translate, modify and zoom.");

	glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// redraw viewport
	glutPostRedisplay();
}


e2ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return e2ga::_vector((float)x * e2ga::e1 - (float)y * e2ga::e2);
}

void MouseButton(int button, int state, int x, int y) {
	g_mouseButton = button;
	g_prevMousePos = mousePosToVector(x, y);

}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	e2ga::vector mousePos = mousePosToVector(x, y);
	e2ga::vector motion = _vector((mousePos - g_prevMousePos) * (-1.0f / (float)g_viewportWidth));

	if (g_mouseButton == GLUT_LEFT_BUTTON) {
		g_position = _vector(g_position -200.0f * g_zoom * motion);
	}
	else if (g_mouseButton == GLUT_MIDDLE_BUTTON) {
		g_c = _vector(g_c + 1.0f * motion);
	}
	else if (g_mouseButton == GLUT_RIGHT_BUTTON) {
		g_zoom = g_zoom * (1.0 + 0.5 * motion.e2());
	}

	// redraw viewport
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	// set
	if ((key >= '1') && (key <= '9'))
		g_maxIter = 10 * (key - '0');

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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);

	glutMainLoop();

	return 0;
}

