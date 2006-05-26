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

#include "h3ga_draw.h"
#include "e3ga_util.h"
#include "gl_util.h"
#include "mv_analyze.h"

using namespace mv_analyze;
using namespace e3ga;

namespace mv_draw {

void draw(const h3ga::mv &X, int method /*= 0 */, Palet *o /*= NULL*/) {
	mvAnalysis A(X);
	drawH3GA(A, method, o);
}

void drawH3GA(mvAnalysis &A, int method /*= 0 */, Palet *o /*= NULL*/) {
	/*
	Draw:
	Versors:
		ROTOR
	Blades:
		LOCALIZED_BLADE
			POINT (option: MAGNITUDE)
			LINE (option: ORIENTATION, MAGNITUDE)
			PLANE (option: ORIENTATION, MAGNITUDE)
		INFINITE_BLADE
			VECTOR
	*/


	//mvAnalysis A(X);

	mv::Float scaleConst = 4.0f * (mv::Float)sqrt(2.0);
	mv::Float stepSize = 0.1f;

	if (A.isBlade()) {
		if (A.bladeClass() == mvAnalysis::LOCALIZED_BLADE) {
			switch (A.bladeSubclass()) {
				case mvAnalysis::POINT:
					{
						g_drawState.pushDrawModeOff(OD_ORIENTATION);
						drawTriVector(A.m_pt[0], g_drawState.m_pointSize, NULL, DRAW_TV_SPHERE, o);
						g_drawState.popDrawMode();
					}
					break;
				case mvAnalysis::LINE:
					{
						glDisable(GL_LIGHTING);
						glPushMatrix();
						// translate to point on line 
						glTranslatef(A.m_pt[0].e1(), A.m_pt[0].e2(), A.m_pt[0].e3());

						// rotate e3 to line direction
						rotor rt = rotorFromVectorToVector(_vector(e3), A.m_vc[0]);
						rotorGLMult(rt);

						// draw line
						glBegin(GL_LINE_STRIP);
						for (mv::Float z = -scaleConst; z <= scaleConst; z += stepSize * scaleConst)
							glVertex3f(0.0, 0.0, z);
						glEnd();

						// draw 'orientation'
						if (g_drawState.getDrawMode() & OD_ORIENTATION) { 
							// option 3: little hooks 
							glTranslatef(0.0, 0.0, -scaleConst);
							for (mv::Float c = 0.0; c < 1.0; c += stepSize) {
								glPushMatrix();
								// if magnitude: scale
								if (g_drawState.getDrawMode() & OD_MAGNITUDE)
									glScaled(0.5 * fabs(A.m_sc[0]), 0.5 * fabs(A.m_sc[0]), 0.5 * fabs(A.m_sc[0]));
								else glScalef(0.5f, 0.5f, 0.5f);

								glBegin(GL_LINE_STRIP);
								glVertex3f(-0.25f, 0.0f, -1.0f);
								glVertex3f(0.0f, 0.0f, 0.0f);
								glVertex3f(0.25f, 0.0f, -1.0f);
								glEnd();

								glPopMatrix();
								glRotated(90.0f, 0.0f, 0.0f, 1.0f);
								glTranslated(0.0f, 0.0f, 2.0f * stepSize * scaleConst);
							}
						}
						glPopMatrix();
					}
					break;
				case mvAnalysis::PLANE:
					{
						for (int s = 0; s < 2; s++) { // draw both front and back side individually
							if (s == 0) { // front
								glPolygonMode(GL_FRONT, (g_drawState.getDrawMode() & OD_WIREFRAME) ? GL_LINE : GL_FILL);
								glNormal3fv(A.m_vc[2].getC(vector_e1_e2_e3)); 
							}
							else { // back
								glPolygonMode(GL_FRONT, ((g_drawState.getDrawMode() & OD_WIREFRAME) || 
									(g_drawState.getDrawMode() & OD_ORIENTATION)) ? GL_LINE : GL_FILL);
								glNormal3fv(_vector(-A.m_vc[2]).getC(vector_e1_e2_e3)); 
							}
							for (mv::Float y = -scaleConst; y < scaleConst - stepSize * scaleConst; y += stepSize * scaleConst) {
								glBegin(GL_QUAD_STRIP);
								for (mv::Float x = -scaleConst; x < scaleConst; x += stepSize * scaleConst) {
									glVertex3fv(_vector(A.m_pt[0] + x * A.m_vc[0] + ((s == 0) ? (y + stepSize * scaleConst) : y) * A.m_vc[1]).getC(vector_e1_e2_e3));
									glVertex3fv(_vector(A.m_pt[0] + x * A.m_vc[0] + ((s == 1) ? (y + stepSize * scaleConst) : y) * A.m_vc[1]).getC(vector_e1_e2_e3));
								}
								glEnd();
							}
						}

						
						if (g_drawState.getDrawMode() & OD_MAGNITUDE) { // draw normals
							mv::Float scaleMag = A.m_sc[0];
							glDisable(GL_LIGHTING);
							glBegin(GL_LINES);
							for (mv::Float y = -scaleConst; y <= scaleConst; y += stepSize * scaleConst) {
								for (mv::Float x = -scaleConst; x <= scaleConst; x += stepSize * scaleConst) {
									glVertex3fv(_vector(A.m_pt[0] + x * A.m_vc[0] + y * A.m_vc[1]).getC(vector_e1_e2_e3));
									glVertex3fv(_vector(A.m_pt[0] + x * A.m_vc[0] + y * A.m_vc[1] + scaleMag * A.m_vc[2]).getC(vector_e1_e2_e3));
								}
							}
							glEnd();
						}

					}
					break;
			}
			return;

		}
		else if (A.bladeClass() == mvAnalysis::INFINITE_BLADE) {
			switch (A.bladeSubclass()) {
				case mvAnalysis::VECTOR:
					{
						drawVector(e3ga::vector(), A.m_vc[0], A.m_sc[0]);
					}
					break;
				case mvAnalysis::LINE:
					{
						// todo: draw as bivector
					}
					break;
				case mvAnalysis::PLANE:
					{
						// todo: draw as trivector
					}
					break;
			}
			return;

		}
	}
	else if (A.isVersor()) {
		if (A.versorSubclass() == mvAnalysis::ROTOR) {
			if (A.m_sc[0] > 0.0001) {
				mv::Float scale = (g_drawState.getDrawMode() & OD_MAGNITUDE)
					? (mv::Float)sqrt(fabs(A.m_sc[0]) / M_PI) : 1.0f;

				// draw plane of rotation
				glPolygonMode(GL_FRONT_AND_BACK, (g_drawState.getDrawMode() & OD_WIREFRAME) ? GL_LINE : GL_FILL);
				g_drawState.pushDrawModeOff(OD_ORIENTATION);
				drawBivector(e3ga::vector(), A.m_vc[2], A.m_vc[0], A.m_vc[1], A.m_sc[0], DRAW_BV_CIRCLE, o);
				g_drawState.popDrawMode();

				// draw 'angle of rotation'
				if (o) o->setOlColor();
				else glColor3f(0.0, 0.0, 0.0);
				vector v = A.m_vc[0]; // vector in rotation plane

				bivector b = _bivector(-dual(A.m_vc[2])); // rotation plane
				v = _vector(unit_e(v) * (mv::Float)(0.8f * scale));

				int nbSteps, i;
				const mv::Float ainc = 0.05f * (mv::Float)M_PI;

				glBegin(GL_LINE_STRIP);
				glVertex3fv(v.getC(vector_e1_e2_e3));

				nbSteps = (int)(A.m_sc[1] / ainc) + 1;
				rotor R = _rotor(exp(((0.5f * A.m_sc[1]) / nbSteps) * b));
				rotor Ri = _rotor(inverse(R));
				for (i = 0; i < nbSteps; i++) {
					v = _vector(R * v * Ri);
					glVertex3fv(v.getC(vector_e1_e2_e3));
				}
				glEnd();

				// add arrowhead
				R = _rotor(exp(0.01f * b));
				v = _vector(R * v * Ri);
				glBegin(GL_LINE_STRIP);
				glVertex3fv(_vector(0.93f * v + 0.13f * (v << b)).getC(vector_e1_e2_e3));
				glVertex3fv(v.getC(vector_e1_e2_e3));
				glVertex3fv(_vector(1.05f * v + 0.15f * (v << b)).getC(vector_e1_e2_e3));
				glEnd();
			}
		}
		return;
	}
}


} /* end of namespace mv_draw */
