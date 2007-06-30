
// Generated on 2007-06-30 15:54:57 by G2 0.1 from 'E:\gasandbox\ga_sandbox\libgasandbox\c3ga.gs2'

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


#include "c3ga.h"

namespace {
	// 1.0*e1
	void projectE1ontoG2(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 1.0f * c[0];
		v[2] = 1.0f * c[1];
		v[3] = 1.0f * c[2];
		v[4] = 1.0f * c[9];
	}
	// 1.0*e2
	void projectE2ontoG2(const float *c, float *v) {
		v[0] = -1.0f * c[0];
		v[1] = 0.0f;
		v[2] = 1.0f * c[3];
		v[3] = -1.0f * c[5];
		v[4] = 1.0f * c[6];
	}
	// 1.0*e3
	void projectE3ontoG2(const float *c, float *v) {
		v[0] = -1.0f * c[1];
		v[1] = -1.0f * c[3];
		v[2] = 0.0f;
		v[3] = 1.0f * c[4];
		v[4] = 1.0f * c[7];
	}
	// 1.0*e4
	void projectE4ontoG2(const float *c, float *v) {
		v[0] = -1.0f * c[2];
		v[1] = 1.0f * c[5];
		v[2] = -1.0f * c[4];
		v[3] = 0.0f;
		v[4] = 1.0f * c[8];
	}
	// 1.0*e5
	void projectE5ontoG2(const float *c, float *v) {
		v[0] = -1.0f * c[9];
		v[1] = -1.0f * c[6];
		v[2] = -1.0f * c[7];
		v[3] = -1.0f * c[8];
		v[4] = 0.0f;
	}
	// 1.0*e1^e2
	void projectE12ontoG3(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = -1.0f * c[8];
		v[3] = -1.0f * c[7];
		v[4] = -1.0f * c[4];
	}
	// 1.0*e1^e3
	void projectE13ontoG3(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 1.0f * c[8];
		v[2] = 0.0f;
		v[3] = -1.0f * c[6];
		v[4] = -1.0f * c[5];
	}
	// 1.0*e1^e4
	void projectE14ontoG3(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 1.0f * c[7];
		v[2] = 1.0f * c[6];
		v[3] = 0.0f;
		v[4] = -1.0f * c[3];
	}
	// 1.0*e2^e3
	void projectE23ontoG3(const float *c, float *v) {
		v[0] = -1.0f * c[8];
		v[1] = 0.0f;
		v[2] = 0.0f;
		v[3] = -1.0f * c[9];
		v[4] = -1.0f * c[2];
	}
	// 1.0*e3^e4
	void projectE34ontoG3(const float *c, float *v) {
		v[0] = -1.0f * c[6];
		v[1] = -1.0f * c[9];
		v[2] = 0.0f;
		v[3] = 0.0f;
		v[4] = -1.0f * c[0];
	}
	// 1.0*e2^e4
	void projectE24ontoG3(const float *c, float *v) {
		v[0] = -1.0f * c[7];
		v[1] = 0.0f;
		v[2] = 1.0f * c[9];
		v[3] = 0.0f;
		v[4] = 1.0f * c[1];
	}
	// 1.0*e2^e5
	void projectE25ontoG3(const float *c, float *v) {
		v[0] = -1.0f * c[4];
		v[1] = 0.0f;
		v[2] = 1.0f * c[2];
		v[3] = -1.0f * c[1];
		v[4] = 0.0f;
	}
	// 1.0*e3^e5
	void projectE35ontoG3(const float *c, float *v) {
		v[0] = -1.0f * c[5];
		v[1] = -1.0f * c[2];
		v[2] = 0.0f;
		v[3] = 1.0f * c[0];
		v[4] = 0.0f;
	}
	// 1.0*e4^e5
	void projectE45ontoG3(const float *c, float *v) {
		v[0] = -1.0f * c[3];
		v[1] = 1.0f * c[1];
		v[2] = -1.0f * c[0];
		v[3] = 0.0f;
		v[4] = 0.0f;
	}
	// 1.0*e1^e5
	void projectE15ontoG3(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 1.0f * c[4];
		v[2] = 1.0f * c[5];
		v[3] = 1.0f * c[3];
		v[4] = 0.0f;
	}
	// 1.0*e3^e4^e5
	void projectE345ontoG4(const float *c, float *v) {
		v[0] = 1.0f * c[1];
		v[1] = 1.0f * c[0];
		v[2] = 0.0f;
		v[3] = 0.0f;
		v[4] = 0.0f;
	}
	// 1.0*e2^e4^e5
	void projectE245ontoG4(const float *c, float *v) {
		v[0] = -1.0f * c[2];
		v[1] = 0.0f;
		v[2] = -1.0f * c[0];
		v[3] = 0.0f;
		v[4] = 0.0f;
	}
	// 1.0*e2^e3^e5
	void projectE235ontoG4(const float *c, float *v) {
		v[0] = 1.0f * c[3];
		v[1] = 0.0f;
		v[2] = 0.0f;
		v[3] = 1.0f * c[0];
		v[4] = 0.0f;
	}
	// 1.0*e1^e4^e5
	void projectE145ontoG4(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 1.0f * c[2];
		v[2] = -1.0f * c[1];
		v[3] = 0.0f;
		v[4] = 0.0f;
	}
	// 1.0*e1^e2^e5
	void projectE125ontoG4(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 1.0f * c[3];
		v[3] = -1.0f * c[2];
		v[4] = 0.0f;
	}
	// 1.0*e1^e3^e5
	void projectE135ontoG4(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = -1.0f * c[3];
		v[2] = 0.0f;
		v[3] = 1.0f * c[1];
		v[4] = 0.0f;
	}
	// 1.0*e1^e3^e4
	void projectE134ontoG4(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = -1.0f * c[4];
		v[2] = 0.0f;
		v[3] = 0.0f;
		v[4] = -1.0f * c[1];
	}
	// 1.0*e1^e2^e4
	void projectE124ontoG4(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 1.0f * c[4];
		v[3] = 0.0f;
		v[4] = 1.0f * c[2];
	}
	// 1.0*e1^e2^e3
	void projectE123ontoG4(const float *c, float *v) {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		v[3] = -1.0f * c[4];
		v[4] = -1.0f * c[3];
	}
	// 1.0*e2^e3^e4
	void projectE234ontoG4(const float *c, float *v) {
		v[0] = 1.0f * c[4];
		v[1] = 0.0f;
		v[2] = 0.0f;
		v[3] = 0.0f;
		v[4] = -1.0f * c[0];
	}
	typedef void (*projectFuncfloat)(const float*, float*);
	projectFuncfloat g_projectFuncTablefloat[32] = {
		NULL, 
			projectE1ontoG2, 
			projectE2ontoG2, 
			projectE12ontoG3, 
			projectE3ontoG2, 
			projectE13ontoG3, 
			projectE23ontoG3, 
			projectE123ontoG4, 
			projectE4ontoG2, 
			projectE14ontoG3, 
			projectE24ontoG3, 
			projectE124ontoG4, 
			projectE34ontoG3, 
			projectE134ontoG4, 
			projectE234ontoG4, 
			NULL, 
			projectE5ontoG2, 
			projectE15ontoG3, 
			projectE25ontoG3, 
			projectE125ontoG4, 
			projectE35ontoG3, 
			projectE135ontoG4, 
			projectE235ontoG4, 
			NULL, 
			projectE45ontoG3, 
			projectE145ontoG4, 
			projectE245ontoG4, 
			NULL, 
			projectE345ontoG4, 
			NULL, 
			NULL, 
			NULL
	};
} // end of anonymous namespace


