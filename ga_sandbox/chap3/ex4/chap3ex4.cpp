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

// Copyright 2007, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined (OSX)
	#include <OpenGL/gl.h>
	#include <OpenGL/glext.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <CoreServices/CoreServices.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif

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
const char *IMAGE_NAME_1 = "image2.raw";
const char *IMAGE_NAME_2 = "image3.raw";

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
e3ga::vector g_IFcolors[3] = {
	_vector(0.82f*e1 + 0.08f*e2 + 0.08f*e3), // 'red'
	_vector(0.01f*e1 + 0.54f*e2 + 0.35f*e3), // 'green'
	_vector(0.18f*e2 + 0.37f*e3) // 'blue'
};

// the reciprocal color 'frame'
e3ga::vector g_RFcolors[3] = {
	_vector(e1), // reciprocal of 'red'
	_vector(e2), // reciprocal of 'green'
	_vector(e3) // reciprocal of 'blue'
};

// the index [0, 1, 2] of the color that will be modified by sampleColorAt()
int g_sampleColorIdx = 0;


// *!*HTML_TAG*!* colorSpaceConvert
/**
Converts colors in 'source' images to 'dest' image, according
to the color frame 'IFcolors'
*/
void colorSpaceConvert(
					   const unsigned char *source,
					   unsigned char *dest,
					   unsigned int width, unsigned int height,
					   const e3ga::vector *IFcolors,
					   e3ga::vector *RFcolors) {
	// compute reciprocal frame
	try {
		reciprocalFrame(IFcolors, RFcolors, 3);
	} catch (std::string &str) {
		fprintf(stderr, "Error: %s\n", str.c_str());
		g_RFcolors[0].set();
		g_RFcolors[1].set();
		g_RFcolors[2].set();
	}

	for (unsigned int i = 0; i < (width * height) * 3; i += 3) {
		// convert RGB pixel to vector:
		e3ga::vector c(vector_e1_e2_e3, (float)source[i + 0], (float)source[i + 1], (float)source[i + 2]);

		// compute colors in in destination image:
		float red = _Float(c << g_RFcolors[0]);
		float green = _Float(c << g_RFcolors[1]);
		float blue = _Float(c << g_RFcolors[2]);

		// clip colors:
		if (red < 0.0f) red = 0.0f;
		else if (red > 255.0f) red = 255.0f;
		if (green < 0.0f) green = 0.0f;
		else if (green > 255.0f) green = 255.0f;
		if (blue < 0.0f) blue = 0.0f;
		else if (blue > 255.0f) blue = 255.0f;

		// set colors in destination image
		dest[i + 0] = (unsigned char)(red + 0.5f); // +0.5f for correct rounding
		dest[i + 1] = (unsigned char)(green + 0.5f);
		dest[i + 2] = (unsigned char)(blue + 0.5f);
	}
}

void drawRectangle(int x, int y, int w, int h) {
	glBegin(GL_QUADS);
	glVertex2i(x + 0, y + 0);
	glVertex2i(x + 0, y + h);
	glVertex2i(x + w, y + h);
	glVertex2i(x + w, y + 0);
	glEnd();
}

void drawArrow(int x, int y, int w, int h) {
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w - h, y - h);
	glVertex2i(x + w, y);
	glVertex2i(x + w - h, y + h);
	glEnd();
}

void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);

	// draw color bar

	// get 'white' vector:
	e3ga::vector white = _vector(unit_e(e1 + e2 +e3));

	// Get two vectors, orthogonal to white:
	// factorizeBlade() find two vectors such that
	// dual(white) == O[1] ^ O[2]
	e3ga::vector O[2];
	factorizeBlade(dual(white), O);

	const float PI2 = (float)(2.0f * M_PI);
	const float STEP = 0.025f;
	float YT = (float)g_viewportHeight;
	float YB = (float)g_viewportHeight - 20;

	// alpha runs from 0 to 2 PI
	for (float angle = 0.0f; angle < PI2; angle += STEP) {
		// generate all fully saturated colors:
		e3ga::vector C = _vector(white + cos(angle) * O[0] + sin(angle) * O[1]);

		// alternative method (using exp() and geometric product)
//		rotor R = exp(_bivector(0.5f * alpha * (O[0] ^ O[1])));
//		e3ga::vector C = _vector(R * (white + O[0]) * inverse(R));

		// set current color:
		glColor3fv(C.getC(vector_e1_e2_e3));

		// draw small patch in the current color:
		float xl = (angle / PI2) * g_viewportWidth;
		float xr = ((angle + STEP) / PI2) * g_viewportWidth;
		glBegin(GL_QUADS);
		glVertex2f(xl, YB);
		glVertex2f(xr, YB);
		glVertex2f(xr, YT);
		glVertex2f(xl, YT);
		glEnd();
	}


	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelZoom(1.0f, -1.0f);
		glRasterPos2i(0, g_viewportHeight - 20);

		GLsizei width = g_imageWidth;
		GLsizei height = g_imageHeight;
		GLenum format = GL_RGB;
		GLenum type = GL_UNSIGNED_BYTE;
		const GLvoid *pixels  = &(g_sourceImage[0]);

		glDrawPixels(width, height, format, type, pixels);

		glRasterPos2i(g_viewportWidth / 2, g_viewportHeight - 20);
		pixels  = &(g_destImage[0]);
		glDrawPixels(width, height, format, type, pixels);
	}

	// draw small squares that show the change in color space:
	{
		const int arrowWidth = 20;
		int width = 80;
		int left = g_viewportWidth / 2 - width - arrowWidth;
		int height = (g_viewportHeight - g_imageHeight - 20) / 3;
		int top = height * 2;
		// input:
		for (int i = 0; i < 3; i++) {
			glColor3fv(g_IFcolors[i].getC(vector_e1_e2_e3));
			drawRectangle(left, top - i * height, width, height);
		}

		// arrows:
		left =  g_viewportWidth / 2 - arrowWidth/2;
		glColor3f(0.0, 0.0, 0.0);
		for (int i = 0; i < 3; i++)
			drawArrow(left, top - i * height + height/2, arrowWidth, 8);

		// goes to:
		left =  g_viewportWidth / 2 + arrowWidth;
		for (int i = 0; i < 3; i++) {
			glColor3f((i == 0) ? 1.0f : 0.0f, (i == 1) ? 1.0f : 0.0f, (i == 2) ? 1.0f : 0.0f);
			drawRectangle(left, top - i * height, width, height);
		}

		// active:
		left = g_viewportWidth / 2 - width - arrowWidth;
		width = 80 * 2 + arrowWidth * 2;
		height = (g_viewportHeight - g_imageHeight - 20) / 3;
		top = height * (2 - g_sampleColorIdx);
		glColor3f(0.0f, 0.0f, 0.0f);
		glLineWidth(3.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		drawRectangle(left, top, width, height);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1.0f);

	}


	glColor3f(0.0f, 0.0f, 0.0f);
	void *font = GLUT_BITMAP_HELVETICA_12;
	renderBitmapString(20, 40, font, "-use left mouse button to 'sample' colors");
	renderBitmapString(20, 20, font, "-use other mouse buttons for popup menu");



	glutSwapBuffers();

}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

	// redraw viewport
	glutPostRedisplay();
}

