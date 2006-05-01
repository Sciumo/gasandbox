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

/*
Gaigen 2 HP Index

Detects singularities in vector fields.
(C) 2001-2006 Daniel Fontijne - University of Amsterdam & Stephen Mann - University of Waterloo
Algorithm and original matlab code by Stephen Mann & Alyn Rockwood

*/

#include <stdio.h>
#include <stdlib.h>


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
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace e2ga;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 2, Example 2: Hidden Surface Removal";

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
const char *g_modelName = "sphere";

// vertex positions: 2d vectors
std::vector<vector> g_vertices2D;
// indices into the g_vertices2D vector:
std::vector<std::vector<int> > g_polygons2D;

e3ga::rotor g_modelRotor(1.0f);
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



void getGLUTmodel(const std::string &modelName);



void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get model, if required:
	if (g_initModelRequired) {
		g_initModelRequired = false;
		getGLUTmodel(g_modelName);
	}
	
	glEnable(GL_DEPTH_TEST);
	
	// DONT cull faces (we will do this ourselves!)
	glDisable(GL_CULL_FACE);
	// fill all polygons (otherwise they get turned into LINES
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	bivector B;

	// render model
	for (unsigned int i = 0; i < g_polygons2D.size(); i++) {
		// get 2D vertices of the polygon:
		const vector &v1 = g_vertices2D[g_polygons2D[i][0]];
		const vector &v2 = g_vertices2D[g_polygons2D[i][1]];
		const vector &v3 = g_vertices2D[g_polygons2D[i][2]];
		
		// Exercise: 
		// Insert code to remove back-facing polygons here.
		// You can extract the e1^e2 coordinate of a bivector 'B' using:
		// float c = B.e1e2();
		// ...

// 		solution:		
		//B = (v2 - v1) ^ (v3 - v1);
		//if (B.e1e2() <= 0.0) continue;
		
		// draw polygon
		glBegin(GL_POLYGON);
		for (unsigned int j = 0; j < g_polygons2D[i].size(); j++)
			glVertex2f(
				g_vertices2D[g_polygons2D[i][j]].e1(), 
				g_vertices2D[g_polygons2D[i][j]].e2());
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
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// refresh model on next redraw
	g_initModelRequired = true;
	
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
		g_initModelRequired = true;
		
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
	e2ga::g2Profiling::init();
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
//	glutAttachMenu(GLUT_LEFT_BUTTON);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	

	glutMainLoop();
	
	return 0;	
}

void getGLUTmodel(const std::string &modelName) {
	// DONT cull faces (we will do this ourselves!)
	glDisable(GL_CULL_FACE);
	// fill all polygons (otherwise they get turned into LINES
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	// setup projection & transform for the model:
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	const float screenWidth = 1600.0f;
	glFrustum(
		-(float)g_viewportWidth / screenWidth, (float)g_viewportWidth / screenWidth, 
		-(float)g_viewportHeight / screenWidth, (float)g_viewportHeight / screenWidth, 
		1.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0f);
	
	rotorGLMult(g_modelRotor);
	
	
	glColor3f(1.0f, 1.0f, 1.0f);

	// buffer for OpenGL feedback.
	// Format will be:
	// GL_POLYGON_TOKEN
	// n (= 3)
	// vertex 0 x, vertex 0 y
	// vertex 1 x, vertex 1 y
	// vertex 2 x, vertex 2 y
	// GL_POLYGON_TOKEN etc etc
	std::vector<GLfloat> buffer(300000); // more than enough for the GLUT primitives
	
	// switch into feedback mode:
	glFeedbackBuffer((GLsizei)buffer.size(), GL_2D, &(buffer[0]));
	glRenderMode(GL_FEEDBACK);
	
	// render model
	if (modelName == "teapot")
		glutSolidTeapot(1.0);
	else if (modelName == "cube")
		glutSolidCube(1.0);
	else if (modelName == "sphere")
		glutSolidSphere(1.0, 16, 8);
	else if (modelName == "cone")
		glutSolidCone(1.0, 2.0, 16, 8);
	else if (modelName == "torus")
		glutSolidTorus(0.5, 1.0, 8, 16);
	else if (modelName == "dodecahedron")
		glutSolidDodecahedron();
	else if (modelName == "octahedron")
		glutSolidOctahedron();
	else if (modelName == "tetrahedron")
		glutSolidTetrahedron();
	else if (modelName == "icosahedron")
		glutSolidIcosahedron();
	
	int nbFeedback = glRenderMode(GL_RENDER);
	
	// parse the buffer:		
	g_polygons2D.clear();
	g_vertices2D.clear();
	
	int idx = 0;
	while (idx < nbFeedback) {
		// check for polygon:
		if (buffer[idx] != GL_POLYGON_TOKEN) {
			fprintf(stderr, "Error parsing the feedback buffer!");
			break;
		}
		idx++;
		
		// number of vertices (3)
		int n = (int)buffer[idx];
		idx++;
		std::vector<int> vtxIdx(n);
		
		// get vertices:
		// Maybe todo later: don't duplicate identical vertices  . . .
		for (int i = 0; i < n; i++) {
			vtxIdx[i] = (int)g_vertices2D.size();
			g_vertices2D.push_back(_vector(buffer[idx] * e1 + buffer[idx+1] * e2));
			idx += 2;
		}
		
		g_polygons2D.push_back(vtxIdx);
	}

	if (g_prevStatisticsModelName != modelName) {
		printf("Model: %s, #polygons: %d, #vertices: %d\n", modelName.c_str(), g_polygons2D.size(), g_vertices2D.size());
		g_prevStatisticsModelName = modelName;
	}
	
	// restore transform & projection:
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}







