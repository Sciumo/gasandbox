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


#include "gl_util.h"
#include <GL/glut.h>



void viewportCoordinates(const GLdouble ptWorld[3], GLdouble ptViewport[2], 
	const GLdouble *pjMatrix /* = NULL */, const GLdouble *mvMatrix/* = NULL */,
	const GLdouble *viewport /* = NULL */) {
	
	GLdouble _pjMatrix[16];
	GLdouble _mvMatrix[16];
	GLdouble _viewport[4];
	if (pjMatrix == NULL) {
		pjMatrix = _pjMatrix;
		glGetDoublev(GL_PROJECTION_MATRIX, _pjMatrix);
	}
	if (mvMatrix == NULL) {
		mvMatrix = _mvMatrix;
		glGetDoublev(GL_MODELVIEW_MATRIX, _mvMatrix);
	}
	if (viewport == NULL) {
		viewport = _viewport;
		glGetDoublev(GL_VIEWPORT, _viewport);
	}
		
	GLdouble pt1[4], pt2[4];
	pt1[0] = ptWorld[0]; pt1[1] = ptWorld[1]; pt1[2] = ptWorld[2]; pt1[3] = 1;
	GLmatrixVectorMul(mvMatrix, pt1, pt2);
	GLmatrixVectorMul(pjMatrix, pt2, pt1);
	ptViewport[0] = (pt1[0] / pt1[3] + 1.0) * viewport[2] / 2.0 + viewport[0];
	ptViewport[1] = (pt1[1] / pt1[3] + 1.0) * viewport[3] / 2.0 + viewport[1];	
}

void viewportCoordinates(const GLfloat ptWorld[3], GLfloat ptViewport[2], 
	const GLfloat *pjMatrix /* = NULL */, const GLfloat *mvMatrix/* = NULL */,
	const GLfloat *viewport /* = NULL */) {
	
	GLfloat _pjMatrix[16];
	GLfloat _mvMatrix[16];
	GLfloat _viewport[4];
	if (pjMatrix == NULL) {
		pjMatrix = _pjMatrix;
		glGetFloatv(GL_PROJECTION_MATRIX, _pjMatrix);
	}
	if (mvMatrix == NULL) {
		mvMatrix = _mvMatrix;
		glGetFloatv(GL_MODELVIEW_MATRIX, _mvMatrix);
	}
	if (viewport == NULL) {
		viewport = _viewport;
		glGetFloatv(GL_VIEWPORT, _viewport);
	}
		
	GLfloat pt1[4], pt2[4];
	pt1[0] = ptWorld[0]; pt1[1] = ptWorld[1]; pt1[2] = ptWorld[2]; pt1[3] = 1;
	GLmatrixVectorMul(mvMatrix, pt1, pt2);
	GLmatrixVectorMul(pjMatrix, pt2, pt1);
	ptViewport[0] = (pt1[0] / pt1[3] + 1.0) * viewport[2] / 2.0 + viewport[0];
	ptViewport[1] = (pt1[1] / pt1[3] + 1.0) * viewport[3] / 2.0 + viewport[1];

	
}

void GLmatrixVectorMul(const GLdouble m[16], const GLdouble v[4], GLdouble r[4]) {
/*	int i, j;
	for (i = 0; i < 4; i++) {
		r[i] = 0;
		for (j = 0; j < 4; j++)
			r[i] += m[j * 4 + i] * v[j];
	}*/
	r[0] = m[0 * 4 + 0] * v[0] + m[1 * 4 + 0] * v[1] + m[2 * 4 + 0] * v[2] + m[3 * 4 + 0] * v[3];
	r[1] = m[0 * 4 + 1] * v[0] + m[1 * 4 + 1] * v[1] + m[2 * 4 + 1] * v[2] + m[3 * 4 + 1] * v[3];
	r[2] = m[0 * 4 + 2] * v[0] + m[1 * 4 + 2] * v[1] + m[2 * 4 + 2] * v[2] + m[3 * 4 + 2] * v[3];
	r[3] = m[0 * 4 + 3] * v[0] + m[1 * 4 + 3] * v[1] + m[2 * 4 + 3] * v[2] + m[3 * 4 + 3] * v[3];
	
}

void GLmatrixVectorMul(const GLfloat m[16], const GLfloat v[4], GLfloat r[4]) {
/*	int i, j;
	for (i = 0; i < 4; i++) {
		r[i] = 0;
		for (j = 0; j < 4; j++)
			r[i] += m[j * 4 + i] * v[j];
	}*/
	r[0] = m[0 * 4 + 0] * v[0] + m[1 * 4 + 0] * v[1] + m[2 * 4 + 0] * v[2] + m[3 * 4 + 0] * v[3];
	r[1] = m[0 * 4 + 1] * v[0] + m[1 * 4 + 1] * v[1] + m[2 * 4 + 1] * v[2] + m[3 * 4 + 1] * v[3];
	r[2] = m[0 * 4 + 2] * v[0] + m[1 * 4 + 2] * v[1] + m[2 * 4 + 2] * v[2] + m[3 * 4 + 2] * v[3];
	r[3] = m[0 * 4 + 3] * v[0] + m[1 * 4 + 3] * v[1] + m[2 * 4 + 3] * v[2] + m[3 * 4 + 3] * v[3];
	
}

/// Multiplies the current OpenGL matrix with rotor 'v'
void rotorGLMult(const e3ga::rotor &v) {
	// compute the images of all OpenGL basis vectors
	e3ga::vector image[4] = {
			e3ga::_vector(v * e3ga::e1 * inverse(v)), // image of e1
			e3ga::_vector(v * e3ga::e2 * inverse(v)), // image of e2
			e3ga::_vector(v * e3ga::e3 * inverse(v)), // image of e3
			e3ga::vector() // 'image of origin'
	};

	// transfer the coordinates to the OpenGL matrix
	GLfloat GLmatrix[16];
	for (int i = 0; i < 4; i++) {
		const e3ga::vector &vc(image[i]);
		GLmatrix[i * 4 + 0] = vc.e1();
		GLmatrix[i * 4 + 1] = vc.e2();
		GLmatrix[i * 4 + 2] = vc.e3();
		GLmatrix[i * 4 + 3] = (i == 3) ? 1.0f : 0.0f;
	}

	/*printf("Knock knock. The matrix has you: \n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%f ", GLmatrix[j * 4 + i]);
		}
		printf("\n");
	}*/

	// multiply current OpenGL matrix:
	glMultMatrixf(GLmatrix);
}
