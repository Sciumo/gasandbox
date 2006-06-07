
// Generated on 2006-06-07 15:25:52 by G2 0.1 from 'E:\ga\ga_sandbox\libgasandbox\c3ga.gs2'

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





#include <string.h>
#include "c3ga.h"

	// pre_cpp_include


	namespace c3ga {

	// The dimension of the space:
	const int mv_spaceDim = 5;

	// Is the metric of the space Euclidean?
	const bool mv_metricEuclidean = false;


	// This array can be used to lookup the number of coordinates for a grade part of a general multivector
	const int mv_gradeSize[6] = {
		1, 5, 10, 10, 5, 1 
	};

	// This array can be used to lookup the number of coordinates based on a grade usage bitmap
	const int mv_size[64] = {
		0, 1, 5, 6, 10, 11, 15, 16, 10, 11, 15, 16, 20, 21, 25, 26, 5, 6, 10, 11, 15, 16, 20, 21, 15, 16, 20, 21, 25, 26, 30, 31, 1, 2, 6, 7, 11, 12, 16, 17, 11, 12, 16, 17, 21, 22, 26, 27, 6, 7, 11, 12, 16, 17, 21, 22, 16, 17, 21, 22, 26, 27, 31, 32 
	};

	// This array of ASCIIZ strings contains the names of the basis vectors
	const char *mv_basisVectorNames[5] = {
		"no", "e1", "e2", "e3", "ni" 
	};

	// This array of integers contains the order of basis elements in the general multivector
	const int mv_basisElements[32][6] = {
		{-1}
		, {0, -1}
		, {1, -1}
		, {2, -1}
		, {3, -1}
		, {4, -1}
		, {0, 1, -1}
		, {0, 2, -1}
		, {0, 3, -1}
		, {1, 2, -1}
		, {2, 3, -1}
		, {1, 3, -1}
		, {1, 4, -1}
		, {2, 4, -1}
		, {3, 4, -1}
		, {0, 4, -1}
		, {2, 3, 4, -1}
		, {1, 3, 4, -1}
		, {1, 2, 4, -1}
		, {0, 3, 4, -1}
		, {0, 1, 4, -1}
		, {0, 2, 4, -1}
		, {0, 2, 3, -1}
		, {0, 1, 3, -1}
		, {0, 1, 2, -1}
		, {1, 2, 3, -1}
		, {1, 2, 3, 4, -1}
		, {0, 2, 3, 4, -1}
		, {0, 1, 3, 4, -1}
		, {0, 1, 2, 4, -1}
		, {0, 1, 2, 3, -1}
		, {0, 1, 2, 3, 4, -1}
	};

	// This array of integers contains the 'sign' (even/odd permutation of the canonical order) of basis elements in the general multivector
	const double mv_basisElementSign[32] = {
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0 
	};

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'at what index do I find basis element [x] (x = basis vector bitmap)?
	const int mv_basisElementIndexByBitmap[32] = {
		0, 1, 2, 6, 3, 7, 9, 24, 4, 8, 11, 23, 10, 22, 25, 30, 5, 15, 12, 20, 13, 21, 18, 29, 14, 19, 17, 28, 16, 27, 26, 31 
	};

	// This array of integers contains the indices of basis elements in the general multivector
	// Use it to answer: 'what basis element do I find at index [x]'?
	const int mv_basisElementBitmapByIndex[32] = {
		0, 1, 2, 4, 8, 16, 3, 5, 9, 6, 12, 10, 18, 20, 24, 17, 28, 26, 22, 25, 19, 21, 13, 11, 7, 14, 30, 29, 27, 23, 15, 31 
	};




	// These strings determine how the output of string() is formatted.
	// You can alter them at runtime using mv_setStringFormat().

	const char *mv_string_fp = "%2.2f"; 
	const char *mv_string_start = ""; 
	const char *mv_string_end = ""; 
	const char *mv_string_mul = "*"; 
	const char *mv_string_wedge = "^"; 
	const char *mv_string_plus = " + "; 
	const char *mv_string_minus = " - "; 

	void mv_setStringFormat(const char *what, const char *format) {

		if (!strcmp(what, "fp")) 
			mv_string_fp = (format) ? format : "%2.2f"; 
		else if (!strcmp(what, "start")) 
			mv_string_start = (format) ? format : ""; 
		else if (!strcmp(what, "end")) 
			mv_string_end = (format) ? format : ""; 
		else if (!strcmp(what, "mul")) 
			mv_string_mul = (format) ? format : "*"; 
		else if (!strcmp(what, "wedge")) 
			mv_string_wedge = (format) ? format : "^"; 
		else if (!strcmp(what, "plus")) 
			mv_string_plus = (format) ? format : " + "; 
		else if (!strcmp(what, "minus")) 
			mv_string_minus = (format) ? format : " - ";	else {
			char msg[1024];
			sprintf(msg, "invalid argument to mv_setStringFormat(): %s", what);
			mv_throw_exception(msg, MV_EXCEPTION_WARNING);
		}

	}



	namespace g2Profiling {
		// Just a bunch of dummy functions:
		// Profiling is disabled, but having these functions around
		// simplifies a lot.
		void profile(unsigned int funcIdx, unsigned short storageTypeIdx, unsigned short nbArg, unsigned short argType[]) {
		}
		void reset() {
		}
		void save(const char *filename /*= "E:\\ga\\ga_sandbox\\libgasandbox\\c3ga.gp2"*/, bool append /*= false*/) {
		}
		void init(const char *filename /*= "E:\\ga\\ga_sandbox\\libgasandbox\\c3ga.gp2"*/,
		const char *hostName /*= "localhost"*/, int port /*= 7693*/) {
		}
	} // end of namespace g2Profiling






	// todo: for all storage formats, generate constants







	float mv::largestCoordinate() const {
		int nc = mv_size[gu()], i;
		Float maxC = -1.0, C;

		for (i = 0; i < nc; i++) {
			C = (m_c[i] < (Float)0.0) ? -m_c[i] : m_c[i];
			if (C > maxC) maxC = C;
		}

		return maxC;
	}

	float mv::largestBasisBlade(unsigned int &bm) const {
		int nc = mv_size[gu()];
		Float maxC = -1.0, C;

		int idx = 0;
		int grade = 0;
		int i = 0;

		while (i < nc) {
			if (gu() & (1 << grade)) {
				for (int j = 0; j < mv_gradeSize[grade]; j++) {
					C = (m_c[i] < (Float)0.0) ? -m_c[i] : m_c[i];
					if (C > maxC) {
						maxC = C;
						bm = mv_basisElementBitmapByIndex[idx];
					}
					idx++;
					i++;
				}
			}
			else idx += mv_gradeSize[grade];
			grade++;
		}

		return maxC;
	}










	float no_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float no_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 1;

		return maxC;
	}






	float e1_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e1_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 2;

		return maxC;
	}






	float e2_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e2_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 4;

		return maxC;
	}






	float e3_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e3_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 8;

		return maxC;
	}






	float ni_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float ni_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 16;

		return maxC;
	}






	float scalar::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float scalar::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 0;

		return maxC;
	}






	float point::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float point::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}






	float normalizedPoint::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedPoint::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 1;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}






	float flatPoint::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float flatPoint::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 18;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}






	float normalizedFlatPoint::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedFlatPoint::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 17;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}






	float pointPair::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float pointPair::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 3;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 9;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}






	float line::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float line::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 22;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 26;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 28;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 19;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 21;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 25;
		}
		return maxC;
	}






	float dualLine::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float dualLine::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 6;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}






	float plane::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float plane::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 30;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		return maxC;
	}






	float dualPlane::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float dualPlane::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 2;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}






	float circle::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float circle::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 28;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 26;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 22;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 25;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 19;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 21;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 13;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 11;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 14;
		}
		return maxC;
	}






	float sphere::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float sphere::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 30;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 15;
		}
		return maxC;
	}






	float dualSphere::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float dualSphere::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}






	float normalizedSphere::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedSphere::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 30;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 15;
		}
		return maxC;
	}






	float normalizedDualSphere::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedDualSphere::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 1;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}






	float freeVector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float freeVector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 18;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}






	float freeBivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float freeBivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 22;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 28;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 26;
		}
		return maxC;
	}






	float freeTrivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float freeTrivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 30;

		return maxC;
	}






	float tangentVector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float tangentVector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 3;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 9;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}






	float tangentBivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float tangentBivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 14;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 28;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 26;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 22;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 25;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 19;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 21;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 13;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 11;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		return maxC;
	}






	float vectorE2GA::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float vectorE2GA::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 2;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		return maxC;
	}






	float vectorE3GA::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float vectorE3GA::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 2;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		return maxC;
	}






	float bivectorE3GA::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float bivectorE3GA::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 6;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		return maxC;
	}






	float TRversor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float TRversor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 30;
		}
		return maxC;
	}






	float TRSversor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		C = (m_c[10] < (Float)0.0) ? -m_c[10] : m_c[10];
		if (C > maxC) maxC = C;
		C = (m_c[11] < (Float)0.0) ? -m_c[11] : m_c[11];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float TRSversor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[10] < (Float)0.0) ? -m_c[10] : m_c[10];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		C = (m_c[11] < (Float)0.0) ? -m_c[11] : m_c[11];
		if (C > maxC) {
			maxC = C;
			bm = 30;
		}
		return maxC;
	}






	float evenVersor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		C = (m_c[10] < (Float)0.0) ? -m_c[10] : m_c[10];
		if (C > maxC) maxC = C;
		C = (m_c[11] < (Float)0.0) ? -m_c[11] : m_c[11];
		if (C > maxC) maxC = C;
		C = (m_c[12] < (Float)0.0) ? -m_c[12] : m_c[12];
		if (C > maxC) maxC = C;
		C = (m_c[13] < (Float)0.0) ? -m_c[13] : m_c[13];
		if (C > maxC) maxC = C;
		C = (m_c[14] < (Float)0.0) ? -m_c[14] : m_c[14];
		if (C > maxC) maxC = C;
		C = (m_c[15] < (Float)0.0) ? -m_c[15] : m_c[15];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float evenVersor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 3;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 9;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[10] < (Float)0.0) ? -m_c[10] : m_c[10];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		C = (m_c[11] < (Float)0.0) ? -m_c[11] : m_c[11];
		if (C > maxC) {
			maxC = C;
			bm = 30;
		}
		C = (m_c[12] < (Float)0.0) ? -m_c[12] : m_c[12];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[13] < (Float)0.0) ? -m_c[13] : m_c[13];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[14] < (Float)0.0) ? -m_c[14] : m_c[14];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		C = (m_c[15] < (Float)0.0) ? -m_c[15] : m_c[15];
		if (C > maxC) {
			maxC = C;
			bm = 15;
		}
		return maxC;
	}






	float translator::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float translator::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}






	float normalizedTranslator::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedTranslator::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 0;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}






	float rotor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float rotor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		return maxC;
	}






	float scalor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float scalor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}






	float __no_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __no_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 1;

		return maxC;
	}






	float __e1_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e1_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 2;

		return maxC;
	}






	float __e2_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e2_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 4;

		return maxC;
	}






	float __e3_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e3_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 8;

		return maxC;
	}






	float __ni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __ni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 16;

		return maxC;
	}






	float __noni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __noni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 17;

		return maxC;
	}






	float __e3ni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e3ni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 24;

		return maxC;
	}






	float __e2ni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e2ni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 20;

		return maxC;
	}






	float __I3_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I3_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 14;

		return maxC;
	}






	float __e1ni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e1ni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 18;

		return maxC;
	}






	float __I5_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I5_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 31;

		return maxC;
	}






	float __I5i_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I5i_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 31;

		return maxC;
	}














	// algebra / user constants:
	__no_ct__ no;
	__ni_ct__ ni;
	__e3_ct__ e3;
	__e2ni_ct__ e2ni;
	__I3_ct__ I3;
	__e1_ct__ e1;
	__e1ni_ct__ e1ni;
	__e2_ct__ e2;
	__e3ni_ct__ e3ni;
	__noni_ct__ noni;
	__I5_ct__ I5;
	__I5i_ct__ I5i;

	char *string(const mv & obj, char *str, int maxLength, const char *fp /* = NULL */) {
		int stdIdx = 0, l;
		char tmpBuf[256], tmpFloatBuf[256]; 
		int i, j, k = 0, bei, ia = 0, s = mv_size[obj.gu()], p = 0, cnt = 0;

		// set up the floating point precision
		if (fp == NULL) fp = mv_string_fp;

		// start the string
		l = sprintf(tmpBuf, "%s", mv_string_start);
		if (stdIdx + l <= maxLength) {
			strcpy(str + stdIdx, tmpBuf);
			stdIdx += l;
		}
		else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);

		// print all coordinates
		for (i = 0; i <= 5; i++) {
			if (obj.gu() & (1 << i)) {
				for (j = 0; j < mv_gradeSize[i]; j++) {
					float coord = (float)mv_basisElementSign[ia] * obj.m_c[k];
					/* goal: print [+|-]obj.m_c[k][* basisVector1 ^ ... ^ basisVectorN] */			
					sprintf(tmpFloatBuf, fp, fabs(coord));
					if (atof(tmpFloatBuf) != 0.0) {
						l = 0;

						// print [+|-]
						l += sprintf(tmpBuf + l, "%s", (coord >= 0.0) 
							? (cnt ? mv_string_plus : "")
							: mv_string_minus);
						// print obj.m_c[k]
						l += sprintf(tmpBuf + l, tmpFloatBuf);

						if (i) { // if not grade 0, print [* basisVector1 ^ ... ^ basisVectorN]
							l += sprintf(tmpBuf + l, "%s", mv_string_mul);

							// print all basis vectors
							bei = 0;
							while (mv_basisElements[ia][bei] >= 0) {
								l += sprintf(tmpBuf + l, "%s%s", (bei) ? mv_string_wedge : "", 
									mv_basisVectorNames[mv_basisElements[ia][bei]]);
								bei++;
							}
						}

						//copy all to 'str'
						if (stdIdx + l <= maxLength) {
							strcpy(str + stdIdx, tmpBuf);
							stdIdx += l;
						}
						else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);
						cnt++;
					}
					k++; ia++;
				}
			}
			else ia += mv_gradeSize[i];
		}

		// if no coordinates printed: 0
		l = 0;
		if (cnt == 0) {
			l += sprintf(tmpBuf + l, "0");
		}

		// end the string
		l += sprintf(tmpBuf + l, "%s", mv_string_end);
		if (stdIdx + l <= maxLength) {
			strcpy(str + stdIdx, tmpBuf);
			stdIdx += l;
		}
		else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);

		return str;
	}

	// this function should be deprecated (conflicts with C++ stdlib)
	char *string(const mv & obj, const char *fp /* = NULL */) {
		// not multithreading safe, but not fatal either.
		static char str[2048];
		return string(obj, str, 2047, fp);
	}

	char *c_str(const mv & obj, const char *fp /* = NULL */) {
		return string(obj, fp);
	}

	std::string toString(const mv & obj, const char *fp /* = NULL */) {
		std::string str;
		const int SIZE = 2048;
		str.resize(SIZE);
		string(obj, &(str[0]), SIZE-1, fp);
		str.resize(strlen(&(str[0])));
		return str;
	}






	/** This function is not for external use. It compressed arrays of floats for storage in multivectors. */
	void compress(const float *c, float *cc, int &cgu, float epsilon /*= 0.0*/, int gu /*= ...*/) {
		int i, j, ia = 0, ib = 0, f, s;
		cgu = 0;

		// for all grade parts...
		for (i = 0; i <= 5; i++) {
			// check if grade part has memory use:
			if (!(gu & (1 << i))) continue;

			// check if abs coordinates of grade part are all < epsilon
			s = mv_gradeSize[i];
			j = ia + s;
			f = 0;
			for (; ia < j; ia++)
			if (mv_absLessThan(c[ia], epsilon)) {f = 1; break;}
			ia = j;
			if (f) {
				mv_memcpy(cc + ib, c + ia - s, s);
				ib += s;
				cgu |= (1 << i);
			}
		}	
	}

	mv mv_compress(const float *c, float epsilon/*= 0.0*/, int gu /*= ...*/) {
		float cc[32];
		int cgu;
		compress(c, cc, cgu, epsilon, gu);
		return mv(cgu, cc);
	}

	mv compress(const mv & arg1, float epsilon /*= 0.0*/) {
		return mv_compress(arg1.m_c, epsilon, arg1.m_gu);
	}

	void mv::compress(float epsilon /*= 0.0*/) {
		float cc[32];
		int cgu;
		c3ga::compress(m_c, cc, cgu, epsilon, m_gu);
		set(cgu, cc);
	}



	/** This function is not for external use. It decompresses the coordinates stored in this */
	void mv::expand(const Float *ptrs[], bool nulls /* = true */) const {
		const Float *c(m_c);
		const Float *null = (nulls) ? NULL : nullFloats();

		if (m_gu & 1) {
			ptrs[0] =  c;
			c += 1;
		}
		else ptrs[0] = null;	
		if (m_gu & 2) {
			ptrs[1] =  c;
			c += 5;
		}
		else ptrs[1] = null;	
		if (m_gu & 4) {
			ptrs[2] =  c;
			c += 10;
		}
		else ptrs[2] = null;	
		if (m_gu & 8) {
			ptrs[3] =  c;
			c += 10;
		}
		else ptrs[3] = null;	
		if (m_gu & 16) {
			ptrs[4] =  c;
			c += 5;
		}
		else ptrs[4] = null;	
		if (m_gu & 32) {
			ptrs[5] =  c;
			c += 1;
		}
		else ptrs[5] = null;	
	}


	void mvType::init(const mv &X, mv::Float epsilon) {
		m_type = MULTIVECTOR;

		// first of all determine grade usage & parity
		mv cX = X;
		cX.compress(epsilon);
		m_gradeUsage = (int)cX.gu();
		int cnt[2] = {0,0}; // nb even, odd grade parts in use
		{
			// count grade part usage:
			int cntIdx = 0;
			int gu = m_gradeUsage;
			while (gu != 0) {
				if ((gu & 1) != 0)
					cnt[cntIdx & 1]++;
				gu >>= 1;
				m_grade = cntIdx;
				cntIdx++;
			}

			// if no grade part in use: zero blade
			if ((cnt[0] == 0) && (cnt[1] == 0)) {
				// multivector = zero blade, case closed
				m_zero = true;
				m_type = BLADE;
				m_parity = 0;
				m_grade = 0; // forced to grade 0, but actually, does not really have a grade
				return;
			}
			else {
				m_zero = false;
				// if both even and odd grade parts in use: multivector
				if ((cnt[0] != 0) && (cnt[1] != 0)) {
					// X = multivector, case closed
					m_parity = -1;
					return;
				}
				else // more work to do, but parity is known:
				// either a blade, or a versor, TBD below
				m_parity = (cnt[1] != 0) ? 1 : 0;
			}
		}

		// first test for versor:
		bool useAlgebraMetric = true;
		init(X, epsilon, useAlgebraMetric, cnt[0] + cnt[1]);

		// Only if metric is not Euclidean:
		// If it was not a versor, or blade using the algebra metric, then try again,
		// at least, if only one grade part is in use:
		if ((m_type == MULTIVECTOR) && ((cnt[0] + cnt[1]) == 1)) {
			useAlgebraMetric = false;
			init(X, epsilon, useAlgebraMetric, cnt[0] + cnt[1]);
		}
	}


	void mvType::init(const mv &X, mv::Float epsilon, bool useAlgebraMetric, int guCnt) {
		mv rX = reverse(X);

		// test if null:
		mv Sq = (useAlgebraMetric) ? scp(X, rX) : scpEM(X, rX);
		Sq.compress(epsilon);
		if (_Float(Sq) == 0) {
			// X = multivector, case closed
			m_type = MULTIVECTOR;
			return;
		}

		// versor inverse must be true inverse:
		mv Xvi = (useAlgebraMetric) ? inverse(X) : inverseEM(X);
		mv Xgi = gradeInvolution(X);

		// check if (Xgi Xvi) is a scalar:
		mv XgiXvi = (useAlgebraMetric) ? gp(Xgi, Xvi) : gpEM(Xgi, Xvi);
		{
			mv tmp = XgiXvi;
			tmp.compress(epsilon);
			if (tmp.gu() != GRADE_0) { // if not scalar:
				// X = multivector, case closed
				m_type = MULTIVECTOR;
				return;
			}
		}

		// check if Xgi Xvi == Xvi Xgi
		mv XviXgi = (useAlgebraMetric) ? gp(Xvi, Xgi) : gpEM(Xvi, Xgi);
		{
			mv tmp = XviXgi - XgiXvi;
			tmp.compress(epsilon); // this should result in 0
			if (tmp.gu()) {
				// if not:
				// X = multivector, case closed
				m_type = MULTIVECTOR;
				return;
			}
		}

		// check if grade preserving for all basis vectors:
		{
			{
				// test no		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, no), Xgi) : gpEM(gpEM(Xvi, no), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e1		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e1), Xgi) : gpEM(gpEM(Xvi, e1), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e2		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e2), Xgi) : gpEM(gpEM(Xvi, e2), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e3		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e3), Xgi) : gpEM(gpEM(Xvi, e3), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test ni		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, ni), Xgi) : gpEM(gpEM(Xvi, ni), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
		}

		// if homogeneous: blade
		if (guCnt == 1) m_type = BLADE;
		else m_type = VERSOR;
	}



	std::string mvType::toString() const {
		char buf[1024];
		sprintf(buf, "%s, grade: %d, gradeUsage: %X, parity: %s",
			(m_type == MULTIVECTOR) ? "multivector" : ((m_type == BLADE) ? "blade" : "versor"),
			m_grade, m_gradeUsage,
			(m_parity < 0) ? "none" : ((m_parity == 0) ? "even" : "odd"));
		return buf;
	}










} // end of namespace c3ga
// post_cpp_include

