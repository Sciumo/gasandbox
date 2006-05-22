
// Generated on 2006-05-22 12:56:24 by G2 0.1 from 'E:\ga\ga_sandbox\libgasandbox\h3ga.gs2'

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

	#ifndef _GA_h3ga_h_H_
	#define _GA_h3ga_h_H_

	namespace h3ga {

	// multivector types:
	enum g2Type {
		MVT_NONE = -1,
			MVT_E1_T = 10,
			MVT_E2_T = 11,
			MVT_E3_T = 12,
			MVT_E0_T = 13,
			MVT_SCALAR = 14,
			MVT_VECTOR = 15,
			MVT_POINT = 16,
			MVT_NORMALIZEDPOINT = 17,
			MVT_LINE = 18,
			MVT_IMPROPERLINE = 19,
			MVT_PLANE = 20,
			MVT_IMPROPERPLANE = 21,
			MVT_ROTOR = 22,
			MVT___E1_CT__ = 23,
			MVT___E2_CT__ = 24,
			MVT___E3_CT__ = 25,
			MVT___E0_CT__ = 26,
			MVT___E0I_CT__ = 27,
			MVT___I4I_CT__ = 28,
			MVT_MV = 8,
			MVT_LAST = 29 
	};

	// outermorphism types:
	enum omType {
		OMT_NONE = -2,
			OMT_OM = 9,
			OMT_LAST = 29 
	};

	// grade definitions that can be joined using the '|' operator:
	const int GRADE_0 = 1;
	const int GRADE_1 = 2;
	const int GRADE_2 = 4;
	const int GRADE_3 = 8;
	const int GRADE_4 = 16;

	// The dimension of the space:
	extern const int mv_spaceDim;

	// Is the metric of the space Euclidean?
	extern const bool mv_metricEuclidean;

	// This array can be used to lookup the number of coordinates for a grade part of a general multivector
	extern const int mv_gradeSize[5];

	// This array can be used to lookup the number of coordinates based on a grade usage bitmap
	extern const int mv_size[32];

	// This array of ASCIIZ strings contains the names of the basis vectors
	extern const char *mv_basisVectorNames[4];

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'what basis vectors are in the basis element at position [x]?
	extern const int mv_basisElements[16][5];

	// This array of integers contains the 'sign' (even/odd permutation of canonical order) of basis elements in the general multivector
	extern const double mv_basisElementSign[16];

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'at what index do I find basis element [x] (x = basis vector bitmap)?'
	extern const int mv_basisElementIndexByBitmap[16];

	// This array of integers contains the indices of basis elements in the general multivector
	// Use it to answer: 'what basis element do I find at index [x]'?
	extern const int mv_basisElementBitmapByIndex[16];



	/* *************************************************************************** */
	/* *************************** define all classes upfront *************************** */
	/* *************************************************************************** */
	class e1_t;
	class e2_t;
	class e3_t;
	class e0_t;
	class scalar;
	class vector;
	class point;
	class normalizedPoint;
	class line;
	class improperLine;
	class plane;
	class improperPlane;
	class rotor;
	class __e1_ct__;
	class __e2_ct__;
	class __e3_ct__;
	class __e0_ct__;
	class __e0i_ct__;
	class __I4i_ct__;
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
		void save(const char *filename = "E:\\ga\\ga_sandbox\\libgasandbox\\h3ga.gp2", bool append = true);
		void init(const char *filename = "E:\\ga\\ga_sandbox\\libgasandbox\\h3ga.gp2",
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
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
		friend class e2_t;

		// friend functions of mv 
		friend char *string(const mv &obj, char *str, int maxLength, const char *fp /*= NULL*/);
		friend void compress(const float *c, float *cc, int &cgu, float epsilon = 0.0, int gu = 31);
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
		/// init from e0_t constructor
		inline mv(const e0_t &arg1) {
			set(arg1);
		}
		/// init from scalar constructor
		inline mv(const scalar &arg1) {
			set(arg1);
		}
		/// init from vector constructor
		inline mv(const vector &arg1) {
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
		/// init from line constructor
		inline mv(const line &arg1) {
			set(arg1);
		}
		/// init from improperLine constructor
		inline mv(const improperLine &arg1) {
			set(arg1);
		}
		/// init from plane constructor
		inline mv(const plane &arg1) {
			set(arg1);
		}
		/// init from improperPlane constructor
		inline mv(const improperPlane &arg1) {
			set(arg1);
		}
		/// init from rotor constructor
		inline mv(const rotor &arg1) {
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
		/// init from __e0_ct__ constructor
		inline mv(const __e0_ct__ &arg1) {
			set(arg1);
		}
		/// init from __e0i_ct__ constructor
		inline mv(const __e0i_ct__ &arg1) {
			set(arg1);
		}
		/// init from __I4i_ct__ constructor
		inline mv(const __I4i_ct__ &arg1) {
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


		/// set to e1_t 
		void set(const e1_t &arg1);
		/// set to e2_t 
		void set(const e2_t &arg1);
		/// set to e3_t 
		void set(const e3_t &arg1);
		/// set to e0_t 
		void set(const e0_t &arg1);
		/// set to scalar 
		void set(const scalar &arg1);
		/// set to vector 
		void set(const vector &arg1);
		/// set to point 
		void set(const point &arg1);
		/// set to normalizedPoint 
		void set(const normalizedPoint &arg1);
		/// set to line 
		void set(const line &arg1);
		/// set to improperLine 
		void set(const improperLine &arg1);
		/// set to plane 
		void set(const plane &arg1);
		/// set to improperPlane 
		void set(const improperPlane &arg1);
		/// set to rotor 
		void set(const rotor &arg1);
		/// set to __e1_ct__ 
		void set(const __e1_ct__ &arg1);
		/// set to __e2_ct__ 
		void set(const __e2_ct__ &arg1);
		/// set to __e3_ct__ 
		void set(const __e3_ct__ &arg1);
		/// set to __e0_ct__ 
		void set(const __e0_ct__ &arg1);
		/// set to __e0i_ct__ 
		void set(const __e0i_ct__ &arg1);
		/// set to __I4i_ct__ 
		void set(const __I4i_ct__ &arg1);


		/// assign copy
		mv &operator=(const mv &arg1);

		/// assign scalar
		mv &operator=(Float scalar);

		/// assign e1_t 
		mv&operator=(const e1_t& arg1);
		/// assign e2_t 
		mv&operator=(const e2_t& arg1);
		/// assign e3_t 
		mv&operator=(const e3_t& arg1);
		/// assign e0_t 
		mv&operator=(const e0_t& arg1);
		/// assign scalar 
		mv&operator=(const scalar& arg1);
		/// assign vector 
		mv&operator=(const vector& arg1);
		/// assign point 
		mv&operator=(const point& arg1);
		/// assign normalizedPoint 
		mv&operator=(const normalizedPoint& arg1);
		/// assign line 
		mv&operator=(const line& arg1);
		/// assign improperLine 
		mv&operator=(const improperLine& arg1);
		/// assign plane 
		mv&operator=(const plane& arg1);
		/// assign improperPlane 
		mv&operator=(const improperPlane& arg1);
		/// assign rotor 
		mv&operator=(const rotor& arg1);
		/// assign __e1_ct__ 
		mv&operator=(const __e1_ct__& arg1);
		/// assign __e2_ct__ 
		mv&operator=(const __e2_ct__& arg1);
		/// assign __e3_ct__ 
		mv&operator=(const __e3_ct__& arg1);
		/// assign __e0_ct__ 
		mv&operator=(const __e0_ct__& arg1);
		/// assign __e0i_ct__ 
		mv&operator=(const __e0i_ct__& arg1);
		/// assign __I4i_ct__ 
		mv&operator=(const __I4i_ct__& arg1);


		void compress(Float epsilon = 0.0);
		inline Float const *nullFloats() const {
			static Float *nf = NULL;
			if (nf == NULL) nf = new Float[16];
			return nf;
		}
		void expand(const Float *ptrs[], bool nulls = true) const;
		/// returns the absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;


		/// coordinate extraction by name
		inline Float e1() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 0];
			else return (float)0.0;
		}
		inline Float e2() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 1];
			else return (float)0.0;
		}
		inline Float e3() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 2];
			else return (float)0.0;
		}
		inline Float e0() const {
			if (gu() & 2)
				return m_c[mv_size[gu() & 1] + 3];
			else return (float)0.0;
		}
		inline Float e1e2() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 0];
			else return (float)0.0;
		}
		inline Float e2e3() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 1];
			else return (float)0.0;
		}
		inline Float e3e1() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 2];
			else return (float)0.0;
		}
		inline Float e1e0() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 3];
			else return (float)0.0;
		}
		inline Float e2e0() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 4];
			else return (float)0.0;
		}
		inline Float e3e0() const {
			if (gu() & 4)
				return m_c[mv_size[gu() & 3] + 5];
			else return (float)0.0;
		}
		inline Float e1e2e3() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 0];
			else return (float)0.0;
		}
		inline Float e1e2e0() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 1];
			else return (float)0.0;
		}
		inline Float e2e3e0() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 2];
			else return (float)0.0;
		}
		inline Float e3e1e0() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 3];
			else return (float)0.0;
		}
		inline Float e1e2e3e0() const {
			if (gu() & 16)
				return m_c[mv_size[gu() & 15] + 0];
			else return (float)0.0;
		}

		// coordinate storage, grade usage
		Float m_c[16]; ///< coordinate storage
		unsigned int m_gu; ///< grade usage
		inline unsigned int gu() const {return m_gu;}
		inline void gu(unsigned int g) {m_gu = g;}



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}
		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
		}
		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}



	}; // end of class mv 

	char *string(const mv & obj, char *str, int maxLength, const char *fp = NULL);
	// this function should be deprecated (conflicts with C++ stdlib)
	char *string(const mv & obj, const char *fp = NULL);


	mv mv_compress(const float *coordinates, float epsilon = (float)0.0, int gu = 16 * 2 -1);


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


	/// enum for the coordinates of e1_t 
	enum __e1_t_coordinates__ {e1_t_e1};

	class e1_t {
		// the friend classes of e1_t 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;

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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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


	/// enum for the coordinates of e0_t 
	enum __e0_t_coordinates__ {e0_t_e0};

	class e0_t {
		// the friend classes of e0_t 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline e0_t() {

			set();
		}

		/// scalar constructor 
		inline e0_t(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> e0_t	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline e0_t(const e0_t &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline e0_t(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> e0_t	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline e0_t(__e0_t_coordinates__, const Float *coordinates) {

			set(e0_t_e0, coordinates);
		}

		/// coordinates constructor
		inline e0_t(__e0_t_coordinates__, Float c_e0) {

			set(e0_t_e0, c_e0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const e0_t &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__e0_t_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__e0_t_coordinates__, Float c_e0);

		/// assign copy
		e0_t &operator=(const e0_t &arg1);

		/// assign general multivector
		e0_t &operator=(const mv &arg1);

		/// assign scalar
		e0_t &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e0() const {
			return m_c[0];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__e0_t_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class e0_t 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline e0_t _e0_t(const mv &arg1) {
		return e0_t(arg1, 0);
	}
	/// from const specialization class:
	inline const e0_t &_e0_t(const e0_t &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline e0_t &_e0_t(e0_t &arg1) {
		return arg1;
	}
	/// from Float:
	inline e0_t _e0_t(e0_t::Float arg1) {
		return e0_t(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline e0_t like(const mv &what, const e0_t &example) {return _e0_t(what);}
	/// from const specialization class:
	inline const e0_t like(const e0_t &what, const e0_t &example) {return _e0_t(what);}
	/// from non-const specialization class:
	inline e0_t like(e0_t &what, const e0_t &example) {return _e0_t(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const e0_t & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const e0_t & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const e0_t & v) {
		return (float)0;
	}


	/// enum for the coordinates of scalar 
	enum __scalar_coordinates__ {scalar_scalar};

	class scalar {
		// the friend classes of scalar 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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


	/// enum for the coordinates of vector 
	enum __vector_coordinates__ {vector_e1_e2_e3};

	class vector {
		// the friend classes of vector 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline vector() {

			set();
		}

		/// scalar constructor 
		inline vector(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> vector	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline vector(const vector &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline vector(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> vector	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline vector(__vector_coordinates__, const Float *coordinates) {

			set(vector_e1_e2_e3, coordinates);
		}

		/// coordinates constructor
		inline vector(__vector_coordinates__, Float c_e1, Float c_e2, Float c_e3) {

			set(vector_e1_e2_e3, c_e1, c_e2, c_e3);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const vector &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__vector_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__vector_coordinates__, Float c_e1, Float c_e2, Float c_e3);

		/// assign copy
		vector &operator=(const vector &arg1);

		/// assign general multivector
		vector &operator=(const mv &arg1);

		/// assign scalar
		vector &operator=(Float scalarVal);

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
		const Float *getC(__vector_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class vector 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline vector _vector(const mv &arg1) {
		return vector(arg1, 0);
	}
	/// from const specialization class:
	inline const vector &_vector(const vector &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline vector &_vector(vector &arg1) {
		return arg1;
	}
	/// from Float:
	inline vector _vector(vector::Float arg1) {
		return vector(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline vector like(const mv &what, const vector &example) {return _vector(what);}
	/// from const specialization class:
	inline const vector like(const vector &what, const vector &example) {return _vector(what);}
	/// from non-const specialization class:
	inline vector like(vector &what, const vector &example) {return _vector(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const vector & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const vector & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const vector & v) {
		return (float)0;
	}


	/// enum for the coordinates of point 
	enum __point_coordinates__ {point_e1_e2_e3_e0};

	class point {
		// the friend classes of point 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
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

			set(point_e1_e2_e3_e0, coordinates);
		}

		/// coordinates constructor
		inline point(__point_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_e0) {

			set(point_e1_e2_e3_e0, c_e1, c_e2, c_e3, c_e0);
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
		void set(__point_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_e0);

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
		inline Float e1() const {
			return m_c[0];
		}
		inline Float e2() const {
			return m_c[1];
		}
		inline Float e3() const {
			return m_c[2];
		}
		inline Float e0() const {
			return m_c[3];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__point_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[4];



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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
	enum __normalizedPoint_coordinates__ {normalizedPoint_e1_e2_e3_e0f1_0};

	class normalizedPoint {
		// the friend classes of normalizedPoint 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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

			set(normalizedPoint_e1_e2_e3_e0f1_0, coordinates);
		}

		/// coordinates constructor
		inline normalizedPoint(__normalizedPoint_coordinates__, Float c_e1, Float c_e2, Float c_e3) {

			set(normalizedPoint_e1_e2_e3_e0f1_0, c_e1, c_e2, c_e3);
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
		void set(__normalizedPoint_coordinates__, Float c_e1, Float c_e2, Float c_e3);

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

		/// const coordinate extraction by name
		inline Float e0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__normalizedPoint_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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


	/// enum for the coordinates of line 
	enum __line_coordinates__ {line_e1e2_e2e3_e3e1_e1e0_e2e0_e3e0};

	class line {
		// the friend classes of line 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class improperLine;
		friend class plane;
		friend class point;
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

			set(line_e1e2_e2e3_e3e1_e1e0_e2e0_e3e0, coordinates);
		}

		/// coordinates constructor
		inline line(__line_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1e0, Float c_e2e0, Float c_e3e0) {

			set(line_e1e2_e2e3_e3e1_e1e0_e2e0_e3e0, c_e1e2, c_e2e3, c_e3e1, c_e1e0, c_e2e0, c_e3e0);
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
		void set(__line_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1e0, Float c_e2e0, Float c_e3e0);

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
		inline Float e1e2() const {
			return m_c[0];
		}
		inline Float e2e3() const {
			return m_c[1];
		}
		inline Float e3e1() const {
			return m_c[2];
		}
		inline Float e1e0() const {
			return m_c[3];
		}
		inline Float e2e0() const {
			return m_c[4];
		}
		inline Float e3e0() const {
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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


	/// enum for the coordinates of improperLine 
	enum __improperLine_coordinates__ {improperLine_e1e2_e2e3_e3e1};

	class improperLine {
		// the friend classes of improperLine 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class plane;
		friend class point;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline improperLine() {

			set();
		}

		/// scalar constructor 
		inline improperLine(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> improperLine	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline improperLine(const improperLine &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline improperLine(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> improperLine	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline improperLine(__improperLine_coordinates__, const Float *coordinates) {

			set(improperLine_e1e2_e2e3_e3e1, coordinates);
		}

		/// coordinates constructor
		inline improperLine(__improperLine_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1) {

			set(improperLine_e1e2_e2e3_e3e1, c_e1e2, c_e2e3, c_e3e1);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const improperLine &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__improperLine_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__improperLine_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1);

		/// assign copy
		improperLine &operator=(const improperLine &arg1);

		/// assign general multivector
		improperLine &operator=(const mv &arg1);

		/// assign scalar
		improperLine &operator=(Float scalarVal);

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
		const Float *getC(__improperLine_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[3];



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class improperLine 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline improperLine _improperLine(const mv &arg1) {
		return improperLine(arg1, 0);
	}
	/// from const specialization class:
	inline const improperLine &_improperLine(const improperLine &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline improperLine &_improperLine(improperLine &arg1) {
		return arg1;
	}
	/// from Float:
	inline improperLine _improperLine(improperLine::Float arg1) {
		return improperLine(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline improperLine like(const mv &what, const improperLine &example) {return _improperLine(what);}
	/// from const specialization class:
	inline const improperLine like(const improperLine &what, const improperLine &example) {return _improperLine(what);}
	/// from non-const specialization class:
	inline improperLine like(improperLine &what, const improperLine &example) {return _improperLine(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const improperLine & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const improperLine & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const improperLine & v) {
		return (float)0;
	}


	/// enum for the coordinates of plane 
	enum __plane_coordinates__ {plane_e1e2e3_e1e2e0_e2e3e0_e3e1e0};

	class plane {
		// the friend classes of plane 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class point;
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

			set(plane_e1e2e3_e1e2e0_e2e3e0_e3e1e0, coordinates);
		}

		/// coordinates constructor
		inline plane(__plane_coordinates__, Float c_e1e2e3, Float c_e1e2e0, Float c_e2e3e0, Float c_e3e1e0) {

			set(plane_e1e2e3_e1e2e0_e2e3e0_e3e1e0, c_e1e2e3, c_e1e2e0, c_e2e3e0, c_e3e1e0);
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
		void set(__plane_coordinates__, Float c_e1e2e3, Float c_e1e2e0, Float c_e2e3e0, Float c_e3e1e0);

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
		inline Float e1e2e3() const {
			return m_c[0];
		}
		inline Float e1e2e0() const {
			return m_c[1];
		}
		inline Float e2e3e0() const {
			return m_c[2];
		}
		inline Float e3e1e0() const {
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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


	/// enum for the coordinates of improperPlane 
	enum __improperPlane_coordinates__ {improperPlane_e1e2e3};

	class improperPlane {
		// the friend classes of improperPlane 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline improperPlane() {

			set();
		}

		/// scalar constructor 
		inline improperPlane(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> improperPlane	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline improperPlane(const improperPlane &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline improperPlane(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> improperPlane	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline improperPlane(__improperPlane_coordinates__, const Float *coordinates) {

			set(improperPlane_e1e2e3, coordinates);
		}

		/// coordinates constructor
		inline improperPlane(__improperPlane_coordinates__, Float c_e1e2e3) {

			set(improperPlane_e1e2e3, c_e1e2e3);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const improperPlane &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(__improperPlane_coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(__improperPlane_coordinates__, Float c_e1e2e3);

		/// assign copy
		improperPlane &operator=(const improperPlane &arg1);

		/// assign general multivector
		improperPlane &operator=(const mv &arg1);

		/// assign scalar
		improperPlane &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name
		inline Float e1e2e3() const {
			return m_c[0];
		}

		/// const coordinate extraction by name

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(__improperPlane_coordinates__ sanityCheckValue) const {
			return m_c;
		}

		/// coordinate storage
		Float m_c[1];



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class improperPlane 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline improperPlane _improperPlane(const mv &arg1) {
		return improperPlane(arg1, 0);
	}
	/// from const specialization class:
	inline const improperPlane &_improperPlane(const improperPlane &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline improperPlane &_improperPlane(improperPlane &arg1) {
		return arg1;
	}
	/// from Float:
	inline improperPlane _improperPlane(improperPlane::Float arg1) {
		return improperPlane(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline improperPlane like(const mv &what, const improperPlane &example) {return _improperPlane(what);}
	/// from const specialization class:
	inline const improperPlane like(const improperPlane &what, const improperPlane &example) {return _improperPlane(what);}
	/// from non-const specialization class:
	inline improperPlane like(improperPlane &what, const improperPlane &example) {return _improperPlane(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const improperPlane & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const improperPlane & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const improperPlane & v) {
		return (float)0;
	}


	/// enum for the coordinates of rotor 
	enum __rotor_coordinates__ {rotor_scalar_e1e2_e2e3_e3e1};

	class rotor {
		// the friend classes of rotor 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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


	/// enum for the coordinates of __e1_ct__ 
	enum ____e1_ct___coordinates__ {__e1_ct___e1f1_0};

	class __e1_ct__ {
		// the friend classes of __e1_ct__ 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
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


	/// enum for the coordinates of __e0_ct__ 
	enum ____e0_ct___coordinates__ {__e0_ct___e0f1_0};

	class __e0_ct__ {
		// the friend classes of __e0_ct__ 
		friend class __e0i_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline __e0_ct__() {

			set();
		}

		/// scalar constructor 
		inline __e0_ct__(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> __e0_ct__	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline __e0_ct__(const __e0_ct__ &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline __e0_ct__(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> __e0_ct__	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline __e0_ct__(____e0_ct___coordinates__, const Float *coordinates) {

			set(__e0_ct___e0f1_0, coordinates);
		}

		/// coordinates constructor
		inline __e0_ct__(____e0_ct___coordinates__) {

			set(__e0_ct___e0f1_0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const __e0_ct__ &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(____e0_ct___coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(____e0_ct___coordinates__);

		/// assign copy
		__e0_ct__ &operator=(const __e0_ct__ &arg1);

		/// assign general multivector
		__e0_ct__ &operator=(const mv &arg1);

		/// assign scalar
		__e0_ct__ &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name
		inline Float e0f1_0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(____e0_ct___coordinates__ sanityCheckValue) const {
			return NULL;
		}

		// constants, so no coordinate storage



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class __e0_ct__ 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline __e0_ct__ ___e0_ct__(const mv &arg1) {
		return __e0_ct__(arg1, 0);
	}
	/// from const specialization class:
	inline const __e0_ct__ &___e0_ct__(const __e0_ct__ &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline __e0_ct__ &___e0_ct__(__e0_ct__ &arg1) {
		return arg1;
	}
	/// from Float:
	inline __e0_ct__ ___e0_ct__(__e0_ct__::Float arg1) {
		return __e0_ct__(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline __e0_ct__ like(const mv &what, const __e0_ct__ &example) {return ___e0_ct__(what);}
	/// from const specialization class:
	inline const __e0_ct__ like(const __e0_ct__ &what, const __e0_ct__ &example) {return ___e0_ct__(what);}
	/// from non-const specialization class:
	inline __e0_ct__ like(__e0_ct__ &what, const __e0_ct__ &example) {return ___e0_ct__(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const __e0_ct__ & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const __e0_ct__ & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const __e0_ct__ & v) {
		return (float)0;
	}


	/// enum for the coordinates of __e0i_ct__ 
	enum ____e0i_ct___coordinates__ {__e0i_ct___e0f1_0};

	class __e0i_ct__ {
		// the friend classes of __e0i_ct__ 
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline __e0i_ct__() {

			set();
		}

		/// scalar constructor 
		inline __e0i_ct__(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> __e0i_ct__	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline __e0i_ct__(const __e0i_ct__ &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline __e0i_ct__(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> __e0i_ct__	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline __e0i_ct__(____e0i_ct___coordinates__, const Float *coordinates) {

			set(__e0i_ct___e0f1_0, coordinates);
		}

		/// coordinates constructor
		inline __e0i_ct__(____e0i_ct___coordinates__) {

			set(__e0i_ct___e0f1_0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const __e0i_ct__ &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(____e0i_ct___coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(____e0i_ct___coordinates__);

		/// assign copy
		__e0i_ct__ &operator=(const __e0i_ct__ &arg1);

		/// assign general multivector
		__e0i_ct__ &operator=(const mv &arg1);

		/// assign scalar
		__e0i_ct__ &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name
		inline Float e0f1_0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(____e0i_ct___coordinates__ sanityCheckValue) const {
			return NULL;
		}

		// constants, so no coordinate storage



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class __e0i_ct__ 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline __e0i_ct__ ___e0i_ct__(const mv &arg1) {
		return __e0i_ct__(arg1, 0);
	}
	/// from const specialization class:
	inline const __e0i_ct__ &___e0i_ct__(const __e0i_ct__ &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline __e0i_ct__ &___e0i_ct__(__e0i_ct__ &arg1) {
		return arg1;
	}
	/// from Float:
	inline __e0i_ct__ ___e0i_ct__(__e0i_ct__::Float arg1) {
		return __e0i_ct__(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline __e0i_ct__ like(const mv &what, const __e0i_ct__ &example) {return ___e0i_ct__(what);}
	/// from const specialization class:
	inline const __e0i_ct__ like(const __e0i_ct__ &what, const __e0i_ct__ &example) {return ___e0i_ct__(what);}
	/// from non-const specialization class:
	inline __e0i_ct__ like(__e0i_ct__ &what, const __e0i_ct__ &example) {return ___e0i_ct__(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const __e0i_ct__ & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const __e0i_ct__ & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const __e0i_ct__ & v) {
		return (float)0;
	}


	/// enum for the coordinates of __I4i_ct__ 
	enum ____I4i_ct___coordinates__ {__I4i_ct___e1e2e3e0f1_0};

	class __I4i_ct__ {
		// the friend classes of __I4i_ct__ 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class vector;
		friend class om;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
		friend class e2_t;

		public:
			typedef float Float;

		/// zero constructor
		inline __I4i_ct__() {

			set();
		}

		/// scalar constructor 
		inline __I4i_ct__(Float s, int filler) { // filler can have any value, it simply prevents implicit conversion from Float -> __I4i_ct__	 
			set(s);
		}




		/// copy constructor (MUST PASS BY REFERENCE)
		inline __I4i_ct__(const __I4i_ct__ &arg1) {

			set(arg1);
		}

		/// general multivector constructor (that can not be selected for implicit conversion by C++)
		inline __I4i_ct__(const mv &arg1, int filler) { // filler can have any value, it simply prevents implicit conversion from mv -> __I4i_ct__	 
			set(arg1);
		}

		/// pointer to coordinates constructor
		inline __I4i_ct__(____I4i_ct___coordinates__, const Float *coordinates) {

			set(__I4i_ct___e1e2e3e0f1_0, coordinates);
		}

		/// coordinates constructor
		inline __I4i_ct__(____I4i_ct___coordinates__) {

			set(__I4i_ct___e1e2e3e0f1_0);
		}

		/// set to null
		void set();

		/// set to scalar
		void set(Float s);

		/// set to copy
		void set(const __I4i_ct__ &arg1);

		/// set to copy of general multivector
		void set(const mv &arg1);

		/// pointer to coordinates constructor
		void set(____I4i_ct___coordinates__, const Float *coordinates);

		/// set to coordinates
		void set(____I4i_ct___coordinates__);

		/// assign copy
		__I4i_ct__ &operator=(const __I4i_ct__ &arg1);

		/// assign general multivector
		__I4i_ct__ &operator=(const mv &arg1);

		/// assign scalar
		__I4i_ct__ &operator=(Float scalarVal);

		/// returns absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// coordinate extraction by name

		/// const coordinate extraction by name
		inline Float e1e2e3e0f1_0() const {
			return 1.0f;
		}

		/// get all coordinates (returns NULL for fully constant specialization
		const Float *getC(____I4i_ct___coordinates__ sanityCheckValue) const {
			return NULL;
		}

		// constants, so no coordinate storage



		inline const char * c_str(const char *fp = NULL) const {
			return ::h3ga::c_str(*this, fp);
		}

		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::h3ga::toString(*this, fp);
		}

		inline std::string toString_f() const {return toString("%f");}
		inline std::string toString_e() const {return toString("%e");}
		inline std::string toString_e20() const {return toString("%2.20e");}







	}; // end of class __I4i_ct__ 

	/* 'underscore constructors' */
	/// underscore constructor from general multivector:
	inline __I4i_ct__ ___I4i_ct__(const mv &arg1) {
		return __I4i_ct__(arg1, 0);
	}
	/// from const specialization class:
	inline const __I4i_ct__ &___I4i_ct__(const __I4i_ct__ &arg1) {
		return arg1;
	}
	/// from non-const specialization class:
	inline __I4i_ct__ &___I4i_ct__(__I4i_ct__ &arg1) {
		return arg1;
	}
	/// from Float:
	inline __I4i_ct__ ___I4i_ct__(__I4i_ct__::Float arg1) {
		return __I4i_ct__(arg1, 0); // 0 = filler; can have any value, it simply prevents implicit conversion from mv -> vector	 
	}



	// like example constructors, for use with templates
	/// underscore constructor from general multivector:
	inline __I4i_ct__ like(const mv &what, const __I4i_ct__ &example) {return ___I4i_ct__(what);}
	/// from const specialization class:
	inline const __I4i_ct__ like(const __I4i_ct__ &what, const __I4i_ct__ &example) {return ___I4i_ct__(what);}
	/// from non-const specialization class:
	inline __I4i_ct__ like(__I4i_ct__ &what, const __I4i_ct__ &example) {return ___I4i_ct__(what);}




	// underscore 'constructors' for float types:

	/// returns scalar part of v as float
	inline float _float(const __I4i_ct__ & v) {
		return (float)0;
	}
	/// returns scalar part of v as double
	inline double _double(const __I4i_ct__ & v) {
		return (double)0;
	}
	/// returns scalar part of v as Float
	inline float _Float(const __I4i_ct__ & v) {
		return (float)0;
	}


	class om {
		// the friend classes of om 
		friend class __e0i_ct__;
		friend class __e0_ct__;
		friend class mv;
		friend class improperPlane;
		friend class __e1_ct__;
		friend class __e2_ct__;
		friend class normalizedPoint;
		friend class e0_t;
		friend class e3_t;
		friend class scalar;
		friend class __e3_ct__;
		friend class __I4i_ct__;
		friend class vector;
		friend class e1_t;
		friend class rotor;
		friend class line;
		friend class improperLine;
		friend class plane;
		friend class point;
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
		inline om(const point & image_of_e1, const point & image_of_e2, const point & image_of_e3, const point & image_of_e0) {
			set(image_of_e1, image_of_e2, image_of_e3, image_of_e0);
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
			const point & image_of_e1, const point & image_of_e2, const point & image_of_e3, const point & image_of_e0);


		/// assign copy
		om &operator=(const om &arg1);

		/// assign scalar (creates scalar * 'I' outermorphism)
		om &operator=(Float scalarVal);

		/// assign specialization:


		Float m_c[69]; ///< coordinate storage




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


	extern __I4i_ct__ I4i;
	extern __e0_ct__ e0;
	extern __e3_ct__ e3;
	extern __e1_ct__ e1;
	extern __e2_ct__ e2;
	extern __I4i_ct__ I4;
	extern __e0i_ct__ e0i;
	inline mv lcont(const mv& x, const mv& y);
	inline scalar scp(const mv& x, const mv& y);
	inline scalar extract_coord(const mv& x, const mv& y);
	inline mv gp(const mv& x, const mv& y);
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
	inline mv apply_om(const om& x, const mv& y);
	inline mv gradeInvolution(const mv& x);
	namespace __G2_GENERATED__ {
		inline void set(om& __x__, const point& __image_of_e1__, const point& __image_of_e2__, const point& __image_of_e3__, const point& __image_of_e0__);
	} /* end of namespace __G2_GENERATED__ */
	inline mv operator+=(mv& arg1, const mv& arg2);
	inline e1_t operator+=(e1_t& arg1, const mv& arg2);
	inline e2_t operator+=(e2_t& arg1, const mv& arg2);
	inline e3_t operator+=(e3_t& arg1, const mv& arg2);
	inline e0_t operator+=(e0_t& arg1, const mv& arg2);
	inline scalar operator+=(scalar& arg1, const mv& arg2);
	inline vector operator+=(vector& arg1, const mv& arg2);
	inline point operator+=(point& arg1, const mv& arg2);
	inline normalizedPoint operator+=(normalizedPoint& arg1, const mv& arg2);
	inline line operator+=(line& arg1, const mv& arg2);
	inline improperLine operator+=(improperLine& arg1, const mv& arg2);
	inline plane operator+=(plane& arg1, const mv& arg2);
	inline improperPlane operator+=(improperPlane& arg1, const mv& arg2);
	inline rotor operator+=(rotor& arg1, const mv& arg2);
	inline __e1_ct__ operator+=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator+=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator+=(__e3_ct__& arg1, const mv& arg2);
	inline __e0_ct__ operator+=(__e0_ct__& arg1, const mv& arg2);
	inline __e0i_ct__ operator+=(__e0i_ct__& arg1, const mv& arg2);
	inline __I4i_ct__ operator+=(__I4i_ct__& arg1, const mv& arg2);
	inline mv operator+(const mv& arg1, const mv& arg2);
	inline mv operator-=(mv& arg1, const mv& arg2);
	inline e1_t operator-=(e1_t& arg1, const mv& arg2);
	inline e2_t operator-=(e2_t& arg1, const mv& arg2);
	inline e3_t operator-=(e3_t& arg1, const mv& arg2);
	inline e0_t operator-=(e0_t& arg1, const mv& arg2);
	inline scalar operator-=(scalar& arg1, const mv& arg2);
	inline vector operator-=(vector& arg1, const mv& arg2);
	inline point operator-=(point& arg1, const mv& arg2);
	inline normalizedPoint operator-=(normalizedPoint& arg1, const mv& arg2);
	inline line operator-=(line& arg1, const mv& arg2);
	inline improperLine operator-=(improperLine& arg1, const mv& arg2);
	inline plane operator-=(plane& arg1, const mv& arg2);
	inline improperPlane operator-=(improperPlane& arg1, const mv& arg2);
	inline rotor operator-=(rotor& arg1, const mv& arg2);
	inline __e1_ct__ operator-=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator-=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator-=(__e3_ct__& arg1, const mv& arg2);
	inline __e0_ct__ operator-=(__e0_ct__& arg1, const mv& arg2);
	inline __e0i_ct__ operator-=(__e0i_ct__& arg1, const mv& arg2);
	inline __I4i_ct__ operator-=(__I4i_ct__& arg1, const mv& arg2);
	inline mv operator-(const mv& arg1, const mv& arg2);
	inline mv operator-(const mv& arg1);
	inline mv operator%=(mv& arg1, const mv& arg2);
	inline e1_t operator%=(e1_t& arg1, const mv& arg2);
	inline e2_t operator%=(e2_t& arg1, const mv& arg2);
	inline e3_t operator%=(e3_t& arg1, const mv& arg2);
	inline e0_t operator%=(e0_t& arg1, const mv& arg2);
	inline scalar operator%=(scalar& arg1, const mv& arg2);
	inline vector operator%=(vector& arg1, const mv& arg2);
	inline point operator%=(point& arg1, const mv& arg2);
	inline normalizedPoint operator%=(normalizedPoint& arg1, const mv& arg2);
	inline line operator%=(line& arg1, const mv& arg2);
	inline improperLine operator%=(improperLine& arg1, const mv& arg2);
	inline plane operator%=(plane& arg1, const mv& arg2);
	inline improperPlane operator%=(improperPlane& arg1, const mv& arg2);
	inline rotor operator%=(rotor& arg1, const mv& arg2);
	inline __e1_ct__ operator%=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator%=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator%=(__e3_ct__& arg1, const mv& arg2);
	inline __e0_ct__ operator%=(__e0_ct__& arg1, const mv& arg2);
	inline __e0i_ct__ operator%=(__e0i_ct__& arg1, const mv& arg2);
	inline __I4i_ct__ operator%=(__I4i_ct__& arg1, const mv& arg2);
	inline scalar operator%(const mv& arg1, const mv& arg2);
	inline mv operator^=(mv& arg1, const mv& arg2);
	inline e1_t operator^=(e1_t& arg1, const mv& arg2);
	inline e2_t operator^=(e2_t& arg1, const mv& arg2);
	inline e3_t operator^=(e3_t& arg1, const mv& arg2);
	inline e0_t operator^=(e0_t& arg1, const mv& arg2);
	inline scalar operator^=(scalar& arg1, const mv& arg2);
	inline vector operator^=(vector& arg1, const mv& arg2);
	inline point operator^=(point& arg1, const mv& arg2);
	inline normalizedPoint operator^=(normalizedPoint& arg1, const mv& arg2);
	inline line operator^=(line& arg1, const mv& arg2);
	inline improperLine operator^=(improperLine& arg1, const mv& arg2);
	inline plane operator^=(plane& arg1, const mv& arg2);
	inline improperPlane operator^=(improperPlane& arg1, const mv& arg2);
	inline rotor operator^=(rotor& arg1, const mv& arg2);
	inline __e1_ct__ operator^=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator^=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator^=(__e3_ct__& arg1, const mv& arg2);
	inline __e0_ct__ operator^=(__e0_ct__& arg1, const mv& arg2);
	inline __e0i_ct__ operator^=(__e0i_ct__& arg1, const mv& arg2);
	inline __I4i_ct__ operator^=(__I4i_ct__& arg1, const mv& arg2);
	inline mv operator^(const mv& arg1, const mv& arg2);
	inline mv operator*=(mv& arg1, const mv& arg2);
	inline e1_t operator*=(e1_t& arg1, const mv& arg2);
	inline e2_t operator*=(e2_t& arg1, const mv& arg2);
	inline e3_t operator*=(e3_t& arg1, const mv& arg2);
	inline e0_t operator*=(e0_t& arg1, const mv& arg2);
	inline scalar operator*=(scalar& arg1, const mv& arg2);
	inline vector operator*=(vector& arg1, const mv& arg2);
	inline point operator*=(point& arg1, const mv& arg2);
	inline normalizedPoint operator*=(normalizedPoint& arg1, const mv& arg2);
	inline line operator*=(line& arg1, const mv& arg2);
	inline improperLine operator*=(improperLine& arg1, const mv& arg2);
	inline plane operator*=(plane& arg1, const mv& arg2);
	inline improperPlane operator*=(improperPlane& arg1, const mv& arg2);
	inline rotor operator*=(rotor& arg1, const mv& arg2);
	inline __e1_ct__ operator*=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator*=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator*=(__e3_ct__& arg1, const mv& arg2);
	inline __e0_ct__ operator*=(__e0_ct__& arg1, const mv& arg2);
	inline __e0i_ct__ operator*=(__e0i_ct__& arg1, const mv& arg2);
	inline __I4i_ct__ operator*=(__I4i_ct__& arg1, const mv& arg2);
	inline mv operator*(const mv& arg1, const mv& arg2);
	inline mv operator<<=(mv& arg1, const mv& arg2);
	inline e1_t operator<<=(e1_t& arg1, const mv& arg2);
	inline e2_t operator<<=(e2_t& arg1, const mv& arg2);
	inline e3_t operator<<=(e3_t& arg1, const mv& arg2);
	inline e0_t operator<<=(e0_t& arg1, const mv& arg2);
	inline scalar operator<<=(scalar& arg1, const mv& arg2);
	inline vector operator<<=(vector& arg1, const mv& arg2);
	inline point operator<<=(point& arg1, const mv& arg2);
	inline normalizedPoint operator<<=(normalizedPoint& arg1, const mv& arg2);
	inline line operator<<=(line& arg1, const mv& arg2);
	inline improperLine operator<<=(improperLine& arg1, const mv& arg2);
	inline plane operator<<=(plane& arg1, const mv& arg2);
	inline improperPlane operator<<=(improperPlane& arg1, const mv& arg2);
	inline rotor operator<<=(rotor& arg1, const mv& arg2);
	inline __e1_ct__ operator<<=(__e1_ct__& arg1, const mv& arg2);
	inline __e2_ct__ operator<<=(__e2_ct__& arg1, const mv& arg2);
	inline __e3_ct__ operator<<=(__e3_ct__& arg1, const mv& arg2);
	inline __e0_ct__ operator<<=(__e0_ct__& arg1, const mv& arg2);
	inline __e0i_ct__ operator<<=(__e0i_ct__& arg1, const mv& arg2);
	inline __I4i_ct__ operator<<=(__I4i_ct__& arg1, const mv& arg2);
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



	// set to e1_t 
	inline void mv::set(const e1_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;


	}
	// set to e2_t 
	inline void mv::set(const e2_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;


	}
	// set to e3_t 
	inline void mv::set(const e3_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[0] ;
		m_c[3] = (Float)0;


	}
	// set to e0_t 
	inline void mv::set(const e0_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;


	}
	// set to scalar 
	inline void mv::set(const scalar & arg1) {

		// set grade usage 
		gu(1);


		m_c[0] = arg1.m_c[0] ;


	}
	// set to vector 
	inline void mv::set(const vector & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = (Float)0;


	}
	// set to point 
	inline void mv::set(const point & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;


	}
	// set to normalizedPoint 
	inline void mv::set(const normalizedPoint & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = (Float)1.0f; 


	}
	// set to line 
	inline void mv::set(const line & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;


	}
	// set to improperLine 
	inline void mv::set(const improperLine & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;


	}
	// set to plane 
	inline void mv::set(const plane & arg1) {

		// set grade usage 
		gu(8);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;


	}
	// set to improperPlane 
	inline void mv::set(const improperPlane & arg1) {

		// set grade usage 
		gu(8);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;


	}
	// set to rotor 
	inline void mv::set(const rotor & arg1) {

		// set grade usage 
		gu(5);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;


	}
	// set to __e1_ct__ 
	inline void mv::set(const __e1_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;


	}
	// set to __e2_ct__ 
	inline void mv::set(const __e2_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)1.0f; 
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;


	}
	// set to __e3_ct__ 
	inline void mv::set(const __e3_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)1.0f; 
		m_c[3] = (Float)0;


	}
	// set to __e0_ct__ 
	inline void mv::set(const __e0_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)1.0f; 


	}
	// set to __e0i_ct__ 
	inline void mv::set(const __e0i_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)1.0f; 


	}
	// set to __I4i_ct__ 
	inline void mv::set(const __I4i_ct__ & arg1) {

		// set grade usage 
		gu(16);


		m_c[0] = (Float)1.0f; 


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
	// assign e0_t 
	inline mv& mv::operator=(const e0_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign scalar 
	inline mv& mv::operator=(const scalar& arg1) {
		set(arg1);
		return *this;
	}
	// assign vector 
	inline mv& mv::operator=(const vector& arg1) {
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
	// assign line 
	inline mv& mv::operator=(const line& arg1) {
		set(arg1);
		return *this;
	}
	// assign improperLine 
	inline mv& mv::operator=(const improperLine& arg1) {
		set(arg1);
		return *this;
	}
	// assign plane 
	inline mv& mv::operator=(const plane& arg1) {
		set(arg1);
		return *this;
	}
	// assign improperPlane 
	inline mv& mv::operator=(const improperPlane& arg1) {
		set(arg1);
		return *this;
	}
	// assign rotor 
	inline mv& mv::operator=(const rotor& arg1) {
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
	// assign __e0_ct__ 
	inline mv& mv::operator=(const __e0_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e0i_ct__ 
	inline mv& mv::operator=(const __e0i_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __I4i_ct__ 
	inline mv& mv::operator=(const __I4i_ct__& arg1) {
		set(arg1);
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
			m_c[0] = arg1.m_c[gidx + 0];
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
			m_c[0] = arg1.m_c[gidx + 1];
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
			m_c[0] = arg1.m_c[gidx + 2];
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
	inline void e0_t::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void e0_t::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;

	}


	// set to copy
	inline void e0_t::set(const e0_t &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void e0_t::set(__e0_t_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void e0_t::set(__e0_t_coordinates__, Float c_e0) {
		// set coordinates
		m_c[0] = c_e0;

	}

	// set to mv 
	inline void e0_t::set(const mv & arg1) {

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
	inline e0_t &e0_t::operator=(const e0_t &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline e0_t &e0_t::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline e0_t &e0_t::operator=(Float scalarVal) {
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
	inline void vector::set() {
		// set coordinates to 0
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void vector::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void vector::set(const vector &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void vector::set(__vector_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void vector::set(__vector_coordinates__, Float c_e1, Float c_e2, Float c_e3) {
		// set coordinates
		m_c[0] = c_e1;
		m_c[1] = c_e2;
		m_c[2] = c_e3;

	}

	// set to mv 
	inline void vector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}





	// assign copy
	inline vector &vector::operator=(const vector &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline vector &vector::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline vector &vector::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void point::set() {
		// set coordinates to 0
		mv_zero(m_c, 4);

	}

	// set to scalar 
	inline void point::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;
		m_c[3] = (Float)0.0;

	}


	// set to copy
	inline void point::set(const point &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 4);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];
		m_c[3] = arg1.m_c[3];

	}

	// set to pointer to coordinates
	inline void point::set(__point_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 4);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];
		m_c[3] = coordinates[3];

	}

	// set to 'coordinates specified' 
	inline void point::set(__point_coordinates__, Float c_e1, Float c_e2, Float c_e3, Float c_e0) {
		// set coordinates
		m_c[0] = c_e1;
		m_c[1] = c_e2;
		m_c[2] = c_e3;
		m_c[3] = c_e0;

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
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
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
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void normalizedPoint::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void normalizedPoint::set(const normalizedPoint &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void normalizedPoint::set(__normalizedPoint_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void normalizedPoint::set(__normalizedPoint_coordinates__, Float c_e1, Float c_e2, Float c_e3) {
		// set coordinates
		m_c[0] = c_e1;
		m_c[1] = c_e2;
		m_c[2] = c_e3;

	}

	// set to mv 
	inline void normalizedPoint::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
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
	inline void line::set(__line_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1, Float c_e1e0, Float c_e2e0, Float c_e3e0) {
		// set coordinates
		m_c[0] = c_e1e2;
		m_c[1] = c_e2e3;
		m_c[2] = c_e3e1;
		m_c[3] = c_e1e0;
		m_c[4] = c_e2e0;
		m_c[5] = c_e3e0;

	}

	// set to mv 
	inline void line::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 4;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
			m_c[5] = arg1.m_c[gidx + 5];
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
	inline void improperLine::set() {
		// set coordinates to 0
		mv_zero(m_c, 3);

	}

	// set to scalar 
	inline void improperLine::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;
		m_c[1] = (Float)0.0;
		m_c[2] = (Float)0.0;

	}


	// set to copy
	inline void improperLine::set(const improperLine &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 3);
		m_c[0] = arg1.m_c[0];
		m_c[1] = arg1.m_c[1];
		m_c[2] = arg1.m_c[2];

	}

	// set to pointer to coordinates
	inline void improperLine::set(__improperLine_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 3);
		m_c[0] = coordinates[0];
		m_c[1] = coordinates[1];
		m_c[2] = coordinates[2];

	}

	// set to 'coordinates specified' 
	inline void improperLine::set(__improperLine_coordinates__, Float c_e1e2, Float c_e2e3, Float c_e3e1) {
		// set coordinates
		m_c[0] = c_e1e2;
		m_c[1] = c_e2e3;
		m_c[2] = c_e3e1;

	}

	// set to mv 
	inline void improperLine::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 4;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}





	// assign copy
	inline improperLine &improperLine::operator=(const improperLine &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline improperLine &improperLine::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline improperLine &improperLine::operator=(Float scalarVal) {
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
	inline void plane::set(__plane_coordinates__, Float c_e1e2e3, Float c_e1e2e0, Float c_e2e3e0, Float c_e3e1e0) {
		// set coordinates
		m_c[0] = c_e1e2e3;
		m_c[1] = c_e1e2e0;
		m_c[2] = c_e2e3e0;
		m_c[3] = c_e3e1e0;

	}

	// set to mv 
	inline void plane::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 4;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 6;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
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
	inline void improperPlane::set() {
		// set coordinates to 0
		mv_zero(m_c, 1);

	}

	// set to scalar 
	inline void improperPlane::set(Float s) {
		// set coordinates 0, except for scalar (if any)
		m_c[0] = (Float)0.0;

	}


	// set to copy
	inline void improperPlane::set(const improperPlane &arg1) {
		// copy coordinates
		//mv_memcpy(m_c, arg1.m_c, 1);
		m_c[0] = arg1.m_c[0];

	}

	// set to pointer to coordinates
	inline void improperPlane::set(__improperPlane_coordinates__, const Float *coordinates) {
		// copy coordinates
		//mv_memcpy(m_c, coordinates, 1);
		m_c[0] = coordinates[0];

	}

	// set to 'coordinates specified' 
	inline void improperPlane::set(__improperPlane_coordinates__, Float c_e1e2e3) {
		// set coordinates
		m_c[0] = c_e1e2e3;

	}

	// set to mv 
	inline void improperPlane::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 4;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 6;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}





	// assign copy
	inline improperPlane &improperPlane::operator=(const improperPlane &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline improperPlane &improperPlane::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline improperPlane &improperPlane::operator=(Float scalarVal) {
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
			gidx += 4;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
			m_c[3] = arg1.m_c[gidx + 2];
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
	inline void __e0_ct__::set() {
		// set coordinates to 0
	}

	// set to scalar 
	inline void __e0_ct__::set(Float s) {
		// set coordinates 0, except for scalar (if any)

	}


	// set to copy
	inline void __e0_ct__::set(const __e0_ct__ &arg1) {
	}

	// set to pointer to coordinates
	inline void __e0_ct__::set(____e0_ct___coordinates__, const Float *coordinates) {
		// copy coordinates
	}

	// set to 'coordinates specified' 
	inline void __e0_ct__::set(____e0_ct___coordinates__) {
		// set coordinates

	}

	// set to mv 
	inline void __e0_ct__::set(const mv & arg1) {



	}





	// assign copy
	inline __e0_ct__ &__e0_ct__::operator=(const __e0_ct__ &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline __e0_ct__ &__e0_ct__::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline __e0_ct__ &__e0_ct__::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void __e0i_ct__::set() {
		// set coordinates to 0
	}

	// set to scalar 
	inline void __e0i_ct__::set(Float s) {
		// set coordinates 0, except for scalar (if any)

	}


	// set to copy
	inline void __e0i_ct__::set(const __e0i_ct__ &arg1) {
	}

	// set to pointer to coordinates
	inline void __e0i_ct__::set(____e0i_ct___coordinates__, const Float *coordinates) {
		// copy coordinates
	}

	// set to 'coordinates specified' 
	inline void __e0i_ct__::set(____e0i_ct___coordinates__) {
		// set coordinates

	}

	// set to mv 
	inline void __e0i_ct__::set(const mv & arg1) {



	}





	// assign copy
	inline __e0i_ct__ &__e0i_ct__::operator=(const __e0i_ct__ &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline __e0i_ct__ &__e0i_ct__::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline __e0i_ct__ &__e0i_ct__::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}






	// set to zero
	inline void __I4i_ct__::set() {
		// set coordinates to 0
	}

	// set to scalar 
	inline void __I4i_ct__::set(Float s) {
		// set coordinates 0, except for scalar (if any)

	}


	// set to copy
	inline void __I4i_ct__::set(const __I4i_ct__ &arg1) {
	}

	// set to pointer to coordinates
	inline void __I4i_ct__::set(____I4i_ct___coordinates__, const Float *coordinates) {
		// copy coordinates
	}

	// set to 'coordinates specified' 
	inline void __I4i_ct__::set(____I4i_ct___coordinates__) {
		// set coordinates

	}

	// set to mv 
	inline void __I4i_ct__::set(const mv & arg1) {



	}





	// assign copy
	inline __I4i_ct__ &__I4i_ct__::operator=(const __I4i_ct__ &arg1) {
		set(arg1);
		return *this;
	}

	// assign general multivector
	inline __I4i_ct__ &__I4i_ct__::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar
	inline __I4i_ct__ &__I4i_ct__::operator=(Float scalarVal) {
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
		mv_memcpy(m_c, arg1.m_c, 69);
	}

	// set to scalar
	inline void om::set(Float scalarVal) {
		h3ga::__G2_GENERATED__::set(*this, point(point_e1_e2_e3_e0, scalarVal, (Float)0, (Float)0, (Float)0), point(point_e1_e2_e3_e0, (Float)0, scalarVal, (Float)0, (Float)0), point(point_e1_e2_e3_e0, (Float)0, (Float)0, scalarVal, (Float)0), point(point_e1_e2_e3_e0, (Float)0, (Float)0, (Float)0, scalarVal));
	}

	// set to coordinates 
	inline void om::set(const Float *coordinates) {
		mv_memcpy(m_c, coordinates, 69);
	}

	// set from basis vectors array
	inline void om::set(const point *vectors) {
		h3ga::__G2_GENERATED__::set(*this, vectors[0], vectors[1], vectors[2], vectors[3]);
	}


	// set from basis vectors 
	inline void om::set(const point & image_of_e1, const point & image_of_e2, const point & image_of_e3, const point & image_of_e0) {
		h3ga::__G2_GENERATED__::set(*this, image_of_e1, image_of_e2, image_of_e3, image_of_e0);
	}


	// set by coordinates, transpose
	inline void om::set(const Float *coordinates, bool transpose) {
		if (transpose) {
			m_c[0] = coordinates[0];
			m_c[4] = coordinates[1];
			m_c[8] = coordinates[2];
			m_c[12] = coordinates[3];
			m_c[1] = coordinates[4];
			m_c[5] = coordinates[5];
			m_c[9] = coordinates[6];
			m_c[13] = coordinates[7];
			m_c[2] = coordinates[8];
			m_c[6] = coordinates[9];
			m_c[10] = coordinates[10];
			m_c[14] = coordinates[11];
			m_c[3] = coordinates[12];
			m_c[7] = coordinates[13];
			m_c[11] = coordinates[14];
			m_c[15] = coordinates[15];
			m_c[16] = coordinates[16];
			m_c[22] = coordinates[17];
			m_c[28] = coordinates[18];
			m_c[34] = coordinates[19];
			m_c[40] = coordinates[20];
			m_c[46] = coordinates[21];
			m_c[17] = coordinates[22];
			m_c[23] = coordinates[23];
			m_c[29] = coordinates[24];
			m_c[35] = coordinates[25];
			m_c[41] = coordinates[26];
			m_c[47] = coordinates[27];
			m_c[18] = coordinates[28];
			m_c[24] = coordinates[29];
			m_c[30] = coordinates[30];
			m_c[36] = coordinates[31];
			m_c[42] = coordinates[32];
			m_c[48] = coordinates[33];
			m_c[19] = coordinates[34];
			m_c[25] = coordinates[35];
			m_c[31] = coordinates[36];
			m_c[37] = coordinates[37];
			m_c[43] = coordinates[38];
			m_c[49] = coordinates[39];
			m_c[20] = coordinates[40];
			m_c[26] = coordinates[41];
			m_c[32] = coordinates[42];
			m_c[38] = coordinates[43];
			m_c[44] = coordinates[44];
			m_c[50] = coordinates[45];
			m_c[21] = coordinates[46];
			m_c[27] = coordinates[47];
			m_c[33] = coordinates[48];
			m_c[39] = coordinates[49];
			m_c[45] = coordinates[50];
			m_c[51] = coordinates[51];
			m_c[52] = coordinates[52];
			m_c[56] = coordinates[53];
			m_c[60] = coordinates[54];
			m_c[64] = coordinates[55];
			m_c[53] = coordinates[56];
			m_c[57] = coordinates[57];
			m_c[61] = coordinates[58];
			m_c[65] = coordinates[59];
			m_c[54] = coordinates[60];
			m_c[58] = coordinates[61];
			m_c[62] = coordinates[62];
			m_c[66] = coordinates[63];
			m_c[55] = coordinates[64];
			m_c[59] = coordinates[65];
			m_c[63] = coordinates[66];
			m_c[67] = coordinates[67];
			m_c[68] = coordinates[68];
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
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline e1_t operator+=(e1_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline e2_t operator+=(e2_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline e3_t operator+=(e3_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline e0_t operator+=(e0_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline scalar operator+=(scalar& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline vector operator+=(vector& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline point operator+=(point& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator+=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline line operator+=(line& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline improperLine operator+=(improperLine& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline plane operator+=(plane& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline improperPlane operator+=(improperPlane& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline rotor operator+=(rotor& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator+=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator+=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator+=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline __e0_ct__ operator+=(__e0_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline __e0i_ct__ operator+=(__e0i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline __I4i_ct__ operator+=(__I4i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::add(arg1, arg2));
		return arg1;
	}
	inline mv operator+(const mv& arg1, const mv& arg2) {
		return ::h3ga::add(arg1, arg2);
	}
	inline mv operator-=(mv& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline e1_t operator-=(e1_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline e2_t operator-=(e2_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline e3_t operator-=(e3_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline e0_t operator-=(e0_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline scalar operator-=(scalar& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline vector operator-=(vector& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline point operator-=(point& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator-=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline line operator-=(line& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline improperLine operator-=(improperLine& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline plane operator-=(plane& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline improperPlane operator-=(improperPlane& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline rotor operator-=(rotor& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator-=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator-=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator-=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __e0_ct__ operator-=(__e0_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __e0i_ct__ operator-=(__e0i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline __I4i_ct__ operator-=(__I4i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::subtract(arg1, arg2));
		return arg1;
	}
	inline mv operator-(const mv& arg1, const mv& arg2) {
		return ::h3ga::subtract(arg1, arg2);
	}
	inline mv operator-(const mv& arg1) {
		return ::h3ga::negate(arg1);
	}
	inline mv operator%=(mv& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline e1_t operator%=(e1_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline e2_t operator%=(e2_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline e3_t operator%=(e3_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline e0_t operator%=(e0_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline scalar operator%=(scalar& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline vector operator%=(vector& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline point operator%=(point& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator%=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline line operator%=(line& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline improperLine operator%=(improperLine& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline plane operator%=(plane& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline improperPlane operator%=(improperPlane& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline rotor operator%=(rotor& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator%=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator%=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator%=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __e0_ct__ operator%=(__e0_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __e0i_ct__ operator%=(__e0i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline __I4i_ct__ operator%=(__I4i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::scp(arg1, arg2));
		return arg1;
	}
	inline scalar operator%(const mv& arg1, const mv& arg2) {
		return ::h3ga::scp(arg1, arg2);
	}
	inline mv operator^=(mv& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline e1_t operator^=(e1_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline e2_t operator^=(e2_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline e3_t operator^=(e3_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline e0_t operator^=(e0_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline scalar operator^=(scalar& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline vector operator^=(vector& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline point operator^=(point& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator^=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline line operator^=(line& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline improperLine operator^=(improperLine& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline plane operator^=(plane& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline improperPlane operator^=(improperPlane& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline rotor operator^=(rotor& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator^=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator^=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator^=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline __e0_ct__ operator^=(__e0_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline __e0i_ct__ operator^=(__e0i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline __I4i_ct__ operator^=(__I4i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::op(arg1, arg2));
		return arg1;
	}
	inline mv operator^(const mv& arg1, const mv& arg2) {
		return ::h3ga::op(arg1, arg2);
	}
	inline mv operator*=(mv& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline e1_t operator*=(e1_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline e2_t operator*=(e2_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline e3_t operator*=(e3_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline e0_t operator*=(e0_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline scalar operator*=(scalar& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline vector operator*=(vector& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline point operator*=(point& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator*=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline line operator*=(line& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline improperLine operator*=(improperLine& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline plane operator*=(plane& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline improperPlane operator*=(improperPlane& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline rotor operator*=(rotor& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator*=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator*=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator*=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __e0_ct__ operator*=(__e0_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __e0i_ct__ operator*=(__e0i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline __I4i_ct__ operator*=(__I4i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::gp(arg1, arg2));
		return arg1;
	}
	inline mv operator*(const mv& arg1, const mv& arg2) {
		return ::h3ga::gp(arg1, arg2);
	}
	inline mv operator<<=(mv& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline e1_t operator<<=(e1_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline e2_t operator<<=(e2_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline e3_t operator<<=(e3_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline e0_t operator<<=(e0_t& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline scalar operator<<=(scalar& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline vector operator<<=(vector& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline point operator<<=(point& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline normalizedPoint operator<<=(normalizedPoint& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline line operator<<=(line& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline improperLine operator<<=(improperLine& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline plane operator<<=(plane& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline improperPlane operator<<=(improperPlane& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline rotor operator<<=(rotor& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __e1_ct__ operator<<=(__e1_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __e2_ct__ operator<<=(__e2_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __e3_ct__ operator<<=(__e3_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __e0_ct__ operator<<=(__e0_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __e0i_ct__ operator<<=(__e0i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline __I4i_ct__ operator<<=(__I4i_ct__& arg1, const mv& arg2) {
		arg1.set(::h3ga::lcont(arg1, arg2));
		return arg1;
	}
	inline mv operator<<(const mv& arg1, const mv& arg2) {
		return ::h3ga::lcont(arg1, arg2);
	}
	inline mv operator*(const mv& arg1) {
		return ::h3ga::dual(arg1);
	}
	inline mv operator!(const mv& arg1) {
		return ::h3ga::inverse(arg1);
	}
	inline mv operator~(const mv& arg1) {
		return ::h3ga::reverse(arg1);
	}


	// G2 functions:
	inline mv lcont(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_1__[16] ;
		mv_zero(__tmp_coord_array_1__, 16);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[5] ;
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

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[0] += ((__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[5] += (__y_xpd__[2][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[6] += (__y_xpd__[2][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[7] += (__y_xpd__[2][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[8] += (__y_xpd__[2][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[9] += (__y_xpd__[2][4] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[10] += (__y_xpd__[2][5] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[1] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][3]) + (__x_xpd__[1][2] * __y_xpd__[2][2]));
				__tmp_coord_array_1__[2] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (__x_xpd__[1][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]));
				__tmp_coord_array_1__[3] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[2][2]) + (__x_xpd__[1][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][5]));
				__tmp_coord_array_1__[4] += ((__x_xpd__[1][2] * __y_xpd__[2][5]) + (__x_xpd__[1][0] * __y_xpd__[2][3]) + (__x_xpd__[1][1] * __y_xpd__[2][4]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[0] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[11] += (__y_xpd__[3][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[12] += (__y_xpd__[3][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[13] += (__y_xpd__[3][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[14] += (__y_xpd__[3][3] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[5] += ((__x_xpd__[1][2] * __y_xpd__[3][0]) + (__x_xpd__[1][3] * __y_xpd__[3][1]));
				__tmp_coord_array_1__[6] += ((__x_xpd__[1][3] * __y_xpd__[3][2]) + (__x_xpd__[1][0] * __y_xpd__[3][0]));
				__tmp_coord_array_1__[7] += ((__x_xpd__[1][1] * __y_xpd__[3][0]) + (__x_xpd__[1][3] * __y_xpd__[3][3]));
				__tmp_coord_array_1__[8] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]) + (__x_xpd__[1][2] * __y_xpd__[3][3]));
				__tmp_coord_array_1__[9] += ((__x_xpd__[1][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]));
				__tmp_coord_array_1__[10] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][3]) + (__x_xpd__[1][1] * __y_xpd__[3][2]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[1] += ((__x_xpd__[2][5] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][0]));
				__tmp_coord_array_1__[2] += ((__x_xpd__[2][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]));
				__tmp_coord_array_1__[3] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][3]) + (__x_xpd__[2][4] * __y_xpd__[3][2]));
				__tmp_coord_array_1__[4] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[0] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]));

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[15] += (__y_xpd__[4][0] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[11] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[12] += (__x_xpd__[1][2] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[13] += (__x_xpd__[1][0] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[14] += (__x_xpd__[1][1] * __y_xpd__[4][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[5] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[6] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[7] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[8] += (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[9] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[10] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[1] += (__x_xpd__[3][2] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[2] += (__x_xpd__[3][3] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[3] += (__x_xpd__[3][1] * __y_xpd__[4][0]);
				__tmp_coord_array_1__[4] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[4][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_1__[0] += (__x_xpd__[4][0] * __y_xpd__[4][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_1__);
		return __temp_var_1__;
	}
	inline scalar scp(const mv& x, const mv& y) {
		scalar __temp_var_1__;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[5] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 2) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 4) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]));

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 8) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]));

			}

		}
		if (((x.m_gu & 16) != 0)) {
			if (((y.m_gu & 16) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[4][0] * __y_xpd__[4][0]);

			}

		}
		return __temp_var_1__;
	}
	inline scalar extract_coord(const mv& x, const mv& y) {
		scalar __temp_var_1__;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[5] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 2) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 4) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[2][5] * __y_xpd__[2][5]) + (__x_xpd__[2][2] * __y_xpd__[2][2]) + (__x_xpd__[2][1] * __y_xpd__[2][1]) + (__x_xpd__[2][3] * __y_xpd__[2][3]) + (__x_xpd__[2][4] * __y_xpd__[2][4]) + (__x_xpd__[2][0] * __y_xpd__[2][0]));

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 8) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[3][0] * __y_xpd__[3][0]) + (__x_xpd__[3][1] * __y_xpd__[3][1]) + (__x_xpd__[3][3] * __y_xpd__[3][3]) + (__x_xpd__[3][2] * __y_xpd__[3][2]));

			}

		}
		if (((x.m_gu & 16) != 0)) {
			if (((y.m_gu & 16) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[4][0] * __y_xpd__[4][0]);

			}

		}
		return __temp_var_1__;
	}
	inline mv gp(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_2__[16] ;
		mv_zero(__tmp_coord_array_2__, 16);
		const float* __y_xpd__[5] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[4] += (__x_xpd__[1][3] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[5] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[6] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[7] += (__x_xpd__[2][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[8] += (__x_xpd__[2][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[9] += (__x_xpd__[2][4] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[10] += (__x_xpd__[2][5] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[11] += (__x_xpd__[3][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[12] += (__x_xpd__[3][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[13] += (__x_xpd__[3][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[14] += (__x_xpd__[3][3] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[15] += (__x_xpd__[4][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_2__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);
				__tmp_coord_array_2__[4] += (__x_xpd__[0][0] * __y_xpd__[1][3]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[0] += ((__x_xpd__[1][3] * __y_xpd__[1][3]) + (__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][1] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[5] += ((__x_xpd__[1][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[1][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[8] += ((__x_xpd__[1][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[9] += ((__x_xpd__[1][1] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[1][2]) + (__x_xpd__[1][2] * __y_xpd__[1][3]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][3]) + (__x_xpd__[2][0] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[2] += ((__x_xpd__[2][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[1][0]) + (__x_xpd__[2][4] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[1][1]) + (__x_xpd__[2][5] * __y_xpd__[1][3]) + (__x_xpd__[2][2] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[2][2] * __y_xpd__[1][1]) + (__x_xpd__[2][1] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[12] += ((__x_xpd__[2][4] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[1][1]) + (__x_xpd__[2][0] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[13] += ((__x_xpd__[2][1] * __y_xpd__[1][3]) + (__x_xpd__[2][5] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[1][0]) + (__x_xpd__[2][3] * __y_xpd__[1][2]) + (__x_xpd__[2][2] * __y_xpd__[1][3]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[5] += ((__x_xpd__[3][1] * __y_xpd__[1][3]) + (__x_xpd__[3][0] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[6] += ((__x_xpd__[3][0] * __y_xpd__[1][0]) + (__x_xpd__[3][2] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[3][0] * __y_xpd__[1][1]) + (__x_xpd__[3][3] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[8] += ((__x_xpd__[3][3] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[9] += ((__x_xpd__[3][1] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[1][0]) + (__x_xpd__[3][2] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][2]) + (__x_xpd__[3][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[11] += (__x_xpd__[4][0] * __y_xpd__[1][3]);
				__tmp_coord_array_2__[12] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][2]);
				__tmp_coord_array_2__[13] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][0]);
				__tmp_coord_array_2__[14] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][1]);

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[5] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_2__[6] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_2__[7] += (__x_xpd__[0][0] * __y_xpd__[2][2]);
				__tmp_coord_array_2__[8] += (__x_xpd__[0][0] * __y_xpd__[2][3]);
				__tmp_coord_array_2__[9] += (__x_xpd__[0][0] * __y_xpd__[2][4]);
				__tmp_coord_array_2__[10] += (__x_xpd__[0][0] * __y_xpd__[2][5]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]) + (__x_xpd__[1][2] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (__x_xpd__[1][0] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[3] += ((__x_xpd__[1][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[4] += ((__x_xpd__[1][0] * __y_xpd__[2][3]) + (__x_xpd__[1][2] * __y_xpd__[2][5]) + (__x_xpd__[1][1] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[1][1] * __y_xpd__[2][2]) + (__x_xpd__[1][2] * __y_xpd__[2][0]) + (__x_xpd__[1][0] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[12] += ((__x_xpd__[1][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[13] += ((__x_xpd__[1][1] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][4]) + (__x_xpd__[1][3] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[14] += ((__x_xpd__[1][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[2][5]) + (__x_xpd__[1][2] * __y_xpd__[2][3]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[0] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[2][2]) + (__x_xpd__[2][4] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][4]) + (__x_xpd__[2][2] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][0]) + (__x_xpd__[2][0] * __y_xpd__[2][2]) + (__x_xpd__[2][5] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[2][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][1]) + (__x_xpd__[2][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][0]) + (__x_xpd__[2][5] * __y_xpd__[2][2]) + (__x_xpd__[2][0] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[9] += ((__x_xpd__[2][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][3]) + (__x_xpd__[2][1] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[2][4]) + (__x_xpd__[2][2] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][2]) + (__x_xpd__[2][4] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[15] += ((__x_xpd__[2][4] * __y_xpd__[2][2]) + (__x_xpd__[2][0] * __y_xpd__[2][5]) + (__x_xpd__[2][5] * __y_xpd__[2][0]) + (__x_xpd__[2][3] * __y_xpd__[2][1]) + (__x_xpd__[2][1] * __y_xpd__[2][3]) + (__x_xpd__[2][2] * __y_xpd__[2][4]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][1]) + (__x_xpd__[3][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[2][5]) + (__x_xpd__[3][1] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[3] += ((__x_xpd__[3][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[11] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[2][2]) + (__x_xpd__[3][0] * __y_xpd__[2][5]) + (__x_xpd__[3][3] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[2][0]) + (__x_xpd__[3][1] * __y_xpd__[2][2]) + (__x_xpd__[3][0] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[2][1]) + (__x_xpd__[3][0] * __y_xpd__[2][4]) + (__x_xpd__[3][2] * __y_xpd__[2][0]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[5] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][5]);
				__tmp_coord_array_2__[6] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][3]);
				__tmp_coord_array_2__[7] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][4]);
				__tmp_coord_array_2__[8] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][1]);
				__tmp_coord_array_2__[9] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][2]);
				__tmp_coord_array_2__[10] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][0]);

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[11] += (__x_xpd__[0][0] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[12] += (__x_xpd__[0][0] * __y_xpd__[3][1]);
				__tmp_coord_array_2__[13] += (__x_xpd__[0][0] * __y_xpd__[3][2]);
				__tmp_coord_array_2__[14] += (__x_xpd__[0][0] * __y_xpd__[3][3]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[5] += ((__x_xpd__[1][3] * __y_xpd__[3][1]) + (__x_xpd__[1][2] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[6] += ((__x_xpd__[1][3] * __y_xpd__[3][2]) + (__x_xpd__[1][0] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[1][1] * __y_xpd__[3][0]) + (__x_xpd__[1][3] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]) + (__x_xpd__[1][2] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[9] += ((__x_xpd__[1][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][3]) + (__x_xpd__[1][1] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[15] += ((__x_xpd__[1][0] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]) + (__x_xpd__[1][2] * __y_xpd__[3][1]) + (__x_xpd__[1][1] * __y_xpd__[3][3]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[3][0]) + (__x_xpd__[2][5] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[2] += ((__x_xpd__[2][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[3][0]) + (__x_xpd__[2][4] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[2][3] * __y_xpd__[3][2]) + (__x_xpd__[2][5] * __y_xpd__[3][1]) + (__x_xpd__[2][4] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[3][0]) + (__x_xpd__[2][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][0]) + (__x_xpd__[2][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[14] += ((__x_xpd__[2][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][2]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[0] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[5] += ((__x_xpd__[3][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[6] += ((__x_xpd__[3][1] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[3][2]) + (__x_xpd__[3][2] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[3][2]) + (__x_xpd__[3][2] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[9] += ((__x_xpd__[3][3] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[3][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][1]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[1] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][2]);
				__tmp_coord_array_2__[2] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][3]);
				__tmp_coord_array_2__[3] += (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][1]);
				__tmp_coord_array_2__[4] += (__x_xpd__[4][0] * __y_xpd__[3][0]);

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[15] += (__x_xpd__[0][0] * __y_xpd__[4][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[11] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[12] += (__x_xpd__[1][2] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[13] += (__x_xpd__[1][0] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[14] += (__x_xpd__[1][1] * __y_xpd__[4][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[5] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[6] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[7] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[8] += (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[9] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[10] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[3][2] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[3][3] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[3] += (__x_xpd__[3][1] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[4] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[4][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[0] += (__x_xpd__[4][0] * __y_xpd__[4][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_2__);
		return __temp_var_1__;
	}
	inline mv op(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_3__[16] ;
		mv_zero(__tmp_coord_array_3__, 16);
		const float* __y_xpd__[5] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[4] += (__x_xpd__[1][3] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[5] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[6] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[7] += (__x_xpd__[2][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[8] += (__x_xpd__[2][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[9] += (__x_xpd__[2][4] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[10] += (__x_xpd__[2][5] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[11] += (__x_xpd__[3][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[12] += (__x_xpd__[3][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[13] += (__x_xpd__[3][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[14] += (__x_xpd__[3][3] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[15] += (__x_xpd__[4][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_3__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);
				__tmp_coord_array_3__[4] += (__x_xpd__[0][0] * __y_xpd__[1][3]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[5] += ((__x_xpd__[1][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[6] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[1][2]) + (__x_xpd__[1][2] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[8] += ((__x_xpd__[1][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[1][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][2]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[11] += ((__x_xpd__[2][2] * __y_xpd__[1][1]) + (__x_xpd__[2][0] * __y_xpd__[1][2]) + (__x_xpd__[2][1] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[2][4] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[2][1] * __y_xpd__[1][3]) + (__x_xpd__[2][5] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[1][0]) + (__x_xpd__[2][3] * __y_xpd__[1][2]) + (__x_xpd__[2][2] * __y_xpd__[1][3]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[15] += ((__x_xpd__[3][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][1]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[5] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_3__[6] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_3__[7] += (__x_xpd__[0][0] * __y_xpd__[2][2]);
				__tmp_coord_array_3__[8] += (__x_xpd__[0][0] * __y_xpd__[2][3]);
				__tmp_coord_array_3__[9] += (__x_xpd__[0][0] * __y_xpd__[2][4]);
				__tmp_coord_array_3__[10] += (__x_xpd__[0][0] * __y_xpd__[2][5]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[11] += ((__x_xpd__[1][1] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][1]) + (__x_xpd__[1][2] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[1][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[13] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][4]) + (__x_xpd__[1][1] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][2]) + (__x_xpd__[1][2] * __y_xpd__[2][3]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[15] += ((__x_xpd__[2][3] * __y_xpd__[2][1]) + (__x_xpd__[2][5] * __y_xpd__[2][0]) + (__x_xpd__[2][1] * __y_xpd__[2][3]) + (__x_xpd__[2][0] * __y_xpd__[2][5]) + (__x_xpd__[2][4] * __y_xpd__[2][2]) + (__x_xpd__[2][2] * __y_xpd__[2][4]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[11] += (__x_xpd__[0][0] * __y_xpd__[3][0]);
				__tmp_coord_array_3__[12] += (__x_xpd__[0][0] * __y_xpd__[3][1]);
				__tmp_coord_array_3__[13] += (__x_xpd__[0][0] * __y_xpd__[3][2]);
				__tmp_coord_array_3__[14] += (__x_xpd__[0][0] * __y_xpd__[3][3]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][3]) + (__x_xpd__[1][0] * __y_xpd__[3][2]) + (__x_xpd__[1][2] * __y_xpd__[3][1]));

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[15] += (__x_xpd__[0][0] * __y_xpd__[4][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_3__);
		return __temp_var_1__;
	}
	inline mv add(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_4__[16] ;
		mv_zero(__tmp_coord_array_4__, 16);
		const float* __y_xpd__[5] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_4__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_4__[1] += __x_xpd__[1][0];
			__tmp_coord_array_4__[2] += __x_xpd__[1][1];
			__tmp_coord_array_4__[3] += __x_xpd__[1][2];
			__tmp_coord_array_4__[4] += __x_xpd__[1][3];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_4__[5] += __x_xpd__[2][0];
			__tmp_coord_array_4__[6] += __x_xpd__[2][1];
			__tmp_coord_array_4__[7] += __x_xpd__[2][2];
			__tmp_coord_array_4__[8] += __x_xpd__[2][3];
			__tmp_coord_array_4__[9] += __x_xpd__[2][4];
			__tmp_coord_array_4__[10] += __x_xpd__[2][5];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_4__[11] += __x_xpd__[3][0];
			__tmp_coord_array_4__[12] += __x_xpd__[3][1];
			__tmp_coord_array_4__[13] += __x_xpd__[3][2];
			__tmp_coord_array_4__[14] += __x_xpd__[3][3];

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_4__[15] += __x_xpd__[4][0];

		}
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_4__[0] += __y_xpd__[0][0];

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_4__[1] += __y_xpd__[1][0];
			__tmp_coord_array_4__[2] += __y_xpd__[1][1];
			__tmp_coord_array_4__[3] += __y_xpd__[1][2];
			__tmp_coord_array_4__[4] += __y_xpd__[1][3];

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_4__[5] += __y_xpd__[2][0];
			__tmp_coord_array_4__[6] += __y_xpd__[2][1];
			__tmp_coord_array_4__[7] += __y_xpd__[2][2];
			__tmp_coord_array_4__[8] += __y_xpd__[2][3];
			__tmp_coord_array_4__[9] += __y_xpd__[2][4];
			__tmp_coord_array_4__[10] += __y_xpd__[2][5];

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_4__[11] += __y_xpd__[3][0];
			__tmp_coord_array_4__[12] += __y_xpd__[3][1];
			__tmp_coord_array_4__[13] += __y_xpd__[3][2];
			__tmp_coord_array_4__[14] += __y_xpd__[3][3];

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_4__[15] += __y_xpd__[4][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_4__);
		return __temp_var_1__;
	}
	inline mv subtract(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_5__[16] ;
		mv_zero(__tmp_coord_array_5__, 16);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[5] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_5__[0] += (-1.0f * __y_xpd__[0][0]);

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_5__[1] += (-1.0f * __y_xpd__[1][0]);
			__tmp_coord_array_5__[2] += (-1.0f * __y_xpd__[1][1]);
			__tmp_coord_array_5__[3] += (-1.0f * __y_xpd__[1][2]);
			__tmp_coord_array_5__[4] += (-1.0f * __y_xpd__[1][3]);

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_5__[5] += (-1.0f * __y_xpd__[2][0]);
			__tmp_coord_array_5__[6] += (-1.0f * __y_xpd__[2][1]);
			__tmp_coord_array_5__[7] += (-1.0f * __y_xpd__[2][2]);
			__tmp_coord_array_5__[8] += (-1.0f * __y_xpd__[2][3]);
			__tmp_coord_array_5__[9] += (-1.0f * __y_xpd__[2][4]);
			__tmp_coord_array_5__[10] += (-1.0f * __y_xpd__[2][5]);

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_5__[11] += (-1.0f * __y_xpd__[3][0]);
			__tmp_coord_array_5__[12] += (-1.0f * __y_xpd__[3][1]);
			__tmp_coord_array_5__[13] += (-1.0f * __y_xpd__[3][2]);
			__tmp_coord_array_5__[14] += (-1.0f * __y_xpd__[3][3]);

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_5__[15] += (-1.0f * __y_xpd__[4][0]);

		}
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_5__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_5__[1] += __x_xpd__[1][0];
			__tmp_coord_array_5__[2] += __x_xpd__[1][1];
			__tmp_coord_array_5__[3] += __x_xpd__[1][2];
			__tmp_coord_array_5__[4] += __x_xpd__[1][3];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_5__[5] += __x_xpd__[2][0];
			__tmp_coord_array_5__[6] += __x_xpd__[2][1];
			__tmp_coord_array_5__[7] += __x_xpd__[2][2];
			__tmp_coord_array_5__[8] += __x_xpd__[2][3];
			__tmp_coord_array_5__[9] += __x_xpd__[2][4];
			__tmp_coord_array_5__[10] += __x_xpd__[2][5];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_5__[11] += __x_xpd__[3][0];
			__tmp_coord_array_5__[12] += __x_xpd__[3][1];
			__tmp_coord_array_5__[13] += __x_xpd__[3][2];
			__tmp_coord_array_5__[14] += __x_xpd__[3][3];

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_5__[15] += __x_xpd__[4][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_5__);
		return __temp_var_1__;
	}
	inline scalar norm_e2(const mv& x) {
		scalar __temp_var_1__;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][3] * __x_xpd__[1][3]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][4] * __x_xpd__[2][4]));

		}
		if (((x.m_gu & 8) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][3] * __x_xpd__[3][3]));

		}
		if (((x.m_gu & 16) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[4][0] * __x_xpd__[4][0]);

		}
		return __temp_var_1__;
	}
	inline scalar norm_e(const mv& x) {
		scalar e2;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += ((__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][4] * __x_xpd__[2][4]));

		}
		if (((x.m_gu & 8) != 0)) {
			e2.m_c[0] += ((__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][0] * __x_xpd__[3][0]));

		}
		if (((x.m_gu & 16) != 0)) {
			e2.m_c[0] += (__x_xpd__[4][0] * __x_xpd__[4][0]);

		}
		return scalar(scalar_scalar, sqrt(e2.m_c[0]));
	}
	inline mv unit_e(const mv& x) {
		scalar e2;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][3] * __x_xpd__[1][3]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += ((__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][0] * __x_xpd__[2][0]));

		}
		if (((x.m_gu & 8) != 0)) {
			e2.m_c[0] += ((__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][3] * __x_xpd__[3][3]));

		}
		if (((x.m_gu & 16) != 0)) {
			e2.m_c[0] += (__x_xpd__[4][0] * __x_xpd__[4][0]);

		}
		scalar ie;
		ie.m_c[0] = ((char)1 / sqrt(e2.m_c[0]));
		mv __temp_var_1__;
		float __tmp_coord_array_6__[16] ;
		mv_zero(__tmp_coord_array_6__, 16);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_6__[0] += (__x_xpd__[0][0] * ie.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_6__[1] += (__x_xpd__[1][0] * ie.m_c[0]);
			__tmp_coord_array_6__[2] += (__x_xpd__[1][1] * ie.m_c[0]);
			__tmp_coord_array_6__[3] += (__x_xpd__[1][2] * ie.m_c[0]);
			__tmp_coord_array_6__[4] += (__x_xpd__[1][3] * ie.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_6__[5] += (__x_xpd__[2][0] * ie.m_c[0]);
			__tmp_coord_array_6__[6] += (__x_xpd__[2][1] * ie.m_c[0]);
			__tmp_coord_array_6__[7] += (__x_xpd__[2][2] * ie.m_c[0]);
			__tmp_coord_array_6__[8] += (__x_xpd__[2][3] * ie.m_c[0]);
			__tmp_coord_array_6__[9] += (__x_xpd__[2][4] * ie.m_c[0]);
			__tmp_coord_array_6__[10] += (__x_xpd__[2][5] * ie.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_6__[11] += (__x_xpd__[3][0] * ie.m_c[0]);
			__tmp_coord_array_6__[12] += (__x_xpd__[3][1] * ie.m_c[0]);
			__tmp_coord_array_6__[13] += (__x_xpd__[3][2] * ie.m_c[0]);
			__tmp_coord_array_6__[14] += (__x_xpd__[3][3] * ie.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_6__[15] += (__x_xpd__[4][0] * ie.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_6__);
		return __temp_var_1__;
	}
	inline scalar norm_r2(const mv& x) {
		scalar __temp_var_1__;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][3] * __x_xpd__[1][3]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][4] * __x_xpd__[2][4]));

		}
		if (((x.m_gu & 8) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][2] * __x_xpd__[3][2]));

		}
		if (((x.m_gu & 16) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[4][0] * __x_xpd__[4][0]);

		}
		return __temp_var_1__;
	}
	inline scalar norm_r(const mv& x) {
		scalar r2;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += ((__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][4] * __x_xpd__[2][4]));

		}
		if (((x.m_gu & 8) != 0)) {
			r2.m_c[0] += ((__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][1] * __x_xpd__[3][1]));

		}
		if (((x.m_gu & 16) != 0)) {
			r2.m_c[0] += (__x_xpd__[4][0] * __x_xpd__[4][0]);

		}
		return scalar(scalar_scalar, ((((r2.m_c[0] < (char)0)) ? (char)-1 : ((((r2.m_c[0] > (char)0)) ? (char)1 : (char)0))) * sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0])))));
	}
	inline mv unit_r(const mv& x) {
		scalar r2;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][2] * __x_xpd__[1][2]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += ((__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][5] * __x_xpd__[2][5]));

		}
		if (((x.m_gu & 8) != 0)) {
			r2.m_c[0] += ((__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][3] * __x_xpd__[3][3]));

		}
		if (((x.m_gu & 16) != 0)) {
			r2.m_c[0] += (__x_xpd__[4][0] * __x_xpd__[4][0]);

		}
		scalar ir;
		ir.m_c[0] = ((char)1 / sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0]))));
		mv __temp_var_1__;
		float __tmp_coord_array_7__[16] ;
		mv_zero(__tmp_coord_array_7__, 16);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_7__[0] += (__x_xpd__[0][0] * ir.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_7__[1] += (__x_xpd__[1][0] * ir.m_c[0]);
			__tmp_coord_array_7__[2] += (__x_xpd__[1][1] * ir.m_c[0]);
			__tmp_coord_array_7__[3] += (__x_xpd__[1][2] * ir.m_c[0]);
			__tmp_coord_array_7__[4] += (__x_xpd__[1][3] * ir.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_7__[5] += (__x_xpd__[2][0] * ir.m_c[0]);
			__tmp_coord_array_7__[6] += (__x_xpd__[2][1] * ir.m_c[0]);
			__tmp_coord_array_7__[7] += (__x_xpd__[2][2] * ir.m_c[0]);
			__tmp_coord_array_7__[8] += (__x_xpd__[2][3] * ir.m_c[0]);
			__tmp_coord_array_7__[9] += (__x_xpd__[2][4] * ir.m_c[0]);
			__tmp_coord_array_7__[10] += (__x_xpd__[2][5] * ir.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_7__[11] += (__x_xpd__[3][0] * ir.m_c[0]);
			__tmp_coord_array_7__[12] += (__x_xpd__[3][1] * ir.m_c[0]);
			__tmp_coord_array_7__[13] += (__x_xpd__[3][2] * ir.m_c[0]);
			__tmp_coord_array_7__[14] += (__x_xpd__[3][3] * ir.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_7__[15] += (__x_xpd__[4][0] * ir.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_7__);
		return __temp_var_1__;
	}
	inline mv reverse(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_8__[16] ;
		mv_zero(__tmp_coord_array_8__, 16);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_8__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_8__[1] += __x_xpd__[1][0];
			__tmp_coord_array_8__[2] += __x_xpd__[1][1];
			__tmp_coord_array_8__[3] += __x_xpd__[1][2];
			__tmp_coord_array_8__[4] += __x_xpd__[1][3];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_8__[5] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_8__[6] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_8__[7] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_8__[8] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_8__[9] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_8__[10] += (-1.0f * __x_xpd__[2][5]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_8__[11] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_8__[12] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_8__[13] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_8__[14] += (-1.0f * __x_xpd__[3][3]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_8__[15] += __x_xpd__[4][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_8__);
		return __temp_var_1__;
	}
	inline mv negate(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_9__[16] ;
		mv_zero(__tmp_coord_array_9__, 16);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_9__[0] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_9__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_9__[2] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_9__[3] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_9__[4] += (-1.0f * __x_xpd__[1][3]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_9__[5] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_9__[6] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_9__[7] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_9__[8] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_9__[9] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_9__[10] += (-1.0f * __x_xpd__[2][5]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_9__[11] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_9__[12] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_9__[13] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_9__[14] += (-1.0f * __x_xpd__[3][3]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_9__[15] += (-1.0f * __x_xpd__[4][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_9__);
		return __temp_var_1__;
	}
	inline mv dual(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_10__[16] ;
		mv_zero(__tmp_coord_array_10__, 16);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_10__[15] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_10__[11] += (-1.0f * __x_xpd__[1][3]);
			__tmp_coord_array_10__[12] += __x_xpd__[1][2];
			__tmp_coord_array_10__[13] += __x_xpd__[1][0];
			__tmp_coord_array_10__[14] += __x_xpd__[1][1];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_10__[5] += (-1.0f * __x_xpd__[2][5]);
			__tmp_coord_array_10__[6] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_10__[7] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_10__[8] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_10__[9] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_10__[10] += (-1.0f * __x_xpd__[2][0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_10__[1] += __x_xpd__[3][2];
			__tmp_coord_array_10__[2] += __x_xpd__[3][3];
			__tmp_coord_array_10__[3] += __x_xpd__[3][1];
			__tmp_coord_array_10__[4] += (-1.0f * __x_xpd__[3][0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_10__[0] += __x_xpd__[4][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_10__);
		return __temp_var_1__;
	}
	inline mv undual(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_11__[16] ;
		mv_zero(__tmp_coord_array_11__, 16);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_11__[15] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_11__[11] += (-1.0f * __x_xpd__[1][3]);
			__tmp_coord_array_11__[12] += __x_xpd__[1][2];
			__tmp_coord_array_11__[13] += __x_xpd__[1][0];
			__tmp_coord_array_11__[14] += __x_xpd__[1][1];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_11__[5] += (-1.0f * __x_xpd__[2][5]);
			__tmp_coord_array_11__[6] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_11__[7] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_11__[8] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_11__[9] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_11__[10] += (-1.0f * __x_xpd__[2][0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_11__[1] += __x_xpd__[3][2];
			__tmp_coord_array_11__[2] += __x_xpd__[3][3];
			__tmp_coord_array_11__[3] += __x_xpd__[3][1];
			__tmp_coord_array_11__[4] += (-1.0f * __x_xpd__[3][0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_11__[0] += __x_xpd__[4][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_11__);
		return __temp_var_1__;
	}
	inline mv inverse(const mv& x) {
		scalar n;
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			n.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			n.m_c[0] += ((__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			n.m_c[0] += ((__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][1] * __x_xpd__[2][1]));

		}
		if (((x.m_gu & 8) != 0)) {
			n.m_c[0] += ((__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][3] * __x_xpd__[3][3]));

		}
		if (((x.m_gu & 16) != 0)) {
			n.m_c[0] += (__x_xpd__[4][0] * __x_xpd__[4][0]);

		}
		scalar in;
		in.m_c[0] = ((char)1 / n.m_c[0]);
		mv __temp_var_1__;
		float __tmp_coord_array_12__[16] ;
		mv_zero(__tmp_coord_array_12__, 16);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_12__[0] += (__x_xpd__[0][0] * in.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_12__[1] += (__x_xpd__[1][0] * in.m_c[0]);
			__tmp_coord_array_12__[2] += (__x_xpd__[1][1] * in.m_c[0]);
			__tmp_coord_array_12__[3] += (__x_xpd__[1][2] * in.m_c[0]);
			__tmp_coord_array_12__[4] += (__x_xpd__[1][3] * in.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_12__[5] += (-1.0f * __x_xpd__[2][0] * in.m_c[0]);
			__tmp_coord_array_12__[6] += (-1.0f * __x_xpd__[2][1] * in.m_c[0]);
			__tmp_coord_array_12__[7] += (-1.0f * __x_xpd__[2][2] * in.m_c[0]);
			__tmp_coord_array_12__[8] += (-1.0f * __x_xpd__[2][3] * in.m_c[0]);
			__tmp_coord_array_12__[9] += (-1.0f * __x_xpd__[2][4] * in.m_c[0]);
			__tmp_coord_array_12__[10] += (-1.0f * __x_xpd__[2][5] * in.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_12__[11] += (-1.0f * __x_xpd__[3][0] * in.m_c[0]);
			__tmp_coord_array_12__[12] += (-1.0f * __x_xpd__[3][1] * in.m_c[0]);
			__tmp_coord_array_12__[13] += (-1.0f * __x_xpd__[3][2] * in.m_c[0]);
			__tmp_coord_array_12__[14] += (-1.0f * __x_xpd__[3][3] * in.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_12__[15] += (__x_xpd__[4][0] * in.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_12__);
		return __temp_var_1__;
	}
	inline mv apply_om(const om& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_13__[16] ;
		mv_zero(__tmp_coord_array_13__, 16);
		const float* __y_xpd__[5] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_13__[1] += ((x.m_c[3] * __y_xpd__[1][3]) + (x.m_c[1] * __y_xpd__[1][1]) + (x.m_c[0] * __y_xpd__[1][0]) + (x.m_c[2] * __y_xpd__[1][2]));
			__tmp_coord_array_13__[2] += ((x.m_c[6] * __y_xpd__[1][2]) + (x.m_c[7] * __y_xpd__[1][3]) + (x.m_c[5] * __y_xpd__[1][1]) + (x.m_c[4] * __y_xpd__[1][0]));
			__tmp_coord_array_13__[3] += ((x.m_c[10] * __y_xpd__[1][2]) + (x.m_c[9] * __y_xpd__[1][1]) + (x.m_c[8] * __y_xpd__[1][0]) + (x.m_c[11] * __y_xpd__[1][3]));
			__tmp_coord_array_13__[4] += ((x.m_c[13] * __y_xpd__[1][1]) + (x.m_c[15] * __y_xpd__[1][3]) + (x.m_c[14] * __y_xpd__[1][2]) + (x.m_c[12] * __y_xpd__[1][0]));

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_13__[5] += ((x.m_c[19] * __y_xpd__[2][3]) + (x.m_c[20] * __y_xpd__[2][4]) + (x.m_c[18] * __y_xpd__[2][2]) + (x.m_c[17] * __y_xpd__[2][1]) + (x.m_c[16] * __y_xpd__[2][0]) + (x.m_c[21] * __y_xpd__[2][5]));
			__tmp_coord_array_13__[6] += ((x.m_c[27] * __y_xpd__[2][5]) + (x.m_c[25] * __y_xpd__[2][3]) + (x.m_c[24] * __y_xpd__[2][2]) + (x.m_c[23] * __y_xpd__[2][1]) + (x.m_c[26] * __y_xpd__[2][4]) + (x.m_c[22] * __y_xpd__[2][0]));
			__tmp_coord_array_13__[7] += ((x.m_c[30] * __y_xpd__[2][2]) + (x.m_c[29] * __y_xpd__[2][1]) + (x.m_c[33] * __y_xpd__[2][5]) + (x.m_c[31] * __y_xpd__[2][3]) + (x.m_c[28] * __y_xpd__[2][0]) + (x.m_c[32] * __y_xpd__[2][4]));
			__tmp_coord_array_13__[8] += ((x.m_c[39] * __y_xpd__[2][5]) + (x.m_c[34] * __y_xpd__[2][0]) + (x.m_c[37] * __y_xpd__[2][3]) + (x.m_c[36] * __y_xpd__[2][2]) + (x.m_c[35] * __y_xpd__[2][1]) + (x.m_c[38] * __y_xpd__[2][4]));
			__tmp_coord_array_13__[9] += ((x.m_c[42] * __y_xpd__[2][2]) + (x.m_c[45] * __y_xpd__[2][5]) + (x.m_c[41] * __y_xpd__[2][1]) + (x.m_c[44] * __y_xpd__[2][4]) + (x.m_c[43] * __y_xpd__[2][3]) + (x.m_c[40] * __y_xpd__[2][0]));
			__tmp_coord_array_13__[10] += ((x.m_c[48] * __y_xpd__[2][2]) + (x.m_c[47] * __y_xpd__[2][1]) + (x.m_c[49] * __y_xpd__[2][3]) + (x.m_c[50] * __y_xpd__[2][4]) + (x.m_c[51] * __y_xpd__[2][5]) + (x.m_c[46] * __y_xpd__[2][0]));

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_13__[11] += ((x.m_c[54] * __y_xpd__[3][2]) + (x.m_c[53] * __y_xpd__[3][1]) + (x.m_c[52] * __y_xpd__[3][0]) + (x.m_c[55] * __y_xpd__[3][3]));
			__tmp_coord_array_13__[12] += ((x.m_c[59] * __y_xpd__[3][3]) + (x.m_c[58] * __y_xpd__[3][2]) + (x.m_c[56] * __y_xpd__[3][0]) + (x.m_c[57] * __y_xpd__[3][1]));
			__tmp_coord_array_13__[13] += ((x.m_c[63] * __y_xpd__[3][3]) + (x.m_c[60] * __y_xpd__[3][0]) + (x.m_c[61] * __y_xpd__[3][1]) + (x.m_c[62] * __y_xpd__[3][2]));
			__tmp_coord_array_13__[14] += ((x.m_c[64] * __y_xpd__[3][0]) + (x.m_c[66] * __y_xpd__[3][2]) + (x.m_c[65] * __y_xpd__[3][1]) + (x.m_c[67] * __y_xpd__[3][3]));

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_13__[15] += (x.m_c[68] * __y_xpd__[4][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_13__);
		return __temp_var_1__;
	}
	inline mv gradeInvolution(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_14__[16] ;
		mv_zero(__tmp_coord_array_14__, 16);
		const float* __x_xpd__[5] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_14__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_14__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_14__[2] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_14__[3] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_14__[4] += (-1.0f * __x_xpd__[1][3]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_14__[5] += __x_xpd__[2][0];
			__tmp_coord_array_14__[6] += __x_xpd__[2][1];
			__tmp_coord_array_14__[7] += __x_xpd__[2][2];
			__tmp_coord_array_14__[8] += __x_xpd__[2][3];
			__tmp_coord_array_14__[9] += __x_xpd__[2][4];
			__tmp_coord_array_14__[10] += __x_xpd__[2][5];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_14__[11] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_14__[12] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_14__[13] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_14__[14] += (-1.0f * __x_xpd__[3][3]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_14__[15] += __x_xpd__[4][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_14__);
		return __temp_var_1__;
	}
	namespace __G2_GENERATED__ {
		inline void set(om& __x__, const point& __image_of_e1__, const point& __image_of_e2__, const point& __image_of_e3__, const point& __image_of_e0__) {
			__x__.m_c[0] = __image_of_e1__.m_c[0];
			__x__.m_c[4] = __image_of_e1__.m_c[1];
			__x__.m_c[8] = __image_of_e1__.m_c[2];
			__x__.m_c[12] = __image_of_e1__.m_c[3];
			__x__.m_c[1] = __image_of_e2__.m_c[0];
			__x__.m_c[5] = __image_of_e2__.m_c[1];
			__x__.m_c[9] = __image_of_e2__.m_c[2];
			__x__.m_c[13] = __image_of_e2__.m_c[3];
			__x__.m_c[2] = __image_of_e3__.m_c[0];
			__x__.m_c[6] = __image_of_e3__.m_c[1];
			__x__.m_c[10] = __image_of_e3__.m_c[2];
			__x__.m_c[14] = __image_of_e3__.m_c[3];
			__x__.m_c[3] = __image_of_e0__.m_c[0];
			__x__.m_c[7] = __image_of_e0__.m_c[1];
			__x__.m_c[11] = __image_of_e0__.m_c[2];
			__x__.m_c[15] = __image_of_e0__.m_c[3];
			__x__.m_c[16] = ((__x__.m_c[5] * __x__.m_c[0]) + (-1.0f * __x__.m_c[1] * __x__.m_c[4]));
			__x__.m_c[22] = ((__x__.m_c[9] * __x__.m_c[4]) + (-1.0f * __x__.m_c[5] * __x__.m_c[8]));
			__x__.m_c[28] = ((__x__.m_c[1] * __x__.m_c[8]) + (-1.0f * __x__.m_c[9] * __x__.m_c[0]));
			__x__.m_c[34] = ((-1.0f * __x__.m_c[1] * __x__.m_c[12]) + (__x__.m_c[13] * __x__.m_c[0]));
			__x__.m_c[40] = ((-1.0f * __x__.m_c[5] * __x__.m_c[12]) + (__x__.m_c[13] * __x__.m_c[4]));
			__x__.m_c[46] = ((__x__.m_c[13] * __x__.m_c[8]) + (-1.0f * __x__.m_c[9] * __x__.m_c[12]));
			__x__.m_c[17] = ((-1.0f * __x__.m_c[2] * __x__.m_c[5]) + (__x__.m_c[6] * __x__.m_c[1]));
			__x__.m_c[23] = ((__x__.m_c[10] * __x__.m_c[5]) + (-1.0f * __x__.m_c[6] * __x__.m_c[9]));
			__x__.m_c[29] = ((__x__.m_c[2] * __x__.m_c[9]) + (-1.0f * __x__.m_c[10] * __x__.m_c[1]));
			__x__.m_c[35] = ((-1.0f * __x__.m_c[2] * __x__.m_c[13]) + (__x__.m_c[14] * __x__.m_c[1]));
			__x__.m_c[41] = ((__x__.m_c[14] * __x__.m_c[5]) + (-1.0f * __x__.m_c[6] * __x__.m_c[13]));
			__x__.m_c[47] = ((__x__.m_c[14] * __x__.m_c[9]) + (-1.0f * __x__.m_c[10] * __x__.m_c[13]));
			__x__.m_c[18] = ((__x__.m_c[2] * __x__.m_c[4]) + (-1.0f * __x__.m_c[6] * __x__.m_c[0]));
			__x__.m_c[24] = ((__x__.m_c[6] * __x__.m_c[8]) + (-1.0f * __x__.m_c[10] * __x__.m_c[4]));
			__x__.m_c[30] = ((-1.0f * __x__.m_c[2] * __x__.m_c[8]) + (__x__.m_c[10] * __x__.m_c[0]));
			__x__.m_c[36] = ((-1.0f * __x__.m_c[14] * __x__.m_c[0]) + (__x__.m_c[2] * __x__.m_c[12]));
			__x__.m_c[42] = ((-1.0f * __x__.m_c[14] * __x__.m_c[4]) + (__x__.m_c[6] * __x__.m_c[12]));
			__x__.m_c[48] = ((-1.0f * __x__.m_c[14] * __x__.m_c[8]) + (__x__.m_c[10] * __x__.m_c[12]));
			__x__.m_c[19] = ((__x__.m_c[7] * __x__.m_c[0]) + (-1.0f * __x__.m_c[3] * __x__.m_c[4]));
			__x__.m_c[25] = ((__x__.m_c[11] * __x__.m_c[4]) + (-1.0f * __x__.m_c[7] * __x__.m_c[8]));
			__x__.m_c[31] = ((__x__.m_c[3] * __x__.m_c[8]) + (-1.0f * __x__.m_c[11] * __x__.m_c[0]));
			__x__.m_c[37] = ((__x__.m_c[15] * __x__.m_c[0]) + (-1.0f * __x__.m_c[3] * __x__.m_c[12]));
			__x__.m_c[43] = ((__x__.m_c[15] * __x__.m_c[4]) + (-1.0f * __x__.m_c[7] * __x__.m_c[12]));
			__x__.m_c[49] = ((-1.0f * __x__.m_c[11] * __x__.m_c[12]) + (__x__.m_c[15] * __x__.m_c[8]));
			__x__.m_c[20] = ((-1.0f * __x__.m_c[3] * __x__.m_c[5]) + (__x__.m_c[7] * __x__.m_c[1]));
			__x__.m_c[26] = ((__x__.m_c[11] * __x__.m_c[5]) + (-1.0f * __x__.m_c[7] * __x__.m_c[9]));
			__x__.m_c[32] = ((-1.0f * __x__.m_c[11] * __x__.m_c[1]) + (__x__.m_c[3] * __x__.m_c[9]));
			__x__.m_c[38] = ((-1.0f * __x__.m_c[3] * __x__.m_c[13]) + (__x__.m_c[15] * __x__.m_c[1]));
			__x__.m_c[44] = ((__x__.m_c[15] * __x__.m_c[5]) + (-1.0f * __x__.m_c[7] * __x__.m_c[13]));
			__x__.m_c[50] = ((__x__.m_c[15] * __x__.m_c[9]) + (-1.0f * __x__.m_c[11] * __x__.m_c[13]));
			__x__.m_c[21] = ((__x__.m_c[7] * __x__.m_c[2]) + (-1.0f * __x__.m_c[3] * __x__.m_c[6]));
			__x__.m_c[27] = ((__x__.m_c[11] * __x__.m_c[6]) + (-1.0f * __x__.m_c[7] * __x__.m_c[10]));
			__x__.m_c[33] = ((-1.0f * __x__.m_c[11] * __x__.m_c[2]) + (__x__.m_c[3] * __x__.m_c[10]));
			__x__.m_c[39] = ((__x__.m_c[15] * __x__.m_c[2]) + (-1.0f * __x__.m_c[3] * __x__.m_c[14]));
			__x__.m_c[45] = ((-1.0f * __x__.m_c[7] * __x__.m_c[14]) + (__x__.m_c[15] * __x__.m_c[6]));
			__x__.m_c[51] = ((-1.0f * __x__.m_c[11] * __x__.m_c[14]) + (__x__.m_c[15] * __x__.m_c[10]));
			__x__.m_c[52] = ((__x__.m_c[30] * __x__.m_c[5]) + (__x__.m_c[18] * __x__.m_c[9]) + (__x__.m_c[24] * __x__.m_c[1]));
			__x__.m_c[56] = ((-1.0f * __x__.m_c[36] * __x__.m_c[5]) + (__x__.m_c[42] * __x__.m_c[1]) + (__x__.m_c[18] * __x__.m_c[13]));
			__x__.m_c[60] = ((__x__.m_c[48] * __x__.m_c[5]) + (__x__.m_c[24] * __x__.m_c[13]) + (-1.0f * __x__.m_c[42] * __x__.m_c[9]));
			__x__.m_c[64] = ((-1.0f * __x__.m_c[48] * __x__.m_c[1]) + (__x__.m_c[36] * __x__.m_c[9]) + (__x__.m_c[30] * __x__.m_c[13]));
			__x__.m_c[53] = ((__x__.m_c[26] * __x__.m_c[0]) + (__x__.m_c[32] * __x__.m_c[4]) + (__x__.m_c[20] * __x__.m_c[8]));
			__x__.m_c[57] = ((__x__.m_c[44] * __x__.m_c[0]) + (-1.0f * __x__.m_c[38] * __x__.m_c[4]) + (__x__.m_c[20] * __x__.m_c[12]));
			__x__.m_c[61] = ((__x__.m_c[26] * __x__.m_c[12]) + (-1.0f * __x__.m_c[44] * __x__.m_c[8]) + (__x__.m_c[50] * __x__.m_c[4]));
			__x__.m_c[65] = ((-1.0f * __x__.m_c[50] * __x__.m_c[0]) + (__x__.m_c[32] * __x__.m_c[12]) + (__x__.m_c[38] * __x__.m_c[8]));
			__x__.m_c[54] = ((__x__.m_c[33] * __x__.m_c[5]) + (__x__.m_c[27] * __x__.m_c[1]) + (__x__.m_c[21] * __x__.m_c[9]));
			__x__.m_c[58] = ((__x__.m_c[45] * __x__.m_c[1]) + (-1.0f * __x__.m_c[39] * __x__.m_c[5]) + (__x__.m_c[21] * __x__.m_c[13]));
			__x__.m_c[62] = ((-1.0f * __x__.m_c[45] * __x__.m_c[9]) + (__x__.m_c[27] * __x__.m_c[13]) + (__x__.m_c[51] * __x__.m_c[5]));
			__x__.m_c[66] = ((__x__.m_c[39] * __x__.m_c[9]) + (__x__.m_c[33] * __x__.m_c[13]) + (-1.0f * __x__.m_c[51] * __x__.m_c[1]));
			__x__.m_c[55] = ((-1.0f * __x__.m_c[33] * __x__.m_c[4]) + (-1.0f * __x__.m_c[27] * __x__.m_c[0]) + (-1.0f * __x__.m_c[21] * __x__.m_c[8]));
			__x__.m_c[59] = ((__x__.m_c[39] * __x__.m_c[4]) + (-1.0f * __x__.m_c[45] * __x__.m_c[0]) + (-1.0f * __x__.m_c[21] * __x__.m_c[12]));
			__x__.m_c[63] = ((-1.0f * __x__.m_c[51] * __x__.m_c[4]) + (-1.0f * __x__.m_c[27] * __x__.m_c[12]) + (__x__.m_c[45] * __x__.m_c[8]));
			__x__.m_c[67] = ((-1.0f * __x__.m_c[39] * __x__.m_c[8]) + (-1.0f * __x__.m_c[33] * __x__.m_c[12]) + (__x__.m_c[51] * __x__.m_c[0]));
			__x__.m_c[68] = ((__x__.m_c[59] * __x__.m_c[9]) + (__x__.m_c[67] * __x__.m_c[5]) + (__x__.m_c[63] * __x__.m_c[1]) + (-1.0f * __x__.m_c[55] * __x__.m_c[13]));
		}
	} /* end of namespace __G2_GENERATED__ */







} // end of namespace h3ga
// post_h_include


#endif //  _GA_h3ga_h_H_
