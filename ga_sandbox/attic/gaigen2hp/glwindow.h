#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <FL/Fl_Gl_Window.H>

#include <libgasandbox/e3ga.h>
using namespace e3ga;

class glwindow : public Fl_Gl_Window {
	bool listNamesGenerated;
	GLuint resultListName, cubeListName, fieldListName, 
	  sphereListName, spherePListName, sphereNListName,
	  circListName, circPListName, circNListName;
	void drawCube(const vector &p, const vector dir[3]);
	int wX, wY, wW, wH;
public:
	void draw();
	bool makeNewList;
	void makeList();
	int handle(int);

	glwindow(int X, int Y, int W, int H, const char *L);
	~glwindow();

	void setupViewport();
	void beginglDraw();
	void endglDraw();

	void drawCube(const vector &p, float size);

	// simple test function that draws the direction of the vector field
	void drawVectorField(const vector &base, const vector dir[3],
						 int gs, vector & (*evalFunc)(const vector &p, vector &v), float scale, int unit);

	float distance,dx,dy;
	rotor rot;
};
extern GLfloat clearColor[];
extern GLfloat lineColor[];


#endif /* _GLWINDOW_H_ */
