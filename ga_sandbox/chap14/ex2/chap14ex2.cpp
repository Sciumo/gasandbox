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
#include <time.h>


#include <vector>
#include <set>
#include <string>
#include <utility>
#include <utility>
#include <iostream>

#include <libgasandbox/common.h>
#include <libgasandbox/c3ga.h>
#include <libgasandbox/c3ga_draw.h>
#include <libgasandbox/c3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace c3ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 14, Example 2: Drawing Euclid's Elements";

int g_randCol = 0;

// GLUT state information 
int g_viewportWidth = 900;
int g_viewportHeight = 600;

void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//               flats rounds free, tangents
	// grade 2
	// grade 3
	// grade 4
	const int NB_HOR = 4;
	const int NB_VER = 3;

	const int labelHeight = 40;
	const int labelWidth = 80;

	// size of a 'box' where we draw the primitive:
	int boxWidth = (g_viewportWidth - labelWidth) / NB_HOR;
	int boxHeight = (g_viewportHeight - labelHeight) / NB_VER;

	// draw the labels:
	{
		glViewport(0, 0, g_viewportWidth, g_viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_LIGHTING);

		glColor3f(0.0, 0.0, 0.0);
		void *font = GLUT_BITMAP_HELVETICA_18;
	
		const char *LABEL_TYPE_NAMES[NB_HOR] = {
			"flat", "round", "free", "tangent"
		};
		const char *LABEL_GRADE_NAMES[NB_VER] = {
			"grade 2", "grade 3", "grade 4"
		};

		for (int i = 0; i < NB_HOR; i++) {
			const char *str = LABEL_TYPE_NAMES[i];
			int w = (int)getBitmapStringWidth(font, str);
			int x = labelWidth + i * boxWidth + (boxWidth - w) /2;
			renderBitmapString((float)x, (float)(g_viewportHeight - 20), font, str);
		}

		for (int i = 0; i < NB_VER; i++) {
			const char *str = LABEL_GRADE_NAMES[i];
			int w = (int)getBitmapStringWidth(font, str);
			int x = 0 + labelWidth - w - 10;
			int y = g_viewportHeight - (labelHeight + boxHeight * i + (boxHeight) / 2);
			renderBitmapString((float)x, (float)y, font, str);
		}
	}

	g_drawState.m_pointSize	= 0.25f;
	g_drawState.pushDrawModeOff(OD_ORIENTATION);
	g_drawState.pushDrawModeOff(OD_MAGNITUDE);

	// draw each box:
	for (int i = 0; i < NB_HOR; i++) {
		for (int j = 0; j < NB_VER; j++) {
			int x = labelWidth + i * boxWidth;
			int y = g_viewportHeight - (labelHeight + (j+1) * boxHeight);
			glViewport(x, y, boxWidth, boxHeight);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			const float screenWidth = 1000.0f;
			glLoadIdentity();
			GLpick::g_frustumWidth = 2.0 *  (double)boxWidth / screenWidth;
			GLpick::g_frustumHeight = 2.0 *  (double)boxHeight / screenWidth;
			glFrustum(
				-GLpick::g_frustumWidth / 2.0, GLpick::g_frustumWidth / 2.0,
				-GLpick::g_frustumHeight / 2.0, GLpick::g_frustumHeight / 2.0,
				GLpick::g_frustumNear, GLpick::g_frustumFar);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0.0f, 0.0f, -40.0f);

			// draw back plane:
			float r = 0.85f + 0.15f * (float)((g_randCol + i * 13 + j * 7) % 11) / 11.0f;
			glColor3f(r, r, r);
			glDisable(GL_LIGHTING);
			glBegin(GL_QUADS);
			glVertex3f(-100.0f, -100.0f, -50.0f);
			glVertex3f(100.0f, -100.0f, -50.0f);
			glVertex3f(100.0f, 100.0f, -50.0f);
			glVertex3f(-100.0f, 100.0f, -50.0f);
			glEnd();

			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_NORMALIZE);
			glColor3fm(1.0f, 0.0f, 0.0f);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			
			
			mv X; // X is initialized below
			const char *name = "-";
			switch (i) {
				case 0:
					// flat
					switch (j + 2) {
						case 2:
							name = "flat point";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
						case 3:
							name = "line";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
						case 4:
							name = "plane";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
					}
					break;
				case 1:
					// round
					switch (j + 2) {
						case 2:
							name = "point pair";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
						case 3:
							name = "circle";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
						case 4:
							name = "sphere";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
					}
					break;
				case 2:
					// free
					switch (j + 2) {
						case 2:
							name = "free vector";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
						case 3:
							name = "free bivector";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
						case 4:
							name = "free trivector";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
					}
					break;
				case 3:
					// tangent
					switch (j + 2) {
						case 2:
							name = "tangent vector";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
						case 3:
							name = "tangent bivector";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
						case 4:
							name = "tangent trivector";
							X = no; // <- EXERCISE: insert correct primitive here
							break;
					}
					break;
			}
			draw(X);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, boxWidth, 0, boxHeight, -100.0, 100.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glDisable(GL_LIGHTING);

			glColor3f(0.0, 0.0, 0.0);
			void *font = GLUT_BITMAP_HELVETICA_12;
	
			int w = (int)getBitmapStringWidth(font, name);
			renderBitmapString((float)((boxWidth - w)/2), (float)(boxHeight - 20), font, name);

			font = GLUT_BITMAP_HELVETICA_10;
			std::string coordStr = X.toString();
			w = (int)getBitmapStringWidth(font, coordStr.c_str());
			renderBitmapString((float)((boxWidth - w)/2), (float)(boxHeight - 40), font, coordStr.c_str());


		}
	}

	g_drawState.popDrawMode();
	g_drawState.popDrawMode();

	glutSwapBuffers();	
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

}


int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	c3ga::g2Profiling::init();

	 srand(time(NULL));
	 g_randCol = rand();

	// GLUT Window Initialization:
	glutInit (&argc, argv);
	glutInitWindowSize(g_viewportWidth, g_viewportHeight);
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(WINDOW_TITLE);
	
	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
	
	return 0;	
}
