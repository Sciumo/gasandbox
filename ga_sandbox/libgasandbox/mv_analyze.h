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

#ifndef _MV_ANALYZE_H_
#define _MV_ANALYZE_H_

#include "e2ga.h"
#include "e3ga.h"
#include "h3ga.h"

namespace mv_analyze {

const double DEFAULT_EPSILON = 1e-5; ///< rather arbitrary default epsilon used during analysis

class mvAnalysis {
protected:
	static const int NB_POINTS = 3;
	static const int NB_VECTORS = 3;
	static const int NB_SCALARS = 3;
	static const int NB_TYPE_LEVELS = 4;

public:
	// flags:
	static const int FLAG_VALID = 1;
	static const int FLAG_DUAL = 2;

	// models:
	static const int VECTOR_SPACE_MODEL = 1;
	static const int HOMOGENEOUS_MODEL = 2;
	static const int CONFORMAL_MODEL = 3;

	// conformal model types:
	// types:
	static const int INVALID_TYPE = -1;
	static const int MULTIVECTOR = e3ga::mvType::MULTIVECTOR;
	static const int VERSOR = e3ga::mvType::VERSOR;
	static const int BLADE = e3ga::mvType::BLADE;

	// blade classes for Conformal Model
	static const int SCALAR = 0;
	static const int FLAT = 1;
	static const int ROUND = 2;
	static const int TANGENT = 3;
	static const int FREE = 4;
	static const int ZERO = 5;

	// FLATs:
	//static const int SCALAR = 0; // is shared with Conformal Model blade classes
	static const int POINT = 1; // is shared with ROUNDS
	static const int LINE = 2;
	static const int PLANE = 3;

	// ROUNDs
	static const int POINT_PAIR = 2;
	static const int CIRCLE = 3;
	static const int SPHERE = 4;

	// FREEs and TANGENTs
	// NOTE: a conformal point is a TANGENT SCALAR!
	//static const int SCALAR = 0; // is shared with Conformal Model blade classes
	static const int VECTOR = 1;
	static const int BIVECTOR = 2;
	static const int TRIVECTOR = 3;

	// extra vector space constants:
	static const int NOT_USED = 0; // used as m_type[2] for vector space model

	// used for  vector space versors (m_type[3]:
	static const int EVEN_VERSOR = 0;
	static const int ODD_VERSOR = 1;

public:
	mvAnalysis();
	/** intFlags can be FLAG_DUAL for dual intepretation */
/*	mvAnalysis(const mv &X, int intFlags = 0, double epsilon = DEFAULT_EPSILON, 
		const normalizedPoint &probe = _normalizedPoint(no));*/
	mvAnalysis(const e2ga::mv &X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);
	mvAnalysis(const e3ga::mv &X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);
	mvAnalysis(const h3ga::mv &X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);
	mvAnalysis(const mvAnalysis &I);
	virtual ~mvAnalysis();

	mvAnalysis &operator=(const mvAnalysis &I);


	/** intFlags can be FLAG_DUAL for dual intepretation */
	void analyze(e2ga::mv X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);
	void analyze(e3ga::mv X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);
	void analyze(h3ga::mv X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);
//	void analyze(mv X, int intFlags = 0, double epsilon = DEFAULT_EPSILON, const normalizedPoint &probe = _normalizedPoint(no));

	std::string toString() const;


	// these retrieve m_type[x]
	inline int model() const {return m_type[0];}
	inline int type() const {return m_type[1];}
	inline int bladeClass() const {return m_type[2];}
	inline int bladeSubclass() const {return m_type[3];}
	inline int versorSubclass() const {return bladeSubclass();}


	inline bool isa(int t0) const {
		return (m_type[0] == t0);
	}
	inline bool isa(int t0, int t1) const {
		return ((m_type[0] == t0) && (m_type[1] == t1));
	}
	inline bool isa(int t0, int t1, int t2) const {
		return ((m_type[0] == t0) && (m_type[1] == t1) && (m_type[2] == t2));
	}
	inline bool isa(int t0, int t1, int t2, int t3) const {
		return ((m_type[0] == t0) && (m_type[1] == t1) && (m_type[2] == t2) && (m_type[3] == t3));
	}

	inline const bool isValid() const {return ((m_flags & FLAG_VALID) != 0);}
	inline const bool isDual() const {return ((m_flags & FLAG_DUAL) != 0);}

	inline const bool isBlade() const {return (type() == BLADE);}
	inline const bool isVersor() const {return (type() == VERSOR);}
	inline const bool isNull() const {return ((type() == BLADE) && (bladeClass() == ZERO));}
	inline const bool isZero() const {return ((type() == BLADE) && (bladeClass() == ZERO));}

	/*
	Each analyzed multivector is decomposed into
	(analysis dependent) points, vectors and scalars.
	*/

	/// points
	e3ga::vector m_pt[NB_POINTS];
	/// vectors
	e3ga::vector m_vc[NB_VECTORS];
	/// scalars:
	e3ga::mv::Float m_sc[NB_SCALARS];

	/**
	Intended use:
	m_type[0] = model 
	m_type[1] = multivector type (c3ga_type::BLADE, c3ga_type::VERSOR, c3ga_type::MULTIVECTOR,)
	m_type[2] = class (round, flat, free, etc)
	m_type[3] = grade / class dependent 
	*/
	int m_type[NB_TYPE_LEVELS];

	/**
	Flags like 'DUAL'
	*/
	unsigned int m_flags;

	/** epsilon used during analysis */
	double m_epsilon;

	/** multivector type (is it a blade, versor, grade, parity) */
	mvTypeBase m_mvType;


protected:
	/** called by analyze to analyze rounds */
//	void analyzeRound(const mv &X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);
	/** called by analyze to tangents */
//	void analyzeTangent(const mv &X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);

	/** called by analyze to analyze flats (you must supply a 'probe' relative to which positions are determined)*/
//	void analyzeFlat(const mv &X, const mv &probe, int intFlags = 0, double epsilon = DEFAULT_EPSILON);
	/** called by analyze to analyze free blades */
//	void analyzeFree(const mv &X, int intFlags = 0, double epsilon = DEFAULT_EPSILON);

	inline int getAnalysisGrade(int topGrade) const {
		if (m_flags & FLAG_DUAL) {
			return topGrade - m_mvType.m_grade;
		}
		else return m_mvType.m_grade;
	}

};


} // end of namespace mv_analyze

#endif /* _MV_ANALYZE_H_ */
