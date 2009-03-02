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

#include <libgasandbox/timing.h>
#include <libgasandbox/gl_util.h>

#include "render.h"
#include "main.h"
#include "hpindex.h"

using namespace e3ga;

GLfloat clearColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lineColor[] = {0.0f, 0.0f, 0.0f, 1.0f};


namespace {
	bool listNamesGenerated = false;;
	GLuint resultListName, cubeListName, fieldListName, 
	  sphereListName, spherePListName, sphereNListName,
	  circListName, circPListName, circNListName;
}
bool g_makeNewList = true;


void drawCube(const vector &p, float size) {
//	printf("%f %f %f, Size: %f\n", pc[0], pc[1], pc[2], size);
	glPushMatrix();
	glTranslatef(p.e1(), p.e2(), p.e3());
	glScalef(size, size, size);
//	printf("Call list: %d\n", cubeListName);
	glCallList(cubeListName);
	glPopMatrix();
}

void drawCube(const vector &p, const vector dir[3]) {
	vector null;
	glBegin(GL_QUADS);

	glNormal3fv(_vector(-dir[2]).getC(vector_e1_e2_e3));
	glVertex3fv(null.getC(vector_e1_e2_e3));
	glVertex3fv(dir[1].getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[1]).getC(vector_e1_e2_e3));
	glVertex3fv(dir[0].getC(vector_e1_e2_e3));

	glNormal3fv(dir[0].getC(vector_e1_e2_e3));
	glVertex3fv(dir[0].getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[1]).getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[1] + dir[2]).getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[2]).getC(vector_e1_e2_e3));

	glNormal3fv(dir[2].getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[2]).getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[1] + dir[2]).getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[1] + dir[2]).getC(vector_e1_e2_e3));
	glVertex3fv(dir[2].getC(vector_e1_e2_e3));

	glNormal3fv(_vector(-dir[0]).getC(vector_e1_e2_e3));
	glVertex3fv(dir[2].getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[1] + dir[2]).getC(vector_e1_e2_e3));
	glVertex3fv(dir[1].getC(vector_e1_e2_e3));
	glVertex3fv(null.getC(vector_e1_e2_e3));

	glNormal3fv(_vector(-dir[1]).getC(vector_e1_e2_e3));
	glVertex3fv(null.getC(vector_e1_e2_e3));
	glVertex3fv(dir[0].getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[2]).getC(vector_e1_e2_e3));
	glVertex3fv(dir[2].getC(vector_e1_e2_e3));

	glNormal3fv(dir[1].getC(vector_e1_e2_e3));
	glVertex3fv(dir[1].getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[2] + dir[1]).getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[1] + dir[2]).getC(vector_e1_e2_e3));
	glVertex3fv(_vector(dir[0] + dir[1]).getC(vector_e1_e2_e3));

	glEnd();
}

// simple test function which draws the direction of the vector field
void drawVectorField(const vector &base, const vector dir[3],
					 int gs, vector & (*evalFunc)(const vector &p, vector &v), float scale, int unit) {
	int i[3];
	vector p, v;
	float igs = 1.0f / gs;
	glBegin(GL_LINES);
	for (i[0] = 0; i[0] <= gs; i[0]++)
		for (i[1] = 0; i[1] <= gs; i[1]++)
			for (i[2] = 0; i[2] <= gs; i[2]++) {
				// compute position in field
				p = _vector(base + 
					dir[0] * (float)i[0] * igs + 
					dir[1] * (float)i[1] * igs + 
					dir[2] * (float)i[2] * igs);
				// evaluate
				evalFunc(p, v);

				// draw line
				glVertex3fv(p.getC(vector_e1_e2_e3));
				if ( unit ) {
					glVertex3fv(_vector(p + scale * unit_e(v)).getC(vector_e1_e2_e3));
				} else {
				  glVertex3fv(_vector(p + scale * v).getC(vector_e1_e2_e3));
				}
			}
	glEnd();
}