#ifdef RIEN
#pragma warning(disable : 4312 4311 4244)

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Scroll.H>
#include <FL/fl_file_chooser.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Box.H>

#include <libgasandbox/timing.h>

#include "glwindow.h" // simple OpenGL window using fltk
#include "hpindex.h"
#include "fields.h"

// user interface (ui) stuff
void uif_callBack(Fl_Widget *W, void *Data);

Fl_Menu_Item uif_fieldMenuItem[] = {
	{"constant", 0,  uif_callBack, (void*)const3, 0},
	{"vortex", 0, uif_callBack, (void*)vortex, 0},
	{"point", 0,  uif_callBack, (void*)point3, 0},
	{"line", 0,  uif_callBack, (void*)line3, 0},
	{"line (helix field)", 0,  uif_callBack, (void*)helix3, 0},
	{"circle", 0,  uif_callBack, (void*)circ3, 0},
	{"eight", 0,  uif_callBack, (void*)eight2, 0},
	{"sphere", 0,  uif_callBack, (void*)sphere3, 0},
	{"testFunc3", 0,  uif_callBack, (void*)testFunc3, 0},
	{"x^3*y^3*z^2", 0, uif_callBack, (void*)testFunc4, 0},
	{"x^3+y^3+z^2", 0, uif_callBack, (void*)testFunc5, 0},
	{"x^3+y^3+x^2", 0, uif_callBack, (void*)testFunc6, 0},
	{"x^3*y^3", 0, uif_callBack, (void*)testFunc7, 0},
	{"Z^2/(Z+2)/(Z-4/5)", 0, uif_callBack, (void*)testFunc8, 0},
	{"1/Z", 0, uif_callBack, (void*)testFunc9, 0},
	{"x^3+y^3+z^3", 0, uif_callBack, (void*)testFunc10, 0},
	{"x^4+y^4+z^4", 0, uif_callBack, (void*)testFunc11, 0},
	{"(x^2+y^2-z)^2 (cup)", 0, uif_callBack, (void*)testFunc12, 0},
	{"sphere union cyl", 0, uif_callBack, (void*)testFunc13, 0},
	{"sphere int cyl", 0, uif_callBack, (void*)testFunc14, 0},
	{"helix", 0, uif_callBack, (void*)testFunc15, 0},
	{"double line", 0, uif_callBack, (void*)testFunc16, 0},
	{"double point", 0, uif_callBack, (void*)testFunc16a, 0},
	{"x^3/3 - xy^2 + z^2", 0, uif_callBack, (void*)testFunc17, 0},
	{"x^3/3 - xy^2", 0, uif_callBack, (void*)testFunc18, 0},
	{0}
};
Fl_Menu_Button *uif_fieldMenu;
Fl_Output *uif_fieldMenuLabel;
Fl_Value_Slider *ui_depthSlider;
Fl_Value_Slider *ui_gsSlider;
Fl_Value_Slider *ui_adapSlider;
Fl_Value_Slider *ui_vgsSlider;
Fl_Value_Slider *ui_cubeSizeSlider;
Fl_Value_Slider *ui_vectorSizeSlider;
Fl_Value_Slider *ui_lratioSlider;
Fl_Value_Slider *ui_sratioSlider;
Fl_Value_Slider *ui_lsingSlider;
Fl_Value_Slider *ui_psingSlider;
Fl_Value_Slider *ui_omegaSlider;
Fl_Value_Slider *ui_gammaSlider;
Fl_Value_Slider *ui_RcoreSlider;

