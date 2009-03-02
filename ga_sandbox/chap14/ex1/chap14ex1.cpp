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
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <set>
#include <string>
#include <utility>

#include <libgasandbox/common.h>
#include <libgasandbox/c2ga.h>
#include <libgasandbox/c2ga_draw.h>
#include <libgasandbox/c2ga_util.h>
#include <libgasandbox/gl_util.h>
#include <libgasandbox/glut_util.h>

// include QHull:
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "../../qhull-2003.1/src/qhull_a.h"
#ifdef __cplusplus
}
#endif /* __cplusplus */

using namespace c2ga;
using namespace mv_draw;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 14, Example 1: Voronoi Diagrams and Delaunay Triangulations";

// GLUT state information 
int g_viewportWidth = 800;
int g_viewportHeight = 600;
int g_GLUTmenu;

#define DRAW_VORONOI 1
#define DRAW_DELAUNAY 2

int g_drawMode = DRAW_DELAUNAY;

#define DRAG_POINTS 1
#define CREATE_POINTS 2

int g_mouseMode = DRAG_POINTS;

// what point to drag (or -1 for none)
int g_dragPoint = -1; 

// mouse position on last call to MouseButton() / MouseMotion()
c2ga::vectorE2GA g_prevMousePos;


std::vector<normalizedPoint> g_points;

class DelaunayVertex {
public:
	DelaunayVertex() {}
	DelaunayVertex(const c2ga::normalizedPoint &pt) : m_pt(pt) {}
	DelaunayVertex(const DelaunayVertex &V) : m_pt(V.m_pt), m_triangles(V.m_triangles) {}
	
	DelaunayVertex &operator=(const DelaunayVertex &V) {
		if (&V != this) {
			m_pt = V.m_pt;
			m_triangles = V.m_triangles;
		}
		return *this;
	}

	/// the position of the vertex:
	c2ga::normalizedPoint m_pt;
	/// the triangles this vertex is a member of:
	std::set<int> m_triangles;
};

class DelaunayTriangle {
public:
	DelaunayTriangle() {
		m_vertices[0] = m_vertices[1] = m_vertices[2] = -1;
		m_neighborTriangles[0] = 
			m_neighborTriangles[1] = 
			m_neighborTriangles[2] = -1;
	}

	DelaunayTriangle(int vtxIdx[3], const circle &C) : m_c(C) {
		m_vertices[0] = vtxIdx[0];
		m_vertices[1] = vtxIdx[1];
		m_vertices[2] = vtxIdx[2];
		m_neighborTriangles[0] = 
			m_neighborTriangles[1] = 
			m_neighborTriangles[2] = -1;
	}
	
	DelaunayTriangle(const DelaunayTriangle &T) : m_c(T.m_c) {
		m_vertices[0] = T.m_vertices[0];
		m_vertices[1] = T.m_vertices[1];
		m_vertices[2] = T.m_vertices[2];
		m_neighborTriangles[0] = T.m_neighborTriangles[0];
		m_neighborTriangles[1] = T.m_neighborTriangles[1];
		m_neighborTriangles[2] = T.m_neighborTriangles[2];
	}
	
	DelaunayTriangle& operator=(const DelaunayTriangle &T) {
		if (this != &T) {
			m_vertices[0] = T.m_vertices[0];
			m_vertices[1] = T.m_vertices[1];
			m_vertices[2] = T.m_vertices[2];
			m_neighborTriangles[0] = T.m_neighborTriangles[0];
			m_neighborTriangles[1] = T.m_neighborTriangles[1];
			m_neighborTriangles[2] = T.m_neighborTriangles[2];
			m_c = T.m_c;
		}
		return *this;
	}
	
	/// indices to the 3 vertices
	int m_vertices[3];
	/** 
	Indices to neighboring triangles.
	m_neighborTriangles[0] is the neighbor of edge m_vertices[0] -> m_vertices[1]
	*/
	int m_neighborTriangles[3];

	/// circle through the three vertices
	circle m_c;
};

class DelaunayTriangulation {
public:
	DelaunayTriangulation() {}
	DelaunayTriangulation(const DelaunayTriangulation &DT) :
		m_vertices(DT.m_vertices),
		m_triangles(DT.m_triangles) {}
		
