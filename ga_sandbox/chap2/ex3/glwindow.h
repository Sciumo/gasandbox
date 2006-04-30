#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <FL/Fl_Gl_Window.H>

#include "e3ga.h"

class glwindow : public Fl_Gl_Window {
	int listNamesGenerated;
	GLuint resultListName, cubeListName, fieldListName, 
	  sphereListName, spherePListName, sphereNListName,
	  circListName, circPListName, circNListName;
	void drawCube(const e3ga &p, const e3ga dir[3]);
	int wX, wY, wW, wH;
public:
	void draw();
	int makeNewList;
	void makeList();
	int handle(int);

	glwindow(int X, int Y, int W, int H, const char *L);
	~glwindow();

	void setupViewport();
	void beginglDraw();
	void endglDraw();

	void drawCube(const e3ga &p, float size);

	// simple test function that draws the direction of the vector field
	void drawVectorField(const e3ga &base, const e3ga dir[3],
						 int gs, e3ga & (*evalFunc)(const e3ga &p, e3ga &v), float scale, int unit);

	float distance,dx,dy;
	e3ga rot;
};
static GLfloat clearColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
static GLfloat lineColor[] = {0.0f, 0.0f, 0.0f, 1.0f};


#endif /* _GLWINDOW_H_ */
