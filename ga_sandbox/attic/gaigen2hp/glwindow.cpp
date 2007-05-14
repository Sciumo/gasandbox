
#ifdef WIN32
#pragma warning(disable : 4312 4311 4244)
#include <windows.h>
#endif

#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Output.H>
#include <GL/gl.h>
#include <math.h>
#include <time.h>

#include <libgasandbox/common.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/timing.h>

#include "glwindow.h"
#include "fields.h"
#include "hpindex.h"
#include "main.h"

extern void timerCallback(void*);

GLfloat clearColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lineColor[] = {0.0f, 0.0f, 0.0f, 1.0f};

glwindow::glwindow(int X, int Y, int W, int H, const char *L) : Fl_Gl_Window (X, Y, W, H, L) {
	wX = X; wY = Y; wW = W; wH = H;
	distance =  11.000002f;
	dx = dy = 0;
	rot = _rotor(1); // identity rotation

	listNamesGenerated = false;
	makeNewList = true;

}

glwindow::~glwindow() {
}


void glwindow::makeList() {

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
	findSingularities(base, dir, g_gs, g_evalFunc, 0, g_maxDepth);
	g_lastTiming = u_timeGet() - t;
	timerCallback(NULL);
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

void glwindow::draw() {
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
		makeNewList = true;
	}
	if (makeNewList) {
	  extern Fl_Output *g_hpvalueOutput;
		makeList();
		makeNewList = 0;
		static char valueText[32];
		if ( g_Dcube > 0 ) {
		  sprintf(valueText,"%g",g_hpvalue);
		  g_hpvalueOutput->value(valueText);
		} else {
		  g_hpvalueOutput->value("");
		}
		g_hpvalueOutput->redraw();
	}

	g_fieldsCurrentTime  = u_timeGet();

	beginglDraw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(dx, dy, -distance);

	rotorGLMult(rot);
	// test for converting a rotor to a OpenGL matrix using outer morphism (should go into seperate function or something)
	/*e3ga_om om;
	e3ga vi[3], ri = rot.inverse(); // vi = vector images; ri = rot inverse
	vi[0] = rot * e3ga::e1 * ri;
	vi[1] = rot * e3ga::e2 * ri;
	vi[2] = rot * e3ga::e3 * ri;
	om.initOuterMorphism(vi);
	float rotM[16] = {
		om.c[1 + 0 * 3 + 0], om.c[1 + 1 * 3 + 0], om.c[1 + 2 * 3 + 0], 0,
		om.c[1 + 0 * 3 + 1], om.c[1 + 1 * 3 + 1], om.c[1 + 2 * 3 + 1], 0,
		om.c[1 + 0 * 3 + 2], om.c[1 + 1 * 3 + 2], om.c[1 + 2 * 3 + 2], 0,
		0, 0, 0, 1
	};
	glMultMatrixf(rotM);*/
	

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

	endglDraw();
}

void glwindow::beginglDraw() {
	if (!valid()) {
		setupViewport();
	}

#ifndef MESA
	glDrawBuffer(GL_BACK);//GL_FRONT_AND_BACK
#endif // !MESA

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void glwindow::endglDraw() {
#ifndef MESA
	glDrawBuffer(GL_BACK);
#endif // !MESA
}

int glwindow::handle(int event) {
	static int firstx, firsty;
	static int inside; // non-zero if first press inside sphere
	static rotor firstRot;
	static int lastx = 0;
	static int lasty = 0;
	float motionX, motionY;
	rotor rx, ry, rz;
	float ax, ay;

	switch (event) {
	case FL_PUSH:
		firstx = Fl::event_x();
		firsty = Fl::event_y();
		if ( sqrtf((float)((wW/2-firstx)*(wW/2-firstx)+
		     (wH/2-firsty)*(wH/2-firsty))) < 0.375*wH ) {
		  inside = 1;
		} else {
		  inside = 0;
		}
		firstRot = rot;
		return 1;
	case FL_RELEASE:
		return 1;
	case FL_MOVE:
		lastx = Fl::event_x();
		lasty = Fl::event_y();
		return 1;
	case FL_DRAG:
		if (Fl::event_state() & FL_BUTTON1) {
		  motionX = (float)(Fl::event_x() - firstx);
		  motionY = (float)(Fl::event_y() - firsty);
		  //if (fabs(motionX) < 5) motionX = motionX / 5;
		  //else motionX = motionX - 5;
		  //if (fabs(motionY) < 5) motionY = motionY / 5;
		  //else motionY = motionY - 5;

			if ( inside ) {
			// trackball orbiter using GA
			ax = -motionX / 100.0f / 2.0f;
			rx = _rotor(cos(ax) + sin(ax) * (e2 << I3));
			ay = -motionY / 100.0f / 2.0f;
			ry = _rotor(cos(ay) + sin(ay) * (e1 << I3));
			rot = rx * ry * firstRot;
			} else {
			  motionX = (float)(Fl::event_x() - lastx);
			  motionY = (float)(Fl::event_y() - lasty);

			  if ( lastx > lasty ) {
			    ay = (motionY+motionX) / 100.0f / 2.0f;
			  } else {
			    ay = -(motionY+motionX) / 100.0f / 2.0f;
			  }
			  rz = _rotor(1.0f + sin(ay) * (e3 << I3));
			  rot = rz * rot;
			}
		}
		if (Fl::event_state() & FL_BUTTON2) {
		  motionX = (float)(Fl::event_x() - lastx);
		  motionY = (float)(Fl::event_y() - lasty);
		  dx += motionX*distance/1000.0f;
		  dy -= motionY*distance/1000.0f;
		}
		if (Fl::event_state() & FL_BUTTON3) {
		  motionX = (float)(Fl::event_x() - lastx);
		  motionY = (float)(Fl::event_y() - lasty);
			distance += motionY / 10.0f;
			if (distance < 1.0f) distance = 1.0f;
			if (distance > 100.0f) distance = 100.0f;
		}
		lastx = Fl::event_x();
		lasty = Fl::event_y();

		redraw();
		return 1;
	default:
		return Fl_Gl_Window::handle(event);
	}
}

void glwindow::setupViewport() {
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	GLsizei width, height;
	GLdouble aspect;

	width = w();
	height = h();
	if ((width == 0) || (height == 0)) return;

	if (width==0) aspect = (GLdouble)width;
	else aspect = (GLdouble)width/(GLdouble)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, aspect, 0.1, 20.0);
	double ScreenSize = 1200;
	glFrustum((GLdouble)(-width / 2) / ScreenSize, (GLdouble)(width / 2) / ScreenSize, (GLdouble)(-height / 2) / ScreenSize, (GLdouble)(height / 2) / ScreenSize, 1.0, 100.0);
	// projection constant = near * viewportsize/screensize
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set standard opengl stuff
	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_TEST);

	glPointSize(5.0f);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void glwindow::drawCube(const vector &p, float size) {
//	printf("%f %f %f, Size: %f\n", pc[0], pc[1], pc[2], size);
	glPushMatrix();
	glTranslatef(p.e1(), p.e2(), p.e3());
	glScalef(size, size, size);
//	printf("Call list: %d\n", cubeListName);
	glCallList(cubeListName);
	glPopMatrix();
}


void glwindow::drawCube(const vector &p, const vector dir[3]) {
	vector null;
	// todo: replace with display list & scale & stuff...
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	glTranslatef(p[GRADE1][0], p[GRADE1][1], p[GRADE1][2]);
//	printf("Draw cube...\n");
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
//	glPopMatrix();
}

// simple test function which draws the direction of the vector field
void glwindow::drawVectorField(const vector &base, const vector dir[3],
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
