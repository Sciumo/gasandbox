#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "ga.h"


CLASSNAME::CLASSNAME() {

}

CLASSNAME::CLASSNAME(GAIM_CLASSNAME &a) {
	copy(a);
}

CLASSNAME::~CLASSNAME() {

}

CLASSNAME &CLASSNAME::operator=(const CLASSNAME &a) {
	copy(a);
	return *this;
}

CLASSNAME &CLASSNAME::operator=(GAIM_FLOAT f) {
	set(GRADE0, &f);
	return *this;
}


CLASSNAME &CLASSNAME::getTemp() {
	// gets a temporary variable (from Stroustup (heaven help you if you write an expression which requires more than MV_MAX_TEMP temporaries))
	static int idx = 0;
	static CLASSNAME *temp = NULL;
	if (!temp) {
		int i;
		temp = new CLASSNAME[MV_MAX_TEMP];
		for (i = 0; i < MV_MAX_TEMP; i++) {
			temp[i].setUsage(0xf | (0x7 << 4) | 0x1000000);
			temp[i].setUsage(0x1000000);
		}
	}
	if (idx == MV_MAX_TEMP) idx = 0;
/*	if (!(temp[idx].usage & 0x1000000)) {
		printf("Whaaa!\n");
	}*/
	return temp[idx++];
}

#ifdef GAIM_FUNCTION_TAKEGRADE
CLASSNAME &CLASSNAME::grade(int g) const {
	CLASSNAME &result = getTemp();
	result.takeGrade(*this, g);
	return result;
}
#endif // GAIM_FUNCTION_TAKEGRADE


#ifdef GAIM_FUNCTION_REVERSE
CLASSNAME &CLASSNAME::operator++() const {
	CLASSNAME &result = getTemp();
	((GAIM_CLASSNAME)result).reverse(*this);
	return result;
}
#endif // GAIM_FUNCTION_REVERSE

#ifdef GAIM_FUNCTION_CLIFFORDCONJUGATE
CLASSNAME &CLASSNAME::operator~() const {
	CLASSNAME &result = getTemp();
	((GAIM_CLASSNAME)result).cliffordConjugate(*this);
	return result;
}
#endif // GAIM_FUNCTION_CLIFFORDCONJUGATE

#ifdef GAIM_FUNCTION_GRADEINVOLUTION
CLASSNAME &CLASSNAME::operator--() const {
	CLASSNAME &result = getTemp();
	((GAIM_CLASSNAME)result).gradeInvolution(*this);
	return result;
}
#endif // GAIM_FUNCTION_GRADEINVOLUTION

#ifdef GAIM_PRODUCT_GP
CLASSNAME &CLASSNAME::operator*=(const CLASSNAME &a) {
	CLASSNAME tmp;
	tmp.gp(*this, a);
	this->copy(tmp);
	return *this;
}
CLASSNAME &CLASSNAME::operator*=(GAIM_FLOAT a) {
	CLASSNAME tmp;
	tmp.op(a, *this);
	this->copy(tmp);
	return *this;
}
CLASSNAME &gp(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.gp(a, b);
	return result;
}
CLASSNAME &gp(GAIM_FLOAT a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.op(a, b);
	return result;
}
CLASSNAME &CLASSNAME::dual() const {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.gp(*this, Ii);
	return result;
}
#endif // GAIM_PRODUCT_GP


#ifdef GAIM_FUNCTION_VERSORINVERSE
CLASSNAME &CLASSNAME::versorInverse() const {
	CLASSNAME &result = getTemp();
	result.versorInverse(*this);
	return result;
}  
#endif
#ifdef GAIM_FUNCTION_LOUNESTOINVERSE
CLASSNAME &CLASSNAME::lounestoInverse() const {
	CLASSNAME &result = getTemp();
	result.lounestoInverse(*this);
	return result;
}  
#endif
#ifdef GAIM_FUNCTION_GENERALINVERSE
CLASSNAME &CLASSNAME::generalInverse() const {
	CLASSNAME &result = getTemp();
	result.generalInverse(*this);
	return result;
}  
#endif

#ifdef GAIM_PRODUCT_IGP
CLASSNAME &CLASSNAME::inverse() const {
	CLASSNAME &result = getTemp();
	result.inverse(*this);
	return result;
}  

CLASSNAME &CLASSNAME::operator/=(const CLASSNAME &a) {
	CLASSNAME tmp, tmp2;
	tmp2.inverse(a);
	tmp.gp(*this, tmp2);
	this->copy(tmp);
	return *this;
}
CLASSNAME &CLASSNAME::operator/=(GAIM_FLOAT a) {
	CLASSNAME tmp;
	tmp.op(1.0f / a, *this);
	this->copy(tmp);
	return *this;
}
#endif // GAIM_PRODUCT_IGP

/*
add
sub
*/

#ifdef GAIM_PRODUCT_SCP
CLASSNAME &CLASSNAME::operator%=(const CLASSNAME &a) {
	CLASSNAME tmp;
	tmp.scp(*this, a);
	this->copy(tmp);
	return *this;
}
CLASSNAME &CLASSNAME::operator%=(GAIM_FLOAT a) {
	GAIM_FLOAT f = scalar() * a;
	setScalar(&f);
	return *this;
}
CLASSNAME &scp(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.scp(a, b);
	return result;
}
CLASSNAME &scp(GAIM_FLOAT a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.set(GRADE0, a * b.scalar());
	return result;
}
#endif // GAIM_PRODUCT_SCP