	DelaunayTriangulation& operator=(const DelaunayTriangulation &DT) {
		if (this != &DT) {
			m_vertices = DT.m_vertices;
			m_triangles = DT.m_triangles;
		}
	}

	/// ordered list of vertices (the index of the vertex is the index into the vector<>)
	std::vector<DelaunayVertex> m_vertices;
	/// ordered list of vertices (the index of the triangle is the index into the vector<>)
	std::vector<DelaunayTriangle> m_triangles;
};

DelaunayTriangulation computeDelaunayTriangulation(const std::vector<normalizedPoint> &points) {
	// init qhull
	{
		qh_init_A (stdin, stdout, stderr, 0, NULL);
		if (setjmp (qh errexit)) {
			fprintf(stderr, "qhull generated error\n");
		}
		qh_initflags("qhull Qx i s Tcv C-0");
	}


	// setup geometry for qhull
	std::vector<coordT> qhCoord(points.size()*3);
	
	for (unsigned int i = 0; i < points.size(); i++) {
		// extract coordinates for each point:
		qhCoord[i * 3 + 0] = points[i].e1();
		qhCoord[i * 3 + 1] = points[i].e2();
		qhCoord[i * 3 + 2] = points[i].ni();
	}
	
	
	// do the qhull 
	{
		qh_init_B(&(qhCoord[0]), (int)points.size(), 3, 0);
		qh_qhull();
		qh_check_output();
	}
	
	// construct Delauney triangulation
	DelaunayTriangulation DT;
	{
		facetT *facet;
		vertexT *vertex;
		vertexT **vertexp;
		int qhCurlong, qhTotlong;
		FORALLfacets {
			setT *vertices = vertices = qh_facet3vertex (facet);
			int i = 0;
			int vtxIdx[3];
			FOREACHvertex_(vertices) {			
				// get index of this vertex
				int idx = qh_pointid(vertex->point);

				// ensure the vertex has been allocated:
				if ((int)DT.m_vertices.size() <= idx)
					DT.m_vertices.resize(idx+1);
				
				// check if vertex has been initialized:
				if (DT.m_vertices[idx].m_triangles.size() == 0) {
					// initialize vertex:
					// get coordinates:
					mv::Float e1C = vertex->point[0];
					mv::Float e2C = vertex->point[1];
					mv::Float niC = vertex->point[2];

					// create vertex:				
					DT.m_vertices[idx] = DelaunayVertex(
						normalizedPoint(normalizedPoint_e1_e2_ni_nof1_0, e1C, e2C, niC));
				}
				
				// add vertex index to triangle:
				vtxIdx[i++] = idx;
			}

			
			DelaunayVertex &V1 = DT.m_vertices[vtxIdx[0]];
			DelaunayVertex &V2 = DT.m_vertices[vtxIdx[1]];
			DelaunayVertex &V3 = DT.m_vertices[vtxIdx[2]];
		
			// check if `front-facing':
			circle C = _circle(V1.m_pt ^ V2.m_pt ^ V3.m_pt);
			if (_Float((C) << (e1 ^ e2 ^ ni)) < 0.0) continue; // do not use this triangle
			
			// add triangle idx to vertices:
			int triangleIdx = (int)DT.m_triangles.size();
			V1.m_triangles.insert(triangleIdx);
			V2.m_triangles.insert(triangleIdx);
			V3.m_triangles.insert(triangleIdx);
				
			// create new triangle:
			DT.m_triangles.push_back(DelaunayTriangle(vtxIdx, C));

			qh_settempfree(&vertices);			
		}

		/* free resources */
		qh_freeqhull(!qh_ALL);
		qh_memfreeshort(&qhCurlong, &qhTotlong);
		qhCoord.clear();
	}
	
	// construct the 'neigboring triangle info':
	// for all faces, check all pairs vertices [0, 1], [1, 2], [2, 0]
	// when two vertices are used in the same triangle (not equal to this
	// triangle), then that is the neighboring triangle
	for (unsigned int i = 0; i < DT.m_triangles.size(); i++) {
		DelaunayTriangle &T = DT.m_triangles[i];

		for (int j = 0; j < 3; j++) {
			const DelaunayVertex &V1 = DT.m_vertices[T.m_vertices[j]];
			const DelaunayVertex &V2 = DT.m_vertices[T.m_vertices[(j+1)%3]];
						
			// todo: use set union of STL
			for (std::set<int>::const_iterator I = V1.m_triangles.begin(); 
				I != V1.m_triangles.end(); I++) {
				if (*I == i) continue; // must not be this triangle!
				if (V2.m_triangles.find(*I) != V2.m_triangles.end()) {
					T.m_neighborTriangles[j] = *I;
				}
			}
		}
	}
	
	return DT;
}




