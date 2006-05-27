
// Generated on 2006-05-27 15:46:13 by G2 0.1 from 'E:\ga\ga_sandbox\libgasandbox\c3ga.gs2'

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

#include <stdio.h>
#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include <string>

	#include "mvtypebase.h"

	// pre_h_include


	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>

	#ifndef _GA_c3ga_h_H_
	#define _GA_c3ga_h_H_

	namespace c3ga {

	// multivector types:
	enum g2Type {
		MVT_NONE = -1,
			MVT_NO_T = 10,
			MVT_E1_T = 11,
			MVT_E2_T = 12,
			MVT_E3_T = 13,
			MVT_NI_T = 14,
			MVT_SCALAR = 15,
			MVT_POINT = 16,
			MVT_NORMALIZEDPOINT = 17,
			MVT_FLATPOINT = 18,
			MVT_NORMALIZEDFLATPOINT = 19,
			MVT_POINTPAIR = 20,
			MVT_LINE = 21,
			MVT_DUALLINE = 22,
			MVT_PLANE = 23,
			MVT_DUALPLANE = 24,
			MVT_CIRCLE = 25,
			MVT_SPHERE = 26,
			MVT_DUALSPHERE = 27,
			MVT_NORMALIZEDSPHERE = 28,
			MVT_NORMALIZEDDUALSPHERE = 29,
			MVT_FREEVECTOR = 30,
			MVT_FREEBIVECTOR = 31,
			MVT_FREETRIVECTOR = 32,
			MVT_TANGENTVECTOR = 33,
			MVT_TANGENTBIVECTOR = 34,
			MVT_VECTORE2GA = 35,
			MVT_VECTORE3GA = 36,
			MVT_BIVECTORE3GA = 37,
			MVT_TRVERSOR = 38,
			MVT_TRSVERSOR = 39,
			MVT_EVENVERSOR = 40,
			MVT_TRANSLATOR = 41,
			MVT_NORMALIZEDTRANSLATOR = 42,
			MVT_ROTOR = 43,
			MVT_SCALOR = 44,
			MVT___NO_CT__ = 45,
			MVT___E1_CT__ = 46,
			MVT___E2_CT__ = 47,
			MVT___E3_CT__ = 48,
			MVT___NI_CT__ = 49,
			MVT_MV = 8,
			MVT_LAST = 50 
	};

	// outermorphism types:
	enum omType {
		OMT_NONE = -2,
			OMT_OM = 9,
			OMT_LAST = 50 
	};

	// grade definitions that can be joined using the '|' operator:
	const int GRADE_0 = 1;
	const int GRADE_1 = 2;
	const int GRADE_2 = 4;
	const int GRADE_3 = 8;
	const int GRADE_4 = 16;
	const int GRADE_5 = 32;

	// The dimension of the space:
	extern const int mv_spaceDim;

	// Is the metric of the space Euclidean?
	extern const bool mv_metricEuclidean;

	// This array can be used to lookup the number of coordinates for a grade part of a general multivector
	extern const int mv_gradeSize[6];

	// This array can be used to lookup the number of coordinates based on a grade usage bitmap
	extern const int mv_size[64];

	// This array of ASCIIZ strings contains the names of the basis vectors
	extern const char *mv_basisVectorNames[5];

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'what basis vectors are in the basis element at position [x]?
	extern const int mv_basisElements[32][6];

	// This array of integers contains the 'sign' (even/odd permutation of canonical order) of basis elements in the general multivector
	extern const double mv_basisElementSign[32];

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'at what index do I find basis element [x] (x = basis vector bitmap)?'
	extern const int mv_basisElementIndexByBitmap[32];

	// This array of integers contains the indices of basis elements in the general multivector
	// Use it to answer: 'what basis element do I find at index [x]'?
	extern const int mv_basisElementBitmapByIndex[32];



	/* *************************************************************************** */
	/* *************************** define all classes upfront *************************** */
	/* *************************************************************************** */
	class no_t;
	class e1_t;
	class e2_t;
	class e3_t;
	class ni_t;
	class scalar;
	class point;
	class normalizedPoint;
	class flatPoint;
	class normalizedFlatPoint;
	class pointPair;
	class line;
	class dualLine;
	class plane;
	class dualPlane;
	class circle;
	class sphere;
	class dualSphere;
	class normalizedSphere;
	class normalizedDualSphere;
	class freeVector;
	class freeBivector;
	class freeTrivector;
	class tangentVector;
	class tangentBivector;
	class vectorE2GA;
	class vectorE3GA;
	class bivectorE3GA;
	class TRversor;
	class TRSversor;
	class evenVersor;
	class translator;
	class normalizedTranslator;
	class rotor;
	class scalor;
	class __no_ct__;
	class __e1_ct__;
	class __e2_ct__;
	class __e3_ct__;
	class __ni_ct__;
	class mv;
	class om;




	// exception handling:
	const int MV_EXCEPTION_WARNING = 1;
	const int MV_EXCEPTION_ERROR = 2;
	// Exception mechanism: ignore & pray
	inline void mv_throw_exception(const char *msg, int level) {}

	// You can alter the formatting of 'string()' through this function.
	// 'format' = NULL will give you back the default.
	void mv_setStringFormat(const char *what, const char *format = NULL);

	extern const char *mv_string_fp; /* = \"%2.2f\" */
	extern const char *mv_string_start; /* = \"\" */
	extern const char *mv_string_end; /* = \"\" */
	extern const char *mv_string_mul; /* = \"*\" */
	extern const char *mv_string_wedge; /* = \"^\" */
	extern const char *mv_string_plus; /* = \" + \" */
	extern const char *mv_string_minus; /* = \" - \" */

	// declaration of profiling functions
	namespace g2Profiling {
		void profile(unsigned int funcIdx, unsigned short storageTypeIdx, unsigned short nbArg, 
			unsigned short argType[], int nbReturnType, unsigned short returnType[]);
		void reset();
		void save(const char *filename = "E:\\ga\\ga_sandbox\\libgasandbox\\c3ga.gp2", bool append = true);
		void init(const char *filename = "E:\\ga\\ga_sandbox\\libgasandbox\\c3ga.gp2",
			const char *hostName = "localhost", int port = 7693);
	} // end of namespace g2Profiling



	inline void mv_memcpy(float *to, const float *from, const int nb) {
		memcpy(to, from, sizeof(float) * nb);
	}

	inline void mv_zero(float *ptr, const int nb) {
		memset(ptr, 0, sizeof(float) * nb);
	}

	// a is any number, b is positive number
	inline bool mv_absLessThan(const float a, const float b) {
		return ((a > b) || (a < -b));
	}

	inline float mv_stringToNumber(const char *asciiz) {
		return (float)atof(asciiz);
	}

	void updateCoordinateString(const mv &x, char **cs, size_t &csl);
	char *c_str(const mv &  obj, const char *fp = NULL);
	std::string toString(const mv &  obj, const char *fp = NULL);

	inline char *c_str_f(const mv &  obj) {return c_str(obj, "%f");}
	inline char *c_str_e(const mv &  obj) {return c_str(obj, "%e");}
	inline char *c_str_e20(const mv &  obj) {return c_str(obj, "%2.20e");}

	inline std::string toString_f(const mv &  obj) {return toString(obj, "%f");}
	inline std::string toString_e(const mv &  obj) {return toString(obj, "%e");}
	inline std::string toString_e20(const mv &  obj) {return toString(obj, "%2.20e");}


	class mv {
		// the friend classes of mv 
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		// friend functions of mv 
		friend char *string(const mv &obj, char *str, int maxLength, const char *fp /*= NULL*/);
		friend void compress(const float *c, float *cc, int &cgu, float epsilon = 0.0, int gu = 63);
		friend mv compress(const mv & arg, float epsilon);

		public:
			typedef float Float;

		/// zero constructor
		inline mv () {

			set();
		}

		/// copy constructor (MUST PASS BY REFERENCE)
		inline mv(const mv &arg1) {

			set(arg1);
		}

		/// scalar constructor
		inline mv(Float scalar) {

			set(scalar);
		}

		/// pointer to coordinates constructor
		inline mv(unsigned int gradeUsage, const Float *coordinates) {

			set(gradeUsage, coordinates);
		}

		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0) {

			set(gradeUsage
				, c0);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1) {

			set(gradeUsage
				, c0, c1);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2) {

			set(gradeUsage
				, c0, c1, c2);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3) {

			set(gradeUsage
				, c0, c1, c2, c3);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4) {

			set(gradeUsage
				, c0, c1, c2, c3, c4);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27, c28);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27, c28, c29);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29, Float c30) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27, c28, c29, c30);
		}
		/// all 'coordinates specified' constructors
		inline mv(unsigned int gradeUsage
		, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29, Float c30, Float c31) {

			set(gradeUsage
				, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27, c28, c29, c30, c31);
		}

		/// init from no_t constructor
		inline mv(const no_t &arg1) {
			set(arg1);
		}
		/// init from e1_t constructor
		inline mv(const e1_t &arg1) {
			set(arg1);
		}
		/// init from e2_t constructor
		inline mv(const e2_t &arg1) {
			set(arg1);
		}
		/// init from e3_t constructor
		inline mv(const e3_t &arg1) {
			set(arg1);
		}
		/// init from ni_t constructor
		inline mv(const ni_t &arg1) {
			set(arg1);
		}
		/// init from scalar constructor
		inline mv(const scalar &arg1) {
			set(arg1);
		}
		/// init from point constructor
		inline mv(const point &arg1) {
			set(arg1);
		}
		/// init from normalizedPoint constructor
		inline mv(const normalizedPoint &arg1) {
			set(arg1);
		}
		/// init from flatPoint constructor
		inline mv(const flatPoint &arg1) {
			set(arg1);
		}
		/// init from normalizedFlatPoint constructor
		inline mv(const normalizedFlatPoint &arg1) {
			set(arg1);
		}
		/// init from pointPair constructor
		inline mv(const pointPair &arg1) {
			set(arg1);
		}
		/// init from line constructor
		inline mv(const line &arg1) {
			set(arg1);
		}
		/// init from dualLine constructor
		inline mv(const dualLine &arg1) {
			set(arg1);
		}
		/// init from plane constructor
		inline mv(const plane &arg1) {
			set(arg1);
		}
		/// init from dualPlane constructor
		inline mv(const dualPlane &arg1) {
			set(arg1);
		}
		/// init from circle constructor
		inline mv(const circle &arg1) {
			set(arg1);
		}
		/// init from sphere constructor
		inline mv(const sphere &arg1) {
			set(arg1);
		}
		/// init from dualSphere constructor
		inline mv(const dualSphere &arg1) {
			set(arg1);
		}
		/// init from normalizedSphere constructor
		inline mv(const normalizedSphere &arg1) {
			set(arg1);
		}
		/// init from normalizedDualSphere constructor
		inline mv(const normalizedDualSphere &arg1) {
			set(arg1);
		}
		/// init from freeVector constructor
		inline mv(const freeVector &arg1) {
			set(arg1);
		}
		/// init from freeBivector constructor
		inline mv(const freeBivector &arg1) {
			set(arg1);
		}
		/// init from freeTrivector constructor
		inline mv(const freeTrivector &arg1) {
			set(arg1);
		}
		/// init from tangentVector constructor
		inline mv(const tangentVector &arg1) {
			set(arg1);
		}
		/// init from tangentBivector constructor
		inline mv(const tangentBivector &arg1) {
			set(arg1);
		}
		/// init from vectorE2GA constructor
		inline mv(const vectorE2GA &arg1) {
			set(arg1);
		}
		/// init from vectorE3GA constructor
		inline mv(const vectorE3GA &arg1) {
			set(arg1);
		}
		/// init from bivectorE3GA constructor
		inline mv(const bivectorE3GA &arg1) {
			set(arg1);
		}
		/// init from TRversor constructor
		inline mv(const TRversor &arg1) {
			set(arg1);
		}
		/// init from TRSversor constructor
		inline mv(const TRSversor &arg1) {
			set(arg1);
		}
		/// init from evenVersor constructor
		inline mv(const evenVersor &arg1) {
			set(arg1);
		}
		/// init from translator constructor
		inline mv(const translator &arg1) {
			set(arg1);
		}
		/// init from normalizedTranslator constructor
		inline mv(const normalizedTranslator &arg1) {
			set(arg1);
		}
		/// init from rotor constructor
		inline mv(const rotor &arg1) {
			set(arg1);
		}
		/// init from scalor constructor
		inline mv(const scalor &arg1) {
			set(arg1);
		}
		/// init from __no_ct__ constructor
		inline mv(const __no_ct__ &arg1) {
			set(arg1);
		}
		/// init from __e1_ct__ constructor
		inline mv(const __e1_ct__ &arg1) {
			set(arg1);
		}
		/// init from __e2_ct__ constructor
		inline mv(const __e2_ct__ &arg1) {
			set(arg1);
		}
		/// init from __e3_ct__ constructor
		inline mv(const __e3_ct__ &arg1) {
			set(arg1);
		}
		/// init from __ni_ct__ constructor
		inline mv(const __ni_ct__ &arg1) {
			set(arg1);
		}


		/// set to null
		void set();

		/// set to copy
		void set(const mv &arg1);

		/// set to scalar
		void set(Float scalar);

		/// pointer to coordinates constructor
		void set(unsigned int gradeUsage, const Float *coordinates);


		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29, Float c30);
		/// set to 'coordinates specified' 
		void set (unsigned int gradeUsage
			, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29, Float c30, Float c31);


		/// set to no_t 
		void set(const no_t &arg1);
		/// set to e1_t 
		void set(const e1_t &arg1);
		/// set to e2_t 
		void set(const e2_t &arg1);
		/// set to e3_t 
		void set(const e3_t &arg1);
		/// set to ni_t 
		void set(const ni_t &arg1);
		/// set to scalar 
		void set(const scalar &arg1);
		/// set to point 
		void set(const point &arg1);
		/// set to normalizedPoint 
		void set(const normalizedPoint &arg1);
		/// set to flatPoint 
		void set(const flatPoint &arg1);
		/// set to normalizedFlatPoint 
		void set(const normalizedFlatPoint &arg1);
		/// set to pointPair 
		void set(const pointPair &arg1);
		/// set to line 
		void set(const line &arg1);
		/// set to dualLine 
		void set(const dualLine &arg1);
		/// set to plane 
		void set(const plane &arg1);
		/// set to dualPlane 
		void set(const dualPlane &arg1);
		/// set to circle 
		void set(const circle &arg1);
		/// set to sphere 
		void set(const sphere &arg1);
		/// set to dualSphere 
		void set(const dualSphere &arg1);
		/// set to normalizedSphere 
		void set(const normalizedSphere &arg1);
		/// set to normalizedDualSphere 
		void set(const normalizedDualSphere &arg1);
		/// set to freeVector 
		void set(const freeVector &arg1);
		/// set to freeBivector 
		void set(const freeBivector &arg1);
		/// set to freeTrivector 
		void set(const freeTrivector &arg1);
		/// set to tangentVector 
		void set(const tangentVector &arg1);
		/// set to tangentBivector 
		void set(const tangentBivector &arg1);
		/// set to vectorE2GA 
		void set(const vectorE2GA &arg1);
		/// set to vectorE3GA 
		void set(const vectorE3GA &arg1);
		/// set to bivectorE3GA 
		void set(const bivectorE3GA &arg1);
		/// set to TRversor 
		void set(const TRversor &arg1);
		/// set to TRSversor 
		void set(const TRSversor &arg1);
		/// set to evenVersor 
		void set(const evenVersor &arg1);
		/// set to translator 
		void set(const translator &arg1);
		/// set to normalizedTranslator 
		void set(const normalizedTranslator &arg1);
		/// set to rotor 
		void set(const rotor &arg1);
		/// set to scalor 
		void set(const scalor &arg1);
		/// set to __no_ct__ 
		void set(const __no_ct__ &arg1);
		/// set to __e1_ct__ 
		void set(const __e1_ct__ &arg1);
		/// set to __e2_ct__ 
		void set(const __e2_ct__ &arg1);
		/// set to __e3_ct__ 
		void set(const __e3_ct__ &arg1);
		/// set to __ni_ct__ 
		void set(const __ni_ct__ &arg1);


		/// assign copy
		mv &operator=(const mv &arg1);

		/// assign scalar
		mv &operator=(Float scalar);

		/// assign no_t 
		mv&operator=(const no_t& arg1);
		/// assign e1_t 
		mv&operator=(const e1_t& arg1);
		/// assign e2_t 
		mv&operator=(const e2_t& arg1);
		/// assign e3_t 
		mv&operator=(const e3_t& arg1);
		/// assign ni_t 
		mv&operator=(const ni_t& arg1);
		/// assign scalar 
		mv&operator=(const scalar& arg1);
		/// assign point 
		mv&operator=(const point& arg1);
		/// assign normalizedPoint 
		mv&operator=(const normalizedPoint& arg1);
		/// assign flatPoint 
		mv&operator=(const flatPoint& arg1);
		/// assign normalizedFlatPoint 
		mv&operator=(const normalizedFlatPoint& arg1);
		/// assign pointPair 
		mv&operator=(const pointPair& arg1);
		/// assign line 
		mv&operator=(const line& arg1);
		/// assign dualLine 
		mv&operator=(const dualLine& arg1);
		/// assign plane 
		mv&operator=(const plane& arg1);
		/// assign dualPlane 
		mv&operator=(const dualPlane& arg1);
		/// assign circle 
		mv&operator=(const circle& arg1);
		/// assign sphere 
		mv&operator=(const sphere& arg1);
		/// assign dualSphere 
		mv&operator=(const dualSphere& arg1);
		/// assign normalizedSphere 
		mv&operator=(const normalizedSphere& arg1);
		/// assign normalizedDualSphere 
		mv&operator=(const normalizedDualSphere& arg1);
		/// assign freeVector 
		mv&operator=(const freeVector& arg1);
		/// assign freeBivector 
		mv&operator=(const freeBivector& arg1);
		/// assign freeTrivector 
		mv&operator=(const freeTrivector& arg1);
		/// assign tangentVector 
		mv&operator=(const tangentVector& arg1);
		/// assign tangentBivector 
		mv&operator=(const tangentBivector& arg1);
		/// assign vectorE2GA 
		mv&operator=(const vectorE2GA& arg1);
		/// assign vectorE3GA 
		mv&operator=(const vectorE3GA& arg1);
		/// assign bivectorE3GA 
		mv&operator=(const bivectorE3GA& arg1);
		/// assign TRversor 
		mv&operator=(const TRversor& arg1);
		/// assign TRSversor 
		mv&operator=(const TRSversor& arg1);
		/// assign evenVersor 
		mv&operator=(const evenVersor& arg1);
		/// assign translator 
		mv&operator=(const translator& arg1);
		/// assign normalizedTranslator 
		mv&operator=(const normalizedTranslator& arg1);
		/// assign rotor 
		mv&operator=(const rotor& arg1);
		/// assign scalor 
		mv&operator=(const scalor& arg1);
		/// assign __no_ct__ 
		mv&operator=(const __no_ct__& arg1);
		/// assign __e1_ct__ 
		mv&operator=(const __e1_ct__& arg1);
		/// assign __e2_ct__ 
		mv&operator=(const __e2_ct__& arg1);
		/// assign __e3_ct__ 
		mv&operator=(const __e3_ct__& arg1);
		/// assign __ni_ct__ 
		mv&operator=(const __ni_ct__& arg1);


		void compress(Float epsilon = 0.0);
		inline Float const *nullFloats() const {
			static Float *nf = NULL;
			if (nf == NULL) nf = new Float[32];
			return nf;
		}
		void expand(const Float *ptrs[], bool nulls = true) const;
		/// returns the absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;


		/// coordinate extraction by name
		inline Float no() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 0];
			else return (float)0.0;
		}
		inline Float e1() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 1];
			else return (float)0.0;
		}
		inline Float e2() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 2];
			else return (float)0.0;
		}
		inline Float e3() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 3];
			else return (float)0.0;
		}
		inline Float ni() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 4];
			else return (float)0.0;
		}
		inline Float noe1() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 0];
			else return (float)0.0;
		}
		inline Float noe2() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 1];
			else return (float)0.0;
		}
		inline Float noe3() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 2];
			else return (float)0.0;
		}
		inline Float e1e2() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 3];
			else return (float)0.0;
		}
		inline Float e2e3() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 4];
			else return (float)0.0;
		}
		inline Float e3e1() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 5];
			else return (float)0.0;
		}
		inline Float e1ni() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 6];
			else return (float)0.0;
		}
		inline Float e2ni() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 7];
			else return (float)0.0;
		}
		inline Float e3ni() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 8];
			else return (float)0.0;
		}
		inline Float noni() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 9];
			else return (float)0.0;
		}
		inline Float e2e3ni() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 0];
			else return (float)0.0;
		}
		inline Float e3e1ni() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 1];
			else return (float)0.0;
		}
		inline Float e1e2ni() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 2];
			else return (float)0.0;
		}
		inline Float noe3ni() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 3];
			else return (float)0.0;
		}
		inline Float noe1ni() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 4];
			else return (float)0.0;
		}
		inline Float noe2ni() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 5];
			else return (float)0.0;
		}
		inline Float noe2e3() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 6];
			else return (float)0.0;
		}
		inline Float noe1e3() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 7];
			else return (float)0.0;
		}
		inline Float noe1e2() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 8];
			else return (float)0.0;
		}
		inline Float e1e2e3() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 9];
			else return (float)0.0;
		}
		inline Float e1e2e3ni() const {
			if (gu() & 16)
				return m_c[mv_size[gu() & 15] + 0];
			else return (float)0.0;
		}
		inline Float noe2e3ni() const {
			if (gu() & 16)
				return m_c[mv_size[gu() & 15] + 1];
			else return (float)0.0;
		}
		inline Float noe1nie3() const {
			if (gu() & 16)
				return m_c[mv_size[gu() & 15] + 2];
			else return (float)0.0;
		}
		inline Float noe1e2ni() const {
			if (gu() & 16)
				return m_c[mv_size[gu() & 15] + 3];
			else return (float)0.0;
		}
		inline Float noe1e2e3() const {
			if (gu() & 16)
				return m_c[mv_size[gu() & 15] + 4];
			else return (float)0.0;
		}
		inline Float noe1e2e3ni() const {
			if (gu() & 32)
				return m_c[mv_size[gu() & 31] + 0];
			else return (float)0.0;
		}

		// coordinate storage, grade usage
		Float m_c[32]; ///< coordinate storage
		unsigned int m_gu; ///< grade usage
		inline unsigned int gu() const {return m_gu;}
		inline void gu(unsigned int g) {m_gu = g;}



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}
		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}
		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}



	}; // end of class mv 

	char *string(const mv & obj, char *str, int maxLength, const char *fp = NULL);
	// this function should be deprecated (conflicts with C++ stdlib)
	char *string(const mv & obj, const char *fp = NULL);


	mv mv_compress(const float *coordinates, float epsilon = (float)0.0, int gu = 32 * 2 -1);


	// underscore 'constructors' for float types:

	/// returns scalar part of arg1 as float
	inline float _float(const mv & arg1) {
		return (arg1.m_gu & 1) ? (float)arg1.m_c[0] : 0.0f;
	}
	/// returns scalar part of arg1 as double
	inline double _double(const mv & arg1) {
		return (arg1.m_gu & 1) ? (double)arg1.m_c[0] : 0.0;
	}
	/// returns scalar part of arg1 as Float
	inline float _Float(const mv & arg1) {
		return (arg1.m_gu & 1) ? arg1.m_c[0] : (float)0.0;
	}

	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline const mv like(const mv &what, const mv &example) {return what;}
	inline mv like(mv &what, const mv &example) {return what;}


	/// enum for the coordinates of no_t 
	enum __no_t_coordinates__ {no_t_no};

	class no_t {
		// the friend classes of no_t 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline no_t() {

			set();
		}

		/// scalar constructor 
		inline no_t(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> no_t	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline no_t(const no_t &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline no_t(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> no_t	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline no_t(__no_t_coordinates__, const Float *coordinates) {

			set(no_t_no, coordinates);
		}

		/// coordinates constructor
		inline no_t(__no_t_coordinates__, Float c_no) {

			set(no_t_no, c_no);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const no_t &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__no_t_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__no_t_coordinates__, Float c_no);

		/// assign copy
		no_t &operator=(const no_t &arg1);

		/// assign general multivector
		no_t &operator=(const mv &arg1);

		/// assign scalar
		no_t &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float no() const {
			return m_c[0];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__no_t_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class no_t 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline no_t _no_t(const mv &arg1) {
		return no_t(arg1, 0);
	}
	/// from const specialization class:
	inline const no_t &_no_t(const no_t &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline no_t &_no_t(no_t &arg1) {
		return arg1;
	}
	/// from Float:
	inline no_t _no_t(no_t::Float arg1) {
		return no_t(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline no_t like(const mv &what, const no_t &example) {return _no_t(what);}
	/// from const specialization class:
	inline const no_t like(const no_t &what, const no_t &example) {return _no_t(what);}
	/// from non-const specialization class:
	inline no_t like(no_t &what, const no_t &example) {return _no_t(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const no_t & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const no_t & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const no_t & v) {
		return (float)0;
	}


	/// enum for the coordinates of e1_t 
	enum __e1_t_coordinates__ {e1_t_e1};

	class e1_t {
		// the friend classes of e1_t 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline e1_t() {

			set();
		}

		/// scalar constructor 
		inline e1_t(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> e1_t	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline e1_t(const e1_t &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline e1_t(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> e1_t	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline e1_t(__e1_t_coordinates__, const Float *coordinates) {

			set(e1_t_e1, coordinates);
		}

		/// coordinates constructor
		inline e1_t(__e1_t_coordinates__, Float c_e1) {

			set(e1_t_e1, c_e1);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const e1_t &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__e1_t_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__e1_t_coordinates__, Float c_e1);

		/// assign copy
		e1_t &operator=(const e1_t &arg1);

		/// assign general multivector
		e1_t &operator=(const mv &arg1);

		/// assign scalar
		e1_t &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1() const {
			return m_c[0];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__e1_t_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class e1_t 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline e1_t _e1_t(const mv &arg1) {
		return e1_t(arg1, 0);
	}
	/// from const specialization class:
	inline const e1_t &_e1_t(const e1_t &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline e1_t &_e1_t(e1_t &arg1) {
		return arg1;
	}
	/// from Float:
	inline e1_t _e1_t(e1_t::Float arg1) {
		return e1_t(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline e1_t like(const mv &what, const e1_t &example) {return _e1_t(what);}
	/// from const specialization class:
	inline const e1_t like(const e1_t &what, const e1_t &example) {return _e1_t(what);}
	/// from non-const specialization class:
	inline e1_t like(e1_t &what, const e1_t &example) {return _e1_t(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const e1_t & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const e1_t & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const e1_t & v) {
		return (float)0;
	}


	/// enum for the coordinates of e2_t 
	enum __e2_t_coordinates__ {e2_t_e2};

	class e2_t {
		// the friend classes of e2_t 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;

		public:
			typedef float Float;

		/// zero constructor
		inline e2_t() {

			set();
		}

		/// scalar constructor 
		inline e2_t(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> e2_t	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline e2_t(const e2_t &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline e2_t(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> e2_t	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline e2_t(__e2_t_coordinates__, const Float *coordinates) {

			set(e2_t_e2, coordinates);
		}

		/// coordinates constructor
		inline e2_t(__e2_t_coordinates__, Float c_e2) {

			set(e2_t_e2, c_e2);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const e2_t &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__e2_t_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__e2_t_coordinates__, Float c_e2);

		/// assign copy
		e2_t &operator=(const e2_t &arg1);

		/// assign general multivector
		e2_t &operator=(const mv &arg1);

		/// assign scalar
		e2_t &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e2() const {
			return m_c[0];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__e2_t_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class e2_t 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline e2_t _e2_t(const mv &arg1) {
		return e2_t(arg1, 0);
	}
	/// from const specialization class:
	inline const e2_t &_e2_t(const e2_t &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline e2_t &_e2_t(e2_t &arg1) {
		return arg1;
	}
	/// from Float:
	inline e2_t _e2_t(e2_t::Float arg1) {
		return e2_t(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline e2_t like(const mv &what, const e2_t &example) {return _e2_t(what);}
	/// from const specialization class:
	inline const e2_t like(const e2_t &what, const e2_t &example) {return _e2_t(what);}
	/// from non-const specialization class:
	inline e2_t like(e2_t &what, const e2_t &example) {return _e2_t(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const e2_t & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const e2_t & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const e2_t & v) {
		return (float)0;
	}


	/// enum for the coordinates of e3_t 
	enum __e3_t_coordinates__ {e3_t_e3};

	class e3_t {
		// the friend classes of e3_t 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline e3_t() {

			set();
		}

		/// scalar constructor 
		inline e3_t(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> e3_t	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline e3_t(const e3_t &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline e3_t(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> e3_t	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline e3_t(__e3_t_coordinates__, const Float *coordinates) {

			set(e3_t_e3, coordinates);
		}

		/// coordinates constructor
		inline e3_t(__e3_t_coordinates__, Float c_e3) {

			set(e3_t_e3, c_e3);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const e3_t &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__e3_t_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__e3_t_coordinates__, Float c_e3);

		/// assign copy
		e3_t &operator=(const e3_t &arg1);

		/// assign general multivector
		e3_t &operator=(const mv &arg1);

		/// assign scalar
		e3_t &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e3() const {
			return m_c[0];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__e3_t_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class e3_t 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline e3_t _e3_t(const mv &arg1) {
		return e3_t(arg1, 0);
	}
	/// from const specialization class:
	inline const e3_t &_e3_t(const e3_t &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline e3_t &_e3_t(e3_t &arg1) {
		return arg1;
	}
	/// from Float:
	inline e3_t _e3_t(e3_t::Float arg1) {
		return e3_t(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline e3_t like(const mv &what, const e3_t &example) {return _e3_t(what);}
	/// from const specialization class:
	inline const e3_t like(const e3_t &what, const e3_t &example) {return _e3_t(what);}
	/// from non-const specialization class:
	inline e3_t like(e3_t &what, const e3_t &example) {return _e3_t(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const e3_t & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const e3_t & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const e3_t & v) {
		return (float)0;
	}


	/// enum for the coordinates of ni_t 
	enum __ni_t_coordinates__ {ni_t_ni};

	class ni_t {
		// the friend classes of ni_t 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline ni_t() {

			set();
		}

		/// scalar constructor 
		inline ni_t(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> ni_t	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline ni_t(const ni_t &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline ni_t(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> ni_t	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline ni_t(__ni_t_coordinates__, const Float *coordinates) {

			set(ni_t_ni, coordinates);
		}

		/// coordinates constructor
		inline ni_t(__ni_t_coordinates__, Float c_ni) {

			set(ni_t_ni, c_ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const ni_t &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__ni_t_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__ni_t_coordinates__, Float c_ni);

		/// assign copy
		ni_t &operator=(const ni_t &arg1);

		/// assign general multivector
		ni_t &operator=(const mv &arg1);

		/// assign scalar
		ni_t &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float ni() const {
			return m_c[0];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__ni_t_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class ni_t 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline ni_t _ni_t(const mv &arg1) {
		return ni_t(arg1, 0);
	}
	/// from const specialization class:
	inline const ni_t &_ni_t(const ni_t &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline ni_t &_ni_t(ni_t &arg1) {
		return arg1;
	}
	/// from Float:
	inline ni_t _ni_t(ni_t::Float arg1) {
		return ni_t(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline ni_t like(const mv &what, const ni_t &example) {return _ni_t(what);}
	/// from const specialization class:
	inline const ni_t like(const ni_t &what, const ni_t &example) {return _ni_t(what);}
	/// from non-const specialization class:
	inline ni_t like(ni_t &what, const ni_t &example) {return _ni_t(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const ni_t & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const ni_t & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const ni_t & v) {
		return (float)0;
	}


	/// enum for the coordinates of scalar 
	enum __scalar_coordinates__ {scalar_scalar};

	class scalar {
		// the friend classes of scalar 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline scalar() {

			set();
		}

		/// scalar constructor 
		inline scalar(Float s) {

			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline scalar(const scalar &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline scalar(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> scalar	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline scalar(__scalar_coordinates__, const Float *coordinates) {

			set(scalar_scalar, coordinates);
		}

		/// coordinates constructor
		inline scalar(__scalar_coordinates__, Float c_scalar) {

			set(scalar_scalar, c_scalar);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const scalar &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__scalar_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__scalar_coordinates__, Float c_scalar);

		/// assign copy
		scalar &operator=(const scalar &arg1);

		/// assign general multivector
		scalar &operator=(const mv &arg1);

		/// assign scalar
		scalar &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__scalar_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class scalar 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline scalar _scalar(const mv &arg1) {
		return scalar(arg1, 0);
	}
	/// from const specialization class:
	inline const scalar &_scalar(const scalar &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline scalar &_scalar(scalar &arg1) {
		return arg1;
	}
	/// from Float:
	inline scalar _scalar(scalar::Float arg1) {
		return scalar(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline scalar like(const mv &what, const scalar &example) {return _scalar(what);}
	/// from const specialization class:
	inline const scalar like(const scalar &what, const scalar &example) {return _scalar(what);}
	/// from non-const specialization class:
	inline scalar like(scalar &what, const scalar &example) {return _scalar(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const scalar & v) {
		return (float)v.m_c[0];
	}
	/// returns scalar part of v as double
	inline double _double(const scalar & v) {
		return (double)v.m_c[0];
	}
	/// returns scalar part of v as Float
	inline float _Float(const scalar & v) {
		return v.m_c[0];
	}


	/// enum for the coordinates of point 
	enum __point_coordinates__ {point_no_e1_e2_e3_ni};

	class point {
		// the friend classes of point 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline point() {

			set();
		}

		/// scalar constructor 
		inline point(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> point	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline point(const point &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline point(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> point	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline point(__point_coordinates__, const Float *coordinates) {

			set(point_no_e1_e2_e3_ni, coordinates);
		}

		/// coordinates constructor
		inline point(__point_coordinates__, Float c_no, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {

			set(point_no_e1_e2_e3_ni, c_no, c_e1, c_e2, c_e3, c_ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const point &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__point_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__point_coordinates__, Float c_no, Float c_e1, Float c_e2, Float c_e3, Float c_ni);

		/// assign copy
		point &operator=(const point &arg1);

		/// assign general multivector
		point &operator=(const mv &arg1);

		/// assign scalar
		point &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float no() const {
			return m_c[0];
		}
		inline Float e1() const {
			return m_c[1];
		}
		inline Float e2() const {
			return m_c[2];
		}
		inline Float e3() const {
			return m_c[3];
		}
		inline Float ni() const {
			return m_c[4];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__point_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[5];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class point 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline point _point(const mv &arg1) {
		return point(arg1, 0);
	}
	/// from const specialization class:
	inline const point &_point(const point &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline point &_point(point &arg1) {
		return arg1;
	}
	/// from Float:
	inline point _point(point::Float arg1) {
		return point(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline point like(const mv &what, const point &example) {return _point(what);}
	/// from const specialization class:
	inline const point like(const point &what, const point &example) {return _point(what);}
	/// from non-const specialization class:
	inline point like(point &what, const point &example) {return _point(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const point & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const point & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const point & v) {
		return (float)0;
	}


	/// enum for the coordinates of normalizedPoint 
	enum __normalizedPoint_coordinates__ {normalizedPoint_e1_e2_e3_ni_nof1_0};

	class normalizedPoint {
		// the friend classes of normalizedPoint 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline normalizedPoint() {

			set();
		}

		/// scalar constructor 
		inline normalizedPoint(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> normalizedPoint	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline normalizedPoint(const normalizedPoint &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline normalizedPoint(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> normalizedPoint	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline normalizedPoint(__normalizedPoint_coordinates__, const Float *coordinates) {

			set(normalizedPoint_e1_e2_e3_ni_nof1_0, coordinates);
		}

		/// coordinates constructor
		inline normalizedPoint(__normalizedPoint_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {

			set(normalizedPoint_e1_e2_e3_ni_nof1_0, c_e1, c_e2, c_e3, c_ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const normalizedPoint &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__normalizedPoint_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__normalizedPoint_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni);

		/// assign copy
		normalizedPoint &operator=(const normalizedPoint &arg1);

		/// assign general multivector
		normalizedPoint &operator=(const mv &arg1);

		/// assign scalar
		normalizedPoint &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1() const {
			return m_c[0];
		}
		inline Float e2() const {
			return m_c[1];
		}
		inline Float e3() const {
			return m_c[2];
		}
		inline Float ni() const {
			return m_c[3];
		}

		/// const coordinate extraction by name
		inline Float no() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__normalizedPoint_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class normalizedPoint 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline normalizedPoint _normalizedPoint(const mv &arg1) {
		return normalizedPoint(arg1, 0);
	}
	/// from const specialization class:
	inline const normalizedPoint &_normalizedPoint(const normalizedPoint &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline normalizedPoint &_normalizedPoint(normalizedPoint &arg1) {
		return arg1;
	}
	/// from Float:
	inline normalizedPoint _normalizedPoint(normalizedPoint::Float arg1) {
		return normalizedPoint(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline normalizedPoint like(const mv &what, const normalizedPoint &example) {return _normalizedPoint(what);}
	/// from const specialization class:
	inline const normalizedPoint like(const normalizedPoint &what, const normalizedPoint &example) {return _normalizedPoint(what);}
	/// from non-const specialization class:
	inline normalizedPoint like(normalizedPoint &what, const normalizedPoint &example) {return _normalizedPoint(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const normalizedPoint & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const normalizedPoint & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const normalizedPoint & v) {
		return (float)0;
	}


	/// enum for the coordinates of flatPoint 
	enum __flatPoint_coordinates__ {flatPoint_e1ni_e2ni_e3ni_noni};

	class flatPoint {
		// the friend classes of flatPoint 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline flatPoint() {

			set();
		}

		/// scalar constructor 
		inline flatPoint(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> flatPoint	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline flatPoint(const flatPoint &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline flatPoint(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> flatPoint	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline flatPoint(__flatPoint_coordinates__, const Float *coordinates) {

			set(flatPoint_e1ni_e2ni_e3ni_noni, coordinates);
		}

		/// coordinates constructor
		inline flatPoint(__flatPoint_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni) {

			set(flatPoint_e1ni_e2ni_e3ni_noni, c_e1ni, c_e2ni, c_e3ni, c_noni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const flatPoint &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__flatPoint_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__flatPoint_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni);

		/// assign copy
		flatPoint &operator=(const flatPoint &arg1);

		/// assign general multivector
		flatPoint &operator=(const mv &arg1);

		/// assign scalar
		flatPoint &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1ni() const {
			return m_c[0];
		}
		inline Float e2ni() const {
			return m_c[1];
		}
		inline Float e3ni() const {
			return m_c[2];
		}
		inline Float noni() const {
			return m_c[3];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__flatPoint_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class flatPoint 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline flatPoint _flatPoint(const mv &arg1) {
		return flatPoint(arg1, 0);
	}
	/// from const specialization class:
	inline const flatPoint &_flatPoint(const flatPoint &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline flatPoint &_flatPoint(flatPoint &arg1) {
		return arg1;
	}
	/// from Float:
	inline flatPoint _flatPoint(flatPoint::Float arg1) {
		return flatPoint(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline flatPoint like(const mv &what, const flatPoint &example) {return _flatPoint(what);}
	/// from const specialization class:
	inline const flatPoint like(const flatPoint &what, const flatPoint &example) {return _flatPoint(what);}
	/// from non-const specialization class:
	inline flatPoint like(flatPoint &what, const flatPoint &example) {return _flatPoint(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const flatPoint & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const flatPoint & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const flatPoint & v) {
		return (float)0;
	}


	/// enum for the coordinates of normalizedFlatPoint 
	enum __normalizedFlatPoint_coordinates__ {normalizedFlatPoint_e1ni_e2ni_e3ni_nonif1_0};

	class normalizedFlatPoint {
		// the friend classes of normalizedFlatPoint 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline normalizedFlatPoint() {

			set();
		}

		/// scalar constructor 
		inline normalizedFlatPoint(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> normalizedFlatPoint	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline normalizedFlatPoint(const normalizedFlatPoint &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline normalizedFlatPoint(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> normalizedFlatPoint	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline normalizedFlatPoint(__normalizedFlatPoint_coordinates__, const Float *coordinates) {

			set(normalizedFlatPoint_e1ni_e2ni_e3ni_nonif1_0, coordinates);
		}

		/// coordinates constructor
		inline normalizedFlatPoint(__normalizedFlatPoint_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni) {

			set(normalizedFlatPoint_e1ni_e2ni_e3ni_nonif1_0, c_e1ni, c_e2ni, c_e3ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const normalizedFlatPoint &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__normalizedFlatPoint_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__normalizedFlatPoint_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni);

		/// assign copy
		normalizedFlatPoint &operator=(const normalizedFlatPoint &arg1);

		/// assign general multivector
		normalizedFlatPoint &operator=(const mv &arg1);

		/// assign scalar
		normalizedFlatPoint &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1ni() const {
			return m_c[0];
		}
		inline Float e2ni() const {
			return m_c[1];
		}
		inline Float e3ni() const {
			return m_c[2];
		}

		/// const coordinate extraction by name
		inline Float noni() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__normalizedFlatPoint_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class normalizedFlatPoint 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline normalizedFlatPoint _normalizedFlatPoint(const mv &arg1) {
		return normalizedFlatPoint(arg1, 0);
	}
	/// from const specialization class:
	inline const normalizedFlatPoint &_normalizedFlatPoint(const normalizedFlatPoint &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline normalizedFlatPoint &_normalizedFlatPoint(normalizedFlatPoint &arg1) {
		return arg1;
	}
	/// from Float:
	inline normalizedFlatPoint _normalizedFlatPoint(normalizedFlatPoint::Float arg1) {
		return normalizedFlatPoint(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline normalizedFlatPoint like(const mv &what, const normalizedFlatPoint &example) {return _normalizedFlatPoint(what);}
	/// from const specialization class:
	inline const normalizedFlatPoint like(const normalizedFlatPoint &what, const normalizedFlatPoint &example) {return _normalizedFlatPoint(what);}
	/// from non-const specialization class:
	inline normalizedFlatPoint like(normalizedFlatPoint &what, const normalizedFlatPoint &example) {return _normalizedFlatPoint(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const normalizedFlatPoint & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const normalizedFlatPoint & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const normalizedFlatPoint & v) {
		return (float)0;
	}


	/// enum for the coordinates of pointPair 
	enum __pointPair_coordinates__ {pointPair_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni};

	class pointPair {
		// the friend classes of pointPair 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline pointPair() {

			set();
		}

		/// scalar constructor 
		inline pointPair(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> pointPair	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline pointPair(const pointPair &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline pointPair(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> pointPair	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline pointPair(__pointPair_coordinates__, const Float *coordinates) {

			set(pointPair_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni, coordinates);
		}

		/// coordinates constructor
		inline pointPair(__pointPair_coordinates__, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni) {

			set(pointPair_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni, c_noe1, c_noe2, c_noe3, c_e1e2, c_e2e3, c_e3e1, c_e1ni, c_e2ni, c_e3ni, c_noni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const pointPair &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__pointPair_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__pointPair_coordinates__, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni);

		/// assign copy
		pointPair &operator=(const pointPair &arg1);

		/// assign general multivector
		pointPair &operator=(const mv &arg1);

		/// assign scalar
		pointPair &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float noe1() const {
			return m_c[0];
		}
		inline Float noe2() const {
			return m_c[1];
		}
		inline Float noe3() const {
			return m_c[2];
		}
		inline Float e1e2() const {
			return m_c[3];
		}
		inline Float e2e3() const {
			return m_c[4];
		}
		inline Float e3e1() const {
			return m_c[5];
		}
		inline Float e1ni() const {
			return m_c[6];
		}
		inline Float e2ni() const {
			return m_c[7];
		}
		inline Float e3ni() const {
			return m_c[8];
		}
		inline Float noni() const {
			return m_c[9];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__pointPair_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[10];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class pointPair 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline pointPair _pointPair(const mv &arg1) {
		return pointPair(arg1, 0);
	}
	/// from const specialization class:
	inline const pointPair &_pointPair(const pointPair &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline pointPair &_pointPair(pointPair &arg1) {
		return arg1;
	}
	/// from Float:
	inline pointPair _pointPair(pointPair::Float arg1) {
		return pointPair(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline pointPair like(const mv &what, const pointPair &example) {return _pointPair(what);}
	/// from const specialization class:
	inline const pointPair like(const pointPair &what, const pointPair &example) {return _pointPair(what);}
	/// from non-const specialization class:
	inline pointPair like(pointPair &what, const pointPair &example) {return _pointPair(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const pointPair & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const pointPair & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const pointPair & v) {
		return (float)0;
	}


	/// enum for the coordinates of line 
	enum __line_coordinates__ {line_e1e2ni_e1e3ni_e2e3ni_e1noni_e2noni_e3noni};

	class line {
		// the friend classes of line 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline line() {

			set();
		}

		/// scalar constructor 
		inline line(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> line	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline line(const line &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline line(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> line	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline line(__line_coordinates__, const Float *coordinates) {

			set(line_e1e2ni_e1e3ni_e2e3ni_e1noni_e2noni_e3noni, coordinates);
		}

		/// coordinates constructor
		inline line(__line_coordinates__, Float c_e1e2ni, Float c_e1e3ni, Float c_e2e3ni, Float c_e1noni, Float c_e2noni, Float c_e3noni) {

			set(line_e1e2ni_e1e3ni_e2e3ni_e1noni_e2noni_e3noni, c_e1e2ni, c_e1e3ni, c_e2e3ni, c_e1noni, c_e2noni, c_e3noni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const line &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__line_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__line_coordinates__, Float c_e1e2ni, Float c_e1e3ni, Float c_e2e3ni, Float c_e1noni, Float c_e2noni, Float c_e3noni);

		/// assign copy
		line &operator=(const line &arg1);

		/// assign general multivector
		line &operator=(const mv &arg1);

		/// assign scalar
		line &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2ni() const {
			return m_c[0];
		}
		inline Float e1e3ni() const {
			return m_c[1];
		}
		inline Float e2e3ni() const {
			return m_c[2];
		}
		inline Float e1noni() const {
			return m_c[3];
		}
		inline Float e2noni() const {
			return m_c[4];
		}
		inline Float e3noni() const {
			return m_c[5];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__line_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[6];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class line 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline line _line(const mv &arg1) {
		return line(arg1, 0);
	}
	/// from const specialization class:
	inline const line &_line(const line &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline line &_line(line &arg1) {
		return arg1;
	}
	/// from Float:
	inline line _line(line::Float arg1) {
		return line(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline line like(const mv &what, const line &example) {return _line(what);}
	/// from const specialization class:
	inline const line like(const line &what, const line &example) {return _line(what);}
	/// from non-const specialization class:
	inline line like(line &what, const line &example) {return _line(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const line & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const line & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const line & v) {
		return (float)0;
	}


	/// enum for the coordinates of dualLine 
	enum __dualLine_coordinates__ {dualLine_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni};

	class dualLine {
		// the friend classes of dualLine 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline dualLine() {

			set();
		}

		/// scalar constructor 
		inline dualLine(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> dualLine	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline dualLine(const dualLine &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline dualLine(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> dualLine	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline dualLine(__dualLine_coordinates__, const Float *coordinates) {

			set(dualLine_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni, coordinates);
		}

		/// coordinates constructor
		inline dualLine(__dualLine_coordinates__, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni) {

			set(dualLine_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni, c_e1e2, c_e1e3, c_e2e3, c_e1ni, c_e2ni, c_e3ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const dualLine &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__dualLine_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__dualLine_coordinates__, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni);

		/// assign copy
		dualLine &operator=(const dualLine &arg1);

		/// assign general multivector
		dualLine &operator=(const mv &arg1);

		/// assign scalar
		dualLine &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2() const {
			return m_c[0];
		}
		inline Float e1e3() const {
			return m_c[1];
		}
		inline Float e2e3() const {
			return m_c[2];
		}
		inline Float e1ni() const {
			return m_c[3];
		}
		inline Float e2ni() const {
			return m_c[4];
		}
		inline Float e3ni() const {
			return m_c[5];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__dualLine_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[6];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class dualLine 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline dualLine _dualLine(const mv &arg1) {
		return dualLine(arg1, 0);
	}
	/// from const specialization class:
	inline const dualLine &_dualLine(const dualLine &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline dualLine &_dualLine(dualLine &arg1) {
		return arg1;
	}
	/// from Float:
	inline dualLine _dualLine(dualLine::Float arg1) {
		return dualLine(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline dualLine like(const mv &what, const dualLine &example) {return _dualLine(what);}
	/// from const specialization class:
	inline const dualLine like(const dualLine &what, const dualLine &example) {return _dualLine(what);}
	/// from non-const specialization class:
	inline dualLine like(dualLine &what, const dualLine &example) {return _dualLine(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const dualLine & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const dualLine & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const dualLine & v) {
		return (float)0;
	}


	/// enum for the coordinates of plane 
	enum __plane_coordinates__ {plane_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni};

	class plane {
		// the friend classes of plane 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline plane() {

			set();
		}

		/// scalar constructor 
		inline plane(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> plane	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline plane(const plane &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline plane(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> plane	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline plane(__plane_coordinates__, const Float *coordinates) {

			set(plane_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni, coordinates);
		}

		/// coordinates constructor
		inline plane(__plane_coordinates__, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni) {

			set(plane_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni, c_e1e2e3ni, c_e1e2noni, c_e1e3noni, c_e2e3noni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const plane &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__plane_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__plane_coordinates__, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni);

		/// assign copy
		plane &operator=(const plane &arg1);

		/// assign general multivector
		plane &operator=(const mv &arg1);

		/// assign scalar
		plane &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2e3ni() const {
			return m_c[0];
		}
		inline Float e1e2noni() const {
			return m_c[1];
		}
		inline Float e1e3noni() const {
			return m_c[2];
		}
		inline Float e2e3noni() const {
			return m_c[3];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__plane_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class plane 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline plane _plane(const mv &arg1) {
		return plane(arg1, 0);
	}
	/// from const specialization class:
	inline const plane &_plane(const plane &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline plane &_plane(plane &arg1) {
		return arg1;
	}
	/// from Float:
	inline plane _plane(plane::Float arg1) {
		return plane(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline plane like(const mv &what, const plane &example) {return _plane(what);}
	/// from const specialization class:
	inline const plane like(const plane &what, const plane &example) {return _plane(what);}
	/// from non-const specialization class:
	inline plane like(plane &what, const plane &example) {return _plane(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const plane & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const plane & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const plane & v) {
		return (float)0;
	}


	/// enum for the coordinates of dualPlane 
	enum __dualPlane_coordinates__ {dualPlane_e1_e2_e3_ni};

	class dualPlane {
		// the friend classes of dualPlane 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline dualPlane() {

			set();
		}

		/// scalar constructor 
		inline dualPlane(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> dualPlane	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline dualPlane(const dualPlane &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline dualPlane(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> dualPlane	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline dualPlane(__dualPlane_coordinates__, const Float *coordinates) {

			set(dualPlane_e1_e2_e3_ni, coordinates);
		}

		/// coordinates constructor
		inline dualPlane(__dualPlane_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {

			set(dualPlane_e1_e2_e3_ni, c_e1, c_e2, c_e3, c_ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const dualPlane &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__dualPlane_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__dualPlane_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni);

		/// assign copy
		dualPlane &operator=(const dualPlane &arg1);

		/// assign general multivector
		dualPlane &operator=(const mv &arg1);

		/// assign scalar
		dualPlane &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1() const {
			return m_c[0];
		}
		inline Float e2() const {
			return m_c[1];
		}
		inline Float e3() const {
			return m_c[2];
		}
		inline Float ni() const {
			return m_c[3];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__dualPlane_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class dualPlane 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline dualPlane _dualPlane(const mv &arg1) {
		return dualPlane(arg1, 0);
	}
	/// from const specialization class:
	inline const dualPlane &_dualPlane(const dualPlane &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline dualPlane &_dualPlane(dualPlane &arg1) {
		return arg1;
	}
	/// from Float:
	inline dualPlane _dualPlane(dualPlane::Float arg1) {
		return dualPlane(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline dualPlane like(const mv &what, const dualPlane &example) {return _dualPlane(what);}
	/// from const specialization class:
	inline const dualPlane like(const dualPlane &what, const dualPlane &example) {return _dualPlane(what);}
	/// from non-const specialization class:
	inline dualPlane like(dualPlane &what, const dualPlane &example) {return _dualPlane(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const dualPlane & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const dualPlane & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const dualPlane & v) {
		return (float)0;
	}


	/// enum for the coordinates of circle 
	enum __circle_coordinates__ {circle_e2e3ni_e3e1ni_e1e2ni_noe3ni_noe1ni_noe2ni_noe2e3_noe1e3_noe1e2_e1e2e3};

	class circle {
		// the friend classes of circle 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline circle() {

			set();
		}

		/// scalar constructor 
		inline circle(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> circle	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline circle(const circle &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline circle(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> circle	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline circle(__circle_coordinates__, const Float *coordinates) {

			set(circle_e2e3ni_e3e1ni_e1e2ni_noe3ni_noe1ni_noe2ni_noe2e3_noe1e3_noe1e2_e1e2e3, coordinates);
		}

		/// coordinates constructor
		inline circle(__circle_coordinates__, Float c_e2e3ni, Float c_e3e1ni, Float c_e1e2ni, Float c_noe3ni, Float c_noe1ni, Float c_noe2ni, Float c_noe2e3, Float c_noe1e3, Float c_noe1e2, Float c_e1e2e3) {

			set(circle_e2e3ni_e3e1ni_e1e2ni_noe3ni_noe1ni_noe2ni_noe2e3_noe1e3_noe1e2_e1e2e3, c_e2e3ni, c_e3e1ni, c_e1e2ni, c_noe3ni, c_noe1ni, c_noe2ni, c_noe2e3, c_noe1e3, c_noe1e2, c_e1e2e3);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const circle &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__circle_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__circle_coordinates__, Float c_e2e3ni, Float c_e3e1ni, Float c_e1e2ni, Float c_noe3ni, Float c_noe1ni, Float c_noe2ni, Float c_noe2e3, Float c_noe1e3, Float c_noe1e2, Float c_e1e2e3);

		/// assign copy
		circle &operator=(const circle &arg1);

		/// assign general multivector
		circle &operator=(const mv &arg1);

		/// assign scalar
		circle &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e2e3ni() const {
			return m_c[0];
		}
		inline Float e3e1ni() const {
			return m_c[1];
		}
		inline Float e1e2ni() const {
			return m_c[2];
		}
		inline Float noe3ni() const {
			return m_c[3];
		}
		inline Float noe1ni() const {
			return m_c[4];
		}
		inline Float noe2ni() const {
			return m_c[5];
		}
		inline Float noe2e3() const {
			return m_c[6];
		}
		inline Float noe1e3() const {
			return m_c[7];
		}
		inline Float noe1e2() const {
			return m_c[8];
		}
		inline Float e1e2e3() const {
			return m_c[9];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__circle_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[10];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class circle 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline circle _circle(const mv &arg1) {
		return circle(arg1, 0);
	}
	/// from const specialization class:
	inline const circle &_circle(const circle &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline circle &_circle(circle &arg1) {
		return arg1;
	}
	/// from Float:
	inline circle _circle(circle::Float arg1) {
		return circle(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline circle like(const mv &what, const circle &example) {return _circle(what);}
	/// from const specialization class:
	inline const circle like(const circle &what, const circle &example) {return _circle(what);}
	/// from non-const specialization class:
	inline circle like(circle &what, const circle &example) {return _circle(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const circle & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const circle & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const circle & v) {
		return (float)0;
	}


	/// enum for the coordinates of sphere 
	enum __sphere_coordinates__ {sphere_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni_e1e2e3no};

	class sphere {
		// the friend classes of sphere 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline sphere() {

			set();
		}

		/// scalar constructor 
		inline sphere(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> sphere	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline sphere(const sphere &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline sphere(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> sphere	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline sphere(__sphere_coordinates__, const Float *coordinates) {

			set(sphere_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni_e1e2e3no, coordinates);
		}

		/// coordinates constructor
		inline sphere(__sphere_coordinates__, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no) {

			set(sphere_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni_e1e2e3no, c_e1e2e3ni, c_e1e2noni, c_e1e3noni, c_e2e3noni, c_e1e2e3no);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const sphere &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__sphere_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__sphere_coordinates__, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no);

		/// assign copy
		sphere &operator=(const sphere &arg1);

		/// assign general multivector
		sphere &operator=(const mv &arg1);

		/// assign scalar
		sphere &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2e3ni() const {
			return m_c[0];
		}
		inline Float e1e2noni() const {
			return m_c[1];
		}
		inline Float e1e3noni() const {
			return m_c[2];
		}
		inline Float e2e3noni() const {
			return m_c[3];
		}
		inline Float e1e2e3no() const {
			return m_c[4];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__sphere_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[5];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class sphere 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline sphere _sphere(const mv &arg1) {
		return sphere(arg1, 0);
	}
	/// from const specialization class:
	inline const sphere &_sphere(const sphere &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline sphere &_sphere(sphere &arg1) {
		return arg1;
	}
	/// from Float:
	inline sphere _sphere(sphere::Float arg1) {
		return sphere(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline sphere like(const mv &what, const sphere &example) {return _sphere(what);}
	/// from const specialization class:
	inline const sphere like(const sphere &what, const sphere &example) {return _sphere(what);}
	/// from non-const specialization class:
	inline sphere like(sphere &what, const sphere &example) {return _sphere(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const sphere & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const sphere & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const sphere & v) {
		return (float)0;
	}


	/// enum for the coordinates of dualSphere 
	enum __dualSphere_coordinates__ {dualSphere_no_e1_e2_e3_ni};

	class dualSphere {
		// the friend classes of dualSphere 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline dualSphere() {

			set();
		}

		/// scalar constructor 
		inline dualSphere(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> dualSphere	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline dualSphere(const dualSphere &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline dualSphere(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> dualSphere	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline dualSphere(__dualSphere_coordinates__, const Float *coordinates) {

			set(dualSphere_no_e1_e2_e3_ni, coordinates);
		}

		/// coordinates constructor
		inline dualSphere(__dualSphere_coordinates__, Float c_no, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {

			set(dualSphere_no_e1_e2_e3_ni, c_no, c_e1, c_e2, c_e3, c_ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const dualSphere &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__dualSphere_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__dualSphere_coordinates__, Float c_no, Float c_e1, Float c_e2, Float c_e3, Float c_ni);

		/// assign copy
		dualSphere &operator=(const dualSphere &arg1);

		/// assign general multivector
		dualSphere &operator=(const mv &arg1);

		/// assign scalar
		dualSphere &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float no() const {
			return m_c[0];
		}
		inline Float e1() const {
			return m_c[1];
		}
		inline Float e2() const {
			return m_c[2];
		}
		inline Float e3() const {
			return m_c[3];
		}
		inline Float ni() const {
			return m_c[4];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__dualSphere_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[5];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class dualSphere 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline dualSphere _dualSphere(const mv &arg1) {
		return dualSphere(arg1, 0);
	}
	/// from const specialization class:
	inline const dualSphere &_dualSphere(const dualSphere &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline dualSphere &_dualSphere(dualSphere &arg1) {
		return arg1;
	}
	/// from Float:
	inline dualSphere _dualSphere(dualSphere::Float arg1) {
		return dualSphere(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline dualSphere like(const mv &what, const dualSphere &example) {return _dualSphere(what);}
	/// from const specialization class:
	inline const dualSphere like(const dualSphere &what, const dualSphere &example) {return _dualSphere(what);}
	/// from non-const specialization class:
	inline dualSphere like(dualSphere &what, const dualSphere &example) {return _dualSphere(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const dualSphere & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const dualSphere & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const dualSphere & v) {
		return (float)0;
	}


	/// enum for the coordinates of normalizedSphere 
	enum __normalizedSphere_coordinates__ {normalizedSphere_e1e2noni_e1e3noni_e2e3noni_e1e2e3no_e1e2e3nif1_0};

	class normalizedSphere {
		// the friend classes of normalizedSphere 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline normalizedSphere() {

			set();
		}

		/// scalar constructor 
		inline normalizedSphere(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> normalizedSphere	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline normalizedSphere(const normalizedSphere &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline normalizedSphere(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> normalizedSphere	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline normalizedSphere(__normalizedSphere_coordinates__, const Float *coordinates) {

			set(normalizedSphere_e1e2noni_e1e3noni_e2e3noni_e1e2e3no_e1e2e3nif1_0, coordinates);
		}

		/// coordinates constructor
		inline normalizedSphere(__normalizedSphere_coordinates__, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no) {

			set(normalizedSphere_e1e2noni_e1e3noni_e2e3noni_e1e2e3no_e1e2e3nif1_0, c_e1e2noni, c_e1e3noni, c_e2e3noni, c_e1e2e3no);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const normalizedSphere &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__normalizedSphere_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__normalizedSphere_coordinates__, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no);

		/// assign copy
		normalizedSphere &operator=(const normalizedSphere &arg1);

		/// assign general multivector
		normalizedSphere &operator=(const mv &arg1);

		/// assign scalar
		normalizedSphere &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2noni() const {
			return m_c[0];
		}
		inline Float e1e3noni() const {
			return m_c[1];
		}
		inline Float e2e3noni() const {
			return m_c[2];
		}
		inline Float e1e2e3no() const {
			return m_c[3];
		}

		/// const coordinate extraction by name
		inline Float e1e2e3ni() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__normalizedSphere_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class normalizedSphere 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline normalizedSphere _normalizedSphere(const mv &arg1) {
		return normalizedSphere(arg1, 0);
	}
	/// from const specialization class:
	inline const normalizedSphere &_normalizedSphere(const normalizedSphere &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline normalizedSphere &_normalizedSphere(normalizedSphere &arg1) {
		return arg1;
	}
	/// from Float:
	inline normalizedSphere _normalizedSphere(normalizedSphere::Float arg1) {
		return normalizedSphere(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline normalizedSphere like(const mv &what, const normalizedSphere &example) {return _normalizedSphere(what);}
	/// from const specialization class:
	inline const normalizedSphere like(const normalizedSphere &what, const normalizedSphere &example) {return _normalizedSphere(what);}
	/// from non-const specialization class:
	inline normalizedSphere like(normalizedSphere &what, const normalizedSphere &example) {return _normalizedSphere(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const normalizedSphere & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const normalizedSphere & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const normalizedSphere & v) {
		return (float)0;
	}


	/// enum for the coordinates of normalizedDualSphere 
	enum __normalizedDualSphere_coordinates__ {normalizedDualSphere_e1_e2_e3_ni_nof1_0};

	class normalizedDualSphere {
		// the friend classes of normalizedDualSphere 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline normalizedDualSphere() {

			set();
		}

		/// scalar constructor 
		inline normalizedDualSphere(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> normalizedDualSphere	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline normalizedDualSphere(const normalizedDualSphere &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline normalizedDualSphere(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> normalizedDualSphere	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline normalizedDualSphere(__normalizedDualSphere_coordinates__, const Float *coordinates) {

			set(normalizedDualSphere_e1_e2_e3_ni_nof1_0, coordinates);
		}

		/// coordinates constructor
		inline normalizedDualSphere(__normalizedDualSphere_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {

			set(normalizedDualSphere_e1_e2_e3_ni_nof1_0, c_e1, c_e2, c_e3, c_ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const normalizedDualSphere &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__normalizedDualSphere_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__normalizedDualSphere_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni);

		/// assign copy
		normalizedDualSphere &operator=(const normalizedDualSphere &arg1);

		/// assign general multivector
		normalizedDualSphere &operator=(const mv &arg1);

		/// assign scalar
		normalizedDualSphere &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1() const {
			return m_c[0];
		}
		inline Float e2() const {
			return m_c[1];
		}
		inline Float e3() const {
			return m_c[2];
		}
		inline Float ni() const {
			return m_c[3];
		}

		/// const coordinate extraction by name
		inline Float no() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__normalizedDualSphere_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class normalizedDualSphere 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline normalizedDualSphere _normalizedDualSphere(const mv &arg1) {
		return normalizedDualSphere(arg1, 0);
	}
	/// from const specialization class:
	inline const normalizedDualSphere &_normalizedDualSphere(const normalizedDualSphere &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline normalizedDualSphere &_normalizedDualSphere(normalizedDualSphere &arg1) {
		return arg1;
	}
	/// from Float:
	inline normalizedDualSphere _normalizedDualSphere(normalizedDualSphere::Float arg1) {
		return normalizedDualSphere(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline normalizedDualSphere like(const mv &what, const normalizedDualSphere &example) {return _normalizedDualSphere(what);}
	/// from const specialization class:
	inline const normalizedDualSphere like(const normalizedDualSphere &what, const normalizedDualSphere &example) {return _normalizedDualSphere(what);}
	/// from non-const specialization class:
	inline normalizedDualSphere like(normalizedDualSphere &what, const normalizedDualSphere &example) {return _normalizedDualSphere(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const normalizedDualSphere & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const normalizedDualSphere & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const normalizedDualSphere & v) {
		return (float)0;
	}


	/// enum for the coordinates of freeVector 
	enum __freeVector_coordinates__ {freeVector_e1ni_e2ni_e3ni};

	class freeVector {
		// the friend classes of freeVector 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline freeVector() {

			set();
		}

		/// scalar constructor 
		inline freeVector(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> freeVector	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline freeVector(const freeVector &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline freeVector(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> freeVector	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline freeVector(__freeVector_coordinates__, const Float *coordinates) {

			set(freeVector_e1ni_e2ni_e3ni, coordinates);
		}

		/// coordinates constructor
		inline freeVector(__freeVector_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni) {

			set(freeVector_e1ni_e2ni_e3ni, c_e1ni, c_e2ni, c_e3ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const freeVector &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__freeVector_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__freeVector_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni);

		/// assign copy
		freeVector &operator=(const freeVector &arg1);

		/// assign general multivector
		freeVector &operator=(const mv &arg1);

		/// assign scalar
		freeVector &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1ni() const {
			return m_c[0];
		}
		inline Float e2ni() const {
			return m_c[1];
		}
		inline Float e3ni() const {
			return m_c[2];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__freeVector_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class freeVector 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline freeVector _freeVector(const mv &arg1) {
		return freeVector(arg1, 0);
	}
	/// from const specialization class:
	inline const freeVector &_freeVector(const freeVector &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline freeVector &_freeVector(freeVector &arg1) {
		return arg1;
	}
	/// from Float:
	inline freeVector _freeVector(freeVector::Float arg1) {
		return freeVector(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline freeVector like(const mv &what, const freeVector &example) {return _freeVector(what);}
	/// from const specialization class:
	inline const freeVector like(const freeVector &what, const freeVector &example) {return _freeVector(what);}
	/// from non-const specialization class:
	inline freeVector like(freeVector &what, const freeVector &example) {return _freeVector(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const freeVector & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const freeVector & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const freeVector & v) {
		return (float)0;
	}


	/// enum for the coordinates of freeBivector 
	enum __freeBivector_coordinates__ {freeBivector_e1e2ni_e2e3ni_e3e1ni};

	class freeBivector {
		// the friend classes of freeBivector 
		friend class mv;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline freeBivector() {

			set();
		}

		/// scalar constructor 
		inline freeBivector(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> freeBivector	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline freeBivector(const freeBivector &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline freeBivector(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> freeBivector	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline freeBivector(__freeBivector_coordinates__, const Float *coordinates) {

			set(freeBivector_e1e2ni_e2e3ni_e3e1ni, coordinates);
		}

		/// coordinates constructor
		inline freeBivector(__freeBivector_coordinates__, Float c_e1e2ni, Float c_e2e3ni, Float c_e3e1ni) {

			set(freeBivector_e1e2ni_e2e3ni_e3e1ni, c_e1e2ni, c_e2e3ni, c_e3e1ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const freeBivector &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__freeBivector_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__freeBivector_coordinates__, Float c_e1e2ni, Float c_e2e3ni, Float c_e3e1ni);

		/// assign copy
		freeBivector &operator=(const freeBivector &arg1);

		/// assign general multivector
		freeBivector &operator=(const mv &arg1);

		/// assign scalar
		freeBivector &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2ni() const {
			return m_c[0];
		}
		inline Float e2e3ni() const {
			return m_c[1];
		}
		inline Float e3e1ni() const {
			return m_c[2];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__freeBivector_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class freeBivector 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline freeBivector _freeBivector(const mv &arg1) {
		return freeBivector(arg1, 0);
	}
	/// from const specialization class:
	inline const freeBivector &_freeBivector(const freeBivector &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline freeBivector &_freeBivector(freeBivector &arg1) {
		return arg1;
	}
	/// from Float:
	inline freeBivector _freeBivector(freeBivector::Float arg1) {
		return freeBivector(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline freeBivector like(const mv &what, const freeBivector &example) {return _freeBivector(what);}
	/// from const specialization class:
	inline const freeBivector like(const freeBivector &what, const freeBivector &example) {return _freeBivector(what);}
	/// from non-const specialization class:
	inline freeBivector like(freeBivector &what, const freeBivector &example) {return _freeBivector(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const freeBivector & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const freeBivector & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const freeBivector & v) {
		return (float)0;
	}


	/// enum for the coordinates of freeTrivector 
	enum __freeTrivector_coordinates__ {freeTrivector_e1e2e3ni};

	class freeTrivector {
		// the friend classes of freeTrivector 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline freeTrivector() {

			set();
		}

		/// scalar constructor 
		inline freeTrivector(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> freeTrivector	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline freeTrivector(const freeTrivector &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline freeTrivector(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> freeTrivector	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline freeTrivector(__freeTrivector_coordinates__, const Float *coordinates) {

			set(freeTrivector_e1e2e3ni, coordinates);
		}

		/// coordinates constructor
		inline freeTrivector(__freeTrivector_coordinates__, Float c_e1e2e3ni) {

			set(freeTrivector_e1e2e3ni, c_e1e2e3ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const freeTrivector &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__freeTrivector_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__freeTrivector_coordinates__, Float c_e1e2e3ni);

		/// assign copy
		freeTrivector &operator=(const freeTrivector &arg1);

		/// assign general multivector
		freeTrivector &operator=(const mv &arg1);

		/// assign scalar
		freeTrivector &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2e3ni() const {
			return m_c[0];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__freeTrivector_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class freeTrivector 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline freeTrivector _freeTrivector(const mv &arg1) {
		return freeTrivector(arg1, 0);
	}
	/// from const specialization class:
	inline const freeTrivector &_freeTrivector(const freeTrivector &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline freeTrivector &_freeTrivector(freeTrivector &arg1) {
		return arg1;
	}
	/// from Float:
	inline freeTrivector _freeTrivector(freeTrivector::Float arg1) {
		return freeTrivector(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline freeTrivector like(const mv &what, const freeTrivector &example) {return _freeTrivector(what);}
	/// from const specialization class:
	inline const freeTrivector like(const freeTrivector &what, const freeTrivector &example) {return _freeTrivector(what);}
	/// from non-const specialization class:
	inline freeTrivector like(freeTrivector &what, const freeTrivector &example) {return _freeTrivector(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const freeTrivector & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const freeTrivector & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const freeTrivector & v) {
		return (float)0;
	}


	/// enum for the coordinates of tangentVector 
	enum __tangentVector_coordinates__ {tangentVector_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni};

	class tangentVector {
		// the friend classes of tangentVector 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline tangentVector() {

			set();
		}

		/// scalar constructor 
		inline tangentVector(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> tangentVector	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline tangentVector(const tangentVector &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline tangentVector(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> tangentVector	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline tangentVector(__tangentVector_coordinates__, const Float *coordinates) {

			set(tangentVector_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni, coordinates);
		}

		/// coordinates constructor
		inline tangentVector(__tangentVector_coordinates__, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni) {

			set(tangentVector_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni, c_noe1, c_noe2, c_noe3, c_e1e2, c_e2e3, c_e3e1, c_e1ni, c_e2ni, c_e3ni, c_noni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const tangentVector &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__tangentVector_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__tangentVector_coordinates__, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni);

		/// assign copy
		tangentVector &operator=(const tangentVector &arg1);

		/// assign general multivector
		tangentVector &operator=(const mv &arg1);

		/// assign scalar
		tangentVector &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float noe1() const {
			return m_c[0];
		}
		inline Float noe2() const {
			return m_c[1];
		}
		inline Float noe3() const {
			return m_c[2];
		}
		inline Float e1e2() const {
			return m_c[3];
		}
		inline Float e2e3() const {
			return m_c[4];
		}
		inline Float e3e1() const {
			return m_c[5];
		}
		inline Float e1ni() const {
			return m_c[6];
		}
		inline Float e2ni() const {
			return m_c[7];
		}
		inline Float e3ni() const {
			return m_c[8];
		}
		inline Float noni() const {
			return m_c[9];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__tangentVector_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[10];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class tangentVector 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline tangentVector _tangentVector(const mv &arg1) {
		return tangentVector(arg1, 0);
	}
	/// from const specialization class:
	inline const tangentVector &_tangentVector(const tangentVector &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline tangentVector &_tangentVector(tangentVector &arg1) {
		return arg1;
	}
	/// from Float:
	inline tangentVector _tangentVector(tangentVector::Float arg1) {
		return tangentVector(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline tangentVector like(const mv &what, const tangentVector &example) {return _tangentVector(what);}
	/// from const specialization class:
	inline const tangentVector like(const tangentVector &what, const tangentVector &example) {return _tangentVector(what);}
	/// from non-const specialization class:
	inline tangentVector like(tangentVector &what, const tangentVector &example) {return _tangentVector(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const tangentVector & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const tangentVector & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const tangentVector & v) {
		return (float)0;
	}


	/// enum for the coordinates of tangentBivector 
	enum __tangentBivector_coordinates__ {tangentBivector_e1e2e3_e2e3ni_e3e1ni_e1e2ni_noe3ni_noe1ni_noe2ni_noe2e3_noe1e3_noe1e2};

	class tangentBivector {
		// the friend classes of tangentBivector 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline tangentBivector() {

			set();
		}

		/// scalar constructor 
		inline tangentBivector(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> tangentBivector	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline tangentBivector(const tangentBivector &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline tangentBivector(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> tangentBivector	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline tangentBivector(__tangentBivector_coordinates__, const Float *coordinates) {

			set(tangentBivector_e1e2e3_e2e3ni_e3e1ni_e1e2ni_noe3ni_noe1ni_noe2ni_noe2e3_noe1e3_noe1e2, coordinates);
		}

		/// coordinates constructor
		inline tangentBivector(__tangentBivector_coordinates__, Float c_e1e2e3, Float c_e2e3ni, Float c_e3e1ni, Float c_e1e2ni, Float c_noe3ni, Float c_noe1ni, Float c_noe2ni, Float c_noe2e3, Float c_noe1e3, Float c_noe1e2) {

			set(tangentBivector_e1e2e3_e2e3ni_e3e1ni_e1e2ni_noe3ni_noe1ni_noe2ni_noe2e3_noe1e3_noe1e2, c_e1e2e3, c_e2e3ni, c_e3e1ni, c_e1e2ni, c_noe3ni, c_noe1ni, c_noe2ni, c_noe2e3, c_noe1e3, c_noe1e2);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const tangentBivector &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__tangentBivector_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__tangentBivector_coordinates__, Float c_e1e2e3, Float c_e2e3ni, Float c_e3e1ni, Float c_e1e2ni, Float c_noe3ni, Float c_noe1ni, Float c_noe2ni, Float c_noe2e3, Float c_noe1e3, Float c_noe1e2);

		/// assign copy
		tangentBivector &operator=(const tangentBivector &arg1);

		/// assign general multivector
		tangentBivector &operator=(const mv &arg1);

		/// assign scalar
		tangentBivector &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2e3() const {
			return m_c[0];
		}
		inline Float e2e3ni() const {
			return m_c[1];
		}
		inline Float e3e1ni() const {
			return m_c[2];
		}
		inline Float e1e2ni() const {
			return m_c[3];
		}
		inline Float noe3ni() const {
			return m_c[4];
		}
		inline Float noe1ni() const {
			return m_c[5];
		}
		inline Float noe2ni() const {
			return m_c[6];
		}
		inline Float noe2e3() const {
			return m_c[7];
		}
		inline Float noe1e3() const {
			return m_c[8];
		}
		inline Float noe1e2() const {
			return m_c[9];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__tangentBivector_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[10];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class tangentBivector 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline tangentBivector _tangentBivector(const mv &arg1) {
		return tangentBivector(arg1, 0);
	}
	/// from const specialization class:
	inline const tangentBivector &_tangentBivector(const tangentBivector &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline tangentBivector &_tangentBivector(tangentBivector &arg1) {
		return arg1;
	}
	/// from Float:
	inline tangentBivector _tangentBivector(tangentBivector::Float arg1) {
		return tangentBivector(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline tangentBivector like(const mv &what, const tangentBivector &example) {return _tangentBivector(what);}
	/// from const specialization class:
	inline const tangentBivector like(const tangentBivector &what, const tangentBivector &example) {return _tangentBivector(what);}
	/// from non-const specialization class:
	inline tangentBivector like(tangentBivector &what, const tangentBivector &example) {return _tangentBivector(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const tangentBivector & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const tangentBivector & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const tangentBivector & v) {
		return (float)0;
	}


	/// enum for the coordinates of vectorE2GA 
	enum __vectorE2GA_coordinates__ {vectorE2GA_e1_e2};

	class vectorE2GA {
		// the friend classes of vectorE2GA 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline vectorE2GA() {

			set();
		}

		/// scalar constructor 
		inline vectorE2GA(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> vectorE2GA	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline vectorE2GA(const vectorE2GA &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline vectorE2GA(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> vectorE2GA	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline vectorE2GA(__vectorE2GA_coordinates__, const Float *coordinates) {

			set(vectorE2GA_e1_e2, coordinates);
		}

		/// coordinates constructor
		inline vectorE2GA(__vectorE2GA_coordinates__, Float c_e1, Float c_e2) {

			set(vectorE2GA_e1_e2, c_e1, c_e2);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const vectorE2GA &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__vectorE2GA_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__vectorE2GA_coordinates__, Float c_e1, Float c_e2);

		/// assign copy
		vectorE2GA &operator=(const vectorE2GA &arg1);

		/// assign general multivector
		vectorE2GA &operator=(const mv &arg1);

		/// assign scalar
		vectorE2GA &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1() const {
			return m_c[0];
		}
		inline Float e2() const {
			return m_c[1];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__vectorE2GA_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[2];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class vectorE2GA 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline vectorE2GA _vectorE2GA(const mv &arg1) {
		return vectorE2GA(arg1, 0);
	}
	/// from const specialization class:
	inline const vectorE2GA &_vectorE2GA(const vectorE2GA &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline vectorE2GA &_vectorE2GA(vectorE2GA &arg1) {
		return arg1;
	}
	/// from Float:
	inline vectorE2GA _vectorE2GA(vectorE2GA::Float arg1) {
		return vectorE2GA(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline vectorE2GA like(const mv &what, const vectorE2GA &example) {return _vectorE2GA(what);}
	/// from const specialization class:
	inline const vectorE2GA like(const vectorE2GA &what, const vectorE2GA &example) {return _vectorE2GA(what);}
	/// from non-const specialization class:
	inline vectorE2GA like(vectorE2GA &what, const vectorE2GA &example) {return _vectorE2GA(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const vectorE2GA & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const vectorE2GA & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const vectorE2GA & v) {
		return (float)0;
	}


	/// enum for the coordinates of vectorE3GA 
	enum __vectorE3GA_coordinates__ {vectorE3GA_e1_e2_e3};

	class vectorE3GA {
		// the friend classes of vectorE3GA 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline vectorE3GA() {

			set();
		}

		/// scalar constructor 
		inline vectorE3GA(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> vectorE3GA	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline vectorE3GA(const vectorE3GA &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline vectorE3GA(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> vectorE3GA	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline vectorE3GA(__vectorE3GA_coordinates__, const Float *coordinates) {

			set(vectorE3GA_e1_e2_e3, coordinates);
		}

		/// coordinates constructor
		inline vectorE3GA(__vectorE3GA_coordinates__, Float c_e1, Float c_e2, Float c_e3) {

			set(vectorE3GA_e1_e2_e3, c_e1, c_e2, c_e3);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const vectorE3GA &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__vectorE3GA_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__vectorE3GA_coordinates__, Float c_e1, Float c_e2, Float c_e3);

		/// assign copy
		vectorE3GA &operator=(const vectorE3GA &arg1);

		/// assign general multivector
		vectorE3GA &operator=(const mv &arg1);

		/// assign scalar
		vectorE3GA &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1() const {
			return m_c[0];
		}
		inline Float e2() const {
			return m_c[1];
		}
		inline Float e3() const {
			return m_c[2];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__vectorE3GA_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class vectorE3GA 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline vectorE3GA _vectorE3GA(const mv &arg1) {
		return vectorE3GA(arg1, 0);
	}
	/// from const specialization class:
	inline const vectorE3GA &_vectorE3GA(const vectorE3GA &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline vectorE3GA &_vectorE3GA(vectorE3GA &arg1) {
		return arg1;
	}
	/// from Float:
	inline vectorE3GA _vectorE3GA(vectorE3GA::Float arg1) {
		return vectorE3GA(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline vectorE3GA like(const mv &what, const vectorE3GA &example) {return _vectorE3GA(what);}
	/// from const specialization class:
	inline const vectorE3GA like(const vectorE3GA &what, const vectorE3GA &example) {return _vectorE3GA(what);}
	/// from non-const specialization class:
	inline vectorE3GA like(vectorE3GA &what, const vectorE3GA &example) {return _vectorE3GA(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const vectorE3GA & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const vectorE3GA & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const vectorE3GA & v) {
		return (float)0;
	}


	/// enum for the coordinates of bivectorE3GA 
	enum __bivectorE3GA_coordinates__ {bivectorE3GA_e1e2_e2e3_e3e1};

	class bivectorE3GA {
		// the friend classes of bivectorE3GA 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline bivectorE3GA() {

			set();
		}

		/// scalar constructor 
		inline bivectorE3GA(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> bivectorE3GA	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline bivectorE3GA(const bivectorE3GA &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline bivectorE3GA(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> bivectorE3GA	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline bivectorE3GA(__bivectorE3GA_coordinates__, const Float *coordinates) {

			set(bivectorE3GA_e1e2_e2e3_e3e1, coordinates);
		}

		/// coordinates constructor
		inline bivectorE3GA(__bivectorE3GA_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1) {

			set(bivectorE3GA_e1e2_e2e3_e3e1, c_e1e2, c_e2e3, c_e3e1);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const bivectorE3GA &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__bivectorE3GA_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__bivectorE3GA_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1);

		/// assign copy
		bivectorE3GA &operator=(const bivectorE3GA &arg1);

		/// assign general multivector
		bivectorE3GA &operator=(const mv &arg1);

		/// assign scalar
		bivectorE3GA &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2() const {
			return m_c[0];
		}
		inline Float e2e3() const {
			return m_c[1];
		}
		inline Float e3e1() const {
			return m_c[2];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__bivectorE3GA_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class bivectorE3GA 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline bivectorE3GA _bivectorE3GA(const mv &arg1) {
		return bivectorE3GA(arg1, 0);
	}
	/// from const specialization class:
	inline const bivectorE3GA &_bivectorE3GA(const bivectorE3GA &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline bivectorE3GA &_bivectorE3GA(bivectorE3GA &arg1) {
		return arg1;
	}
	/// from Float:
	inline bivectorE3GA _bivectorE3GA(bivectorE3GA::Float arg1) {
		return bivectorE3GA(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline bivectorE3GA like(const mv &what, const bivectorE3GA &example) {return _bivectorE3GA(what);}
	/// from const specialization class:
	inline const bivectorE3GA like(const bivectorE3GA &what, const bivectorE3GA &example) {return _bivectorE3GA(what);}
	/// from non-const specialization class:
	inline bivectorE3GA like(bivectorE3GA &what, const bivectorE3GA &example) {return _bivectorE3GA(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const bivectorE3GA & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const bivectorE3GA & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const bivectorE3GA & v) {
		return (float)0;
	}


	/// enum for the coordinates of TRversor 
	enum __TRversor_coordinates__ {TRversor_scalar_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni_e1e2e3ni};

	class TRversor {
		// the friend classes of TRversor 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline TRversor() {

			set();
		}

		/// scalar constructor 
		inline TRversor(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> TRversor	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline TRversor(const TRversor &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline TRversor(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> TRversor	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline TRversor(__TRversor_coordinates__, const Float *coordinates) {

			set(TRversor_scalar_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni_e1e2e3ni, coordinates);
		}

		/// coordinates constructor
		inline TRversor(__TRversor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_e1e2e3ni) {

			set(TRversor_scalar_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni_e1e2e3ni, c_scalar, c_e1e2, c_e1e3, c_e2e3, c_e1ni, c_e2ni, c_e3ni, c_e1e2e3ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const TRversor &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__TRversor_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__TRversor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_e1e2e3ni);

		/// assign copy
		TRversor &operator=(const TRversor &arg1);

		/// assign general multivector
		TRversor &operator=(const mv &arg1);

		/// assign scalar
		TRversor &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2() const {
			return m_c[1];
		}
		inline Float e1e3() const {
			return m_c[2];
		}
		inline Float e2e3() const {
			return m_c[3];
		}
		inline Float e1ni() const {
			return m_c[4];
		}
		inline Float e2ni() const {
			return m_c[5];
		}
		inline Float e3ni() const {
			return m_c[6];
		}
		inline Float e1e2e3ni() const {
			return m_c[7];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__TRversor_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[8];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class TRversor 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline TRversor _TRversor(const mv &arg1) {
		return TRversor(arg1, 0);
	}
	/// from const specialization class:
	inline const TRversor &_TRversor(const TRversor &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline TRversor &_TRversor(TRversor &arg1) {
		return arg1;
	}
	/// from Float:
	inline TRversor _TRversor(TRversor::Float arg1) {
		return TRversor(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline TRversor like(const mv &what, const TRversor &example) {return _TRversor(what);}
	/// from const specialization class:
	inline const TRversor like(const TRversor &what, const TRversor &example) {return _TRversor(what);}
	/// from non-const specialization class:
	inline TRversor like(TRversor &what, const TRversor &example) {return _TRversor(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const TRversor & v) {
		return (float)v.m_c[0];
	}
	/// returns scalar part of v as double
	inline double _double(const TRversor & v) {
		return (double)v.m_c[0];
	}
	/// returns scalar part of v as Float
	inline float _Float(const TRversor & v) {
		return v.m_c[0];
	}


	/// enum for the coordinates of TRSversor 
	enum __TRSversor_coordinates__ {TRSversor_scalar_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni_noni_e1e2noni_e1e3noni_e2e3noni_e1e2e3ni};

	class TRSversor {
		// the friend classes of TRSversor 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline TRSversor() {

			set();
		}

		/// scalar constructor 
		inline TRSversor(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> TRSversor	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline TRSversor(const TRSversor &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline TRSversor(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> TRSversor	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline TRSversor(__TRSversor_coordinates__, const Float *coordinates) {

			set(TRSversor_scalar_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni_noni_e1e2noni_e1e3noni_e2e3noni_e1e2e3ni, coordinates);
		}

		/// coordinates constructor
		inline TRSversor(__TRSversor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3ni) {

			set(TRSversor_scalar_e1e2_e1e3_e2e3_e1ni_e2ni_e3ni_noni_e1e2noni_e1e3noni_e2e3noni_e1e2e3ni, c_scalar, c_e1e2, c_e1e3, c_e2e3, c_e1ni, c_e2ni, c_e3ni, c_noni, c_e1e2noni, c_e1e3noni, c_e2e3noni, c_e1e2e3ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const TRSversor &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__TRSversor_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__TRSversor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3ni);

		/// assign copy
		TRSversor &operator=(const TRSversor &arg1);

		/// assign general multivector
		TRSversor &operator=(const mv &arg1);

		/// assign scalar
		TRSversor &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2() const {
			return m_c[1];
		}
		inline Float e1e3() const {
			return m_c[2];
		}
		inline Float e2e3() const {
			return m_c[3];
		}
		inline Float e1ni() const {
			return m_c[4];
		}
		inline Float e2ni() const {
			return m_c[5];
		}
		inline Float e3ni() const {
			return m_c[6];
		}
		inline Float noni() const {
			return m_c[7];
		}
		inline Float e1e2noni() const {
			return m_c[8];
		}
		inline Float e1e3noni() const {
			return m_c[9];
		}
		inline Float e2e3noni() const {
			return m_c[10];
		}
		inline Float e1e2e3ni() const {
			return m_c[11];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__TRSversor_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[12];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class TRSversor 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline TRSversor _TRSversor(const mv &arg1) {
		return TRSversor(arg1, 0);
	}
	/// from const specialization class:
	inline const TRSversor &_TRSversor(const TRSversor &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline TRSversor &_TRSversor(TRSversor &arg1) {
		return arg1;
	}
	/// from Float:
	inline TRSversor _TRSversor(TRSversor::Float arg1) {
		return TRSversor(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline TRSversor like(const mv &what, const TRSversor &example) {return _TRSversor(what);}
	/// from const specialization class:
	inline const TRSversor like(const TRSversor &what, const TRSversor &example) {return _TRSversor(what);}
	/// from non-const specialization class:
	inline TRSversor like(TRSversor &what, const TRSversor &example) {return _TRSversor(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const TRSversor & v) {
		return (float)v.m_c[0];
	}
	/// returns scalar part of v as double
	inline double _double(const TRSversor & v) {
		return (double)v.m_c[0];
	}
	/// returns scalar part of v as Float
	inline float _Float(const TRSversor & v) {
		return v.m_c[0];
	}


	/// enum for the coordinates of evenVersor 
	enum __evenVersor_coordinates__ {evenVersor_scalar_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni_e1e2e3no};

	class evenVersor {
		// the friend classes of evenVersor 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline evenVersor() {

			set();
		}

		/// scalar constructor 
		inline evenVersor(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> evenVersor	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline evenVersor(const evenVersor &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline evenVersor(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> evenVersor	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline evenVersor(__evenVersor_coordinates__, const Float *coordinates) {

			set(evenVersor_scalar_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni_e1e2e3no, coordinates);
		}

		/// coordinates constructor
		inline evenVersor(__evenVersor_coordinates__, Float c_scalar, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no) {

			set(evenVersor_scalar_noe1_noe2_noe3_e1e2_e2e3_e3e1_e1ni_e2ni_e3ni_noni_e1e2e3ni_e1e2noni_e1e3noni_e2e3noni_e1e2e3no, c_scalar, c_noe1, c_noe2, c_noe3, c_e1e2, c_e2e3, c_e3e1, c_e1ni, c_e2ni, c_e3ni, c_noni, c_e1e2e3ni, c_e1e2noni, c_e1e3noni, c_e2e3noni, c_e1e2e3no);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const evenVersor &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__evenVersor_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__evenVersor_coordinates__, Float c_scalar, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no);

		/// assign copy
		evenVersor &operator=(const evenVersor &arg1);

		/// assign general multivector
		evenVersor &operator=(const mv &arg1);

		/// assign scalar
		evenVersor &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float noe1() const {
			return m_c[1];
		}
		inline Float noe2() const {
			return m_c[2];
		}
		inline Float noe3() const {
			return m_c[3];
		}
		inline Float e1e2() const {
			return m_c[4];
		}
		inline Float e2e3() const {
			return m_c[5];
		}
		inline Float e3e1() const {
			return m_c[6];
		}
		inline Float e1ni() const {
			return m_c[7];
		}
		inline Float e2ni() const {
			return m_c[8];
		}
		inline Float e3ni() const {
			return m_c[9];
		}
		inline Float noni() const {
			return m_c[10];
		}
		inline Float e1e2e3ni() const {
			return m_c[11];
		}
		inline Float e1e2noni() const {
			return m_c[12];
		}
		inline Float e1e3noni() const {
			return m_c[13];
		}
		inline Float e2e3noni() const {
			return m_c[14];
		}
		inline Float e1e2e3no() const {
			return m_c[15];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__evenVersor_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[16];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class evenVersor 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline evenVersor _evenVersor(const mv &arg1) {
		return evenVersor(arg1, 0);
	}
	/// from const specialization class:
	inline const evenVersor &_evenVersor(const evenVersor &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline evenVersor &_evenVersor(evenVersor &arg1) {
		return arg1;
	}
	/// from Float:
	inline evenVersor _evenVersor(evenVersor::Float arg1) {
		return evenVersor(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline evenVersor like(const mv &what, const evenVersor &example) {return _evenVersor(what);}
	/// from const specialization class:
	inline const evenVersor like(const evenVersor &what, const evenVersor &example) {return _evenVersor(what);}
	/// from non-const specialization class:
	inline evenVersor like(evenVersor &what, const evenVersor &example) {return _evenVersor(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const evenVersor & v) {
		return (float)v.m_c[0];
	}
	/// returns scalar part of v as double
	inline double _double(const evenVersor & v) {
		return (double)v.m_c[0];
	}
	/// returns scalar part of v as Float
	inline float _Float(const evenVersor & v) {
		return v.m_c[0];
	}


	/// enum for the coordinates of translator 
	enum __translator_coordinates__ {translator_scalar_e1ni_e2ni_e3ni};

	class translator {
		// the friend classes of translator 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline translator() {

			set();
		}

		/// scalar constructor 
		inline translator(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> translator	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline translator(const translator &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline translator(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> translator	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline translator(__translator_coordinates__, const Float *coordinates) {

			set(translator_scalar_e1ni_e2ni_e3ni, coordinates);
		}

		/// coordinates constructor
		inline translator(__translator_coordinates__, Float c_scalar, Float c_e1ni, Float c_e2ni, Float c_e3ni) {

			set(translator_scalar_e1ni_e2ni_e3ni, c_scalar, c_e1ni, c_e2ni, c_e3ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const translator &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__translator_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__translator_coordinates__, Float c_scalar, Float c_e1ni, Float c_e2ni, Float c_e3ni);

		/// assign copy
		translator &operator=(const translator &arg1);

		/// assign general multivector
		translator &operator=(const mv &arg1);

		/// assign scalar
		translator &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1ni() const {
			return m_c[1];
		}
		inline Float e2ni() const {
			return m_c[2];
		}
		inline Float e3ni() const {
			return m_c[3];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__translator_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class translator 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline translator _translator(const mv &arg1) {
		return translator(arg1, 0);
	}
	/// from const specialization class:
	inline const translator &_translator(const translator &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline translator &_translator(translator &arg1) {
		return arg1;
	}
	/// from Float:
	inline translator _translator(translator::Float arg1) {
		return translator(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline translator like(const mv &what, const translator &example) {return _translator(what);}
	/// from const specialization class:
	inline const translator like(const translator &what, const translator &example) {return _translator(what);}
	/// from non-const specialization class:
	inline translator like(translator &what, const translator &example) {return _translator(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const translator & v) {
		return (float)v.m_c[0];
	}
	/// returns scalar part of v as double
	inline double _double(const translator & v) {
		return (double)v.m_c[0];
	}
	/// returns scalar part of v as Float
	inline float _Float(const translator & v) {
		return v.m_c[0];
	}


	/// enum for the coordinates of normalizedTranslator 
	enum __normalizedTranslator_coordinates__ {normalizedTranslator_e1ni_e2ni_e3ni_scalarf1_0};

	class normalizedTranslator {
		// the friend classes of normalizedTranslator 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline normalizedTranslator() {

			set();
		}

		/// scalar constructor 
		inline normalizedTranslator(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> normalizedTranslator	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline normalizedTranslator(const normalizedTranslator &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline normalizedTranslator(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> normalizedTranslator	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline normalizedTranslator(__normalizedTranslator_coordinates__, const Float *coordinates) {

			set(normalizedTranslator_e1ni_e2ni_e3ni_scalarf1_0, coordinates);
		}

		/// coordinates constructor
		inline normalizedTranslator(__normalizedTranslator_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni) {

			set(normalizedTranslator_e1ni_e2ni_e3ni_scalarf1_0, c_e1ni, c_e2ni, c_e3ni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const normalizedTranslator &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__normalizedTranslator_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__normalizedTranslator_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni);

		/// assign copy
		normalizedTranslator &operator=(const normalizedTranslator &arg1);

		/// assign general multivector
		normalizedTranslator &operator=(const mv &arg1);

		/// assign scalar
		normalizedTranslator &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1ni() const {
			return m_c[0];
		}
		inline Float e2ni() const {
			return m_c[1];
		}
		inline Float e3ni() const {
			return m_c[2];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__normalizedTranslator_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class normalizedTranslator 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline normalizedTranslator _normalizedTranslator(const mv &arg1) {
		return normalizedTranslator(arg1, 0);
	}
	/// from const specialization class:
	inline const normalizedTranslator &_normalizedTranslator(const normalizedTranslator &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline normalizedTranslator &_normalizedTranslator(normalizedTranslator &arg1) {
		return arg1;
	}
	/// from Float:
	inline normalizedTranslator _normalizedTranslator(normalizedTranslator::Float arg1) {
		return normalizedTranslator(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline normalizedTranslator like(const mv &what, const normalizedTranslator &example) {return _normalizedTranslator(what);}
	/// from const specialization class:
	inline const normalizedTranslator like(const normalizedTranslator &what, const normalizedTranslator &example) {return _normalizedTranslator(what);}
	/// from non-const specialization class:
	inline normalizedTranslator like(normalizedTranslator &what, const normalizedTranslator &example) {return _normalizedTranslator(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const normalizedTranslator & v) {
		return (float)1.0f;
	}
	/// returns scalar part of v as double
	inline double _double(const normalizedTranslator & v) {
		return (double)1.0f;
	}
	/// returns scalar part of v as Float
	inline float _Float(const normalizedTranslator & v) {
		return (float)1.0f;
	}


	/// enum for the coordinates of rotor 
	enum __rotor_coordinates__ {rotor_scalar_e1e2_e2e3_e3e1};

	class rotor {
		// the friend classes of rotor 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline rotor() {

			set();
		}

		/// scalar constructor 
		inline rotor(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> rotor	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline rotor(const rotor &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline rotor(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> rotor	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline rotor(__rotor_coordinates__, const Float *coordinates) {

			set(rotor_scalar_e1e2_e2e3_e3e1, coordinates);
		}

		/// coordinates constructor
		inline rotor(__rotor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e2e3, Float c_e3e1) {

			set(rotor_scalar_e1e2_e2e3_e3e1, c_scalar, c_e1e2, c_e2e3, c_e3e1);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const rotor &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__rotor_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__rotor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e2e3, Float c_e3e1);

		/// assign copy
		rotor &operator=(const rotor &arg1);

		/// assign general multivector
		rotor &operator=(const mv &arg1);

		/// assign scalar
		rotor &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2() const {
			return m_c[1];
		}
		inline Float e2e3() const {
			return m_c[2];
		}
		inline Float e3e1() const {
			return m_c[3];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__rotor_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class rotor 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline rotor _rotor(const mv &arg1) {
		return rotor(arg1, 0);
	}
	/// from const specialization class:
	inline const rotor &_rotor(const rotor &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline rotor &_rotor(rotor &arg1) {
		return arg1;
	}
	/// from Float:
	inline rotor _rotor(rotor::Float arg1) {
		return rotor(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline rotor like(const mv &what, const rotor &example) {return _rotor(what);}
	/// from const specialization class:
	inline const rotor like(const rotor &what, const rotor &example) {return _rotor(what);}
	/// from non-const specialization class:
	inline rotor like(rotor &what, const rotor &example) {return _rotor(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const rotor & v) {
		return (float)v.m_c[0];
	}
	/// returns scalar part of v as double
	inline double _double(const rotor & v) {
		return (double)v.m_c[0];
	}
	/// returns scalar part of v as Float
	inline float _Float(const rotor & v) {
		return v.m_c[0];
	}


	/// enum for the coordinates of scalor 
	enum __scalor_coordinates__ {scalor_scalar_noni};

	class scalor {
		// the friend classes of scalor 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline scalor() {

			set();
		}

		/// scalar constructor 
		inline scalor(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> scalor	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline scalor(const scalor &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline scalor(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> scalor	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline scalor(__scalor_coordinates__, const Float *coordinates) {

			set(scalor_scalar_noni, coordinates);
		}

		/// coordinates constructor
		inline scalor(__scalor_coordinates__, Float c_scalar, Float c_noni) {

			set(scalor_scalar_noni, c_scalar, c_noni);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const scalor &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__scalor_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__scalor_coordinates__, Float c_scalar, Float c_noni);

		/// assign copy
		scalor &operator=(const scalor &arg1);

		/// assign general multivector
		scalor &operator=(const mv &arg1);

		/// assign scalar
		scalor &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float noni() const {
			return m_c[1];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__scalor_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[2];



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class scalor 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline scalor _scalor(const mv &arg1) {
		return scalor(arg1, 0);
	}
	/// from const specialization class:
	inline const scalor &_scalor(const scalor &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline scalor &_scalor(scalor &arg1) {
		return arg1;
	}
	/// from Float:
	inline scalor _scalor(scalor::Float arg1) {
		return scalor(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline scalor like(const mv &what, const scalor &example) {return _scalor(what);}
	/// from const specialization class:
	inline const scalor like(const scalor &what, const scalor &example) {return _scalor(what);}
	/// from non-const specialization class:
	inline scalor like(scalor &what, const scalor &example) {return _scalor(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const scalor & v) {
		return (float)v.m_c[0];
	}
	/// returns scalar part of v as double
	inline double _double(const scalor & v) {
		return (double)v.m_c[0];
	}
	/// returns scalar part of v as Float
	inline float _Float(const scalor & v) {
		return v.m_c[0];
	}


	/// enum for the coordinates of __no_ct__ 
	enum ____no_ct___coordinates__ {__no_ct___nof1_0};

	class __no_ct__ {
		// the friend classes of __no_ct__ 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline __no_ct__() {

			set();
		}

		/// scalar constructor 
		inline __no_ct__(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> __no_ct__	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline __no_ct__(const __no_ct__ &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline __no_ct__(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> __no_ct__	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline __no_ct__(____no_ct___coordinates__, const Float *coordinates) {

			set(__no_ct___nof1_0, coordinates);
		}

		/// coordinates constructor
		inline __no_ct__(____no_ct___coordinates__) {

			set(__no_ct___nof1_0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const __no_ct__ &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(____no_ct___coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(____no_ct___coordinates__);

		/// assign copy
		__no_ct__ &operator=(const __no_ct__ &arg1);

		/// assign general multivector
		__no_ct__ &operator=(const mv &arg1);

		/// assign scalar
		__no_ct__ &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name
		inline Float nof1_0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(____no_ct___coordinates__ sanityCheckValue) const {
			return NULL;
		}

		// constants, so no coordinate storage



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class __no_ct__ 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline __no_ct__ ___no_ct__(const mv &arg1) {
		return __no_ct__(arg1, 0);
	}
	/// from const specialization class:
	inline const __no_ct__ &___no_ct__(const __no_ct__ &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline __no_ct__ &___no_ct__(__no_ct__ &arg1) {
		return arg1;
	}
	/// from Float:
	inline __no_ct__ ___no_ct__(__no_ct__::Float arg1) {
		return __no_ct__(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline __no_ct__ like(const mv &what, const __no_ct__ &example) {return ___no_ct__(what);}
	/// from const specialization class:
	inline const __no_ct__ like(const __no_ct__ &what, const __no_ct__ &example) {return ___no_ct__(what);}
	/// from non-const specialization class:
	inline __no_ct__ like(__no_ct__ &what, const __no_ct__ &example) {return ___no_ct__(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const __no_ct__ & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const __no_ct__ & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const __no_ct__ & v) {
		return (float)0;
	}


	/// enum for the coordinates of __e1_ct__ 
	enum ____e1_ct___coordinates__ {__e1_ct___e1f1_0};

	class __e1_ct__ {
		// the friend classes of __e1_ct__ 
		friend class mv;
		friend class freeBivector;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline __e1_ct__() {

			set();
		}

		/// scalar constructor 
		inline __e1_ct__(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> __e1_ct__	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline __e1_ct__(const __e1_ct__ &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline __e1_ct__(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> __e1_ct__	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline __e1_ct__(____e1_ct___coordinates__, const Float *coordinates) {

			set(__e1_ct___e1f1_0, coordinates);
		}

		/// coordinates constructor
		inline __e1_ct__(____e1_ct___coordinates__) {

			set(__e1_ct___e1f1_0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const __e1_ct__ &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(____e1_ct___coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(____e1_ct___coordinates__);

		/// assign copy
		__e1_ct__ &operator=(const __e1_ct__ &arg1);

		/// assign general multivector
		__e1_ct__ &operator=(const mv &arg1);

		/// assign scalar
		__e1_ct__ &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name
		inline Float e1f1_0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(____e1_ct___coordinates__ sanityCheckValue) const {
			return NULL;
		}

		// constants, so no coordinate storage



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class __e1_ct__ 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline __e1_ct__ ___e1_ct__(const mv &arg1) {
		return __e1_ct__(arg1, 0);
	}
	/// from const specialization class:
	inline const __e1_ct__ &___e1_ct__(const __e1_ct__ &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline __e1_ct__ &___e1_ct__(__e1_ct__ &arg1) {
		return arg1;
	}
	/// from Float:
	inline __e1_ct__ ___e1_ct__(__e1_ct__::Float arg1) {
		return __e1_ct__(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline __e1_ct__ like(const mv &what, const __e1_ct__ &example) {return ___e1_ct__(what);}
	/// from const specialization class:
	inline const __e1_ct__ like(const __e1_ct__ &what, const __e1_ct__ &example) {return ___e1_ct__(what);}
	/// from non-const specialization class:
	inline __e1_ct__ like(__e1_ct__ &what, const __e1_ct__ &example) {return ___e1_ct__(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const __e1_ct__ & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const __e1_ct__ & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const __e1_ct__ & v) {
		return (float)0;
	}


	/// enum for the coordinates of __e2_ct__ 
	enum ____e2_ct___coordinates__ {__e2_ct___e2f1_0};

	class __e2_ct__ {
		// the friend classes of __e2_ct__ 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline __e2_ct__() {

			set();
		}

		/// scalar constructor 
		inline __e2_ct__(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> __e2_ct__	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline __e2_ct__(const __e2_ct__ &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline __e2_ct__(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> __e2_ct__	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline __e2_ct__(____e2_ct___coordinates__, const Float *coordinates) {

			set(__e2_ct___e2f1_0, coordinates);
		}

		/// coordinates constructor
		inline __e2_ct__(____e2_ct___coordinates__) {

			set(__e2_ct___e2f1_0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const __e2_ct__ &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(____e2_ct___coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(____e2_ct___coordinates__);

		/// assign copy
		__e2_ct__ &operator=(const __e2_ct__ &arg1);

		/// assign general multivector
		__e2_ct__ &operator=(const mv &arg1);

		/// assign scalar
		__e2_ct__ &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name
		inline Float e2f1_0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(____e2_ct___coordinates__ sanityCheckValue) const {
			return NULL;
		}

		// constants, so no coordinate storage



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class __e2_ct__ 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline __e2_ct__ ___e2_ct__(const mv &arg1) {
		return __e2_ct__(arg1, 0);
	}
	/// from const specialization class:
	inline const __e2_ct__ &___e2_ct__(const __e2_ct__ &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline __e2_ct__ &___e2_ct__(__e2_ct__ &arg1) {
		return arg1;
	}
	/// from Float:
	inline __e2_ct__ ___e2_ct__(__e2_ct__::Float arg1) {
		return __e2_ct__(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline __e2_ct__ like(const mv &what, const __e2_ct__ &example) {return ___e2_ct__(what);}
	/// from const specialization class:
	inline const __e2_ct__ like(const __e2_ct__ &what, const __e2_ct__ &example) {return ___e2_ct__(what);}
	/// from non-const specialization class:
	inline __e2_ct__ like(__e2_ct__ &what, const __e2_ct__ &example) {return ___e2_ct__(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const __e2_ct__ & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const __e2_ct__ & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const __e2_ct__ & v) {
		return (float)0;
	}


	/// enum for the coordinates of __e3_ct__ 
	enum ____e3_ct___coordinates__ {__e3_ct___e3f1_0};

	class __e3_ct__ {
		// the friend classes of __e3_ct__ 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline __e3_ct__() {

			set();
		}

		/// scalar constructor 
		inline __e3_ct__(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> __e3_ct__	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline __e3_ct__(const __e3_ct__ &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline __e3_ct__(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> __e3_ct__	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline __e3_ct__(____e3_ct___coordinates__, const Float *coordinates) {

			set(__e3_ct___e3f1_0, coordinates);
		}

		/// coordinates constructor
		inline __e3_ct__(____e3_ct___coordinates__) {

			set(__e3_ct___e3f1_0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const __e3_ct__ &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(____e3_ct___coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(____e3_ct___coordinates__);

		/// assign copy
		__e3_ct__ &operator=(const __e3_ct__ &arg1);

		/// assign general multivector
		__e3_ct__ &operator=(const mv &arg1);

		/// assign scalar
		__e3_ct__ &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name
		inline Float e3f1_0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(____e3_ct___coordinates__ sanityCheckValue) const {
			return NULL;
		}

		// constants, so no coordinate storage



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class __e3_ct__ 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline __e3_ct__ ___e3_ct__(const mv &arg1) {
		return __e3_ct__(arg1, 0);
	}
	/// from const specialization class:
	inline const __e3_ct__ &___e3_ct__(const __e3_ct__ &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline __e3_ct__ &___e3_ct__(__e3_ct__ &arg1) {
		return arg1;
	}
	/// from Float:
	inline __e3_ct__ ___e3_ct__(__e3_ct__::Float arg1) {
		return __e3_ct__(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline __e3_ct__ like(const mv &what, const __e3_ct__ &example) {return ___e3_ct__(what);}
	/// from const specialization class:
	inline const __e3_ct__ like(const __e3_ct__ &what, const __e3_ct__ &example) {return ___e3_ct__(what);}
	/// from non-const specialization class:
	inline __e3_ct__ like(__e3_ct__ &what, const __e3_ct__ &example) {return ___e3_ct__(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const __e3_ct__ & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const __e3_ct__ & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const __e3_ct__ & v) {
		return (float)0;
	}


	/// enum for the coordinates of __ni_ct__ 
	enum ____ni_ct___coordinates__ {__ni_ct___nif1_0};

	class __ni_ct__ {
		// the friend classes of __ni_ct__ 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class om;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline __ni_ct__() {

			set();
		}

		/// scalar constructor 
		inline __ni_ct__(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> __ni_ct__	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline __ni_ct__(const __ni_ct__ &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline __ni_ct__(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> __ni_ct__	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline __ni_ct__(____ni_ct___coordinates__, const Float *coordinates) {

			set(__ni_ct___nif1_0, coordinates);
		}

		/// coordinates constructor
		inline __ni_ct__(____ni_ct___coordinates__) {

			set(__ni_ct___nif1_0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const __ni_ct__ &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(____ni_ct___coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(____ni_ct___coordinates__);

		/// assign copy
		__ni_ct__ &operator=(const __ni_ct__ &arg1);

		/// assign general multivector
		__ni_ct__ &operator=(const mv &arg1);

		/// assign scalar
		__ni_ct__ &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name
		inline Float nif1_0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(____ni_ct___coordinates__ sanityCheckValue) const {
			return NULL;
		}

		// constants, so no coordinate storage



		inline const char * c_str(const char *fp = NULL) const {
			return ::c3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::c3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class __ni_ct__ 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline __ni_ct__ ___ni_ct__(const mv &arg1) {
		return __ni_ct__(arg1, 0);
	}
	/// from const specialization class:
	inline const __ni_ct__ &___ni_ct__(const __ni_ct__ &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline __ni_ct__ &___ni_ct__(__ni_ct__ &arg1) {
		return arg1;
	}
	/// from Float:
	inline __ni_ct__ ___ni_ct__(__ni_ct__::Float arg1) {
		return __ni_ct__(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline __ni_ct__ like(const mv &what, const __ni_ct__ &example) {return ___ni_ct__(what);}
	/// from const specialization class:
	inline const __ni_ct__ like(const __ni_ct__ &what, const __ni_ct__ &example) {return ___ni_ct__(what);}
	/// from non-const specialization class:
	inline __ni_ct__ like(__ni_ct__ &what, const __ni_ct__ &example) {return ___ni_ct__(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const __ni_ct__ & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const __ni_ct__ & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const __ni_ct__ & v) {
		return (float)0;
	}


	class om {
		// the friend classes of om 
		friend class mv;
		friend class freeBivector;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class dualLine;
		friend class e3_t;
		friend class __e3_ct__;
		friend class vectorE3GA;
		friend class TRversor;
		friend class evenVersor;
		friend class line;
		friend class freeTrivector;
		friend class normalizedFlatPoint;
		friend class TRSversor;
		friend class plane;
		friend class point;
		friend class __ni_ct__;
		friend class normalizedDualSphere;
		friend class pointPair;
		friend class translator;
		friend class freeVector;
		friend class bivectorE3GA;
		friend class normalizedPoint;
		friend class flatPoint;
		friend class dualPlane;
		friend class scalor;
		friend class scalar;
		friend class __no_ct__;
		friend class tangentBivector;
		friend class dualSphere;
		friend class normalizedSphere;
		friend class vectorE2GA;
		friend class ni_t;
		friend class sphere;
		friend class normalizedTranslator;
		friend class e1_t;
		friend class rotor;
		friend class no_t;
		friend class circle;
		friend class tangentVector;
		friend class e2_t;

		public:
			typedef float Float;

		/// identity 'I' constructor
		inline om() {
			set();
		}

		/// copy constructor (MUST PASS BY REFERENCE!)
		inline om(const om &arg1) {
			set(arg1);
		}

		/// scalar constructor (creates scalar * 'I' outermorphism)
		inline om(Float scalar) {
			set(scalar);
		}

		/// pointer to coordinates constructor
		inline om(const Float *coordinates) {
			set(coordinates);
		}

		/// pointer to coordinates/transpose constructor
		inline om(const Float *coordinates, bool transpose) {
			set(coordinates, transpose);
		}

		/// constructor from basis vectors array
		inline om(const point *vectors) {
			set(vectors);
		}

		/// constructor from basis vectors 
		inline om(const point & image_of_no, const point & image_of_e1, const point & image_of_e2, const point & image_of_e3, const point & image_of_ni) {
			set(image_of_no, image_of_e1, image_of_e2, image_of_e3, image_of_ni);
		}


		/// set to identity 'I'
		void set();

		/// set to copy
		void set(const om &arg1);

		/// set to scalar (creates scalar * 'I' outermorphism)
		void set(Float scalarVal);

		/// set to coordinates 
		void set(const Float *coordinates);

		/// set to coordinates/transpose 
		void set(const Float *coordinates, bool transpose);

		/// set from basis vectors array
		void set(const point *vectors);

		/// set from basis vectors 
		void set(
			const point & image_of_no, const point & image_of_e1, const point & image_of_e2, const point & image_of_e3, const point & image_of_ni);


		/// assign copy
		om &operator=(const om &arg1);

		/// assign scalar (creates scalar * 'I' outermorphism)
		om &operator=(Float scalarVal);

		/// assign specialization:


		Float m_c[251]; ///< coordinate storage




	}; // end of class om



	// multivector type
	class mvType : public mvTypeBase {
		public:

			inline mvType() {
		}

		/** Creates a new instance of MultivectorInfo */
		inline mvType(const mv &X) {
			init(X, (mv::Float)0.0);
		}

		/** Creates a new instance of MultivectorInfo */
		inline mvType(const mv &X, mv::Float epsilon) {
			init(X, epsilon);
		}

		inline mvType(const mvType &T) {
		}


		void init(const mv &X, mv::Float epsilon);

		std::string toString() const;

		protected:
			void init(const mv &X, mv::Float epsilon, bool useAlgebraMetric, int guCnt);
	};





	// extra underscore constructors from profile:


	extern __no_ct__ no;
	extern __ni_ct__ ni;
	extern __e3_ct__ e3;
	extern __e1_ct__ e1;
	extern __e2_ct__ e2;
	inline mv lcont(const mv& x, const mv& y);
	inline scalar scp(const mv& x, const mv& y);
	inline mv gp(const mv& x, const mv& y);
	inline mv gpEM(const mv& x, const mv& y);
	inline scalar scpEM(const mv& x, const mv& y);
	inline mv lcontEM(const mv& x, const mv& y);
	inline mv op(const mv& x, const mv& y);
	inline mv add(const mv& x, const mv& y);
	inline mv subtract(const mv& x, const mv& y);
	inline scalar norm_e2(const mv& x);
	inline scalar norm_e(const mv& x);
	inline mv unit_e(const mv& x);
	inline scalar norm_r2(const mv& x);
	inline scalar norm_r(const mv& x);
	inline mv unit_r(const mv& x);
	inline mv reverse(const mv& x);
	inline mv negate(const mv& x);
	inline mv dual(const mv& x);
	inline mv undual(const mv& x);
	inline mv inverse(const mv& x);
	inline mv inverseEM(const mv& x);
	inline mv apply_om(const om& x, const mv& y);
	inline mv gradeInvolution(const mv& x);
	inline normalizedPoint c3gaPoint(const vectorE3GA& l);
	namespace __G2_GENERATED__ {
		inline void set(om& __x__, const point& __image_of_no__, const point& __image_of_e1__, const point& __image_of_e2__, const point& __image_of_e3__, const point& __image_of_ni__);
	} /* end of namespace __G2_GENERATED__ */
	inline mv operator+=(mv& arg1, const mv& arg2);
	inline no_t operator+=(no_t& arg1, const mv& arg2);
	inline e1_t operator+=(e1_t& arg1, const mv& arg2);
	inline e2_t operator+=(e2_t& arg1, const mv& arg2);
	inline e3_t operator+=(e3_t& arg1, const mv& arg2);
	inline ni_t operator+=(ni_t& arg1, const mv& arg2);
	inline scalar operator+=(scalar& arg1, const mv& arg2);
	inline point operator+=(point& arg1, const mv& arg2);
	inline normalizedPoint operator+=(normalizedPoint& arg1, const mv& arg2);
	inline flatPoint operator+=(flatPoint& arg1, const mv& arg2);
	inline normalizedFlatPoint operator+=(normalizedFlatPoint& arg1, const mv& arg2);
	inline pointPair operator+=(pointPair& arg1, const mv& arg2);
	inline line operator+=(line& arg1, const mv& arg2);
	inline dualLine operator+=(dualLine& arg1, const mv& arg2);
	inline plane operator+=(plane& arg1, const mv& arg2);
	inline dualPlane operator+=(dualPlane& arg1, const mv& arg2);
	inline circle operator+=(circle& arg1, const mv& arg2);
	inline sphere operator+=(sphere& arg1, const mv& arg2);
	inline dualSphere operator+=(dualSphere& arg1, const mv& arg2);
	inline normalizedSphere operator+=(normalizedSphere& arg1, const mv& arg2);
	inline normalizedDualSphere operator+=(normalizedDualSphere& arg1, const mv& arg2);
	inline freeVector operator+=(freeVector& arg1, const mv& arg2);
	inline freeBivector operator+=(freeBivector& arg1, const mv& arg2);
	inline freeTrivector operator+=(freeTrivector& arg1, const mv& arg2);
	inline tangentVector operator+=(tangentVector& arg1, const mv& arg2);
	inline tangentBivector operator+=(tangentBivector& arg1, const mv& arg2);
	inline vectorE2GA operator+=(vectorE2GA& arg1, const mv& arg2);
	inline vectorE3GA operator+=(vectorE3GA& arg1, const mv& arg2);
	inline bivectorE3GA operator+=(bivectorE3GA& arg1, const mv& arg2);
	inline TRversor operator+=(TRversor& arg1, const mv& arg2);
	inline TRSversor operator+=(TRSversor& arg1, const mv& arg2);
	inline evenVersor operator+=(evenVersor& arg1, const mv& arg2);
	inline translator operator+=(translator& arg1, const mv& arg2);
	inline normalizedTranslator operator+=(normalizedTranslator& arg1, const mv& arg2);
	inline rotor operator+=(rotor& arg1, const mv& arg2);
	inline scalor operator+=(scalor& arg1, const mv& arg2);
	inline __no_ct__ operator+=(__no_ct__& arg1, const mv& arg2);
	inline __e1_ct__ operator+=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator+=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator+=(__e3_ct__& arg1, const mv& arg2);
	inline __ni_ct__ operator+=(__ni_ct__& arg1, const mv& arg2);
	inline mv operator+(const mv& arg1, const mv& arg2);
	inline mv operator-=(mv& arg1, const mv& arg2);
	inline no_t operator-=(no_t& arg1, const mv& arg2);
	inline e1_t operator-=(e1_t& arg1, const mv& arg2);
	inline e2_t operator-=(e2_t& arg1, const mv& arg2);
	inline e3_t operator-=(e3_t& arg1, const mv& arg2);
	inline ni_t operator-=(ni_t& arg1, const mv& arg2);
	inline scalar operator-=(scalar& arg1, const mv& arg2);
	inline point operator-=(point& arg1, const mv& arg2);
	inline normalizedPoint operator-=(normalizedPoint& arg1, const mv& arg2);
	inline flatPoint operator-=(flatPoint& arg1, const mv& arg2);
	inline normalizedFlatPoint operator-=(normalizedFlatPoint& arg1, const mv& arg2);
	inline pointPair operator-=(pointPair& arg1, const mv& arg2);
	inline line operator-=(line& arg1, const mv& arg2);
	inline dualLine operator-=(dualLine& arg1, const mv& arg2);
	inline plane operator-=(plane& arg1, const mv& arg2);
	inline dualPlane operator-=(dualPlane& arg1, const mv& arg2);
	inline circle operator-=(circle& arg1, const mv& arg2);
	inline sphere operator-=(sphere& arg1, const mv& arg2);
	inline dualSphere operator-=(dualSphere& arg1, const mv& arg2);
	inline normalizedSphere operator-=(normalizedSphere& arg1, const mv& arg2);
	inline normalizedDualSphere operator-=(normalizedDualSphere& arg1, const mv& arg2);
	inline freeVector operator-=(freeVector& arg1, const mv& arg2);
	inline freeBivector operator-=(freeBivector& arg1, const mv& arg2);
	inline freeTrivector operator-=(freeTrivector& arg1, const mv& arg2);
	inline tangentVector operator-=(tangentVector& arg1, const mv& arg2);
	inline tangentBivector operator-=(tangentBivector& arg1, const mv& arg2);
	inline vectorE2GA operator-=(vectorE2GA& arg1, const mv& arg2);
	inline vectorE3GA operator-=(vectorE3GA& arg1, const mv& arg2);
	inline bivectorE3GA operator-=(bivectorE3GA& arg1, const mv& arg2);
	inline TRversor operator-=(TRversor& arg1, const mv& arg2);
	inline TRSversor operator-=(TRSversor& arg1, const mv& arg2);
	inline evenVersor operator-=(evenVersor& arg1, const mv& arg2);
	inline translator operator-=(translator& arg1, const mv& arg2);
	inline normalizedTranslator operator-=(normalizedTranslator& arg1, const mv& arg2);
	inline rotor operator-=(rotor& arg1, const mv& arg2);
	inline scalor operator-=(scalor& arg1, const mv& arg2);
	inline __no_ct__ operator-=(__no_ct__& arg1, const mv& arg2);
	inline __e1_ct__ operator-=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator-=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator-=(__e3_ct__& arg1, const mv& arg2);
	inline __ni_ct__ operator-=(__ni_ct__& arg1, const mv& arg2);
	inline mv operator-(const mv& arg1, const mv& arg2);
	inline mv operator-(const mv& arg1);
	inline mv operator%=(mv& arg1, const mv& arg2);
	inline no_t operator%=(no_t& arg1, const mv& arg2);
	inline e1_t operator%=(e1_t& arg1, const mv& arg2);
	inline e2_t operator%=(e2_t& arg1, const mv& arg2);
	inline e3_t operator%=(e3_t& arg1, const mv& arg2);
	inline ni_t operator%=(ni_t& arg1, const mv& arg2);
	inline scalar operator%=(scalar& arg1, const mv& arg2);
	inline point operator%=(point& arg1, const mv& arg2);
	inline normalizedPoint operator%=(normalizedPoint& arg1, const mv& arg2);
	inline flatPoint operator%=(flatPoint& arg1, const mv& arg2);
	inline normalizedFlatPoint operator%=(normalizedFlatPoint& arg1, const mv& arg2);
	inline pointPair operator%=(pointPair& arg1, const mv& arg2);
	inline line operator%=(line& arg1, const mv& arg2);
	inline dualLine operator%=(dualLine& arg1, const mv& arg2);
	inline plane operator%=(plane& arg1, const mv& arg2);
	inline dualPlane operator%=(dualPlane& arg1, const mv& arg2);
	inline circle operator%=(circle& arg1, const mv& arg2);
	inline sphere operator%=(sphere& arg1, const mv& arg2);
	inline dualSphere operator%=(dualSphere& arg1, const mv& arg2);
	inline normalizedSphere operator%=(normalizedSphere& arg1, const mv& arg2);
	inline normalizedDualSphere operator%=(normalizedDualSphere& arg1, const mv& arg2);
	inline freeVector operator%=(freeVector& arg1, const mv& arg2);
	inline freeBivector operator%=(freeBivector& arg1, const mv& arg2);
	inline freeTrivector operator%=(freeTrivector& arg1, const mv& arg2);
	inline tangentVector operator%=(tangentVector& arg1, const mv& arg2);
	inline tangentBivector operator%=(tangentBivector& arg1, const mv& arg2);
	inline vectorE2GA operator%=(vectorE2GA& arg1, const mv& arg2);
	inline vectorE3GA operator%=(vectorE3GA& arg1, const mv& arg2);
	inline bivectorE3GA operator%=(bivectorE3GA& arg1, const mv& arg2);
	inline TRversor operator%=(TRversor& arg1, const mv& arg2);
	inline TRSversor operator%=(TRSversor& arg1, const mv& arg2);
	inline evenVersor operator%=(evenVersor& arg1, const mv& arg2);
	inline translator operator%=(translator& arg1, const mv& arg2);
	inline normalizedTranslator operator%=(normalizedTranslator& arg1, const mv& arg2);
	inline rotor operator%=(rotor& arg1, const mv& arg2);
	inline scalor operator%=(scalor& arg1, const mv& arg2);
	inline __no_ct__ operator%=(__no_ct__& arg1, const mv& arg2);
	inline __e1_ct__ operator%=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator%=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator%=(__e3_ct__& arg1, const mv& arg2);
	inline __ni_ct__ operator%=(__ni_ct__& arg1, const mv& arg2);
	inline scalar operator%(const mv& arg1, const mv& arg2);
	inline mv operator^=(mv& arg1, const mv& arg2);
	inline no_t operator^=(no_t& arg1, const mv& arg2);
	inline e1_t operator^=(e1_t& arg1, const mv& arg2);
	inline e2_t operator^=(e2_t& arg1, const mv& arg2);
	inline e3_t operator^=(e3_t& arg1, const mv& arg2);
	inline ni_t operator^=(ni_t& arg1, const mv& arg2);
	inline scalar operator^=(scalar& arg1, const mv& arg2);
	inline point operator^=(point& arg1, const mv& arg2);
	inline normalizedPoint operator^=(normalizedPoint& arg1, const mv& arg2);
	inline flatPoint operator^=(flatPoint& arg1, const mv& arg2);
	inline normalizedFlatPoint operator^=(normalizedFlatPoint& arg1, const mv& arg2);
	inline pointPair operator^=(pointPair& arg1, const mv& arg2);
	inline line operator^=(line& arg1, const mv& arg2);
	inline dualLine operator^=(dualLine& arg1, const mv& arg2);
	inline plane operator^=(plane& arg1, const mv& arg2);
	inline dualPlane operator^=(dualPlane& arg1, const mv& arg2);
	inline circle operator^=(circle& arg1, const mv& arg2);
	inline sphere operator^=(sphere& arg1, const mv& arg2);
	inline dualSphere operator^=(dualSphere& arg1, const mv& arg2);
	inline normalizedSphere operator^=(normalizedSphere& arg1, const mv& arg2);
	inline normalizedDualSphere operator^=(normalizedDualSphere& arg1, const mv& arg2);
	inline freeVector operator^=(freeVector& arg1, const mv& arg2);
	inline freeBivector operator^=(freeBivector& arg1, const mv& arg2);
	inline freeTrivector operator^=(freeTrivector& arg1, const mv& arg2);
	inline tangentVector operator^=(tangentVector& arg1, const mv& arg2);
	inline tangentBivector operator^=(tangentBivector& arg1, const mv& arg2);
	inline vectorE2GA operator^=(vectorE2GA& arg1, const mv& arg2);
	inline vectorE3GA operator^=(vectorE3GA& arg1, const mv& arg2);
	inline bivectorE3GA operator^=(bivectorE3GA& arg1, const mv& arg2);
	inline TRversor operator^=(TRversor& arg1, const mv& arg2);
	inline TRSversor operator^=(TRSversor& arg1, const mv& arg2);
	inline evenVersor operator^=(evenVersor& arg1, const mv& arg2);
	inline translator operator^=(translator& arg1, const mv& arg2);
	inline normalizedTranslator operator^=(normalizedTranslator& arg1, const mv& arg2);
	inline rotor operator^=(rotor& arg1, const mv& arg2);
	inline scalor operator^=(scalor& arg1, const mv& arg2);
	inline __no_ct__ operator^=(__no_ct__& arg1, const mv& arg2);
	inline __e1_ct__ operator^=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator^=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator^=(__e3_ct__& arg1, const mv& arg2);
	inline __ni_ct__ operator^=(__ni_ct__& arg1, const mv& arg2);
	inline mv operator^(const mv& arg1, const mv& arg2);
	inline mv operator*=(mv& arg1, const mv& arg2);
	inline no_t operator*=(no_t& arg1, const mv& arg2);
	inline e1_t operator*=(e1_t& arg1, const mv& arg2);
	inline e2_t operator*=(e2_t& arg1, const mv& arg2);
	inline e3_t operator*=(e3_t& arg1, const mv& arg2);
	inline ni_t operator*=(ni_t& arg1, const mv& arg2);
	inline scalar operator*=(scalar& arg1, const mv& arg2);
	inline point operator*=(point& arg1, const mv& arg2);
	inline normalizedPoint operator*=(normalizedPoint& arg1, const mv& arg2);
	inline flatPoint operator*=(flatPoint& arg1, const mv& arg2);
	inline normalizedFlatPoint operator*=(normalizedFlatPoint& arg1, const mv& arg2);
	inline pointPair operator*=(pointPair& arg1, const mv& arg2);
	inline line operator*=(line& arg1, const mv& arg2);
	inline dualLine operator*=(dualLine& arg1, const mv& arg2);
	inline plane operator*=(plane& arg1, const mv& arg2);
	inline dualPlane operator*=(dualPlane& arg1, const mv& arg2);
	inline circle operator*=(circle& arg1, const mv& arg2);
	inline sphere operator*=(sphere& arg1, const mv& arg2);
	inline dualSphere operator*=(dualSphere& arg1, const mv& arg2);
	inline normalizedSphere operator*=(normalizedSphere& arg1, const mv& arg2);
	inline normalizedDualSphere operator*=(normalizedDualSphere& arg1, const mv& arg2);
	inline freeVector operator*=(freeVector& arg1, const mv& arg2);
	inline freeBivector operator*=(freeBivector& arg1, const mv& arg2);
	inline freeTrivector operator*=(freeTrivector& arg1, const mv& arg2);
	inline tangentVector operator*=(tangentVector& arg1, const mv& arg2);
	inline tangentBivector operator*=(tangentBivector& arg1, const mv& arg2);
	inline vectorE2GA operator*=(vectorE2GA& arg1, const mv& arg2);
	inline vectorE3GA operator*=(vectorE3GA& arg1, const mv& arg2);
	inline bivectorE3GA operator*=(bivectorE3GA& arg1, const mv& arg2);
	inline TRversor operator*=(TRversor& arg1, const mv& arg2);
	inline TRSversor operator*=(TRSversor& arg1, const mv& arg2);
	inline evenVersor operator*=(evenVersor& arg1, const mv& arg2);
	inline translator operator*=(translator& arg1, const mv& arg2);
	inline normalizedTranslator operator*=(normalizedTranslator& arg1, const mv& arg2);
	inline rotor operator*=(rotor& arg1, const mv& arg2);
	inline scalor operator*=(scalor& arg1, const mv& arg2);
	inline __no_ct__ operator*=(__no_ct__& arg1, const mv& arg2);
	inline __e1_ct__ operator*=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator*=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator*=(__e3_ct__& arg1, const mv& arg2);
	inline __ni_ct__ operator*=(__ni_ct__& arg1, const mv& arg2);
	inline mv operator*(const mv& arg1, const mv& arg2);
	inline mv operator<<=(mv& arg1, const mv& arg2);
	inline no_t operator<<=(no_t& arg1, const mv& arg2);
	inline e1_t operator<<=(e1_t& arg1, const mv& arg2);
	inline e2_t operator<<=(e2_t& arg1, const mv& arg2);
	inline e3_t operator<<=(e3_t& arg1, const mv& arg2);
	inline ni_t operator<<=(ni_t& arg1, const mv& arg2);
	inline scalar operator<<=(scalar& arg1, const mv& arg2);
	inline point operator<<=(point& arg1, const mv& arg2);
	inline normalizedPoint operator<<=(normalizedPoint& arg1, const mv& arg2);
	inline flatPoint operator<<=(flatPoint& arg1, const mv& arg2);
	inline normalizedFlatPoint operator<<=(normalizedFlatPoint& arg1, const mv& arg2);
	inline pointPair operator<<=(pointPair& arg1, const mv& arg2);
	inline line operator<<=(line& arg1, const mv& arg2);
	inline dualLine operator<<=(dualLine& arg1, const mv& arg2);
	inline plane operator<<=(plane& arg1, const mv& arg2);
	inline dualPlane operator<<=(dualPlane& arg1, const mv& arg2);
	inline circle operator<<=(circle& arg1, const mv& arg2);
	inline sphere operator<<=(sphere& arg1, const mv& arg2);
	inline dualSphere operator<<=(dualSphere& arg1, const mv& arg2);
	inline normalizedSphere operator<<=(normalizedSphere& arg1, const mv& arg2);
	inline normalizedDualSphere operator<<=(normalizedDualSphere& arg1, const mv& arg2);
	inline freeVector operator<<=(freeVector& arg1, const mv& arg2);
	inline freeBivector operator<<=(freeBivector& arg1, const mv& arg2);
	inline freeTrivector operator<<=(freeTrivector& arg1, const mv& arg2);
	inline tangentVector operator<<=(tangentVector& arg1, const mv& arg2);
	inline tangentBivector operator<<=(tangentBivector& arg1, const mv& arg2);
	inline vectorE2GA operator<<=(vectorE2GA& arg1, const mv& arg2);
	inline vectorE3GA operator<<=(vectorE3GA& arg1, const mv& arg2);
	inline bivectorE3GA operator<<=(bivectorE3GA& arg1, const mv& arg2);
	inline TRversor operator<<=(TRversor& arg1, const mv& arg2);
	inline TRSversor operator<<=(TRSversor& arg1, const mv& arg2);
	inline evenVersor operator<<=(evenVersor& arg1, const mv& arg2);
	inline translator operator<<=(translator& arg1, const mv& arg2);
	inline normalizedTranslator operator<<=(normalizedTranslator& arg1, const mv& arg2);
	inline rotor operator<<=(rotor& arg1, const mv& arg2);
	inline scalor operator<<=(scalor& arg1, const mv& arg2);
	inline __no_ct__ operator<<=(__no_ct__& arg1, const mv& arg2);
	inline __e1_ct__ operator<<=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator<<=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator<<=(__e3_ct__& arg1, const mv& arg2);
	inline __ni_ct__ operator<<=(__ni_ct__& arg1, const mv& arg2);
	inline mv operator<<(const mv& arg1, const mv& arg2);
	inline mv operator*(const mv& arg1);
	inline mv operator!(const mv& arg1);
	inline mv operator~(const mv& arg1);







	// set to 0
	inline void mv::set() {
		// set grade usage
		gu(0);

	}

	// set to copy 
	inline void mv::set(const mv &arg1) {
		// copy grade usage
		gu(arg1.gu());
		// copy coordinates
		mv_memcpy(m_c, arg1.m_c, mv_size[gu()]);

	}

	// set to scalar
	inline void mv::set(Float scalarVal) {
		// set grade usage
		gu(1);
		// set type (if profile)
		// set coordinate
		m_c[0] = scalarVal;

	}


	// set to coordinates 
	inline void mv::set(unsigned int gradeUsage, const Float *coordinates) {
		// set grade usage
		gu(gradeUsage);
		// set coordinates
		mv_memcpy(m_c, coordinates, mv_size[gu()]);

	}


	// set to 1 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 1)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;

	}

	// set to 2 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 2)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;

	}

	// set to 3 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 3)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;

	}

	// set to 4 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 4)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;

	}

	// set to 5 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 5)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;

	}

	// set to 6 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 6)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;

	}

	// set to 7 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 7)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;

	}

	// set to 8 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 8)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;

	}

	// set to 9 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 9)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;

	}

	// set to 10 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 10)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;

	}

	// set to 11 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 11)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;

	}

	// set to 12 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 12)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;

	}

	// set to 13 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 13)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;

	}

	// set to 14 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 14)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;

	}

	// set to 15 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 15)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;

	}

	// set to 16 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 16)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;

	}

	// set to 17 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 17)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;

	}

	// set to 18 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 18)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;

	}

	// set to 19 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 19)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;

	}

	// set to 20 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 20)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;

	}

	// set to 21 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 21)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;

	}

	// set to 22 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 22)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;

	}

	// set to 23 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 23)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;

	}

	// set to 24 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 24)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;

	}

	// set to 25 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 25)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;

	}

	// set to 26 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 26)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;

	}

	// set to 27 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 27)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;

	}

	// set to 28 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 28)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;

	}

	// set to 29 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 29)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;
		m_c[28] = c28;

	}

	// set to 30 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 30)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;
		m_c[28] = c28;
		m_c[29] = c29;

	}

	// set to 31 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29, Float c30	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 31)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;
		m_c[28] = c28;
		m_c[29] = c29;
		m_c[30] = c30;

	}

	// set to 32 coordinates 
	inline void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29, Float c30, Float c31	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 32)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;
		m_c[28] = c28;
		m_c[29] = c29;
		m_c[30] = c30;
		m_c[31] = c31;

	}



	// set to no_t 
	inline void mv::set(const no_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to e1_t 
	inline void mv::set(const e1_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to e2_t 
	inline void mv::set(const e2_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[0] ;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to e3_t 
	inline void mv::set(const e3_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = (Float)0;


	}
	// set to ni_t 
	inline void mv::set(const ni_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = arg1.m_c[0] ;


	}
	// set to scalar 
	inline void mv::set(const scalar & arg1) {

		// set grade usage 
		gu(1);


		m_c[0] = arg1.m_c[0] ;


	}
	// set to point 
	inline void mv::set(const point & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;


	}
	// set to normalizedPoint 
	inline void mv::set(const normalizedPoint & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)1.0f; 
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;
		m_c[4] = arg1.m_c[3] ;


	}
	// set to flatPoint 
	inline void mv::set(const flatPoint & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = arg1.m_c[0] ;
		m_c[7] = arg1.m_c[1] ;
		m_c[8] = arg1.m_c[2] ;
		m_c[9] = arg1.m_c[3] ;


	}
	// set to normalizedFlatPoint 
	inline void mv::set(const normalizedFlatPoint & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = arg1.m_c[0] ;
		m_c[7] = arg1.m_c[1] ;
		m_c[8] = arg1.m_c[2] ;
		m_c[9] = (Float)1.0f; 


	}
	// set to pointPair 
	inline void mv::set(const pointPair & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;
		m_c[6] = arg1.m_c[6] ;
		m_c[7] = arg1.m_c[7] ;
		m_c[8] = arg1.m_c[8] ;
		m_c[9] = arg1.m_c[9] ;


	}
	// set to line 
	inline void mv::set(const line & arg1) {

		// set grade usage 
		gu(8);


		m_c[0] = arg1.m_c[2] ;
		m_c[1] = arg1.m_c[1] * (Float)-1.0;
		m_c[2] = arg1.m_c[0] ;
		m_c[3] = arg1.m_c[5] * (Float)-1.0;
		m_c[4] = arg1.m_c[3] * (Float)-1.0;
		m_c[5] = arg1.m_c[4] * (Float)-1.0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;


	}
	// set to dualLine 
	inline void mv::set(const dualLine & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = arg1.m_c[2] ;
		m_c[5] = arg1.m_c[1] * (Float)-1.0;
		m_c[6] = arg1.m_c[3] ;
		m_c[7] = arg1.m_c[4] ;
		m_c[8] = arg1.m_c[5] ;
		m_c[9] = (Float)0;


	}
	// set to plane 
	inline void mv::set(const plane & arg1) {

		// set grade usage 
		gu(16);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[3] ;
		m_c[2] = arg1.m_c[2] * (Float)-1.0;
		m_c[3] = arg1.m_c[1] ;
		m_c[4] = (Float)0;


	}
	// set to dualPlane 
	inline void mv::set(const dualPlane & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;
		m_c[4] = arg1.m_c[3] ;


	}
	// set to circle 
	inline void mv::set(const circle & arg1) {

		// set grade usage 
		gu(8);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;
		m_c[6] = arg1.m_c[6] ;
		m_c[7] = arg1.m_c[7] ;
		m_c[8] = arg1.m_c[8] ;
		m_c[9] = arg1.m_c[9] ;


	}
	// set to sphere 
	inline void mv::set(const sphere & arg1) {

		// set grade usage 
		gu(16);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[3] ;
		m_c[2] = arg1.m_c[2] * (Float)-1.0;
		m_c[3] = arg1.m_c[1] ;
		m_c[4] = arg1.m_c[4] * (Float)-1.0;


	}
	// set to dualSphere 
	inline void mv::set(const dualSphere & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;


	}
	// set to normalizedSphere 
	inline void mv::set(const normalizedSphere & arg1) {

		// set grade usage 
		gu(16);


		m_c[0] = (Float)1.0f; 
		m_c[1] = arg1.m_c[2] ;
		m_c[2] = arg1.m_c[1] * (Float)-1.0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = arg1.m_c[3] * (Float)-1.0;


	}
	// set to normalizedDualSphere 
	inline void mv::set(const normalizedDualSphere & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)1.0f; 
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;
		m_c[4] = arg1.m_c[3] ;


	}
	// set to freeVector 
	inline void mv::set(const freeVector & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = arg1.m_c[0] ;
		m_c[7] = arg1.m_c[1] ;
		m_c[8] = arg1.m_c[2] ;
		m_c[9] = (Float)0;


	}
	// set to freeBivector 
	inline void mv::set(const freeBivector & arg1) {

		// set grade usage 
		gu(8);


		m_c[0] = arg1.m_c[1] ;
		m_c[1] = arg1.m_c[2] ;
		m_c[2] = arg1.m_c[0] ;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;


	}
	// set to freeTrivector 
	inline void mv::set(const freeTrivector & arg1) {

		// set grade usage 
		gu(16);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to tangentVector 
	inline void mv::set(const tangentVector & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;
		m_c[6] = arg1.m_c[6] ;
		m_c[7] = arg1.m_c[7] ;
		m_c[8] = arg1.m_c[8] ;
		m_c[9] = arg1.m_c[9] ;


	}
	// set to tangentBivector 
	inline void mv::set(const tangentBivector & arg1) {

		// set grade usage 
		gu(8);


		m_c[0] = arg1.m_c[1] ;
		m_c[1] = arg1.m_c[2] ;
		m_c[2] = arg1.m_c[3] ;
		m_c[3] = arg1.m_c[4] ;
		m_c[4] = arg1.m_c[5] ;
		m_c[5] = arg1.m_c[6] ;
		m_c[6] = arg1.m_c[7] ;
		m_c[7] = arg1.m_c[8] ;
		m_c[8] = arg1.m_c[9] ;
		m_c[9] = arg1.m_c[0] ;


	}
	// set to vectorE2GA 
	inline void mv::set(const vectorE2GA & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to vectorE3GA 
	inline void mv::set(const vectorE3GA & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;
		m_c[4] = (Float)0;


	}
	// set to bivectorE3GA 
	inline void mv::set(const bivectorE3GA & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[2] ;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;


	}
	// set to TRversor 
	inline void mv::set(const TRversor & arg1) {

		// set grade usage 
		gu(21);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[3] ;
		m_c[6] = arg1.m_c[2] * (Float)-1.0;
		m_c[7] = arg1.m_c[4] ;
		m_c[8] = arg1.m_c[5] ;
		m_c[9] = arg1.m_c[6] ;
		m_c[10] = (Float)0;
		m_c[11] = arg1.m_c[7] ;
		m_c[12] = (Float)0;
		m_c[13] = (Float)0;
		m_c[14] = (Float)0;
		m_c[15] = (Float)0;


	}
	// set to TRSversor 
	inline void mv::set(const TRSversor & arg1) {

		// set grade usage 
		gu(21);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[3] ;
		m_c[6] = arg1.m_c[2] * (Float)-1.0;
		m_c[7] = arg1.m_c[4] ;
		m_c[8] = arg1.m_c[5] ;
		m_c[9] = arg1.m_c[6] ;
		m_c[10] = arg1.m_c[7] ;
		m_c[11] = arg1.m_c[11] ;
		m_c[12] = arg1.m_c[10] ;
		m_c[13] = arg1.m_c[9] * (Float)-1.0;
		m_c[14] = arg1.m_c[8] ;
		m_c[15] = (Float)0;


	}
	// set to evenVersor 
	inline void mv::set(const evenVersor & arg1) {

		// set grade usage 
		gu(21);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;
		m_c[6] = arg1.m_c[6] ;
		m_c[7] = arg1.m_c[7] ;
		m_c[8] = arg1.m_c[8] ;
		m_c[9] = arg1.m_c[9] ;
		m_c[10] = arg1.m_c[10] ;
		m_c[11] = arg1.m_c[11] ;
		m_c[12] = arg1.m_c[14] ;
		m_c[13] = arg1.m_c[13] * (Float)-1.0;
		m_c[14] = arg1.m_c[12] ;
		m_c[15] = arg1.m_c[15] * (Float)-1.0;


	}
	// set to translator 
	inline void mv::set(const translator & arg1) {

		// set grade usage 
		gu(5);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = arg1.m_c[1] ;
		m_c[8] = arg1.m_c[2] ;
		m_c[9] = arg1.m_c[3] ;
		m_c[10] = (Float)0;


	}
	// set to normalizedTranslator 
	inline void mv::set(const normalizedTranslator & arg1) {

		// set grade usage 
		gu(5);


		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = arg1.m_c[0] ;
		m_c[8] = arg1.m_c[1] ;
		m_c[9] = arg1.m_c[2] ;
		m_c[10] = (Float)0;


	}
	// set to rotor 
	inline void mv::set(const rotor & arg1) {

		// set grade usage 
		gu(5);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[2] ;
		m_c[6] = arg1.m_c[3] ;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;
		m_c[10] = (Float)0;


	}
	// set to scalor 
	inline void mv::set(const scalor & arg1) {

		// set grade usage 
		gu(5);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;
		m_c[10] = arg1.m_c[1] ;


	}
	// set to __no_ct__ 
	inline void mv::set(const __no_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to __e1_ct__ 
	inline void mv::set(const __e1_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)1.0f; 
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to __e2_ct__ 
	inline void mv::set(const __e2_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)1.0f; 
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to __e3_ct__ 
	inline void mv::set(const __e3_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)1.0f; 
		m_c[4] = (Float)0;


	}
	// set to __ni_ct__ 
	inline void mv::set(const __ni_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)1.0f; 


	}






	// assign copy
	inline mv& mv::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}


	// assign scalar
	inline mv& mv::operator=(Float s) {
		set(s);
		return *this;
	}

	// assign no_t 
	inline mv& mv::operator=(const no_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e1_t 
	inline mv& mv::operator=(const e1_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e2_t 
	inline mv& mv::operator=(const e2_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e3_t 
	inline mv& mv::operator=(const e3_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign ni_t 
	inline mv& mv::operator=(const ni_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign scalar 
	inline mv& mv::operator=(const scalar& arg1) {
		set(arg1);
		return *this;
	}
	// assign point 
	inline mv& mv::operator=(const point& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedPoint 
	inline mv& mv::operator=(const normalizedPoint& arg1) {
		set(arg1);
		return *this;
	}
	// assign flatPoint 
	inline mv& mv::operator=(const flatPoint& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedFlatPoint 
	inline mv& mv::operator=(const normalizedFlatPoint& arg1) {
		set(arg1);
		return *this;
	}
	// assign pointPair 
	inline mv& mv::operator=(const pointPair& arg1) {
		set(arg1);
		return *this;
	}
	// assign line 
	inline mv& mv::operator=(const line& arg1) {
		set(arg1);
		return *this;
	}
	// assign dualLine 
	inline mv& mv::operator=(const dualLine& arg1) {
		set(arg1);
		return *this;
	}
	// assign plane 
	inline mv& mv::operator=(const plane& arg1) {
		set(arg1);
		return *this;
	}
	// assign dualPlane 
	inline mv& mv::operator=(const dualPlane& arg1) {
		set(arg1);
		return *this;
	}
	// assign circle 
	inline mv& mv::operator=(const circle& arg1) {
		set(arg1);
		return *this;
	}
	// assign sphere 
	inline mv& mv::operator=(const sphere& arg1) {
		set(arg1);
		return *this;
	}
	// assign dualSphere 
	inline mv& mv::operator=(const dualSphere& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedSphere 
	inline mv& mv::operator=(const normalizedSphere& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedDualSphere 
	inline mv& mv::operator=(const normalizedDualSphere& arg1) {
		set(arg1);
		return *this;
	}
	// assign freeVector 
	inline mv& mv::operator=(const freeVector& arg1) {
		set(arg1);
		return *this;
	}
	// assign freeBivector 
	inline mv& mv::operator=(const freeBivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign freeTrivector 
	inline mv& mv::operator=(const freeTrivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign tangentVector 
	inline mv& mv::operator=(const tangentVector& arg1) {
		set(arg1);
		return *this;
	}
	// assign tangentBivector 
	inline mv& mv::operator=(const tangentBivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign vectorE2GA 
	inline mv& mv::operator=(const vectorE2GA& arg1) {
		set(arg1);
		return *this;
	}
	// assign vectorE3GA 
	inline mv& mv::operator=(const vectorE3GA& arg1) {
		set(arg1);
		return *this;
	}
	// assign bivectorE3GA 
	inline mv& mv::operator=(const bivectorE3GA& arg1) {
		set(arg1);
		return *this;
	}
	// assign TRversor 
	inline mv& mv::operator=(const TRversor& arg1) {
		set(arg1);
		return *this;
	}
	// assign TRSversor 
	inline mv& mv::operator=(const TRSversor& arg1) {
		set(arg1);
		return *this;
	}
	// assign evenVersor 
	inline mv& mv::operator=(const evenVersor& arg1) {
		set(arg1);
		return *this;
	}
	// assign translator 
	inline mv& mv::operator=(const translator& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedTranslator 
	inline mv& mv::operator=(const normalizedTranslator& arg1) {
		set(arg1);
		return *this;
	}
	// assign rotor 
	inline mv& mv::operator=(const rotor& arg1) {
		set(arg1);
		return *this;
	}
	// assign scalor 
	inline mv& mv::operator=(const scalor& arg1) {
		set(arg1);
		return *this;
	}
	// assign __no_ct__ 
	inline mv& mv::operator=(const __no_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e1_ct__ 
	inline mv& mv::operator=(const __e1_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e2_ct__ 
	inline mv& mv::operator=(const __e2_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e3_ct__ 
	inline mv& mv::operator=(const __e3_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __ni_ct__ 
	inline mv& mv::operator=(const __ni_ct__& arg1) {
		set(arg1);
		return *this;
	}










	// set to zero
	inline void no_t::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void no_t::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;

	}


	// set to copy
	inline void no_t::set(const no_t &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void no_t::set(__no_t_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void no_t::set(__no_t_coordinates__, Float c_no) {
		// set coordinates
		m_c[0] = c_no;

	}

	// set to mv 
	inline void no_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}





	// assign copy
	inline no_t &no_t::operator=(const no_t &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline no_t &no_t::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline no_t &no_t::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void e1_t::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void e1_t::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;

	}


	// set to copy
	inline void e1_t::set(const e1_t &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void e1_t::set(__e1_t_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void e1_t::set(__e1_t_coordinates__, Float c_e1) {
		// set coordinates
		m_c[0] = c_e1;

	}

	// set to mv 
	inline void e1_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}





	// assign copy
	inline e1_t &e1_t::operator=(const e1_t &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline e1_t &e1_t::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline e1_t &e1_t::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void e2_t::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void e2_t::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;

	}


	// set to copy
	inline void e2_t::set(const e2_t &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void e2_t::set(__e2_t_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void e2_t::set(__e2_t_coordinates__, Float c_e2) {
		// set coordinates
		m_c[0] = c_e2;

	}

	// set to mv 
	inline void e2_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}





	// assign copy
	inline e2_t &e2_t::operator=(const e2_t &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline e2_t &e2_t::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline e2_t &e2_t::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void e3_t::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void e3_t::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;

	}


	// set to copy
	inline void e3_t::set(const e3_t &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void e3_t::set(__e3_t_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void e3_t::set(__e3_t_coordinates__, Float c_e3) {
		// set coordinates
		m_c[0] = c_e3;

	}

	// set to mv 
	inline void e3_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 3];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}





	// assign copy
	inline e3_t &e3_t::operator=(const e3_t &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline e3_t &e3_t::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline e3_t &e3_t::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void ni_t::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void ni_t::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;

	}


	// set to copy
	inline void ni_t::set(const ni_t &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void ni_t::set(__ni_t_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void ni_t::set(__ni_t_coordinates__, Float c_ni) {
		// set coordinates
		m_c[0] = c_ni;

	}

	// set to mv 
	inline void ni_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}





	// assign copy
	inline ni_t &ni_t::operator=(const ni_t &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline ni_t &ni_t::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline ni_t &ni_t::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void scalar::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void scalar::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = s ;

	}


	// set to copy
	inline void scalar::set(const scalar &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void scalar::set(__scalar_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void scalar::set(__scalar_coordinates__, Float c_scalar) {
		// set coordinates
		m_c[0] = c_scalar;

	}

	// set to mv 
	inline void scalar::set(const mv & arg1) {


		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}





	// assign copy
	inline scalar &scalar::operator=(const scalar &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline scalar &scalar::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline scalar &scalar::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void point::set() {
		// set coordinates to 0
		mv_zero(m_c, 5);

	}

	// set to scalar 
	inline void point::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;

	}


	// set to copy
	inline void point::set(const point &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 5);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];

	}

	// set to pointer to coordinates
	inline void point::set(__point_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 5);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];

	}

	// set to 'coordinates specified' 
	inline void point::set(__point_coordinates__, Float c_no, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {
		// set coordinates
		m_c[0] = c_no;
		m_c[1] = c_e1;
		m_c[2] = c_e2;
		m_c[3] = c_e3;
		m_c[4] = c_ni;

	}

	// set to mv 
	inline void point::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
		}


	}





	// assign copy
	inline point &point::operator=(const point &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline point &point::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline point &point::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void normalizedPoint::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void normalizedPoint::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void normalizedPoint::set(const normalizedPoint &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void normalizedPoint::set(__normalizedPoint_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void normalizedPoint::set(__normalizedPoint_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {
		// set coordinates
		m_c[0] = c_e1;
		m_c[1] = c_e2;
		m_c[2] = c_e3;
		m_c[3] = c_ni;

	}

	// set to mv 
	inline void normalizedPoint::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			m_c[2] = arg1.m_c[gidx + 3];
			m_c[3] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}





	// assign copy
	inline normalizedPoint &normalizedPoint::operator=(const normalizedPoint &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline normalizedPoint &normalizedPoint::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline normalizedPoint &normalizedPoint::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void flatPoint::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void flatPoint::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void flatPoint::set(const flatPoint &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void flatPoint::set(__flatPoint_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void flatPoint::set(__flatPoint_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni) {
		// set coordinates
		m_c[0] = c_e1ni;
		m_c[1] = c_e2ni;
		m_c[2] = c_e3ni;
		m_c[3] = c_noni;

	}

	// set to mv 
	inline void flatPoint::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 6];
			m_c[1] = arg1.m_c[gidx + 7];
			m_c[2] = arg1.m_c[gidx + 8];
			m_c[3] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}





	// assign copy
	inline flatPoint &flatPoint::operator=(const flatPoint &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline flatPoint &flatPoint::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline flatPoint &flatPoint::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void normalizedFlatPoint::set() {
		// set coordinates to 0
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void normalizedFlatPoint::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void normalizedFlatPoint::set(const normalizedFlatPoint &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void normalizedFlatPoint::set(__normalizedFlatPoint_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void normalizedFlatPoint::set(__normalizedFlatPoint_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni) {
		// set coordinates
		m_c[0] = c_e1ni;
		m_c[1] = c_e2ni;
		m_c[2] = c_e3ni;

	}

	// set to mv 
	inline void normalizedFlatPoint::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 6];
			m_c[1] = arg1.m_c[gidx + 7];
			m_c[2] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}





	// assign copy
	inline normalizedFlatPoint &normalizedFlatPoint::operator=(const normalizedFlatPoint &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline normalizedFlatPoint &normalizedFlatPoint::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline normalizedFlatPoint &normalizedFlatPoint::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void pointPair::set() {
		// set coordinates to 0
		mv_zero(m_c, 10);

	}

	// set to scalar 
	inline void pointPair::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;
		m_c[6] = (Float)0.0;
		m_c[7] = (Float)0.0;
		m_c[8] = (Float)0.0;
		m_c[9] = (Float)0.0;

	}


	// set to copy
	inline void pointPair::set(const pointPair &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 10);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];
		m_c[6] = arg1.m_c[6];
		m_c[7] = arg1.m_c[7];
		m_c[8] = arg1.m_c[8];
		m_c[9] = arg1.m_c[9];

	}

	// set to pointer to coordinates
	inline void pointPair::set(__pointPair_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 10);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];
		m_c[6] = coordinates[6];
		m_c[7] = coordinates[7];
		m_c[8] = coordinates[8];
		m_c[9] = coordinates[9];

	}

	// set to 'coordinates specified' 
	inline void pointPair::set(__pointPair_coordinates__, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni) {
		// set coordinates
		m_c[0] = c_noe1;
		m_c[1] = c_noe2;
		m_c[2] = c_noe3;
		m_c[3] = c_e1e2;
		m_c[4] = c_e2e3;
		m_c[5] = c_e3e1;
		m_c[6] = c_e1ni;
		m_c[7] = c_e2ni;
		m_c[8] = c_e3ni;
		m_c[9] = c_noni;

	}

	// set to mv 
	inline void pointPair::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
			m_c[5] = arg1.m_c[gidx + 5];
			m_c[6] = arg1.m_c[gidx + 6];
			m_c[7] = arg1.m_c[gidx + 7];
			m_c[8] = arg1.m_c[gidx + 8];
			m_c[9] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
		}


	}





	// assign copy
	inline pointPair &pointPair::operator=(const pointPair &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline pointPair &pointPair::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline pointPair &pointPair::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void line::set() {
		// set coordinates to 0
		mv_zero(m_c, 6);

	}

	// set to scalar 
	inline void line::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;

	}


	// set to copy
	inline void line::set(const line &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 6);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];

	}

	// set to pointer to coordinates
	inline void line::set(__line_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 6);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];

	}

	// set to 'coordinates specified' 
	inline void line::set(__line_coordinates__, Float c_e1e2ni, Float c_e1e3ni, Float c_e2e3ni, Float c_e1noni, Float c_e2noni, Float c_e3noni) {
		// set coordinates
		m_c[0] = c_e1e2ni;
		m_c[1] = c_e1e3ni;
		m_c[2] = c_e2e3ni;
		m_c[3] = c_e1noni;
		m_c[4] = c_e2noni;
		m_c[5] = c_e3noni;

	}

	// set to mv 
	inline void line::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 2];
			m_c[1] = arg1.m_c[gidx + 1]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 0];
			m_c[3] = arg1.m_c[gidx + 4]* (Float)-1.0;
			m_c[4] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[5] = arg1.m_c[gidx + 3]* (Float)-1.0;
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
		}


	}





	// assign copy
	inline line &line::operator=(const line &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline line &line::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline line &line::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void dualLine::set() {
		// set coordinates to 0
		mv_zero(m_c, 6);

	}

	// set to scalar 
	inline void dualLine::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;

	}


	// set to copy
	inline void dualLine::set(const dualLine &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 6);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];

	}

	// set to pointer to coordinates
	inline void dualLine::set(__dualLine_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 6);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];

	}

	// set to 'coordinates specified' 
	inline void dualLine::set(__dualLine_coordinates__, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni) {
		// set coordinates
		m_c[0] = c_e1e2;
		m_c[1] = c_e1e3;
		m_c[2] = c_e2e3;
		m_c[3] = c_e1ni;
		m_c[4] = c_e2ni;
		m_c[5] = c_e3ni;

	}

	// set to mv 
	inline void dualLine::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 3];
			m_c[1] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 4];
			m_c[3] = arg1.m_c[gidx + 6];
			m_c[4] = arg1.m_c[gidx + 7];
			m_c[5] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
		}


	}





	// assign copy
	inline dualLine &dualLine::operator=(const dualLine &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline dualLine &dualLine::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline dualLine &dualLine::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void plane::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void plane::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void plane::set(const plane &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void plane::set(__plane_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void plane::set(__plane_coordinates__, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni) {
		// set coordinates
		m_c[0] = c_e1e2e3ni;
		m_c[1] = c_e1e2noni;
		m_c[2] = c_e1e3noni;
		m_c[3] = c_e2e3noni;

	}

	// set to mv 
	inline void plane::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[3] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}





	// assign copy
	inline plane &plane::operator=(const plane &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline plane &plane::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline plane &plane::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void dualPlane::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void dualPlane::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void dualPlane::set(const dualPlane &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void dualPlane::set(__dualPlane_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void dualPlane::set(__dualPlane_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {
		// set coordinates
		m_c[0] = c_e1;
		m_c[1] = c_e2;
		m_c[2] = c_e3;
		m_c[3] = c_ni;

	}

	// set to mv 
	inline void dualPlane::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			m_c[2] = arg1.m_c[gidx + 3];
			m_c[3] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}





	// assign copy
	inline dualPlane &dualPlane::operator=(const dualPlane &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline dualPlane &dualPlane::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline dualPlane &dualPlane::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void circle::set() {
		// set coordinates to 0
		mv_zero(m_c, 10);

	}

	// set to scalar 
	inline void circle::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;
		m_c[6] = (Float)0.0;
		m_c[7] = (Float)0.0;
		m_c[8] = (Float)0.0;
		m_c[9] = (Float)0.0;

	}


	// set to copy
	inline void circle::set(const circle &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 10);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];
		m_c[6] = arg1.m_c[6];
		m_c[7] = arg1.m_c[7];
		m_c[8] = arg1.m_c[8];
		m_c[9] = arg1.m_c[9];

	}

	// set to pointer to coordinates
	inline void circle::set(__circle_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 10);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];
		m_c[6] = coordinates[6];
		m_c[7] = coordinates[7];
		m_c[8] = coordinates[8];
		m_c[9] = coordinates[9];

	}

	// set to 'coordinates specified' 
	inline void circle::set(__circle_coordinates__, Float c_e2e3ni, Float c_e3e1ni, Float c_e1e2ni, Float c_noe3ni, Float c_noe1ni, Float c_noe2ni, Float c_noe2e3, Float c_noe1e3, Float c_noe1e2, Float c_e1e2e3) {
		// set coordinates
		m_c[0] = c_e2e3ni;
		m_c[1] = c_e3e1ni;
		m_c[2] = c_e1e2ni;
		m_c[3] = c_noe3ni;
		m_c[4] = c_noe1ni;
		m_c[5] = c_noe2ni;
		m_c[6] = c_noe2e3;
		m_c[7] = c_noe1e3;
		m_c[8] = c_noe1e2;
		m_c[9] = c_e1e2e3;

	}

	// set to mv 
	inline void circle::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
			m_c[5] = arg1.m_c[gidx + 5];
			m_c[6] = arg1.m_c[gidx + 6];
			m_c[7] = arg1.m_c[gidx + 7];
			m_c[8] = arg1.m_c[gidx + 8];
			m_c[9] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
		}


	}





	// assign copy
	inline circle &circle::operator=(const circle &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline circle &circle::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline circle &circle::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void sphere::set() {
		// set coordinates to 0
		mv_zero(m_c, 5);

	}

	// set to scalar 
	inline void sphere::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;

	}


	// set to copy
	inline void sphere::set(const sphere &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 5);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];

	}

	// set to pointer to coordinates
	inline void sphere::set(__sphere_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 5);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];

	}

	// set to 'coordinates specified' 
	inline void sphere::set(__sphere_coordinates__, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no) {
		// set coordinates
		m_c[0] = c_e1e2e3ni;
		m_c[1] = c_e1e2noni;
		m_c[2] = c_e1e3noni;
		m_c[3] = c_e2e3noni;
		m_c[4] = c_e1e2e3no;

	}

	// set to mv 
	inline void sphere::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[3] = arg1.m_c[gidx + 1];
			m_c[4] = arg1.m_c[gidx + 4]* (Float)-1.0;
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
		}


	}





	// assign copy
	inline sphere &sphere::operator=(const sphere &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline sphere &sphere::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline sphere &sphere::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void dualSphere::set() {
		// set coordinates to 0
		mv_zero(m_c, 5);

	}

	// set to scalar 
	inline void dualSphere::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;

	}


	// set to copy
	inline void dualSphere::set(const dualSphere &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 5);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];

	}

	// set to pointer to coordinates
	inline void dualSphere::set(__dualSphere_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 5);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];

	}

	// set to 'coordinates specified' 
	inline void dualSphere::set(__dualSphere_coordinates__, Float c_no, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {
		// set coordinates
		m_c[0] = c_no;
		m_c[1] = c_e1;
		m_c[2] = c_e2;
		m_c[3] = c_e3;
		m_c[4] = c_ni;

	}

	// set to mv 
	inline void dualSphere::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
		}


	}





	// assign copy
	inline dualSphere &dualSphere::operator=(const dualSphere &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline dualSphere &dualSphere::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline dualSphere &dualSphere::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void normalizedSphere::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void normalizedSphere::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void normalizedSphere::set(const normalizedSphere &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void normalizedSphere::set(__normalizedSphere_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void normalizedSphere::set(__normalizedSphere_coordinates__, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no) {
		// set coordinates
		m_c[0] = c_e1e2noni;
		m_c[1] = c_e1e3noni;
		m_c[2] = c_e2e3noni;
		m_c[3] = c_e1e2e3no;

	}

	// set to mv 
	inline void normalizedSphere::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[0] = arg1.m_c[gidx + 3];
			m_c[1] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 1];
			m_c[3] = arg1.m_c[gidx + 4]* (Float)-1.0;
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}





	// assign copy
	inline normalizedSphere &normalizedSphere::operator=(const normalizedSphere &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline normalizedSphere &normalizedSphere::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline normalizedSphere &normalizedSphere::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void normalizedDualSphere::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void normalizedDualSphere::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void normalizedDualSphere::set(const normalizedDualSphere &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void normalizedDualSphere::set(__normalizedDualSphere_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void normalizedDualSphere::set(__normalizedDualSphere_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_ni) {
		// set coordinates
		m_c[0] = c_e1;
		m_c[1] = c_e2;
		m_c[2] = c_e3;
		m_c[3] = c_ni;

	}

	// set to mv 
	inline void normalizedDualSphere::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			m_c[2] = arg1.m_c[gidx + 3];
			m_c[3] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}





	// assign copy
	inline normalizedDualSphere &normalizedDualSphere::operator=(const normalizedDualSphere &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline normalizedDualSphere &normalizedDualSphere::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline normalizedDualSphere &normalizedDualSphere::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void freeVector::set() {
		// set coordinates to 0
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void freeVector::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void freeVector::set(const freeVector &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void freeVector::set(__freeVector_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void freeVector::set(__freeVector_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni) {
		// set coordinates
		m_c[0] = c_e1ni;
		m_c[1] = c_e2ni;
		m_c[2] = c_e3ni;

	}

	// set to mv 
	inline void freeVector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 6];
			m_c[1] = arg1.m_c[gidx + 7];
			m_c[2] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}





	// assign copy
	inline freeVector &freeVector::operator=(const freeVector &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline freeVector &freeVector::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline freeVector &freeVector::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void freeBivector::set() {
		// set coordinates to 0
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void freeBivector::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void freeBivector::set(const freeBivector &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void freeBivector::set(__freeBivector_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void freeBivector::set(__freeBivector_coordinates__, Float c_e1e2ni, Float c_e2e3ni, Float c_e3e1ni) {
		// set coordinates
		m_c[0] = c_e1e2ni;
		m_c[1] = c_e2e3ni;
		m_c[2] = c_e3e1ni;

	}

	// set to mv 
	inline void freeBivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 2];
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}





	// assign copy
	inline freeBivector &freeBivector::operator=(const freeBivector &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline freeBivector &freeBivector::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline freeBivector &freeBivector::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void freeTrivector::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void freeTrivector::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;

	}


	// set to copy
	inline void freeTrivector::set(const freeTrivector &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void freeTrivector::set(__freeTrivector_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void freeTrivector::set(__freeTrivector_coordinates__, Float c_e1e2e3ni) {
		// set coordinates
		m_c[0] = c_e1e2e3ni;

	}

	// set to mv 
	inline void freeTrivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}





	// assign copy
	inline freeTrivector &freeTrivector::operator=(const freeTrivector &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline freeTrivector &freeTrivector::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline freeTrivector &freeTrivector::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void tangentVector::set() {
		// set coordinates to 0
		mv_zero(m_c, 10);

	}

	// set to scalar 
	inline void tangentVector::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;
		m_c[6] = (Float)0.0;
		m_c[7] = (Float)0.0;
		m_c[8] = (Float)0.0;
		m_c[9] = (Float)0.0;

	}


	// set to copy
	inline void tangentVector::set(const tangentVector &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 10);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];
		m_c[6] = arg1.m_c[6];
		m_c[7] = arg1.m_c[7];
		m_c[8] = arg1.m_c[8];
		m_c[9] = arg1.m_c[9];

	}

	// set to pointer to coordinates
	inline void tangentVector::set(__tangentVector_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 10);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];
		m_c[6] = coordinates[6];
		m_c[7] = coordinates[7];
		m_c[8] = coordinates[8];
		m_c[9] = coordinates[9];

	}

	// set to 'coordinates specified' 
	inline void tangentVector::set(__tangentVector_coordinates__, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni) {
		// set coordinates
		m_c[0] = c_noe1;
		m_c[1] = c_noe2;
		m_c[2] = c_noe3;
		m_c[3] = c_e1e2;
		m_c[4] = c_e2e3;
		m_c[5] = c_e3e1;
		m_c[6] = c_e1ni;
		m_c[7] = c_e2ni;
		m_c[8] = c_e3ni;
		m_c[9] = c_noni;

	}

	// set to mv 
	inline void tangentVector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
			m_c[5] = arg1.m_c[gidx + 5];
			m_c[6] = arg1.m_c[gidx + 6];
			m_c[7] = arg1.m_c[gidx + 7];
			m_c[8] = arg1.m_c[gidx + 8];
			m_c[9] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
		}


	}





	// assign copy
	inline tangentVector &tangentVector::operator=(const tangentVector &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline tangentVector &tangentVector::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline tangentVector &tangentVector::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void tangentBivector::set() {
		// set coordinates to 0
		mv_zero(m_c, 10);

	}

	// set to scalar 
	inline void tangentBivector::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;
		m_c[6] = (Float)0.0;
		m_c[7] = (Float)0.0;
		m_c[8] = (Float)0.0;
		m_c[9] = (Float)0.0;

	}


	// set to copy
	inline void tangentBivector::set(const tangentBivector &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 10);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];
		m_c[6] = arg1.m_c[6];
		m_c[7] = arg1.m_c[7];
		m_c[8] = arg1.m_c[8];
		m_c[9] = arg1.m_c[9];

	}

	// set to pointer to coordinates
	inline void tangentBivector::set(__tangentBivector_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 10);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];
		m_c[6] = coordinates[6];
		m_c[7] = coordinates[7];
		m_c[8] = coordinates[8];
		m_c[9] = coordinates[9];

	}

	// set to 'coordinates specified' 
	inline void tangentBivector::set(__tangentBivector_coordinates__, Float c_e1e2e3, Float c_e2e3ni, Float c_e3e1ni, Float c_e1e2ni, Float c_noe3ni, Float c_noe1ni, Float c_noe2ni, Float c_noe2e3, Float c_noe1e3, Float c_noe1e2) {
		// set coordinates
		m_c[0] = c_e1e2e3;
		m_c[1] = c_e2e3ni;
		m_c[2] = c_e3e1ni;
		m_c[3] = c_e1e2ni;
		m_c[4] = c_noe3ni;
		m_c[5] = c_noe1ni;
		m_c[6] = c_noe2ni;
		m_c[7] = c_noe2e3;
		m_c[8] = c_noe1e3;
		m_c[9] = c_noe1e2;

	}

	// set to mv 
	inline void tangentBivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 9];
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
			m_c[3] = arg1.m_c[gidx + 2];
			m_c[4] = arg1.m_c[gidx + 3];
			m_c[5] = arg1.m_c[gidx + 4];
			m_c[6] = arg1.m_c[gidx + 5];
			m_c[7] = arg1.m_c[gidx + 6];
			m_c[8] = arg1.m_c[gidx + 7];
			m_c[9] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
		}


	}





	// assign copy
	inline tangentBivector &tangentBivector::operator=(const tangentBivector &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline tangentBivector &tangentBivector::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline tangentBivector &tangentBivector::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void vectorE2GA::set() {
		// set coordinates to 0
		mv_zero(m_c, 2);

	}

	// set to scalar 
	inline void vectorE2GA::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;

	}


	// set to copy
	inline void vectorE2GA::set(const vectorE2GA &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 2);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];

	}

	// set to pointer to coordinates
	inline void vectorE2GA::set(__vectorE2GA_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 2);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];

	}

	// set to 'coordinates specified' 
	inline void vectorE2GA::set(__vectorE2GA_coordinates__, Float c_e1, Float c_e2) {
		// set coordinates
		m_c[0] = c_e1;
		m_c[1] = c_e2;

	}

	// set to mv 
	inline void vectorE2GA::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}





	// assign copy
	inline vectorE2GA &vectorE2GA::operator=(const vectorE2GA &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline vectorE2GA &vectorE2GA::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline vectorE2GA &vectorE2GA::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void vectorE3GA::set() {
		// set coordinates to 0
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void vectorE3GA::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void vectorE3GA::set(const vectorE3GA &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void vectorE3GA::set(__vectorE3GA_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void vectorE3GA::set(__vectorE3GA_coordinates__, Float c_e1, Float c_e2, Float c_e3) {
		// set coordinates
		m_c[0] = c_e1;
		m_c[1] = c_e2;
		m_c[2] = c_e3;

	}

	// set to mv 
	inline void vectorE3GA::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			m_c[2] = arg1.m_c[gidx + 3];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}





	// assign copy
	inline vectorE3GA &vectorE3GA::operator=(const vectorE3GA &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline vectorE3GA &vectorE3GA::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline vectorE3GA &vectorE3GA::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void bivectorE3GA::set() {
		// set coordinates to 0
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void bivectorE3GA::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void bivectorE3GA::set(const bivectorE3GA &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void bivectorE3GA::set(__bivectorE3GA_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void bivectorE3GA::set(__bivectorE3GA_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1) {
		// set coordinates
		m_c[0] = c_e1e2;
		m_c[1] = c_e2e3;
		m_c[2] = c_e3e1;

	}

	// set to mv 
	inline void bivectorE3GA::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 3];
			m_c[1] = arg1.m_c[gidx + 4];
			m_c[2] = arg1.m_c[gidx + 5];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}





	// assign copy
	inline bivectorE3GA &bivectorE3GA::operator=(const bivectorE3GA &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline bivectorE3GA &bivectorE3GA::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline bivectorE3GA &bivectorE3GA::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void TRversor::set() {
		// set coordinates to 0
		mv_zero(m_c, 8);

	}

	// set to scalar 
	inline void TRversor::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = s ;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;
		m_c[6] = (Float)0.0;
		m_c[7] = (Float)0.0;

	}


	// set to copy
	inline void TRversor::set(const TRversor &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 8);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];
		m_c[6] = arg1.m_c[6];
		m_c[7] = arg1.m_c[7];

	}

	// set to pointer to coordinates
	inline void TRversor::set(__TRversor_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 8);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];
		m_c[6] = coordinates[6];
		m_c[7] = coordinates[7];

	}

	// set to 'coordinates specified' 
	inline void TRversor::set(__TRversor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_e1e2e3ni) {
		// set coordinates
		m_c[0] = c_scalar;
		m_c[1] = c_e1e2;
		m_c[2] = c_e1e3;
		m_c[3] = c_e2e3;
		m_c[4] = c_e1ni;
		m_c[5] = c_e2ni;
		m_c[6] = c_e3ni;
		m_c[7] = c_e1e2e3ni;

	}

	// set to mv 
	inline void TRversor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[3] = arg1.m_c[gidx + 4];
			m_c[4] = arg1.m_c[gidx + 6];
			m_c[5] = arg1.m_c[gidx + 7];
			m_c[6] = arg1.m_c[gidx + 8];
			gidx += 10;		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[7] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[7] = (Float)0.0;
		}


	}





	// assign copy
	inline TRversor &TRversor::operator=(const TRversor &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline TRversor &TRversor::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline TRversor &TRversor::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void TRSversor::set() {
		// set coordinates to 0
		mv_zero(m_c, 12);

	}

	// set to scalar 
	inline void TRSversor::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = s ;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;
		m_c[6] = (Float)0.0;
		m_c[7] = (Float)0.0;
		m_c[8] = (Float)0.0;
		m_c[9] = (Float)0.0;
		m_c[10] = (Float)0.0;
		m_c[11] = (Float)0.0;

	}


	// set to copy
	inline void TRSversor::set(const TRSversor &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 12);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];
		m_c[6] = arg1.m_c[6];
		m_c[7] = arg1.m_c[7];
		m_c[8] = arg1.m_c[8];
		m_c[9] = arg1.m_c[9];
		m_c[10] = arg1.m_c[10];
		m_c[11] = arg1.m_c[11];

	}

	// set to pointer to coordinates
	inline void TRSversor::set(__TRSversor_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 12);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];
		m_c[6] = coordinates[6];
		m_c[7] = coordinates[7];
		m_c[8] = coordinates[8];
		m_c[9] = coordinates[9];
		m_c[10] = coordinates[10];
		m_c[11] = coordinates[11];

	}

	// set to 'coordinates specified' 
	inline void TRSversor::set(__TRSversor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e1e3, Float c_e2e3, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3ni) {
		// set coordinates
		m_c[0] = c_scalar;
		m_c[1] = c_e1e2;
		m_c[2] = c_e1e3;
		m_c[3] = c_e2e3;
		m_c[4] = c_e1ni;
		m_c[5] = c_e2ni;
		m_c[6] = c_e3ni;
		m_c[7] = c_noni;
		m_c[8] = c_e1e2noni;
		m_c[9] = c_e1e3noni;
		m_c[10] = c_e2e3noni;
		m_c[11] = c_e1e2e3ni;

	}

	// set to mv 
	inline void TRSversor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[3] = arg1.m_c[gidx + 4];
			m_c[4] = arg1.m_c[gidx + 6];
			m_c[5] = arg1.m_c[gidx + 7];
			m_c[6] = arg1.m_c[gidx + 8];
			m_c[7] = arg1.m_c[gidx + 9];
			gidx += 10;		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[8] = arg1.m_c[gidx + 3];
			m_c[9] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[10] = arg1.m_c[gidx + 1];
			m_c[11] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
			m_c[10] = (Float)0.0;
			m_c[11] = (Float)0.0;
		}


	}





	// assign copy
	inline TRSversor &TRSversor::operator=(const TRSversor &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline TRSversor &TRSversor::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline TRSversor &TRSversor::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void evenVersor::set() {
		// set coordinates to 0
		mv_zero(m_c, 16);

	}

	// set to scalar 
	inline void evenVersor::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = s ;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;
		m_c[4] = (Float)0.0;
		m_c[5] = (Float)0.0;
		m_c[6] = (Float)0.0;
		m_c[7] = (Float)0.0;
		m_c[8] = (Float)0.0;
		m_c[9] = (Float)0.0;
		m_c[10] = (Float)0.0;
		m_c[11] = (Float)0.0;
		m_c[12] = (Float)0.0;
		m_c[13] = (Float)0.0;
		m_c[14] = (Float)0.0;
		m_c[15] = (Float)0.0;

	}


	// set to copy
	inline void evenVersor::set(const evenVersor &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 16);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];
		m_c[4] = arg1.m_c[4];
		m_c[5] = arg1.m_c[5];
		m_c[6] = arg1.m_c[6];
		m_c[7] = arg1.m_c[7];
		m_c[8] = arg1.m_c[8];
		m_c[9] = arg1.m_c[9];
		m_c[10] = arg1.m_c[10];
		m_c[11] = arg1.m_c[11];
		m_c[12] = arg1.m_c[12];
		m_c[13] = arg1.m_c[13];
		m_c[14] = arg1.m_c[14];
		m_c[15] = arg1.m_c[15];

	}

	// set to pointer to coordinates
	inline void evenVersor::set(__evenVersor_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 16);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];
		m_c[4] = coordinates[4];
		m_c[5] = coordinates[5];
		m_c[6] = coordinates[6];
		m_c[7] = coordinates[7];
		m_c[8] = coordinates[8];
		m_c[9] = coordinates[9];
		m_c[10] = coordinates[10];
		m_c[11] = coordinates[11];
		m_c[12] = coordinates[12];
		m_c[13] = coordinates[13];
		m_c[14] = coordinates[14];
		m_c[15] = coordinates[15];

	}

	// set to 'coordinates specified' 
	inline void evenVersor::set(__evenVersor_coordinates__, Float c_scalar, Float c_noe1, Float c_noe2, Float c_noe3, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1ni, Float c_e2ni, Float c_e3ni, Float c_noni, Float c_e1e2e3ni, Float c_e1e2noni, Float c_e1e3noni, Float c_e2e3noni, Float c_e1e2e3no) {
		// set coordinates
		m_c[0] = c_scalar;
		m_c[1] = c_noe1;
		m_c[2] = c_noe2;
		m_c[3] = c_noe3;
		m_c[4] = c_e1e2;
		m_c[5] = c_e2e3;
		m_c[6] = c_e3e1;
		m_c[7] = c_e1ni;
		m_c[8] = c_e2ni;
		m_c[9] = c_e3ni;
		m_c[10] = c_noni;
		m_c[11] = c_e1e2e3ni;
		m_c[12] = c_e1e2noni;
		m_c[13] = c_e1e3noni;
		m_c[14] = c_e2e3noni;
		m_c[15] = c_e1e2e3no;

	}

	// set to mv 
	inline void evenVersor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
			m_c[3] = arg1.m_c[gidx + 2];
			m_c[4] = arg1.m_c[gidx + 3];
			m_c[5] = arg1.m_c[gidx + 4];
			m_c[6] = arg1.m_c[gidx + 5];
			m_c[7] = arg1.m_c[gidx + 6];
			m_c[8] = arg1.m_c[gidx + 7];
			m_c[9] = arg1.m_c[gidx + 8];
			m_c[10] = arg1.m_c[gidx + 9];
			gidx += 10;		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
			m_c[10] = (Float)0.0;
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[11] = arg1.m_c[gidx + 0];
			m_c[12] = arg1.m_c[gidx + 3];
			m_c[13] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[14] = arg1.m_c[gidx + 1];
			m_c[15] = arg1.m_c[gidx + 4]* (Float)-1.0;
		}
		else {
			m_c[11] = (Float)0.0;
			m_c[12] = (Float)0.0;
			m_c[13] = (Float)0.0;
			m_c[14] = (Float)0.0;
			m_c[15] = (Float)0.0;
		}


	}





	// assign copy
	inline evenVersor &evenVersor::operator=(const evenVersor &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline evenVersor &evenVersor::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline evenVersor &evenVersor::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void translator::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void translator::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = s ;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void translator::set(const translator &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void translator::set(__translator_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void translator::set(__translator_coordinates__, Float c_scalar, Float c_e1ni, Float c_e2ni, Float c_e3ni) {
		// set coordinates
		m_c[0] = c_scalar;
		m_c[1] = c_e1ni;
		m_c[2] = c_e2ni;
		m_c[3] = c_e3ni;

	}

	// set to mv 
	inline void translator::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 6];
			m_c[2] = arg1.m_c[gidx + 7];
			m_c[3] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}





	// assign copy
	inline translator &translator::operator=(const translator &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline translator &translator::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline translator &translator::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void normalizedTranslator::set() {
		// set coordinates to 0
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void normalizedTranslator::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void normalizedTranslator::set(const normalizedTranslator &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void normalizedTranslator::set(__normalizedTranslator_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void normalizedTranslator::set(__normalizedTranslator_coordinates__, Float c_e1ni, Float c_e2ni, Float c_e3ni) {
		// set coordinates
		m_c[0] = c_e1ni;
		m_c[1] = c_e2ni;
		m_c[2] = c_e3ni;

	}

	// set to mv 
	inline void normalizedTranslator::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 6];
			m_c[1] = arg1.m_c[gidx + 7];
			m_c[2] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}





	// assign copy
	inline normalizedTranslator &normalizedTranslator::operator=(const normalizedTranslator &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline normalizedTranslator &normalizedTranslator::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline normalizedTranslator &normalizedTranslator::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void rotor::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void rotor::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = s ;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void rotor::set(const rotor &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void rotor::set(__rotor_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void rotor::set(__rotor_coordinates__, Float c_scalar, Float c_e1e2, Float c_e2e3, Float c_e3e1) {
		// set coordinates
		m_c[0] = c_scalar;
		m_c[1] = c_e1e2;
		m_c[2] = c_e2e3;
		m_c[3] = c_e3e1;

	}

	// set to mv 
	inline void rotor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 4];
			m_c[3] = arg1.m_c[gidx + 5];
		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}





	// assign copy
	inline rotor &rotor::operator=(const rotor &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline rotor &rotor::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline rotor &rotor::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void scalor::set() {
		// set coordinates to 0
		mv_zero(m_c, 2);

	}

	// set to scalar 
	inline void scalor::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = s ;
		m_c[1] = (Float)0.0;

	}


	// set to copy
	inline void scalor::set(const scalor &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 2);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];

	}

	// set to pointer to coordinates
	inline void scalor::set(__scalor_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 2);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];

	}

	// set to 'coordinates specified' 
	inline void scalor::set(__scalor_coordinates__, Float c_scalar, Float c_noni) {
		// set coordinates
		m_c[0] = c_scalar;
		m_c[1] = c_noni;

	}

	// set to mv 
	inline void scalor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[1] = (Float)0.0;
		}


	}





	// assign copy
	inline scalor &scalor::operator=(const scalor &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline scalor &scalor::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline scalor &scalor::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void __no_ct__::set() {
		// set coordinates to 0
	}

	// set to scalar 
	inline void __no_ct__::set(Float s) {
		// set coordinates 0, except for scalar (if any)

	}


	// set to copy
	inline void __no_ct__::set(const __no_ct__ &arg1) {
	}

	// set to pointer to coordinates
	inline void __no_ct__::set(____no_ct___coordinates__, const Float *coordinates) {
		// copy coordinates
	}

	// set to 'coordinates specified' 
	inline void __no_ct__::set(____no_ct___coordinates__) {
		// set coordinates

	}

	// set to mv 
	inline void __no_ct__::set(const mv & arg1) {



	}





	// assign copy
	inline __no_ct__ &__no_ct__::operator=(const __no_ct__ &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline __no_ct__ &__no_ct__::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline __no_ct__ &__no_ct__::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void __e1_ct__::set() {
		// set coordinates to 0
	}

	// set to scalar 
	inline void __e1_ct__::set(Float s) {
		// set coordinates 0, except for scalar (if any)

	}


	// set to copy
	inline void __e1_ct__::set(const __e1_ct__ &arg1) {
	}

	// set to pointer to coordinates
	inline void __e1_ct__::set(____e1_ct___coordinates__, const Float *coordinates) {
		// copy coordinates
	}

	// set to 'coordinates specified' 
	inline void __e1_ct__::set(____e1_ct___coordinates__) {
		// set coordinates

	}

	// set to mv 
	inline void __e1_ct__::set(const mv & arg1) {



	}





	// assign copy
	inline __e1_ct__ &__e1_ct__::operator=(const __e1_ct__ &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline __e1_ct__ &__e1_ct__::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline __e1_ct__ &__e1_ct__::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void __e2_ct__::set() {
		// set coordinates to 0
	}

	// set to scalar 
	inline void __e2_ct__::set(Float s) {
		// set coordinates 0, except for scalar (if any)

	}


	// set to copy
	inline void __e2_ct__::set(const __e2_ct__ &arg1) {
	}

	// set to pointer to coordinates
	inline void __e2_ct__::set(____e2_ct___coordinates__, const Float *coordinates) {
		// copy coordinates
	}

	// set to 'coordinates specified' 
	inline void __e2_ct__::set(____e2_ct___coordinates__) {
		// set coordinates

	}

	// set to mv 
	inline void __e2_ct__::set(const mv & arg1) {



	}





	// assign copy
	inline __e2_ct__ &__e2_ct__::operator=(const __e2_ct__ &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline __e2_ct__ &__e2_ct__::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline __e2_ct__ &__e2_ct__::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void __e3_ct__::set() {
		// set coordinates to 0
	}

	// set to scalar 
	inline void __e3_ct__::set(Float s) {
		// set coordinates 0, except for scalar (if any)

	}


	// set to copy
	inline void __e3_ct__::set(const __e3_ct__ &arg1) {
	}

	// set to pointer to coordinates
	inline void __e3_ct__::set(____e3_ct___coordinates__, const Float *coordinates) {
		// copy coordinates
	}

	// set to 'coordinates specified' 
	inline void __e3_ct__::set(____e3_ct___coordinates__) {
		// set coordinates

	}

	// set to mv 
	inline void __e3_ct__::set(const mv & arg1) {



	}





	// assign copy
	inline __e3_ct__ &__e3_ct__::operator=(const __e3_ct__ &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline __e3_ct__ &__e3_ct__::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline __e3_ct__ &__e3_ct__::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void __ni_ct__::set() {
		// set coordinates to 0
	}

	// set to scalar 
	inline void __ni_ct__::set(Float s) {
		// set coordinates 0, except for scalar (if any)

	}


	// set to copy
	inline void __ni_ct__::set(const __ni_ct__ &arg1) {
	}

	// set to pointer to coordinates
	inline void __ni_ct__::set(____ni_ct___coordinates__, const Float *coordinates) {
		// copy coordinates
	}

	// set to 'coordinates specified' 
	inline void __ni_ct__::set(____ni_ct___coordinates__) {
		// set coordinates

	}

	// set to mv 
	inline void __ni_ct__::set(const mv & arg1) {



	}





	// assign copy
	inline __ni_ct__ &__ni_ct__::operator=(const __ni_ct__ &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline __ni_ct__ &__ni_ct__::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline __ni_ct__ &__ni_ct__::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}







	// set to identity 'I'
	inline void om::set() {
		// simplify forward call to set(scalar)
		set(1.0);
	}

	// set to copy
	inline void om::set(const om &arg1) {
		mv_memcpy(m_c, arg1.m_c, 251);
	}

	// set to scalar
	inline void om::set(Float scalarVal) {
		c3ga::__G2_GENERATED__::set(*this, point(point_no_e1_e2_e3_ni, scalarVal, (Float)0, (Float)0, (Float)0, (Float)0), point(point_no_e1_e2_e3_ni, (Float)0, scalarVal, (Float)0, (Float)0, (Float)0), point(point_no_e1_e2_e3_ni, (Float)0, (Float)0, scalarVal, (Float)0, (Float)0), point(point_no_e1_e2_e3_ni, (Float)0, (Float)0, (Float)0, scalarVal, (Float)0), point(point_no_e1_e2_e3_ni, (Float)0, (Float)0, (Float)0, (Float)0, scalarVal));
	}

	// set to coordinates 
	inline void om::set(const Float *coordinates) {
		mv_memcpy(m_c, coordinates, 251);
	}

	// set from basis vectors array
	inline void om::set(const point *vectors) {
		c3ga::__G2_GENERATED__::set(*this, vectors[0], vectors[1], vectors[2], vectors[3], vectors[4]);
	}


	// set from basis vectors 
	inline void om::set(const point & image_of_no, const point & image_of_e1, const point & image_of_e2, const point & image_of_e3, const point & image_of_ni) {
		c3ga::__G2_GENERATED__::set(*this, image_of_no, image_of_e1, image_of_e2, image_of_e3, image_of_ni);
	}


	// set by coordinates, transpose
	inline void om::set(const Float *coordinates, bool transpose) {
		if (transpose) {
			m_c[0] = coordinates[0];
			m_c[5] = coordinates[1];
			m_c[10] = coordinates[2];
			m_c[15] = coordinates[3];
			m_c[20] = coordinates[4];
			m_c[1] = coordinates[5];
			m_c[6] = coordinates[6];
			m_c[11] = coordinates[7];
			m_c[16] = coordinates[8];
			m_c[21] = coordinates[9];
			m_c[2] = coordinates[10];
			m_c[7] = coordinates[11];
			m_c[12] = coordinates[12];
			m_c[17] = coordinates[13];
			m_c[22] = coordinates[14];
			m_c[3] = coordinates[15];
			m_c[8] = coordinates[16];
			m_c[13] = coordinates[17];
			m_c[18] = coordinates[18];
			m_c[23] = coordinates[19];
			m_c[4] = coordinates[20];
			m_c[9] = coordinates[21];
			m_c[14] = coordinates[22];
			m_c[19] = coordinates[23];
			m_c[24] = coordinates[24];
			m_c[25] = coordinates[25];
			m_c[35] = coordinates[26];
			m_c[45] = coordinates[27];
			m_c[55] = coordinates[28];
			m_c[65] = coordinates[29];
			m_c[75] = coordinates[30];
			m_c[85] = coordinates[31];
			m_c[95] = coordinates[32];
			m_c[105] = coordinates[33];
			m_c[115] = coordinates[34];
			m_c[26] = coordinates[35];
			m_c[36] = coordinates[36];
			m_c[46] = coordinates[37];
			m_c[56] = coordinates[38];
			m_c[66] = coordinates[39];
			m_c[76] = coordinates[40];
			m_c[86] = coordinates[41];
			m_c[96] = coordinates[42];
			m_c[106] = coordinates[43];
			m_c[116] = coordinates[44];
			m_c[27] = coordinates[45];
			m_c[37] = coordinates[46];
			m_c[47] = coordinates[47];
			m_c[57] = coordinates[48];
			m_c[67] = coordinates[49];
			m_c[77] = coordinates[50];
			m_c[87] = coordinates[51];
			m_c[97] = coordinates[52];
			m_c[107] = coordinates[53];
			m_c[117] = coordinates[54];
			m_c[28] = coordinates[55];
			m_c[38] = coordinates[56];
			m_c[48] = coordinates[57];
			m_c[58] = coordinates[58];
			m_c[68] = coordinates[59];
			m_c[78] = coordinates[60];
			m_c[88] = coordinates[61];
			m_c[98] = coordinates[62];
			m_c[108] = coordinates[63];
			m_c[118] = coordinates[64];
			m_c[29] = coordinates[65];
			m_c[39] = coordinates[66];
			m_c[49] = coordinates[67];
			m_c[59] = coordinates[68];
			m_c[69] = coordinates[69];
			m_c[79] = coordinates[70];
			m_c[89] = coordinates[71];
			m_c[99] = coordinates[72];
			m_c[109] = coordinates[73];
			m_c[119] = coordinates[74];
			m_c[30] = coordinates[75];
			m_c[40] = coordinates[76];
			m_c[50] = coordinates[77];
			m_c[60] = coordinates[78];
			m_c[70] = coordinates[79];
			m_c[80] = coordinates[80];
			m_c[90] = coordinates[81];
			m_c[100] = coordinates[82];
			m_c[110] = coordinates[83];
			m_c[120] = coordinates[84];
			m_c[31] = coordinates[85];
			m_c[41] = coordinates[86];
			m_c[51] = coordinates[87];
			m_c[61] = coordinates[88];
			m_c[71] = coordinates[89];
			m_c[81] = coordinates[90];
			m_c[91] = coordinates[91];
			m_c[101] = coordinates[92];
			m_c[111] = coordinates[93];
			m_c[121] = coordinates[94];
			m_c[32] = coordinates[95];
			m_c[42] = coordinates[96];
			m_c[52] = coordinates[97];
			m_c[62] = coordinates[98];
			m_c[72] = coordinates[99];
			m_c[82] = coordinates[100];
			m_c[92] = coordinates[101];
			m_c[102] = coordinates[102];
			m_c[112] = coordinates[103];
			m_c[122] = coordinates[104];
			m_c[33] = coordinates[105];
			m_c[43] = coordinates[106];
			m_c[53] = coordinates[107];
			m_c[63] = coordinates[108];
			m_c[73] = coordinates[109];
			m_c[83] = coordinates[110];
			m_c[93] = coordinates[111];
			m_c[103] = coordinates[112];
			m_c[113] = coordinates[113];
			m_c[123] = coordinates[114];
			m_c[34] = coordinates[115];
			m_c[44] = coordinates[116];
			m_c[54] = coordinates[117];
			m_c[64] = coordinates[118];
			m_c[74] = coordinates[119];
			m_c[84] = coordinates[120];
			m_c[94] = coordinates[121];
			m_c[104] = coordinates[122];
			m_c[114] = coordinates[123];
			m_c[124] = coordinates[124];
			m_c[125] = coordinates[125];
			m_c[135] = coordinates[126];
			m_c[145] = coordinates[127];
			m_c[155] = coordinates[128];
			m_c[165] = coordinates[129];
			m_c[175] = coordinates[130];
			m_c[185] = coordinates[131];
			m_c[195] = coordinates[132];
			m_c[205] = coordinates[133];
			m_c[215] = coordinates[134];
			m_c[126] = coordinates[135];
			m_c[136] = coordinates[136];
			m_c[146] = coordinates[137];
			m_c[156] = coordinates[138];
			m_c[166] = coordinates[139];
			m_c[176] = coordinates[140];
			m_c[186] = coordinates[141];
			m_c[196] = coordinates[142];
			m_c[206] = coordinates[143];
			m_c[216] = coordinates[144];
			m_c[127] = coordinates[145];
			m_c[137] = coordinates[146];
			m_c[147] = coordinates[147];
			m_c[157] = coordinates[148];
			m_c[167] = coordinates[149];
			m_c[177] = coordinates[150];
			m_c[187] = coordinates[151];
			m_c[197] = coordinates[152];
			m_c[207] = coordinates[153];
			m_c[217] = coordinates[154];
			m_c[128] = coordinates[155];
			m_c[138] = coordinates[156];
			m_c[148] = coordinates[157];
			m_c[158] = coordinates[158];
			m_c[168] = coordinates[159];
			m_c[178] = coordinates[160];
			m_c[188] = coordinates[161];
			m_c[198] = coordinates[162];
			m_c[208] = coordinates[163];
			m_c[218] = coordinates[164];
			m_c[129] = coordinates[165];
			m_c[139] = coordinates[166];
			m_c[149] = coordinates[167];
			m_c[159] = coordinates[168];
			m_c[169] = coordinates[169];
			m_c[179] = coordinates[170];
			m_c[189] = coordinates[171];
			m_c[199] = coordinates[172];
			m_c[209] = coordinates[173];
			m_c[219] = coordinates[174];
			m_c[130] = coordinates[175];
			m_c[140] = coordinates[176];
			m_c[150] = coordinates[177];
			m_c[160] = coordinates[178];
			m_c[170] = coordinates[179];
			m_c[180] = coordinates[180];
			m_c[190] = coordinates[181];
			m_c[200] = coordinates[182];
			m_c[210] = coordinates[183];
			m_c[220] = coordinates[184];
			m_c[131] = coordinates[185];
			m_c[141] = coordinates[186];
			m_c[151] = coordinates[187];
			m_c[161] = coordinates[188];
			m_c[171] = coordinates[189];
			m_c[181] = coordinates[190];
			m_c[191] = coordinates[191];
			m_c[201] = coordinates[192];
			m_c[211] = coordinates[193];
			m_c[221] = coordinates[194];
			m_c[132] = coordinates[195];
			m_c[142] = coordinates[196];
			m_c[152] = coordinates[197];
			m_c[162] = coordinates[198];
			m_c[172] = coordinates[199];
			m_c[182] = coordinates[200];
			m_c[192] = coordinates[201];
			m_c[202] = coordinates[202];
			m_c[212] = coordinates[203];
			m_c[222] = coordinates[204];
			m_c[133] = coordinates[205];
			m_c[143] = coordinates[206];
			m_c[153] = coordinates[207];
			m_c[163] = coordinates[208];
			m_c[173] = coordinates[209];
			m_c[183] = coordinates[210];
			m_c[193] = coordinates[211];
			m_c[203] = coordinates[212];
			m_c[213] = coordinates[213];
			m_c[223] = coordinates[214];
			m_c[134] = coordinates[215];
			m_c[144] = coordinates[216];
			m_c[154] = coordinates[217];
			m_c[164] = coordinates[218];
			m_c[174] = coordinates[219];
			m_c[184] = coordinates[220];
			m_c[194] = coordinates[221];
			m_c[204] = coordinates[222];
			m_c[214] = coordinates[223];
			m_c[224] = coordinates[224];
			m_c[225] = coordinates[225];
			m_c[230] = coordinates[226];
			m_c[235] = coordinates[227];
			m_c[240] = coordinates[228];
			m_c[245] = coordinates[229];
			m_c[226] = coordinates[230];
			m_c[231] = coordinates[231];
			m_c[236] = coordinates[232];
			m_c[241] = coordinates[233];
			m_c[246] = coordinates[234];
			m_c[227] = coordinates[235];
			m_c[232] = coordinates[236];
			m_c[237] = coordinates[237];
			m_c[242] = coordinates[238];
			m_c[247] = coordinates[239];
			m_c[228] = coordinates[240];
			m_c[233] = coordinates[241];
			m_c[238] = coordinates[242];
			m_c[243] = coordinates[243];
			m_c[248] = coordinates[244];
			m_c[229] = coordinates[245];
			m_c[234] = coordinates[246];
			m_c[239] = coordinates[247];
			m_c[244] = coordinates[248];
			m_c[249] = coordinates[249];
			m_c[250] = coordinates[250];
		}
		else set(coordinates);
	}




	// assign copy
	inline om &om::operator=(const om &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar (creates scalar * 'I' outermorphism)
	inline om &om::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}

	/// assign specialization:





	inline mv operator+=(mv& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline no_t operator+=(no_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline e1_t operator+=(e1_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline e2_t operator+=(e2_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline e3_t operator+=(e3_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline ni_t operator+=(ni_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline scalar operator+=(scalar& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline point operator+=(point& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator+=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline flatPoint operator+=(flatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline normalizedFlatPoint operator+=(normalizedFlatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline pointPair operator+=(pointPair& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline line operator+=(line& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline dualLine operator+=(dualLine& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline plane operator+=(plane& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline dualPlane operator+=(dualPlane& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline circle operator+=(circle& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline sphere operator+=(sphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline dualSphere operator+=(dualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline normalizedSphere operator+=(normalizedSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline normalizedDualSphere operator+=(normalizedDualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline freeVector operator+=(freeVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline freeBivector operator+=(freeBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline freeTrivector operator+=(freeTrivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline tangentVector operator+=(tangentVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline tangentBivector operator+=(tangentBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline vectorE2GA operator+=(vectorE2GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline vectorE3GA operator+=(vectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline bivectorE3GA operator+=(bivectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline TRversor operator+=(TRversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline TRSversor operator+=(TRSversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline evenVersor operator+=(evenVersor& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline translator operator+=(translator& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline normalizedTranslator operator+=(normalizedTranslator& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline rotor operator+=(rotor& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline scalor operator+=(scalor& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline __no_ct__ operator+=(__no_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator+=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator+=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator+=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline __ni_ct__ operator+=(__ni_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::add(arg1, arg2));
		return arg1;
	}
	inline mv operator+(const mv& arg1, const mv& arg2) {
		return ::c3ga::add(arg1, arg2);
	}
	inline mv operator-=(mv& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline no_t operator-=(no_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline e1_t operator-=(e1_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline e2_t operator-=(e2_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline e3_t operator-=(e3_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline ni_t operator-=(ni_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline scalar operator-=(scalar& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline point operator-=(point& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator-=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline flatPoint operator-=(flatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline normalizedFlatPoint operator-=(normalizedFlatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline pointPair operator-=(pointPair& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline line operator-=(line& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline dualLine operator-=(dualLine& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline plane operator-=(plane& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline dualPlane operator-=(dualPlane& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline circle operator-=(circle& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline sphere operator-=(sphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline dualSphere operator-=(dualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline normalizedSphere operator-=(normalizedSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline normalizedDualSphere operator-=(normalizedDualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline freeVector operator-=(freeVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline freeBivector operator-=(freeBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline freeTrivector operator-=(freeTrivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline tangentVector operator-=(tangentVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline tangentBivector operator-=(tangentBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline vectorE2GA operator-=(vectorE2GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline vectorE3GA operator-=(vectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline bivectorE3GA operator-=(bivectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline TRversor operator-=(TRversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline TRSversor operator-=(TRSversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline evenVersor operator-=(evenVersor& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline translator operator-=(translator& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline normalizedTranslator operator-=(normalizedTranslator& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline rotor operator-=(rotor& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline scalor operator-=(scalor& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __no_ct__ operator-=(__no_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator-=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator-=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator-=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __ni_ct__ operator-=(__ni_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline mv operator-(const mv& arg1, const mv& arg2) {
		return ::c3ga::subtract(arg1, arg2);
	}
	inline mv operator-(const mv& arg1) {
		return ::c3ga::negate(arg1);
	}
	inline mv operator%=(mv& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline no_t operator%=(no_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline e1_t operator%=(e1_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline e2_t operator%=(e2_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline e3_t operator%=(e3_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline ni_t operator%=(ni_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline scalar operator%=(scalar& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline point operator%=(point& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator%=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline flatPoint operator%=(flatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline normalizedFlatPoint operator%=(normalizedFlatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline pointPair operator%=(pointPair& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline line operator%=(line& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline dualLine operator%=(dualLine& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline plane operator%=(plane& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline dualPlane operator%=(dualPlane& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline circle operator%=(circle& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline sphere operator%=(sphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline dualSphere operator%=(dualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline normalizedSphere operator%=(normalizedSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline normalizedDualSphere operator%=(normalizedDualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline freeVector operator%=(freeVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline freeBivector operator%=(freeBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline freeTrivector operator%=(freeTrivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline tangentVector operator%=(tangentVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline tangentBivector operator%=(tangentBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline vectorE2GA operator%=(vectorE2GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline vectorE3GA operator%=(vectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline bivectorE3GA operator%=(bivectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline TRversor operator%=(TRversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline TRSversor operator%=(TRSversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline evenVersor operator%=(evenVersor& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline translator operator%=(translator& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline normalizedTranslator operator%=(normalizedTranslator& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline rotor operator%=(rotor& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline scalor operator%=(scalor& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __no_ct__ operator%=(__no_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator%=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator%=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator%=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __ni_ct__ operator%=(__ni_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::scp(arg1, arg2));
		return arg1;
	}
	inline scalar operator%(const mv& arg1, const mv& arg2) {
		return ::c3ga::scp(arg1, arg2);
	}
	inline mv operator^=(mv& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline no_t operator^=(no_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline e1_t operator^=(e1_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline e2_t operator^=(e2_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline e3_t operator^=(e3_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline ni_t operator^=(ni_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline scalar operator^=(scalar& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline point operator^=(point& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator^=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline flatPoint operator^=(flatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline normalizedFlatPoint operator^=(normalizedFlatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline pointPair operator^=(pointPair& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline line operator^=(line& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline dualLine operator^=(dualLine& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline plane operator^=(plane& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline dualPlane operator^=(dualPlane& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline circle operator^=(circle& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline sphere operator^=(sphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline dualSphere operator^=(dualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline normalizedSphere operator^=(normalizedSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline normalizedDualSphere operator^=(normalizedDualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline freeVector operator^=(freeVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline freeBivector operator^=(freeBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline freeTrivector operator^=(freeTrivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline tangentVector operator^=(tangentVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline tangentBivector operator^=(tangentBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline vectorE2GA operator^=(vectorE2GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline vectorE3GA operator^=(vectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline bivectorE3GA operator^=(bivectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline TRversor operator^=(TRversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline TRSversor operator^=(TRSversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline evenVersor operator^=(evenVersor& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline translator operator^=(translator& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline normalizedTranslator operator^=(normalizedTranslator& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline rotor operator^=(rotor& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline scalor operator^=(scalor& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline __no_ct__ operator^=(__no_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator^=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator^=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator^=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline __ni_ct__ operator^=(__ni_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::op(arg1, arg2));
		return arg1;
	}
	inline mv operator^(const mv& arg1, const mv& arg2) {
		return ::c3ga::op(arg1, arg2);
	}
	inline mv operator*=(mv& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline no_t operator*=(no_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline e1_t operator*=(e1_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline e2_t operator*=(e2_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline e3_t operator*=(e3_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline ni_t operator*=(ni_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline scalar operator*=(scalar& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline point operator*=(point& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator*=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline flatPoint operator*=(flatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline normalizedFlatPoint operator*=(normalizedFlatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline pointPair operator*=(pointPair& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline line operator*=(line& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline dualLine operator*=(dualLine& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline plane operator*=(plane& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline dualPlane operator*=(dualPlane& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline circle operator*=(circle& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline sphere operator*=(sphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline dualSphere operator*=(dualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline normalizedSphere operator*=(normalizedSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline normalizedDualSphere operator*=(normalizedDualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline freeVector operator*=(freeVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline freeBivector operator*=(freeBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline freeTrivector operator*=(freeTrivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline tangentVector operator*=(tangentVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline tangentBivector operator*=(tangentBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline vectorE2GA operator*=(vectorE2GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline vectorE3GA operator*=(vectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline bivectorE3GA operator*=(bivectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline TRversor operator*=(TRversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline TRSversor operator*=(TRSversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline evenVersor operator*=(evenVersor& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline translator operator*=(translator& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline normalizedTranslator operator*=(normalizedTranslator& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline rotor operator*=(rotor& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline scalor operator*=(scalor& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __no_ct__ operator*=(__no_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator*=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator*=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator*=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __ni_ct__ operator*=(__ni_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::gp(arg1, arg2));
		return arg1;
	}
	inline mv operator*(const mv& arg1, const mv& arg2) {
		return ::c3ga::gp(arg1, arg2);
	}
	inline mv operator<<=(mv& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline no_t operator<<=(no_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline e1_t operator<<=(e1_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline e2_t operator<<=(e2_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline e3_t operator<<=(e3_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline ni_t operator<<=(ni_t& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline scalar operator<<=(scalar& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline point operator<<=(point& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator<<=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline flatPoint operator<<=(flatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline normalizedFlatPoint operator<<=(normalizedFlatPoint& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline pointPair operator<<=(pointPair& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline line operator<<=(line& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline dualLine operator<<=(dualLine& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline plane operator<<=(plane& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline dualPlane operator<<=(dualPlane& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline circle operator<<=(circle& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline sphere operator<<=(sphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline dualSphere operator<<=(dualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline normalizedSphere operator<<=(normalizedSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline normalizedDualSphere operator<<=(normalizedDualSphere& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline freeVector operator<<=(freeVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline freeBivector operator<<=(freeBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline freeTrivector operator<<=(freeTrivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline tangentVector operator<<=(tangentVector& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline tangentBivector operator<<=(tangentBivector& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline vectorE2GA operator<<=(vectorE2GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline vectorE3GA operator<<=(vectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline bivectorE3GA operator<<=(bivectorE3GA& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline TRversor operator<<=(TRversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline TRSversor operator<<=(TRSversor& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline evenVersor operator<<=(evenVersor& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline translator operator<<=(translator& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline normalizedTranslator operator<<=(normalizedTranslator& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline rotor operator<<=(rotor& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline scalor operator<<=(scalor& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __no_ct__ operator<<=(__no_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator<<=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator<<=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator<<=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __ni_ct__ operator<<=(__ni_ct__& arg1, const mv& arg2) {
		arg1.set(::c3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline mv operator<<(const mv& arg1, const mv& arg2) {
		return ::c3ga::lcont(arg1, arg2);
	}
	inline mv operator*(const mv& arg1) {
		return ::c3ga::dual(arg1);
	}
	inline mv operator!(const mv& arg1) {
		return ::c3ga::inverse(arg1);
	}
	inline mv operator~(const mv& arg1) {
		return ::c3ga::reverse(arg1);
	}


	// G2 functions:
	inline mv lcont(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_1__[32] ;
		mv_zero(__tmp_coord_array_1__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[1] += (__y_xpd__[1][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[2] += (__y_xpd__[1][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[3] += (__y_xpd__[1][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[4] += (__y_xpd__[1][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[5] += (__y_xpd__[1][4] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[0] += ((__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[6] += (__y_xpd__[2][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[7] += (__y_xpd__[2][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[8] += (__y_xpd__[2][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[9] += (__y_xpd__[2][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[10] += (__y_xpd__[2][4] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[11] += (__y_xpd__[2][5] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[12] += (__y_xpd__[2][6] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[13] += (__y_xpd__[2][7] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[14] += (__y_xpd__[2][8] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[15] += (__y_xpd__[2][9] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[1] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][2]));
				__tmp_coord_array_1__[2] += ((__x_xpd__[1][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][6]));
				__tmp_coord_array_1__[3] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (__x_xpd__[1][0] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][1]) + (__x_xpd__[1][1] * __y_xpd__[2][3]));
				__tmp_coord_array_1__[4] += ((__x_xpd__[1][0] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][2]) + (__x_xpd__[1][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][5]));
				__tmp_coord_array_1__[5] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][9]) + (__x_xpd__[1][1] * __y_xpd__[2][6]) + (__x_xpd__[1][2] * __y_xpd__[2][7]) + (__x_xpd__[1][3] * __y_xpd__[2][8]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[0] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (__x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[16] += (__y_xpd__[3][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[17] += (__y_xpd__[3][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[18] += (__y_xpd__[3][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[19] += (__y_xpd__[3][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[20] += (__y_xpd__[3][4] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[21] += (__y_xpd__[3][5] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[22] += (__y_xpd__[3][6] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[23] += (__y_xpd__[3][7] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[24] += (__y_xpd__[3][8] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[25] += (__y_xpd__[3][9] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[6] += ((__x_xpd__[1][3] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][4]) + (__x_xpd__[1][2] * __y_xpd__[3][8]));
				__tmp_coord_array_1__[7] += ((__x_xpd__[1][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][8]));
				__tmp_coord_array_1__[8] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][6]));
				__tmp_coord_array_1__[9] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (__x_xpd__[1][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][2]));
				__tmp_coord_array_1__[10] += ((__x_xpd__[1][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]));
				__tmp_coord_array_1__[11] += ((__x_xpd__[1][4] * __y_xpd__[3][7]) + (__x_xpd__[1][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][1]));
				__tmp_coord_array_1__[12] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][4]) + (__x_xpd__[1][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]));
				__tmp_coord_array_1__[13] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][5]));
				__tmp_coord_array_1__[14] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][3]) + (__x_xpd__[1][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]));
				__tmp_coord_array_1__[15] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][5]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[1] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][5]) + (__x_xpd__[2][5] * __y_xpd__[3][7]));
				__tmp_coord_array_1__[2] += ((__x_xpd__[2][8] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][9]) + (__x_xpd__[2][7] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][4]) + (__x_xpd__[2][2] * __y_xpd__[3][1]));
				__tmp_coord_array_1__[3] += ((__x_xpd__[2][8] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]) + (__x_xpd__[2][0] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][5]));
				__tmp_coord_array_1__[4] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[3][6]) + (__x_xpd__[2][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][9]));
				__tmp_coord_array_1__[5] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][2]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[0] += ((__x_xpd__[3][5] * __y_xpd__[3][5]) + (__x_xpd__[3][8] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (__x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][1]) + (__x_xpd__[3][0] * __y_xpd__[3][6]) + (__x_xpd__[3][2] * __y_xpd__[3][8]) + (__x_xpd__[3][6] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (__x_xpd__[3][4] * __y_xpd__[3][4]));

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[26] += (__y_xpd__[4][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[27] += (__y_xpd__[4][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[28] += (__y_xpd__[4][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[29] += (__y_xpd__[4][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[30] += (__y_xpd__[4][4] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[16] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][1]) + (__x_xpd__[1][1] * __y_xpd__[4][0]));
				__tmp_coord_array_1__[17] += ((__x_xpd__[1][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][2]));
				__tmp_coord_array_1__[18] += ((__x_xpd__[1][3] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[19] += ((__x_xpd__[1][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[20] += ((__x_xpd__[1][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][2]));
				__tmp_coord_array_1__[21] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[4][3]) + (__x_xpd__[1][3] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[22] += ((__x_xpd__[1][0] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[23] += ((__x_xpd__[1][2] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[4][2]));
				__tmp_coord_array_1__[24] += ((__x_xpd__[1][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[25] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][4]) + (__x_xpd__[1][0] * __y_xpd__[4][0]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[6] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[4][4]) + (__x_xpd__[2][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[7] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][1]) + (__x_xpd__[2][0] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[8] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][2]) + (__x_xpd__[2][1] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[9] += ((__x_xpd__[2][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[10] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[11] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[12] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][2]) + (__x_xpd__[2][7] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[13] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]) + (__x_xpd__[2][8] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[14] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]) + (__x_xpd__[2][6] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[15] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][1]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[1] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[4][3]) + (__x_xpd__[3][7] * __y_xpd__[4][2]) + (__x_xpd__[3][9] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[2] += ((__x_xpd__[3][0] * __y_xpd__[4][4]) + (__x_xpd__[3][5] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][0]));
				__tmp_coord_array_1__[3] += ((__x_xpd__[3][3] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][3]) + (__x_xpd__[3][1] * __y_xpd__[4][4]) + (__x_xpd__[3][7] * __y_xpd__[4][0]));
				__tmp_coord_array_1__[4] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][0]) + (__x_xpd__[3][2] * __y_xpd__[4][4]) + (__x_xpd__[3][4] * __y_xpd__[4][2]));
				__tmp_coord_array_1__[5] += ((__x_xpd__[3][1] * __y_xpd__[4][2]) + (__x_xpd__[3][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[4][0]) + (__x_xpd__[3][0] * __y_xpd__[4][1]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_1__[0] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][3]) + (__x_xpd__[4][0] * __y_xpd__[4][4]) + (__x_xpd__[4][4] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][2]));

			}

		}
		if (((y.m_gu & 32) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[31] += (__y_xpd__[5][0] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[26] += (-1.0f * __x_xpd__[1][4] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[27] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[28] += (-1.0f * __x_xpd__[1][2] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[29] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[30] += (-1.0f * __x_xpd__[1][0] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[16] += (-1.0f * __x_xpd__[2][6] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[17] += (-1.0f * __x_xpd__[2][7] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[18] += (-1.0f * __x_xpd__[2][8] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[19] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[20] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[21] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[22] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[23] += (__x_xpd__[2][1] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[24] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[25] += (-1.0f * __x_xpd__[2][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[6] += (__x_xpd__[3][6] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[7] += (-1.0f * __x_xpd__[3][7] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[8] += (__x_xpd__[3][8] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[9] += (__x_xpd__[3][3] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[10] += (__x_xpd__[3][4] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[11] += (__x_xpd__[3][5] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[12] += (__x_xpd__[3][0] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[13] += (__x_xpd__[3][1] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[14] += (__x_xpd__[3][2] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[15] += (__x_xpd__[3][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_1__[1] += (__x_xpd__[4][4] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[2] += (__x_xpd__[4][1] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[3] += (__x_xpd__[4][2] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[4] += (__x_xpd__[4][3] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[5] += (__x_xpd__[4][0] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_1__[0] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_1__);
		return __temp_var_1__;
	}
	inline scalar scp(const mv& x, const mv& y) {
		scalar __temp_var_1__;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 2) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[1][3] * __y_xpd__[1][3]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][4]));

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 4) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]) + (__x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]));

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 8) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[3][0] * __y_xpd__[3][6]) + (__x_xpd__[3][8] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][1]) + (__x_xpd__[3][4] * __y_xpd__[3][4]) + (__x_xpd__[3][5] * __y_xpd__[3][5]) + (__x_xpd__[3][6] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (__x_xpd__[3][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (__x_xpd__[3][3] * __y_xpd__[3][3]));

			}

		}
		if (((x.m_gu & 16) != 0)) {
			if (((y.m_gu & 16) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[4][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[4][1]) + (__x_xpd__[4][4] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][3]));

			}

		}
		if (((x.m_gu & 32) != 0)) {
			if (((y.m_gu & 32) != 0)) {
				__temp_var_1__.m_c[0] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		return __temp_var_1__;
	}
	inline mv gp(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_2__[32] ;
		mv_zero(__tmp_coord_array_2__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_2__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);
				__tmp_coord_array_2__[4] += (__x_xpd__[0][0] * __y_xpd__[1][3]);
				__tmp_coord_array_2__[5] += (__x_xpd__[0][0] * __y_xpd__[1][4]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[6] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_2__[7] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_2__[8] += (__x_xpd__[0][0] * __y_xpd__[2][2]);
				__tmp_coord_array_2__[9] += (__x_xpd__[0][0] * __y_xpd__[2][3]);
				__tmp_coord_array_2__[10] += (__x_xpd__[0][0] * __y_xpd__[2][4]);
				__tmp_coord_array_2__[11] += (__x_xpd__[0][0] * __y_xpd__[2][5]);
				__tmp_coord_array_2__[12] += (__x_xpd__[0][0] * __y_xpd__[2][6]);
				__tmp_coord_array_2__[13] += (__x_xpd__[0][0] * __y_xpd__[2][7]);
				__tmp_coord_array_2__[14] += (__x_xpd__[0][0] * __y_xpd__[2][8]);
				__tmp_coord_array_2__[15] += (__x_xpd__[0][0] * __y_xpd__[2][9]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[16] += (__x_xpd__[0][0] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[17] += (__x_xpd__[0][0] * __y_xpd__[3][1]);
				__tmp_coord_array_2__[18] += (__x_xpd__[0][0] * __y_xpd__[3][2]);
				__tmp_coord_array_2__[19] += (__x_xpd__[0][0] * __y_xpd__[3][3]);
				__tmp_coord_array_2__[20] += (__x_xpd__[0][0] * __y_xpd__[3][4]);
				__tmp_coord_array_2__[21] += (__x_xpd__[0][0] * __y_xpd__[3][5]);
				__tmp_coord_array_2__[22] += (__x_xpd__[0][0] * __y_xpd__[3][6]);
				__tmp_coord_array_2__[23] += (__x_xpd__[0][0] * __y_xpd__[3][7]);
				__tmp_coord_array_2__[24] += (__x_xpd__[0][0] * __y_xpd__[3][8]);
				__tmp_coord_array_2__[25] += (__x_xpd__[0][0] * __y_xpd__[3][9]);

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[26] += (__x_xpd__[0][0] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[27] += (__x_xpd__[0][0] * __y_xpd__[4][1]);
				__tmp_coord_array_2__[28] += (__x_xpd__[0][0] * __y_xpd__[4][2]);
				__tmp_coord_array_2__[29] += (__x_xpd__[0][0] * __y_xpd__[4][3]);
				__tmp_coord_array_2__[30] += (__x_xpd__[0][0] * __y_xpd__[4][4]);

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[31] += (__x_xpd__[0][0] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[4] += (__x_xpd__[1][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[5] += (__x_xpd__[1][4] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[0] += ((__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][3] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][1] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[6] += ((__x_xpd__[1][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[8] += ((__x_xpd__[1][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[1][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[11] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[1][3]) + (__x_xpd__[1][3] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][2]) + (__x_xpd__[1][2] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[14] += ((__x_xpd__[1][3] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][4]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += ((__x_xpd__[1][0] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][0]) + (__x_xpd__[1][3] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][7]) + (__x_xpd__[1][1] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][8]) + (__x_xpd__[1][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[5] += ((__x_xpd__[1][2] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][9]) + (__x_xpd__[1][1] * __y_xpd__[2][6]) + (__x_xpd__[1][3] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][7]) + (__x_xpd__[1][2] * __y_xpd__[2][8]) + (__x_xpd__[1][4] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[17] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][8]) + (__x_xpd__[1][3] * __y_xpd__[2][6]) + (__x_xpd__[1][4] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[18] += ((__x_xpd__[1][4] * __y_xpd__[2][3]) + (__x_xpd__[1][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[1][4] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[20] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][9]) + (__x_xpd__[1][4] * __y_xpd__[2][0]) + (__x_xpd__[1][0] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[1][0] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[22] += ((__x_xpd__[1][3] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][3]) + (__x_xpd__[1][2] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[25] += ((__x_xpd__[1][3] * __y_xpd__[2][3]) + (__x_xpd__[1][1] * __y_xpd__[2][4]) + (__x_xpd__[1][2] * __y_xpd__[2][5]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[6] += ((__x_xpd__[1][3] * __y_xpd__[3][7]) + (__x_xpd__[1][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[1][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][6]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (__x_xpd__[1][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]));
				__tmp_coord_array_2__[11] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][1]) + (__x_xpd__[1][2] * __y_xpd__[3][9]) + (__x_xpd__[1][4] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]) + (__x_xpd__[1][3] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][5]) + (__x_xpd__[1][1] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][3]) + (__x_xpd__[1][2] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[26] += ((__x_xpd__[1][2] * __y_xpd__[3][1]) + (__x_xpd__[1][3] * __y_xpd__[3][2]) + (__x_xpd__[1][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[27] += ((__x_xpd__[1][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]) + (__x_xpd__[1][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[28] += ((__x_xpd__[1][1] * __y_xpd__[3][3]) + (__x_xpd__[1][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][4]) + (__x_xpd__[1][4] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[29] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][5]) + (__x_xpd__[1][2] * __y_xpd__[3][4]) + (__x_xpd__[1][0] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[30] += ((__x_xpd__[1][2] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][8]) + (__x_xpd__[1][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][6]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[16] += ((__x_xpd__[1][1] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[17] += ((__x_xpd__[1][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][3]) + (__x_xpd__[1][3] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[1][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[20] += ((__x_xpd__[1][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[1][3] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[22] += ((__x_xpd__[1][0] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[4][2]) + (__x_xpd__[1][2] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[4][4]) + (__x_xpd__[1][0] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][4]) + (__x_xpd__[1][0] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[31] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[4][2]) + (__x_xpd__[1][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][3]) + (__x_xpd__[1][4] * __y_xpd__[4][4]));

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[26] += (-1.0f * __x_xpd__[1][4] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[27] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[28] += (-1.0f * __x_xpd__[1][2] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[29] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[30] += (-1.0f * __x_xpd__[1][0] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[6] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[7] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[8] += (__x_xpd__[2][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[9] += (__x_xpd__[2][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[10] += (__x_xpd__[2][4] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[11] += (__x_xpd__[2][5] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[12] += (__x_xpd__[2][6] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[13] += (__x_xpd__[2][7] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[14] += (__x_xpd__[2][8] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[15] += (__x_xpd__[2][9] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[1][0]) + (__x_xpd__[2][1] * __y_xpd__[1][2]) + (__x_xpd__[2][0] * __y_xpd__[1][1]) + (__x_xpd__[2][2] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[1][3]) + (__x_xpd__[2][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[1][0]) + (__x_xpd__[2][3] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[1][0]) + (__x_xpd__[2][1] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[1][1]) + (__x_xpd__[2][4] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[4] += ((__x_xpd__[2][5] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][0]) + (__x_xpd__[2][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[5] += ((__x_xpd__[2][9] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[1][3]) + (__x_xpd__[2][8] * __y_xpd__[1][2]) + (__x_xpd__[2][4] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[17] += ((__x_xpd__[2][5] * __y_xpd__[1][4]) + (__x_xpd__[2][6] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][4]) + (__x_xpd__[2][7] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[2][8] * __y_xpd__[1][0]) + (__x_xpd__[2][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[20] += ((__x_xpd__[2][6] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][1]) + (__x_xpd__[2][0] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[2][1] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][2]) + (__x_xpd__[2][7] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[22] += ((__x_xpd__[2][4] * __y_xpd__[1][0]) + (__x_xpd__[2][1] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][1]) + (__x_xpd__[2][0] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[24] += ((__x_xpd__[2][0] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[25] += ((__x_xpd__[2][3] * __y_xpd__[1][3]) + (__x_xpd__[2][4] * __y_xpd__[1][1]) + (__x_xpd__[2][5] * __y_xpd__[1][2]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[0] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][6]) + (__x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[2][0]) + (__x_xpd__[2][3] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][3]) + (__x_xpd__[2][0] * __y_xpd__[2][9]) + (__x_xpd__[2][2] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[2][1]) + (__x_xpd__[2][1] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][0]) + (__x_xpd__[2][4] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][4]) + (__x_xpd__[2][0] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[8] += ((__x_xpd__[2][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][1]) + (__x_xpd__[2][1] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][2]) + (__x_xpd__[2][5] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[2][5]) + (__x_xpd__[2][1] * __y_xpd__[2][6]) + (__x_xpd__[2][5] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][1]) + (__x_xpd__[2][7] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[2][8]) + (__x_xpd__[2][2] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][2]) + (__x_xpd__[2][3] * __y_xpd__[2][5]) + (__x_xpd__[2][8] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[2][4] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][0]) + (__x_xpd__[2][0] * __y_xpd__[2][8]) + (__x_xpd__[2][6] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[2][3]) + (__x_xpd__[2][3] * __y_xpd__[2][7]) + (__x_xpd__[2][8] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][9]) + (__x_xpd__[2][9] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[13] += ((__x_xpd__[2][9] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][9]) + (__x_xpd__[2][4] * __y_xpd__[2][8]) + (__x_xpd__[2][6] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[14] += ((__x_xpd__[2][5] * __y_xpd__[2][6]) + (__x_xpd__[2][9] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][5]) + (__x_xpd__[2][7] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[15] += ((__x_xpd__[2][0] * __y_xpd__[2][6]) + (__x_xpd__[2][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]) + (__x_xpd__[2][1] * __y_xpd__[2][7]));
				__tmp_coord_array_2__[26] += ((__x_xpd__[2][5] * __y_xpd__[2][7]) + (__x_xpd__[2][4] * __y_xpd__[2][6]) + (__x_xpd__[2][8] * __y_xpd__[2][3]) + (__x_xpd__[2][7] * __y_xpd__[2][5]) + (__x_xpd__[2][3] * __y_xpd__[2][8]) + (__x_xpd__[2][6] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[27] += ((__x_xpd__[2][4] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][7]) + (__x_xpd__[2][9] * __y_xpd__[2][4]) + (__x_xpd__[2][1] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][2]) + (__x_xpd__[2][8] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[28] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][8]) + (__x_xpd__[2][9] * __y_xpd__[2][5]) + (__x_xpd__[2][2] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][0]) + (__x_xpd__[2][6] * __y_xpd__[2][2]) + (__x_xpd__[2][5] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[29] += ((__x_xpd__[2][0] * __y_xpd__[2][7]) + (__x_xpd__[2][3] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][1]) + (__x_xpd__[2][9] * __y_xpd__[2][3]) + (__x_xpd__[2][7] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[30] += ((__x_xpd__[2][4] * __y_xpd__[2][0]) + (__x_xpd__[2][5] * __y_xpd__[2][1]) + (__x_xpd__[2][2] * __y_xpd__[2][3]) + (__x_xpd__[2][3] * __y_xpd__[2][2]) + (__x_xpd__[2][1] * __y_xpd__[2][5]) + (__x_xpd__[2][0] * __y_xpd__[2][4]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][6]) + (__x_xpd__[2][5] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (__x_xpd__[2][2] * __y_xpd__[3][1]) + (__x_xpd__[2][7] * __y_xpd__[3][8]) + (__x_xpd__[2][8] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][9]) + (__x_xpd__[2][0] * __y_xpd__[3][2]) + (__x_xpd__[2][8] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][7]) + (__x_xpd__[2][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[16] += ((__x_xpd__[2][8] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][3]) + (__x_xpd__[2][3] * __y_xpd__[3][1]) + (__x_xpd__[2][9] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[17] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][9]) + (__x_xpd__[2][4] * __y_xpd__[3][2]) + (__x_xpd__[2][6] * __y_xpd__[3][3]) + (__x_xpd__[2][9] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[18] += ((__x_xpd__[2][5] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][1]) + (__x_xpd__[2][7] * __y_xpd__[3][4]) + (__x_xpd__[2][9] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[2][5] * __y_xpd__[3][4]) + (__x_xpd__[2][7] * __y_xpd__[3][6]) + (__x_xpd__[2][1] * __y_xpd__[3][0]) + (__x_xpd__[2][6] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[20] += ((__x_xpd__[2][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (__x_xpd__[2][2] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[2][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][4]) + (__x_xpd__[2][0] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][6]) + (__x_xpd__[2][6] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][7]) + (__x_xpd__[2][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][6]) + (__x_xpd__[2][0] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][3]) + (__x_xpd__[2][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][9]) + (__x_xpd__[2][3] * __y_xpd__[3][6]));
				__tmp_coord_array_2__[24] += ((__x_xpd__[2][5] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][5]) + (__x_xpd__[2][2] * __y_xpd__[3][9]) + (__x_xpd__[2][4] * __y_xpd__[3][7]) + (__x_xpd__[2][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[25] += ((__x_xpd__[2][0] * __y_xpd__[3][0]) + (__x_xpd__[2][7] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][8]) + (__x_xpd__[2][1] * __y_xpd__[3][1]) + (__x_xpd__[2][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][6]));
				__tmp_coord_array_2__[31] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[3][9]) + (__x_xpd__[2][6] * __y_xpd__[3][6]) + (__x_xpd__[2][0] * __y_xpd__[3][0]) + (__x_xpd__[2][5] * __y_xpd__[3][5]) + (__x_xpd__[2][3] * __y_xpd__[3][3]) + (__x_xpd__[2][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][7]) + (__x_xpd__[2][2] * __y_xpd__[3][2]) + (__x_xpd__[2][4] * __y_xpd__[3][4]) + (__x_xpd__[2][8] * __y_xpd__[3][8]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][3]) + (__x_xpd__[2][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[4][1]) + (__x_xpd__[2][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[8] += ((__x_xpd__[2][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[11] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]) + (__x_xpd__[2][7] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[13] += ((__x_xpd__[2][8] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]) + (__x_xpd__[2][6] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[26] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][1]) + (__x_xpd__[2][9] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[27] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][4]) + (__x_xpd__[2][3] * __y_xpd__[4][2]) + (__x_xpd__[2][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[28] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][1]) + (__x_xpd__[2][1] * __y_xpd__[4][0]) + (__x_xpd__[2][4] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[29] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][4]) + (__x_xpd__[2][5] * __y_xpd__[4][1]) + (__x_xpd__[2][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[30] += ((__x_xpd__[2][1] * __y_xpd__[4][2]) + (__x_xpd__[2][0] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][4]) + (__x_xpd__[2][2] * __y_xpd__[4][3]));

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[16] += (-1.0f * __x_xpd__[2][6] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[17] += (-1.0f * __x_xpd__[2][7] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[18] += (-1.0f * __x_xpd__[2][8] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[19] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[20] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[21] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[22] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[23] += (__x_xpd__[2][1] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[24] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[25] += (-1.0f * __x_xpd__[2][9] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[16] += (__x_xpd__[3][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[17] += (__x_xpd__[3][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[18] += (__x_xpd__[3][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[19] += (__x_xpd__[3][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[20] += (__x_xpd__[3][4] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[21] += (__x_xpd__[3][5] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[22] += (__x_xpd__[3][6] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[23] += (__x_xpd__[3][7] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[24] += (__x_xpd__[3][8] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[25] += (__x_xpd__[3][9] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[6] += ((__x_xpd__[3][8] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[1][0]) + (__x_xpd__[3][7] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[1][1]) + (__x_xpd__[3][6] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[1][4]) + (__x_xpd__[3][9] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[1][4]) + (__x_xpd__[3][9] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[3][7] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][0]) + (__x_xpd__[3][9] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[1][2]) + (__x_xpd__[3][1] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[13] += ((__x_xpd__[3][2] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[1][1]) + (__x_xpd__[3][0] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[26] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][1]) + (__x_xpd__[3][9] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[27] += ((__x_xpd__[3][6] * __y_xpd__[1][4]) + (__x_xpd__[3][3] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[28] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[1][4]) + (__x_xpd__[3][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[29] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]) + (__x_xpd__[3][5] * __y_xpd__[1][1]) + (__x_xpd__[3][8] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[30] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[1][0]) + (__x_xpd__[3][8] * __y_xpd__[1][3]) + (__x_xpd__[3][6] * __y_xpd__[1][1]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[2][1]) + (__x_xpd__[3][7] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[2] += ((__x_xpd__[3][1] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][1]) + (__x_xpd__[3][8] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][9]) + (__x_xpd__[3][7] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][6]) + (__x_xpd__[3][2] * __y_xpd__[2][0]) + (__x_xpd__[3][6] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][6]) + (__x_xpd__[3][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][9]) + (__x_xpd__[3][2] * __y_xpd__[2][5]) + (__x_xpd__[3][3] * __y_xpd__[2][7]) + (__x_xpd__[3][9] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[17] += ((__x_xpd__[3][9] * __y_xpd__[2][7]) + (__x_xpd__[3][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][4]) + (__x_xpd__[3][4] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][9]) + (__x_xpd__[3][1] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][5]) + (__x_xpd__[3][5] * __y_xpd__[2][6]) + (__x_xpd__[3][9] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[3][5] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][7]) + (__x_xpd__[3][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[20] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[2][2]) + (__x_xpd__[3][3] * __y_xpd__[2][5]) + (__x_xpd__[3][8] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][3]) + (__x_xpd__[3][2] * __y_xpd__[2][1]) + (__x_xpd__[3][7] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[21] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][4]) + (__x_xpd__[3][0] * __y_xpd__[2][2]) + (__x_xpd__[3][4] * __y_xpd__[2][3]) + (__x_xpd__[3][6] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][0]) + (__x_xpd__[3][7] * __y_xpd__[2][3]) + (__x_xpd__[3][3] * __y_xpd__[2][1]) + (__x_xpd__[3][8] * __y_xpd__[2][5]) + (__x_xpd__[3][6] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[2][2]) + (__x_xpd__[3][7] * __y_xpd__[2][9]) + (__x_xpd__[3][9] * __y_xpd__[2][1]) + (__x_xpd__[3][8] * __y_xpd__[2][4]) + (__x_xpd__[3][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][2]) + (__x_xpd__[3][8] * __y_xpd__[2][9]) + (__x_xpd__[3][5] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][1]) + (__x_xpd__[3][6] * __y_xpd__[2][6]) + (__x_xpd__[3][8] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][7]));
				__tmp_coord_array_2__[31] += ((__x_xpd__[3][0] * __y_xpd__[2][0]) + (__x_xpd__[3][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][9]) + (__x_xpd__[3][2] * __y_xpd__[2][2]) + (__x_xpd__[3][6] * __y_xpd__[2][6]) + (__x_xpd__[3][8] * __y_xpd__[2][8]) + (__x_xpd__[3][1] * __y_xpd__[2][1]) + (__x_xpd__[3][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][7]) + (__x_xpd__[3][3] * __y_xpd__[2][3]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[0] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (__x_xpd__[3][3] * __y_xpd__[3][3]) + (__x_xpd__[3][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (__x_xpd__[3][0] * __y_xpd__[3][6]) + (__x_xpd__[3][4] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][1]) + (__x_xpd__[3][5] * __y_xpd__[3][5]) + (__x_xpd__[3][8] * __y_xpd__[3][2]) + (__x_xpd__[3][6] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[3][5]) + (__x_xpd__[3][3] * __y_xpd__[3][7]) + (__x_xpd__[3][5] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][3]) + (__x_xpd__[3][9] * __y_xpd__[3][6]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[3][7] * __y_xpd__[3][9]) + (__x_xpd__[3][8] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][8]) + (__x_xpd__[3][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[8] += ((__x_xpd__[3][7] * __y_xpd__[3][4]) + (__x_xpd__[3][9] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][7]) + (__x_xpd__[3][6] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[9] += ((__x_xpd__[3][7] * __y_xpd__[3][0]) + (__x_xpd__[3][6] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][7]) + (__x_xpd__[3][4] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][2]) + (__x_xpd__[3][5] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][1]) + (__x_xpd__[3][2] * __y_xpd__[3][7]) + (__x_xpd__[3][1] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[3][8] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][2]) + (__x_xpd__[3][3] * __y_xpd__[3][4]) + (__x_xpd__[3][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[3][5]) + (__x_xpd__[3][5] * __y_xpd__[3][2]) + (__x_xpd__[3][1] * __y_xpd__[3][3]) + (__x_xpd__[3][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[3][3]) + (__x_xpd__[3][3] * __y_xpd__[3][0]) + (__x_xpd__[3][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][1]) + (__x_xpd__[3][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][4]) + (__x_xpd__[3][0] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][0]) + (__x_xpd__[3][4] * __y_xpd__[3][1]) + (__x_xpd__[3][2] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][2]) + (__x_xpd__[3][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (__x_xpd__[3][0] * __y_xpd__[3][6]) + (__x_xpd__[3][7] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[26] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[27] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][9]) + (__x_xpd__[3][7] * __y_xpd__[3][2]) + (__x_xpd__[3][2] * __y_xpd__[3][7]) + (__x_xpd__[3][1] * __y_xpd__[3][8]) + (__x_xpd__[3][8] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[28] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][9]) + (__x_xpd__[3][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][8]) + (__x_xpd__[3][6] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[29] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[30] += ((__x_xpd__[3][5] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][6]) + (__x_xpd__[3][7] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][3]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[1] += ((__x_xpd__[3][9] * __y_xpd__[4][4]) + (__x_xpd__[3][7] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[2] += ((__x_xpd__[3][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][0]) + (__x_xpd__[3][5] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[3] += ((__x_xpd__[3][3] * __y_xpd__[4][1]) + (__x_xpd__[3][1] * __y_xpd__[4][4]) + (__x_xpd__[3][7] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[4] += ((__x_xpd__[3][2] * __y_xpd__[4][4]) + (__x_xpd__[3][4] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[4][0]) + (__x_xpd__[3][1] * __y_xpd__[4][2]) + (__x_xpd__[3][0] * __y_xpd__[4][1]) + (__x_xpd__[3][2] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[16] += ((__x_xpd__[3][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[17] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[4][3]) + (__x_xpd__[3][2] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[18] += ((__x_xpd__[3][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[3][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[20] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[4][4]) + (__x_xpd__[3][9] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[3][7] * __y_xpd__[4][0]) + (__x_xpd__[3][9] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[4][4]) + (__x_xpd__[3][8] * __y_xpd__[4][2]) + (__x_xpd__[3][7] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[4][3]) + (__x_xpd__[3][5] * __y_xpd__[4][4]) + (__x_xpd__[3][8] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][1]));

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[6] += (__x_xpd__[3][6] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[7] += (-1.0f * __x_xpd__[3][7] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[8] += (__x_xpd__[3][8] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[9] += (__x_xpd__[3][3] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[10] += (__x_xpd__[3][4] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[11] += (__x_xpd__[3][5] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[12] += (__x_xpd__[3][0] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[13] += (__x_xpd__[3][1] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[14] += (__x_xpd__[3][2] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[15] += (__x_xpd__[3][9] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 16) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[26] += (__x_xpd__[4][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[27] += (__x_xpd__[4][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[28] += (__x_xpd__[4][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[29] += (__x_xpd__[4][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[30] += (__x_xpd__[4][4] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[1][1]) + (__x_xpd__[4][1] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[17] += ((__x_xpd__[4][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[1][3]) + (__x_xpd__[4][3] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[19] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[1][1]) + (__x_xpd__[4][1] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[20] += ((__x_xpd__[4][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[4][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[22] += ((__x_xpd__[4][4] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[1][2]) + (__x_xpd__[4][2] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[1][0]) + (__x_xpd__[4][4] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[1][0]) + (__x_xpd__[4][4] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[31] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[1][1]) + (__x_xpd__[4][0] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[1][2]) + (__x_xpd__[4][4] * __y_xpd__[1][4]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][1]) + (__x_xpd__[4][2] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[2][2]) + (__x_xpd__[4][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[2][0]) + (__x_xpd__[4][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][8]) + (__x_xpd__[4][3] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[4][1] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[4][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][7]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[2][8]) + (__x_xpd__[4][3] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][6]) + (__x_xpd__[4][1] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[14] += ((__x_xpd__[4][2] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][7]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[26] += ((__x_xpd__[4][1] * __y_xpd__[2][6]) + (__x_xpd__[4][3] * __y_xpd__[2][8]) + (__x_xpd__[4][2] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[27] += ((__x_xpd__[4][4] * __y_xpd__[2][6]) + (__x_xpd__[4][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[28] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[2][4]) + (__x_xpd__[4][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][1]) + (__x_xpd__[4][1] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[29] += ((__x_xpd__[4][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][2]) + (__x_xpd__[4][4] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[30] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[2][1]) + (__x_xpd__[4][4] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][2]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[1] += ((__x_xpd__[4][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][7]) + (__x_xpd__[4][1] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][0]) + (__x_xpd__[4][0] * __y_xpd__[3][6]) + (__x_xpd__[4][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][1]) + (__x_xpd__[4][3] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][2]) + (__x_xpd__[4][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][4]) + (__x_xpd__[4][1] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[3][2]) + (__x_xpd__[4][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[3][2]) + (__x_xpd__[4][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[17] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[3][0]) + (__x_xpd__[4][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][3]) + (__x_xpd__[4][2] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[19] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][2]) + (__x_xpd__[4][3] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[20] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][6]) + (__x_xpd__[4][1] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[4][2] * __y_xpd__[3][9]) + (__x_xpd__[4][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][4]) + (__x_xpd__[4][3] * __y_xpd__[3][7]) + (__x_xpd__[4][2] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[3][6]) + (__x_xpd__[4][4] * __y_xpd__[3][5]) + (__x_xpd__[4][1] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][4]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[0] += ((__x_xpd__[4][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][2]) + (__x_xpd__[4][4] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[4][1]) + (__x_xpd__[4][1] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[4][2] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[4][3]) + (__x_xpd__[4][3] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[4][2]) + (__x_xpd__[4][2] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[4][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[4][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[13] += ((__x_xpd__[4][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[15] += ((__x_xpd__[4][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[4][0]));

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[4][4] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[4][1] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[3] += (__x_xpd__[4][2] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[4] += (__x_xpd__[4][3] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[5] += (__x_xpd__[4][0] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 32) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[31] += (__x_xpd__[5][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[26] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][4]);
				__tmp_coord_array_2__[27] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][1]);
				__tmp_coord_array_2__[28] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][2]);
				__tmp_coord_array_2__[29] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][3]);
				__tmp_coord_array_2__[30] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][0]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[16] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][6]);
				__tmp_coord_array_2__[17] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][7]);
				__tmp_coord_array_2__[18] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][8]);
				__tmp_coord_array_2__[19] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][3]);
				__tmp_coord_array_2__[20] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][4]);
				__tmp_coord_array_2__[21] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][5]);
				__tmp_coord_array_2__[22] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][0]);
				__tmp_coord_array_2__[23] += (__x_xpd__[5][0] * __y_xpd__[2][1]);
				__tmp_coord_array_2__[24] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][2]);
				__tmp_coord_array_2__[25] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][9]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[6] += (__x_xpd__[5][0] * __y_xpd__[3][6]);
				__tmp_coord_array_2__[7] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][7]);
				__tmp_coord_array_2__[8] += (__x_xpd__[5][0] * __y_xpd__[3][8]);
				__tmp_coord_array_2__[9] += (__x_xpd__[5][0] * __y_xpd__[3][3]);
				__tmp_coord_array_2__[10] += (__x_xpd__[5][0] * __y_xpd__[3][4]);
				__tmp_coord_array_2__[11] += (__x_xpd__[5][0] * __y_xpd__[3][5]);
				__tmp_coord_array_2__[12] += (__x_xpd__[5][0] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[13] += (__x_xpd__[5][0] * __y_xpd__[3][1]);
				__tmp_coord_array_2__[14] += (__x_xpd__[5][0] * __y_xpd__[3][2]);
				__tmp_coord_array_2__[15] += (__x_xpd__[5][0] * __y_xpd__[3][9]);

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[5][0] * __y_xpd__[4][4]);
				__tmp_coord_array_2__[2] += (__x_xpd__[5][0] * __y_xpd__[4][1]);
				__tmp_coord_array_2__[3] += (__x_xpd__[5][0] * __y_xpd__[4][2]);
				__tmp_coord_array_2__[4] += (__x_xpd__[5][0] * __y_xpd__[4][3]);
				__tmp_coord_array_2__[5] += (__x_xpd__[5][0] * __y_xpd__[4][0]);

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[0] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_2__);
		return __temp_var_1__;
	}
	inline mv gpEM(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_3__[32] ;
		mv_zero(__tmp_coord_array_3__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_3__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);
				__tmp_coord_array_3__[4] += (__x_xpd__[0][0] * __y_xpd__[1][3]);
				__tmp_coord_array_3__[5] += (__x_xpd__[0][0] * __y_xpd__[1][4]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[6] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_3__[7] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_3__[8] += (__x_xpd__[0][0] * __y_xpd__[2][2]);
				__tmp_coord_array_3__[9] += (__x_xpd__[0][0] * __y_xpd__[2][3]);
				__tmp_coord_array_3__[10] += (__x_xpd__[0][0] * __y_xpd__[2][4]);
				__tmp_coord_array_3__[11] += (__x_xpd__[0][0] * __y_xpd__[2][5]);
				__tmp_coord_array_3__[12] += (__x_xpd__[0][0] * __y_xpd__[2][6]);
				__tmp_coord_array_3__[13] += (__x_xpd__[0][0] * __y_xpd__[2][7]);
				__tmp_coord_array_3__[14] += (__x_xpd__[0][0] * __y_xpd__[2][8]);
				__tmp_coord_array_3__[15] += (__x_xpd__[0][0] * __y_xpd__[2][9]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[16] += (__x_xpd__[0][0] * __y_xpd__[3][0]);
				__tmp_coord_array_3__[17] += (__x_xpd__[0][0] * __y_xpd__[3][1]);
				__tmp_coord_array_3__[18] += (__x_xpd__[0][0] * __y_xpd__[3][2]);
				__tmp_coord_array_3__[19] += (__x_xpd__[0][0] * __y_xpd__[3][3]);
				__tmp_coord_array_3__[20] += (__x_xpd__[0][0] * __y_xpd__[3][4]);
				__tmp_coord_array_3__[21] += (__x_xpd__[0][0] * __y_xpd__[3][5]);
				__tmp_coord_array_3__[22] += (__x_xpd__[0][0] * __y_xpd__[3][6]);
				__tmp_coord_array_3__[23] += (__x_xpd__[0][0] * __y_xpd__[3][7]);
				__tmp_coord_array_3__[24] += (__x_xpd__[0][0] * __y_xpd__[3][8]);
				__tmp_coord_array_3__[25] += (__x_xpd__[0][0] * __y_xpd__[3][9]);

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[26] += (__x_xpd__[0][0] * __y_xpd__[4][0]);
				__tmp_coord_array_3__[27] += (__x_xpd__[0][0] * __y_xpd__[4][1]);
				__tmp_coord_array_3__[28] += (__x_xpd__[0][0] * __y_xpd__[4][2]);
				__tmp_coord_array_3__[29] += (__x_xpd__[0][0] * __y_xpd__[4][3]);
				__tmp_coord_array_3__[30] += (__x_xpd__[0][0] * __y_xpd__[4][4]);

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[31] += (__x_xpd__[0][0] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[4] += (__x_xpd__[1][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[5] += (__x_xpd__[1][4] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[0] += ((__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][3] * __y_xpd__[1][3]) + (__x_xpd__[1][4] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[6] += ((__x_xpd__[1][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[8] += ((__x_xpd__[1][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[1][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[1][3]) + (__x_xpd__[1][3] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[1][1] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[1][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][3]) + (__x_xpd__[1][3] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][4]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[1] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[2] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][0]) + (__x_xpd__[1][3] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[1][1] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (__x_xpd__[1][0] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[4] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][8]) + (__x_xpd__[1][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][5]) + (__x_xpd__[1][0] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[5] += ((__x_xpd__[1][1] * __y_xpd__[2][6]) + (__x_xpd__[1][2] * __y_xpd__[2][7]) + (__x_xpd__[1][3] * __y_xpd__[2][8]) + (__x_xpd__[1][0] * __y_xpd__[2][9]));
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][7]) + (__x_xpd__[1][2] * __y_xpd__[2][8]) + (__x_xpd__[1][4] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][8]) + (__x_xpd__[1][3] * __y_xpd__[2][6]) + (__x_xpd__[1][4] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[18] += ((__x_xpd__[1][1] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[1][0] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][9]) + (__x_xpd__[1][4] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[20] += ((__x_xpd__[1][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][9]) + (__x_xpd__[1][4] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[1][4] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][9]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][2]) + (__x_xpd__[1][3] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[23] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][2]) + (__x_xpd__[1][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[1][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][1]) + (__x_xpd__[1][2] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[1][1] * __y_xpd__[2][4]) + (__x_xpd__[1][3] * __y_xpd__[2][3]) + (__x_xpd__[1][2] * __y_xpd__[2][5]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[6] += ((__x_xpd__[1][2] * __y_xpd__[3][8]) + (__x_xpd__[1][4] * __y_xpd__[3][4]) + (__x_xpd__[1][3] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][8]) + (__x_xpd__[1][3] * __y_xpd__[3][6]) + (__x_xpd__[1][4] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][7]) + (__x_xpd__[1][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[9] += ((__x_xpd__[1][4] * __y_xpd__[3][2]) + (__x_xpd__[1][0] * __y_xpd__[3][8]) + (__x_xpd__[1][3] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[1][4] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][9]) + (__x_xpd__[1][0] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[11] += ((__x_xpd__[1][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][7]) + (__x_xpd__[1][4] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[1][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]) + (__x_xpd__[1][0] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[1][1] * __y_xpd__[3][2]) + (__x_xpd__[1][0] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[14] += ((__x_xpd__[1][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]) + (__x_xpd__[1][2] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[26] += ((__x_xpd__[1][2] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][9]) + (__x_xpd__[1][3] * __y_xpd__[3][2]) + (__x_xpd__[1][1] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[27] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]) + (__x_xpd__[1][3] * __y_xpd__[3][5]) + (__x_xpd__[1][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][3]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[1][1] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][4]) + (__x_xpd__[1][0] * __y_xpd__[3][1]) + (__x_xpd__[1][4] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[29] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][5]) + (__x_xpd__[1][2] * __y_xpd__[3][4]) + (__x_xpd__[1][0] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[30] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][6]) + (__x_xpd__[1][0] * __y_xpd__[3][9]) + (__x_xpd__[1][2] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][8]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[16] += ((__x_xpd__[1][0] * __y_xpd__[4][1]) + (__x_xpd__[1][1] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[17] += ((__x_xpd__[1][2] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[18] += ((__x_xpd__[1][3] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[1][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[4][2]) + (__x_xpd__[1][2] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[1][3] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[1][2] * __y_xpd__[4][4]) + (__x_xpd__[1][4] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[24] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[25] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[31] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[4][2]) + (__x_xpd__[1][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][1]) + (__x_xpd__[1][4] * __y_xpd__[4][4]));

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[26] += (__x_xpd__[1][0] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[27] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[28] += (-1.0f * __x_xpd__[1][2] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[29] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[30] += (__x_xpd__[1][4] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[6] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[7] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[8] += (__x_xpd__[2][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[9] += (__x_xpd__[2][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[10] += (__x_xpd__[2][4] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[11] += (__x_xpd__[2][5] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[12] += (__x_xpd__[2][6] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[13] += (__x_xpd__[2][7] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[14] += (__x_xpd__[2][8] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[15] += (__x_xpd__[2][9] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[1] += ((__x_xpd__[2][0] * __y_xpd__[1][1]) + (__x_xpd__[2][2] * __y_xpd__[1][3]) + (__x_xpd__[2][9] * __y_xpd__[1][4]) + (__x_xpd__[2][1] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[2] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[1][3]) + (__x_xpd__[2][6] * __y_xpd__[1][4]) + (__x_xpd__[2][3] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[2][7] * __y_xpd__[1][4]) + (__x_xpd__[2][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[4] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[1][2]) + (__x_xpd__[2][5] * __y_xpd__[1][1]) + (__x_xpd__[2][8] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[5] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[1][3]) + (__x_xpd__[2][4] * __y_xpd__[1][4]) + (__x_xpd__[2][8] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[17] += ((__x_xpd__[2][6] * __y_xpd__[1][3]) + (__x_xpd__[2][5] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][4]) + (__x_xpd__[2][7] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[19] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[1][3]) + (__x_xpd__[2][2] * __y_xpd__[1][4]) + (__x_xpd__[2][8] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[1][1]) + (__x_xpd__[2][6] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[21] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[1][2]) + (__x_xpd__[2][1] * __y_xpd__[1][4]) + (__x_xpd__[2][7] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[1][2]) + (__x_xpd__[2][1] * __y_xpd__[1][3]) + (__x_xpd__[2][4] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[2][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[2][0] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[2][4] * __y_xpd__[1][1]) + (__x_xpd__[2][3] * __y_xpd__[1][3]) + (__x_xpd__[2][5] * __y_xpd__[1][2]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[0] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[6] += ((__x_xpd__[2][2] * __y_xpd__[2][5]) + (__x_xpd__[2][6] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][3]) + (__x_xpd__[2][3] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][4]) + (__x_xpd__[2][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][7]) + (__x_xpd__[2][7] * __y_xpd__[2][9]) + (__x_xpd__[2][4] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][5]) + (__x_xpd__[2][8] * __y_xpd__[2][9]) + (__x_xpd__[2][1] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][1]) + (__x_xpd__[2][5] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][5]) + (__x_xpd__[2][5] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][7]) + (__x_xpd__[2][7] * __y_xpd__[2][6]) + (__x_xpd__[2][1] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[10] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[2][8]) + (__x_xpd__[2][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][2]) + (__x_xpd__[2][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][3]) + (__x_xpd__[2][8] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][4]) + (__x_xpd__[2][0] * __y_xpd__[2][2]) + (__x_xpd__[2][4] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][6]) + (__x_xpd__[2][6] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[2][9] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][3]) + (__x_xpd__[2][8] * __y_xpd__[2][5]) + (__x_xpd__[2][3] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[2][4] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][6]) + (__x_xpd__[2][6] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][9]) + (__x_xpd__[2][9] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[14] += ((__x_xpd__[2][9] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][7]) + (__x_xpd__[2][7] * __y_xpd__[2][4]) + (__x_xpd__[2][5] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (__x_xpd__[2][2] * __y_xpd__[2][8]) + (__x_xpd__[2][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (__x_xpd__[2][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[26] += ((__x_xpd__[2][6] * __y_xpd__[2][4]) + (__x_xpd__[2][5] * __y_xpd__[2][7]) + (__x_xpd__[2][4] * __y_xpd__[2][6]) + (__x_xpd__[2][8] * __y_xpd__[2][3]) + (__x_xpd__[2][7] * __y_xpd__[2][5]) + (__x_xpd__[2][3] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[27] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][2]) + (__x_xpd__[2][9] * __y_xpd__[2][4]) + (__x_xpd__[2][4] * __y_xpd__[2][9]) + (__x_xpd__[2][1] * __y_xpd__[2][8]) + (__x_xpd__[2][8] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[2][2] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][8]) + (__x_xpd__[2][6] * __y_xpd__[2][2]) + (__x_xpd__[2][5] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][0]) + (__x_xpd__[2][9] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[29] += ((__x_xpd__[2][0] * __y_xpd__[2][7]) + (__x_xpd__[2][3] * __y_xpd__[2][9]) + (__x_xpd__[2][9] * __y_xpd__[2][3]) + (__x_xpd__[2][7] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[2][1] * __y_xpd__[2][5]) + (__x_xpd__[2][5] * __y_xpd__[2][1]) + (__x_xpd__[2][3] * __y_xpd__[2][2]) + (__x_xpd__[2][2] * __y_xpd__[2][3]) + (__x_xpd__[2][4] * __y_xpd__[2][0]) + (__x_xpd__[2][0] * __y_xpd__[2][4]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[1] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][6]) + (__x_xpd__[2][5] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[2] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[3][2]) + (__x_xpd__[2][1] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][9]) + (__x_xpd__[2][9] * __y_xpd__[3][4]) + (__x_xpd__[2][8] * __y_xpd__[3][1]) + (__x_xpd__[2][2] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[2][2] * __y_xpd__[3][6]) + (__x_xpd__[2][9] * __y_xpd__[3][5]) + (__x_xpd__[2][6] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[4] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][1]) + (__x_xpd__[2][7] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][7]) + (__x_xpd__[2][9] * __y_xpd__[3][3]));
				__tmp_coord_array_3__[5] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][6]) + (__x_xpd__[2][3] * __y_xpd__[3][1]) + (__x_xpd__[2][2] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[3][4]) + (__x_xpd__[2][0] * __y_xpd__[3][3]) + (__x_xpd__[2][4] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][0]) + (__x_xpd__[2][9] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][5]) + (__x_xpd__[2][5] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][8]) + (__x_xpd__[2][1] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[2][5] * __y_xpd__[3][4]) + (__x_xpd__[2][6] * __y_xpd__[3][7]) + (__x_xpd__[2][1] * __y_xpd__[3][0]) + (__x_xpd__[2][7] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[20] += ((__x_xpd__[2][2] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (__x_xpd__[2][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[2][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]) + (__x_xpd__[2][0] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][6]) + (__x_xpd__[2][6] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][3]) + (__x_xpd__[2][9] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][7]) + (__x_xpd__[2][0] * __y_xpd__[3][9]) + (__x_xpd__[2][8] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[23] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][1]) + (__x_xpd__[2][8] * __y_xpd__[3][4]) + (__x_xpd__[2][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[2][7] * __y_xpd__[3][4]) + (__x_xpd__[2][5] * __y_xpd__[3][6]) + (__x_xpd__[2][9] * __y_xpd__[3][2]) + (__x_xpd__[2][4] * __y_xpd__[3][7]) + (__x_xpd__[2][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[25] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][6]) + (__x_xpd__[2][8] * __y_xpd__[3][2]) + (__x_xpd__[2][6] * __y_xpd__[3][0]) + (__x_xpd__[2][1] * __y_xpd__[3][7]) + (__x_xpd__[2][7] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[31] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[3][9]) + (__x_xpd__[2][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][7]) + (__x_xpd__[2][6] * __y_xpd__[3][6]) + (__x_xpd__[2][2] * __y_xpd__[3][2]) + (__x_xpd__[2][1] * __y_xpd__[3][1]) + (__x_xpd__[2][4] * __y_xpd__[3][4]) + (__x_xpd__[2][5] * __y_xpd__[3][5]) + (__x_xpd__[2][8] * __y_xpd__[3][8]) + (__x_xpd__[2][3] * __y_xpd__[3][3]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[6] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][3]) + (__x_xpd__[2][8] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][4]) + (__x_xpd__[2][6] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][4]) + (__x_xpd__[2][7] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[10] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[2][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[13] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][3]) + (__x_xpd__[2][2] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][1]) + (__x_xpd__[2][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[26] += ((__x_xpd__[2][9] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[27] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][4]) + (__x_xpd__[2][0] * __y_xpd__[4][0]) + (__x_xpd__[2][3] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[28] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][1]) + (__x_xpd__[2][1] * __y_xpd__[4][0]) + (__x_xpd__[2][4] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[29] += ((__x_xpd__[2][5] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][2]) + (__x_xpd__[2][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[2][8] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][0]) + (__x_xpd__[2][7] * __y_xpd__[4][2]) + (__x_xpd__[2][6] * __y_xpd__[4][1]));

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[16] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[17] += (-1.0f * __x_xpd__[2][1] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[18] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[19] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[20] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[21] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[22] += (-1.0f * __x_xpd__[2][6] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[23] += (__x_xpd__[2][7] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[24] += (-1.0f * __x_xpd__[2][8] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[25] += (__x_xpd__[2][9] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[16] += (__x_xpd__[3][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[17] += (__x_xpd__[3][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[18] += (__x_xpd__[3][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[19] += (__x_xpd__[3][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[20] += (__x_xpd__[3][4] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[21] += (__x_xpd__[3][5] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[22] += (__x_xpd__[3][6] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[23] += (__x_xpd__[3][7] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[24] += (__x_xpd__[3][8] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[25] += (__x_xpd__[3][9] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[6] += ((__x_xpd__[3][8] * __y_xpd__[1][2]) + (__x_xpd__[3][4] * __y_xpd__[1][4]) + (__x_xpd__[3][7] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[7] += ((__x_xpd__[3][5] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[1][1]) + (__x_xpd__[3][6] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[1][2]) + (__x_xpd__[3][3] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[9] += ((__x_xpd__[3][8] * __y_xpd__[1][0]) + (__x_xpd__[3][2] * __y_xpd__[1][4]) + (__x_xpd__[3][9] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[3][6] * __y_xpd__[1][0]) + (__x_xpd__[3][9] * __y_xpd__[1][1]) + (__x_xpd__[3][0] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[11] += ((__x_xpd__[3][9] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][0]) + (__x_xpd__[3][1] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[3][1] * __y_xpd__[1][3]) + (__x_xpd__[3][4] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[3][5] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][3]) + (__x_xpd__[3][2] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[14] += ((__x_xpd__[3][3] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][1]) + (__x_xpd__[3][0] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[26] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][3]) + (__x_xpd__[3][9] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[27] += ((__x_xpd__[3][3] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][0]) + (__x_xpd__[3][6] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[3][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[29] += ((__x_xpd__[3][8] * __y_xpd__[1][4]) + (__x_xpd__[3][5] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[30] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][2]) + (__x_xpd__[3][8] * __y_xpd__[1][3]) + (__x_xpd__[3][6] * __y_xpd__[1][1]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[1] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][8]) + (__x_xpd__[3][7] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[2] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[2][7]) + (__x_xpd__[3][8] * __y_xpd__[2][1]) + (__x_xpd__[3][1] * __y_xpd__[2][8]) + (__x_xpd__[3][4] * __y_xpd__[2][9]) + (__x_xpd__[3][7] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[3][6] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][5]) + (__x_xpd__[3][2] * __y_xpd__[2][6]) + (__x_xpd__[3][5] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[4] += ((__x_xpd__[3][0] * __y_xpd__[2][7]) + (__x_xpd__[3][3] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[5] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[16] += ((__x_xpd__[3][3] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][3]) + (__x_xpd__[3][9] * __y_xpd__[2][6]) + (__x_xpd__[3][2] * __y_xpd__[2][5]) + (__x_xpd__[3][6] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][9]) + (__x_xpd__[3][0] * __y_xpd__[2][3]) + (__x_xpd__[3][9] * __y_xpd__[2][7]) + (__x_xpd__[3][4] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[18] += ((__x_xpd__[3][8] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][1]) + (__x_xpd__[3][1] * __y_xpd__[2][4]) + (__x_xpd__[3][5] * __y_xpd__[2][0]) + (__x_xpd__[3][9] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[19] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][6]) + (__x_xpd__[3][5] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][5]) + (__x_xpd__[3][1] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[2][2]) + (__x_xpd__[3][8] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][3]) + (__x_xpd__[3][7] * __y_xpd__[2][8]) + (__x_xpd__[3][2] * __y_xpd__[2][1]) + (__x_xpd__[3][3] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[3][0] * __y_xpd__[2][2]) + (__x_xpd__[3][6] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][0]) + (__x_xpd__[3][4] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[22] += ((__x_xpd__[3][3] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][9]) + (__x_xpd__[3][7] * __y_xpd__[2][3]) + (__x_xpd__[3][8] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[3][3] * __y_xpd__[2][6]) + (__x_xpd__[3][8] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][3]) + (__x_xpd__[3][9] * __y_xpd__[2][1]) + (__x_xpd__[3][1] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[3][5] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[3][6] * __y_xpd__[2][0]) + (__x_xpd__[3][8] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[31] += ((__x_xpd__[3][8] * __y_xpd__[2][8]) + (__x_xpd__[3][5] * __y_xpd__[2][5]) + (__x_xpd__[3][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][7]) + (__x_xpd__[3][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][9]) + (__x_xpd__[3][6] * __y_xpd__[2][6]) + (__x_xpd__[3][1] * __y_xpd__[2][1]) + (__x_xpd__[3][2] * __y_xpd__[2][2]) + (__x_xpd__[3][0] * __y_xpd__[2][0]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[0] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[6] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[3][9]) + (__x_xpd__[3][3] * __y_xpd__[3][1]) + (__x_xpd__[3][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][3]) + (__x_xpd__[3][9] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[7] += ((__x_xpd__[3][4] * __y_xpd__[3][2]) + (__x_xpd__[3][7] * __y_xpd__[3][9]) + (__x_xpd__[3][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[8] += ((__x_xpd__[3][1] * __y_xpd__[3][4]) + (__x_xpd__[3][9] * __y_xpd__[3][8]) + (__x_xpd__[3][5] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[9] += ((__x_xpd__[3][6] * __y_xpd__[3][7]) + (__x_xpd__[3][1] * __y_xpd__[3][0]) + (__x_xpd__[3][5] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[10] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][3]) + (__x_xpd__[3][7] * __y_xpd__[3][8]) + (__x_xpd__[3][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][7]) + (__x_xpd__[3][2] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[3][6]) + (__x_xpd__[3][4] * __y_xpd__[3][3]) + (__x_xpd__[3][0] * __y_xpd__[3][2]) + (__x_xpd__[3][6] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[12] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[3][7]) + (__x_xpd__[3][8] * __y_xpd__[3][5]) + (__x_xpd__[3][0] * __y_xpd__[3][9]) + (__x_xpd__[3][7] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[13] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[3][6]) + (__x_xpd__[3][4] * __y_xpd__[3][8]) + (__x_xpd__[3][6] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][4]) + (__x_xpd__[3][1] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[14] += ((__x_xpd__[3][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][4]) + (__x_xpd__[3][4] * __y_xpd__[3][7]) + (__x_xpd__[3][5] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[15] += ((__x_xpd__[3][0] * __y_xpd__[3][6]) + (__x_xpd__[3][7] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][0]) + (__x_xpd__[3][2] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[26] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[3][7]) + (__x_xpd__[3][4] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][5]) + (__x_xpd__[3][3] * __y_xpd__[3][8]) + (__x_xpd__[3][8] * __y_xpd__[3][3]) + (__x_xpd__[3][6] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[27] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][9]) + (__x_xpd__[3][2] * __y_xpd__[3][7]) + (__x_xpd__[3][7] * __y_xpd__[3][2]) + (__x_xpd__[3][8] * __y_xpd__[3][1]) + (__x_xpd__[3][1] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[3][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][5]) + (__x_xpd__[3][6] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[29] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[3][4] * __y_xpd__[3][0]) + (__x_xpd__[3][3] * __y_xpd__[3][2]) + (__x_xpd__[3][5] * __y_xpd__[3][1]) + (__x_xpd__[3][1] * __y_xpd__[3][5]) + (__x_xpd__[3][0] * __y_xpd__[3][4]) + (__x_xpd__[3][2] * __y_xpd__[3][3]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[1] += ((__x_xpd__[3][9] * __y_xpd__[4][4]) + (__x_xpd__[3][1] * __y_xpd__[4][2]) + (__x_xpd__[3][0] * __y_xpd__[4][1]) + (__x_xpd__[3][2] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[2] += ((__x_xpd__[3][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[4][3]) + (__x_xpd__[3][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[3][1] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][1]) + (__x_xpd__[3][7] * __y_xpd__[4][4]) + (__x_xpd__[3][4] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[4] += ((__x_xpd__[3][5] * __y_xpd__[4][1]) + (__x_xpd__[3][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[5] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][3]) + (__x_xpd__[3][7] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[16] += ((__x_xpd__[3][7] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][4]) + (__x_xpd__[3][8] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][1]) + (__x_xpd__[3][6] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[19] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[4][0]) + (__x_xpd__[3][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[4][4]) + (__x_xpd__[3][9] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[3][9] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[4][4]) + (__x_xpd__[3][7] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[4][0]) + (__x_xpd__[3][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[3][5] * __y_xpd__[4][0]) + (__x_xpd__[3][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[3][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[3][5] * __y_xpd__[4][2]) + (__x_xpd__[3][4] * __y_xpd__[4][1]) + (__x_xpd__[3][3] * __y_xpd__[4][3]));

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[6] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[7] += (-1.0f * __x_xpd__[3][1] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[8] += (-1.0f * __x_xpd__[3][2] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[9] += (-1.0f * __x_xpd__[3][3] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[10] += (-1.0f * __x_xpd__[3][4] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[11] += (-1.0f * __x_xpd__[3][5] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[12] += (-1.0f * __x_xpd__[3][6] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[13] += (__x_xpd__[3][7] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[14] += (-1.0f * __x_xpd__[3][8] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[15] += (__x_xpd__[3][9] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 16) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[26] += (__x_xpd__[4][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[27] += (__x_xpd__[4][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[28] += (__x_xpd__[4][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[29] += (__x_xpd__[4][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[30] += (__x_xpd__[4][4] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[4][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[1][2]) + (__x_xpd__[4][2] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[4][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[22] += ((__x_xpd__[4][1] * __y_xpd__[1][4]) + (__x_xpd__[4][4] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[23] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[4][3] * __y_xpd__[1][4]) + (__x_xpd__[4][4] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[4][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[31] += ((__x_xpd__[4][4] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][1]) + (__x_xpd__[4][0] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][3]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[6] += ((__x_xpd__[4][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][8]) + (__x_xpd__[4][3] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[2][6]) + (__x_xpd__[4][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[10] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][9]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[4][3] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[4][1] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][1]) + (__x_xpd__[4][2] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[26] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][9]) + (__x_xpd__[4][3] * __y_xpd__[2][2]) + (__x_xpd__[4][2] * __y_xpd__[2][1]) + (__x_xpd__[4][1] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[27] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][3]) + (__x_xpd__[4][4] * __y_xpd__[2][6]) + (__x_xpd__[4][3] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[4][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][4]) + (__x_xpd__[4][1] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[29] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][5]) + (__x_xpd__[4][2] * __y_xpd__[2][4]) + (__x_xpd__[4][4] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[30] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][7]) + (__x_xpd__[4][0] * __y_xpd__[2][9]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[1] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[2] += ((__x_xpd__[4][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][0]) + (__x_xpd__[4][4] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][3]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[4][1] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[4] += ((__x_xpd__[4][4] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][2]) + (__x_xpd__[4][2] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[5] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[3][7]) + (__x_xpd__[4][0] * __y_xpd__[3][9]) + (__x_xpd__[4][1] * __y_xpd__[3][6]) + (__x_xpd__[4][3] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[16] += ((__x_xpd__[4][3] * __y_xpd__[3][7]) + (__x_xpd__[4][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][5]) + (__x_xpd__[4][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[19] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][2]) + (__x_xpd__[4][3] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][0]) + (__x_xpd__[4][1] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[4][0] * __y_xpd__[3][7]) + (__x_xpd__[4][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][2]) + (__x_xpd__[4][3] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[4][0] * __y_xpd__[3][5]) + (__x_xpd__[4][3] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[4][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[4][3] * __y_xpd__[3][3]) + (__x_xpd__[4][1] * __y_xpd__[3][4]) + (__x_xpd__[4][2] * __y_xpd__[3][5]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[0] += ((__x_xpd__[4][2] * __y_xpd__[4][2]) + (__x_xpd__[4][3] * __y_xpd__[4][3]) + (__x_xpd__[4][4] * __y_xpd__[4][4]) + (__x_xpd__[4][1] * __y_xpd__[4][1]) + (__x_xpd__[4][0] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[6] += ((__x_xpd__[4][1] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[7] += ((__x_xpd__[4][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[8] += ((__x_xpd__[4][3] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[4][1]) + (__x_xpd__[4][1] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[4][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[11] += ((__x_xpd__[4][3] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[12] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[4][4]) + (__x_xpd__[4][4] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[4][4] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[4][4]) + (__x_xpd__[4][4] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][4]));

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[4][0] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[2] += (-1.0f * __x_xpd__[4][1] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[3] += (-1.0f * __x_xpd__[4][2] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[4] += (-1.0f * __x_xpd__[4][3] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[5] += (__x_xpd__[4][4] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 32) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[31] += (__x_xpd__[5][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[26] += (__x_xpd__[5][0] * __y_xpd__[1][0]);
				__tmp_coord_array_3__[27] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][1]);
				__tmp_coord_array_3__[28] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][2]);
				__tmp_coord_array_3__[29] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][3]);
				__tmp_coord_array_3__[30] += (__x_xpd__[5][0] * __y_xpd__[1][4]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[16] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][0]);
				__tmp_coord_array_3__[17] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][1]);
				__tmp_coord_array_3__[18] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][2]);
				__tmp_coord_array_3__[19] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][3]);
				__tmp_coord_array_3__[20] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][4]);
				__tmp_coord_array_3__[21] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][5]);
				__tmp_coord_array_3__[22] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][6]);
				__tmp_coord_array_3__[23] += (__x_xpd__[5][0] * __y_xpd__[2][7]);
				__tmp_coord_array_3__[24] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][8]);
				__tmp_coord_array_3__[25] += (__x_xpd__[5][0] * __y_xpd__[2][9]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[6] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][0]);
				__tmp_coord_array_3__[7] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][1]);
				__tmp_coord_array_3__[8] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][2]);
				__tmp_coord_array_3__[9] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][3]);
				__tmp_coord_array_3__[10] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][4]);
				__tmp_coord_array_3__[11] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][5]);
				__tmp_coord_array_3__[12] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][6]);
				__tmp_coord_array_3__[13] += (__x_xpd__[5][0] * __y_xpd__[3][7]);
				__tmp_coord_array_3__[14] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][8]);
				__tmp_coord_array_3__[15] += (__x_xpd__[5][0] * __y_xpd__[3][9]);

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[5][0] * __y_xpd__[4][0]);
				__tmp_coord_array_3__[2] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[4][1]);
				__tmp_coord_array_3__[3] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[4][2]);
				__tmp_coord_array_3__[4] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[4][3]);
				__tmp_coord_array_3__[5] += (__x_xpd__[5][0] * __y_xpd__[4][4]);

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[0] += (__x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_3__);
		return __temp_var_1__;
	}
	inline scalar scpEM(const mv& x, const mv& y) {
		scalar __temp_var_1__;
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 2) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][4] * __y_xpd__[1][4]) + (__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 4) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][6]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 8) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]));

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 16) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[4][1] * __y_xpd__[4][1]) + (__x_xpd__[4][2] * __y_xpd__[4][2]) + (__x_xpd__[4][0] * __y_xpd__[4][0]) + (__x_xpd__[4][4] * __y_xpd__[4][4]) + (__x_xpd__[4][3] * __y_xpd__[4][3]));

			}

		}
		if (((y.m_gu & 32) != 0)) {
			if (((x.m_gu & 32) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		return __temp_var_1__;
	}
	inline mv lcontEM(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_4__[32] ;
		mv_zero(__tmp_coord_array_4__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[1] += (__y_xpd__[1][0] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[2] += (__y_xpd__[1][1] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[3] += (__y_xpd__[1][2] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[4] += (__y_xpd__[1][3] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[5] += (__y_xpd__[1][4] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[0] += ((__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][4] * __y_xpd__[1][4]) + (__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[6] += (__y_xpd__[2][0] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[7] += (__y_xpd__[2][1] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[8] += (__y_xpd__[2][2] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[9] += (__y_xpd__[2][3] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[10] += (__y_xpd__[2][4] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[11] += (__y_xpd__[2][5] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[12] += (__y_xpd__[2][6] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[13] += (__y_xpd__[2][7] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[14] += (__y_xpd__[2][8] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[15] += (__y_xpd__[2][9] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[1] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][2]));
				__tmp_coord_array_4__[2] += ((__x_xpd__[1][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][6]) + (__x_xpd__[1][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][3]));
				__tmp_coord_array_4__[3] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (__x_xpd__[1][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][7]) + (__x_xpd__[1][1] * __y_xpd__[2][3]));
				__tmp_coord_array_4__[4] += ((__x_xpd__[1][0] * __y_xpd__[2][2]) + (__x_xpd__[1][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][5]));
				__tmp_coord_array_4__[5] += ((__x_xpd__[1][3] * __y_xpd__[2][8]) + (__x_xpd__[1][0] * __y_xpd__[2][9]) + (__x_xpd__[1][2] * __y_xpd__[2][7]) + (__x_xpd__[1][1] * __y_xpd__[2][6]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_4__[0] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][9]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[16] += (__y_xpd__[3][0] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[17] += (__y_xpd__[3][1] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[18] += (__y_xpd__[3][2] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[19] += (__y_xpd__[3][3] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[20] += (__y_xpd__[3][4] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[21] += (__y_xpd__[3][5] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[22] += (__y_xpd__[3][6] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[23] += (__y_xpd__[3][7] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[24] += (__y_xpd__[3][8] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[25] += (__y_xpd__[3][9] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[6] += ((__x_xpd__[1][4] * __y_xpd__[3][4]) + (__x_xpd__[1][3] * __y_xpd__[3][7]) + (__x_xpd__[1][2] * __y_xpd__[3][8]));
				__tmp_coord_array_4__[7] += ((__x_xpd__[1][4] * __y_xpd__[3][5]) + (__x_xpd__[1][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][8]));
				__tmp_coord_array_4__[8] += ((__x_xpd__[1][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][7]));
				__tmp_coord_array_4__[9] += ((__x_xpd__[1][3] * __y_xpd__[3][9]) + (__x_xpd__[1][4] * __y_xpd__[3][2]) + (__x_xpd__[1][0] * __y_xpd__[3][8]));
				__tmp_coord_array_4__[10] += ((__x_xpd__[1][4] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][9]) + (__x_xpd__[1][0] * __y_xpd__[3][6]));
				__tmp_coord_array_4__[11] += ((__x_xpd__[1][2] * __y_xpd__[3][9]) + (__x_xpd__[1][4] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][7]));
				__tmp_coord_array_4__[12] += ((__x_xpd__[1][0] * __y_xpd__[3][4]) + (__x_xpd__[1][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]));
				__tmp_coord_array_4__[13] += ((__x_xpd__[1][0] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][2]));
				__tmp_coord_array_4__[14] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]) + (__x_xpd__[1][0] * __y_xpd__[3][3]) + (__x_xpd__[1][2] * __y_xpd__[3][0]));
				__tmp_coord_array_4__[15] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][3]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_4__[1] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][5]) + (__x_xpd__[2][5] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][6]));
				__tmp_coord_array_4__[2] += ((__x_xpd__[2][9] * __y_xpd__[3][4]) + (__x_xpd__[2][1] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][9]) + (__x_xpd__[2][2] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][2]) + (__x_xpd__[2][8] * __y_xpd__[3][1]));
				__tmp_coord_array_4__[3] += ((__x_xpd__[2][6] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][8]) + (__x_xpd__[2][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][9]) + (__x_xpd__[2][9] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][0]));
				__tmp_coord_array_4__[4] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][9]) + (__x_xpd__[2][9] * __y_xpd__[3][3]) + (__x_xpd__[2][7] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][1]));
				__tmp_coord_array_4__[5] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_4__[0] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][7]));

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[26] += (__y_xpd__[4][0] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[27] += (__y_xpd__[4][1] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[28] += (__y_xpd__[4][2] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[29] += (__y_xpd__[4][3] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[30] += (__y_xpd__[4][4] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[16] += ((__x_xpd__[1][0] * __y_xpd__[4][1]) + (__x_xpd__[1][1] * __y_xpd__[4][0]));
				__tmp_coord_array_4__[17] += ((__x_xpd__[1][2] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[18] += ((__x_xpd__[1][0] * __y_xpd__[4][3]) + (__x_xpd__[1][3] * __y_xpd__[4][0]));
				__tmp_coord_array_4__[19] += ((__x_xpd__[1][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[20] += ((__x_xpd__[1][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[21] += ((__x_xpd__[1][3] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][3]));
				__tmp_coord_array_4__[22] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[23] += ((__x_xpd__[1][4] * __y_xpd__[4][2]) + (__x_xpd__[1][2] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[24] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[25] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][4]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_4__[6] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][4]) + (__x_xpd__[2][8] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[7] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][1]) + (__x_xpd__[2][6] * __y_xpd__[4][3]));
				__tmp_coord_array_4__[8] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][2]) + (__x_xpd__[2][7] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[9] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[10] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[11] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[12] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]) + (__x_xpd__[2][1] * __y_xpd__[4][3]));
				__tmp_coord_array_4__[13] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][3]) + (__x_xpd__[2][2] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[14] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][1]) + (__x_xpd__[2][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]));
				__tmp_coord_array_4__[15] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][1]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_4__[1] += ((__x_xpd__[3][9] * __y_xpd__[4][4]) + (__x_xpd__[3][2] * __y_xpd__[4][3]) + (__x_xpd__[3][1] * __y_xpd__[4][2]) + (__x_xpd__[3][0] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[2] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[4][4]) + (__x_xpd__[3][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[4][3]) + (__x_xpd__[3][0] * __y_xpd__[4][0]));
				__tmp_coord_array_4__[3] += ((__x_xpd__[3][1] * __y_xpd__[4][0]) + (__x_xpd__[3][4] * __y_xpd__[4][3]) + (__x_xpd__[3][7] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[4] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][2]) + (__x_xpd__[3][2] * __y_xpd__[4][0]) + (__x_xpd__[3][5] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[5] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][3]) + (__x_xpd__[3][7] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][1]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_4__[0] += ((__x_xpd__[4][2] * __y_xpd__[4][2]) + (__x_xpd__[4][4] * __y_xpd__[4][4]) + (__x_xpd__[4][0] * __y_xpd__[4][0]) + (__x_xpd__[4][1] * __y_xpd__[4][1]) + (__x_xpd__[4][3] * __y_xpd__[4][3]));

			}

		}
		if (((y.m_gu & 32) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[31] += (__y_xpd__[5][0] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[26] += (__x_xpd__[1][0] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[27] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[28] += (-1.0f * __x_xpd__[1][2] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[29] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[30] += (__x_xpd__[1][4] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_4__[16] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[17] += (-1.0f * __x_xpd__[2][1] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[18] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[19] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[20] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[21] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[22] += (-1.0f * __x_xpd__[2][6] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[23] += (__x_xpd__[2][7] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[24] += (-1.0f * __x_xpd__[2][8] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[25] += (__x_xpd__[2][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_4__[6] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[7] += (-1.0f * __x_xpd__[3][1] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[8] += (-1.0f * __x_xpd__[3][2] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[9] += (-1.0f * __x_xpd__[3][3] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[10] += (-1.0f * __x_xpd__[3][4] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[11] += (-1.0f * __x_xpd__[3][5] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[12] += (-1.0f * __x_xpd__[3][6] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[13] += (__x_xpd__[3][7] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[14] += (-1.0f * __x_xpd__[3][8] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[15] += (__x_xpd__[3][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_4__[1] += (__x_xpd__[4][0] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[2] += (-1.0f * __x_xpd__[4][1] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[3] += (-1.0f * __x_xpd__[4][2] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[4] += (-1.0f * __x_xpd__[4][3] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[5] += (__x_xpd__[4][4] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_4__[0] += (__x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_4__);
		return __temp_var_1__;
	}
	inline mv op(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_5__[32] ;
		mv_zero(__tmp_coord_array_5__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_5__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_5__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);
				__tmp_coord_array_5__[4] += (__x_xpd__[0][0] * __y_xpd__[1][3]);
				__tmp_coord_array_5__[5] += (__x_xpd__[0][0] * __y_xpd__[1][4]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_5__[6] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_5__[7] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_5__[8] += (__x_xpd__[0][0] * __y_xpd__[2][2]);
				__tmp_coord_array_5__[9] += (__x_xpd__[0][0] * __y_xpd__[2][3]);
				__tmp_coord_array_5__[10] += (__x_xpd__[0][0] * __y_xpd__[2][4]);
				__tmp_coord_array_5__[11] += (__x_xpd__[0][0] * __y_xpd__[2][5]);
				__tmp_coord_array_5__[12] += (__x_xpd__[0][0] * __y_xpd__[2][6]);
				__tmp_coord_array_5__[13] += (__x_xpd__[0][0] * __y_xpd__[2][7]);
				__tmp_coord_array_5__[14] += (__x_xpd__[0][0] * __y_xpd__[2][8]);
				__tmp_coord_array_5__[15] += (__x_xpd__[0][0] * __y_xpd__[2][9]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_5__[16] += (__x_xpd__[0][0] * __y_xpd__[3][0]);
				__tmp_coord_array_5__[17] += (__x_xpd__[0][0] * __y_xpd__[3][1]);
				__tmp_coord_array_5__[18] += (__x_xpd__[0][0] * __y_xpd__[3][2]);
				__tmp_coord_array_5__[19] += (__x_xpd__[0][0] * __y_xpd__[3][3]);
				__tmp_coord_array_5__[20] += (__x_xpd__[0][0] * __y_xpd__[3][4]);
				__tmp_coord_array_5__[21] += (__x_xpd__[0][0] * __y_xpd__[3][5]);
				__tmp_coord_array_5__[22] += (__x_xpd__[0][0] * __y_xpd__[3][6]);
				__tmp_coord_array_5__[23] += (__x_xpd__[0][0] * __y_xpd__[3][7]);
				__tmp_coord_array_5__[24] += (__x_xpd__[0][0] * __y_xpd__[3][8]);
				__tmp_coord_array_5__[25] += (__x_xpd__[0][0] * __y_xpd__[3][9]);

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_5__[26] += (__x_xpd__[0][0] * __y_xpd__[4][0]);
				__tmp_coord_array_5__[27] += (__x_xpd__[0][0] * __y_xpd__[4][1]);
				__tmp_coord_array_5__[28] += (__x_xpd__[0][0] * __y_xpd__[4][2]);
				__tmp_coord_array_5__[29] += (__x_xpd__[0][0] * __y_xpd__[4][3]);
				__tmp_coord_array_5__[30] += (__x_xpd__[0][0] * __y_xpd__[4][4]);

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_5__[31] += (__x_xpd__[0][0] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[4] += (__x_xpd__[1][3] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[5] += (__x_xpd__[1][4] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[6] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][1]));
				__tmp_coord_array_5__[7] += ((__x_xpd__[1][0] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[8] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[9] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][2]));
				__tmp_coord_array_5__[10] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[1][2]) + (__x_xpd__[1][2] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[11] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[1][3]) + (__x_xpd__[1][3] * __y_xpd__[1][1]));
				__tmp_coord_array_5__[12] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[13] += ((__x_xpd__[1][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][2]));
				__tmp_coord_array_5__[14] += ((__x_xpd__[1][3] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[15] += ((__x_xpd__[1][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_5__[16] += ((__x_xpd__[1][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][4]));
				__tmp_coord_array_5__[17] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][8]) + (__x_xpd__[1][4] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][6]));
				__tmp_coord_array_5__[18] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][6]) + (__x_xpd__[1][1] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][3]));
				__tmp_coord_array_5__[19] += ((__x_xpd__[1][0] * __y_xpd__[2][8]) + (__x_xpd__[1][4] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][9]));
				__tmp_coord_array_5__[20] += ((__x_xpd__[1][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][9]) + (__x_xpd__[1][0] * __y_xpd__[2][6]));
				__tmp_coord_array_5__[21] += ((__x_xpd__[1][4] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][9]) + (__x_xpd__[1][0] * __y_xpd__[2][7]));
				__tmp_coord_array_5__[22] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][4]) + (__x_xpd__[1][3] * __y_xpd__[2][1]));
				__tmp_coord_array_5__[23] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][2]));
				__tmp_coord_array_5__[24] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][1]) + (__x_xpd__[1][2] * __y_xpd__[2][0]) + (__x_xpd__[1][0] * __y_xpd__[2][3]));
				__tmp_coord_array_5__[25] += ((__x_xpd__[1][1] * __y_xpd__[2][4]) + (__x_xpd__[1][3] * __y_xpd__[2][3]) + (__x_xpd__[1][2] * __y_xpd__[2][5]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_5__[26] += ((__x_xpd__[1][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][9]) + (__x_xpd__[1][2] * __y_xpd__[3][1]) + (__x_xpd__[1][1] * __y_xpd__[3][0]));
				__tmp_coord_array_5__[27] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][3]) + (__x_xpd__[1][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]) + (__x_xpd__[1][0] * __y_xpd__[3][0]));
				__tmp_coord_array_5__[28] += ((__x_xpd__[1][1] * __y_xpd__[3][3]) + (__x_xpd__[1][4] * __y_xpd__[3][7]) + (__x_xpd__[1][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][4]));
				__tmp_coord_array_5__[29] += ((__x_xpd__[1][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (__x_xpd__[1][0] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][5]));
				__tmp_coord_array_5__[30] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][6]) + (__x_xpd__[1][0] * __y_xpd__[3][9]) + (__x_xpd__[1][2] * __y_xpd__[3][7]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_5__[31] += ((__x_xpd__[1][4] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][2]) + (__x_xpd__[1][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][1]));

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[6] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[7] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[8] += (__x_xpd__[2][2] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[9] += (__x_xpd__[2][3] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[10] += (__x_xpd__[2][4] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[11] += (__x_xpd__[2][5] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[12] += (__x_xpd__[2][6] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[13] += (__x_xpd__[2][7] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[14] += (__x_xpd__[2][8] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[15] += (__x_xpd__[2][9] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[16] += ((__x_xpd__[2][4] * __y_xpd__[1][4]) + (__x_xpd__[2][8] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[17] += ((__x_xpd__[2][6] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][1]) + (__x_xpd__[2][5] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[18] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[1][2]) + (__x_xpd__[2][7] * __y_xpd__[1][1]) + (__x_xpd__[2][3] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[19] += ((__x_xpd__[2][2] * __y_xpd__[1][4]) + (__x_xpd__[2][8] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[20] += ((__x_xpd__[2][6] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][1]));
				__tmp_coord_array_5__[21] += ((__x_xpd__[2][7] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][2]) + (__x_xpd__[2][1] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[22] += ((__x_xpd__[2][1] * __y_xpd__[1][3]) + (__x_xpd__[2][4] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][2]));
				__tmp_coord_array_5__[23] += ((__x_xpd__[2][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][1]));
				__tmp_coord_array_5__[24] += ((__x_xpd__[2][0] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[1][1]) + (__x_xpd__[2][3] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[25] += ((__x_xpd__[2][4] * __y_xpd__[1][1]) + (__x_xpd__[2][5] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][3]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_5__[26] += ((__x_xpd__[2][7] * __y_xpd__[2][5]) + (__x_xpd__[2][6] * __y_xpd__[2][4]) + (__x_xpd__[2][4] * __y_xpd__[2][6]) + (__x_xpd__[2][3] * __y_xpd__[2][8]) + (__x_xpd__[2][8] * __y_xpd__[2][3]) + (__x_xpd__[2][5] * __y_xpd__[2][7]));
				__tmp_coord_array_5__[27] += ((__x_xpd__[2][9] * __y_xpd__[2][4]) + (__x_xpd__[2][8] * __y_xpd__[2][1]) + (__x_xpd__[2][4] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][7]) + (__x_xpd__[2][1] * __y_xpd__[2][8]));
				__tmp_coord_array_5__[28] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][8]) + (__x_xpd__[2][6] * __y_xpd__[2][2]) + (__x_xpd__[2][2] * __y_xpd__[2][6]) + (__x_xpd__[2][5] * __y_xpd__[2][9]) + (__x_xpd__[2][9] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][0]));
				__tmp_coord_array_5__[29] += ((__x_xpd__[2][7] * __y_xpd__[2][0]) + (__x_xpd__[2][3] * __y_xpd__[2][9]) + (__x_xpd__[2][9] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][6]) + (__x_xpd__[2][0] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][1]));
				__tmp_coord_array_5__[30] += ((__x_xpd__[2][0] * __y_xpd__[2][4]) + (__x_xpd__[2][5] * __y_xpd__[2][1]) + (__x_xpd__[2][2] * __y_xpd__[2][3]) + (__x_xpd__[2][3] * __y_xpd__[2][2]) + (__x_xpd__[2][1] * __y_xpd__[2][5]) + (__x_xpd__[2][4] * __y_xpd__[2][0]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_5__[31] += ((__x_xpd__[2][0] * __y_xpd__[3][0]) + (__x_xpd__[2][8] * __y_xpd__[3][8]) + (__x_xpd__[2][4] * __y_xpd__[3][4]) + (__x_xpd__[2][5] * __y_xpd__[3][5]) + (__x_xpd__[2][1] * __y_xpd__[3][1]) + (__x_xpd__[2][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][9]) + (__x_xpd__[2][6] * __y_xpd__[3][6]) + (__x_xpd__[2][2] * __y_xpd__[3][2]));

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[16] += (__x_xpd__[3][0] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[17] += (__x_xpd__[3][1] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[18] += (__x_xpd__[3][2] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[19] += (__x_xpd__[3][3] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[20] += (__x_xpd__[3][4] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[21] += (__x_xpd__[3][5] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[22] += (__x_xpd__[3][6] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[23] += (__x_xpd__[3][7] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[24] += (__x_xpd__[3][8] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[25] += (__x_xpd__[3][9] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[26] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][1]) + (__x_xpd__[3][9] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[27] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][3]) + (__x_xpd__[3][6] * __y_xpd__[1][4]) + (__x_xpd__[3][3] * __y_xpd__[1][2]));
				__tmp_coord_array_5__[28] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][4]) + (__x_xpd__[3][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][1]));
				__tmp_coord_array_5__[29] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[1][2]) + (__x_xpd__[3][5] * __y_xpd__[1][1]) + (__x_xpd__[3][8] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[30] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[1][0]) + (__x_xpd__[3][8] * __y_xpd__[1][3]) + (__x_xpd__[3][6] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][2]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_5__[31] += ((__x_xpd__[3][4] * __y_xpd__[2][4]) + (__x_xpd__[3][6] * __y_xpd__[2][6]) + (__x_xpd__[3][0] * __y_xpd__[2][0]) + (__x_xpd__[3][5] * __y_xpd__[2][5]) + (__x_xpd__[3][8] * __y_xpd__[2][8]) + (__x_xpd__[3][3] * __y_xpd__[2][3]) + (__x_xpd__[3][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][7]) + (__x_xpd__[3][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][9]));

			}

		}
		if (((x.m_gu & 16) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[26] += (__x_xpd__[4][0] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[27] += (__x_xpd__[4][1] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[28] += (__x_xpd__[4][2] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[29] += (__x_xpd__[4][3] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[30] += (__x_xpd__[4][4] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[31] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][1]) + (__x_xpd__[4][4] * __y_xpd__[1][4]) + (__x_xpd__[4][0] * __y_xpd__[1][0]));

			}

		}
		if (((x.m_gu & 32) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[31] += (__x_xpd__[5][0] * __y_xpd__[0][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_5__);
		return __temp_var_1__;
	}
	inline mv add(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_6__[32] ;
		mv_zero(__tmp_coord_array_6__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_6__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_6__[1] += __x_xpd__[1][0];
			__tmp_coord_array_6__[2] += __x_xpd__[1][1];
			__tmp_coord_array_6__[3] += __x_xpd__[1][2];
			__tmp_coord_array_6__[4] += __x_xpd__[1][3];
			__tmp_coord_array_6__[5] += __x_xpd__[1][4];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_6__[6] += __x_xpd__[2][0];
			__tmp_coord_array_6__[7] += __x_xpd__[2][1];
			__tmp_coord_array_6__[8] += __x_xpd__[2][2];
			__tmp_coord_array_6__[9] += __x_xpd__[2][3];
			__tmp_coord_array_6__[10] += __x_xpd__[2][4];
			__tmp_coord_array_6__[11] += __x_xpd__[2][5];
			__tmp_coord_array_6__[12] += __x_xpd__[2][6];
			__tmp_coord_array_6__[13] += __x_xpd__[2][7];
			__tmp_coord_array_6__[14] += __x_xpd__[2][8];
			__tmp_coord_array_6__[15] += __x_xpd__[2][9];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_6__[16] += __x_xpd__[3][0];
			__tmp_coord_array_6__[17] += __x_xpd__[3][1];
			__tmp_coord_array_6__[18] += __x_xpd__[3][2];
			__tmp_coord_array_6__[19] += __x_xpd__[3][3];
			__tmp_coord_array_6__[20] += __x_xpd__[3][4];
			__tmp_coord_array_6__[21] += __x_xpd__[3][5];
			__tmp_coord_array_6__[22] += __x_xpd__[3][6];
			__tmp_coord_array_6__[23] += __x_xpd__[3][7];
			__tmp_coord_array_6__[24] += __x_xpd__[3][8];
			__tmp_coord_array_6__[25] += __x_xpd__[3][9];

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_6__[26] += __x_xpd__[4][0];
			__tmp_coord_array_6__[27] += __x_xpd__[4][1];
			__tmp_coord_array_6__[28] += __x_xpd__[4][2];
			__tmp_coord_array_6__[29] += __x_xpd__[4][3];
			__tmp_coord_array_6__[30] += __x_xpd__[4][4];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_6__[31] += __x_xpd__[5][0];

		}
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_6__[0] += __y_xpd__[0][0];

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_6__[1] += __y_xpd__[1][0];
			__tmp_coord_array_6__[2] += __y_xpd__[1][1];
			__tmp_coord_array_6__[3] += __y_xpd__[1][2];
			__tmp_coord_array_6__[4] += __y_xpd__[1][3];
			__tmp_coord_array_6__[5] += __y_xpd__[1][4];

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_6__[6] += __y_xpd__[2][0];
			__tmp_coord_array_6__[7] += __y_xpd__[2][1];
			__tmp_coord_array_6__[8] += __y_xpd__[2][2];
			__tmp_coord_array_6__[9] += __y_xpd__[2][3];
			__tmp_coord_array_6__[10] += __y_xpd__[2][4];
			__tmp_coord_array_6__[11] += __y_xpd__[2][5];
			__tmp_coord_array_6__[12] += __y_xpd__[2][6];
			__tmp_coord_array_6__[13] += __y_xpd__[2][7];
			__tmp_coord_array_6__[14] += __y_xpd__[2][8];
			__tmp_coord_array_6__[15] += __y_xpd__[2][9];

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_6__[16] += __y_xpd__[3][0];
			__tmp_coord_array_6__[17] += __y_xpd__[3][1];
			__tmp_coord_array_6__[18] += __y_xpd__[3][2];
			__tmp_coord_array_6__[19] += __y_xpd__[3][3];
			__tmp_coord_array_6__[20] += __y_xpd__[3][4];
			__tmp_coord_array_6__[21] += __y_xpd__[3][5];
			__tmp_coord_array_6__[22] += __y_xpd__[3][6];
			__tmp_coord_array_6__[23] += __y_xpd__[3][7];
			__tmp_coord_array_6__[24] += __y_xpd__[3][8];
			__tmp_coord_array_6__[25] += __y_xpd__[3][9];

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_6__[26] += __y_xpd__[4][0];
			__tmp_coord_array_6__[27] += __y_xpd__[4][1];
			__tmp_coord_array_6__[28] += __y_xpd__[4][2];
			__tmp_coord_array_6__[29] += __y_xpd__[4][3];
			__tmp_coord_array_6__[30] += __y_xpd__[4][4];

		}
		if (((y.m_gu & 32) != 0)) {
			__tmp_coord_array_6__[31] += __y_xpd__[5][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_6__);
		return __temp_var_1__;
	}
	inline mv subtract(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_7__[32] ;
		mv_zero(__tmp_coord_array_7__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_7__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_7__[1] += __x_xpd__[1][0];
			__tmp_coord_array_7__[2] += __x_xpd__[1][1];
			__tmp_coord_array_7__[3] += __x_xpd__[1][2];
			__tmp_coord_array_7__[4] += __x_xpd__[1][3];
			__tmp_coord_array_7__[5] += __x_xpd__[1][4];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_7__[6] += __x_xpd__[2][0];
			__tmp_coord_array_7__[7] += __x_xpd__[2][1];
			__tmp_coord_array_7__[8] += __x_xpd__[2][2];
			__tmp_coord_array_7__[9] += __x_xpd__[2][3];
			__tmp_coord_array_7__[10] += __x_xpd__[2][4];
			__tmp_coord_array_7__[11] += __x_xpd__[2][5];
			__tmp_coord_array_7__[12] += __x_xpd__[2][6];
			__tmp_coord_array_7__[13] += __x_xpd__[2][7];
			__tmp_coord_array_7__[14] += __x_xpd__[2][8];
			__tmp_coord_array_7__[15] += __x_xpd__[2][9];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_7__[16] += __x_xpd__[3][0];
			__tmp_coord_array_7__[17] += __x_xpd__[3][1];
			__tmp_coord_array_7__[18] += __x_xpd__[3][2];
			__tmp_coord_array_7__[19] += __x_xpd__[3][3];
			__tmp_coord_array_7__[20] += __x_xpd__[3][4];
			__tmp_coord_array_7__[21] += __x_xpd__[3][5];
			__tmp_coord_array_7__[22] += __x_xpd__[3][6];
			__tmp_coord_array_7__[23] += __x_xpd__[3][7];
			__tmp_coord_array_7__[24] += __x_xpd__[3][8];
			__tmp_coord_array_7__[25] += __x_xpd__[3][9];

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_7__[26] += __x_xpd__[4][0];
			__tmp_coord_array_7__[27] += __x_xpd__[4][1];
			__tmp_coord_array_7__[28] += __x_xpd__[4][2];
			__tmp_coord_array_7__[29] += __x_xpd__[4][3];
			__tmp_coord_array_7__[30] += __x_xpd__[4][4];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_7__[31] += __x_xpd__[5][0];

		}
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_7__[0] += (-1.0f * __y_xpd__[0][0]);

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_7__[1] += (-1.0f * __y_xpd__[1][0]);
			__tmp_coord_array_7__[2] += (-1.0f * __y_xpd__[1][1]);
			__tmp_coord_array_7__[3] += (-1.0f * __y_xpd__[1][2]);
			__tmp_coord_array_7__[4] += (-1.0f * __y_xpd__[1][3]);
			__tmp_coord_array_7__[5] += (-1.0f * __y_xpd__[1][4]);

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_7__[6] += (-1.0f * __y_xpd__[2][0]);
			__tmp_coord_array_7__[7] += (-1.0f * __y_xpd__[2][1]);
			__tmp_coord_array_7__[8] += (-1.0f * __y_xpd__[2][2]);
			__tmp_coord_array_7__[9] += (-1.0f * __y_xpd__[2][3]);
			__tmp_coord_array_7__[10] += (-1.0f * __y_xpd__[2][4]);
			__tmp_coord_array_7__[11] += (-1.0f * __y_xpd__[2][5]);
			__tmp_coord_array_7__[12] += (-1.0f * __y_xpd__[2][6]);
			__tmp_coord_array_7__[13] += (-1.0f * __y_xpd__[2][7]);
			__tmp_coord_array_7__[14] += (-1.0f * __y_xpd__[2][8]);
			__tmp_coord_array_7__[15] += (-1.0f * __y_xpd__[2][9]);

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_7__[16] += (-1.0f * __y_xpd__[3][0]);
			__tmp_coord_array_7__[17] += (-1.0f * __y_xpd__[3][1]);
			__tmp_coord_array_7__[18] += (-1.0f * __y_xpd__[3][2]);
			__tmp_coord_array_7__[19] += (-1.0f * __y_xpd__[3][3]);
			__tmp_coord_array_7__[20] += (-1.0f * __y_xpd__[3][4]);
			__tmp_coord_array_7__[21] += (-1.0f * __y_xpd__[3][5]);
			__tmp_coord_array_7__[22] += (-1.0f * __y_xpd__[3][6]);
			__tmp_coord_array_7__[23] += (-1.0f * __y_xpd__[3][7]);
			__tmp_coord_array_7__[24] += (-1.0f * __y_xpd__[3][8]);
			__tmp_coord_array_7__[25] += (-1.0f * __y_xpd__[3][9]);

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_7__[26] += (-1.0f * __y_xpd__[4][0]);
			__tmp_coord_array_7__[27] += (-1.0f * __y_xpd__[4][1]);
			__tmp_coord_array_7__[28] += (-1.0f * __y_xpd__[4][2]);
			__tmp_coord_array_7__[29] += (-1.0f * __y_xpd__[4][3]);
			__tmp_coord_array_7__[30] += (-1.0f * __y_xpd__[4][4]);

		}
		if (((y.m_gu & 32) != 0)) {
			__tmp_coord_array_7__[31] += (-1.0f * __y_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_7__);
		return __temp_var_1__;
	}
	inline scalar norm_e2(const mv& x) {
		scalar __temp_var_1__;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[1][4] * __x_xpd__[1][4]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][8] * __x_xpd__[2][8]) + (__x_xpd__[2][6] * __x_xpd__[2][6]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][7] * __x_xpd__[2][7]));

		}
		if (((x.m_gu & 8) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[3][8] * __x_xpd__[3][8]) + (__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][7] * __x_xpd__[3][7]) + (__x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][6] * __x_xpd__[3][6]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][3] * __x_xpd__[3][3]));

		}
		if (((x.m_gu & 16) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][3] * __x_xpd__[4][3]) + (__x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][4] * __x_xpd__[4][4]) + (__x_xpd__[4][0] * __x_xpd__[4][0]));

		}
		if (((x.m_gu & 32) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		return __temp_var_1__;
	}
	inline scalar norm_e(const mv& x) {
		scalar e2;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][4] * __x_xpd__[1][4]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += ((__x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][7] * __x_xpd__[2][7]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][8] * __x_xpd__[2][8]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][6] * __x_xpd__[2][6]) + (__x_xpd__[2][1] * __x_xpd__[2][1]));

		}
		if (((x.m_gu & 8) != 0)) {
			e2.m_c[0] += ((__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][6] * __x_xpd__[3][6]) + (__x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][8] * __x_xpd__[3][8]) + (__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][7] * __x_xpd__[3][7]) + (__x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][0] * __x_xpd__[3][0]));

		}
		if (((x.m_gu & 16) != 0)) {
			e2.m_c[0] += ((__x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][0] * __x_xpd__[4][0]) + (__x_xpd__[4][4] * __x_xpd__[4][4]) + (__x_xpd__[4][3] * __x_xpd__[4][3]) + (__x_xpd__[4][1] * __x_xpd__[4][1]));

		}
		if (((x.m_gu & 32) != 0)) {
			e2.m_c[0] += (__x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		return scalar(scalar_scalar, sqrt(e2.m_c[0]));
	}
	inline mv unit_e(const mv& x) {
		scalar e2;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][4] * __x_xpd__[1][4]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += ((__x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][7] * __x_xpd__[2][7]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][6] * __x_xpd__[2][6]) + (__x_xpd__[2][8] * __x_xpd__[2][8]) + (__x_xpd__[2][0] * __x_xpd__[2][0]));

		}
		if (((x.m_gu & 8) != 0)) {
			e2.m_c[0] += ((__x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][8] * __x_xpd__[3][8]) + (__x_xpd__[3][6] * __x_xpd__[3][6]) + (__x_xpd__[3][7] * __x_xpd__[3][7]) + (__x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][3] * __x_xpd__[3][3]));

		}
		if (((x.m_gu & 16) != 0)) {
			e2.m_c[0] += ((__x_xpd__[4][3] * __x_xpd__[4][3]) + (__x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][4] * __x_xpd__[4][4]) + (__x_xpd__[4][0] * __x_xpd__[4][0]) + (__x_xpd__[4][1] * __x_xpd__[4][1]));

		}
		if (((x.m_gu & 32) != 0)) {
			e2.m_c[0] += (__x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		scalar ie;
		ie.m_c[0] = ((char)1 / sqrt(e2.m_c[0]));
		mv __temp_var_1__;
		float __tmp_coord_array_8__[32] ;
		mv_zero(__tmp_coord_array_8__, 32);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_8__[0] += (__x_xpd__[0][0] * ie.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_8__[1] += (__x_xpd__[1][0] * ie.m_c[0]);
			__tmp_coord_array_8__[2] += (__x_xpd__[1][1] * ie.m_c[0]);
			__tmp_coord_array_8__[3] += (__x_xpd__[1][2] * ie.m_c[0]);
			__tmp_coord_array_8__[4] += (__x_xpd__[1][3] * ie.m_c[0]);
			__tmp_coord_array_8__[5] += (__x_xpd__[1][4] * ie.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_8__[6] += (__x_xpd__[2][0] * ie.m_c[0]);
			__tmp_coord_array_8__[7] += (__x_xpd__[2][1] * ie.m_c[0]);
			__tmp_coord_array_8__[8] += (__x_xpd__[2][2] * ie.m_c[0]);
			__tmp_coord_array_8__[9] += (__x_xpd__[2][3] * ie.m_c[0]);
			__tmp_coord_array_8__[10] += (__x_xpd__[2][4] * ie.m_c[0]);
			__tmp_coord_array_8__[11] += (__x_xpd__[2][5] * ie.m_c[0]);
			__tmp_coord_array_8__[12] += (__x_xpd__[2][6] * ie.m_c[0]);
			__tmp_coord_array_8__[13] += (__x_xpd__[2][7] * ie.m_c[0]);
			__tmp_coord_array_8__[14] += (__x_xpd__[2][8] * ie.m_c[0]);
			__tmp_coord_array_8__[15] += (__x_xpd__[2][9] * ie.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_8__[16] += (__x_xpd__[3][0] * ie.m_c[0]);
			__tmp_coord_array_8__[17] += (__x_xpd__[3][1] * ie.m_c[0]);
			__tmp_coord_array_8__[18] += (__x_xpd__[3][2] * ie.m_c[0]);
			__tmp_coord_array_8__[19] += (__x_xpd__[3][3] * ie.m_c[0]);
			__tmp_coord_array_8__[20] += (__x_xpd__[3][4] * ie.m_c[0]);
			__tmp_coord_array_8__[21] += (__x_xpd__[3][5] * ie.m_c[0]);
			__tmp_coord_array_8__[22] += (__x_xpd__[3][6] * ie.m_c[0]);
			__tmp_coord_array_8__[23] += (__x_xpd__[3][7] * ie.m_c[0]);
			__tmp_coord_array_8__[24] += (__x_xpd__[3][8] * ie.m_c[0]);
			__tmp_coord_array_8__[25] += (__x_xpd__[3][9] * ie.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_8__[26] += (__x_xpd__[4][0] * ie.m_c[0]);
			__tmp_coord_array_8__[27] += (__x_xpd__[4][1] * ie.m_c[0]);
			__tmp_coord_array_8__[28] += (__x_xpd__[4][2] * ie.m_c[0]);
			__tmp_coord_array_8__[29] += (__x_xpd__[4][3] * ie.m_c[0]);
			__tmp_coord_array_8__[30] += (__x_xpd__[4][4] * ie.m_c[0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_8__[31] += (__x_xpd__[5][0] * ie.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_8__);
		return __temp_var_1__;
	}
	inline scalar norm_r2(const mv& x) {
		scalar __temp_var_1__;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[1][0] * __x_xpd__[1][4]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (-1.0f * __x_xpd__[1][4] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[2][6] * __x_xpd__[2][0]) + (__x_xpd__[2][1] * __x_xpd__[2][7]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][2] * __x_xpd__[2][8]) + (__x_xpd__[2][0] * __x_xpd__[2][6]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][7] * __x_xpd__[2][1]) + (__x_xpd__[2][8] * __x_xpd__[2][2]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (-1.0f * __x_xpd__[2][9] * __x_xpd__[2][9]));

		}
		if (((x.m_gu & 8) != 0)) {
			__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[3][3] * __x_xpd__[3][3]) + (-1.0f * __x_xpd__[3][5] * __x_xpd__[3][5]) + (-1.0f * __x_xpd__[3][8] * __x_xpd__[3][2]) + (__x_xpd__[3][1] * __x_xpd__[3][7]) + (-1.0f * __x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][7] * __x_xpd__[3][1]) + (-1.0f * __x_xpd__[3][0] * __x_xpd__[3][6]) + (-1.0f * __x_xpd__[3][6] * __x_xpd__[3][0]) + (-1.0f * __x_xpd__[3][2] * __x_xpd__[3][8]) + (__x_xpd__[3][9] * __x_xpd__[3][9]));

		}
		if (((x.m_gu & 16) != 0)) {
			__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[4][2] * __x_xpd__[4][2]) + (-1.0f * __x_xpd__[4][3] * __x_xpd__[4][3]) + (__x_xpd__[4][0] * __x_xpd__[4][4]) + (__x_xpd__[4][4] * __x_xpd__[4][0]) + (-1.0f * __x_xpd__[4][1] * __x_xpd__[4][1]));

		}
		if (((x.m_gu & 32) != 0)) {
			__temp_var_1__.m_c[0] += (-1.0f * __x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		return __temp_var_1__;
	}
	inline scalar norm_r(const mv& x) {
		scalar r2;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][1] * __x_xpd__[1][1]) + (-1.0f * __x_xpd__[1][4] * __x_xpd__[1][0]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (-1.0f * __x_xpd__[1][0] * __x_xpd__[1][4]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += ((__x_xpd__[2][8] * __x_xpd__[2][2]) + (__x_xpd__[2][1] * __x_xpd__[2][7]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][2] * __x_xpd__[2][8]) + (__x_xpd__[2][7] * __x_xpd__[2][1]) + (__x_xpd__[2][6] * __x_xpd__[2][0]) + (__x_xpd__[2][0] * __x_xpd__[2][6]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (-1.0f * __x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][4] * __x_xpd__[2][4]));

		}
		if (((x.m_gu & 8) != 0)) {
			r2.m_c[0] += ((__x_xpd__[3][7] * __x_xpd__[3][1]) + (-1.0f * __x_xpd__[3][0] * __x_xpd__[3][6]) + (-1.0f * __x_xpd__[3][2] * __x_xpd__[3][8]) + (-1.0f * __x_xpd__[3][3] * __x_xpd__[3][3]) + (-1.0f * __x_xpd__[3][8] * __x_xpd__[3][2]) + (-1.0f * __x_xpd__[3][4] * __x_xpd__[3][4]) + (-1.0f * __x_xpd__[3][6] * __x_xpd__[3][0]) + (-1.0f * __x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][1] * __x_xpd__[3][7]) + (__x_xpd__[3][9] * __x_xpd__[3][9]));

		}
		if (((x.m_gu & 16) != 0)) {
			r2.m_c[0] += ((__x_xpd__[4][4] * __x_xpd__[4][0]) + (-1.0f * __x_xpd__[4][1] * __x_xpd__[4][1]) + (-1.0f * __x_xpd__[4][3] * __x_xpd__[4][3]) + (-1.0f * __x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][0] * __x_xpd__[4][4]));

		}
		if (((x.m_gu & 32) != 0)) {
			r2.m_c[0] += (-1.0f * __x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		return scalar(scalar_scalar, ((((r2.m_c[0] < (char)0)) ? (char)-1 : ((((r2.m_c[0] > (char)0)) ? (char)1 : (char)0))) * sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0])))));
	}
	inline mv unit_r(const mv& x) {
		scalar r2;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (-1.0f * __x_xpd__[1][4] * __x_xpd__[1][0]) + (-1.0f * __x_xpd__[1][0] * __x_xpd__[1][4]) + (__x_xpd__[1][2] * __x_xpd__[1][2]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += ((__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][8] * __x_xpd__[2][2]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][2] * __x_xpd__[2][8]) + (-1.0f * __x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][0] * __x_xpd__[2][6]) + (__x_xpd__[2][1] * __x_xpd__[2][7]) + (__x_xpd__[2][7] * __x_xpd__[2][1]) + (__x_xpd__[2][6] * __x_xpd__[2][0]));

		}
		if (((x.m_gu & 8) != 0)) {
			r2.m_c[0] += ((__x_xpd__[3][7] * __x_xpd__[3][1]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][1] * __x_xpd__[3][7]) + (-1.0f * __x_xpd__[3][4] * __x_xpd__[3][4]) + (-1.0f * __x_xpd__[3][0] * __x_xpd__[3][6]) + (-1.0f * __x_xpd__[3][6] * __x_xpd__[3][0]) + (-1.0f * __x_xpd__[3][3] * __x_xpd__[3][3]) + (-1.0f * __x_xpd__[3][8] * __x_xpd__[3][2]) + (-1.0f * __x_xpd__[3][2] * __x_xpd__[3][8]) + (-1.0f * __x_xpd__[3][5] * __x_xpd__[3][5]));

		}
		if (((x.m_gu & 16) != 0)) {
			r2.m_c[0] += ((-1.0f * __x_xpd__[4][3] * __x_xpd__[4][3]) + (-1.0f * __x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][4] * __x_xpd__[4][0]) + (__x_xpd__[4][0] * __x_xpd__[4][4]) + (-1.0f * __x_xpd__[4][1] * __x_xpd__[4][1]));

		}
		if (((x.m_gu & 32) != 0)) {
			r2.m_c[0] += (-1.0f * __x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		scalar ir;
		ir.m_c[0] = ((char)1 / sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0]))));
		mv __temp_var_1__;
		float __tmp_coord_array_9__[32] ;
		mv_zero(__tmp_coord_array_9__, 32);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_9__[0] += (__x_xpd__[0][0] * ir.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_9__[1] += (__x_xpd__[1][0] * ir.m_c[0]);
			__tmp_coord_array_9__[2] += (__x_xpd__[1][1] * ir.m_c[0]);
			__tmp_coord_array_9__[3] += (__x_xpd__[1][2] * ir.m_c[0]);
			__tmp_coord_array_9__[4] += (__x_xpd__[1][3] * ir.m_c[0]);
			__tmp_coord_array_9__[5] += (__x_xpd__[1][4] * ir.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_9__[6] += (__x_xpd__[2][0] * ir.m_c[0]);
			__tmp_coord_array_9__[7] += (__x_xpd__[2][1] * ir.m_c[0]);
			__tmp_coord_array_9__[8] += (__x_xpd__[2][2] * ir.m_c[0]);
			__tmp_coord_array_9__[9] += (__x_xpd__[2][3] * ir.m_c[0]);
			__tmp_coord_array_9__[10] += (__x_xpd__[2][4] * ir.m_c[0]);
			__tmp_coord_array_9__[11] += (__x_xpd__[2][5] * ir.m_c[0]);
			__tmp_coord_array_9__[12] += (__x_xpd__[2][6] * ir.m_c[0]);
			__tmp_coord_array_9__[13] += (__x_xpd__[2][7] * ir.m_c[0]);
			__tmp_coord_array_9__[14] += (__x_xpd__[2][8] * ir.m_c[0]);
			__tmp_coord_array_9__[15] += (__x_xpd__[2][9] * ir.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_9__[16] += (__x_xpd__[3][0] * ir.m_c[0]);
			__tmp_coord_array_9__[17] += (__x_xpd__[3][1] * ir.m_c[0]);
			__tmp_coord_array_9__[18] += (__x_xpd__[3][2] * ir.m_c[0]);
			__tmp_coord_array_9__[19] += (__x_xpd__[3][3] * ir.m_c[0]);
			__tmp_coord_array_9__[20] += (__x_xpd__[3][4] * ir.m_c[0]);
			__tmp_coord_array_9__[21] += (__x_xpd__[3][5] * ir.m_c[0]);
			__tmp_coord_array_9__[22] += (__x_xpd__[3][6] * ir.m_c[0]);
			__tmp_coord_array_9__[23] += (__x_xpd__[3][7] * ir.m_c[0]);
			__tmp_coord_array_9__[24] += (__x_xpd__[3][8] * ir.m_c[0]);
			__tmp_coord_array_9__[25] += (__x_xpd__[3][9] * ir.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_9__[26] += (__x_xpd__[4][0] * ir.m_c[0]);
			__tmp_coord_array_9__[27] += (__x_xpd__[4][1] * ir.m_c[0]);
			__tmp_coord_array_9__[28] += (__x_xpd__[4][2] * ir.m_c[0]);
			__tmp_coord_array_9__[29] += (__x_xpd__[4][3] * ir.m_c[0]);
			__tmp_coord_array_9__[30] += (__x_xpd__[4][4] * ir.m_c[0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_9__[31] += (__x_xpd__[5][0] * ir.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_9__);
		return __temp_var_1__;
	}
	inline mv reverse(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_10__[32] ;
		mv_zero(__tmp_coord_array_10__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_10__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_10__[1] += __x_xpd__[1][0];
			__tmp_coord_array_10__[2] += __x_xpd__[1][1];
			__tmp_coord_array_10__[3] += __x_xpd__[1][2];
			__tmp_coord_array_10__[4] += __x_xpd__[1][3];
			__tmp_coord_array_10__[5] += __x_xpd__[1][4];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_10__[6] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_10__[7] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_10__[8] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_10__[9] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_10__[10] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_10__[11] += (-1.0f * __x_xpd__[2][5]);
			__tmp_coord_array_10__[12] += (-1.0f * __x_xpd__[2][6]);
			__tmp_coord_array_10__[13] += (-1.0f * __x_xpd__[2][7]);
			__tmp_coord_array_10__[14] += (-1.0f * __x_xpd__[2][8]);
			__tmp_coord_array_10__[15] += (-1.0f * __x_xpd__[2][9]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_10__[16] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_10__[17] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_10__[18] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_10__[19] += (-1.0f * __x_xpd__[3][3]);
			__tmp_coord_array_10__[20] += (-1.0f * __x_xpd__[3][4]);
			__tmp_coord_array_10__[21] += (-1.0f * __x_xpd__[3][5]);
			__tmp_coord_array_10__[22] += (-1.0f * __x_xpd__[3][6]);
			__tmp_coord_array_10__[23] += (-1.0f * __x_xpd__[3][7]);
			__tmp_coord_array_10__[24] += (-1.0f * __x_xpd__[3][8]);
			__tmp_coord_array_10__[25] += (-1.0f * __x_xpd__[3][9]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_10__[26] += __x_xpd__[4][0];
			__tmp_coord_array_10__[27] += __x_xpd__[4][1];
			__tmp_coord_array_10__[28] += __x_xpd__[4][2];
			__tmp_coord_array_10__[29] += __x_xpd__[4][3];
			__tmp_coord_array_10__[30] += __x_xpd__[4][4];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_10__[31] += __x_xpd__[5][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_10__);
		return __temp_var_1__;
	}
	inline mv negate(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_11__[32] ;
		mv_zero(__tmp_coord_array_11__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_11__[0] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_11__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_11__[2] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_11__[3] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_11__[4] += (-1.0f * __x_xpd__[1][3]);
			__tmp_coord_array_11__[5] += (-1.0f * __x_xpd__[1][4]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_11__[6] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_11__[7] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_11__[8] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_11__[9] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_11__[10] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_11__[11] += (-1.0f * __x_xpd__[2][5]);
			__tmp_coord_array_11__[12] += (-1.0f * __x_xpd__[2][6]);
			__tmp_coord_array_11__[13] += (-1.0f * __x_xpd__[2][7]);
			__tmp_coord_array_11__[14] += (-1.0f * __x_xpd__[2][8]);
			__tmp_coord_array_11__[15] += (-1.0f * __x_xpd__[2][9]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_11__[16] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_11__[17] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_11__[18] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_11__[19] += (-1.0f * __x_xpd__[3][3]);
			__tmp_coord_array_11__[20] += (-1.0f * __x_xpd__[3][4]);
			__tmp_coord_array_11__[21] += (-1.0f * __x_xpd__[3][5]);
			__tmp_coord_array_11__[22] += (-1.0f * __x_xpd__[3][6]);
			__tmp_coord_array_11__[23] += (-1.0f * __x_xpd__[3][7]);
			__tmp_coord_array_11__[24] += (-1.0f * __x_xpd__[3][8]);
			__tmp_coord_array_11__[25] += (-1.0f * __x_xpd__[3][9]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_11__[26] += (-1.0f * __x_xpd__[4][0]);
			__tmp_coord_array_11__[27] += (-1.0f * __x_xpd__[4][1]);
			__tmp_coord_array_11__[28] += (-1.0f * __x_xpd__[4][2]);
			__tmp_coord_array_11__[29] += (-1.0f * __x_xpd__[4][3]);
			__tmp_coord_array_11__[30] += (-1.0f * __x_xpd__[4][4]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_11__[31] += (-1.0f * __x_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_11__);
		return __temp_var_1__;
	}
	inline mv dual(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_12__[32] ;
		mv_zero(__tmp_coord_array_12__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_12__[31] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_12__[26] += __x_xpd__[1][4];
			__tmp_coord_array_12__[27] += __x_xpd__[1][1];
			__tmp_coord_array_12__[28] += __x_xpd__[1][2];
			__tmp_coord_array_12__[29] += __x_xpd__[1][3];
			__tmp_coord_array_12__[30] += __x_xpd__[1][0];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_12__[16] += __x_xpd__[2][6];
			__tmp_coord_array_12__[17] += __x_xpd__[2][7];
			__tmp_coord_array_12__[18] += __x_xpd__[2][8];
			__tmp_coord_array_12__[19] += __x_xpd__[2][3];
			__tmp_coord_array_12__[20] += __x_xpd__[2][4];
			__tmp_coord_array_12__[21] += __x_xpd__[2][5];
			__tmp_coord_array_12__[22] += __x_xpd__[2][0];
			__tmp_coord_array_12__[23] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_12__[24] += __x_xpd__[2][2];
			__tmp_coord_array_12__[25] += __x_xpd__[2][9];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_12__[6] += (-1.0f * __x_xpd__[3][6]);
			__tmp_coord_array_12__[7] += __x_xpd__[3][7];
			__tmp_coord_array_12__[8] += (-1.0f * __x_xpd__[3][8]);
			__tmp_coord_array_12__[9] += (-1.0f * __x_xpd__[3][3]);
			__tmp_coord_array_12__[10] += (-1.0f * __x_xpd__[3][4]);
			__tmp_coord_array_12__[11] += (-1.0f * __x_xpd__[3][5]);
			__tmp_coord_array_12__[12] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_12__[13] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_12__[14] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_12__[15] += (-1.0f * __x_xpd__[3][9]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_12__[1] += (-1.0f * __x_xpd__[4][4]);
			__tmp_coord_array_12__[2] += (-1.0f * __x_xpd__[4][1]);
			__tmp_coord_array_12__[3] += (-1.0f * __x_xpd__[4][2]);
			__tmp_coord_array_12__[4] += (-1.0f * __x_xpd__[4][3]);
			__tmp_coord_array_12__[5] += (-1.0f * __x_xpd__[4][0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_12__[0] += __x_xpd__[5][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_12__);
		return __temp_var_1__;
	}
	inline mv undual(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_13__[32] ;
		mv_zero(__tmp_coord_array_13__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_13__[31] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_13__[26] += (-1.0f * __x_xpd__[1][4]);
			__tmp_coord_array_13__[27] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_13__[28] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_13__[29] += (-1.0f * __x_xpd__[1][3]);
			__tmp_coord_array_13__[30] += (-1.0f * __x_xpd__[1][0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_13__[16] += (-1.0f * __x_xpd__[2][6]);
			__tmp_coord_array_13__[17] += (-1.0f * __x_xpd__[2][7]);
			__tmp_coord_array_13__[18] += (-1.0f * __x_xpd__[2][8]);
			__tmp_coord_array_13__[19] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_13__[20] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_13__[21] += (-1.0f * __x_xpd__[2][5]);
			__tmp_coord_array_13__[22] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_13__[23] += __x_xpd__[2][1];
			__tmp_coord_array_13__[24] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_13__[25] += (-1.0f * __x_xpd__[2][9]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_13__[6] += __x_xpd__[3][6];
			__tmp_coord_array_13__[7] += (-1.0f * __x_xpd__[3][7]);
			__tmp_coord_array_13__[8] += __x_xpd__[3][8];
			__tmp_coord_array_13__[9] += __x_xpd__[3][3];
			__tmp_coord_array_13__[10] += __x_xpd__[3][4];
			__tmp_coord_array_13__[11] += __x_xpd__[3][5];
			__tmp_coord_array_13__[12] += __x_xpd__[3][0];
			__tmp_coord_array_13__[13] += __x_xpd__[3][1];
			__tmp_coord_array_13__[14] += __x_xpd__[3][2];
			__tmp_coord_array_13__[15] += __x_xpd__[3][9];

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_13__[1] += __x_xpd__[4][4];
			__tmp_coord_array_13__[2] += __x_xpd__[4][1];
			__tmp_coord_array_13__[3] += __x_xpd__[4][2];
			__tmp_coord_array_13__[4] += __x_xpd__[4][3];
			__tmp_coord_array_13__[5] += __x_xpd__[4][0];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_13__[0] += (-1.0f * __x_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_13__);
		return __temp_var_1__;
	}
	inline mv inverse(const mv& x) {
		scalar n;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			n.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			n.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (-1.0f * __x_xpd__[1][0] * __x_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			n.m_c[0] += ((__x_xpd__[2][5] * __x_xpd__[2][5]) + (-1.0f * __x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][0] * __x_xpd__[2][6]) + (__x_xpd__[2][8] * __x_xpd__[2][2]) + (__x_xpd__[2][6] * __x_xpd__[2][0]) + (__x_xpd__[2][2] * __x_xpd__[2][8]) + (__x_xpd__[2][7] * __x_xpd__[2][1]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][1] * __x_xpd__[2][7]) + (__x_xpd__[2][4] * __x_xpd__[2][4]));

		}
		if (((x.m_gu & 8) != 0)) {
			n.m_c[0] += ((__x_xpd__[3][7] * __x_xpd__[3][1]) + (-1.0f * __x_xpd__[3][4] * __x_xpd__[3][4]) + (-1.0f * __x_xpd__[3][2] * __x_xpd__[3][8]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (-1.0f * __x_xpd__[3][0] * __x_xpd__[3][6]) + (-1.0f * __x_xpd__[3][3] * __x_xpd__[3][3]) + (-1.0f * __x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][1] * __x_xpd__[3][7]) + (-1.0f * __x_xpd__[3][8] * __x_xpd__[3][2]) + (-1.0f * __x_xpd__[3][6] * __x_xpd__[3][0]));

		}
		if (((x.m_gu & 16) != 0)) {
			n.m_c[0] += ((-1.0f * __x_xpd__[4][3] * __x_xpd__[4][3]) + (-1.0f * __x_xpd__[4][1] * __x_xpd__[4][1]) + (-1.0f * __x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][0] * __x_xpd__[4][4]) + (__x_xpd__[4][4] * __x_xpd__[4][0]));

		}
		if (((x.m_gu & 32) != 0)) {
			n.m_c[0] += (-1.0f * __x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		scalar in;
		in.m_c[0] = ((char)1 / n.m_c[0]);
		mv __temp_var_1__;
		float __tmp_coord_array_14__[32] ;
		mv_zero(__tmp_coord_array_14__, 32);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_14__[0] += (__x_xpd__[0][0] * in.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_14__[1] += (__x_xpd__[1][0] * in.m_c[0]);
			__tmp_coord_array_14__[2] += (__x_xpd__[1][1] * in.m_c[0]);
			__tmp_coord_array_14__[3] += (__x_xpd__[1][2] * in.m_c[0]);
			__tmp_coord_array_14__[4] += (__x_xpd__[1][3] * in.m_c[0]);
			__tmp_coord_array_14__[5] += (__x_xpd__[1][4] * in.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_14__[6] += (-1.0f * __x_xpd__[2][0] * in.m_c[0]);
			__tmp_coord_array_14__[7] += (-1.0f * __x_xpd__[2][1] * in.m_c[0]);
			__tmp_coord_array_14__[8] += (-1.0f * __x_xpd__[2][2] * in.m_c[0]);
			__tmp_coord_array_14__[9] += (-1.0f * __x_xpd__[2][3] * in.m_c[0]);
			__tmp_coord_array_14__[10] += (-1.0f * __x_xpd__[2][4] * in.m_c[0]);
			__tmp_coord_array_14__[11] += (-1.0f * __x_xpd__[2][5] * in.m_c[0]);
			__tmp_coord_array_14__[12] += (-1.0f * __x_xpd__[2][6] * in.m_c[0]);
			__tmp_coord_array_14__[13] += (-1.0f * __x_xpd__[2][7] * in.m_c[0]);
			__tmp_coord_array_14__[14] += (-1.0f * __x_xpd__[2][8] * in.m_c[0]);
			__tmp_coord_array_14__[15] += (-1.0f * __x_xpd__[2][9] * in.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_14__[16] += (-1.0f * __x_xpd__[3][0] * in.m_c[0]);
			__tmp_coord_array_14__[17] += (-1.0f * __x_xpd__[3][1] * in.m_c[0]);
			__tmp_coord_array_14__[18] += (-1.0f * __x_xpd__[3][2] * in.m_c[0]);
			__tmp_coord_array_14__[19] += (-1.0f * __x_xpd__[3][3] * in.m_c[0]);
			__tmp_coord_array_14__[20] += (-1.0f * __x_xpd__[3][4] * in.m_c[0]);
			__tmp_coord_array_14__[21] += (-1.0f * __x_xpd__[3][5] * in.m_c[0]);
			__tmp_coord_array_14__[22] += (-1.0f * __x_xpd__[3][6] * in.m_c[0]);
			__tmp_coord_array_14__[23] += (-1.0f * __x_xpd__[3][7] * in.m_c[0]);
			__tmp_coord_array_14__[24] += (-1.0f * __x_xpd__[3][8] * in.m_c[0]);
			__tmp_coord_array_14__[25] += (-1.0f * __x_xpd__[3][9] * in.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_14__[26] += (__x_xpd__[4][0] * in.m_c[0]);
			__tmp_coord_array_14__[27] += (__x_xpd__[4][1] * in.m_c[0]);
			__tmp_coord_array_14__[28] += (__x_xpd__[4][2] * in.m_c[0]);
			__tmp_coord_array_14__[29] += (__x_xpd__[4][3] * in.m_c[0]);
			__tmp_coord_array_14__[30] += (__x_xpd__[4][4] * in.m_c[0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_14__[31] += (__x_xpd__[5][0] * in.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_14__);
		return __temp_var_1__;
	}
	inline mv inverseEM(const mv& x) {
		scalar n;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			n.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			n.m_c[0] += ((__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][4] * __x_xpd__[1][4]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][2] * __x_xpd__[1][2]));

		}
		if (((x.m_gu & 4) != 0)) {
			n.m_c[0] += ((__x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][8] * __x_xpd__[2][8]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][6] * __x_xpd__[2][6]) + (__x_xpd__[2][7] * __x_xpd__[2][7]));

		}
		if (((x.m_gu & 8) != 0)) {
			n.m_c[0] += ((__x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][8] * __x_xpd__[3][8]) + (__x_xpd__[3][7] * __x_xpd__[3][7]) + (__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][6] * __x_xpd__[3][6]) + (__x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][1] * __x_xpd__[3][1]));

		}
		if (((x.m_gu & 16) != 0)) {
			n.m_c[0] += ((__x_xpd__[4][4] * __x_xpd__[4][4]) + (__x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][3] * __x_xpd__[4][3]) + (__x_xpd__[4][0] * __x_xpd__[4][0]));

		}
		if (((x.m_gu & 32) != 0)) {
			n.m_c[0] += (__x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		scalar in;
		in.m_c[0] = ((char)1 / n.m_c[0]);
		mv __temp_var_1__;
		float __tmp_coord_array_15__[32] ;
		mv_zero(__tmp_coord_array_15__, 32);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_15__[0] += (__x_xpd__[0][0] * in.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_15__[1] += (__x_xpd__[1][0] * in.m_c[0]);
			__tmp_coord_array_15__[2] += (__x_xpd__[1][1] * in.m_c[0]);
			__tmp_coord_array_15__[3] += (__x_xpd__[1][2] * in.m_c[0]);
			__tmp_coord_array_15__[4] += (__x_xpd__[1][3] * in.m_c[0]);
			__tmp_coord_array_15__[5] += (__x_xpd__[1][4] * in.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_15__[6] += (-1.0f * __x_xpd__[2][0] * in.m_c[0]);
			__tmp_coord_array_15__[7] += (-1.0f * __x_xpd__[2][1] * in.m_c[0]);
			__tmp_coord_array_15__[8] += (-1.0f * __x_xpd__[2][2] * in.m_c[0]);
			__tmp_coord_array_15__[9] += (-1.0f * __x_xpd__[2][3] * in.m_c[0]);
			__tmp_coord_array_15__[10] += (-1.0f * __x_xpd__[2][4] * in.m_c[0]);
			__tmp_coord_array_15__[11] += (-1.0f * __x_xpd__[2][5] * in.m_c[0]);
			__tmp_coord_array_15__[12] += (-1.0f * __x_xpd__[2][6] * in.m_c[0]);
			__tmp_coord_array_15__[13] += (-1.0f * __x_xpd__[2][7] * in.m_c[0]);
			__tmp_coord_array_15__[14] += (-1.0f * __x_xpd__[2][8] * in.m_c[0]);
			__tmp_coord_array_15__[15] += (-1.0f * __x_xpd__[2][9] * in.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_15__[16] += (-1.0f * __x_xpd__[3][0] * in.m_c[0]);
			__tmp_coord_array_15__[17] += (-1.0f * __x_xpd__[3][1] * in.m_c[0]);
			__tmp_coord_array_15__[18] += (-1.0f * __x_xpd__[3][2] * in.m_c[0]);
			__tmp_coord_array_15__[19] += (-1.0f * __x_xpd__[3][3] * in.m_c[0]);
			__tmp_coord_array_15__[20] += (-1.0f * __x_xpd__[3][4] * in.m_c[0]);
			__tmp_coord_array_15__[21] += (-1.0f * __x_xpd__[3][5] * in.m_c[0]);
			__tmp_coord_array_15__[22] += (-1.0f * __x_xpd__[3][6] * in.m_c[0]);
			__tmp_coord_array_15__[23] += (-1.0f * __x_xpd__[3][7] * in.m_c[0]);
			__tmp_coord_array_15__[24] += (-1.0f * __x_xpd__[3][8] * in.m_c[0]);
			__tmp_coord_array_15__[25] += (-1.0f * __x_xpd__[3][9] * in.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_15__[26] += (__x_xpd__[4][0] * in.m_c[0]);
			__tmp_coord_array_15__[27] += (__x_xpd__[4][1] * in.m_c[0]);
			__tmp_coord_array_15__[28] += (__x_xpd__[4][2] * in.m_c[0]);
			__tmp_coord_array_15__[29] += (__x_xpd__[4][3] * in.m_c[0]);
			__tmp_coord_array_15__[30] += (__x_xpd__[4][4] * in.m_c[0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_15__[31] += (__x_xpd__[5][0] * in.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_15__);
		return __temp_var_1__;
	}
	inline mv apply_om(const om& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_16__[32] ;
		mv_zero(__tmp_coord_array_16__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_16__[1] += ((x.m_c[2] * __y_xpd__[1][2]) + (x.m_c[4] * __y_xpd__[1][4]) + (x.m_c[1] * __y_xpd__[1][1]) + (x.m_c[0] * __y_xpd__[1][0]) + (x.m_c[3] * __y_xpd__[1][3]));
			__tmp_coord_array_16__[2] += ((x.m_c[5] * __y_xpd__[1][0]) + (x.m_c[7] * __y_xpd__[1][2]) + (x.m_c[8] * __y_xpd__[1][3]) + (x.m_c[9] * __y_xpd__[1][4]) + (x.m_c[6] * __y_xpd__[1][1]));
			__tmp_coord_array_16__[3] += ((x.m_c[10] * __y_xpd__[1][0]) + (x.m_c[12] * __y_xpd__[1][2]) + (x.m_c[11] * __y_xpd__[1][1]) + (x.m_c[13] * __y_xpd__[1][3]) + (x.m_c[14] * __y_xpd__[1][4]));
			__tmp_coord_array_16__[4] += ((x.m_c[18] * __y_xpd__[1][3]) + (x.m_c[17] * __y_xpd__[1][2]) + (x.m_c[19] * __y_xpd__[1][4]) + (x.m_c[15] * __y_xpd__[1][0]) + (x.m_c[16] * __y_xpd__[1][1]));
			__tmp_coord_array_16__[5] += ((x.m_c[23] * __y_xpd__[1][3]) + (x.m_c[24] * __y_xpd__[1][4]) + (x.m_c[21] * __y_xpd__[1][1]) + (x.m_c[20] * __y_xpd__[1][0]) + (x.m_c[22] * __y_xpd__[1][2]));

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_16__[6] += ((x.m_c[30] * __y_xpd__[2][5]) + (x.m_c[26] * __y_xpd__[2][1]) + (x.m_c[27] * __y_xpd__[2][2]) + (x.m_c[25] * __y_xpd__[2][0]) + (x.m_c[32] * __y_xpd__[2][7]) + (x.m_c[33] * __y_xpd__[2][8]) + (x.m_c[28] * __y_xpd__[2][3]) + (x.m_c[34] * __y_xpd__[2][9]) + (x.m_c[29] * __y_xpd__[2][4]) + (x.m_c[31] * __y_xpd__[2][6]));
			__tmp_coord_array_16__[7] += ((x.m_c[43] * __y_xpd__[2][8]) + (x.m_c[44] * __y_xpd__[2][9]) + (x.m_c[37] * __y_xpd__[2][2]) + (x.m_c[35] * __y_xpd__[2][0]) + (x.m_c[38] * __y_xpd__[2][3]) + (x.m_c[39] * __y_xpd__[2][4]) + (x.m_c[40] * __y_xpd__[2][5]) + (x.m_c[36] * __y_xpd__[2][1]) + (x.m_c[41] * __y_xpd__[2][6]) + (x.m_c[42] * __y_xpd__[2][7]));
			__tmp_coord_array_16__[8] += ((x.m_c[52] * __y_xpd__[2][7]) + (x.m_c[49] * __y_xpd__[2][4]) + (x.m_c[50] * __y_xpd__[2][5]) + (x.m_c[48] * __y_xpd__[2][3]) + (x.m_c[51] * __y_xpd__[2][6]) + (x.m_c[47] * __y_xpd__[2][2]) + (x.m_c[46] * __y_xpd__[2][1]) + (x.m_c[53] * __y_xpd__[2][8]) + (x.m_c[45] * __y_xpd__[2][0]) + (x.m_c[54] * __y_xpd__[2][9]));
			__tmp_coord_array_16__[9] += ((x.m_c[58] * __y_xpd__[2][3]) + (x.m_c[59] * __y_xpd__[2][4]) + (x.m_c[60] * __y_xpd__[2][5]) + (x.m_c[64] * __y_xpd__[2][9]) + (x.m_c[56] * __y_xpd__[2][1]) + (x.m_c[57] * __y_xpd__[2][2]) + (x.m_c[61] * __y_xpd__[2][6]) + (x.m_c[62] * __y_xpd__[2][7]) + (x.m_c[55] * __y_xpd__[2][0]) + (x.m_c[63] * __y_xpd__[2][8]));
			__tmp_coord_array_16__[10] += ((x.m_c[69] * __y_xpd__[2][4]) + (x.m_c[65] * __y_xpd__[2][0]) + (x.m_c[74] * __y_xpd__[2][9]) + (x.m_c[70] * __y_xpd__[2][5]) + (x.m_c[73] * __y_xpd__[2][8]) + (x.m_c[68] * __y_xpd__[2][3]) + (x.m_c[71] * __y_xpd__[2][6]) + (x.m_c[72] * __y_xpd__[2][7]) + (x.m_c[66] * __y_xpd__[2][1]) + (x.m_c[67] * __y_xpd__[2][2]));
			__tmp_coord_array_16__[11] += ((x.m_c[83] * __y_xpd__[2][8]) + (x.m_c[76] * __y_xpd__[2][1]) + (x.m_c[79] * __y_xpd__[2][4]) + (x.m_c[77] * __y_xpd__[2][2]) + (x.m_c[84] * __y_xpd__[2][9]) + (x.m_c[81] * __y_xpd__[2][6]) + (x.m_c[78] * __y_xpd__[2][3]) + (x.m_c[80] * __y_xpd__[2][5]) + (x.m_c[75] * __y_xpd__[2][0]) + (x.m_c[82] * __y_xpd__[2][7]));
			__tmp_coord_array_16__[12] += ((x.m_c[85] * __y_xpd__[2][0]) + (x.m_c[92] * __y_xpd__[2][7]) + (x.m_c[89] * __y_xpd__[2][4]) + (x.m_c[91] * __y_xpd__[2][6]) + (x.m_c[90] * __y_xpd__[2][5]) + (x.m_c[93] * __y_xpd__[2][8]) + (x.m_c[87] * __y_xpd__[2][2]) + (x.m_c[88] * __y_xpd__[2][3]) + (x.m_c[94] * __y_xpd__[2][9]) + (x.m_c[86] * __y_xpd__[2][1]));
			__tmp_coord_array_16__[13] += ((x.m_c[99] * __y_xpd__[2][4]) + (x.m_c[97] * __y_xpd__[2][2]) + (x.m_c[103] * __y_xpd__[2][8]) + (x.m_c[102] * __y_xpd__[2][7]) + (x.m_c[104] * __y_xpd__[2][9]) + (x.m_c[101] * __y_xpd__[2][6]) + (x.m_c[98] * __y_xpd__[2][3]) + (x.m_c[95] * __y_xpd__[2][0]) + (x.m_c[100] * __y_xpd__[2][5]) + (x.m_c[96] * __y_xpd__[2][1]));
			__tmp_coord_array_16__[14] += ((x.m_c[105] * __y_xpd__[2][0]) + (x.m_c[111] * __y_xpd__[2][6]) + (x.m_c[112] * __y_xpd__[2][7]) + (x.m_c[113] * __y_xpd__[2][8]) + (x.m_c[110] * __y_xpd__[2][5]) + (x.m_c[108] * __y_xpd__[2][3]) + (x.m_c[107] * __y_xpd__[2][2]) + (x.m_c[109] * __y_xpd__[2][4]) + (x.m_c[106] * __y_xpd__[2][1]) + (x.m_c[114] * __y_xpd__[2][9]));
			__tmp_coord_array_16__[15] += ((x.m_c[122] * __y_xpd__[2][7]) + (x.m_c[118] * __y_xpd__[2][3]) + (x.m_c[121] * __y_xpd__[2][6]) + (x.m_c[123] * __y_xpd__[2][8]) + (x.m_c[116] * __y_xpd__[2][1]) + (x.m_c[124] * __y_xpd__[2][9]) + (x.m_c[119] * __y_xpd__[2][4]) + (x.m_c[120] * __y_xpd__[2][5]) + (x.m_c[117] * __y_xpd__[2][2]) + (x.m_c[115] * __y_xpd__[2][0]));

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_16__[16] += ((x.m_c[132] * __y_xpd__[3][7]) + (x.m_c[131] * __y_xpd__[3][6]) + (x.m_c[134] * __y_xpd__[3][9]) + (x.m_c[133] * __y_xpd__[3][8]) + (x.m_c[128] * __y_xpd__[3][3]) + (x.m_c[129] * __y_xpd__[3][4]) + (x.m_c[130] * __y_xpd__[3][5]) + (x.m_c[125] * __y_xpd__[3][0]) + (x.m_c[126] * __y_xpd__[3][1]) + (x.m_c[127] * __y_xpd__[3][2]));
			__tmp_coord_array_16__[17] += ((x.m_c[136] * __y_xpd__[3][1]) + (x.m_c[144] * __y_xpd__[3][9]) + (x.m_c[138] * __y_xpd__[3][3]) + (x.m_c[139] * __y_xpd__[3][4]) + (x.m_c[137] * __y_xpd__[3][2]) + (x.m_c[141] * __y_xpd__[3][6]) + (x.m_c[135] * __y_xpd__[3][0]) + (x.m_c[143] * __y_xpd__[3][8]) + (x.m_c[142] * __y_xpd__[3][7]) + (x.m_c[140] * __y_xpd__[3][5]));
			__tmp_coord_array_16__[18] += ((x.m_c[147] * __y_xpd__[3][2]) + (x.m_c[150] * __y_xpd__[3][5]) + (x.m_c[148] * __y_xpd__[3][3]) + (x.m_c[145] * __y_xpd__[3][0]) + (x.m_c[151] * __y_xpd__[3][6]) + (x.m_c[149] * __y_xpd__[3][4]) + (x.m_c[146] * __y_xpd__[3][1]) + (x.m_c[153] * __y_xpd__[3][8]) + (x.m_c[152] * __y_xpd__[3][7]) + (x.m_c[154] * __y_xpd__[3][9]));
			__tmp_coord_array_16__[19] += ((x.m_c[163] * __y_xpd__[3][8]) + (x.m_c[156] * __y_xpd__[3][1]) + (x.m_c[157] * __y_xpd__[3][2]) + (x.m_c[159] * __y_xpd__[3][4]) + (x.m_c[160] * __y_xpd__[3][5]) + (x.m_c[155] * __y_xpd__[3][0]) + (x.m_c[162] * __y_xpd__[3][7]) + (x.m_c[164] * __y_xpd__[3][9]) + (x.m_c[161] * __y_xpd__[3][6]) + (x.m_c[158] * __y_xpd__[3][3]));
			__tmp_coord_array_16__[20] += ((x.m_c[165] * __y_xpd__[3][0]) + (x.m_c[174] * __y_xpd__[3][9]) + (x.m_c[172] * __y_xpd__[3][7]) + (x.m_c[173] * __y_xpd__[3][8]) + (x.m_c[170] * __y_xpd__[3][5]) + (x.m_c[169] * __y_xpd__[3][4]) + (x.m_c[167] * __y_xpd__[3][2]) + (x.m_c[166] * __y_xpd__[3][1]) + (x.m_c[168] * __y_xpd__[3][3]) + (x.m_c[171] * __y_xpd__[3][6]));
			__tmp_coord_array_16__[21] += ((x.m_c[176] * __y_xpd__[3][1]) + (x.m_c[183] * __y_xpd__[3][8]) + (x.m_c[182] * __y_xpd__[3][7]) + (x.m_c[175] * __y_xpd__[3][0]) + (x.m_c[177] * __y_xpd__[3][2]) + (x.m_c[178] * __y_xpd__[3][3]) + (x.m_c[184] * __y_xpd__[3][9]) + (x.m_c[181] * __y_xpd__[3][6]) + (x.m_c[179] * __y_xpd__[3][4]) + (x.m_c[180] * __y_xpd__[3][5]));
			__tmp_coord_array_16__[22] += ((x.m_c[187] * __y_xpd__[3][2]) + (x.m_c[188] * __y_xpd__[3][3]) + (x.m_c[189] * __y_xpd__[3][4]) + (x.m_c[185] * __y_xpd__[3][0]) + (x.m_c[190] * __y_xpd__[3][5]) + (x.m_c[194] * __y_xpd__[3][9]) + (x.m_c[192] * __y_xpd__[3][7]) + (x.m_c[191] * __y_xpd__[3][6]) + (x.m_c[186] * __y_xpd__[3][1]) + (x.m_c[193] * __y_xpd__[3][8]));
			__tmp_coord_array_16__[23] += ((x.m_c[197] * __y_xpd__[3][2]) + (x.m_c[198] * __y_xpd__[3][3]) + (x.m_c[200] * __y_xpd__[3][5]) + (x.m_c[195] * __y_xpd__[3][0]) + (x.m_c[201] * __y_xpd__[3][6]) + (x.m_c[202] * __y_xpd__[3][7]) + (x.m_c[204] * __y_xpd__[3][9]) + (x.m_c[203] * __y_xpd__[3][8]) + (x.m_c[199] * __y_xpd__[3][4]) + (x.m_c[196] * __y_xpd__[3][1]));
			__tmp_coord_array_16__[24] += ((x.m_c[213] * __y_xpd__[3][8]) + (x.m_c[207] * __y_xpd__[3][2]) + (x.m_c[208] * __y_xpd__[3][3]) + (x.m_c[205] * __y_xpd__[3][0]) + (x.m_c[206] * __y_xpd__[3][1]) + (x.m_c[209] * __y_xpd__[3][4]) + (x.m_c[214] * __y_xpd__[3][9]) + (x.m_c[212] * __y_xpd__[3][7]) + (x.m_c[210] * __y_xpd__[3][5]) + (x.m_c[211] * __y_xpd__[3][6]));
			__tmp_coord_array_16__[25] += ((x.m_c[222] * __y_xpd__[3][7]) + (x.m_c[218] * __y_xpd__[3][3]) + (x.m_c[223] * __y_xpd__[3][8]) + (x.m_c[220] * __y_xpd__[3][5]) + (x.m_c[221] * __y_xpd__[3][6]) + (x.m_c[224] * __y_xpd__[3][9]) + (x.m_c[215] * __y_xpd__[3][0]) + (x.m_c[217] * __y_xpd__[3][2]) + (x.m_c[216] * __y_xpd__[3][1]) + (x.m_c[219] * __y_xpd__[3][4]));

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_16__[26] += ((x.m_c[229] * __y_xpd__[4][4]) + (x.m_c[225] * __y_xpd__[4][0]) + (-1.0f * x.m_c[227] * __y_xpd__[4][2]) + (x.m_c[226] * __y_xpd__[4][1]) + (x.m_c[228] * __y_xpd__[4][3]));
			__tmp_coord_array_16__[27] += ((x.m_c[231] * __y_xpd__[4][1]) + (x.m_c[234] * __y_xpd__[4][4]) + (-1.0f * x.m_c[232] * __y_xpd__[4][2]) + (x.m_c[233] * __y_xpd__[4][3]) + (x.m_c[230] * __y_xpd__[4][0]));
			__tmp_coord_array_16__[28] += ((-1.0f * x.m_c[239] * __y_xpd__[4][4]) + (-1.0f * x.m_c[235] * __y_xpd__[4][0]) + (-1.0f * x.m_c[238] * __y_xpd__[4][3]) + (-1.0f * x.m_c[236] * __y_xpd__[4][1]) + (x.m_c[237] * __y_xpd__[4][2]));
			__tmp_coord_array_16__[29] += ((x.m_c[244] * __y_xpd__[4][4]) + (x.m_c[241] * __y_xpd__[4][1]) + (x.m_c[243] * __y_xpd__[4][3]) + (-1.0f * x.m_c[242] * __y_xpd__[4][2]) + (x.m_c[240] * __y_xpd__[4][0]));
			__tmp_coord_array_16__[30] += ((x.m_c[246] * __y_xpd__[4][1]) + (x.m_c[248] * __y_xpd__[4][3]) + (x.m_c[245] * __y_xpd__[4][0]) + (-1.0f * x.m_c[247] * __y_xpd__[4][2]) + (x.m_c[249] * __y_xpd__[4][4]));

		}
		if (((y.m_gu & 32) != 0)) {
			__tmp_coord_array_16__[31] += (x.m_c[250] * __y_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_16__);
		return __temp_var_1__;
	}
	inline mv gradeInvolution(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_17__[32] ;
		mv_zero(__tmp_coord_array_17__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_17__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_17__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_17__[2] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_17__[3] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_17__[4] += (-1.0f * __x_xpd__[1][3]);
			__tmp_coord_array_17__[5] += (-1.0f * __x_xpd__[1][4]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_17__[6] += __x_xpd__[2][0];
			__tmp_coord_array_17__[7] += __x_xpd__[2][1];
			__tmp_coord_array_17__[8] += __x_xpd__[2][2];
			__tmp_coord_array_17__[9] += __x_xpd__[2][3];
			__tmp_coord_array_17__[10] += __x_xpd__[2][4];
			__tmp_coord_array_17__[11] += __x_xpd__[2][5];
			__tmp_coord_array_17__[12] += __x_xpd__[2][6];
			__tmp_coord_array_17__[13] += __x_xpd__[2][7];
			__tmp_coord_array_17__[14] += __x_xpd__[2][8];
			__tmp_coord_array_17__[15] += __x_xpd__[2][9];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_17__[16] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_17__[17] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_17__[18] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_17__[19] += (-1.0f * __x_xpd__[3][3]);
			__tmp_coord_array_17__[20] += (-1.0f * __x_xpd__[3][4]);
			__tmp_coord_array_17__[21] += (-1.0f * __x_xpd__[3][5]);
			__tmp_coord_array_17__[22] += (-1.0f * __x_xpd__[3][6]);
			__tmp_coord_array_17__[23] += (-1.0f * __x_xpd__[3][7]);
			__tmp_coord_array_17__[24] += (-1.0f * __x_xpd__[3][8]);
			__tmp_coord_array_17__[25] += (-1.0f * __x_xpd__[3][9]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_17__[26] += __x_xpd__[4][0];
			__tmp_coord_array_17__[27] += __x_xpd__[4][1];
			__tmp_coord_array_17__[28] += __x_xpd__[4][2];
			__tmp_coord_array_17__[29] += __x_xpd__[4][3];
			__tmp_coord_array_17__[30] += __x_xpd__[4][4];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_17__[31] += (-1.0f * __x_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_17__);
		return __temp_var_1__;
	}
	inline normalizedPoint c3gaPoint(const vectorE3GA& l) {
		return normalizedPoint(normalizedPoint_e1_e2_e3_ni_nof1_0, l.m_c[0], l.m_c[1], l.m_c[2], ((0.5 * l.m_c[1] * l.m_c[1]) + (0.5 * l.m_c[2] * l.m_c[2]) + (0.5 * l.m_c[0] * l.m_c[0])));
	}
	namespace __G2_GENERATED__ {
		inline void set(om& __x__, const point& __image_of_no__, const point& __image_of_e1__, const point& __image_of_e2__, const point& __image_of_e3__, const point& __image_of_ni__) {
			__x__.m_c[0] = __image_of_no__.m_c[0];
			__x__.m_c[5] = __image_of_no__.m_c[1];
			__x__.m_c[10] = __image_of_no__.m_c[2];
			__x__.m_c[15] = __image_of_no__.m_c[3];
			__x__.m_c[20] = __image_of_no__.m_c[4];
			__x__.m_c[1] = __image_of_e1__.m_c[0];
			__x__.m_c[6] = __image_of_e1__.m_c[1];
			__x__.m_c[11] = __image_of_e1__.m_c[2];
			__x__.m_c[16] = __image_of_e1__.m_c[3];
			__x__.m_c[21] = __image_of_e1__.m_c[4];
			__x__.m_c[2] = __image_of_e2__.m_c[0];
			__x__.m_c[7] = __image_of_e2__.m_c[1];
			__x__.m_c[12] = __image_of_e2__.m_c[2];
			__x__.m_c[17] = __image_of_e2__.m_c[3];
			__x__.m_c[22] = __image_of_e2__.m_c[4];
			__x__.m_c[3] = __image_of_e3__.m_c[0];
			__x__.m_c[8] = __image_of_e3__.m_c[1];
			__x__.m_c[13] = __image_of_e3__.m_c[2];
			__x__.m_c[18] = __image_of_e3__.m_c[3];
			__x__.m_c[23] = __image_of_e3__.m_c[4];
			__x__.m_c[4] = __image_of_ni__.m_c[0];
			__x__.m_c[9] = __image_of_ni__.m_c[1];
			__x__.m_c[14] = __image_of_ni__.m_c[2];
			__x__.m_c[19] = __image_of_ni__.m_c[3];
			__x__.m_c[24] = __image_of_ni__.m_c[4];
			__x__.m_c[25] = ((-1.0f * __x__.m_c[1] * __x__.m_c[5]) + (__x__.m_c[6] * __x__.m_c[0]));
			__x__.m_c[35] = ((-1.0f * __x__.m_c[1] * __x__.m_c[10]) + (__x__.m_c[11] * __x__.m_c[0]));
			__x__.m_c[45] = ((__x__.m_c[16] * __x__.m_c[0]) + (-1.0f * __x__.m_c[1] * __x__.m_c[15]));
			__x__.m_c[55] = ((-1.0f * __x__.m_c[6] * __x__.m_c[10]) + (__x__.m_c[11] * __x__.m_c[5]));
			__x__.m_c[65] = ((-1.0f * __x__.m_c[11] * __x__.m_c[15]) + (__x__.m_c[16] * __x__.m_c[10]));
			__x__.m_c[75] = ((-1.0f * __x__.m_c[16] * __x__.m_c[5]) + (__x__.m_c[6] * __x__.m_c[15]));
			__x__.m_c[85] = ((__x__.m_c[21] * __x__.m_c[5]) + (-1.0f * __x__.m_c[6] * __x__.m_c[20]));
			__x__.m_c[95] = ((-1.0f * __x__.m_c[11] * __x__.m_c[20]) + (__x__.m_c[21] * __x__.m_c[10]));
			__x__.m_c[105] = ((-1.0f * __x__.m_c[16] * __x__.m_c[20]) + (__x__.m_c[21] * __x__.m_c[15]));
			__x__.m_c[115] = ((-1.0f * __x__.m_c[1] * __x__.m_c[20]) + (__x__.m_c[21] * __x__.m_c[0]));
			__x__.m_c[26] = ((-1.0f * __x__.m_c[2] * __x__.m_c[5]) + (__x__.m_c[7] * __x__.m_c[0]));
			__x__.m_c[36] = ((__x__.m_c[12] * __x__.m_c[0]) + (-1.0f * __x__.m_c[2] * __x__.m_c[10]));
			__x__.m_c[46] = ((__x__.m_c[17] * __x__.m_c[0]) + (-1.0f * __x__.m_c[2] * __x__.m_c[15]));
			__x__.m_c[56] = ((-1.0f * __x__.m_c[7] * __x__.m_c[10]) + (__x__.m_c[12] * __x__.m_c[5]));
			__x__.m_c[66] = ((__x__.m_c[17] * __x__.m_c[10]) + (-1.0f * __x__.m_c[12] * __x__.m_c[15]));
			__x__.m_c[76] = ((__x__.m_c[7] * __x__.m_c[15]) + (-1.0f * __x__.m_c[17] * __x__.m_c[5]));
			__x__.m_c[86] = ((-1.0f * __x__.m_c[7] * __x__.m_c[20]) + (__x__.m_c[22] * __x__.m_c[5]));
			__x__.m_c[96] = ((__x__.m_c[22] * __x__.m_c[10]) + (-1.0f * __x__.m_c[12] * __x__.m_c[20]));
			__x__.m_c[106] = ((__x__.m_c[22] * __x__.m_c[15]) + (-1.0f * __x__.m_c[17] * __x__.m_c[20]));
			__x__.m_c[116] = ((-1.0f * __x__.m_c[2] * __x__.m_c[20]) + (__x__.m_c[22] * __x__.m_c[0]));
			__x__.m_c[27] = ((-1.0f * __x__.m_c[3] * __x__.m_c[5]) + (__x__.m_c[8] * __x__.m_c[0]));
			__x__.m_c[37] = ((-1.0f * __x__.m_c[3] * __x__.m_c[10]) + (__x__.m_c[13] * __x__.m_c[0]));
			__x__.m_c[47] = ((-1.0f * __x__.m_c[3] * __x__.m_c[15]) + (__x__.m_c[18] * __x__.m_c[0]));
			__x__.m_c[57] = ((__x__.m_c[13] * __x__.m_c[5]) + (-1.0f * __x__.m_c[8] * __x__.m_c[10]));
			__x__.m_c[67] = ((__x__.m_c[18] * __x__.m_c[10]) + (-1.0f * __x__.m_c[13] * __x__.m_c[15]));
			__x__.m_c[77] = ((-1.0f * __x__.m_c[18] * __x__.m_c[5]) + (__x__.m_c[8] * __x__.m_c[15]));
			__x__.m_c[87] = ((-1.0f * __x__.m_c[8] * __x__.m_c[20]) + (__x__.m_c[23] * __x__.m_c[5]));
			__x__.m_c[97] = ((__x__.m_c[23] * __x__.m_c[10]) + (-1.0f * __x__.m_c[13] * __x__.m_c[20]));
			__x__.m_c[107] = ((__x__.m_c[23] * __x__.m_c[15]) + (-1.0f * __x__.m_c[18] * __x__.m_c[20]));
			__x__.m_c[117] = ((__x__.m_c[23] * __x__.m_c[0]) + (-1.0f * __x__.m_c[3] * __x__.m_c[20]));
			__x__.m_c[28] = ((__x__.m_c[7] * __x__.m_c[1]) + (-1.0f * __x__.m_c[2] * __x__.m_c[6]));
			__x__.m_c[38] = ((__x__.m_c[12] * __x__.m_c[1]) + (-1.0f * __x__.m_c[2] * __x__.m_c[11]));
			__x__.m_c[48] = ((-1.0f * __x__.m_c[2] * __x__.m_c[16]) + (__x__.m_c[17] * __x__.m_c[1]));
			__x__.m_c[58] = ((-1.0f * __x__.m_c[7] * __x__.m_c[11]) + (__x__.m_c[12] * __x__.m_c[6]));
			__x__.m_c[68] = ((__x__.m_c[17] * __x__.m_c[11]) + (-1.0f * __x__.m_c[12] * __x__.m_c[16]));
			__x__.m_c[78] = ((__x__.m_c[7] * __x__.m_c[16]) + (-1.0f * __x__.m_c[17] * __x__.m_c[6]));
			__x__.m_c[88] = ((__x__.m_c[22] * __x__.m_c[6]) + (-1.0f * __x__.m_c[7] * __x__.m_c[21]));
			__x__.m_c[98] = ((__x__.m_c[22] * __x__.m_c[11]) + (-1.0f * __x__.m_c[12] * __x__.m_c[21]));
			__x__.m_c[108] = ((-1.0f * __x__.m_c[17] * __x__.m_c[21]) + (__x__.m_c[22] * __x__.m_c[16]));
			__x__.m_c[118] = ((__x__.m_c[22] * __x__.m_c[1]) + (-1.0f * __x__.m_c[2] * __x__.m_c[21]));
			__x__.m_c[29] = ((-1.0f * __x__.m_c[3] * __x__.m_c[7]) + (__x__.m_c[8] * __x__.m_c[2]));
			__x__.m_c[39] = ((__x__.m_c[13] * __x__.m_c[2]) + (-1.0f * __x__.m_c[3] * __x__.m_c[12]));
			__x__.m_c[49] = ((__x__.m_c[18] * __x__.m_c[2]) + (-1.0f * __x__.m_c[3] * __x__.m_c[17]));
			__x__.m_c[59] = ((-1.0f * __x__.m_c[8] * __x__.m_c[12]) + (__x__.m_c[13] * __x__.m_c[7]));
			__x__.m_c[69] = ((-1.0f * __x__.m_c[13] * __x__.m_c[17]) + (__x__.m_c[18] * __x__.m_c[12]));
			__x__.m_c[79] = ((-1.0f * __x__.m_c[18] * __x__.m_c[7]) + (__x__.m_c[8] * __x__.m_c[17]));
			__x__.m_c[89] = ((__x__.m_c[23] * __x__.m_c[7]) + (-1.0f * __x__.m_c[8] * __x__.m_c[22]));
			__x__.m_c[99] = ((__x__.m_c[23] * __x__.m_c[12]) + (-1.0f * __x__.m_c[13] * __x__.m_c[22]));
			__x__.m_c[109] = ((-1.0f * __x__.m_c[18] * __x__.m_c[22]) + (__x__.m_c[23] * __x__.m_c[17]));
			__x__.m_c[119] = ((-1.0f * __x__.m_c[3] * __x__.m_c[22]) + (__x__.m_c[23] * __x__.m_c[2]));
			__x__.m_c[30] = ((__x__.m_c[3] * __x__.m_c[6]) + (-1.0f * __x__.m_c[8] * __x__.m_c[1]));
			__x__.m_c[40] = ((__x__.m_c[3] * __x__.m_c[11]) + (-1.0f * __x__.m_c[13] * __x__.m_c[1]));
			__x__.m_c[50] = ((__x__.m_c[3] * __x__.m_c[16]) + (-1.0f * __x__.m_c[18] * __x__.m_c[1]));
			__x__.m_c[60] = ((-1.0f * __x__.m_c[13] * __x__.m_c[6]) + (__x__.m_c[8] * __x__.m_c[11]));
			__x__.m_c[70] = ((__x__.m_c[13] * __x__.m_c[16]) + (-1.0f * __x__.m_c[18] * __x__.m_c[11]));
			__x__.m_c[80] = ((-1.0f * __x__.m_c[8] * __x__.m_c[16]) + (__x__.m_c[18] * __x__.m_c[6]));
			__x__.m_c[90] = ((-1.0f * __x__.m_c[23] * __x__.m_c[6]) + (__x__.m_c[8] * __x__.m_c[21]));
			__x__.m_c[100] = ((-1.0f * __x__.m_c[23] * __x__.m_c[11]) + (__x__.m_c[13] * __x__.m_c[21]));
			__x__.m_c[110] = ((-1.0f * __x__.m_c[23] * __x__.m_c[16]) + (__x__.m_c[18] * __x__.m_c[21]));
			__x__.m_c[120] = ((-1.0f * __x__.m_c[23] * __x__.m_c[1]) + (__x__.m_c[3] * __x__.m_c[21]));
			__x__.m_c[31] = ((__x__.m_c[9] * __x__.m_c[1]) + (-1.0f * __x__.m_c[4] * __x__.m_c[6]));
			__x__.m_c[41] = ((-1.0f * __x__.m_c[4] * __x__.m_c[11]) + (__x__.m_c[14] * __x__.m_c[1]));
			__x__.m_c[51] = ((-1.0f * __x__.m_c[4] * __x__.m_c[16]) + (__x__.m_c[19] * __x__.m_c[1]));
			__x__.m_c[61] = ((-1.0f * __x__.m_c[9] * __x__.m_c[11]) + (__x__.m_c[14] * __x__.m_c[6]));
			__x__.m_c[71] = ((-1.0f * __x__.m_c[14] * __x__.m_c[16]) + (__x__.m_c[19] * __x__.m_c[11]));
			__x__.m_c[81] = ((__x__.m_c[9] * __x__.m_c[16]) + (-1.0f * __x__.m_c[19] * __x__.m_c[6]));
			__x__.m_c[91] = ((__x__.m_c[24] * __x__.m_c[6]) + (-1.0f * __x__.m_c[9] * __x__.m_c[21]));
			__x__.m_c[101] = ((-1.0f * __x__.m_c[14] * __x__.m_c[21]) + (__x__.m_c[24] * __x__.m_c[11]));
			__x__.m_c[111] = ((-1.0f * __x__.m_c[19] * __x__.m_c[21]) + (__x__.m_c[24] * __x__.m_c[16]));
			__x__.m_c[121] = ((-1.0f * __x__.m_c[4] * __x__.m_c[21]) + (__x__.m_c[24] * __x__.m_c[1]));
			__x__.m_c[32] = ((__x__.m_c[9] * __x__.m_c[2]) + (-1.0f * __x__.m_c[4] * __x__.m_c[7]));
			__x__.m_c[42] = ((__x__.m_c[14] * __x__.m_c[2]) + (-1.0f * __x__.m_c[4] * __x__.m_c[12]));
			__x__.m_c[52] = ((__x__.m_c[19] * __x__.m_c[2]) + (-1.0f * __x__.m_c[4] * __x__.m_c[17]));
			__x__.m_c[62] = ((-1.0f * __x__.m_c[9] * __x__.m_c[12]) + (__x__.m_c[14] * __x__.m_c[7]));
			__x__.m_c[72] = ((-1.0f * __x__.m_c[14] * __x__.m_c[17]) + (__x__.m_c[19] * __x__.m_c[12]));
			__x__.m_c[82] = ((__x__.m_c[9] * __x__.m_c[17]) + (-1.0f * __x__.m_c[19] * __x__.m_c[7]));
			__x__.m_c[92] = ((-1.0f * __x__.m_c[9] * __x__.m_c[22]) + (__x__.m_c[24] * __x__.m_c[7]));
			__x__.m_c[102] = ((-1.0f * __x__.m_c[14] * __x__.m_c[22]) + (__x__.m_c[24] * __x__.m_c[12]));
			__x__.m_c[112] = ((__x__.m_c[24] * __x__.m_c[17]) + (-1.0f * __x__.m_c[19] * __x__.m_c[22]));
			__x__.m_c[122] = ((-1.0f * __x__.m_c[4] * __x__.m_c[22]) + (__x__.m_c[24] * __x__.m_c[2]));
			__x__.m_c[33] = ((-1.0f * __x__.m_c[4] * __x__.m_c[8]) + (__x__.m_c[9] * __x__.m_c[3]));
			__x__.m_c[43] = ((-1.0f * __x__.m_c[4] * __x__.m_c[13]) + (__x__.m_c[14] * __x__.m_c[3]));
			__x__.m_c[53] = ((-1.0f * __x__.m_c[4] * __x__.m_c[18]) + (__x__.m_c[19] * __x__.m_c[3]));
			__x__.m_c[63] = ((-1.0f * __x__.m_c[9] * __x__.m_c[13]) + (__x__.m_c[14] * __x__.m_c[8]));
			__x__.m_c[73] = ((__x__.m_c[19] * __x__.m_c[13]) + (-1.0f * __x__.m_c[14] * __x__.m_c[18]));
			__x__.m_c[83] = ((-1.0f * __x__.m_c[19] * __x__.m_c[8]) + (__x__.m_c[9] * __x__.m_c[18]));
			__x__.m_c[93] = ((__x__.m_c[24] * __x__.m_c[8]) + (-1.0f * __x__.m_c[9] * __x__.m_c[23]));
			__x__.m_c[103] = ((-1.0f * __x__.m_c[14] * __x__.m_c[23]) + (__x__.m_c[24] * __x__.m_c[13]));
			__x__.m_c[113] = ((__x__.m_c[24] * __x__.m_c[18]) + (-1.0f * __x__.m_c[19] * __x__.m_c[23]));
			__x__.m_c[123] = ((-1.0f * __x__.m_c[4] * __x__.m_c[23]) + (__x__.m_c[24] * __x__.m_c[3]));
			__x__.m_c[34] = ((-1.0f * __x__.m_c[4] * __x__.m_c[5]) + (__x__.m_c[9] * __x__.m_c[0]));
			__x__.m_c[44] = ((-1.0f * __x__.m_c[4] * __x__.m_c[10]) + (__x__.m_c[14] * __x__.m_c[0]));
			__x__.m_c[54] = ((__x__.m_c[19] * __x__.m_c[0]) + (-1.0f * __x__.m_c[4] * __x__.m_c[15]));
			__x__.m_c[64] = ((-1.0f * __x__.m_c[9] * __x__.m_c[10]) + (__x__.m_c[14] * __x__.m_c[5]));
			__x__.m_c[74] = ((-1.0f * __x__.m_c[14] * __x__.m_c[15]) + (__x__.m_c[19] * __x__.m_c[10]));
			__x__.m_c[84] = ((__x__.m_c[9] * __x__.m_c[15]) + (-1.0f * __x__.m_c[19] * __x__.m_c[5]));
			__x__.m_c[94] = ((-1.0f * __x__.m_c[9] * __x__.m_c[20]) + (__x__.m_c[24] * __x__.m_c[5]));
			__x__.m_c[104] = ((__x__.m_c[24] * __x__.m_c[10]) + (-1.0f * __x__.m_c[14] * __x__.m_c[20]));
			__x__.m_c[114] = ((__x__.m_c[24] * __x__.m_c[15]) + (-1.0f * __x__.m_c[19] * __x__.m_c[20]));
			__x__.m_c[124] = ((__x__.m_c[24] * __x__.m_c[0]) + (-1.0f * __x__.m_c[4] * __x__.m_c[20]));
			__x__.m_c[125] = ((__x__.m_c[113] * __x__.m_c[12]) + (-1.0f * __x__.m_c[103] * __x__.m_c[17]) + (__x__.m_c[73] * __x__.m_c[22]));
			__x__.m_c[135] = ((__x__.m_c[83] * __x__.m_c[22]) + (-1.0f * __x__.m_c[113] * __x__.m_c[7]) + (__x__.m_c[93] * __x__.m_c[17]));
			__x__.m_c[145] = ((__x__.m_c[63] * __x__.m_c[22]) + (__x__.m_c[103] * __x__.m_c[7]) + (-1.0f * __x__.m_c[93] * __x__.m_c[12]));
			__x__.m_c[155] = ((__x__.m_c[113] * __x__.m_c[2]) + (__x__.m_c[53] * __x__.m_c[22]) + (-1.0f * __x__.m_c[123] * __x__.m_c[17]));
			__x__.m_c[165] = ((__x__.m_c[93] * __x__.m_c[2]) + (-1.0f * __x__.m_c[123] * __x__.m_c[7]) + (__x__.m_c[33] * __x__.m_c[22]));
			__x__.m_c[175] = ((__x__.m_c[43] * __x__.m_c[22]) + (-1.0f * __x__.m_c[123] * __x__.m_c[12]) + (__x__.m_c[103] * __x__.m_c[2]));
			__x__.m_c[185] = ((__x__.m_c[73] * __x__.m_c[2]) + (-1.0f * __x__.m_c[53] * __x__.m_c[12]) + (__x__.m_c[43] * __x__.m_c[17]));
			__x__.m_c[195] = ((-1.0f * __x__.m_c[53] * __x__.m_c[7]) + (__x__.m_c[33] * __x__.m_c[17]) + (-1.0f * __x__.m_c[83] * __x__.m_c[2]));
			__x__.m_c[205] = ((__x__.m_c[63] * __x__.m_c[2]) + (__x__.m_c[33] * __x__.m_c[12]) + (-1.0f * __x__.m_c[43] * __x__.m_c[7]));
			__x__.m_c[215] = ((__x__.m_c[73] * __x__.m_c[7]) + (__x__.m_c[83] * __x__.m_c[12]) + (__x__.m_c[63] * __x__.m_c[17]));
			__x__.m_c[126] = ((-1.0f * __x__.m_c[73] * __x__.m_c[21]) + (-1.0f * __x__.m_c[113] * __x__.m_c[11]) + (__x__.m_c[103] * __x__.m_c[16]));
			__x__.m_c[136] = ((-1.0f * __x__.m_c[83] * __x__.m_c[21]) + (__x__.m_c[113] * __x__.m_c[6]) + (-1.0f * __x__.m_c[93] * __x__.m_c[16]));
			__x__.m_c[146] = ((-1.0f * __x__.m_c[63] * __x__.m_c[21]) + (__x__.m_c[93] * __x__.m_c[11]) + (-1.0f * __x__.m_c[103] * __x__.m_c[6]));
			__x__.m_c[156] = ((__x__.m_c[123] * __x__.m_c[16]) + (-1.0f * __x__.m_c[53] * __x__.m_c[21]) + (-1.0f * __x__.m_c[113] * __x__.m_c[1]));
			__x__.m_c[166] = ((__x__.m_c[123] * __x__.m_c[6]) + (-1.0f * __x__.m_c[33] * __x__.m_c[21]) + (-1.0f * __x__.m_c[93] * __x__.m_c[1]));
			__x__.m_c[176] = ((__x__.m_c[123] * __x__.m_c[11]) + (-1.0f * __x__.m_c[103] * __x__.m_c[1]) + (-1.0f * __x__.m_c[43] * __x__.m_c[21]));
			__x__.m_c[186] = ((__x__.m_c[53] * __x__.m_c[11]) + (-1.0f * __x__.m_c[43] * __x__.m_c[16]) + (-1.0f * __x__.m_c[73] * __x__.m_c[1]));
			__x__.m_c[196] = ((-1.0f * __x__.m_c[33] * __x__.m_c[16]) + (__x__.m_c[53] * __x__.m_c[6]) + (__x__.m_c[83] * __x__.m_c[1]));
			__x__.m_c[206] = ((__x__.m_c[43] * __x__.m_c[6]) + (-1.0f * __x__.m_c[33] * __x__.m_c[11]) + (-1.0f * __x__.m_c[63] * __x__.m_c[1]));
			__x__.m_c[216] = ((-1.0f * __x__.m_c[63] * __x__.m_c[16]) + (-1.0f * __x__.m_c[83] * __x__.m_c[11]) + (-1.0f * __x__.m_c[73] * __x__.m_c[6]));
			__x__.m_c[127] = ((__x__.m_c[72] * __x__.m_c[21]) + (-1.0f * __x__.m_c[102] * __x__.m_c[16]) + (__x__.m_c[112] * __x__.m_c[11]));
			__x__.m_c[137] = ((__x__.m_c[92] * __x__.m_c[16]) + (__x__.m_c[82] * __x__.m_c[21]) + (-1.0f * __x__.m_c[112] * __x__.m_c[6]));
			__x__.m_c[147] = ((__x__.m_c[62] * __x__.m_c[21]) + (__x__.m_c[102] * __x__.m_c[6]) + (-1.0f * __x__.m_c[92] * __x__.m_c[11]));
			__x__.m_c[157] = ((-1.0f * __x__.m_c[122] * __x__.m_c[16]) + (__x__.m_c[52] * __x__.m_c[21]) + (__x__.m_c[112] * __x__.m_c[1]));
			__x__.m_c[167] = ((__x__.m_c[92] * __x__.m_c[1]) + (__x__.m_c[32] * __x__.m_c[21]) + (-1.0f * __x__.m_c[122] * __x__.m_c[6]));
			__x__.m_c[177] = ((__x__.m_c[42] * __x__.m_c[21]) + (-1.0f * __x__.m_c[122] * __x__.m_c[11]) + (__x__.m_c[102] * __x__.m_c[1]));
			__x__.m_c[187] = ((__x__.m_c[42] * __x__.m_c[16]) + (__x__.m_c[72] * __x__.m_c[1]) + (-1.0f * __x__.m_c[52] * __x__.m_c[11]));
			__x__.m_c[197] = ((-1.0f * __x__.m_c[82] * __x__.m_c[1]) + (-1.0f * __x__.m_c[52] * __x__.m_c[6]) + (__x__.m_c[32] * __x__.m_c[16]));
			__x__.m_c[207] = ((-1.0f * __x__.m_c[42] * __x__.m_c[6]) + (__x__.m_c[62] * __x__.m_c[1]) + (__x__.m_c[32] * __x__.m_c[11]));
			__x__.m_c[217] = ((__x__.m_c[62] * __x__.m_c[16]) + (__x__.m_c[72] * __x__.m_c[6]) + (__x__.m_c[82] * __x__.m_c[11]));
			__x__.m_c[128] = ((-1.0f * __x__.m_c[74] * __x__.m_c[23]) + (__x__.m_c[104] * __x__.m_c[18]) + (-1.0f * __x__.m_c[114] * __x__.m_c[13]));
			__x__.m_c[138] = ((-1.0f * __x__.m_c[94] * __x__.m_c[18]) + (__x__.m_c[114] * __x__.m_c[8]) + (-1.0f * __x__.m_c[84] * __x__.m_c[23]));
			__x__.m_c[148] = ((__x__.m_c[94] * __x__.m_c[13]) + (-1.0f * __x__.m_c[64] * __x__.m_c[23]) + (-1.0f * __x__.m_c[104] * __x__.m_c[8]));
			__x__.m_c[158] = ((__x__.m_c[124] * __x__.m_c[18]) + (-1.0f * __x__.m_c[54] * __x__.m_c[23]) + (-1.0f * __x__.m_c[114] * __x__.m_c[3]));
			__x__.m_c[168] = ((__x__.m_c[124] * __x__.m_c[8]) + (-1.0f * __x__.m_c[94] * __x__.m_c[3]) + (-1.0f * __x__.m_c[34] * __x__.m_c[23]));
			__x__.m_c[178] = ((-1.0f * __x__.m_c[104] * __x__.m_c[3]) + (__x__.m_c[124] * __x__.m_c[13]) + (-1.0f * __x__.m_c[44] * __x__.m_c[23]));
			__x__.m_c[188] = ((-1.0f * __x__.m_c[44] * __x__.m_c[18]) + (__x__.m_c[54] * __x__.m_c[13]) + (-1.0f * __x__.m_c[74] * __x__.m_c[3]));
			__x__.m_c[198] = ((__x__.m_c[54] * __x__.m_c[8]) + (__x__.m_c[84] * __x__.m_c[3]) + (-1.0f * __x__.m_c[34] * __x__.m_c[18]));
			__x__.m_c[208] = ((-1.0f * __x__.m_c[64] * __x__.m_c[3]) + (-1.0f * __x__.m_c[34] * __x__.m_c[13]) + (__x__.m_c[44] * __x__.m_c[8]));
			__x__.m_c[218] = ((-1.0f * __x__.m_c[74] * __x__.m_c[8]) + (-1.0f * __x__.m_c[84] * __x__.m_c[13]) + (-1.0f * __x__.m_c[64] * __x__.m_c[18]));
			__x__.m_c[129] = ((-1.0f * __x__.m_c[74] * __x__.m_c[21]) + (__x__.m_c[104] * __x__.m_c[16]) + (-1.0f * __x__.m_c[114] * __x__.m_c[11]));
			__x__.m_c[139] = ((-1.0f * __x__.m_c[94] * __x__.m_c[16]) + (-1.0f * __x__.m_c[84] * __x__.m_c[21]) + (__x__.m_c[114] * __x__.m_c[6]));
			__x__.m_c[149] = ((__x__.m_c[94] * __x__.m_c[11]) + (-1.0f * __x__.m_c[64] * __x__.m_c[21]) + (-1.0f * __x__.m_c[104] * __x__.m_c[6]));
			__x__.m_c[159] = ((-1.0f * __x__.m_c[54] * __x__.m_c[21]) + (-1.0f * __x__.m_c[114] * __x__.m_c[1]) + (__x__.m_c[124] * __x__.m_c[16]));
			__x__.m_c[169] = ((-1.0f * __x__.m_c[34] * __x__.m_c[21]) + (-1.0f * __x__.m_c[94] * __x__.m_c[1]) + (__x__.m_c[124] * __x__.m_c[6]));
			__x__.m_c[179] = ((-1.0f * __x__.m_c[104] * __x__.m_c[1]) + (__x__.m_c[124] * __x__.m_c[11]) + (-1.0f * __x__.m_c[44] * __x__.m_c[21]));
			__x__.m_c[189] = ((__x__.m_c[54] * __x__.m_c[11]) + (-1.0f * __x__.m_c[44] * __x__.m_c[16]) + (-1.0f * __x__.m_c[74] * __x__.m_c[1]));
			__x__.m_c[199] = ((-1.0f * __x__.m_c[34] * __x__.m_c[16]) + (__x__.m_c[54] * __x__.m_c[6]) + (__x__.m_c[84] * __x__.m_c[1]));
			__x__.m_c[209] = ((__x__.m_c[44] * __x__.m_c[6]) + (-1.0f * __x__.m_c[34] * __x__.m_c[11]) + (-1.0f * __x__.m_c[64] * __x__.m_c[1]));
			__x__.m_c[219] = ((-1.0f * __x__.m_c[84] * __x__.m_c[11]) + (-1.0f * __x__.m_c[74] * __x__.m_c[6]) + (-1.0f * __x__.m_c[64] * __x__.m_c[16]));
			__x__.m_c[130] = ((-1.0f * __x__.m_c[74] * __x__.m_c[22]) + (__x__.m_c[104] * __x__.m_c[17]) + (-1.0f * __x__.m_c[114] * __x__.m_c[12]));
			__x__.m_c[140] = ((-1.0f * __x__.m_c[94] * __x__.m_c[17]) + (__x__.m_c[114] * __x__.m_c[7]) + (-1.0f * __x__.m_c[84] * __x__.m_c[22]));
			__x__.m_c[150] = ((__x__.m_c[94] * __x__.m_c[12]) + (-1.0f * __x__.m_c[104] * __x__.m_c[7]) + (-1.0f * __x__.m_c[64] * __x__.m_c[22]));
			__x__.m_c[160] = ((-1.0f * __x__.m_c[54] * __x__.m_c[22]) + (__x__.m_c[124] * __x__.m_c[17]) + (-1.0f * __x__.m_c[114] * __x__.m_c[2]));
			__x__.m_c[170] = ((__x__.m_c[124] * __x__.m_c[7]) + (-1.0f * __x__.m_c[34] * __x__.m_c[22]) + (-1.0f * __x__.m_c[94] * __x__.m_c[2]));
			__x__.m_c[180] = ((__x__.m_c[124] * __x__.m_c[12]) + (-1.0f * __x__.m_c[44] * __x__.m_c[22]) + (-1.0f * __x__.m_c[104] * __x__.m_c[2]));
			__x__.m_c[190] = ((-1.0f * __x__.m_c[44] * __x__.m_c[17]) + (__x__.m_c[54] * __x__.m_c[12]) + (-1.0f * __x__.m_c[74] * __x__.m_c[2]));
			__x__.m_c[200] = ((__x__.m_c[54] * __x__.m_c[7]) + (__x__.m_c[84] * __x__.m_c[2]) + (-1.0f * __x__.m_c[34] * __x__.m_c[17]));
			__x__.m_c[210] = ((__x__.m_c[44] * __x__.m_c[7]) + (-1.0f * __x__.m_c[64] * __x__.m_c[2]) + (-1.0f * __x__.m_c[34] * __x__.m_c[12]));
			__x__.m_c[220] = ((-1.0f * __x__.m_c[64] * __x__.m_c[17]) + (-1.0f * __x__.m_c[74] * __x__.m_c[7]) + (-1.0f * __x__.m_c[84] * __x__.m_c[12]));
			__x__.m_c[131] = ((-1.0f * __x__.m_c[99] * __x__.m_c[15]) + (__x__.m_c[69] * __x__.m_c[20]) + (__x__.m_c[109] * __x__.m_c[10]));
			__x__.m_c[141] = ((__x__.m_c[79] * __x__.m_c[20]) + (__x__.m_c[89] * __x__.m_c[15]) + (-1.0f * __x__.m_c[109] * __x__.m_c[5]));
			__x__.m_c[151] = ((__x__.m_c[99] * __x__.m_c[5]) + (__x__.m_c[59] * __x__.m_c[20]) + (-1.0f * __x__.m_c[89] * __x__.m_c[10]));
			__x__.m_c[161] = ((__x__.m_c[49] * __x__.m_c[20]) + (__x__.m_c[109] * __x__.m_c[0]) + (-1.0f * __x__.m_c[119] * __x__.m_c[15]));
			__x__.m_c[171] = ((__x__.m_c[29] * __x__.m_c[20]) + (-1.0f * __x__.m_c[119] * __x__.m_c[5]) + (__x__.m_c[89] * __x__.m_c[0]));
			__x__.m_c[181] = ((__x__.m_c[99] * __x__.m_c[0]) + (-1.0f * __x__.m_c[119] * __x__.m_c[10]) + (__x__.m_c[39] * __x__.m_c[20]));
			__x__.m_c[191] = ((-1.0f * __x__.m_c[49] * __x__.m_c[10]) + (__x__.m_c[39] * __x__.m_c[15]) + (__x__.m_c[69] * __x__.m_c[0]));
			__x__.m_c[201] = ((__x__.m_c[29] * __x__.m_c[15]) + (-1.0f * __x__.m_c[79] * __x__.m_c[0]) + (-1.0f * __x__.m_c[49] * __x__.m_c[5]));
			__x__.m_c[211] = ((__x__.m_c[59] * __x__.m_c[0]) + (__x__.m_c[29] * __x__.m_c[10]) + (-1.0f * __x__.m_c[39] * __x__.m_c[5]));
			__x__.m_c[221] = ((__x__.m_c[59] * __x__.m_c[15]) + (__x__.m_c[69] * __x__.m_c[5]) + (__x__.m_c[79] * __x__.m_c[10]));
			__x__.m_c[132] = ((-1.0f * __x__.m_c[110] * __x__.m_c[10]) + (-1.0f * __x__.m_c[70] * __x__.m_c[20]) + (__x__.m_c[100] * __x__.m_c[15]));
			__x__.m_c[142] = ((__x__.m_c[110] * __x__.m_c[5]) + (-1.0f * __x__.m_c[90] * __x__.m_c[15]) + (-1.0f * __x__.m_c[80] * __x__.m_c[20]));
			__x__.m_c[152] = ((-1.0f * __x__.m_c[100] * __x__.m_c[5]) + (-1.0f * __x__.m_c[60] * __x__.m_c[20]) + (__x__.m_c[90] * __x__.m_c[10]));
			__x__.m_c[162] = ((-1.0f * __x__.m_c[110] * __x__.m_c[0]) + (-1.0f * __x__.m_c[50] * __x__.m_c[20]) + (__x__.m_c[120] * __x__.m_c[15]));
			__x__.m_c[172] = ((-1.0f * __x__.m_c[90] * __x__.m_c[0]) + (__x__.m_c[120] * __x__.m_c[5]) + (-1.0f * __x__.m_c[30] * __x__.m_c[20]));
			__x__.m_c[182] = ((__x__.m_c[120] * __x__.m_c[10]) + (-1.0f * __x__.m_c[40] * __x__.m_c[20]) + (-1.0f * __x__.m_c[100] * __x__.m_c[0]));
			__x__.m_c[192] = ((-1.0f * __x__.m_c[70] * __x__.m_c[0]) + (__x__.m_c[50] * __x__.m_c[10]) + (-1.0f * __x__.m_c[40] * __x__.m_c[15]));
			__x__.m_c[202] = ((-1.0f * __x__.m_c[30] * __x__.m_c[15]) + (__x__.m_c[80] * __x__.m_c[0]) + (__x__.m_c[50] * __x__.m_c[5]));
			__x__.m_c[212] = ((-1.0f * __x__.m_c[60] * __x__.m_c[0]) + (-1.0f * __x__.m_c[30] * __x__.m_c[10]) + (__x__.m_c[40] * __x__.m_c[5]));
			__x__.m_c[222] = ((-1.0f * __x__.m_c[60] * __x__.m_c[15]) + (-1.0f * __x__.m_c[80] * __x__.m_c[10]) + (-1.0f * __x__.m_c[70] * __x__.m_c[5]));
			__x__.m_c[133] = ((-1.0f * __x__.m_c[98] * __x__.m_c[15]) + (__x__.m_c[68] * __x__.m_c[20]) + (__x__.m_c[108] * __x__.m_c[10]));
			__x__.m_c[143] = ((-1.0f * __x__.m_c[108] * __x__.m_c[5]) + (__x__.m_c[78] * __x__.m_c[20]) + (__x__.m_c[88] * __x__.m_c[15]));
			__x__.m_c[153] = ((-1.0f * __x__.m_c[88] * __x__.m_c[10]) + (__x__.m_c[58] * __x__.m_c[20]) + (__x__.m_c[98] * __x__.m_c[5]));
			__x__.m_c[163] = ((-1.0f * __x__.m_c[118] * __x__.m_c[15]) + (__x__.m_c[48] * __x__.m_c[20]) + (__x__.m_c[108] * __x__.m_c[0]));
			__x__.m_c[173] = ((__x__.m_c[28] * __x__.m_c[20]) + (-1.0f * __x__.m_c[118] * __x__.m_c[5]) + (__x__.m_c[88] * __x__.m_c[0]));
			__x__.m_c[183] = ((-1.0f * __x__.m_c[118] * __x__.m_c[10]) + (__x__.m_c[98] * __x__.m_c[0]) + (__x__.m_c[38] * __x__.m_c[20]));
			__x__.m_c[193] = ((-1.0f * __x__.m_c[48] * __x__.m_c[10]) + (__x__.m_c[68] * __x__.m_c[0]) + (__x__.m_c[38] * __x__.m_c[15]));
			__x__.m_c[203] = ((-1.0f * __x__.m_c[78] * __x__.m_c[0]) + (-1.0f * __x__.m_c[48] * __x__.m_c[5]) + (__x__.m_c[28] * __x__.m_c[15]));
			__x__.m_c[213] = ((-1.0f * __x__.m_c[38] * __x__.m_c[5]) + (__x__.m_c[28] * __x__.m_c[10]) + (__x__.m_c[58] * __x__.m_c[0]));
			__x__.m_c[223] = ((__x__.m_c[78] * __x__.m_c[10]) + (__x__.m_c[58] * __x__.m_c[15]) + (__x__.m_c[68] * __x__.m_c[5]));
			__x__.m_c[134] = ((__x__.m_c[70] * __x__.m_c[22]) + (-1.0f * __x__.m_c[100] * __x__.m_c[17]) + (__x__.m_c[110] * __x__.m_c[12]));
			__x__.m_c[144] = ((__x__.m_c[80] * __x__.m_c[22]) + (__x__.m_c[90] * __x__.m_c[17]) + (-1.0f * __x__.m_c[110] * __x__.m_c[7]));
			__x__.m_c[154] = ((__x__.m_c[60] * __x__.m_c[22]) + (__x__.m_c[100] * __x__.m_c[7]) + (-1.0f * __x__.m_c[90] * __x__.m_c[12]));
			__x__.m_c[164] = ((__x__.m_c[50] * __x__.m_c[22]) + (__x__.m_c[110] * __x__.m_c[2]) + (-1.0f * __x__.m_c[120] * __x__.m_c[17]));
			__x__.m_c[174] = ((__x__.m_c[30] * __x__.m_c[22]) + (-1.0f * __x__.m_c[120] * __x__.m_c[7]) + (__x__.m_c[90] * __x__.m_c[2]));
			__x__.m_c[184] = ((__x__.m_c[100] * __x__.m_c[2]) + (__x__.m_c[40] * __x__.m_c[22]) + (-1.0f * __x__.m_c[120] * __x__.m_c[12]));
			__x__.m_c[194] = ((__x__.m_c[70] * __x__.m_c[2]) + (__x__.m_c[40] * __x__.m_c[17]) + (-1.0f * __x__.m_c[50] * __x__.m_c[12]));
			__x__.m_c[204] = ((-1.0f * __x__.m_c[80] * __x__.m_c[2]) + (-1.0f * __x__.m_c[50] * __x__.m_c[7]) + (__x__.m_c[30] * __x__.m_c[17]));
			__x__.m_c[214] = ((__x__.m_c[60] * __x__.m_c[2]) + (-1.0f * __x__.m_c[40] * __x__.m_c[7]) + (__x__.m_c[30] * __x__.m_c[12]));
			__x__.m_c[224] = ((__x__.m_c[60] * __x__.m_c[17]) + (__x__.m_c[80] * __x__.m_c[12]) + (__x__.m_c[70] * __x__.m_c[7]));
			__x__.m_c[225] = ((-1.0f * __x__.m_c[134] * __x__.m_c[9]) + (__x__.m_c[224] * __x__.m_c[24]) + (-1.0f * __x__.m_c[144] * __x__.m_c[14]) + (-1.0f * __x__.m_c[154] * __x__.m_c[19]));
			__x__.m_c[230] = ((-1.0f * __x__.m_c[134] * __x__.m_c[4]) + (__x__.m_c[164] * __x__.m_c[14]) + (-1.0f * __x__.m_c[184] * __x__.m_c[19]) + (__x__.m_c[194] * __x__.m_c[24]));
			__x__.m_c[235] = ((__x__.m_c[164] * __x__.m_c[9]) + (__x__.m_c[204] * __x__.m_c[24]) + (__x__.m_c[144] * __x__.m_c[4]) + (-1.0f * __x__.m_c[174] * __x__.m_c[19]));
			__x__.m_c[240] = ((-1.0f * __x__.m_c[154] * __x__.m_c[4]) + (-1.0f * __x__.m_c[174] * __x__.m_c[14]) + (__x__.m_c[214] * __x__.m_c[24]) + (__x__.m_c[184] * __x__.m_c[9]));
			__x__.m_c[245] = ((-1.0f * __x__.m_c[224] * __x__.m_c[4]) + (__x__.m_c[194] * __x__.m_c[9]) + (__x__.m_c[214] * __x__.m_c[19]) + (-1.0f * __x__.m_c[204] * __x__.m_c[14]));
			__x__.m_c[226] = ((-1.0f * __x__.m_c[131] * __x__.m_c[9]) + (-1.0f * __x__.m_c[151] * __x__.m_c[19]) + (-1.0f * __x__.m_c[141] * __x__.m_c[14]) + (__x__.m_c[221] * __x__.m_c[24]));
			__x__.m_c[231] = ((__x__.m_c[161] * __x__.m_c[14]) + (-1.0f * __x__.m_c[181] * __x__.m_c[19]) + (__x__.m_c[191] * __x__.m_c[24]) + (-1.0f * __x__.m_c[131] * __x__.m_c[4]));
			__x__.m_c[236] = ((-1.0f * __x__.m_c[171] * __x__.m_c[19]) + (__x__.m_c[161] * __x__.m_c[9]) + (__x__.m_c[141] * __x__.m_c[4]) + (__x__.m_c[201] * __x__.m_c[24]));
			__x__.m_c[241] = ((-1.0f * __x__.m_c[151] * __x__.m_c[4]) + (-1.0f * __x__.m_c[171] * __x__.m_c[14]) + (__x__.m_c[181] * __x__.m_c[9]) + (__x__.m_c[211] * __x__.m_c[24]));
			__x__.m_c[246] = ((__x__.m_c[191] * __x__.m_c[9]) + (-1.0f * __x__.m_c[201] * __x__.m_c[14]) + (-1.0f * __x__.m_c[221] * __x__.m_c[4]) + (__x__.m_c[211] * __x__.m_c[19]));
			__x__.m_c[227] = ((-1.0f * __x__.m_c[132] * __x__.m_c[9]) + (__x__.m_c[222] * __x__.m_c[24]) + (-1.0f * __x__.m_c[152] * __x__.m_c[19]) + (-1.0f * __x__.m_c[142] * __x__.m_c[14]));
			__x__.m_c[232] = ((__x__.m_c[192] * __x__.m_c[24]) + (-1.0f * __x__.m_c[132] * __x__.m_c[4]) + (-1.0f * __x__.m_c[182] * __x__.m_c[19]) + (__x__.m_c[162] * __x__.m_c[14]));
			__x__.m_c[237] = ((-1.0f * __x__.m_c[172] * __x__.m_c[19]) + (__x__.m_c[142] * __x__.m_c[4]) + (__x__.m_c[162] * __x__.m_c[9]) + (__x__.m_c[202] * __x__.m_c[24]));
			__x__.m_c[242] = ((-1.0f * __x__.m_c[152] * __x__.m_c[4]) + (-1.0f * __x__.m_c[172] * __x__.m_c[14]) + (__x__.m_c[212] * __x__.m_c[24]) + (__x__.m_c[182] * __x__.m_c[9]));
			__x__.m_c[247] = ((__x__.m_c[192] * __x__.m_c[9]) + (-1.0f * __x__.m_c[202] * __x__.m_c[14]) + (-1.0f * __x__.m_c[222] * __x__.m_c[4]) + (__x__.m_c[212] * __x__.m_c[19]));
			__x__.m_c[228] = ((__x__.m_c[223] * __x__.m_c[24]) + (-1.0f * __x__.m_c[133] * __x__.m_c[9]) + (-1.0f * __x__.m_c[143] * __x__.m_c[14]) + (-1.0f * __x__.m_c[153] * __x__.m_c[19]));
			__x__.m_c[233] = ((-1.0f * __x__.m_c[183] * __x__.m_c[19]) + (-1.0f * __x__.m_c[133] * __x__.m_c[4]) + (__x__.m_c[193] * __x__.m_c[24]) + (__x__.m_c[163] * __x__.m_c[14]));
			__x__.m_c[238] = ((-1.0f * __x__.m_c[173] * __x__.m_c[19]) + (__x__.m_c[163] * __x__.m_c[9]) + (__x__.m_c[143] * __x__.m_c[4]) + (__x__.m_c[203] * __x__.m_c[24]));
			__x__.m_c[243] = ((-1.0f * __x__.m_c[153] * __x__.m_c[4]) + (-1.0f * __x__.m_c[173] * __x__.m_c[14]) + (__x__.m_c[183] * __x__.m_c[9]) + (__x__.m_c[213] * __x__.m_c[24]));
			__x__.m_c[248] = ((__x__.m_c[193] * __x__.m_c[9]) + (-1.0f * __x__.m_c[203] * __x__.m_c[14]) + (-1.0f * __x__.m_c[223] * __x__.m_c[4]) + (__x__.m_c[213] * __x__.m_c[19]));
			__x__.m_c[229] = ((__x__.m_c[154] * __x__.m_c[15]) + (-1.0f * __x__.m_c[224] * __x__.m_c[20]) + (__x__.m_c[134] * __x__.m_c[5]) + (__x__.m_c[144] * __x__.m_c[10]));
			__x__.m_c[234] = ((__x__.m_c[134] * __x__.m_c[0]) + (-1.0f * __x__.m_c[164] * __x__.m_c[10]) + (__x__.m_c[184] * __x__.m_c[15]) + (-1.0f * __x__.m_c[194] * __x__.m_c[20]));
			__x__.m_c[239] = ((-1.0f * __x__.m_c[204] * __x__.m_c[20]) + (-1.0f * __x__.m_c[164] * __x__.m_c[5]) + (__x__.m_c[174] * __x__.m_c[15]) + (-1.0f * __x__.m_c[144] * __x__.m_c[0]));
			__x__.m_c[244] = ((-1.0f * __x__.m_c[184] * __x__.m_c[5]) + (__x__.m_c[174] * __x__.m_c[10]) + (-1.0f * __x__.m_c[214] * __x__.m_c[20]) + (__x__.m_c[154] * __x__.m_c[0]));
			__x__.m_c[249] = ((-1.0f * __x__.m_c[214] * __x__.m_c[15]) + (__x__.m_c[224] * __x__.m_c[0]) + (-1.0f * __x__.m_c[194] * __x__.m_c[5]) + (__x__.m_c[204] * __x__.m_c[10]));
			__x__.m_c[250] = ((-1.0f * __x__.m_c[234] * __x__.m_c[9]) + (__x__.m_c[229] * __x__.m_c[4]) + (-1.0f * __x__.m_c[244] * __x__.m_c[19]) + (__x__.m_c[239] * __x__.m_c[14]) + (__x__.m_c[249] * __x__.m_c[24]));
		}
	} /* end of namespace __G2_GENERATED__ */







} // end of namespace c3ga
// post_h_include


#endif //  _GA_c3ga_h_H_