#ifdef GAIM_PRODUCT_LCONT
CLASSNAME &lcont(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.lcont(a, b);
	return result;
}
CLASSNAME &CLASSNAME::operator<<=(const CLASSNAME &a) {
	CLASSNAME tmp;
	tmp.lcont(*this, a);
	this->copy(tmp);
	return *this;
}
#endif // GAIM_PRODUCT_LCONT

#ifdef GAIM_PRODUCT_RCONT
CLASSNAME &rcont(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.rcont(a, b);
	return result;
}
CLASSNAME &CLASSNAME::operator>>=(const CLASSNAME &a) {
	CLASSNAME tmp;
	tmp.rcont(*this, a);
	this->copy(tmp);
	return *this;
}
#endif // GAIM_PRODUCT_RCONT

#ifdef GAIM_PRODUCT_HIP
CLASSNAME &hip(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.hip(a, b);
	return result;
}
CLASSNAME &hip(GAIM_FLOAT a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp(), CLASSNAME_a(a);
	result.hip(CLASSNAME_a, b);
	return result;
}
CLASSNAME &hip(const CLASSNAME &a, GAIM_FLOAT b) {
	CLASSNAME &result = CLASSNAME::getTemp(), CLASSNAME_b(b);
	result.hip(a, CLASSNAME_b);
	return result;
}
#endif // GAIM_PRODUCT_HIP

#ifdef GAIM_PRODUCT_MHIP
CLASSNAME &mhip(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.mhip(a, b);
	return result;
}
CLASSNAME &mhip(GAIM_FLOAT a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp(), CLASSNAME_a(a);
	result.mhip(CLASSNAME_a, b);
	return result;
}
CLASSNAME &mhip(const CLASSNAME &a, GAIM_FLOAT b) {
	CLASSNAME &result = CLASSNAME::getTemp(), CLASSNAME_b(b);
	result.mhip(a, CLASSNAME_b);
	return result;
}
#endif // GAIM_PRODUCT_MHIP


#ifdef GAIM_PRODUCT_OP
CLASSNAME &op(GAIM_FLOAT a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.op(a, b);
	return result;
}
CLASSNAME &op(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.op(a, b);
	return result;
}
CLASSNAME &CLASSNAME::operator^=(const CLASSNAME &a) {
	CLASSNAME tmp;
	tmp.op(*this, a);
	this->copy(tmp);
	return *this;
}
CLASSNAME &CLASSNAME::operator^=(GAIM_FLOAT a) {
	CLASSNAME tmp;
	tmp.op(a, *this);
	this->copy(tmp);
	return *this;
}
#endif // GAIM_PRODUCT_OP

#ifdef GAIM_FUNCTION_MEETJOIN
CLASSNAME &meet(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.meet(a, b);
	return result;
}

CLASSNAME &join(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.join(a, b);
	return result;
}

#endif // GAIM_FUNCTION_MEETJOIN


#ifdef GAIM_FUNCTION_ADD
CLASSNAME &add(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.add(a, b);
	return result;
}
CLASSNAME &add(GAIM_FLOAT a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.add(a, b);
	return result;
}
CLASSNAME &CLASSNAME::operator+=(const CLASSNAME &a) {
	CLASSNAME tmp;
	tmp.add(*this, a);
	this->copy(tmp);
	return *this;
}
CLASSNAME &CLASSNAME::operator+=(GAIM_FLOAT a) {
	CLASSNAME tmp;
	tmp.add(a, *this);
	this->copy(tmp);
	return *this;
}
#endif // GAIM_FUNCTION_ADD

#ifdef GAIM_FUNCTION_SUBSTRACT
CLASSNAME &sub(const CLASSNAME &a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.sub(a, b);
	return result;
}
CLASSNAME &sub(GAIM_FLOAT a, const CLASSNAME &b) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.sub(a, b);
	return result;
}
CLASSNAME &CLASSNAME::operator-=(const CLASSNAME &a) {
	CLASSNAME tmp;
	tmp.sub(*this, a);
	this->copy(tmp);
	return *this;
}
CLASSNAME &CLASSNAME::operator-=(GAIM_FLOAT a) {
	CLASSNAME tmp;
	tmp.add(a, *this);
	this->copy(tmp);
	return *this;
}
#endif // GAIM_FUNCTION_SUBSTRACT

#ifdef GAIM_FUNCTION_NEGATE
CLASSNAME &negate(const CLASSNAME &a) {
	CLASSNAME &result = CLASSNAME::getTemp();
	result.negate(a);
	return result;
}
#endif //GAIM_FUNCTION_NEGATE



#ifdef GAIM_FUNCTION_NORMALIZE
CLASSNAME &CLASSNAME::normal() const {
	CLASSNAME &result = getTemp();
	result.normalize(*this, 1);
	return result;
}
#endif // GAIM_FUNCTION_NORMALIZE


#ifdef GAIM_PRODUCT_OM
CLASSNAME_OM::CLASSNAME_OM(const CLASSNAME *vectorImages[3]) {
	initOuterMorphism(vectorImages);
}	

CLASSNAME &om(const CLASSNAME_OM &om, const CLASSNAME &a) {
	CLASSNAME &result = CLASSNAME::getTemp();

	result.om(a, om);
	
	return result;
}
#endif // GAIM_PRODUCT_OM