Fl_Value_Slider *ui_dxSlider;
Fl_Value_Slider *ui_dySlider;
Fl_Value_Slider *ui_dzSlider;

Fl_Button *ui_exitButton;
Fl_Button *ui_goButton;
Fl_Check_Button *ui_showField, *ui_showOctree, *ui_showResult, *ui_unitField,
  *ui_bottom;
Fl_Check_Button *ui_surfSing, *ui_lineSing;
Fl_Check_Button *ui_falseSurfSing, *ui_falseLineSing;
Fl_Check_Button *ui_lighting;
Fl_Check_Button *ui_sphere;
Fl_Check_Button *ui_psphere;
Fl_Check_Button *ui_nsphere;
Fl_Check_Button *ui_usphere;
Fl_Check_Button *ui_isphere;

Fl_Check_Button *ui_circ;

Fl_Value_Input* ui_cx;
Fl_Value_Input* ui_cy;
Fl_Value_Input* ui_cz;
Fl_Value_Input* ui_Dbox;

glwindow *g_GLWindow = NULL;
Fl_Window *g_window;
Fl_Output *g_timingOutput;
Fl_Output *g_hpvalueOutput;
Fl_Output *g_boxesOutput;

// ui controlled globals:
float g_cx=0.05f, g_cy=0.05f, g_cz=0.05f;
int g_showField = 0, g_showOctree = 0,  g_showResult = 1, g_unitField=0,
  g_bottom=0;
int g_gs = 8, g_maxDepth = 4;
int g_adap=0;
int g_vgs = 10;
float g_vectorSize = 1.0f;
float g_cubeSize = 2.0f;
float g_lratio = 10.0f;
float g_sratio = 10.0f;
float g_lsing = 0.10f;
float g_psing = 0.10f;
float g_refine = 0.10f;
float g_lrefine = 0.10f;
double g_lastTiming = 0.0f;
int g_boxes=0;
int g_refines=0;
int g_lineSing = 1;
int g_surfSing = 1;
int g_lighting = 1;
int g_falseLineSing = 1; 
int g_falseSurfSing=1;
int g_pushGo = 0;

int g_Dcube = 0;
int g_showSphere=1;
int g_showPSphere=1;
int g_showNSphere=1;
int g_showCirc=0;
int g_USphere=1;
int g_ISphere=0;
float g_hpvalue=0.0;

/* Constants used in vortex field */
float g_omega=1.0;
float g_gamma=1.0;
float g_Rcore=1.0;

float g_dx=0.;
float g_dy=0.;
float g_dz=1.;

int ui_setGo(int state);

// what function are we using currently 
vector & (*g_evalFunc)(const vector &p, vector &v) = (vector & (*)(const vector &p, vector &v))uif_fieldMenuItem[0].user_data_;

void uif_callBack(Fl_Widget *W, void *Data) {
	int i;
	g_evalFunc = (vector & (*)(const vector &p, vector &v))Data;
	i = 0;
	while (uif_fieldMenuItem[i].text) {
		if (uif_fieldMenuItem[i].user_data_ == Data) break;
		i++;
	}
	if (!uif_fieldMenuItem[i].text) {
		printf("uif_callBack(): Could not find function\n");
		uif_fieldMenu->label("error");	
	}
	else uif_fieldMenu->label(uif_fieldMenuItem[i].text);	

	ui_setGo(1);

	uif_fieldMenu->redraw();
}

