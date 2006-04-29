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

} /* end of namespace e3ga */
