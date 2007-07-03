
// Generated on 2007-07-03 14:16:17 by G2 0.1 from 'E:\gasandbox\ga_sandbox\libgasandbox\e3ga.gs2'

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

	#ifndef _GA_e3ga_h_H_
	#define _GA_e3ga_h_H_

	namespace e3ga {

	// multivector types:
	enum g2Type {
		MVT_NONE = -1,
			MVT_E1_T = 10,
			MVT_E2_T = 11,
			MVT_E3_T = 12,
			MVT_SCALAR = 13,
			MVT_VECTOR2D = 14,
			MVT_VECTOR = 15,
			MVT_BIVECTOR = 16,
			MVT_TRIVECTOR = 17,
			MVT_ROTOR = 18,
			MVT___E1_CT__ = 19,
			MVT___E2_CT__ = 20,
			MVT___E3_CT__ = 21,
			MVT___I3_CT__ = 22,
			MVT___I3I_CT__ = 23,
			MVT___SYN_SMV___E1_E2_E3_E1E2E3 = 24,
			MVT___SYN_SMV___E1E2F1_0 = 25,
			MVT___SYN_SMV___E1E2 = 26,
			MVT___SYN_SMV___SCALAR_E1E2 = 27,
			MVT___SYN_SMV___E3F_1_0 = 28,
			MVT___SYN_SMV___E1E3_E2E3 = 29,
			MVT___SYN_SMV___SCALAR_E1E3_E2E3 = 30,
			MVT___SYN_SMV___E1E2_E1E3_E2E3_E1E2E3 = 31,
			MVT___SYN_SMV___E1E3F_1_0 = 32,
			MVT___SYN_SMV___E1E3 = 33,
			MVT___SYN_SMV___SCALAR_E1E3 = 34,
			MVT___SYN_SMV___E2E3F1_0 = 35,
			MVT___SYN_SMV___E2E3 = 36,
			MVT___SYN_SMV___SCALAR_E2E3 = 37,
			MVT___SYN_SMV___E2_E3 = 38,
			MVT___SYN_SMV___E1_E3 = 39,
			MVT___SYN_SMV___E2_E3_E1E2E3 = 40,
			MVT___SYN_SMV___E1_E3_E1E2E3 = 41,
			MVT___SYN_SMV___E1_E2_E1E2E3 = 42,
			MVT___SYN_SMV___SCALAR_E1E2_E1E3 = 43,
			MVT___SYN_SMV___SCALAR_E1E2_E2E3 = 44,
			MVT___SYN_SMV___E2F_1_0 = 45,
			MVT___SYN_SMV___E1E2_E1E3 = 46,
			MVT___SYN_SMV___E1E2_E2E3 = 47,
			MVT___SYN_SMV___E1F1_0_E2F1_0 = 48,
			MVT___SYN_SMV___E1F1_0_E2F1_0_E3F1_0 = 49,
			MVT___SYN_SMV___E2_E1F1_0 = 50,
			MVT___SYN_SMV___SCALAR_E1_E2_E3_E1E2E3 = 51,
			MVT___SYN_SMV___E1_E3F1_0 = 52,
			MVT_MV = 8,
			MVT_LAST = 53 
	};

	// outermorphism types:
	enum omType {
		OMT_NONE = -2,
			OMT_OM = 9,
			OMT_LAST = 53 
	};

	// grade definitions that can be joined using the '|' operator:
	const int GRADE_0 = 1;
	const int GRADE_1 = 2;
	const int GRADE_2 = 4;
	const int GRADE_3 = 8;

	// The dimension of the space:
	extern const int mv_spaceDim;

	// Is the metric of the space Euclidean?
	extern const bool mv_metricEuclidean;

	// This array can be used to lookup the number of coordinates for a grade part of a general multivector
	extern const int mv_gradeSize[4];

	// This array can be used to lookup the number of coordinates based on a grade usage bitmap
	extern const int mv_size[16];

	// This array of ASCIIZ strings contains the names of the basis vectors
	extern const char *mv_basisVectorNames[3];

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'what basis vectors are in the basis element at position [x]?
	extern const int mv_basisElements[8][4];

	// This array of integers contains the 'sign' (even/odd permutation of canonical order) of basis elements in the general multivector
	// Use it to answer 'what is the permutation of the coordinate at index [x]'?
	extern const double mv_basisElementSignByIndex[8];

	// This array of integers contains the 'sign' (even/odd permutation of canonical order) of basis elements in the general multivector
	// Use it to answer 'what is the permutation of the coordinate of bitmap [x]'?
	extern const double mv_basisElementSignByBitmap[8];

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'at what index do I find basis element [x] (x = basis vector bitmap)?'
	extern const int mv_basisElementIndexByBitmap[8];

	// This array of integers contains the indices of basis elements in the general multivector
	// Use it to answer: 'what basis element do I find at index [x]'?
	extern const int mv_basisElementBitmapByIndex[8];

	// This array of grade of each basis elements in the general multivector
	// Use it to answer: 'what is the grade of basis element bitmap [x]'?
	extern const int mv_basisElementGradeByBitmap[8];




	/* *************************************************************************** */
	/* *************************** define all classes upfront *************************** */
	/* *************************************************************************** */
	class e1_t;
	class e2_t;
	class e3_t;
	class scalar;
	class vector2D;
	class vector;
	class bivector;
	class trivector;
	class rotor;
	class __e1_ct__;
	class __e2_ct__;
	class __e3_ct__;
	class __I3_ct__;
	class __I3i_ct__;
	class __syn_smv___e1_e2_e3_e1e2e3;
	class __syn_smv___e1e2f1_0;
	class __syn_smv___e1e2;
	class __syn_smv___scalar_e1e2;
	class __syn_smv___e3f_1_0;
	class __syn_smv___e1e3_e2e3;
	class __syn_smv___scalar_e1e3_e2e3;
	class __syn_smv___e1e2_e1e3_e2e3_e1e2e3;
	class __syn_smv___e1e3f_1_0;
	class __syn_smv___e1e3;
	class __syn_smv___scalar_e1e3;
	class __syn_smv___e2e3f1_0;
	class __syn_smv___e2e3;
	class __syn_smv___scalar_e2e3;
	class __syn_smv___e2_e3;
	class __syn_smv___e1_e3;
	class __syn_smv___e2_e3_e1e2e3;
	class __syn_smv___e1_e3_e1e2e3;
	class __syn_smv___e1_e2_e1e2e3;
	class __syn_smv___scalar_e1e2_e1e3;
	class __syn_smv___scalar_e1e2_e2e3;
	class __syn_smv___e2f_1_0;
	class __syn_smv___e1e2_e1e3;
	class __syn_smv___e1e2_e2e3;
	class __syn_smv___e1f1_0_e2f1_0;
	class __syn_smv___e1f1_0_e2f1_0_e3f1_0;
	class __syn_smv___e2_e1f1_0;
	class __syn_smv___scalar_e1_e2_e3_e1e2e3;
	class __syn_smv___e1_e3f1_0;
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
		void save(const char *filename = "E:\\gasandbox\\ga_sandbox\\libgasandbox\\e3ga.gp2", bool append = true);
		void init(const char *filename = "E:\\gasandbox\\ga_sandbox\\libgasandbox\\e3ga.gp2",
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
		/// init from scalar constructor
		inline mv(const scalar &arg1) {
			set(arg1);
		}
		/// init from vector2D constructor
		inline mv(const vector2D &arg1) {
			set(arg1);
		}
		/// init from vector constructor
		inline mv(const vector &arg1) {
			set(arg1);
		}
		/// init from bivector constructor
		inline mv(const bivector &arg1) {
			set(arg1);
		}
		/// init from trivector constructor
		inline mv(const trivector &arg1) {
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
		/// init from __I3_ct__ constructor
		inline mv(const __I3_ct__ &arg1) {
			set(arg1);
		}
		/// init from __I3i_ct__ constructor
		inline mv(const __I3i_ct__ &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1_e2_e3_e1e2e3 constructor
		inline mv(const __syn_smv___e1_e2_e3_e1e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1e2f1_0 constructor
		inline mv(const __syn_smv___e1e2f1_0 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1e2 constructor
		inline mv(const __syn_smv___e1e2 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___scalar_e1e2 constructor
		inline mv(const __syn_smv___scalar_e1e2 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e3f_1_0 constructor
		inline mv(const __syn_smv___e3f_1_0 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1e3_e2e3 constructor
		inline mv(const __syn_smv___e1e3_e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___scalar_e1e3_e2e3 constructor
		inline mv(const __syn_smv___scalar_e1e3_e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1e2_e1e3_e2e3_e1e2e3 constructor
		inline mv(const __syn_smv___e1e2_e1e3_e2e3_e1e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1e3f_1_0 constructor
		inline mv(const __syn_smv___e1e3f_1_0 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1e3 constructor
		inline mv(const __syn_smv___e1e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___scalar_e1e3 constructor
		inline mv(const __syn_smv___scalar_e1e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e2e3f1_0 constructor
		inline mv(const __syn_smv___e2e3f1_0 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e2e3 constructor
		inline mv(const __syn_smv___e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___scalar_e2e3 constructor
		inline mv(const __syn_smv___scalar_e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e2_e3 constructor
		inline mv(const __syn_smv___e2_e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1_e3 constructor
		inline mv(const __syn_smv___e1_e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e2_e3_e1e2e3 constructor
		inline mv(const __syn_smv___e2_e3_e1e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1_e3_e1e2e3 constructor
		inline mv(const __syn_smv___e1_e3_e1e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1_e2_e1e2e3 constructor
		inline mv(const __syn_smv___e1_e2_e1e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___scalar_e1e2_e1e3 constructor
		inline mv(const __syn_smv___scalar_e1e2_e1e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___scalar_e1e2_e2e3 constructor
		inline mv(const __syn_smv___scalar_e1e2_e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e2f_1_0 constructor
		inline mv(const __syn_smv___e2f_1_0 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1e2_e1e3 constructor
		inline mv(const __syn_smv___e1e2_e1e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1e2_e2e3 constructor
		inline mv(const __syn_smv___e1e2_e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1f1_0_e2f1_0 constructor
		inline mv(const __syn_smv___e1f1_0_e2f1_0 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1f1_0_e2f1_0_e3f1_0 constructor
		inline mv(const __syn_smv___e1f1_0_e2f1_0_e3f1_0 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e2_e1f1_0 constructor
		inline mv(const __syn_smv___e2_e1f1_0 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___scalar_e1_e2_e3_e1e2e3 constructor
		inline mv(const __syn_smv___scalar_e1_e2_e3_e1e2e3 &arg1) {
			set(arg1);
		}
		/// init from __syn_smv___e1_e3f1_0 constructor
		inline mv(const __syn_smv___e1_e3f1_0 &arg1) {
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


		/// set to e1_t 
		void set(const e1_t &arg1);
		/// set to e2_t 
		void set(const e2_t &arg1);
		/// set to e3_t 
		void set(const e3_t &arg1);
		/// set to scalar 
		void set(const scalar &arg1);
		/// set to vector2D 
		void set(const vector2D &arg1);
		/// set to vector 
		void set(const vector &arg1);
		/// set to bivector 
		void set(const bivector &arg1);
		/// set to trivector 
		void set(const trivector &arg1);
		/// set to rotor 
		void set(const rotor &arg1);
		/// set to __e1_ct__ 
		void set(const __e1_ct__ &arg1);
		/// set to __e2_ct__ 
		void set(const __e2_ct__ &arg1);
		/// set to __e3_ct__ 
		void set(const __e3_ct__ &arg1);
		/// set to __I3_ct__ 
		void set(const __I3_ct__ &arg1);
		/// set to __I3i_ct__ 
		void set(const __I3i_ct__ &arg1);
		/// set to __syn_smv___e1_e2_e3_e1e2e3 
		void set(const __syn_smv___e1_e2_e3_e1e2e3 &arg1);
		/// set to __syn_smv___e1e2f1_0 
		void set(const __syn_smv___e1e2f1_0 &arg1);
		/// set to __syn_smv___e1e2 
		void set(const __syn_smv___e1e2 &arg1);
		/// set to __syn_smv___scalar_e1e2 
		void set(const __syn_smv___scalar_e1e2 &arg1);
		/// set to __syn_smv___e3f_1_0 
		void set(const __syn_smv___e3f_1_0 &arg1);
		/// set to __syn_smv___e1e3_e2e3 
		void set(const __syn_smv___e1e3_e2e3 &arg1);
		/// set to __syn_smv___scalar_e1e3_e2e3 
		void set(const __syn_smv___scalar_e1e3_e2e3 &arg1);
		/// set to __syn_smv___e1e2_e1e3_e2e3_e1e2e3 
		void set(const __syn_smv___e1e2_e1e3_e2e3_e1e2e3 &arg1);
		/// set to __syn_smv___e1e3f_1_0 
		void set(const __syn_smv___e1e3f_1_0 &arg1);
		/// set to __syn_smv___e1e3 
		void set(const __syn_smv___e1e3 &arg1);
		/// set to __syn_smv___scalar_e1e3 
		void set(const __syn_smv___scalar_e1e3 &arg1);
		/// set to __syn_smv___e2e3f1_0 
		void set(const __syn_smv___e2e3f1_0 &arg1);
		/// set to __syn_smv___e2e3 
		void set(const __syn_smv___e2e3 &arg1);
		/// set to __syn_smv___scalar_e2e3 
		void set(const __syn_smv___scalar_e2e3 &arg1);
		/// set to __syn_smv___e2_e3 
		void set(const __syn_smv___e2_e3 &arg1);
		/// set to __syn_smv___e1_e3 
		void set(const __syn_smv___e1_e3 &arg1);
		/// set to __syn_smv___e2_e3_e1e2e3 
		void set(const __syn_smv___e2_e3_e1e2e3 &arg1);
		/// set to __syn_smv___e1_e3_e1e2e3 
		void set(const __syn_smv___e1_e3_e1e2e3 &arg1);
		/// set to __syn_smv___e1_e2_e1e2e3 
		void set(const __syn_smv___e1_e2_e1e2e3 &arg1);
		/// set to __syn_smv___scalar_e1e2_e1e3 
		void set(const __syn_smv___scalar_e1e2_e1e3 &arg1);
		/// set to __syn_smv___scalar_e1e2_e2e3 
		void set(const __syn_smv___scalar_e1e2_e2e3 &arg1);
		/// set to __syn_smv___e2f_1_0 
		void set(const __syn_smv___e2f_1_0 &arg1);
		/// set to __syn_smv___e1e2_e1e3 
		void set(const __syn_smv___e1e2_e1e3 &arg1);
		/// set to __syn_smv___e1e2_e2e3 
		void set(const __syn_smv___e1e2_e2e3 &arg1);
		/// set to __syn_smv___e1f1_0_e2f1_0 
		void set(const __syn_smv___e1f1_0_e2f1_0 &arg1);
		/// set to __syn_smv___e1f1_0_e2f1_0_e3f1_0 
		void set(const __syn_smv___e1f1_0_e2f1_0_e3f1_0 &arg1);
		/// set to __syn_smv___e2_e1f1_0 
		void set(const __syn_smv___e2_e1f1_0 &arg1);
		/// set to __syn_smv___scalar_e1_e2_e3_e1e2e3 
		void set(const __syn_smv___scalar_e1_e2_e3_e1e2e3 &arg1);
		/// set to __syn_smv___e1_e3f1_0 
		void set(const __syn_smv___e1_e3f1_0 &arg1);


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
		/// assign scalar 
		mv&operator=(const scalar& arg1);
		/// assign vector2D 
		mv&operator=(const vector2D& arg1);
		/// assign vector 
		mv&operator=(const vector& arg1);
		/// assign bivector 
		mv&operator=(const bivector& arg1);
		/// assign trivector 
		mv&operator=(const trivector& arg1);
		/// assign rotor 
		mv&operator=(const rotor& arg1);
		/// assign __e1_ct__ 
		mv&operator=(const __e1_ct__& arg1);
		/// assign __e2_ct__ 
		mv&operator=(const __e2_ct__& arg1);
		/// assign __e3_ct__ 
		mv&operator=(const __e3_ct__& arg1);
		/// assign __I3_ct__ 
		mv&operator=(const __I3_ct__& arg1);
		/// assign __I3i_ct__ 
		mv&operator=(const __I3i_ct__& arg1);
		/// assign __syn_smv___e1_e2_e3_e1e2e3 
		mv&operator=(const __syn_smv___e1_e2_e3_e1e2e3& arg1);
		/// assign __syn_smv___e1e2f1_0 
		mv&operator=(const __syn_smv___e1e2f1_0& arg1);
		/// assign __syn_smv___e1e2 
		mv&operator=(const __syn_smv___e1e2& arg1);
		/// assign __syn_smv___scalar_e1e2 
		mv&operator=(const __syn_smv___scalar_e1e2& arg1);
		/// assign __syn_smv___e3f_1_0 
		mv&operator=(const __syn_smv___e3f_1_0& arg1);
		/// assign __syn_smv___e1e3_e2e3 
		mv&operator=(const __syn_smv___e1e3_e2e3& arg1);
		/// assign __syn_smv___scalar_e1e3_e2e3 
		mv&operator=(const __syn_smv___scalar_e1e3_e2e3& arg1);
		/// assign __syn_smv___e1e2_e1e3_e2e3_e1e2e3 
		mv&operator=(const __syn_smv___e1e2_e1e3_e2e3_e1e2e3& arg1);
		/// assign __syn_smv___e1e3f_1_0 
		mv&operator=(const __syn_smv___e1e3f_1_0& arg1);
		/// assign __syn_smv___e1e3 
		mv&operator=(const __syn_smv___e1e3& arg1);
		/// assign __syn_smv___scalar_e1e3 
		mv&operator=(const __syn_smv___scalar_e1e3& arg1);
		/// assign __syn_smv___e2e3f1_0 
		mv&operator=(const __syn_smv___e2e3f1_0& arg1);
		/// assign __syn_smv___e2e3 
		mv&operator=(const __syn_smv___e2e3& arg1);
		/// assign __syn_smv___scalar_e2e3 
		mv&operator=(const __syn_smv___scalar_e2e3& arg1);
		/// assign __syn_smv___e2_e3 
		mv&operator=(const __syn_smv___e2_e3& arg1);
		/// assign __syn_smv___e1_e3 
		mv&operator=(const __syn_smv___e1_e3& arg1);
		/// assign __syn_smv___e2_e3_e1e2e3 
		mv&operator=(const __syn_smv___e2_e3_e1e2e3& arg1);
		/// assign __syn_smv___e1_e3_e1e2e3 
		mv&operator=(const __syn_smv___e1_e3_e1e2e3& arg1);
		/// assign __syn_smv___e1_e2_e1e2e3 
		mv&operator=(const __syn_smv___e1_e2_e1e2e3& arg1);
		/// assign __syn_smv___scalar_e1e2_e1e3 
		mv&operator=(const __syn_smv___scalar_e1e2_e1e3& arg1);
		/// assign __syn_smv___scalar_e1e2_e2e3 
		mv&operator=(const __syn_smv___scalar_e1e2_e2e3& arg1);
		/// assign __syn_smv___e2f_1_0 
		mv&operator=(const __syn_smv___e2f_1_0& arg1);
		/// assign __syn_smv___e1e2_e1e3 
		mv&operator=(const __syn_smv___e1e2_e1e3& arg1);
		/// assign __syn_smv___e1e2_e2e3 
		mv&operator=(const __syn_smv___e1e2_e2e3& arg1);
		/// assign __syn_smv___e1f1_0_e2f1_0 
		mv&operator=(const __syn_smv___e1f1_0_e2f1_0& arg1);
		/// assign __syn_smv___e1f1_0_e2f1_0_e3f1_0 
		mv&operator=(const __syn_smv___e1f1_0_e2f1_0_e3f1_0& arg1);
		/// assign __syn_smv___e2_e1f1_0 
		mv&operator=(const __syn_smv___e2_e1f1_0& arg1);
		/// assign __syn_smv___scalar_e1_e2_e3_e1e2e3 
		mv&operator=(const __syn_smv___scalar_e1_e2_e3_e1e2e3& arg1);
		/// assign __syn_smv___e1_e3f1_0 
		mv&operator=(const __syn_smv___e1_e3f1_0& arg1);


		void compress(Float epsilon = 0.0);
		inline Float const *nullFloats() const {
			static Float *nf = NULL;
			if (nf == NULL) nf = new Float[8];
			return nf;
		}
		void expand(const Float *ptrs[], bool nulls = true) const;
		/// returns the absolute largest coordinate
		Float largestCoordinate() const;
		/// returns the absolute largest coordinate, and the corresponding basis blade bitmap 
		Float largestBasisBlade(unsigned int &bm) const;

		/// converts this multvector to an array of basis blade bitmaps and coordinates (returns number of blades)
		int toBasisBladeBitmapArray(unsigned int *bitmaps, Float *coords);

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
		inline Float e1e2e3() const {
			if (gu() & 8)
				return m_c[mv_size[gu() & 7] + 0];
			else return (float)0.0;
		}

		// coordinate storage, grade usage
		Float m_c[8]; ///< coordinate storage (TODO: if parity pure, allocate only half of the coordinates!!!)
		unsigned int m_gu; ///< grade usage
		inline unsigned int gu() const {return m_gu;}
		inline void gu(unsigned int g) {m_gu = g;}



		inline const char * c_str(const char *fp = NULL) const {
			return ::e3ga::c_str(*this, fp);
		}
		inline const char * c_str_f() const {return c_str("%f");}
		inline const char * c_str_e() const {return c_str("%e");}
		inline const char * c_str_e20() const {return c_str("%2.20e");}

		inline std::string toString(const char *fp = NULL) const {
			return ::e3ga::toString(*this, fp);
		}
		inlin