void ui_callBack(Fl_Widget *W, void *Data) {
	if (W == ui_exitButton) {
		delete g_window;
	} else if (W == ui_goButton) {
		ui_setGo(0);
		g_GLWindow->makeNewList = 1;
		g_GLWindow->redraw();

	} else if (W == ui_depthSlider) {
		ui_setGo(1);
		g_maxDepth = (int)ui_depthSlider->value();
	} else if (W == ui_gsSlider) {
		ui_setGo(1);
		g_gs = (int)ui_gsSlider->value();
	} else if (W == ui_adapSlider) {
		ui_setGo(1);
		g_adap = (int)ui_adapSlider->value();
	} else if (W == ui_vgsSlider) {
		ui_setGo(1);
		g_vgs = (int)ui_vgsSlider->value();
	} else if (W == ui_cubeSizeSlider) {
		ui_setGo(1);
		g_cubeSize = ui_cubeSizeSlider->value();
	} else if (W == ui_vectorSizeSlider) {
		ui_setGo(1);
		g_vectorSize = ui_vectorSizeSlider->value();
	} else if (W == ui_lratioSlider) {
		ui_setGo(1);
		g_lratio = ui_lratioSlider->value();
	} else if (W == ui_sratioSlider) {
		ui_setGo(1);
		g_sratio = ui_sratioSlider->value();

	} else if (W == ui_omegaSlider) {
		ui_setGo(1);
		g_omega = ui_omegaSlider->value();
	} else if (W == ui_gammaSlider) {
		ui_setGo(1);
		g_gamma = ui_gammaSlider->value();
	} else if (W == ui_RcoreSlider) {
		ui_setGo(1);
		g_Rcore = ui_RcoreSlider->value();


		/* dx, dy, dz */
	} else if (W == ui_dxSlider) {
		ui_setGo(1);
		g_dx = ui_dxSlider->value();
	} else if (W == ui_dySlider) {
		ui_setGo(1);
		g_dy = ui_dySlider->value();
	} else if (W == ui_dzSlider) {
		ui_setGo(1);
		g_dz = ui_dzSlider->value();

	} else if (W == ui_lsingSlider) {
		ui_setGo(1);
		g_lsing = ui_lsingSlider->value();
	} else if (W == ui_psingSlider) {
		ui_setGo(1);
		g_psing = ui_psingSlider->value();

	} else if (W == ui_showField) {
		g_showField = (int)ui_showField->value();
		g_GLWindow->redraw();
	} else if (W == ui_showOctree) {
		ui_setGo(1);
		g_showOctree = (int)ui_showOctree->value();
	} else if (W == ui_showResult) {
		g_showResult = (int)ui_showResult->value();
		g_GLWindow->redraw();
	} else if (W == ui_unitField) {
		ui_setGo(1);
		g_unitField = (int)ui_unitField->value();
	} else if (W == ui_bottom) {
		ui_setGo(1);
		g_bottom = (int)ui_bottom->value();

	} else if (W == ui_surfSing) {
		ui_setGo(1);
		g_surfSing = (int)ui_surfSing->value();
	} else if (W == ui_lineSing) {
		ui_setGo(1);
		g_lineSing = (int)ui_lineSing->value();
	} else if (W == ui_falseSurfSing) {
		ui_setGo(1);
		g_falseSurfSing = (int)ui_falseSurfSing->value();
	} else if (W == ui_falseLineSing) {
		ui_setGo(1);
		g_falseLineSing = (int)ui_falseLineSing->value();

	} else if (W == ui_cx) {
	  ui_setGo(1);
	  g_cx = ui_cx->value();
	} else if (W == ui_cy) {
	  ui_setGo(1);
	  g_cy = ui_cy->value();
	} else if (W == ui_cz) {
	  ui_setGo(1);
	  g_cz = ui_cz->value();

	} else if (W == ui_Dbox) {
	  ui_setGo(1);
	  g_Dcube = (int)(ui_Dbox->value());
	  g_hpvalueOutput->value("");

	} else if (W == ui_lighting) {
		ui_setGo(1);
		g_lighting = (int)ui_lighting->value();
	} else if (W == ui_sphere) {
		g_showSphere = (int)ui_sphere->value();
		g_GLWindow->redraw();
	} else if (W == ui_psphere) {
		g_showPSphere = (int)ui_psphere->value();
		g_GLWindow->redraw();
	} else if (W == ui_nsphere) {
		g_showNSphere = (int)ui_nsphere->value();
		g_GLWindow->redraw();
	} else if (W == ui_usphere) {
		ui_setGo(1);
		g_USphere = (int)ui_usphere->value();
		if ( ui_usphere->value() == 1 ) {
		  g_ISphere = 0;
		  ui_isphere->value(g_ISphere);
		}
	} else if (W == ui_isphere) {
		ui_setGo(1);
		g_ISphere = (int)ui_isphere->value();
		if ( ui_isphere->value() == 1 ) {
		  g_USphere = 0;
		  ui_usphere->value(g_USphere);
		}
	} else if (W == ui_circ) {
		g_showCirc = (int)ui_circ->value();
		g_GLWindow->redraw();
	}
	
}


