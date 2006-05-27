#ifdef WIN32
#include <windows.h>
#endif

#ifdef RIEN

#include <GL/gl.h>
#include <GL/glu.h>

#include "draw.h"
#include "c3ga_draw.h"
#include "c3ga_analyze.h"
#include "c3ga_util.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif /* M_PI */

// todo: . . . .

namespace c3ga {

namespace drawConst {
const double POINT_SIZE = 0.033;
const double LINE_LENGTH = 5.0;
const double PLANE_SIZE = 10.0;
}
using namespace drawConst;

// test all done so far . . .
// 4 points, and sphere, line, plane, etc thorugh them . .. 
// 
void drawFlat(const mvAnalysis &A) {
	if (A.bladeSubclass() == mvAnalysis::POINT) {
		drawSphere(_vectorE3GA(A.m_pt[0]), POINT_SIZE);
	}
	else if (A.bladeSubclass() == mvAnalysis::LINE) {
		glLineWidth(2.0f);
		glBegin(GL_LINES);
		glVertex3dv(_vectorE3GA(A.m_pt[0] + LINE_LENGTH * A.m_vc[0]).getC(vectorE3GA_e1_e2_e3));
		glVertex3dv(_vectorE3GA(A.m_pt[0] - LINE_LENGTH * A.m_vc[0]).getC(vectorE3GA_e1_e2_e3));
		glEnd();
		glLineWidth(1.0f);
	}
	else if (A.bladeSubclass() == mvAnalysis::PLANE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		double scale = 1.0;
		int flags = 0;
		int nbSegs = (int)PLANE_SIZE;
		drawPlane(_vectorE3GA(A.m_pt[0]), _vectorE3GA((A.m_vc[0] ^ A.m_vc[1]) << inverse(I3)), scale, flags, nbSegs);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void drawRound(const mvAnalysis &A) {
	if (A.bladeSubclass() == mvAnalysis::POINT_PAIR) {
		drawSphere(_vectorE3GA(A.m_pt[0] + A.m_sc[0] * A.m_vc[0]), POINT_SIZE);
		drawSphere(_vectorE3GA(A.m_pt[0] - A.m_sc[0] * A.m_vc[0]), POINT_SIZE);
	}
	else if (A.bladeSubclass() == mvAnalysis::CIRCLE) {
		glLineWidth(2.0f);
		int flags = DD_OUTLINE;
		drawDisc(_vectorE3GA(A.m_pt[0]), _vectorE3GA((A.m_vc[0] ^ A.m_vc[1]) << inverse(I3)), A.m_sc[0], flags);
		glLineWidth(1.0f);
	}
	else if (A.bladeSubclass() == mvAnalysis::SPHERE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		drawSphere(_vectorE3GA(A.m_pt[0]),  A.m_sc[0]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void drawTangent(const mvAnalysis &A) {
	if (A.bladeSubclass() == mvAnalysis::SCALAR) {
		drawSphere(_vectorE3GA(A.m_pt[0]), POINT_SIZE);		
	}
	
	else if (A.bladeSubclass() == mvAnalysis::VECTOR) {
		drawVector(_vectorE3GA(A.m_pt[0]), A.m_vc[0], A.m_sc[0]);
	}
	else if (A.bladeSubclass() == mvAnalysis::BIVECTOR) {
		int flags = DD_OUTLINE | DD_FILL;
		double r2 = A.m_sc[0] / M_PI;
		double r = sqrt(r2);
		drawDisc(_vectorE3GA(A.m_pt[0]), _vectorE3GA((A.m_vc[0] ^ A.m_vc[1]) << inverse(I3)), r, flags);
	}
	else if (A.bladeSubclass() == mvAnalysis::TRIVECTOR) {
		double r3 = A.m_sc[0] * 3 / (4 * M_PI);
		double r = pow(r3, 1.0/3.0);
		drawSphere(_vectorE3GA(A.m_pt[0]),  r/2);
	}


}

void drawFree(const mvAnalysis &A) {
	glEnable(GL_POLYGON_STIPPLE);
	glEnable(GL_LINE_STIPPLE);

	if (A.bladeSubclass() == mvAnalysis::VECTOR) {
		drawVector(vectorE3GA(), A.m_vc[0], A.m_sc[0]);
	}
	else if (A.bladeSubclass() == mvAnalysis::BIVECTOR) {
		int flags = DD_OUTLINE | DD_FILL;
		double r2 = A.m_sc[0] / M_PI;
		double r = sqrt(r2);
		drawDisc(vectorE3GA(), _vectorE3GA((A.m_vc[0] ^ A.m_vc[1]) << inverse(I3)), r, flags);
	}
	else if (A.bladeSubclass() == mvAnalysis::TRIVECTOR) {
		double r3 = A.m_sc[0] * 3 / (4 * M_PI);
		double r = pow(r3, 1.0/3.0);
		drawSphere(vectorE3GA(),  r/2);
	}

	glDisable(GL_LINE_STIPPLE);
	glDisable(GL_POLYGON_STIPPLE);
}



void draw(const mvAnalysis &A) {
	if (A.model() != mvAnalysis::CONFORMAL)
		return;

	switch(A.bladeClass()) {
	case mvAnalysis::SCALAR:
	case mvAnalysis::ZERO:
		return;
	case mvAnalysis::FLAT:
		drawFlat(A);
		return;
	case mvAnalysis::ROUND:
		drawRound(A);
		return;
	case mvAnalysis::TANGENT:
		drawTangent(A);
		return;
	case mvAnalysis::FREE:
		drawFree(A);
		return;
	}

}

normalizedPoint labelPositionPoint(const mvAnalysis &A, unsigned int labelGenerator) {
	double r = POINT_SIZE + 2.0 * POINT_SIZE * (double)(labelGenerator % 5) / 4; // distance to center point
	double a1 = 2.0 * M_PI * (double)((labelGenerator / 5) % 11) / 10;
	double a2 = 2.0 * M_PI * (double)((labelGenerator / (5*11)) % 11) / 10;

	rotor R = _rotor(exp(a1 * (e1 ^ e2)) * exp(a2 * (e2 ^ e3)));
	freeVector t = _freeVector((r * _vectorE3GA(R * e3 * inverse(R))) ^ ni);
	translator T = _translator(1.0 - 0.5 * t);

	return _normalizedPoint(T * A.m_pt[0] * inverse(T));
}


normalizedPoint labelPositionFlat(const mvAnalysis &A, unsigned int labelGenerator) {
	if (A.bladeSubclass() == mvAnalysis::POINT) {
		return labelPositionPoint(A, labelGenerator);
	}
	else if (A.bladeSubclass() == mvAnalysis::LINE) {
		double a1 = -1.0 + 2.0 * (double)(labelGenerator % 31) / 30.0;

		freeVector t = _freeVector((LINE_LENGTH * a1 * A.m_vc[0]) ^ ni);
		translator T = _translator(1.0 - 0.5 * t);
		return _normalizedPoint(T * A.m_pt[0] * inverse(T));
	}
	else if (A.bladeSubclass() == mvAnalysis::PLANE) {
		double a1 = -1.0 + 2.0 * (double)(labelGenerator % 31) / 30.0;
		double r1 =  2 * M_PI * (double)((labelGenerator / 31) % 4) / 4.0;

		

		freeVector t = _freeVector((0.5 * PLANE_SIZE * A.m_vc[0] + a1 * 0.5 * PLANE_SIZE * A.m_vc[1]) ^ ni);
		rotor R = _rotor(exp(0.5 * r1 * (A.m_vc[0] ^ A.m_vc[1])));
		t = _freeVector(R * t * inverse(R));
		translator T = _translator(1.0 - 0.5 * t);
		return _normalizedPoint(T * A.m_pt[0] * inverse(T));
	}

	throw -1;
}

normalizedPoint labelPositionRound(const mvAnalysis &A, unsigned int labelGenerator) {
	if (A.bladeSubclass() == mvAnalysis::POINT_PAIR) {
		translator T;
		double shift = -0.5 + (double)((labelGenerator / 51) % 11) / 10.0;
			
		if ((labelGenerator % 51) & 1)
			T = _translator(1.0 - (0.5 * A.m_sc[0] + shift * POINT_SIZE) * (A.m_vc[0] ^ ni));
		else T = _translator(1.0 + (0.5 * A.m_sc[0] + shift * POINT_SIZE) * (A.m_vc[0] ^ ni));

		return _normalizedPoint(T * A.m_pt[0] * inverse(T));
	}
	else if (A.bladeSubclass() == mvAnalysis::CIRCLE) {
		double alpha = (double)(labelGenerator % 31) / 30.0;
		freeVector t = _freeVector((A.m_sc[0] * (cos(alpha) * A.m_vc[0] + sin(alpha) * A.m_vc[1])) ^ ni);
		translator T = _translator(1.0 - 0.5 * t);

		return _normalizedPoint(T * A.m_pt[0] * inverse(T));
	}
	else if (A.bladeSubclass() == mvAnalysis::SPHERE) {
		double r = A.m_sc[0]; // distance to center point
		double a1 = 2.0 * M_PI * (double)((labelGenerator / 5) % 11) / 10;
		double a2 = 2.0 * M_PI * (double)((labelGenerator / (5*11)) % 11) / 10;

		rotor R = _rotor(exp(a1 * (e1 ^ e2)) * exp(a2 * (e2 ^ e3)));
		freeVector t = _freeVector((r * _vectorE3GA(R * e3 * inverse(R))) ^ ni);
		translator T = _translator(1.0 - 0.5 * t);

		return _normalizedPoint(T * A.m_pt[0] * inverse(T));
	}
	

	throw -1;
}

normalizedPoint labelPositionTangentOrFree(const mvAnalysis &A, unsigned int labelGenerator, const normalizedPoint &pt) {
	if (A.bladeSubclass() == mvAnalysis::SCALAR) {
		return labelPositionPoint(A, labelGenerator);
	}
	else if (A.bladeSubclass() == mvAnalysis::VECTOR) {
		double a1 = (double)(labelGenerator % 31) / 30.0;

		freeVector t = _freeVector((A.m_sc[0] * a1 * A.m_vc[0]) ^ ni);
		translator T = _translator(1.0 - 0.5 * t);
		return _normalizedPoint(T * pt * inverse(T));
	}
	else if (A.bladeSubclass() == mvAnalysis::BIVECTOR) {
		double alpha = (double)(labelGenerator % 31) / 30.0;
		double r2 = A.m_sc[0] / M_PI;
		double r = sqrt(r2);

		freeVector t = _freeVector((r * (cos(alpha) * A.m_vc[0] + sin(alpha) * A.m_vc[1])) ^ ni);
		translator T = _translator(1.0 - 0.5 * t);

		return _normalizedPoint(T *pt * inverse(T));
	}
	else if (A.bladeSubclass() == mvAnalysis::TRIVECTOR) {
		double r3 = A.m_sc[0] * 3 / (4 * M_PI);
		double r = 0.5 * pow(r3, 1.0/3.0); // distance to center point
		double a1 = 2.0 * M_PI * (double)((labelGenerator / 5) % 11) / 10;
		double a2 = 2.0 * M_PI * (double)((labelGenerator / (5*11)) % 11) / 10;

		rotor R = _rotor(exp(a1 * (e1 ^ e2)) * exp(a2 * (e2 ^ e3)));
		freeVector t = _freeVector((r * _vectorE3GA(R * e3 * inverse(R))) ^ ni);
		translator T = _translator(1.0 - 0.5 * t);

		return _normalizedPoint(T * pt * inverse(T));
	}

	throw -1;
}


normalizedPoint labelPositionTangent(const mvAnalysis &A, unsigned int labelGenerator) {
	return labelPositionTangentOrFree(A, labelGenerator, A.m_pt[0]);
}


normalizedPoint labelPositionFree(const mvAnalysis &A, int labelGenerator) {
	return labelPositionTangentOrFree(A, labelGenerator, _normalizedPoint(no));
}


normalizedPoint labelPosition(const mvAnalysis &A, int labelGenerator /* = 0 */) {
	if (A.model() != mvAnalysis::CONFORMAL)
		throw -1;

	switch(A.bladeClass()) {
	case mvAnalysis::SCALAR:
	case mvAnalysis::ZERO:
		throw -1;
	case mvAnalysis::FLAT:
		return labelPositionFlat(A, labelGenerator);
	case mvAnalysis::ROUND:
		return labelPositionRound(A, labelGenerator);
	case mvAnalysis::TANGENT:
		return labelPositionTangent(A, labelGenerator);
	case mvAnalysis::FREE:
		return labelPositionFree(A, labelGenerator);
	}
	throw -1;
}


} // end of namespace c3ga

#endif 