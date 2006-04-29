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
#include <libgasandbox/e2ga.h>
#include <libgasandbox/e2ga_draw.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace e2ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 2, Example 1: Drawing Bivectors";

// GLUT state information 
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

bool g_drawParallelogram = true;


void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	// we store the label positions & text here:
	std::vector<std::string> labelString;
	std::vector<vector> labelPos;
	
	
	// how many bivectors? what spacing between them?:
	const float entryWidth = 2.75f;
	const float entryHeight = 3.5f;
	const int nbBivectorX = 6;
	const int nbBivectorY = 4;
	
	// scale / translate to right transform:
	const float scale = 40.0f;
	glScalef(scale, scale, scale);
	glTranslatef(entryWidth, ((float)nbBivectorY - 0.5f) * entryHeight, 0.0f);
	
	int posX = 0;
	
	vector v1, v2, v1_plus_v2;
	
	bivector B;
	
	for (double a = 0; a < 2 * M_PI - 10e-7; a += 2 * M_PI / (nbBivectorX * nbBivectorY)) {
		// vector 1 is fixed to e1 	
		v1 = e1;
		
		// compute vector 2:
		v2 = cos(a) * e1 + sin(a) * e2;

		// compute the bivector:
		B = v1 ^ v2;

		// draw vector 1, vector 2		
		glColor3f(1.0f, 0.0f, 0.0f);
		draw(v1);
		glColor3f(0.0f, 1.0f, 0.0f);
		draw(v2);
		
		// draw outer product v1^v2:
		glColor3f(0.0f, 0.0f, 1.0f);
		if (!g_drawParallelogram) {
			draw(B);
		}
		else {
			v1_plus_v2 = v1 + v2;
			// draw QUAD with vertices
			// origin  ->  v1  ->  (v1+v2)  ->  v2
			glBegin(GL_QUADS);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(v1.e1(), v1.e2());
			glVertex2f(v1_plus_v2.e1(), v1_plus_v2.e2());
			glVertex2f(v2.e1(), v2.e2());
			glEnd();
		}
		
		
		// store label of bivector:
		{
			labelString.push_back(B.toString());
			GLfloat pos[2];
			viewportCoordinates(e3ga::_vector(0.35f * entryHeight * e3ga::e2).getC(e3ga::vector_e1_e2_e3), pos);
			labelPos.push_back(vector(vector_e1_e2, pos));
		}
		
		// translate to next entry:
		glTranslatef(entryWidth, 0.0f, 0.0f);
		posX++;
		if (posX == nbBivectorX) {
			posX = 0;
			glTranslatef(-(float)nbBivectorX * entryWidth, -entryHeight, 0.0f);
		}
	
	}
		
	glPopMatrix();
	
	// draw the labels:
	glColor3f(0.8, 0.8, 0.8);
	void *font = GLUT_BITMAP_HELVETICA_12;
	for (unsigned int i = 0; i < labelString.size(); i++) {
		float w = getBitmapStringWidth(font, labelString[i].c_str());
		renderBitmapString(labelPos[i].e1() - 0.45f * w, labelPos[i].e2(), font, labelString[i].c_str());
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
}

void MouseButton(int button, int state, int x, int y) {

}

void MouseMotion(int x, int y) {


}

void Keyboard(unsigned char key, int x, int y) {

}

void menuCallback(int value) {
	g_drawParallelogram = value != 0;
}


int main(int argc, char*argv[]) {
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
	glutAddMenuEntry("disc", 0);
	glutAddMenuEntry("parallelogram", 1);
	glutAttachMenu(GLUT_LEFT_BUTTON);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	
	return 0;	
}
