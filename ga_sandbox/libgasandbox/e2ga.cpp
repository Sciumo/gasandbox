
// Generated on 2007-01-09 19:46:34 by G2 0.1 from 'E:\ga\ga_sandbox\ga_sandbox\libgasandbox\e2ga.gs2'

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
#include "e2ga.h"

	// pre_cpp_include


	namespace e2ga {

	// The dimension of the space:
	const int mv_spaceDim = 2;

	// Is the metric of the space Euclidean?
	const bool mv_metricEuclidean = true;


	// This array can be used to lookup the number of coordinates for a grade part of a general multivector
	const int mv_gradeSize[3] = {
		1, 2, 1 
	};

	// This array can be used to lookup the number of coordinates based on a grade usage bitmap
	const int mv_size[8] = {
		0, 1, 2, 3, 1, 2, 3, 4 
	};

	// This array of ASCIIZ strings contains the names of the basis vectors
	const char *mv_basisVectorNames[2] = {
		"e1", "e2" 
	};

	// This array of integers contains the order of basis elements in the general multivector
	const int mv_basisElements[4][3] = {
		{-1}
		, {0, -1}
		, {1, -1}
		, {0, 1, -1}
	};

	// This array of integers contains the 'sign' (even/odd permutation of the canonical order) of basis elements in the general multivector
	const double mv_basisElementSign[4] = {
		1.0, 1.0, 1.0, 1.0 
	};

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'at what index do I find basis element [x] (x = basis vector bitmap)?
	const int mv_basisElementIndexByBitmap[4] = {
		0, 1, 2, 3 
	};

	// This array of integers contains the indices of basis elements in the general multivector
	// Use it to answer: 'what basis element do I find at index [x]'?
	const int mv_basisElementBitmapByIndex[4] = {
		0, 1, 2, 3 
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
		void save(const char *filename /*= "E:\\ga\\ga_sandbox\\ga_sandbox\\libgasandbox\\e2ga.gp2"*/, bool append /*= false*/) {
		}
		void init(const char *filename /*= "E:\\ga\\ga_sandbox\\ga_sandbox\\libgasandbox\\e2ga.gp2"*/,
		const char *hostName /*= "localhost"*/, int port /*= 7693*/) {
		}
	} // end of namespace g2Profiling






	// todo: for all storage formats, generate constants






	// set to 0
	void mv::set() {
		// set grade usage
		gu(0);

	}

	// set to copy 
	void mv::set(const mv &arg1) {
		// copy grade usage
		gu(arg1.gu());
		// copy coordinates
		mv_memcpy(m_c, arg1.m_c, mv_size[gu()]);

	}

	// set to scalar
	void mv::set(Float scalarVal) {
		// set grade usage
		gu(1);
		// set type (if profile)
		// set coordinate
		m_c[0] = scalarVal;

	}


	// set to coordinates 
	void mv::set(unsigned int gradeUsage, const Float *coordinates) {
		// set grade usage
		gu(gradeUsage);
		// set coordinates
		mv_memcpy(m_c, coordinates, mv_size[gu()]);

	}


	// set to 1 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0	) {
		// set grade usage
		gu(gradeUsage);
		// check the number of coordinates
		if (mv_size[gu()] != 1)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;

	}

	// set to 2 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1	) {
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
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2	) {
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
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3	) {
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



	// set to e1_t 
	void mv::set(const e1_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;


	}
	// set to e2_t 
	void mv::set(const e2_t & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;


	}
	// set to scalar 
	void mv::set(const scalar & arg1) {

		// set grade usage 
		gu(1);


		m_c[0] = arg1.m_c[0] ;


	}
	// set to vector 
	void mv::set(const vector & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;


	}
	// set to bivector 
	void mv::set(const bivector & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = arg1.m_c[0] ;


	}
	// set to rotor 
	void mv::set(const rotor & arg1) {

		// set grade usage 
		gu(5);


		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;


	}
	// set to __e1_ct__ 
	void mv::set(const __e1_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)0;


	}
	// set to __e2_ct__ 
	void mv::set(const __e2_ct__ & arg1) {

		// set grade usage 
		gu(2);


		m_c[0] = (Float)0;
		m_c[1] = (Float)1.0f; 


	}
	// set to __I2_ct__ 
	void mv::set(const __I2_ct__ & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = (Float)1.0f; 


	}
	// set to __I2i_ct__ 
	void mv::set(const __I2i_ct__ & arg1) {

		// set grade usage 
		gu(4);


		m_c[0] = (Float)-1.0f; 


	}






	// assign copy
	mv& mv::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}


	// assign scalar
	mv& mv::operator=(Float s) {
		set(s);
		return *this;
	}

	// assign e1_t 
	mv& mv::operator=(const e1_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e2_t 
	mv& mv::operator=(const e2_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign scalar 
	mv& mv::operator=(const scalar& arg1) {
		set(arg1);
		return *this;
	}
	// assign vector 
	mv& mv::operator=(const vector& arg1) {
		set(arg1);
		return *this;
	}
	// assign bivector 
	mv& mv::operator=(const bivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign rotor 
	mv& mv::operator=(const rotor& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e1_ct__ 
	mv& mv::operator=(const __e1_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e2_ct__ 
	mv& mv::operator=(const __e2_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __I2_ct__ 
	mv& mv::operator=(const __I2_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __I2i_ct__ 
	mv& mv::operator=(const __I2i_ct__& arg1) {
		set(arg1);
		return *this;
	}




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








	// set to mv 
	void e1_t::set(const mv & arg1) {

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




	float e1_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e1_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 1;

		return maxC;
	}




	// set to mv 
	void e2_t::set(const mv & arg1) {

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




	float e2_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e2_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 2;

		return maxC;
	}




	// set to mv 
	void scalar::set(const mv & arg1) {


		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


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




	// set to mv 
	void vector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}




	float vector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float vector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		return maxC;
	}




	// set to mv 
	void bivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 2;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float bivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float bivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 3;

		return maxC;
	}




	// set to mv 
	void rotor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 2;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[1] = (Float)0.0;
		}


	}




	float rotor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float rotor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 3;
		}
		return maxC;
	}




	// set to mv 
	void __e1_ct__::set(const mv & arg1) {



	}




	float __e1_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e1_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 1;

		return maxC;
	}




	// set to mv 
	void __e2_ct__::set(const mv & arg1) {



	}




	float __e2_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e2_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 2;

		return maxC;
	}




	// set to mv 
	void __I2_ct__::set(const mv & arg1) {



	}




	float __I2_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I2_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 3;

		return maxC;
	}




	// set to mv 
	void __I2i_ct__::set(const mv & arg1) {



	}




	float __I2i_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I2i_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 3;

		return maxC;
	}






	// set to identity 'I'
	void om::set() {
		// simplify forward call to set(scalar)
		set(1.0);
	}

	// set to copy
	void om::set(const om &arg1) {
		mv_memcpy(m_c, arg1.m_c, 5);
	}

	// set to scalar
	void om::set(Float scalarVal) {
		e2ga::__G2_GENERATED__::set(*this, vector(vector_e1_e2, scalarVal, (Float)0), vector(vector_e1_e2, (Float)0, scalarVal));
	}

	// set to coordinates 
	void om::set(const Float *coordinates) {
		mv_memcpy(m_c, coordinates, 5);
	}

	// set from basis vectors array
	void om::set(const vector *vectors) {
		e2ga::__G2_GENERATED__::set(*this, vectors[0], vectors[1]);
	}


	// set from basis vectors 
	void om::set(const vector & image_of_e1, const vector & image_of_e2) {
		e2ga::__G2_GENERATED__::set(*this, image_of_e1, image_of_e2);
	}


	// set by coordinates, transpose
	void om::set(const Float *coordinates, bool transpose) {
		if (transpose) {
			m_c[0] = coordinates[0];
			m_c[2] = coordinates[1];
			m_c[1] = coordinates[2];
			m_c[3] = coordinates[3];
			m_c[4] = coordinates[4];
		}
		else set(coordinates);
	}




	// assign copy
	om &om::operator=(const om &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar (creates scalar * 'I' outermorphism)
	om &om::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}

	/// assign specialization:






	// G2 functions:
	mv lcont(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_1__[4] ;
		mv_zero(__tmp_coord_array_1__, 4);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[3] ;
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

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[0] += ((__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][1] * __y_xpd__[1][1]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[3] += (__y_xpd__[2][0] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[1] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]);
				__tmp_coord_array_1__[2] += (__x_xpd__[1][0] * __y_xpd__[2][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[0] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_1__);
		return __temp_var_1__;
	}
	scalar scp(const mv& x, const mv& y) {
		scalar __temp_var_1__;
		const float* __y_xpd__[3] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 2) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][0] * __y_xpd__[1][0]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 4) != 0)) {
				__temp_var_1__.m_c[0] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]);

			}

		}
		return __temp_var_1__;
	}
	mv gp(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_2__[4] ;
		mv_zero(__tmp_coord_array_2__, 4);
		const float* __y_xpd__[3] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[3] += (__x_xpd__[2][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[0] += ((__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][1] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][1]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[2][0] * __y_xpd__[1][1]);
				__tmp_coord_array_2__[2] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[1][0]);

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[3] += (__x_xpd__[0][0] * __y_xpd__[2][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[1][0] * __y_xpd__[2][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[0] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_2__);
		return __temp_var_1__;
	}
	mv op(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_3__[4] ;
		mv_zero(__tmp_coord_array_3__, 4);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[3] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[3] += (__x_xpd__[0][0] * __y_xpd__[2][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[3] += ((__x_xpd__[1][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]));

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[3] += (__x_xpd__[2][0] * __y_xpd__[0][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_3__);
		return __temp_var_1__;
	}
	mv add(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_4__[4] ;
		mv_zero(__tmp_coord_array_4__, 4);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[3] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_4__[0] += __y_xpd__[0][0];

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_4__[1] += __y_xpd__[1][0];
			__tmp_coord_array_4__[2] += __y_xpd__[1][1];

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_4__[3] += __y_xpd__[2][0];

		}
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_4__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_4__[1] += __x_xpd__[1][0];
			__tmp_coord_array_4__[2] += __x_xpd__[1][1];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_4__[3] += __x_xpd__[2][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_4__);
		return __temp_var_1__;
	}
	mv subtract(const mv& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_5__[4] ;
		mv_zero(__tmp_coord_array_5__, 4);
		const float* __y_xpd__[3] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_5__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_5__[1] += __x_xpd__[1][0];
			__tmp_coord_array_5__[2] += __x_xpd__[1][1];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_5__[3] += __x_xpd__[2][0];

		}
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_5__[0] += (-1.0f * __y_xpd__[0][0]);

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_5__[1] += (-1.0f * __y_xpd__[1][0]);
			__tmp_coord_array_5__[2] += (-1.0f * __y_xpd__[1][1]);

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_5__[3] += (-1.0f * __y_xpd__[2][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_5__);
		return __temp_var_1__;
	}
	scalar norm_e2(const mv& x) {
		scalar __temp_var_1__;
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[2][0] * __x_xpd__[2][0]);

		}
		return __temp_var_1__;
	}
	scalar norm_e(const mv& x) {
		scalar e2;
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += (__x_xpd__[2][0] * __x_xpd__[2][0]);

		}
		return scalar(scalar_scalar, sqrt(e2.m_c[0]));
	}
	mv unit_e(const mv& x) {
		scalar e2;
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += (__x_xpd__[2][0] * __x_xpd__[2][0]);

		}
		scalar ie;
		ie.m_c[0] = ((char)1 / sqrt(e2.m_c[0]));
		mv __temp_var_1__;
		float __tmp_coord_array_6__[4] ;
		mv_zero(__tmp_coord_array_6__, 4);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_6__[0] += (__x_xpd__[0][0] * ie.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_6__[1] += (__x_xpd__[1][0] * ie.m_c[0]);
			__tmp_coord_array_6__[2] += (__x_xpd__[1][1] * ie.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_6__[3] += (__x_xpd__[2][0] * ie.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_6__);
		return __temp_var_1__;
	}
	scalar norm_r2(const mv& x) {
		scalar __temp_var_1__;
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[2][0] * __x_xpd__[2][0]);

		}
		return __temp_var_1__;
	}
	scalar norm_r(const mv& x) {
		scalar r2;
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += (__x_xpd__[2][0] * __x_xpd__[2][0]);

		}
		return scalar(scalar_scalar, ((((r2.m_c[0] < (char)0)) ? (char)-1 : ((((r2.m_c[0] > (char)0)) ? (char)1 : (char)0))) * sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0])))));
	}
	mv unit_r(const mv& x) {
		scalar r2;
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += (__x_xpd__[2][0] * __x_xpd__[2][0]);

		}
		scalar ir;
		ir.m_c[0] = ((char)1 / sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0]))));
		mv __temp_var_1__;
		float __tmp_coord_array_7__[4] ;
		mv_zero(__tmp_coord_array_7__, 4);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_7__[0] += (__x_xpd__[0][0] * ir.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_7__[1] += (__x_xpd__[1][0] * ir.m_c[0]);
			__tmp_coord_array_7__[2] += (__x_xpd__[1][1] * ir.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_7__[3] += (__x_xpd__[2][0] * ir.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_7__);
		return __temp_var_1__;
	}
	mv reverse(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_8__[4] ;
		mv_zero(__tmp_coord_array_8__, 4);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_8__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_8__[1] += __x_xpd__[1][0];
			__tmp_coord_array_8__[2] += __x_xpd__[1][1];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_8__[3] += (-1.0f * __x_xpd__[2][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_8__);
		return __temp_var_1__;
	}
	mv negate(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_9__[4] ;
		mv_zero(__tmp_coord_array_9__, 4);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_9__[0] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_9__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_9__[2] += (-1.0f * __x_xpd__[1][1]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_9__[3] += (-1.0f * __x_xpd__[2][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_9__);
		return __temp_var_1__;
	}
	mv dual(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_10__[4] ;
		mv_zero(__tmp_coord_array_10__, 4);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_10__[3] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_10__[1] += __x_xpd__[1][1];
			__tmp_coord_array_10__[2] += (-1.0f * __x_xpd__[1][0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_10__[0] += __x_xpd__[2][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_10__);
		return __temp_var_1__;
	}
	mv undual(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_11__[4] ;
		mv_zero(__tmp_coord_array_11__, 4);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_11__[3] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_11__[1] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_11__[2] += __x_xpd__[1][0];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_11__[0] += (-1.0f * __x_xpd__[2][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_11__);
		return __temp_var_1__;
	}
	mv inverse(const mv& x) {
		scalar n;
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			n.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			n.m_c[0] += ((__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]));

		}
		if (((x.m_gu & 4) != 0)) {
			n.m_c[0] += (__x_xpd__[2][0] * __x_xpd__[2][0]);

		}
		scalar in;
		in.m_c[0] = ((char)1 / n.m_c[0]);
		mv __temp_var_1__;
		float __tmp_coord_array_12__[4] ;
		mv_zero(__tmp_coord_array_12__, 4);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_12__[0] += (__x_xpd__[0][0] * in.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_12__[1] += (__x_xpd__[1][0] * in.m_c[0]);
			__tmp_coord_array_12__[2] += (__x_xpd__[1][1] * in.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_12__[3] += (-1.0f * __x_xpd__[2][0] * in.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_12__);
		return __temp_var_1__;
	}
	mv gradeInvolution(const mv& x) {
		mv __temp_var_1__;
		float __tmp_coord_array_13__[4] ;
		mv_zero(__tmp_coord_array_13__, 4);
		const float* __x_xpd__[3] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_13__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_13__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_13__[2] += (-1.0f * __x_xpd__[1][1]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_13__[3] += __x_xpd__[2][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_13__);
		return __temp_var_1__;
	}

	// G2 functions:
	mv apply_om(const om& x, const mv& y) {
		mv __temp_var_1__;
		float __tmp_coord_array_14__[4] ;
		mv_zero(__tmp_coord_array_14__, 4);
		const float* __y_xpd__[3] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_14__[1] += ((x.m_c[1] * __y_xpd__[1][1]) + (x.m_c[0] * __y_xpd__[1][0]));
			__tmp_coord_array_14__[2] += ((x.m_c[2] * __y_xpd__[1][0]) + (x.m_c[3] * __y_xpd__[1][1]));

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_14__[3] += (x.m_c[4] * __y_xpd__[2][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_14__);
		return __temp_var_1__;
	}
	namespace __G2_GENERATED__ {
		void set(om& __x__, const vector& __image_of_e1__, const vector& __image_of_e2__) {
			__x__.m_c[0] = __image_of_e1__.m_c[0];
			__x__.m_c[2] = __image_of_e1__.m_c[1];
			__x__.m_c[1] = __image_of_e2__.m_c[0];
			__x__.m_c[3] = __image_of_e2__.m_c[1];
			__x__.m_c[4] = ((__x__.m_c[3] * __x__.m_c[0]) + (-1.0f * __x__.m_c[1] * __x__.m_c[2]));
		}
	} /* end of namespace __G2_GENERATED__ */


	// algebra / user constants:
	__I2i_ct__ I2i;
	__I2_ct__ I2;
	__e1_ct__ e1;
	__e2_ct__ e2;

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
		for (i = 0; i <= 2; i++) {
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
		for (i = 0; i <= 2; i++) {
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
		float cc[4];
		int cgu;
		compress(c, cc, cgu, epsilon, gu);
		return mv(cgu, cc);
	}

	mv compress(const mv & arg1, float epsilon /*= 0.0*/) {
		return mv_compress(arg1.m_c, epsilon, arg1.m_gu);
	}

	void mv::compress(float epsilon /*= 0.0*/) {
		float cc[4];
		int cgu;
		e2ga::compress(m_c, cc, cgu, epsilon, m_gu);
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
			c += 2;
		}
		else ptrs[1] = null;	
		if (m_gu & 4) {
			ptrs[2] =  c;
			c += 1;
		}
		else ptrs[2] = null;	
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

	}


	void mvType::init(const mv &X, mv::Float epsilon, bool useAlgebraMetric, int guCnt) {
		mv rX = reverse(X);

		// test if null:
		mv Sq = (useAlgebraMetric) ? scp(X, rX) : scp(X, rX);
		Sq.compress(epsilon);
		if (_Float(Sq) == 0) {
			// X = multivector, case closed
			m_type = MULTIVECTOR;
			return;
		}

		// versor inverse must be true inverse:
		mv Xvi = (useAlgebraMetric) ? inverse(X) : inverse(X);
		mv Xgi = gradeInvolution(X);

		// check if (Xgi Xvi) is a scalar:
		mv XgiXvi = (useAlgebraMetric) ? gp(Xgi, Xvi) : gp(Xgi, Xvi);
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
		mv XviXgi = (useAlgebraMetric) ? gp(Xvi, Xgi) : gp(Xvi, Xgi);
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
				// test e1		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e1), Xgi) : gp(gp(Xvi, e1), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e2		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e2), Xgi) : gp(gp(Xvi, e2), Xgi);
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










} // end of namespace e2ga
// post_cpp_include