void sampleColorAt(int x, int y) {
	// sample color at x, y
	unsigned char rgb[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, rgb);
	printf("Color: %d %d %d\n", rgb[0], rgb[1], rgb[2]);
	e3ga::vector newColor = e3ga::vector(vector_e1_e2_e3, (float)rgb[0] / 255.0f, (float)rgb[1] / 255.0f, (float)rgb[2] / 255.0f);

	// set new value
	if (_Float(norm_e2(g_IFcolors[g_sampleColorIdx] - newColor))) {
		g_IFcolors[g_sampleColorIdx] = newColor;

		// convert image
		colorSpaceConvert(&(g_sourceImage[0]), &(g_destImage[0]),
			g_imageWidth, g_imageHeight, g_IFcolors, g_RFcolors);

		// redraw viewport
		glutPostRedisplay();
	}
}


void MouseButton(int button, int state, int x, int y) {
	sampleColorAt(x, g_viewportHeight - y);
}

void MouseMotion(int x, int y) {
	sampleColorAt(x, g_viewportHeight - y);
}

void loadRawImage(const char *filename) {
	FILE *F = fopen(filename, "rb");
	if (F == NULL) {
		char altName[1024];
		sprintf(altName, "../chap3/ex4/%s", filename);
		F = fopen(altName, "rb");
		if (F == NULL) {
			fprintf(stderr, "Could not open '%s'. This file should be in the current directory for this example to work!\n", filename);
			exit(-1);
		}
	}
	unsigned char buf[4];
	if (fread(buf, 4, 1, F) != 1) {
		fprintf(stderr, "Could not read '%s'.\n", filename);
		exit(-1);
	}
	g_imageWidth = (buf[0] << 8) + buf[1];
	g_imageHeight = (buf[2] << 8) + buf[3];
	printf("Image is %d X %d\n", g_imageWidth, g_imageHeight);
	g_sourceImage.resize(g_imageWidth*g_imageHeight*3);
	g_destImage.resize(g_imageWidth*g_imageHeight*3);

	if (fread(&(g_sourceImage[0]), 1, g_sourceImage.size(), F) != g_sourceImage.size()) {
		fprintf(stderr, "Could not read '%s'.\n", filename);
		exit(-1);
	}

	fclose(F);

	colorSpaceConvert(&(g_sourceImage[0]), &(g_destImage[0]),
		g_imageWidth, g_imageHeight, g_IFcolors, g_RFcolors);
}


void getfilename(const char *name, char *filename, int n) {
	filename[0] = '\0';
	#if defined (__APPLE__) || defined (OSX)
		FSRef fileref;
		Boolean isDir;
		FSPathMakeRef((const UInt8 *)name, &fileref, &isDir);
		
		FSRefMakePath(&fileref, (UInt8 *)filename, n);
	#else
		strcpy(filename, name);
	#endif
}


void menuCallback(int value) {
	if ((value >= 0) && (value < 3))
		g_sampleColorIdx = value;
	else if (value == -1) {
		char filename[512];
		getfilename(IMAGE_NAME_1, filename, 512);
		loadRawImage(filename);
	}
	else if (value == -2) {
		char filename[512];
		getfilename(IMAGE_NAME_2, filename, 512);
		loadRawImage(filename);
	}

	glutPostRedisplay();
}

int main(int argc, char*argv[]) {
	e3ga::g2Profiling::init();

	// load the raw image:
	char filename[512];
	getfilename(IMAGE_NAME_1, filename, 512);
	loadRawImage(filename);

	// GLUT Window Initialization:
	glutInit (&argc, argv);
	glutInitWindowSize(g_viewportWidth, g_viewportHeight);
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(WINDOW_TITLE);

	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);

	// create menu for color selection
	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry("sample red", 0);
	glutAddMenuEntry("sample green", 1);
	glutAddMenuEntry("sample blue", 2);
	glutAddMenuEntry("-------------------------", -3);
	glutAddMenuEntry("Image: computer parts", -1);
	glutAddMenuEntry("Image: soda cans", -2);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}
