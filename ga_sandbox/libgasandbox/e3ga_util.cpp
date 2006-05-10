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

#include "e3ga_util.h"
#include "gabits.h"

namespace e3ga {

rotor rotorFromVectorToVector(const vector &v1, const vector &v2) {
	if (_Float(scp(v1, v2)) < -0.99999f) {
		// (near) 180 degree rotation:
		vector tmp = _vector(lcont(v1, op(v1, v2)));
		double n2 = _Float(norm_e2(tmp));
		if (n2 != 0.0f) tmp = _vector(tmp * (1.0f /  (mv::Float)sqrt(n2)));
		else
			tmp = (_Float(norm_e2(v1 ^ e1)) > _Float(norm_e2(v1 ^ e2))) ? _vector(e1) : _vector(e2);
		return _rotor(unit_e(v1 ^ tmp));
	}
	else {
		mv::Float s = (mv::Float)sqrt(2.0 * (1.0f + _Float(v2 << v1)));
		return _rotor((1.0 + v2 * v1) * (1.0f / s));
	}
}

mv exp(const mv &x, int order /*= 9*/) {
	// todo:
	// first try special cases:
	mv x2 = x * x;
	mv::Float s_x2 = _Float(x2);
	if (_Float(norm_e2(x2 - s_x2)) == 0.0f) {
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

void reciprocalFrame(const e3ga::vector *IF, e3ga::vector *RF, int nbVectors) {
	if (nbVectors == 0) return; // nothing to do
	else if (nbVectors == 1) {
		// trivial case
		if (_Float(norm_r2(IF[0])) == 0.0)
			throw std::string("reciprocalFrame(): null vector");
		RF[0] = inverse(IF[0]);
		return;
	}
	else {
		// compute pseudoscalar 'I' of space spanned by input frame:
		mv I = IF[0];
		for (int i = 1; i < nbVectors; i++) I ^= IF[i];
		if (_Float(norm_r2(I)) == 0.0) 
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
			RF[i] = _vector(P << Ii);
		}
		return;
	}

}


/// factors blade into vectors (euclidean unit length), returns  scale (or throws exception when non-blade is passed)
mv::Float factorizeBlade(const mv &X, vector factor[], int gradeOfX /* = -1 */) {
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
	
	mv::Float coords[3] = {0.0, 0.0, 0.0};
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
	    factor[i] = _vector(unit_e(lcont(lcont(ei, Bc), Bc))); // no inverse(Bc) required, since Bc is always unit
	    
	    // remove f[i] from Bc
	    Bc = lcont(factor[i], Bc);
	}
	
	// last factor = what is left of the input blade
	factor[k-1] = _vector(unit_e(Bc)); // already normalized, but renormalize to remove any FP round-off error
	
	return scale;
}

#ifdef RIEN
// todo: integrate into G2
mv largestGradePart(const mv &X, int *gradeIdx = NULL) {
	int nbBits = bitCount16(X.gu());
	if (nbBits == 1) {
		return X;
	}
	else if (nbBits == 0) return mv(0.0f);
	else {
		// loop over all grade
		// if grade is present: sum + square coordinates
		//								 if larger than current -> keep pointer
		mv::Float largestG = 0.0f;
		int largestGidx = -1;
		const mv::Float *largestC = NULL;
		const mv::Float *C = X.m_c;

		for (int i = 0; i <= 3; i++) {
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
		else return mv(0.0f);
	}
}

// todo: integrate into G2
mv highestGradePart(const mv &X, double epsilon /* = 1e-14 */, int *gradeIdx = NULL) {
	// todo:
	/*
	int g = 3, gu = a.gradeUsage(), ia = e3gai_mvSize[gu], size, i;
	const double *cptr;
	do {
		if (gu & (1 << g)) {
			size = e3gai_gradeSize[g];
			ia -= size;
			cptr = a.c + ia;
			for (i = 0; i < size; i++) 
				if (fabs(cptr[i]) > epsilon) {
					set(1 << g, a.c + ia);
					return g;
				}
		}
	} while ((--g)>= 0); // bug fix on 2003 11 16, used to be while ((--g) _>_ 0)
//return -1; // modification on 20020828

	setUsage(0);
	return 0;
*/
}

/*
Todo: 
-largest grade
-delta product
*/



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
	int ga = a.grade();
	int gb = b.grade();
	c3gai _ca, _cb;
	if (ga < 0) { // if we are not handed homogeneous multivectors, take the grade parts with the largest norm
		ga = a.largestGrade();
		_ca.takeGrade(a, 1 << ga);
	}
	else _ca.copy(a);
	if (gb < 0) {
		gb = b.largestGrade();
		_cb.takeGrade(b, 1 << gb);
	}
	else _cb.copy(b);

	// normalize (approximatelly) and swap (optionally)
	c3gai ca, cb;
	if (ga <= gb) {
		ca.op(_ca, 1.0 / la);
		cb.op(_cb, 1.0 / lb);
	}
	else {
		ca.op(_cb, 1.0 / lb);
		cb.op(_ca, 1.0 / la);
		int tempg = ga;
		ga = gb;
		gb = tempg;
	}

	// compute delta product & 'normalize'
	c3gai d,_d;
	int gd = _d.deltaProduct(a, b); // internally uses epsilon of 10e-14  (can not be influenced right now)
	mv::Float ld = _d.largestCoordinate();
	d.op(_d, 1.0 / ld);

	// if delta product is scalar, we're done:
	if (gd == 0) {
		// a == b (up to scalar)
		m.copy(ca);
		j.copy(ca);
		// todo: largest coordinate positive?
		return;
	}

	// if grade of delta product is equal to ga + gb, we're done, too
	if (gd == ga + gb) {
		// a and b entirely disjoint
		m.setScalar(1.0);
		j.op(ca, cb);
		// todo: largest coordinate positive?
		return;
	}

	// init join
	j.copy(c3gai::I);
	int Ej = 5 - ((ga + gb + gd) >> 1);

	// check join excessity
	if (Ej == 0) {
		m.lcem(d, j);
		// todo: largest coordinate positive?
		return;
	}

	// init meet 
	m.setScalar(1.0);
	int Em = ((ga + gb - gd) >> 1);

	// init s, the dual of the delta product:
	c3gai s;
	s.lcem(d, c3gai::Ii);

	// precompute inverse of ca
	c3gai cai;
	cai.versorInverseEM(ca);

	for (unsigned int i = 0; i < 5; i++) {
		// compute next factor 'c'
		c3gai c;
		// since we don't 'whittle down' s, this is (usually) useless:
//		if (s.grade() == 1) {
//			c.copy(s);
//		}
//		else 
		{
			c3gai tmpc;
			tmpc.lcem(*c3gai::bv[i], s);
			c.lcem(tmpc, s);
		}

		// check if 'c' is OK to use:
		if (c.largestCoordinate() < largeEpsilon)
			continue;

		// compute projection, rejection of 'c' wrt to 'ca'
		c3gai cp, cr; // c projected, c rejected
		c3gai tmpc;
		tmpc.lcem(c, ca);
		cp.lcem(tmpc, cai); // use correct inverse because otherwise cr != c - cp
		cr.sub(c, cp);

		// if 'c' has enough of it in 'ca', then add to meet
		if (cp.largestCoordinate() > largeEpsilon) {
			c3gai tmpm;
			tmpm.op(m, cp);
			m.copy(tmpm);
			Em--;	
			if (Em == 0) {
				j.op(d, m);
				// todo: largest coordinate positive?
				return;
			}
		}

		if (cr.largestCoordinate() > largeEpsilon) {
			c3gai tmpj;
			tmpj.lcem(cr, j);
			j.copy(tmpj);
			Ej--;	
			if (Ej == 0) {
				m.lcem(d, j);
				// todo: largest coordinate positive?
				return;
			}
		}

		// optionally remove 'c' from 's' (do that?)
	}

	throw "Error!";

}

#endif

} /* end of namespace e3ga */
