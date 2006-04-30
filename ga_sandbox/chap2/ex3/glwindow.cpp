#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Output.H>
#include <GL/gl.h>
#include <math.h>
#include <time.h>

#include "glwindow.h"
#include "e3ga.h"
#include "fields.h"
#include "hpindex.h"
#include "timing.h"
#include "main.h"

extern void timerCallback(void*);

#ifndef M_PI
#define M_PI 3.14159265358979323846 
#endif
#define U_RAD2DEG( x ) ( (x) * (float)180.0 / (float)M_PI)
#define U_DEG2RAD( x ) ( (x) * (float)M_PI / (float)180.0)

glwindow::glwindow(int X, int Y, int W, int H, const char *L) : Fl_Gl_Window (X, Y, W, H, L) {
	wX = X; wY = Y; wW = W; wH = H;
	distance =  11.000002f;
	dx = dy = 0;
	rot.setScalar(1.0f); // identity rotation

	listNamesGenerated = 0;
	makeNewList = 1;

}

glwindow::~glwindow() {
}


void glwindow::makeList() {

	// create a cube display list
	e3ga dir[3], base;
	base.null();
	dir[0] = (e3ga)e3ga::e1;
	dir[1] = (e3ga)e3ga::e2;
	dir[2] = (e3ga)e3ga::e3;
	glNewList(cubeListName, GL_COMPILE);
	drawCube(base, dir);
	glEndList();

	// create vector field display list
	glNewList(fieldListName, GL_COMPILE);
	glColor3f(lineColor[0], lineColor[1], lineColor[2]);

	// set up the cube
	base.setVector(-0.5f * g_cubeSize+g_cx, -0.5f * g_cubeSize+g_cy, -0.5f * g_cubeSize+g_cz);
	dir[0] = (e3ga)e3ga::e1 * g_cubeSize;
	dir[1] = (e3ga)e3ga::e2 * g_cubeSize;
	dir[2] = (e3ga)e3ga::e3 * g_cubeSize;

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
		listNamesGenerated = 1;
		makeNewList = 1;
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

	// test for converting a rotor to a OpenGL matrix using outer morphism (should go into seperate function or something)
	e3ga_om om;
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
	glMultMatrixf(rotM);

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
	static e3ga firstRot;
	static int lastx = 0;
	static int lasty = 0;
	float motionX, motionY;
	e3ga rx, ry, rz;
	float ax, ay;

	switch (event) {
	case FL_PUSH:
		firstx = Fl::event_x();
		firsty = Fl::event_y();
		if ( sqrt((wW/2-firstx)*(wW/2-firstx)+
		     (wH/2-firsty)*(wH/2-firsty)) < 0.375*wH ) {
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
			rx = cos(ax) + sin(ax) * ((e3ga)e3ga::e2 << (e3ga)e3ga::I);
			ay = -motionY / 100.0f / 2.0f;
			ry = cos(ay) + sin(ay) * ((e3ga)e3ga::e1 << (e3ga)e3ga::I);
			rot = rx * ry * firstRot;
			} else {
			  motionX = (float)(Fl::event_x() - lastx);
			  motionY = (float)(Fl::event_y() - lasty);

			  if ( lastx > lasty ) {
			    ay = (motionY+motionX) / 100.0f / 2.0f;
			  } else {
			    ay = -(motionY+motionX) / 100.0f / 2.0f;
			  }
			  rz = 1.0f + sin(ay) * ((e3ga)e3ga::e3 << (e3ga)e3ga::I);
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

void glwindow::drawCube(const e3ga &p, float size) {
	const float *pc = p[GRADE1];
//	printf("%f %f %f, Size: %f\n", pc[0], pc[1], pc[2], size);
	glPushMatrix();
	glTranslatef(pc[0], pc[1], pc[2]);
	glScalef(size, size, size);
//	printf("Call list: %d\n", cubeListName);
	glCallList(cubeListName);
	glPopMatrix();
}


void glwindow::drawCube(const e3ga &p, const e3ga dir[3]) {
	float null[3] = {0.0f, 0.0f, 0.0f};
	// todo: replace with display list & scale & stuff...
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	glTranslatef(p[GRADE1][0], p[GRADE1][1], p[GRADE1][2]);
//	printf("Draw cube...\n");
	glBegin(GL_QUADS);

	glNormal3fv((-dir[2])[GRADE1]);
	glVertex3fv(null);
	glVertex3fv(dir[1][GRADE1]);
	glVertex3fv((dir[0] + dir[1])[GRADE1]);
	glVertex3fv(dir[0][GRADE1]);

	glNormal3fv((dir[0])[GRADE1]);
	glVertex3fv(dir[0][GRADE1]);
	glVertex3fv((dir[0] + dir[1])[GRADE1]);
	glVertex3fv((dir[0] + dir[1] + dir[2])[GRADE1]);
	glVertex3fv((dir[0] + dir[2])[GRADE1]);

	glNormal3fv((dir[2])[GRADE1]);
	glVertex3fv((dir[0] + dir[2])[GRADE1]);
	glVertex3fv((dir[0] + dir[1] + dir[2])[GRADE1]);
	glVertex3fv((dir[1] + dir[2])[GRADE1]);
	glVertex3fv(dir[2][GRADE1]);

	glNormal3fv((-dir[0])[GRADE1]);
	glVertex3fv(dir[2][GRADE1]);
	glVertex3fv((dir[1] + dir[2])[GRADE1]);
	glVertex3fv(dir[1][GRADE1]);
	glVertex3fv(null);

	glNormal3fv((-dir[1])[GRADE1]);
	glVertex3fv(null);
	glVertex3fv(dir[0][GRADE1]);
	glVertex3fv((dir[0] + dir[2])[GRADE1]);
	glVertex3fv(dir[2][GRADE1]);

	glNormal3fv((dir[1])[GRADE1]);
	glVertex3fv(dir[1][GRADE1]);
	glVertex3fv((dir[2] + dir[1])[GRADE1]);
	glVertex3fv((dir[0] + dir[1] + dir[2])[GRADE1]);
	glVertex3fv((dir[0] + dir[1])[GRADE1]);

	glEnd();
//	glPopMatrix();
}

// simple test function which draws the direction of the vector field
void glwindow::drawVectorField(const e3ga &base, const e3ga dir[3],
					 int gs, e3ga & (*evalFunc)(const e3ga &p, e3ga &v), float scale, int unit) {
	int i[3];
	e3ga p, v;
	glBegin(GL_LINES);
	for (i[0] = 0; i[0] <= gs; i[0]++)
		for (i[1] = 0; i[1] <= gs; i[1]++)
			for (i[2] = 0; i[2] <= gs; i[2]++) {
				// compute position in field
				p = base + 
					dir[0] * (float)i[0] / (float)gs + 
					dir[1] * (float)i[1] / (float)gs + 
					dir[2] * (float)i[2] / (float)gs;
				// evaluate
				evalFunc(p, v);

				// draw line
				glVertex3fv(p[GRADE1]);
				if ( unit ) {
				glVertex3fv((p + scale * v/sqrt(v.norm_a()))[GRADE1]);
				} else {
				  glVertex3fv((p + scale * v)[GRADE1]);
				}
			}
	glEnd();
}
