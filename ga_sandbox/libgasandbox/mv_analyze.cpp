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

#include "mv_analyze.h"
#include "e3ga_util.h"
#include "h3ga_util.h"
#include "c3ga_util.h"

namespace mv_analyze {

// This is some weird inconsistency between gcc and MS compiler:
// With GCC, you have to define static const int members here, too!
#ifndef WIN32
const int mvAnalysis::NB_POINTS;
const int mvAnalysis::NB_VECTORS;
const int mvAnalysis::NB_SCALARS ;
const int mvAnalysis::NB_TYPE_LEVELS ;
const int mvAnalysis::FLAG_VALID ;
const int mvAnalysis::FLAG_DUAL;
const int mvAnalysis::VECTOR_SPACE;
const int mvAnalysis::HOMOGENEOUS ;
const int mvAnalysis::CONFORMAL;
const int mvAnalysis::INVALID_TYPE ;
const int mvAnalysis::MULTIVECTOR;
const int mvAnalysis::VERSOR;
const int mvAnalysis::BLADE;
const int mvAnalysis::SCALAR;
const int mvAnalysis::FLAT;
const int mvAnalysis::ROUND;
const int mvAnalysis::TANGENT ;
const int mvAnalysis::FREE ;
const int mvAnalysis::ZERO;

	
const int mvAnalysis::POINT;
const int mvAnalysis::LINE;
const int mvAnalysis::PLANE;
const int mvAnalysis::POINT_PAIR ;
const int mvAnalysis::CIRCLE ;
const int mvAnalysis::SPHERE;
const int mvAnalysis::VECTOR;
const int mvAnalysis::BIVECTOR;
const int mvAnalysis::TRIVECTOR;
const int mvAnalysis::NOT_USED ;
const int mvAnalysis::EVEN_VERSOR;
const int mvAnalysis::ODD_VERSOR;
#endif

mvAnalysis::mvAnalysis() : m_flags(0), m_epsilon(0.0) {
	for (int i = 0; i < NB_SCALARS; i++)
		m_sc[i] = (e3ga::mv::Float)0.0;

	for (int i = 0; i < NB_TYPE_LEVELS; i++)
		m_type[i] = INVALID_TYPE;
}

mvAnalysis::mvAnalysis(const e2ga::mv &X, int intFlags/* = 0 */, double epsilon/* = DEFAULT_EPSILON */) {
	analyze(X, intFlags, epsilon);
}

mvAnalysis::mvAnalysis(const e3ga::mv &X, int intFlags/* = 0 */, double epsilon/* = DEFAULT_EPSILON */) {
	analyze(X, intFlags, epsilon);
}

mvAnalysis::mvAnalysis(const h3ga::mv &X, int intFlags/* = 0 */, double epsilon/* = DEFAULT_EPSILON */, 
					   const h3ga::normalizedPoint &probe /*= h3ga::_normalizedPoint(h3ga::e0)*/) {
	analyze(X, intFlags, epsilon, probe);
}

mvAnalysis::mvAnalysis(const c3ga::mv &X, int intFlags/* = 0 */, double epsilon/* = DEFAULT_EPSILON */, 
					   const c3ga::normalizedPoint &probe /*= c3ga::_normalizedPoint(c3ga::no)*/) {
	analyze(X, intFlags, epsilon, probe);
}


mvAnalysis::~mvAnalysis() {
}

mvAnalysis::mvAnalysis(const mvAnalysis &I) {
	operator=(I);
}


mvAnalysis &mvAnalysis::operator=(const mvAnalysis &I) {
	if (&I != this) {
		for (int i = 0; i < NB_POINTS; i++)
			m_pt[i] = I.m_pt[i];
		for (int i = 0; i < NB_VECTORS; i++)
			m_vc[i] = I.m_vc[i];
		for (int i = 0; i < NB_SCALARS; i++)
			m_sc[i] = I.m_sc[i];
		for (int i = 0; i < NB_TYPE_LEVELS; i++)
			m_type[i] = I.m_type[i];
		m_flags = I.m_flags;
		m_epsilon = I.m_epsilon;
		m_mvType = I.m_mvType;
	}
	return *this;
}

std::string mvAnalysis::toString() const {
	std::string result;
	if (!isValid()) result = "invalid analysis";

	else if (model() == VECTOR_SPACE_MODEL) {
		// model:
		result += "Conformal";

		// flags / special stuff:
		if (isDual()) result += " dual";
		if (isZero()) result += " zero";

		// blade / versor / multivector?
		if (isBlade()) result += " blade";
		else if (isVersor()) result += " versor";
		else result += " multivector";

		if (isBlade()) {
			result += ":";
			switch(bladeSubclass()) {
				case SCALAR:
					result += " point";
					break;
				case VECTOR:
					result += " vector";
					break;
				case BIVECTOR:
					result += " bivector";
					break;
				case TRIVECTOR:
					result += " trivector";
					break;
			}
		}
		else if (isVersor()) {
			result += ":";
			switch(versorSubclass()) {
				case ODD_VERSOR:
					result += " odd versor";
					break;
				case EVEN_VERSOR:
					result += " even versor";
					break;
			}
		}
	}

	else if (model() == HOMOGENEOUS_MODEL) {
		// model:
		result += "Conformal";

		// flags / special stuff:
		if (isDual()) result += " dual";
		if (isZero()) result += " zero";

		// blade / versor / multivector?
		if (isBlade()) result += " blade";
		else if (isVersor()) result += " versor";
		else result += " multivector";

		if (!isZero()) {
			if (isBlade()) {
				result += ":";

				if (bladeClass() == INFINITE_BLADE) {
					switch(bladeSubclass()) {
					case POINT:
						result += " vector";
						break;
					case LINE:
						result += " line at infinity";
						break;
					case PLANE:
						result += " plane at infinity";
						break;
					}
				}
				else if (bladeClass() == LOCALIZED_BLADE) {
					switch(bladeSubclass()) {
					case POINT:
						result += " point";
						break;
					case LINE:
						result += " line";
						break;
					case PLANE:
						result += " plane";
						break;
					}
				}
			}
			else if (isVersor()) {
				result += ":";
				switch(versorSubclass()) {
					case ODD_VERSOR:
						result += " odd versor";
						break;
					case EVEN_VERSOR:
						result += " even versor";
						break;
					case ROTOR:
						result += " rotor";
						break;
				}
			}
		}
	}

	else if (model() == CONFORMAL_MODEL) {
		// model:
		result += "Conformal";

		// flags / special stuff:
		if (isDual()) result += " dual";
		if (isZero()) result += " zero";

		// blade / versor / multivector?
		if (isBlade()) result += " blade";
		else if (isVersor()) result += " versor";
		else result += " multivector";

		if (!isZero()) {
			if (isBlade()) {
				result += ":";
				switch (bladeClass()) {
				case SCALAR:
					result += " scalar";
					break;
				case FLAT:
					switch(bladeSubclass()) {
					case SCALAR:
						result += " scalar";
						break;
					case POINT:
						result += " scalar (AKA: 'point')";
						break;
					case LINE:
						result += " line";
						break;
					case PLANE:
						result += " plane";
						break;
					}
					break;
				case ROUND:
					switch(bladeSubclass()) {
					case POINT_PAIR:
						result += " point pair";
						break;
					case CIRCLE:
						result += " circle";
						break;
					case SPHERE:
						result += " sphere";
						break;
					}
					break;
				case TANGENT:
				case FREE:
					result +=(bladeClass() == FREE) ? " free" : " tangent";
					switch(bladeSubclass()) {
					case SCALAR:
						result += " point";
						break;
					case VECTOR:
						result += " vector";
						break;
					case BIVECTOR:
						result += " bivector";
						break;
					case TRIVECTOR:
						result += " trivector";
						break;
					}
					break;
				default:
					result += "of unknown class";
					break;
				}
			}
		}

	}
	else {
		result += "multivector from unknown model";
	}
	return result;

}


void mvAnalysis::analyze(e2ga::mv X, int intFlags/* = 0 */,  double epsilon/* = DEFAULT_EPSILON */) {
	// cleanup:
	m_flags = FLAG_VALID;
	m_epsilon = epsilon;
	for (int i = 0; i < NB_TYPE_LEVELS; i++)
		m_type[i] = INVALID_TYPE;

	// type is vector space
	m_type[0] = VECTOR_SPACE_MODEL;
	m_type[2] = NOT_USED; // no blade/versor classes

	// forced dual interpretation?
	if (intFlags & FLAG_DUAL) {
		m_flags ^= FLAG_DUAL;
		X = e2ga::dual(X); // should 'dual' be 'undual?'
	}

	// get basic mv type (BLADE, VERSOR, etc)
	m_mvType = e2ga::mvType(X, (e2ga::mv::Float)epsilon);
	m_type[1] = m_mvType.m_type;

	// zero blade? 
	if (m_mvType.m_zero) {
		m_type[3] = ZERO;
		m_sc[0] = 0;
		return;
	}

	// versor?
	else if (m_mvType.m_type == VERSOR) {
		m_type[3] = EVEN_VERSOR;		

		// format for versor:
		// m_sc[0] = magnitude
		// m_sc[1] = angle
		// m_vc[0], m_vc[1] is basis for rotation plane
		m_vc[0] = e3ga::_vector(e3ga::e1);
		m_vc[1] = (_bivector(X).e1e2() < 0.0) ? -e3ga::e2 : e3ga::e2;

		m_sc[0] = e2ga::_Float(norm_e(X));
		m_sc[1] = 2.0f * (e3ga::mv::Float)atan2(e2ga::_Float(e2ga::norm_e(e2ga::_bivector(X))), e2ga::_Float(X));
		return;
	}

	// blade
	else if (m_mvType.m_type == BLADE) {
		m_type[3] = VECTOR + m_mvType.m_grade - 1;

		// format for blade:
		// m_sc[0] = size (norm_e())

		// for a vector: 
		// m_vc[0] is the unit direction

		// for bivector:
		// m_vc[0], m_vc[1] is basis for plane

		m_sc[0] = e2ga::_Float(e2ga::norm_e(X));
		if (m_type[3] == VECTOR) {
			e2ga::vector Xn = e2ga::_vector(e2ga::unit_e(X));
			m_vc[0] = Xn.e1() * e3ga::e1 + Xn.e2() * e3ga::e2;
		}
		else if (m_type[3] == BIVECTOR) {
			m_vc[0] = e3ga::e1;
			m_vc[1] = (_bivector(X).e1e2() < 0.0) ? -e3ga::e2 : e3ga::e2;
		}
		return;
	}




}

void mvAnalysis::analyze(e3ga::mv X, int intFlags/* = 0 */,  double epsilon/* = DEFAULT_EPSILON */) {
	// cleanup:
	m_flags = FLAG_VALID;
	m_epsilon = epsilon;
	for (int i = 0; i < NB_TYPE_LEVELS; i++)
		m_type[i] = INVALID_TYPE;

	// type is vector space
	m_type[0] = VECTOR_SPACE_MODEL;
	m_type[2] = NOT_USED; // no blade/versor classes

	// forced dual interpretation?
	if (intFlags & FLAG_DUAL) {
		m_flags ^= FLAG_DUAL;
		X = e3ga::dual(X); // should 'dual' be 'undual?'
	}

	// get basic mv type (BLADE, VERSOR, etc)
	m_mvType = e3ga::mvType(X, (e3ga::mv::Float)epsilon);
	m_type[1] = m_mvType.m_type;

	// zero blade? 
	if (m_mvType.m_zero) {
		m_type[3] = ZERO;
		m_sc[0] = 0;
		return;
	}

	// versor?
	else if (m_mvType.m_type == VERSOR) {
		m_type[3] = (m_mvType.m_parity) ? ODD_VERSOR : ROTOR;		

		if (m_type[3] == ROTOR) {
			// format for rotor:
			// m_sc[0] = magnitude
			// m_sc[1] = angle
			// m_vc[0], m_vc[1] is basis for rotation plane
			// m_vc[2] is normal to rotation plane
			e3ga::factorizeBlade(_bivector(X), m_vc);
			m_vc[2] = _vector(e3ga::dual(m_vc[0] ^ m_vc[1]));

			m_sc[0] = e3ga::_Float(norm_e(X));
	//		printf("%f %f\n", e3ga::_Float(e3ga::norm_e(e3ga::_bivector(X))), e3ga::_Float(X));
			m_sc[1] = (e3ga::mv::Float)(2.0 * atan2(e3ga::_Float(e3ga::norm_e(e3ga::_bivector(X))), e3ga::_Float(X)));
		}
		else {
			// no info for odd versor, since we do not draw it?
		}

		return;
	}

	// blade
	else if (m_mvType.m_type == BLADE) {
		// format for blade:
		// m_sc[0] = size (unit_e())

		// for a vector: 
		// m_vc[0] is the unit direction

		// for bivector:
		// m_vc[0], m_vc[1] is basis for plane

		// for trivector:
		// m_vc[0], m_vc[1], m_vc[2]

		m_sc[0] = e3ga::_Float(e3ga::norm_e(X));
		if (m_mvType.m_grade == 1) {
			m_type[3] = VECTOR;
			m_vc[0] = e3ga::_vector(e3ga::unit_e(X));
		}
		else if (m_mvType.m_grade == 2) {
			m_type[3] = BIVECTOR;
			e3ga::factorizeBlade(_bivector(X), m_vc);
			m_vc[2] = _vector(e3ga::dual(m_vc[0] ^ m_vc[1]));
		}
		else if (m_mvType.m_grade == 3) {
			m_type[3] = TRIVECTOR;
			m_vc[0] = e3ga::_vector(e3ga::e1);
			m_vc[1] = e3ga::_vector(e3ga::e2);
			m_vc[2] = e3ga::_vector(e3ga::e3);
		}
		return;
	}
}

void mvAnalysis::analyze(h3ga::mv X, int intFlags/* = 0 */,  double epsilon/* = DEFAULT_EPSILON */, 
						 const h3ga::normalizedPoint &probe /*= h3ga::_normalizedPoint(h3ga::e0)*/) {
	// cleanup:
	m_flags = FLAG_VALID;
	m_epsilon = epsilon;
	for (int i = 0; i < NB_TYPE_LEVELS; i++)
		m_type[i] = INVALID_TYPE;

	// type is vector space
	m_type[0] = HOMOGENEOUS_MODEL;
	m_type[2] = NOT_USED; // later on in this function, if 'X' it is a blade, the m_type[2] will be set to either LOCALIZED_BLADE or INFINITE_BLADE

	// forced dual interpretation?
	if (intFlags & FLAG_DUAL) {
		m_flags ^= FLAG_DUAL;
		X = h3ga::dual(X); // should 'dual' be 'undual?'
	}

	// get basic mv type (BLADE, VERSOR, etc)
	m_mvType = h3ga::mvType(X, (h3ga::mv::Float)epsilon);
	m_type[1] = m_mvType.m_type;

	// zero blade? 
	if (m_mvType.m_zero) {
		m_type[3] = ZERO;
		m_sc[0] = 0;
		return;
	}

	// versor?
	else if (m_mvType.m_type == VERSOR) {
		if (m_mvType.m_parity) {
			// no info for odd versor, since we don't draw it
			m_type[3] = ODD_VERSOR;
		}
		else {
			if (_Float(norm_e(X - _rotor(X))) < epsilon) {
				// rotor
				m_type[3] = ROTOR;

				// test by applying it to e0?
				// or simply cast to rotor, subtract, get norm, must be (near-)zero

				// format for versor:
				// m_sc[0] = magnitude
				// m_sc[1] = angle
				// m_vc[0], m_vc[1] is basis for rotation plane
				// m_vc[2] is normal to rotation plane
				h3ga::vector factors[2];
				h3ga::factorizeBlade(_bivector(X), factors);
				m_vc[0] = e3ga::vector(e3ga::vector_e1_e2_e3, factors[0].getC(h3ga::vector_e1_e2_e3));
				m_vc[1] = e3ga::vector(e3ga::vector_e1_e2_e3, factors[1].getC(h3ga::vector_e1_e2_e3));
				m_vc[2] = _vector(e3ga::dual(m_vc[0] ^ m_vc[1]));

				m_sc[0] = h3ga::_Float(norm_e(X));
				m_sc[1] = (h3ga::mv::Float)(2.0 * atan2(h3ga::_Float(h3ga::norm_e(h3ga::_bivector(X))), h3ga::_Float(X)));
			}
			else {
				// no info for even versor, since we don't draw it
				m_type[3] = EVEN_VERSOR;
			}
		}
		return;
	}

	// blade
	else if (m_mvType.m_type == BLADE) {
		if (m_mvType.m_grade == 0) {
			m_type[2] =	 LOCALIZED_BLADE;
			m_type[3] = SCALAR;

			// format for scalar:
			// m_sc[0] = size (unit_e())
			m_sc[0] = _Float(X);
			return;
		}
		else if (m_mvType.m_grade == 4) {
			m_type[2] =	 LOCALIZED_BLADE;
			m_type[3] = PSEUDOSCALAR;

			// format for scalar:
			// m_sc[0] = size
			m_sc[0] = X.e1e2e3e0();
			return;
		}
		else {
			h3ga::mv attitude = h3ga::e0i << X;
			h3ga::mv moment = h3ga::e0i << (h3ga::e0 ^ X);

			if (_Float(norm_e(attitude)) < epsilon) {
				m_type[2] =	 INFINITE_BLADE;
				// INFINITE blade
				// VECTOR, LINE, or PLANE

				// format for INFINITE blade:
				// m_sc[0] = size (norm_e())

				// for a VECTOR: 
				// m_vc[0] is the unit direction

				// for LINE:
				// m_vc[0], m_vc[1] is basis for plane

				// for PLANE:
				// m_vc[0], m_vc[1], m_vc[2] is basis for trivector

				m_sc[0] = _Float(norm_e(X));
				if (m_mvType.m_grade == 1) {
					m_type[3] = VECTOR;
					m_vc[0] = e3ga::vector(e3ga::vector_e1_e2_e3, h3ga::_vector(unit_e(X)).getC(h3ga::vector_e1_e2_e3));
				}
				else if (m_mvType.m_grade == 2) {
					m_type[3] = LINE;
					h3ga::vector factors[2];
					h3ga::factorizeBlade(_bivector(X), factors);
					m_vc[0] = e3ga::vector(e3ga::vector_e1_e2_e3, factors[0].getC(h3ga::vector_e1_e2_e3));
					m_vc[1] = e3ga::vector(e3ga::vector_e1_e2_e3, factors[1].getC(h3ga::vector_e1_e2_e3));
				}
				else if (m_mvType.m_grade == 3) {
					m_type[3] = PLANE;
					m_vc[0] = e3ga::e1;
					m_vc[1] = e3ga::e2;
					m_vc[2] = e3ga::e3;
				}
				return;
			}
			else {
				// translate blade such that probe == origin
				h3ga::vector T = _vector(probe);
				if (_Float(h3ga::norm_e2(T)) != 0.0f)
					X = X - (T ^ (h3ga::e0 << X));
			

				// recompute attitude & moment
				attitude = h3ga::e0i << X;
				moment = h3ga::e0i << (h3ga::e0 ^ X);

				m_type[2] =	 LOCALIZED_BLADE;

				h3ga::vector supportVector = h3ga::_vector(moment * inverse(attitude));
				h3ga::point supportPoint = h3ga::_point(X * inverse(attitude));

				// LOCALIZED blade
				// POINT, LINE, or PLANE

				// format for LOCALIZED blade:
				// m_sc[0] = size (norm_e())
				// m_pt[0] is support point

				// for a VECTOR: 
				// -

				// for LINE:
				// m_vc[0], is basis for moment
				// m_vc[2] basis for dual of moment

				// for PLANE:
				// m_vc[0], m_vc[1] is basis for moment
				// m_vc[2] dual of moment

				m_sc[0] = _Float(norm_e(X));
				m_pt[0] = e3ga::vector(e3ga::vector_e1_e2_e3, supportVector.getC(h3ga::vector_e1_e2_e3));

				if (m_mvType.m_grade == 1) {
					m_type[3] = VECTOR;
				}
				else if (m_mvType.m_grade == 2) {
					m_type[3] = LINE;
					m_vc[0] = e3ga::vector(e3ga::vector_e1_e2_e3, h3ga::_vector(unit_e(attitude)).getC(h3ga::vector_e1_e2_e3));
					// dual (in e3ga)
					e3ga::factorizeBlade(dual(m_vc[0]), m_vc + 1);
				}
				else if (m_mvType.m_grade == 3) {
					m_type[3] = PLANE;

					h3ga::vector factors[2];
					h3ga::factorizeBlade(_bivector(attitude), factors);
					m_vc[0] = e3ga::vector(e3ga::vector_e1_e2_e3, factors[0].getC(h3ga::vector_e1_e2_e3));
					m_vc[1] = e3ga::vector(e3ga::vector_e1_e2_e3, factors[1].getC(h3ga::vector_e1_e2_e3));
					m_vc[2] = _vector(e3ga::dual(m_vc[0] ^ m_vc[1]));
				}

				// translate support point to undo the probe translation, above:
				if (_Float(h3ga::norm_e2(T)) != 0.0)
					m_pt[0] = _vector(m_pt[0] + T.e1() * e3ga::e1 + T.e2() * e3ga::e2 + T.e3() * e3ga::e3);

				return;
			}
		}
	}

}

using namespace c3ga;

void mvAnalysis::analyze(c3ga::mv X, int intFlags/* = 0 */,  double epsilon/* = DEFAULT_EPSILON */, 
						 const c3ga::normalizedPoint &probe /*= _normalizedPoint(no)*/) {
	// cleanup:
	m_flags = FLAG_VALID;
	m_epsilon = epsilon;
	for (int i = 0; i < NB_TYPE_LEVELS; i++)
		m_type[i] = INVALID_TYPE;

	// type is conformal
	m_type[0] = CONFORMAL_MODEL;

	// forced dual interpretation?
	if (intFlags & FLAG_DUAL) {
		m_flags ^= FLAG_DUAL;
		X = dual(X); // should 'dual' be 'undual?'
	}

	// get basic mv type (BLADE, VERSOR, etc)
	m_mvType = mvType(X, (mv::Float)epsilon);
	m_type[1] = m_mvType.m_type;

	// zero blade? 
	if (m_mvType.m_zero) {
		m_type[2] = ZERO;
		m_sc[0] = 0;
		return;
	}

	// scalar, pseudoscalar???

	// init basic classifiers:
	c3ga::mv::Float _opNiX = _Float(norm_e(op(ni, X)));
	c3ga::mv::Float _ipNiX = _Float(norm_e(lcont(ni, X)));
	c3ga::mv::Float _X2 = _Float(norm_r2(X));

	// init basic classifiers (bool):
	bool opNiX = (fabs(_opNiX) >= epsilon);
	bool ipNiX = (fabs(_ipNiX) >= epsilon);
	bool X2 = (fabs(_X2) >= epsilon);
	//printf("X2 = %e\n", _X2);

	// free?
	if ((!opNiX) && (!ipNiX))
		analyzeFree(X, intFlags,  epsilon);

	// flat?
	else if ((!opNiX) && (ipNiX)) {
//		mv probe = no; // allow probe to be specified
		analyzeFlat(X, probe, intFlags,  epsilon);
	}

	// dual flat?
	else if ((opNiX) && (!ipNiX)) {
		m_flags ^= FLAG_DUAL;
//		mv probe = no;
		analyzeFlat(dual(X), probe, intFlags,  epsilon); // should 'dual' be 'undual'?
	}

	// tangent
	else if ((opNiX) && (ipNiX) && (!X2))
		analyzeTangent(X, intFlags,  epsilon);

	// round
	else if ((opNiX) && (ipNiX) && (X2))
		analyzeRound(X, intFlags,  epsilon);
}

void mvAnalysis::analyzeRound(const mv &X, int intFlags /* = 0 */, double epsilon /* = DEFAULT_EPSILON */) {

	m_type[2] = ROUND;
	int Agrade = m_mvType.m_grade;

	// make exception for scalars:
	if (Agrade == 0) {
		m_type[2] = SCALAR;
		m_type[3] = SCALAR;
		// ************* format of 'round' scalar***************
		// m_sc[0] = signed weight
		// ************* END format of round ***************
		m_sc[0] = _float(X);
		return;
	}


	// free N-vector
	mv attitude = negate(op(lcont(ni, X), ni)); 

	// _location is normalized dual sphere
	mv _location = gp(X, inverse(lcont(ni, X))); 
	_location = gp(_location, inverse(-_Float(scp(ni, _location))));
	// location:
	normalizedPoint location = c3gaPoint(_vectorE3GA(_location));

	mv::Float niX2 = _Float(scp(lcont(ni, X), lcont(ni, X)));

	// radius squared:
	mv::Float radius2 = _Float(gp(X, gradeInvolution(X)) * (1.0f / niX2)); // *-1 required?

	// weight:
	mv::Float weight = _Float(norm_r(lcont(no, attitude)));

	// ************* format of round ***************
	// m_pt[0] = location
	// m_sc[0] = signed radius
	// m_sc[1] = signed weight
	// m_vc[0] .. m_vc[2] = unit 3D vector basis for attitude
	// ************* END format of round ***************

	m_pt[0] = vectorToE3GA(_vectorE3GA(location));
	m_sc[0] = sqrt(fabs(radius2)) * ((radius2 < 0) ? -1.0f : 1.0f);
	m_sc[1] = weight;

	// factor attitude:
	if ((Agrade == 4) || (Agrade == 1)) { 
		// (dual) sphere 
		m_vc[0] = e3ga::_vector(e3ga::e1);
		m_vc[1] = e3ga::_vector(e3ga::e2);
		m_vc[2] = e3ga::_vector(e3ga::e3);
	}
	else if (Agrade == 2) {
//		printf("att = %s,\n", attitude.c_str());
		// point pair
		m_vc[0] = vectorToE3GA(_vectorE3GA(unit_e(lcont(no, attitude))));
//		printf("vc = %s,\n", m_vc[0].c_str());
	}
	else if (Agrade == 3) {
		// circle
		// explicit factorization required:
		dualSphere factor[5];
		const int gradeOfBlade = 2;
		mv::Float scale = factorizeBlade(reverse(lcont(no, reverse(attitude))), factor, gradeOfBlade);
		m_vc[0] = vectorToE3GA(_vectorE3GA(factor[0]));
		m_vc[1] = vectorToE3GA(_vectorE3GA(factor[1]));
	}

	switch (Agrade) {
		case 1:
			// dual sphere
            m_type[3] = SPHERE;
			m_flags ^= FLAG_DUAL;
			break;
		case 2:
            m_type[3] = POINT_PAIR;
			break;
		case 3:
            m_type[3] = CIRCLE;
			break;
		case 4:
            m_type[3] = SPHERE;
			break;
	}

}

void mvAnalysis::analyzeTangent(const mv &X, int intFlags /* = 0 */, double epsilon /* = DEFAULT_EPSILON */) {

	m_type[2] = TANGENT;


	int Agrade = m_mvType.m_grade;

	// free N-vector
	mv attitude = negate(op(lcont(ni, X), ni)); 

	// _location is normalized dual sphere
	mv _location = gp(X, inverse(lcont(ni, X))); 
	_location = gp(_location, inverse(-_Float(scp(ni, _location))));
	// location:
	normalizedPoint location = c3gaPoint(_vectorE3GA(_location));

	mv::Float weight = sqrt(_Float(norm_e(ni << X)));

	// ************* format of tangent ***************
	// m_pt[0] = location
	// m_vc[0] .. m_vc[2] = unit 3D vector basis for attitude
	// m_sc[0] = weight
	// ************* END format of tangent ***************
	m_pt[0] = vectorToE3GA(_vectorE3GA(location));
	m_sc[0] = weight;

	// factor attitude:
	if (Agrade == 4) { 
		// T trivector
		m_vc[0] = e3ga::e1;
		m_vc[1] = e3ga::e2;
		m_vc[2] = e3ga::e3;
	}
	else if (Agrade == 2) {
		// T vector
		m_vc[0] = vectorToE3GA(_vectorE3GA(unit_e(lcont(no, attitude))));
	}
	else if (Agrade == 3) {
		// T bivector
		// explicit factorization required:
		dualSphere factor[5];
		int gradeOfBlade = 2;
		mv::Float scale = factorizeBlade(reverse(lcont(no, reverse(attitude))), factor, gradeOfBlade);
		m_vc[0] = vectorToE3GA(_vectorE3GA(factor[0]));
		m_vc[1] = vectorToE3GA(_vectorE3GA(factor[1]));
		m_vc[2] = _vector(dual(m_vc[0] ^ m_vc[1]));
	}

	switch (Agrade) {
		case 1:
			// point
            m_type[3] = SCALAR;
			break;
		case 2:
            m_type[3] = VECTOR;
			break;
		case 3:
            m_type[3] = BIVECTOR;
			break;
		case 4:
            m_type[3] = TRIVECTOR;
			break;
	}


}

void mvAnalysis::analyzeFlat(const mv &X, const normalizedPoint &probe, int intFlags /* = 0 */, double epsilon /* = DEFAULT_EPSILON */) {
	using namespace c3ga;

	m_type[2] = FLAT;
	int Agrade = m_mvType.m_grade;

	// free N-vector
	mv attitude = negate(lcont(ni, X)); 
//	printf("att = %s,\n", attitude.c_str_e20());

	// _location is normalized dual sphere
	mv _location = lcont(lcont(probe, X), inverse(X)); 
	_location = gp(_location, inverse(-_Float(scp(ni, _location))));
	// location:
	normalizedPoint location = c3gaPoint(_vectorE3GA(_location));

//	printf("loc = %s,\n", location.c_str_e20());

	mv::Float weight = (Agrade == 1) ? -_Float(scp(X, no))  : fabs(_Float(norm_r(X)));


	// ************* format of flat ***************
	// m_pt[0] = location
	// m_vc[0] .. m_vc[1] = unit 3D vector basis for attitude
	// m_sc[0] = weight 
	// ************* END format of flat ***************
	m_pt[0] = vectorToE3GA(_vectorE3GA(location));
	m_sc[0] = weight;

	// factor attitude:
	if (Agrade == 4) { 
		// plane
		// explicit factorization required:
		dualSphere factor[5];
		const int gradeOfBlade = 2;
		double scale = factorizeBlade(reverse(lcont(no, reverse(attitude))), factor, gradeOfBlade);
		m_vc[0] = vectorToE3GA(_vectorE3GA(factor[0]));
		m_vc[1] = vectorToE3GA(_vectorE3GA(factor[1]));
		m_vc[2] = _vector(dual(m_vc[0] ^ m_vc[1]));
//		printf("vc0 = %s,\n", (m_vc[0] ^ ni).c_str_e20());
//		printf("vc1 = %s,\n", (m_vc[1] ^ ni).c_str_e20());
	}
	else if (Agrade == 3) {
		// line
		m_vc[0] = vectorToE3GA(_vectorE3GA(unit_e(lcont(no, attitude))));
//		printf("vc0 = %s,\n", (m_vc[0] ^ ni).c_str_e20());
	}
	// flat point and flat scalar have no attitude


	switch (Agrade) {
		case 1:
            m_type[3] = SCALAR;
			break;
		case 2:
            m_type[3] = POINT;
			break;
		case 3:
            m_type[3] = LINE;
			break;
		case 4:
            m_type[3] = PLANE;
			break;
	}
}

void mvAnalysis::analyzeFree(const mv &X, int intFlags /* = 0 */, double epsilon /* = DEFAULT_EPSILON */) {
	using namespace c3ga;

	m_type[2] = FREE;
	int Agrade = m_mvType.m_grade;

	const mv &attitude = X;
	float weight = _Float(norm_e(X));

	// ************* format of free ***************
	// m_pt[0] = no (or probe?)
	// m_vc[0] .. m_vc[2] = unit 3D vector basis for attitude
	// m_sc[0] = weight 
	// ************* END format of free ***************

	m_pt[0] = e3ga::vector();
	m_sc[0] = weight;

	// factor attitude:
	if (Agrade == 4) { 
		// F trivector
		m_vc[0] = e3ga::e1;
		m_vc[1] = e3ga::e2;
		m_vc[2] = e3ga::e3;
	}
	else if (Agrade == 2) {
		// F vector
		m_vc[0] = vectorToE3GA(_vectorE3GA(unit_e(lcont(no, attitude))));
	}
	else if (Agrade == 3) {
		// F bivector
		// explicit factorization required:
		dualSphere factor[5];
		int gradeOfBlade = 2;
		double scale = factorizeBlade(reverse(lcont(no, reverse(attitude))), factor, gradeOfBlade);
		m_vc[0] = vectorToE3GA(_vectorE3GA(factor[0]));
		m_vc[1] = vectorToE3GA(_vectorE3GA(factor[1]));
		m_vc[2] = _vector(dual(m_vc[0] ^ m_vc[1]));
	}

	switch (Agrade) {
		case 1:
            m_type[3] = SCALAR;
			break;
		case 2:
            m_type[3] = VECTOR;
			break;
		case 3:
            m_type[3] = BIVECTOR;
			break;
		case 4:
            m_type[3] = TRIVECTOR;
			break;
	}

}

} /** end of namespace mv_analyze */