/**
Factorizes blades. Input coordinates as defined by general multivector type.
Return of vectors as defined by vector type.

Input:
k = grade of input
c = coordinates of input
ortho = orthogonalize factors (if not orthogonalized, scale will not have the correct value

Output:
scale: used to return scale of blade
factors: array of points to arrays of float [5][5]

*/
unsigned int factorizeBlade(
int k,
	const float *c,
	float **factors,
	float &scale,
	bool ortho) {
	const int N = 5;

	if (k == 0) {
		scale = 0.0f;
		return 0;
	}

	// pseudoscalar?
	if (k == N) {
		factors[0][1] = factors[0][2] = factors[0][3] = factors[0][4] = 			
			factors[1][0] = factors[1][2] = factors[1][3] = factors[1][4] = 			
			factors[2][0] = factors[2][1] = factors[2][3] = factors[2][4] = 			
			factors[3][0] = factors[3][1] = factors[3][2] = factors[3][4] = 			
			factors[4][0] = factors[4][1] = factors[4][2] = factors[4][3] = 			
			0.0f;
		factors[0][0] = factors[1][1] = factors[2][2] = factors[3][3] = factors[4][4] =  1.0f;

		scale = c[0] * 1.0f;
		return N;
	}

	float inputScale = c[0] * c[0];
	{
		int nbBlades = mv_gradeSize[k];
		for (int i = 1; i < nbBlades; i++) inputScale += c[i] * c[i];	
		inputScale = sqrt(inputScale);
	}

	// zero input?:
	if (inputScale == 0.0f) {
		scale = 0.0f;
		return 0;
	}

	// vector?
	if (k == 1) {
		// copy all vector coords to first factor:
		factors[0][0] = c[0];
		factors[0][1] = c[1];
		factors[0][2] = c[2];
		factors[0][3] = c[3];
		factors[0][4] = c[4];
		scale = inputScale; 
		return 1;  
	}

	// find largest basis blade:
	int baseIndex = mv_size[(1 << k) - 1]; // get base index for grade 'k'
	int bmE = mv_basisElementBitmapByIndex[baseIndex + 0];
	float scE = c[0] * mv_basisElementBitmapByIndex[baseIndex + 0];
	{
		float scC = (c[0] < 0.0f) ? -c[0] : c[0];
		for (int i = 1; i < mv_gradeSize[k]; i++) {
			float ciAbs = (c[i] < 0.0f) ? -c[i] : c[i];
			if (ciAbs > scC) {
				scC = ciAbs;
				bmE = mv_basisElementBitmapByIndex[baseIndex + i];
				scE = c[i] * mv_basisElementBitmapByIndex[baseIndex + i];
			}
		}
	}

	// compute scale (sign)
	scale = inputScale;
	if (scE < 0) {
		scale *= -1.0f;

		// take care of orientation of blade:
		if ((k & 1) == 1) scale *= -1.0f;
	}

	// fix sign issues (see Leo's notes)
	if ((k % 4) == 2) scale *= -1.0f;


	// `project' each of the basis vectors onto the blade
	int fIdx = 0;
	for (int i = 0; i < 5; i++) {
		int bvM = 1 << i;
		if ((bmE & bvM) == 0) continue;

		// compute inner product of (bmE ^ bvM) . bmE
		int bm = bmE ^ bvM;
		g_projectFuncTablefloatfloat[bm](c, factors[fIdx]);

		fIdx++;
		if (fIdx == k) break;
	}


	if (ortho) { // do a gram-schmidt of the factors
		for (int i = 0; i < k; i++) {
			float Fi = factors[i];

			// subtract all ortho factor so far:
			for (int j = 0; j < i; j++) {
				float Fj = factors[j];

				// inner product with ortho factors so far:
				float s = Fi[0] * Fj[0] + Fi[1] * Fj[1] + Fi[2] * Fj[2] + Fi[3] * Fj[3] + Fi[4] * Fj[4] ;

				// subtract s * factors[j] from factors[i]:
				Fi[0] -= s * Fj[0];
				Fi[1] -= s * Fj[1];
				Fi[2] -= s * Fj[2];
				Fi[3] -= s * Fj[3];
				Fi[4] -= s * Fj[4];
			}

			// normalize each factor
			float n = sqrtf(Fi[0] * Fi[0] + Fi[1] * Fi[1] + Fi[2] * Fi[2] + Fi[3] * Fi[3] + Fi[4] * Fi[4] );
			if (n != 0.0f) {
				Fi[0] /= n;
				Fi[1] /= n;
				Fi[2] /= n;
				Fi[3] /= n;
				Fi[4] /= n;
			}
		}
	}

	return k;
}








