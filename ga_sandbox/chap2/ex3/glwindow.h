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
static GLfloat clearColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
static GLfloat lineColor[] = {0.0f, 0.0f, 0.0f, 1.0f};


#endif /* _GLWINDOW_H_ */
