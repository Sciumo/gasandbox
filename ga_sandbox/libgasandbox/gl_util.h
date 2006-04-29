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

#ifndef _GL_UTIL_H_
#define _GL_UTIL_H_

#ifdef WIN32
#include <windows.h>
#endif WIN32

#include <GL/gl.h>

#include "e3ga.h"

/**
Simulates OpenGL 3D -> 2D viewport transform
'ptWorld' is transformed to 'ptViewport'.

pjMatrix, mvMatrix and viewport should be obtained by
glGetDoublev(GL_VIEWPORT, ...), glGetDoublev(GL_PROJECTION_MATRIX, ...) and
glGetDoublev(GL_MODELVIEW_MATRIX, ...), or can be set to NULL.
When NULL, the function will use glGetDoublev(...) itself, which is inefficient
if you call this function a lot of times.
*/
void viewportCoordinates(const GLdouble ptWorld[3], GLdouble ptViewport[2], 
	const GLdouble *pjMatrix = NULL, const GLdouble *mvMatrix = NULL,
	const GLdouble *viewport = NULL);
void viewportCoordinates(const GLfloat ptWorld[3], GLfloat ptViewport[2], 
	const GLfloat *pjMatrix = NULL, const GLfloat *mvMatrix = NULL,
	const GLfloat *viewport = NULL);

void GLmatrixVectorMul(const GLdouble m[16], const GLdouble v[4], GLdouble r[4]);
void GLmatrixVectorMul(const GLfloat m[16], const GLfloat v[4], GLfloat r[4]);

/// Multiplies the current OpenGL matrix with rotor 'v'
void rotorGLMult(const e3ga::rotor &v);

#endif /* _GL_UTIL_H_ */
