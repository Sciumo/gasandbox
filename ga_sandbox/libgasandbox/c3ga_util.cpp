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

#include <string>

#include "c3ga.h"
#include "c3ga_util.h"
#include "e3ga_util.h"
#include "gabits.h"

namespace c3ga {

mv exp(const mv &x, int order /*= 9*/) {
	// First try special cases:
	// Check if (x * x == scalar) is scalar
	mv x2 = x * x;
	mv::Float s_x2 = _Float(x2);
	if ((_Float(norm_e2(x2) - s_x2 * s_x2)) < 1e-7f) {
		// OK (x * x == scalar), so use special cases:
		if (s_x2 < 0.0) {
			mv::Float a = sqrt(-s_x2);
			return (mv::Float)cos(a) + (mv::Float)sin(a) * x * (1.0f / a);
		}
		else if (s_x2 > 0.0) {
			mv::Float a = sqrt(s_x2);
			return (mv::Float)cosh(a) + (mv::Float)sinh(a) * x * (1.0f / a);
		}
		else {
			return 1 + x;
		}
	}


	// now do general series eval:


    int i;
    mv result;

    result = 1.0;
    if (order == 0) {
        return result;
    }

    // scale by power of 2 so that its norm is < 1
    unsigned long max = (unsigned long)x.largestCoordinate();
    unsigned long scale=1;
    if (max > 1) scale <<= 1;
    while (max)
    {
        max >>= 1;
        scale <<= 1;
    }

    mv scaled = x * scalar(1.0f / (mv::Float)scale);

    // taylor approximation
    mv tmp;

    tmp = 1.0;
    for (i = 1; i < order; i++) {
        tmp = tmp*scaled * scalar(1.0f / (mv::Float)i);
        result += tmp;
    }

    // undo scaling
    while (scale > 1)
    {
        result *= result;
        scale >>= 1;
    }
	return result;
}


bivectorE3GA log(const c3ga::rotor &R) {
	mv::Float R2 = _Float(norm_r(_bivectorE3GA(R)));
	if (R2 <= 0.0) return bivectorE3GA(); // check to avoid divide-by-zero (and below zero due to FP roundoff)
	return _bivectorE3GA(_bivectorE3GA(R) * ((float)atan2(R2, _Float(R)) / R2));
}

// todo: don't return pointpair (there is no 'no' in the log of TRversor)
pointPair log(const TRversor &V) {
	rotor R = _rotor(-no << (V * ni));
	vectorE3GA t = _vectorE3GA(-2.0f * (no << V) * inverse(R));
	bivectorE3GA Iphi = _bivectorE3GA(-2.0f * log(R));
	rotor I = (_Float(norm_e2(Iphi)) == 0.0f) ? _rotor(1) :_rotor(unit_e(Iphi));

	return _pointPair(
		0.5f * (
		-(t ^ I) * inverse(I) * ni + 
		inverse(1.0f - R * R) * (t << Iphi) * ni -
		Iphi));
}
#ifdef RIEN
// this is the version that can not handle negative scaling . . .
TRSversor matrix4x4ToVersor(const mv::Float _M[4 * 4], bool transpose /*= false*/) {
	const mv::Float *M = NULL;
	mv::Float Mt[4 * 4];
	if (transpose) {
		Mt[0 * 4 + 0] = _M[0 * 4 + 0]; Mt[1 * 4 + 0] = _M[0 * 4 + 1]; Mt[2 * 4 + 0] = _M[0 * 4 + 2]; Mt[3 * 4 + 0] = _M[0 * 4 + 3]; 
		Mt[0 * 4 + 1] = _M[1 * 4 + 0]; Mt[1 * 4 + 1] = _M[1 * 4 + 1]; Mt[2 * 4 + 1] = _M[1 * 4 + 2]; Mt[3 * 4 + 1] = _M[1 * 4 + 3]; 
		Mt[0 * 4 + 2] = _M[2 * 4 + 0]; Mt[1 * 4 + 2] = _M[2 * 4 + 1]; Mt[2 * 4 + 2] = _M[2 * 4 + 2]; Mt[3 * 4 + 2] = _M[2 * 4 + 3]; 
		Mt[0 * 4 + 3] = _M[3 * 4 + 0]; Mt[1 * 4 + 3] = _M[3 * 4 + 1]; Mt[2 * 4 + 3] = _M[3 * 4 + 2]; Mt[3 * 4 + 3] = _M[3 * 4 + 3]; 
		M = Mt;
	}
	else M = _M;

//	printf("Matrix:\n");
//	printf("%f %f %f %f\n", M[0 * 4 + 0], M[0 * 4 + 1], M[0 * 4 + 2], M[0 * 4 + 3]);
//	printf("%f %f %f %f\n", M[1 * 4 + 0], M[1 * 4 + 1], M[1 * 4 + 2], M[1 * 4 + 3]);
//	printf("%f %f %f %f\n", M[2 * 4 + 0], M[2 * 4 + 1], M[2 * 4 + 2], M[2 * 4 + 3]);
//	printf("%f %f %f %f\n", M[3 * 4 + 0], M[3 * 4 + 1], M[3 * 4 + 2], M[3 * 4 + 3]);

	// get scale of the whole matrix:
	mv::Float scale = M[3 * 4 + 3];
	// determine translation:
	vectorE3GA t(vectorE3GA_e1_e2_e3, M[0 * 4 + 3] / scale, M[1 * 4 + 3] / scale, M[2 * 4 + 3] / scale);

	// initialize images of Euclidean basis vectors (the columns of the matrix)
	vectorE3GA imageOfE1(vectorE3GA_e1_e2_e3, M[0 * 4 + 0], M[1 * 4 + 0], M[2 * 4 + 0]);
	vectorE3GA imageOfE2(vectorE3GA_e1_e2_e3, M[0 * 4 + 1], M[1 * 4 + 1], M[2 * 4 + 1]);
	vectorE3GA imageOfE3(vectorE3GA_e1_e2_e3, M[0 * 4 + 2], M[1 * 4 + 2], M[2 * 4 + 2]);

	// get scale of the 3x3 part (e1, e2, e3)
	mv::Float scaleR = _Float(norm_e(imageOfE1) + norm_e(imageOfE2) + norm_e(imageOfE3))  / 3.0f;

	// compute determinant of matrix (if negative, flip 3rd column)
	float sc3 = 1.0f; // sc3 = scale column 3
	if ((imageOfE1 ^ imageOfE2 ^ imageOfE3).e1e2e3() < 0.0f) sc3 = -1.0f;

	printf("Scale: %f %f (total %f)\n", scale, scaleR, scale * scaleR);

	// initialize 3x3 'rotation' matrix, call e3ga::matrixToRotor
	float RM[3 * 3] = {
		M[0 * 4 + 0] / scaleR, M[0 * 4 + 1] / scaleR, sc3 * M[0 * 4 + 2] / scaleR, 
		M[1 * 4 + 0] / scaleR, M[1 * 4 + 1] / scaleR, sc3 * M[1 * 4 + 2] / scaleR, 
		M[2 * 4 + 0] / scaleR, M[2 * 4 + 1] / scaleR, sc3 * M[2 * 4 + 2] / scaleR
	};
	e3ga::rotor tmpR = e3ga::matrixToRotor(RM);

	// convert e3ga rotor to c3ga rotor:
	c3ga::rotor R(rotor_scalar_e1e2_e2e3_e3e1,
		tmpR.getC(e3ga::rotor_scalar_e1e2_e2e3_e3e1));

	// get log of scale:
	mv::Float logScale = (mv::Float) ::log(scale * scaleR);

	// return full versor:
	return _TRSversor(
		exp(_freeVector(-0.5f * (t ^ ni))) *  // translation
		R * // rotation
		exp(_noni_t(0.5f * logScale * noni)) // scaling
		); 
}
#endif
mv matrix4x4ToVersor(const mv::Float _M[4 * 4], bool transpose /*= false*/) {
	const mv::Float *M = NULL;
	mv::Float Mt[4 * 4];
	if (transpose) {
		Mt[0 * 4 + 0] = _M[0 * 4 + 0]; Mt[1 * 4 + 0] = _M[0 * 4 + 1]; Mt[2 * 4 + 0] = _M[0 * 4 + 2]; Mt[3 * 4 + 0] = _M[0 * 4 + 3]; 
		Mt[0 * 4 + 1] = _M[1 * 4 + 0]; Mt[1 * 4 + 1] = _M[1 * 4 + 1]; Mt[2 * 4 + 1] = _M[1 * 4 + 2]; Mt[3 * 4 + 1] = _M[1 * 4 + 3]; 
		Mt[0 * 4 + 2] = _M[2 * 4 + 0]; Mt[1 * 4 + 2] = _M[2 * 4 + 1]; Mt[2 * 4 + 2] = _M[2 * 4 + 2]; Mt[3 * 4 + 2] = _M[2 * 4 + 3]; 
		Mt[0 * 4 + 3] = _M[3 * 4 + 0]; Mt[1 * 4 + 3] = _M[3 * 4 + 1]; Mt[2 * 4 + 3] = _M[3 * 4 + 2]; Mt[3 * 4 + 3] = _M[3 * 4 + 3]; 
		M = Mt;
	}
	else M = _M;

//	printf("Matrix:\n");
//	printf("%f %f %f %f\n", M[0 * 4 + 0], M[0 * 4 + 1], M[0 * 4 + 2], M[0 * 4 + 3]);
//	printf("%f %f %f %f\n", M[1 * 4 + 0], M[1 * 4 + 1], M[1 * 4 + 2], M[1 * 4 + 3]);
//	printf("%f %f %f %f\n", M[2 * 4 + 0], M[2 * 4 + 1], M[2 * 4 + 2], M[2 * 4 + 3]);
//	printf("%f %f %f %f\n", M[3 * 4 + 0], M[3 * 4 + 1], M[3 * 4 + 2], M[3 * 4 + 3]);

	// get scale of the whole matrix:
	mv::Float scale = M[3 * 4 + 3];
	// determine translation:
	vectorE3GA t(vectorE3GA_e1_e2_e3, M[0 * 4 + 3] / scale, M[1 * 4 + 3] / scale, M[2 * 4 + 3] / scale);

	// initialize images of Euclidean basis vectors (the columns of the matrix)
	vectorE3GA imageOfE1(vectorE3GA_e1_e2_e3, M[0 * 4 + 0], M[1 * 4 + 0], M[2 * 4 + 0]);
	vectorE3GA imageOfE2(vectorE3GA_e1_e2_e3, M[0 * 4 + 1], M[1 * 4 + 1], M[2 * 4 + 1]);
	vectorE3GA imageOfE3(vectorE3GA_e1_e2_e3, M[0 * 4 + 2], M[1 * 4 + 2], M[2 * 4 + 2]);

	// get scale of the 3x3 part (e1, e2, e3)
	mv::Float scaleR = _Float(norm_e(imageOfE1) + norm_e(imageOfE2) + norm_e(imageOfE3))  / 3.0f;

	// compute determinant of matrix (if negative, flip 3rd column)
	float sc3 = 1.0f; // sc3 = scale column 3
	mv reflectionPlane = 1;
	if ((imageOfE1 ^ imageOfE2 ^ imageOfE3).e1e2e3() < 0.0f) {
		sc3 = -1.0f;
		reflectionPlane = e3;
	}

	// initialize 3x3 'rotation' matrix, call e3ga::matrixToRotor
	float RM[3 * 3] = {
		M[0 * 4 + 0] / scaleR, M[0 * 4 + 1] / scaleR, sc3 * M[0 * 4 + 2] / scaleR, 
		M[1 * 4 + 0] / scaleR, M[1 * 4 + 1] / scaleR, sc3 * M[1 * 4 + 2] / scaleR, 
		M[2 * 4 + 0] / scaleR, M[2 * 4 + 1] / scaleR, sc3 * M[2 * 4 + 2] / scaleR
	};
	e3ga::rotor tmpR = e3ga::matrixToRotor(RM);

	// convert e3ga rotor to c3ga rotor:
	c3ga::rotor R(rotor_scalar_e1e2_e2e3_e3e1,
		tmpR.getC(e3ga::rotor_scalar_e1e2_e2e3_e3e1));

	// get log of scale:
	mv::Float logScale = (mv::Float) ::log(scale * scaleR);

	// return full versor:
	return exp(_freeVector(-0.5f * (t ^ ni))) *  // translation
		R * // rotation
		exp(_noni_t(0.5f * logScale * noni)) * // scaling
		reflectionPlane;

}


void reciprocalFrame(const dualSphere *IF, dualSphere *RF, int nbVectors) {
	if (nbVectors == 0) return; // nothing to do
	else if (nbVectors == 1) {
		// trivial case
		if (_Float(norm_r2(IF[0])) == 0.0f)
			throw std::string("reciprocalFrame(): null vector");
		RF[0] = inverse(IF[0]);
		return;
	}
	else {
		// compute pseudoscalar 'I' of space spanned by input frame:
		mv I = IF[0];
		for (int i = 1; i < nbVectors; i++) I ^= IF[i];
		if (_Float(norm_r2(I)) == 0.0f) 
			throw std::string("reciprocalFrame(): vectors are not independent");

		// compute inverse of 'I':
		mv Ii = inverse(I);

		// compute the vectors of the reciprocal framevector
		for (int i = 0; i < nbVectors; i++) {
			// compute outer product of all vectors except IF[i]
			mv P = (i & 1) ? -1.0f : 1.0f; // = pow(-1, i)
			for (int j = 0; j < nbVectors; j++)
				if (j != i) P ^= IF[j];

			// compute reciprocal vector 'i':
			RF[i] = _dualSphere(P << Ii);
		}
		return;
	}
}

/// factors blade into vectors (euclidean unit length), returns  scale (or throws exception when non-blade is passed)
mv::Float factorizeBlade(const mv &X, dualSphere factor[], int gradeOfX /* = -1 */) {
//	printf("X = %s;\n", X.c_str());
	// get scale of blade, grade of blade
	int k = gradeOfX;
	if (k < 0) {
		mvType T(X);
		k = T.m_grade;
	}
	mv::Float s = (k == 0) ? _Float(X): _Float(norm_e(X));
	
	// detect non-blades
	if (k < 0) throw -1;
	
	// set scale of output, no matter what:
	mv::Float scale = s;
	
	// detect null-blades, scalar-blades
	if ((s == 0.0) || (k == 0))
	    return scale;
	
	
	// get largest basis blade, basis vectors
	unsigned int E;
	int Eidx = 0;
	X.largestBasisBlade(E);
	
	// setup the 'current input blade'
	mv Bc = unit_e(X);
	
	mv::Float coords[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	for (int i = 0; i < (k-1); i++) {
		// get next basisvector
		while (!(E&1)) {
			coords[Eidx] = 0.0;
			E >>= 1;	Eidx++;
		}
		coords[Eidx] = 1.0;
		E ^= 1;
		mv ei(GRADE_1, coords);

	    // project basis vector ei, normalize projection:
	    factor[i] = _dualSphere(unit_e(lcontEM(lcontEM(ei, Bc), Bc))); // no inverse(Bc) required, since Bc is always unit
	    
	    // remove f[i] from Bc
	    Bc = lcontEM(factor[i], Bc);
	}
	
	// last factor = what is left of the input blade
	factor[k-1] = _dualSphere(unit_e(Bc)); // already normalized, but renormalize to remove any FP round-off error
	
	return scale;
}

// todo: integrate into G2
mv largestGradePart(const mv &X, int *gradeIdx /* = NULL */) {
	int nbBits = bitCount16(X.gu()); // bitCount16 also goes into Gaigen 2
	if (nbBits == 1) {
		if (gradeIdx) *gradeIdx = highestOneBit16(X.gu());
		return X;
	}
	else if (nbBits == 0) {
		if (gradeIdx) *gradeIdx = 0;
		return mv(0.0f);
	}
	else {
		// loop over all grade
		// if grade is present: sum + square coordinates
		//								 if larger than current -> keep pointer
		mv::Float largestG = 0.0f;
		int largestGidx = -1;
		const mv::Float *largestC = NULL;
		const mv::Float *C = X.m_c;

		for (int i = 0; i <= 5; i++) {
			if ((X.gu() & (1 << i)) == 0) continue;
			else {
				// square, sum 
				mv::Float l = C[0] * C[0];
				int s = mv_gradeSize[i];
				for (int j = 1; j < s; j++) l = C[j] * C[j];

				// check if larger
				if (l > largestG) {
					largestC = C;
					largestG = l;
					largestGidx = i;
					if (gradeIdx) *gradeIdx = i;
				}

				C += mv_gradeSize[i];
			}
		}
		if (largestC)
			return mv((unsigned int)(1 << largestGidx), largestC);
		else {
			if (gradeIdx) *gradeIdx = 0;
			return mv(0.0f);
		}
	}
}

// todo: integrate into G2
/**
Returns grade usage of multivector.
The returned integer is a bitwise or of 
GRADE_0 = 1, 
GRADE_1 = 2, 
GRADE_N = 1 << (N) 
constants.
*/
mv grade(const mv &X, float epsilon /* = 1e-7 */);

// todo: integrate into G2
mv highestGradePart(const mv &X, float epsilon /* = 1e-7 */, int *gradeIdx /* = NULL*/) {
	int g = 5, gu = X.gu(), iX = mv_size[gu], size, i;
	const float *cptr = NULL;
	do {
		if (gu & (1 << g)) {
			size = mv_gradeSize[g];
			iX -= size;
			cptr = X.m_c + iX;
			for (i = 0; i < size; i++) 
				if ((cptr[i] > epsilon) || (-cptr[i] > epsilon)) {
					if (gradeIdx) *gradeIdx = g;
					return mv((unsigned int)(1 << g), cptr);
				}
		}
	} while ((--g)>= 0);

	if (gradeIdx) *gradeIdx = 0;
	return mv(0.0f);
}

// todo: integrate into G2
mv takeGrade(const mv &X, int gradeUsageBitmap) {
	int gua;

	// determine what the grage usage 'gu' of the result should be:
	if (gradeUsageBitmap = ((gua = X.gu()) & gradeUsageBitmap)) { // only execute if any grade will be present in the result
		mv::Float C[8]; 
		mv::Float *bc; 
		const mv::Float *ac; 

		bc = C; ac = X.m_c; // pointers to the coordinates of source (ac) and result (bc)
		for (int i = 1; i <= gradeUsageBitmap; i = i << 1) { // for each grade that is possibly in the result
			if (gua & i) { // determine if grade is present in source
				int s = mv_size[i]; // get the size of grade
				if (gradeUsageBitmap & i) { // determine if grade is present in result
					// copy coordinates
					for (int j = 0; j < s; j++) bc[j] = ac[j];
					bc += s; // increment pointer to result
				}
				ac += s; // increment pointer to source
			}
		}
		return mv(gradeUsageBitmap, C);
	}
	else return mv(0.0f);
}


// todo: integrate into G2
mv deltaProduct(const mv &X, const mv &Y, float epsilon /* = 1e-7 */, int *gradeIdx /* = NULL*/) {
	return highestGradePart(gpEM(X, Y), epsilon, gradeIdx);
}


inline mv randomVector() {
	float c[5] =
	{
		(float)(rand() - RAND_MAX / 2),
		(float)(rand() - RAND_MAX / 2),
		(float)(rand() - RAND_MAX / 2),
		(float)(rand() - RAND_MAX / 2),
		(float)(rand() - RAND_MAX / 2)
	};
	return mv(GRADE_1, c);
}

/** 
Returns a random blade of 'grade' with a (Euclidean) size in range [0, 1.0].
If grade < 0, then a random grade is picked

Currently, rand() is used to generate the blade
Todo: use Mersenne twister or something (license issues?)
*/
mv randomBlade(int grade/* = -1*/, float size /*= 1.0f*/) {
	if (grade < 0) 
		grade = rand() % 6;
	

	if (grade == 0) {
		return mv(size * (-1.0f + 2.0f * (float)rand() / (float)RAND_MAX));
	}
	else if (grade == 5) {
		return mv(GRADE_5, size * (-1.0f + 2.0f * (float)rand() / (float)RAND_MAX));
	}
	else {
		mv result = randomVector();
		for (int g = 1; g < grade; g++) {
			result ^= randomVector();
		}
		result = (-1.0f + 2.0f * (float)rand() / (float)RAND_MAX) * size * unit_e(result); // todo: random factor
		return result;
	}
}

mv randomMultivector(int gradeParts /* = GRADE_0 | GRADE_1 | GRADE_2 | GRADE_3  | GRADE_4 | GRADE_5 */, float size /*= 1.0f*/) {
	mv::Float C[8];
	gradeParts &= GRADE_0 | GRADE_1 | GRADE_2 | GRADE_3 | GRADE_4 | GRADE_5; // to prevent weird input
	int s = mv_size[gradeParts];
	for (int i = 0; i < s; i++) {
		C[i] = -1.0f + 2.0f * (float)rand() * size / (float)RAND_MAX;
	}
	return mv(gradeParts, C);
}

void meetJoin(const mv  &a, const mv &b, mv &m, mv &j, mv::Float smallEpsilon, mv::Float largeEpsilon) {
	mv::Float la = a.largestCoordinate();
	mv::Float lb = b.largestCoordinate();

	// step one: check for near-zero input
	if ((la < smallEpsilon) || (lb < smallEpsilon)) {
		// set both meet and join to 0;
		m.set();
		j.set();
		return; // done
	}

	// determine grade of input
	int ga, gb;
	mv _ca = largestGradePart(a, &ga);
	mv _cb = largestGradePart(b, &gb);

	// normalize (approximatelly) and swap (optionally)
	mv ca, cb;
	if (ga <= gb) {
		ca = op(_ca, 1.0f / la);
		cb = op(_cb, 1.0f / lb);
	}
	else {
		ca = op(_cb, 1.0f / lb);
		cb = op(_ca, 1.0f / la);
		int tempg = ga;
		ga = gb;
		gb = tempg;
	}

	// compute delta product & 'normalize'
	mv d,_d;
	int gd;
	_d = deltaProduct(a, b, smallEpsilon, &gd);
	mv::Float ld = _d.largestCoordinate();
	d = op(_d, 1.0f / ld);

	// if delta product is scalar, we're done:
	if (gd == 0) {
		// a == b (up to scalar)
		m = ca;
		j  = ca;
		// todo: largest coordinate positive?
		return;
	}

	// if grade of delta product is equal to ga + gb, we're done, too
	if (gd == ga + gb) {
		// a and b entirely disjoint
		m.set(1.0f);
		j = unit_e(op(ca, cb));
		// todo: largest coordinate positive?
		return;
	}

	// init join
	j = I5;
	int Ej = 5 - ((ga + gb + gd) >> 1);

	// check join excessity
	if (Ej == 0) {
		m = lcontEM(d, j);
		// todo: largest coordinate positive?
		return;
	}

	// init meet 
	m = 1.0f;
	int Em = ((ga + gb - gd) >> 1);

	// init s, the dual of the delta product:
	mv s = lcontEM(d, I5i);

	// precompute inverse of ca
	mv cai = inverseEM(ca);

	mv e[5] = {
		mv(GRADE_1, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		mv(GRADE_1, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
		mv(GRADE_1, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
		mv(GRADE_1, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		mv(GRADE_1, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)
	};

//	printf("d = %s\n", d.c_str_e());

	for (unsigned int i = 0; i < 5; i++) {
		// compute next factor 'c'
		mv c = lcontEM(lcontEM(e[i], s), s);		

		// check if 'c' is OK to use:
		if (c.largestCoordinate() < largeEpsilon)
			continue;

		// compute projection, rejection of 'c' wrt to 'ca'
		mv cp, cr; // c projected, c rejected
		mv tmpc = lcontEM(c, ca);
		cp = lcontEM(tmpc, cai); // use correct inverse because otherwise cr != c - cp
		cr = subtract(c, cp);

		// if 'c' has enough of it in 'ca', then add to meet
		if (cp.largestCoordinate() > largeEpsilon) {
//			printf("m%d = %s\n", Em, cp.c_str_e());
			m = op(m, cp);
			Em--;	
			if (Em == 0) {
				j = op(d, m); // ???? here error?
				m = unit_e(m);
				j = unit_e(j);

				// todo: largest coordinate positive?
				return;
			}
		}

		if (cr.largestCoordinate() > largeEpsilon) {
			j = lcontEM(cr, j);
			Ej--;	
			if (Ej == 0) {
				m = lcontEM(d, j);
				m = unit_e(m);
				j = unit_e(j);

				// todo: largest coordinate positive?
				return;
			}
		}

		// optionally remove 'c' from 's' (do that?)
		// put this also in other meet/join algos?
		s = lcontEM(c, s);
	}

	throw std::string("Error while computing meet & join!");
}

} /* end of namespace c3ga */
