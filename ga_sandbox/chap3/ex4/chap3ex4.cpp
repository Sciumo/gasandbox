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
#endif WIN32

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <libgasandbox/e3ga.h>
#include <libgasandbox/e3ga_draw.h>
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

using namespace e3ga;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 3, Example 4: Color Space Conversion";

// note that image name is hard coded!!!
const char *IMAGE_NAME = "image.raw";

// dimension of images
unsigned int g_imageWidth, g_imageHeight;

// original image (read from file)
std::vector<unsigned char>g_sourceImage;
// color-converted image 
std::vector<unsigned char>g_destImage;

// GLUT state information
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

// the color 'frame'
vector g_IFcolors[3] = {
	_vector(e1), // 'red'
	_vector(e2), // 'green'
	_vector(e3) // 'blue'
};

// the reciprocal color 'frame'
vector g_RFcolors[3] = {
	_vector(e1), // reciprocal of 'red'
	_vector(e2), // reciprocal of 'green'
	_vector(e3) // reciprocal of 'blue'
};

/**
Updates g_destImage according to the input color frame g_IFcolors
*/
void colorSpaceConvert(
					   const unsigned char *source, 
					   unsigned char *dest,
					   unsigned int width, unsigned int height,
					   const vector *IFcolors,
					   vector *RFcolors) {
	// compute reciprocal frame
	reciprocalFrame(IFcolors, RFcolors, 3);

	for (unsigned int i = 0; i < (width * height) * 3; i += 3) {
		// convert RGB pixel to vector:
		vector c(vector_e1_e2_e3, (float)source[i + 0], (float)source[i + 1], (float)source[i + 2]);
		// compute colors in in destination image:
		float red = _Float(c % g_RFcolors[0]);
		float green = _Float(c % g_RFcolors[1]);
		float blue = _Float(c % g_RFcolors[2]);

		// clip colors:
		if (red < 0.0f) red = 0.0f;
		else if (red > 255.0f) red = 255.0f;
		if (green < 0.0f) green = 0.0f;
		else if (green > 255.0f) green = 255.0f;
		if (blue < 0.0f) blue = 0.0f;
		else if (blue > 255.0f) blue = 255.0f;

		dest[i + 0] = (unsigned char)red;
		dest[i + 1] = (unsigned char)green;
		dest[i + 2] = (unsigned char)blue;
	}


}

void display() {
	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);

	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelZoom(1.0f, -1.0f);
		glRasterPos2i(0, g_viewportHeight);

		GLsizei width = g_imageWidth; 
		GLsizei height = g_imageHeight;
		GLenum format = GL_RGB;
		GLenum type = GL_UNSIGNED_BYTE;
		const GLvoid *pixels  = &(g_sourceImage[0]);

		glDrawPixels(width, height, format, type, pixels);

		glRasterPos2i(g_viewportWidth / 2, g_viewportHeight);
		pixels  = &(g_destImage[0]);
		glDrawPixels(width, height, format, type, pixels);
	}


/*	glColor3f(1,1,1);
	void *font = GLUT_BITMAP_HELVETICA_12;
	renderBitmapString(10, 40, font, "-use left mouse button to drag red/green vectors and to orbit scene");
	renderBitmapString(10, 20, font, "-the blue vector should always be orthogonal to the red and green vectors");*/



	glutSwapBuffers();

}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// redraw viewport
	glutPostRedisplay();	
}



void MouseButton(int button, int state, int x, int y) {
	// todo: sample color

	// redraw viewport
	glutPostRedisplay();	
}

void MouseMotion(int x, int y) {
}

void Keyboard(unsigned char key, int x, int y) {

}

int main(int argc, char*argv[]) {
	e3ga::g2Profiling::init();

	// load the raw image:
	{
		FILE *F = fopen(IMAGE_NAME, "rb");
		if (F == NULL) {
			fprintf(stderr, "Could not open '%s'. This file should be in the current directory for this example to work!\n", IMAGE_NAME);
			return -1;
		}
		unsigned char buf[4];
		if (fread(buf, 4, 1, F) != 1) {
			fprintf(stderr, "Could not read '%s'.\n", IMAGE_NAME);
			return -1;
		}
		g_imageWidth = (buf[0] << 8) + buf[1];
		g_imageHeight = (buf[2] << 8) + buf[3];
		printf("Image is %d X %d\n", g_imageWidth, g_imageHeight);
		g_sourceImage.resize(g_imageWidth*g_imageHeight*3);
		g_destImage.resize(g_imageWidth*g_imageHeight*3);

		if (fread(&(g_sourceImage[0]), 1, g_sourceImage.size(), F) != g_sourceImage.size()) {
			fprintf(stderr, "Could not read '%s'.\n", IMAGE_NAME);
			return -1;
		}
		
		fclose(F);

	}

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

	glutMainLoop();

	return 0;
}