void display() {
	doIntelWarning(); // warn for possible problems with pciking on Intel graphics chipsets

	// compute the triangulation:
	DelaunayTriangulation DT = computeDelaunayTriangulation(g_points);

	glViewport(0, 0, g_viewportWidth, g_viewportHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	pickLoadMatrix();
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

//	glTranslatef((float)g_viewportWidth / 2.0f, (float)g_viewportHeight / 2.0f, 0.0f);

	g_drawState.m_pointSize	= 3.0f;
	glColor3f(1.0f, 0.0f, 0.0f);
	// draw the points:
	for (unsigned int i = 0; i < g_points.size(); i++) {
		if (GLpick::g_pickActive) glLoadName(i);
		draw(g_points[i]);
	}
	
	if ((!GLpick::g_pickActive) && (g_drawMode == DRAW_DELAUNAY)) {
		// draw the Delaunay triangulation
		glColor3f(0.0f, 0.0f, 1.0f);
		for (unsigned int i = 0; i < DT.m_triangles.size(); i++) {
			const DelaunayTriangle &T = DT.m_triangles[i];
			const DelaunayVertex &V1 = DT.m_vertices[T.m_vertices[0]];
			const DelaunayVertex &V2 = DT.m_vertices[T.m_vertices[1]];
			const DelaunayVertex &V3 = DT.m_vertices[T.m_vertices[2]];
			
			glBegin(GL_LINE_LOOP);
				glVertex2f(V1.m_pt.e1(), V1.m_pt.e2());
				glVertex2f(V2.m_pt.e1(), V2.m_pt.e2());
				glVertex2f(V3.m_pt.e1(), V3.m_pt.e2());			
			glEnd();
		}
	}
	
	if ((!GLpick::g_pickActive) && (g_drawMode == DRAW_VORONOI)) {
		// draw the Voronoi diagram
		glLineStipple(1, 0x0F0F);
		
		// set of pair<triangleIdx, triangleIdx> that lists edges that were already drawn
		// (to avoid double work)
//		std::set<std::pair<int, int> > drawnEdges;
		
		glColor3f(0.0f, 1.0f, 0.0f);
		for (unsigned int i = 0; i < DT.m_triangles.size(); i++) {
			// visit each triangle:
			const DelaunayTriangle &T1 = DT.m_triangles[i];
						
			// get center point of T1:
			normalizedPoint C1 = _normalizedPoint(-T1.m_c * inverse(ni << T1.m_c));
			
			for (int j = 0; j < 3; j++) {
				// visit each edge:
				if (T1.m_neighborTriangles[j] < 0) {
					// from here to infinity!
					const DelaunayVertex &V1 = DT.m_vertices[T1.m_vertices[j]];
					const DelaunayVertex &V2 = DT.m_vertices[T1.m_vertices[(j+1)%3]];
					
					// get edge-mid-point direction(hack):
					vectorE2GA D = _vectorE2GA(unit_e(_vectorE2GA(0.5f * (V1.m_pt + V2.m_pt) - C1)));
					
					// possibly flip edge-mid-point direction (on which side of the edge is the center point?)
					if (_Float(dual(V1.m_pt ^ V2.m_pt ^ ni) << C1) < 0.0f)
						D = -D;
					
					glEnable(GL_LINE_STIPPLE);
					glBegin(GL_LINES);
					glVertex2f(C1.e1(), C1.e2());
					glVertex2f(C1.e1() + 300.0f * D.e1(), C1.e2() + 300.0f * D.e2());
					glEnd();
					glDisable(GL_LINE_STIPPLE);
				
				}
				else if (T1.m_neighborTriangles[j] <= (int)i)
					continue; // do not draw edges twice!
				else {
					// from here to center of other triangle
					const DelaunayTriangle &T2 = DT.m_triangles[T1.m_neighborTriangles[j]];
					
					// get center point of T2:
					normalizedPoint C2 = _normalizedPoint(-T2.m_c * inverse(ni << T2.m_c));
					
					// draw bisector:
					glBegin(GL_LINES);
					glVertex2f(C1.e1(), C1.e2());
					glVertex2f(C2.e1(), C2.e2());
					glEnd();
				
				}
				
			}
		}
	}
	
	
		
	glPopMatrix();
	
	if (!GLpick::g_pickActive) {
		glDisable(GL_DEPTH_TEST);
		glColor3f(0.0, 0.0, 0.0);
		void *font = GLUT_BITMAP_HELVETICA_12;
		renderBitmapString(20, g_viewportHeight - 20, font, (g_mouseMode == DRAG_POINTS) ? "Mouse mode: DRAG points" : "Mouse mode: CREATE points");
		renderBitmapString(g_viewportWidth / 2, g_viewportHeight - 20, font, (g_drawMode == DRAW_VORONOI) ? "Draw mode: VORONOI" : "Draw mode: DELAUNAY");
		
		renderBitmapString(20, 40, font, "Use the left mouse button to create and drag points (depending on mouse mode).");
		renderBitmapString(20, 20, font, "Use the other mouse buttons to access the popup menu (to select mouse mode, select draw mode).");
	}
	
	if (!GLpick::g_pickActive) {
		glutSwapBuffers();	
	}
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width;
	g_viewportHeight = height;

}

c2ga::vectorE2GA mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2;
	y -= g_viewportHeight / 2;
	return _vectorE2GA((float)x * e1 - (float)y * e2);
}