void makeList() {

	// create a cube display list
	vector dir[3], base;
	dir[0] = _vector(e1);
	dir[1] = _vector(e2);
	dir[2] = _vector(e3);
	glNewList(cubeListName, GL_COMPILE);
	drawCube(base, dir);
	glEndList();

	// create vector field display list
	glNewList(fieldListName, GL_COMPILE);
	glColor3f(lineColor[0], lineColor[1], lineColor[2]);

	// set up the cube
	base.set(vector_e1_e2_e3, -0.5f * g_cubeSize+g_cx, -0.5f * g_cubeSize+g_cy, -0.5f * g_cubeSize+g_cz);
	dir[0] = _vector(e1 * g_cubeSize);
	dir[1] = _vector(e2 * g_cubeSize);
	dir[2] = _vector(e3 * g_cubeSize);

	// draw it's vector field
	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
	  drawVectorField(base, dir, g_vgs, g_evalFunc, 
			  g_vectorSize*0.05f, g_unitField);
	glEndList();

	glNewList(resultListName, GL_COMPILE);
	// evaluate, draw
	if (g_lighting) {
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	double t = u_timeGet();
	extern int g_refines;
	g_boxes=0; g_refines=0;
	printf("Finding singularities (can take a while). . .\n");
	findSingularities(base, dir, g_gs, g_evalFunc, 0, g_maxDepth);
	g_lastTiming = u_timeGet() - t;
	printf("%f secs\n", g_lastTiming);
//	timerCallback(NULL); // WHAT DID THIS DO???
	glEndList();
	if ( g_Dcube > 0 ) {
	  glNewList(sphereListName, GL_COMPILE);
	  glDisable(GL_NORMALIZE);
	  glDisable(GL_LIGHTING);
	  drawSphere(g_gs, 0);
	  glEndList();

	  glNewList(spherePListName, GL_COMPILE);
	  if (g_lighting) {
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	  }
	  drawSphere(g_gs,1);
	  glEndList();

	  glNewList(sphereNListName, GL_COMPILE);
	  if (g_lighting) {
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	  }
	  drawSphere(g_gs,2);
	  glEndList();



	  glNewList(circListName, GL_COMPILE);
	  glDisable(GL_NORMALIZE);
	  glDisable(GL_LIGHTING);
	  drawCirc(g_gs, 0);
	  glEndList();

	  glNewList(circPListName, GL_COMPILE);
	  if (g_lighting) {
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	  }
	  drawCirc(g_gs,1);
	  glEndList();

	  glNewList(circNListName, GL_COMPILE);
	  if (g_lighting) {
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	  }
	  drawCirc(g_gs,2);
	  glEndList();
	}
}

void drawAll() {
	if (!listNamesGenerated) {
		resultListName = glGenLists(9);
		cubeListName = resultListName + 1;
		fieldListName = resultListName + 2;
		sphereListName = resultListName +3;
		spherePListName = resultListName +4;
		sphereNListName = resultListName +5;
		circListName = resultListName +6;
		circPListName = resultListName +7;
		circNListName = resultListName +8;
		listNamesGenerated = true;
		g_makeNewList = true;
	}
	if (g_makeNewList) {
		makeList();
		g_makeNewList = false;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	if (g_showField) {
	  glCallList(fieldListName);
	}

	if (g_showResult) {
	  glCallList(resultListName);
	}

	if (g_showSphere && g_Dcube>0) {
	  glCallList(sphereListName);
	}
	if (g_showPSphere && g_Dcube>0) {
	  glCallList(spherePListName);
	}
	if (g_showNSphere && g_Dcube>0) {
	  glCallList(sphereNListName);
	}

	if ( g_showCirc && g_Dcube > 0 ) {
	  glCallList(circListName);
	  glCallList(circPListName);
	  glCallList(circNListName);
	}
	glPopMatrix();
}
