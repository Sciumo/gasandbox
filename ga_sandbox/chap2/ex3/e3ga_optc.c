#include <stdlib.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void e3gai_general_gp(const float *a[], const float *b[], float *c) {
	const float *an, *bn;
	memset(c, 0, sizeof(float) * 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
			c[4] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[5] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[6] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] ;
			c[7] += + an[2] * bn[2] + an[1] * bn[1] + an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] ;
			c[7] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
			c[4] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[5] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[6] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[1] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[7] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_general_lcont(const float *a[], const float *b[], float *c) {
	const float *an, *bn;
	memset(c, 0, sizeof(float) * 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[3]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[1] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_general_op(const float *a[], const float *b[], float *c) {
	const float *an, *bn;
	memset(c, 0, sizeof(float) * 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[4] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[5] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[6] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[7] += + an[2] * bn[2] + an[1] * bn[1] + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[7] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
}

void e3gai_general_scp(const float *a[], const float *b[], float *c) {
	const float *an, *bn;
	memset(c, 0, sizeof(float) * 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_opt_01_op_02(const float *a, const float *b, float *c) {
	c[0] = + a[0] * b[0] ;
	c[1] = + a[0] * b[1] ;
	c[2] = + a[0] * b[2] ;
}

void e3gai_opt_02_op_02(const float *a, const float *b, float *c) {
	c[0] = - a[2] * b[1] + a[1] * b[2] ;
	c[1] = + a[2] * b[0] - a[0] * b[2] ;
	c[2] = - a[1] * b[0] + a[0] * b[1] ;
}

void e3gai_opt_04_op_02(const float *a, const float *b, float *c) {
	c[0] = + a[0] * b[0] + a[1] * b[1] + a[2] * b[2] ;
}

void e3gai_opt_02_lcont_04(const float *a, const float *b, float *c) {
	c[0] = - a[1] * b[2] + a[2] * b[1] ;
	c[1] = + a[0] * b[2] - a[2] * b[0] ;
	c[2] = - a[0] * b[1] + a[1] * b[0] ;
}

void e3gai_opt_02_lcont_02(const float *a, const float *b, float *c) {
	c[0] = + a[0] * b[0] + a[1] * b[1] + a[2] * b[2] ;
}

void e3gai_opt_om_01x01(const float *a, const float *b, float *c) {
	c[0] = + a[0] * b[0] ;
}

void e3gai_opt_om_03x03(const float *a, const float *b, float *c) {
	c[0] = + a[0] * b[0] + a[1] * b[1] + a[2] * b[2] ;
	c[1] = + a[3] * b[0] + a[4] * b[1] + a[5] * b[2] ;
	c[2] = + a[6] * b[0] + a[7] * b[1] + a[8] * b[2] ;
}

void e3gai_copy(float *dest, const float *src, int length) {
	memcpy(dest, src, length * sizeof(float));
}

void e3gai_reverse(float *a[]) {
	float *an;
	if (an = a[2]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
	}
	if (an = a[3]) {
		an[0] = -an[0];
	}
}

void e3gai_cliffordConjugate(float *a[]) {
	float *an;
	if (an = a[1]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
	}
	if (an = a[2]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
	}
}

void e3gai_involution(float *a[]) {
	float *an;
	if (an = a[1]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
	}
	if (an = a[3]) {
		an[0] = -an[0];
	}
}

void e3gai_negate(float *dest, const float *src, int length) {
	int i;
	for (i = 0; i < length; i++)
		dest[i] = -src[i];
}

float e3gai_norm_a(float a[], int nb) {
	int i;
	float norm = 0.0;
	for (i = 0; i < nb; i++)
		norm += a[i] * a[i];
	return norm;
}

void e3gai_addSameGradeUsage(float *c, const float *a, const float *b, int length) {
	int i;
	for (i = 0; i < length; i++)
		c[i] = a[i] + b[i];
}

void e3gai_add(const float *a[4], const float *b[4], float *c[4]) {
	float const *an, *bn;
	float *cn;

	if (cn = c[0]) {
		bn = b[0];
		if ((an = a[0]) && bn) {
			cn[0] = an[0] + bn[0];
		}
		else if (an) {
			cn[0] = an[0];
		}
		else {
			cn[0] = bn[0];
		}
	}
	if (cn = c[1]) {
		bn = b[1];
		if ((an = a[1]) && bn) {
			cn[0] = an[0] + bn[0];
			cn[1] = an[1] + bn[1];
			cn[2] = an[2] + bn[2];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
		}
	}
	if (cn = c[2]) {
		bn = b[2];
		if ((an = a[2]) && bn) {
			cn[0] = an[0] + bn[0];
			cn[1] = an[1] + bn[1];
			cn[2] = an[2] + bn[2];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
		}
	}
	if (cn = c[3]) {
		bn = b[3];
		if ((an = a[3]) && bn) {
			cn[0] = an[0] + bn[0];
		}
		else if (an) {
			cn[0] = an[0];
		}
		else {
			cn[0] = bn[0];
		}
	}
}

void e3gai_subSameGradeUsage(float *c, const float *a, const float *b, int length) {
	int i;
	for (i = 0; i < length; i++)
		c[i] = a[i] - b[i];
}

void e3gai_sub(const float *a[4], const float *b[4], float *c[4]) {
	float const *an, *bn;
	float *cn;

	if (cn = c[0]) {
		bn = b[0];
		if ((an = a[0]) && bn) {
			cn[0] = an[0] - bn[0];
		}
		else if (an) {
			cn[0] = an[0];
		}
		else {
			cn[0] = -bn[0];
		}
	}
	if (cn = c[1]) {
		bn = b[1];
		if ((an = a[1]) && bn) {
			cn[0] = an[0] - bn[0];
			cn[1] = an[1] - bn[1];
			cn[2] = an[2] - bn[2];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
		}
	}
	if (cn = c[2]) {
		bn = b[2];
		if ((an = a[2]) && bn) {
			cn[0] = an[0] - bn[0];
			cn[1] = an[1] - bn[1];
			cn[2] = an[2] - bn[2];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
		}
	}
	if (cn = c[3]) {
		bn = b[3];
		if ((an = a[3]) && bn) {
			cn[0] = an[0] - bn[0];
		}
		else if (an) {
			cn[0] = an[0];
		}
		else {
			cn[0] = -bn[0];
		}
	}
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