void MouseButton(int button, int state, int x, int y) {
	if (state == GLUT_UP) return;
	
	if (g_mouseMode == DRAG_POINTS) {
		g_dragPoint = pick(x, g_viewportHeight - y, display, NULL); // NULL = pointer to distance
	}
	else if (g_mouseMode == CREATE_POINTS) {
		g_dragPoint = pick(x, g_viewportHeight - y, display, NULL); // NULL = pointer to distance
		if (g_dragPoint >= 0) {
			// when you click too close to an existing point, switch to drag mode:
			g_mouseMode = DRAG_POINTS;
		}
		else g_points.push_back(c2gaPoint(x, g_viewportHeight - y));
	}
	
	g_prevMousePos = mousePosToVector(x, y);
	
	// redraw viewport
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	// get mouse position, motion
	c2ga::vectorE2GA mousePos = mousePosToVector(x, y);
	c2ga::vectorE2GA motion = _vectorE2GA(mousePos - g_prevMousePos);
	
	if (g_mouseMode == DRAG_POINTS) {
		if (g_dragPoint >= 0) {
			// translate point
			normalizedTranslator T = _normalizedTranslator(1.0f - (0.5f * motion ^ ni));
			g_points[g_dragPoint] = _normalizedPoint(T * g_points[g_dragPoint] * inverse(T));
		}
	}

	// remember mouse pos for next motion:
	g_prevMousePos = mousePos;

	// redraw viewport
	glutPostRedisplay();
}

void menuCallback(int value) {
	if (value < 0) {
		g_mouseMode = -value;
	}
	else g_drawMode = value;

	
	// redraw viewport
	glutPostRedisplay();	
}


int main(int argc, char*argv[]) {
	// profiling for Gaigen 2:
	c2ga::g2Profiling::init();

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
	
	g_GLUTmenu = glutCreateMenu(menuCallback);
	glutAddMenuEntry("Voronoi Diagram", DRAW_VORONOI);
	glutAddMenuEntry("Delaunay Triangulation", DRAW_DELAUNAY);
	glutAddMenuEntry("Mode: Drag Points", -DRAG_POINTS);
	glutAddMenuEntry("Mode: Create Points", -CREATE_POINTS);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	g_points.push_back(c2gaPoint(100, 200));
	g_points.push_back(c2gaPoint(200, 200));
	g_points.push_back(c2gaPoint(300, 400));
	g_points.push_back(c2gaPoint(100, 400));
	g_points.push_back(c2gaPoint(250, 450));
	g_points.push_back(c2gaPoint(700, 500));
	g_points.push_back(c2gaPoint(400, 300));
	g_points.push_back(c2gaPoint(650, 150));
	


	glutMainLoop();
	
	return 0;	
}
