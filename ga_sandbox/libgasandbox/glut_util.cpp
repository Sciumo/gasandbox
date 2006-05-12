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
#endif 

#include <GL/gl.h>
#include <GL/glut.h>

// todo: check out coin3d for the m4 functions SIM_AC_CHECK_OPENGL and such
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
//#include <GLUT/glut.h>



#include "glut_util.h"

// based on LightHouse 3D tutorial code 
void renderSpacedBitmapString(float x, float y, float spacing, void *font, const char *string) {
	const char *c;
	float x1 = x;
	for (c=string; *c != '\0'; c++) {
		glRasterPos2f(x1,y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font,*c) + spacing;
  	}
}

float getSpacedBitmapStringWidth(float spacing, void *font, const char *string){
	const char *c;
	float x1 = 0.0f;
	for (c=string; *c != '\0'; c++) {
		x1 = x1 + glutBitmapWidth(font,*c);
  	}
	return x1 + (float)(c - string - 1) * spacing;
}