void timerCallback(void *) {
	static char timingText[32];
	sprintf(timingText, "%f", g_lastTiming);
	g_timingOutput->value(timingText);

	static char boxesText[32];
	sprintf(boxesText, "%d", g_boxes);
	g_boxesOutput->value(boxesText);
	fprintf(stderr,"boxes %d, refines %d\n",g_boxes,g_refines);
//	Fl::add_timeout(10.0f / 30.0f, timerCallback);

	if (g_pushGo) {
		if ((int)(u_timeGet() * 2.0) & 1)
			ui_goButton->color(FL_GRAY);
		else ui_goButton->color(FL_RED);
		ui_goButton->redraw();
	}
}

int ui_setGo(int state) {
	if (state) {
		g_pushGo = 1;
	}
	else {
		g_pushGo = 0;
		ui_goButton->color(FL_GRAY);
		ui_goButton->redraw();
	}
	return 0;
}

int main(int argc, char *argv[]) {
	printf("Gaigen HP version 2.0 -- Copyright 2006 University of Amsterdam\n");

	// profiling for Gaigen 2:
	e3ga::g2Profiling::init();

	Fl_Output *label;
	Fl_Output *vlabel;
	Fl_Output *labelBoxes;

	g_window = new Fl_Window(1024,612, "HP Index / Gaigen 2");
	g_window->size_range(1024,612);

	g_GLWindow = new glwindow(0, 0, 512, 512, "g_GLWindow");
	g_GLWindow->mode(FL_RGB | FL_DEPTH | FL_DOUBLE);
	g_window->resizable(g_GLWindow);

	int x, y;
	y = 0;

	x = 512;
	ui_exitButton = new Fl_Button(x, y, 100, 25, "exit");
	ui_exitButton->callback(ui_callBack);

	x += 230;
	ui_goButton = new Fl_Button(x, y, 100, 25, "Go");
	ui_goButton->callback(ui_callBack);

	x += 110;
	uif_fieldMenuLabel = new Fl_Output(x, y, 40, 25);
	uif_fieldMenuLabel->value("field:");
	uif_fieldMenuLabel->color(FL_GRAY);
	uif_fieldMenuLabel->box(FL_FLAT_BOX);
	uif_fieldMenu= new Fl_Menu_Button(x + 35, y, 130, 25, uif_fieldMenuItem[0].text);
	uif_fieldMenu->menu(uif_fieldMenuItem);



	y += 30;
	x = 512;
	label = new Fl_Output(x, y, 50, 25);
	label->value("time: ");
	label->color(FL_GRAY);
	label->box(FL_FLAT_BOX);
	x += 35;
	g_timingOutput = new Fl_Output(x, y, 95, 25);
	g_timingOutput->value("");

	x += 100;
	labelBoxes = new Fl_Output(x,y,60,25);
	labelBoxes->value("Boxes: ");
	labelBoxes->color(FL_GRAY);
	labelBoxes->box(FL_FLAT_BOX);
	x += 50;
	g_boxesOutput = new Fl_Output(x,y, 50, 25);
	g_boxesOutput->value("");

	x += 100;
	ui_Dbox = new Fl_Value_Input(x, y, 50, 25, "DBox");
	ui_Dbox->step(1);
	ui_Dbox->range(0,10000);
	ui_Dbox->callback(ui_callBack);
	ui_Dbox->value(g_Dcube);

	x += 70;
	vlabel = new Fl_Output(x, y, 50, 25);
	vlabel->value("Value: ");
	vlabel->color(FL_GRAY);
	vlabel->box(FL_FLAT_BOX);
	x += 35;
	g_hpvalueOutput = new Fl_Output(x, y, 95, 25);
	g_hpvalueOutput->value("");


	y += 25;
	x = 512;
	ui_showField = new Fl_Check_Button(x, y, 100, 25, "show field");
	ui_showField->callback(ui_callBack);
	ui_showField->value(g_showField);

	x += 100;
	ui_showOctree = new Fl_Check_Button(x, y, 100, 25, "show octree");
	ui_showOctree->callback(ui_callBack);
	ui_showOctree->value(g_showOctree);

	x += 110;
	ui_showResult = new Fl_Check_Button(x, y, 100, 25, "show result");
	ui_showResult->callback(ui_callBack);
	ui_showResult->value(g_showResult);

	x += 100;
	ui_lighting = new Fl_Check_Button(x, y, 100, 25, "lighting");
	ui_lighting->callback(ui_callBack);
	ui_lighting->value(g_lighting);

	x += 80;
	ui_bottom = new Fl_Check_Button(x, y, 100, 25, "show o-all");
	ui_bottom->callback(ui_callBack);
	ui_bottom->value(g_bottom);

	y += 25;

	x = 512;
	ui_sphere = new Fl_Check_Button(x, y, 100, 25, "V sphere");
	ui_sphere->callback(ui_callBack);
	ui_sphere->value(g_showSphere);

	x += 100;
	ui_psphere = new Fl_Check_Button(x, y, 100, 25, "P sphere");
	ui_psphere->callback(ui_callBack);
	ui_psphere->value(g_showPSphere);

	x += 100;
	ui_nsphere = new Fl_Check_Button(x, y, 100, 25, "M sphere");
	ui_nsphere->callback(ui_callBack);
	ui_nsphere->value(g_showNSphere);

	x += 100;
	ui_usphere = new Fl_Check_Button(x, y, 100, 25, "Unit");
	ui_usphere->callback(ui_callBack);
	ui_usphere->value(g_USphere);

	x += 100;
	ui_isphere = new Fl_Check_Button(x, y, 100, 25, "Inscribed");
	ui_isphere->callback(ui_callBack);
	ui_isphere->value(g_ISphere);


	y += 25;
	x = 512;
	ui_circ = new Fl_Check_Button(x, y, 100, 25, "Circ");
	ui_circ->callback(ui_callBack);
	ui_circ->value(g_showCirc);
	y -= 25;


	// Octree Controls
	y += 50;

	Fl_Box* b2 = new Fl_Box(FL_UP_BOX, 512, y, 512, 120, "Octree Controls");
	b2->align(FL_ALIGN_TOP);


	y += 15;

	x = 513;
	ui_cubeSizeSlider = new Fl_Value_Slider(x, y, 115, 25, "main cube size");
	ui_cubeSizeSlider->type(FL_HOR_NICE_SLIDER);
	ui_cubeSizeSlider->range(0.5, 10.0);
	ui_cubeSizeSlider->callback(ui_callBack);
	ui_cubeSizeSlider->value(g_cubeSize);


	x += 130;
	ui_depthSlider = new Fl_Value_Slider(x, y, 115, 25, "max depth");
	ui_depthSlider->step(1);
	ui_depthSlider->type(FL_HOR_NICE_SLIDER);
	ui_depthSlider->range(0, 12);
	ui_depthSlider->callback(ui_callBack);
	ui_depthSlider->value(g_maxDepth);

	x += 130;
	ui_gsSlider = new Fl_Value_Slider(x, y, 115, 25, "grid sample");
	ui_gsSlider->step(1);
	ui_gsSlider->type(FL_HOR_NICE_SLIDER);
	ui_gsSlider->range(1, 20);
	ui_gsSlider->callback(ui_callBack);
	ui_gsSlider->value(g_gs);

	x += 130;
	ui_adapSlider = new Fl_Value_Slider(x, y, 115, 25, "Adaptive depth");
	ui_adapSlider->step(1);
	ui_adapSlider->type(FL_HOR_NICE_SLIDER);
	ui_adapSlider->range(0, 20);
	ui_adapSlider->callback(ui_callBack);
	ui_adapSlider->value(g_adap);


	y += 50;
	Fl_Box* b3 = new Fl_Box(512, y, 512, 20, "Octree Center");
  
	y += 20;
	x = 513+100;
	ui_cx = new Fl_Value_Input(x, y, 100, 25, "x");
	ui_cx->step(0.05);
	ui_cx->range(-5.0,5.0);
	ui_cx->callback(ui_callBack);
	ui_cx->value(g_cx);

	x = 513+220;
	ui_cy = new Fl_Value_Input(x, y, 100, 25, "y");
	ui_cy->step(0.05);
	ui_cy->range(-5.0,5.0);
	ui_cy->callback(ui_callBack);
	ui_cy->value(g_cy);

	x = 513+340;
	ui_cz = new Fl_Value_Input(x, y, 100, 25, "z");
	ui_cz->step(0.05);
	ui_cz->range(-5.0,5.0);
	ui_cz->callback(ui_callBack);
	ui_cz->value(g_cz);


	// Singularity controls
	y += 60;

	Fl_Box* b1 = new Fl_Box(FL_UP_BOX, 512, y, 512, 140, "Singularity Controls");
	b1->align(FL_ALIGN_TOP);

	y += 5;

	x = 513+170;
	ui_lineSing = new Fl_Check_Button(x, y, 100, 25, "line sing");
	ui_lineSing->callback(ui_callBack);
	ui_lineSing->value(g_lineSing);

	x = 513+330;
	ui_surfSing = new Fl_Check_Button(x, y, 100, 25, "surface sing");
	ui_surfSing->callback(ui_callBack);
	ui_surfSing->value(g_surfSing);

	y += 20;
	x = 513+170;
	ui_falseLineSing = new Fl_Check_Button(x, y, 100, 25, "filter line sing");
	ui_falseLineSing->callback(ui_callBack);
	ui_falseLineSing->value(g_falseLineSing);

	x = 513+330;
	ui_falseSurfSing = new Fl_Check_Button(x, y, 100, 25, "filter surface");
	ui_falseSurfSing->callback(ui_callBack);
	ui_falseSurfSing->value(g_falseSurfSing);

	y += 25;
	
	x = 513+160;
	ui_lratioSlider = new Fl_Value_Slider(x, y, 150, 25, "l ratio");
	ui_lratioSlider->type(FL_HOR_NICE_SLIDER);
	ui_lratioSlider->range(1.0, 50.0);
	ui_lratioSlider->callback(ui_callBack);
	ui_lratioSlider->value(g_lratio);


	x = 513+320;
	ui_sratioSlider = new Fl_Value_Slider(x, y, 150, 25, "s ratio");
	ui_sratioSlider->type(FL_HOR_NICE_SLIDER);
	ui_sratioSlider->range(1.0, 50.0);
	ui_sratioSlider->callback(ui_callBack);
	ui_sratioSlider->value(g_sratio);

	y += 45;
	x = 513+5;
	ui_psingSlider = new Fl_Value_Slider(x, y, 150, 25, "point sing");
	ui_psingSlider->type(FL_HOR_NICE_SLIDER);
	ui_psingSlider->range(0.01,1.0);
	ui_psingSlider->callback(ui_callBack);
	ui_psingSlider->value(g_psing);

	x = 513+160;
	ui_lsingSlider = new Fl_Value_Slider(x, y, 150, 25, "line sing");
	ui_lsingSlider->type(FL_HOR_NICE_SLIDER);
	ui_lsingSlider->range(0.01,1.0);
	ui_lsingSlider->callback(ui_callBack);
	ui_lsingSlider->value(g_lsing);



	// Vector Field Controls
	y += 75;

	Fl_Box* b4 = new Fl_Box(FL_UP_BOX, 512, y, 512, 70, "Vector Field Controls");
	b4->align(FL_ALIGN_TOP);


	y += 15;

	x = 513;
	ui_vgsSlider = new Fl_Value_Slider(x, y, 145, 25, "vector sample");
	ui_vgsSlider->step(1);
	ui_vgsSlider->type(FL_HOR_NICE_SLIDER);
	ui_vgsSlider->range(3, 20);
	ui_vgsSlider->callback(ui_callBack);
	ui_vgsSlider->value(g_vgs);

	x += 160;
	ui_vectorSizeSlider = new Fl_Value_Slider(x, y, 145, 25, "length");
	ui_vectorSizeSlider->type(FL_HOR_NICE_SLIDER);
	ui_vectorSizeSlider->range(0.5, 10.0);
	ui_vectorSizeSlider->callback(ui_callBack);
	ui_vectorSizeSlider->value(g_vectorSize);

	x += 160;
	ui_unitField = new Fl_Check_Button(x, y, 100, 25, "unit field");
	ui_unitField->callback(ui_callBack);
	ui_unitField->value(g_unitField);

	// Parameter controls
	y += 75;
	Fl_Box* b5 = new Fl_Box(FL_UP_BOX, 1, y, 1022, 70, "Vortex Parameters");
	b5->align(FL_ALIGN_TOP);


	y += 15;

	x = 10;
	ui_omegaSlider = new Fl_Value_Slider(x, y, 145, 25, "Omega");
	ui_omegaSlider->type(FL_HOR_NICE_SLIDER);
	ui_omegaSlider->range(0.,10.);
	ui_omegaSlider->callback(ui_callBack);
	ui_omegaSlider->value(g_omega);

	x += 160;
	ui_gammaSlider = new Fl_Value_Slider(x, y, 145, 25, "Gamma");
	ui_gammaSlider->type(FL_HOR_NICE_SLIDER);
	ui_gammaSlider->range(0., 10.);
	ui_gammaSlider->callback(ui_callBack);
	ui_gammaSlider->value(g_gamma);

	x += 160;
	ui_RcoreSlider = new Fl_Value_Slider(x, y, 145, 25, "R");
	ui_RcoreSlider->type(FL_HOR_NICE_SLIDER);
	ui_RcoreSlider->range(0.5, 10.0);
	ui_RcoreSlider->callback(ui_callBack);
	ui_RcoreSlider->value(g_Rcore);

	x += 160;
	ui_dxSlider = new Fl_Value_Slider(x, y, 145, 25, "dx");
	ui_dxSlider->type(FL_HOR_NICE_SLIDER);
	ui_dxSlider->range(0.0, 2.0);
	ui_dxSlider->callback(ui_callBack);
	ui_dxSlider->value(g_dx);

	x += 160;
	ui_dySlider = new Fl_Value_Slider(x, y, 145, 25, "dy");
	ui_dySlider->type(FL_HOR_NICE_SLIDER);
	ui_dySlider->range(0.0, 2.0);
	ui_dySlider->callback(ui_callBack);
	ui_dySlider->value(g_dy);

	x += 160;
	ui_dzSlider = new Fl_Value_Slider(x, y, 145, 25, "dz");
	ui_dzSlider->type(FL_HOR_NICE_SLIDER);
	ui_dzSlider->range(0.0, 2.0);
	ui_dzSlider->callback(ui_callBack);
	ui_dzSlider->value(g_dz);

	g_window->end();
	g_window->show(argc, argv);
//	Fl::add_timeout(1.0f, timerCallback);
	Fl::run();

//	e3ga::printProfile();

	//Sleep(10000);

	return 0;
}
#endif
