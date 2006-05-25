#include <GL/glut.h>
#include "e3ga.h"
#include "e3ga_draw.h"
#include "e2ga.h"
#include "e2ga_draw.h"

/*

Todo:

Get first exercises written (also integrate into book)
(among this is ported singularity thingy


*/

using namespace mv_draw;

void display() {
	// Clear frame buffer and depth buffer
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up viewing transformation, looking down -Z axis
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float width = 1024;
	float height = 768;
	float ScreenSize = 1280;
	float m_frustumNear = 1.0;
	float m_frustumFar = 100.0;
	float m_frustumWidth = width / ScreenSize;
	float m_frustumHeight = height / ScreenSize;

	glFrustum(
		(GLdouble)-0.5 * m_frustumWidth, 
		(GLdouble)0.5 * m_frustumWidth, 
		(GLdouble)-0.5 * m_frustumHeight, 
		(GLdouble)0.5 * m_frustumHeight, 
		m_frustumNear, m_frustumFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -10.0f);

	glColor3f(1.0, 0.0, 0.0);


	//draw(e3ga::e1);
	//draw(e3ga::e1 ^ e3ga::e2, DRAW_BV_CIRCLE, 0x01);
	//draw(e3ga::e1 ^ e3ga::e2 ^ e3ga::e3, DRAW_TV_PARALLELEPIPED, 0x01);
	glScalef(0.5f, 0.5f, 0.5f);
	glTranslatef(-1, 0, 0);
	draw(e3ga::_rotor((e3ga::e1 + e3ga::e2) * e3ga::e2));

	//	draw(e2ga::e2);
	//draw(0.1 * e2ga::e1 ^ e2ga::e2, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(2, 0, 0);
	draw(e2ga::_rotor((e2ga::e1 + e2ga::e2) * e2ga::e2));
	

	// Make sure changes appear onscreen
	glutSwapBuffers();
}



int main(int argc, char *argv[]) {
	// GLUT Window Initialization:
	glutInit (&argc, argv);
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLUT test");

	glutDisplayFunc(display);


	glutMainLoop();

	return 0;
}