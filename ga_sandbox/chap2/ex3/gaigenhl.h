#include <stdlib.h>

/*
#if GAIM_DIM == 2
#include "dim2.h"
#elif GAIM_DIM == 3
#include "dim3.h"
#endif
*/


#define MV_MAX_TEMP 64

// temp enable drawing by hand..., should depend on something else (todo)
//#define GAIM_DRAWING

//#define CLASSNAME_OM GAIM_OM_CLASSNAME

class CLASSNAME;
#ifdef GAIM_PRODUCT_OM
class CLASSNAME_OM;
#endif // GAIM_PRODUCT_OM

#ifdef GAIM_PRODUCT_GP
CLASSNAME &gp(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &gp(GAIM_FLOAT a, const CLASSNAME &b);
inline CLASSNAME &gp(const CLASSNAME &a, GAIM_FLOAT b) {return gp(b, a);}
inline CLASSNAME &operator*(GAIM_FLOAT a, const CLASSNAME &b) {return gp(a, b);}
#endif // GAIM_PRODUCT_GP

#ifdef GAIM_PRODUCT_IGP
CLASSNAME &igp(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &igp(const CLASSNAME &a, GAIM_FLOAT b);
CLASSNAME &igp(GAIM_FLOAT a, const CLASSNAME &b);
CLASSNAME &operator/(GAIM_FLOAT a, const CLASSNAME &b);
#endif // GAIM_PRODUCT_IGP

#ifdef GAIM_PRODUCT_OP
CLASSNAME &op(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &op(GAIM_FLOAT a, const CLASSNAME &b);
inline CLASSNAME &op(const CLASSNAME &a, GAIM_FLOAT b) {return op(b, a);}
inline CLASSNAME &operator^(GAIM_FLOAT a, const CLASSNAME &b) {return op(a, b);}
#endif // GAIM_PRODUCT_OP

#ifdef GAIM_PRODUCT_LCONT
CLASSNAME &lcont(const CLASSNAME &a, const CLASSNAME &b);
#endif // GAIM_PRODUCT_LCONT
	
#ifdef GAIM_PRODUCT_RCONT
CLASSNAME &rcont(const CLASSNAME &a, const CLASSNAME &b);
#endif // GAIM_PRODUCT_RCONT

#ifdef GAIM_PRODUCT_SCP
CLASSNAME &scp(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &scp(GAIM_FLOAT b, const CLASSNAME &a);
inline CLASSNAME &scp(const CLASSNAME &a, GAIM_FLOAT b)  {return scp(b, a);}
inline CLASSNAME &operator%(GAIM_FLOAT a, const CLASSNAME &b) {return scp(b, a);}
#endif // GAIM_PRODUCT_SCP

#ifdef GAIM_PRODUCT_HIP
CLASSNAME &hip(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &hip(GAIM_FLOAT b, const CLASSNAME &a);
CLASSNAME &hip(const CLASSNAME &a, GAIM_FLOAT b);
#endif // GAIM_PRODUCT_HIP

#ifdef GAIM_PRODUCT_MHIP
CLASSNAME &mhip(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &mhip(GAIM_FLOAT b, const CLASSNAME &a);
CLASSNAME &mhip(const CLASSNAME &a, GAIM_FLOAT b);
#endif // GAIM_PRODUCT_MHIP

#ifdef GAIM_FUNCTION_MEETJOIN
CLASSNAME &meet(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &join(const CLASSNAME &a, const CLASSNAME &b);
#endif // GAIM_FUNCTION_MEETJOIN


#ifdef GAIM_FUNCTION_ADD
CLASSNAME &add(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &add(GAIM_FLOAT a, const CLASSNAME &b);
inline CLASSNAME &add(const CLASSNAME &a, GAIM_FLOAT b) {return add(b, a);}
inline CLASSNAME &operator+(GAIM_FLOAT a, const CLASSNAME &b) {return add(a, b);}
#endif // GAIM_FUNCTION_ADD

#ifdef GAIM_FUNCTION_SUBSTRACT
CLASSNAME &sub(const CLASSNAME &a, const CLASSNAME &b);
CLASSNAME &sub(GAIM_FLOAT a, const CLASSNAME &b);
inline CLASSNAME &sub(const CLASSNAME &a, GAIM_FLOAT b) {return add(-b, a);}
inline CLASSNAME &operator-(GAIM_FLOAT a, const CLASSNAME &b) {return sub(a, b);}
#endif // GAIM_FUNCTION_SUBSTRACT


#ifdef GAIM_FUNCTION_NEGATE
CLASSNAME &negate(const CLASSNAME &a);
#endif //GAIM_FUNCTION_NEGATE


class CLASSNAME : public GAIM_CLASSNAME {
public:
	CLASSNAME();
	CLASSNAME(GAIM_CLASSNAME &a);
	CLASSNAME(GAIM_FLOAT scalar) : GAIM_CLASSNAME (GRADE0, scalar) {};
	CLASSNAME(int gradeUsage, const GAIM_FLOAT *coordinates) : GAIM_CLASSNAME (gradeUsage, coordinates) {};
	
#ifdef GAIM_CONSTRUCTOR_1_COOR
	CLASSNAME(int gradeUsage, GAIM_FLOAT c0) : GAIM_CLASSNAME (gradeUsage, c0) {};
#endif 
#ifdef GAIM_CONSTRUCTOR_2_COOR
	CLASSNAME(int gradeUsage, GAIM_FLOAT c0, GAIM_FLOAT c1) : GAIM_CLASSNAME (gradeUsage, c0, c1) {};
#endif 
#ifdef GAIM_CONSTRUCTOR_3_COOR
	CLASSNAME(int gradeUsage, GAIM_FLOAT c0, GAIM_FLOAT c1, GAIM_FLOAT c2) : GAIM_CLASSNAME (gradeUsage, c0, c1, c2) {};
#endif 
#ifdef GAIM_CONSTRUCTOR_4_COOR
	CLASSNAME(int gradeUsage, GAIM_FLOAT c0, GAIM_FLOAT c1, GAIM_FLOAT c2, GAIM_FLOAT c3) : GAIM_CLASSNAME (gradeUsage, c0, c1, c2, c3) {};
#endif 
#ifdef GAIM_CONSTRUCTOR_5_COOR
	CLASSNAME(int gradeUsage, GAIM_FLOAT c0, GAIM_FLOAT c1, GAIM_FLOAT c2, GAIM_FLOAT c3, GAIM_FLOAT c4) : GAIM_CLASSNAME (gradeUsage, c0, c1, c2, c3, c4) {};
#endif 
#ifdef GAIM_CONSTRUCTOR_6_COOR
	CLASSNAME(int gradeUsage, GAIM_FLOAT c0, GAIM_FLOAT c1, GAIM_FLOAT c2, GAIM_FLOAT c3, GAIM_FLOAT c4, GAIM_FLOAT c5) : GAIM_CLASSNAME (gradeUsage, c0, c1, c2, c3, c4, c5) {};
#endif 
#ifdef GAIM_CONSTRUCTOR_7_COOR
	CLASSNAME(int gradeUsage, GAIM_FLOAT c0, GAIM_FLOAT c1, GAIM_FLOAT c2, GAIM_FLOAT c3, GAIM_FLOAT c4, GAIM_FLOAT c5, GAIM_FLOAT c6) : GAIM_CLASSNAME (gradeUsage, c0, c1, c2, c3, c4, c5, c6) {};
#endif 
#ifdef GAIM_CONSTRUCTOR_8_COOR
	CLASSNAME(int gradeUsage, GAIM_FLOAT c0, GAIM_FLOAT c1, GAIM_FLOAT c2, GAIM_FLOAT c3, GAIM_FLOAT c4, GAIM_FLOAT c5, GAIM_FLOAT c6, GAIM_FLOAT c7) : GAIM_CLASSNAME (gradeUsage, c0, c1, c2, c3, c4, c5, c6, c7) {};
#endif 

	CLASSNAME(const CLASSNAME &a) : GAIM_CLASSNAME (a) {};
	~CLASSNAME();

	CLASSNAME &operator=(const CLASSNAME &a);
	CLASSNAME &operator=(GAIM_FLOAT f);

	// take grade
#ifdef GAIM_FUNCTION_TAKEGRADE
	CLASSNAME &grade(int g) const;
	inline CLASSNAME &operator()(int g) const {return grade(g);}
#endif // GAIM_FUNCTION_TAKEGRADE

	inline const GAIM_FLOAT *operator[](int g) const {return coordinates(g);}

#ifdef GAIM_FUNCTION_REVERSE
	CLASSNAME &operator++() const;
	inline CLASSNAME &operator++(int) const {return operator++();};
	inline CLASSNAME &reverse() const {return operator++();};
#endif // GAIM_FUNCTION_REVERSE

#ifdef GAIM_FUNCTION_CLIFFORDCONJUGATE
	CLASSNAME &operator--() const;
	inline CLASSNAME &operator--(int) const {return operator--();};
	inline CLASSNAME &cliffordConjugate() const {return operator--();};
#endif // GAIM_FUNCTION_CLIFFORDCONJUGATE

#ifdef GAIM_FUNCTION_GRADEINVOLUTION
	CLASSNAME &operator~() const;
	inline CLASSNAME &gradeInvolution() const {return operator~();};
#endif // GAIM_FUNCTION_GRADEINVOLUTION

#ifdef GAIM_FUNCTION_NORMALIZE
	CLASSNAME &normal() const;
#endif // GAIM_FUNCTION_NORMALIZE

	// inverse
#ifdef GAIM_FUNCTION_VERSORINVERSE
	inline void inverse(const CLASSNAME &a) {versorInverse(a);};
#elif defined(GAIM_FUNCTION_LOUNESTOINVERSE)
	inline void inverse(const CLASSNAME &a) {lounestoInverse(a);};
#elif defined(GAIM_FUNCTION_GENERALINVERSE)
	inline void inverse(const CLASSNAME &a) {generalInverse(a);};
#endif

#ifdef GAIM_FUNCTION_VERSORINVERSE
	inline void versorInverse(const CLASSNAME &a) {GAIM_CLASSNAME::versorInverse(a);};
	CLASSNAME &versorInverse() const;
#endif
#ifdef GAIM_FUNCTION_LOUNESTOINVERSE
	inline void lounestoInverse(const CLASSNAME &a) {GAIM_CLASSNAME::lounestoInverse(a);};
	CLASSNAME &lounestoInverse() const;
#endif
#ifdef GAIM_FUNCTION_GENERALINVERSE
	inline void generalInverse(const CLASSNAME &a) {GAIM_CLASSNAME::generalInverse(a);};
	CLASSNAME &generalInverse() const;
#endif

	// geometric product
#ifdef GAIM_PRODUCT_GP
	CLASSNAME &operator*=(const CLASSNAME &a);
	CLASSNAME &operator*=(GAIM_FLOAT a);
	inline CLASSNAME &operator*(const CLASSNAME &a) const {return ::gp(*this, a);}
	inline CLASSNAME &operator*(GAIM_FLOAT a) const {return ::gp(*this, a);}
	CLASSNAME &dual() const;
#endif // GAIM_PRODUCT_GP

	// inverse geometric product
#ifdef GAIM_PRODUCT_IGP
	CLASSNAME &inverse() const;
	inline CLASSNAME &operator!() const {return inverse();}

	inline CLASSNAME &operator/(const CLASSNAME &a) const {return ::igp(*this, a);}
	inline CLASSNAME &operator/(GAIM_FLOAT a) const {return ::igp(*this, a);}
	CLASSNAME &operator/=(const CLASSNAME &a);
	CLASSNAME &operator/=(GAIM_FLOAT a);
#endif // GAIM_PRODUCT_IGP

	// scalar product
#ifdef GAIM_PRODUCT_SCP
	inline CLASSNAME &operator%(const CLASSNAME &a) const {return ::scp(*this, a);};
	inline CLASSNAME &operator%(GAIM_FLOAT a) const {return ::scp(a, *this);};
	CLASSNAME &operator%=(const CLASSNAME &a);
	CLASSNAME &operator%=(GAIM_FLOAT a);
#endif // GAIM_PRODUCT_SCP

	// left contraction
#ifdef GAIM_PRODUCT_LCONT
	inline CLASSNAME &operator<<(const CLASSNAME &a) const {return ::lcont(*this, a);}
	CLASSNAME &operator<<=(const CLASSNAME &a);
#endif // GAIM_PRODUCT_LCONT
	
	// right contraction
#ifdef GAIM_PRODUCT_RCONT
	inline CLASSNAME &operator>>(const CLASSNAME &a) const {return ::rcont(*this, a);}
	CLASSNAME &operator>>=(const CLASSNAME &a);
#endif // GAIM_PRODUCT_RCONT

	// outer product
#ifdef GAIM_PRODUCT_OP
	inline CLASSNAME &operator^(const CLASSNAME &a) const {return ::op(*this, a);}
	inline CLASSNAME &operator^(GAIM_FLOAT a) const {return ::op(a, *this);}
	CLASSNAME &operator^=(const CLASSNAME &a);
	CLASSNAME &operator^=(GAIM_FLOAT a);
#endif // GAIM_PRODUCT_OP

#ifdef GAIM_FUNCTION_MEETJOIN
	inline CLASSNAME &operator&(const CLASSNAME &a) {return ::meet(*this, a);}
	inline CLASSNAME &operator|(const CLASSNAME &a) {return ::join(*this, a);}
#endif // GAIM_FUNCTION_MEETJOIN

#ifdef GAIM_FUNCTION_ADD
	inline CLASSNAME &operator+(const CLASSNAME &a) const {return ::add(*this, a);}
	inline CLASSNAME &operator+(GAIM_FLOAT a) const {return ::add(a, *this);}
	CLASSNAME &operator+=(const CLASSNAME &a);
	CLASSNAME &operator+=(GAIM_FLOAT a);
#endif // GAIM_FUNCTION_ADD

#ifdef GAIM_FUNCTION_SUBSTRACT
	inline CLASSNAME &operator-(const CLASSNAME &a) const {return ::sub(*this, a);}
	inline CLASSNAME &operator-(GAIM_FLOAT a) const {return ::add(-a, *this);}
	CLASSNAME &operator-=(const CLASSNAME &a);
	CLASSNAME &operator-=(GAIM_FLOAT a);
#endif // GAIM_FUNCTION_SUBSTRACT

#ifdef GAIM_FUNCTION_NEGATE
	inline CLASSNAME &operator-() const {return ::negate(*this);}
#endif //GAIM_FUNCTION_NEGATE


	static CLASSNAME &getTemp();	// returns a temporary variable; don't use expressions which require more than MV_MAX_TEMP temporaries

#ifdef GAIM_DRAWING
	/* ********************** drawing ************************/
/* ****************** under construction ************************/

	/*
	sets the color of objects
	*/
	static int setColor(int grade, int idx, float r, float g, float b, float a = 1.0f);
	static int setColor(int grade, int idx, float *rgba);
	static int setColor(int grade, int idx, const char *name, float alpha = 1.0f);

	/*
	Sets the frame used for drawing OpenGL images.
	Specifies to what vectors the x, y and z axis in OpenGL correspond.
	Returns 0 on success, -1 on failure (i.e. when x^y^z is too small)
	*/
	static unsigned int m_Draw3DMode;
	static int setDraw3DMode(unsigned int mode);
	static int setDraw3DFrame(CLASSNAME &x, CLASSNAME &y, CLASSNAME &z);
	void draw3DProject(float *p);
	void draw3DBlade();

protected:
	static CLASSNAME m_Draw3DFrame[3], m_Draw3DTriVector, m_Draw3DTriVectorInverse;
	void draw3DVector();
	void draw3DBiVector();
	void draw3DTriVector();
	void drawBandedDisc(int halfSphere = 0, int colorSkip = 0, int ori = 1); 
	static int m_drawLightOn;
	static void drawEnableLighting();
	static void drawDisableLighting();
	static int m_drawCullFaceOn;
	static void drawEnableCullFace();
	static void drawDisableCullFace();

	static float m_color[4][2][4];
	void setColor(int grade, int idx); 	// automatically sets material properties as well



public:
/* ****************** under construction ************************/
	/* ********************** drawing ************************/
#endif //GAIM_DRAWING


	// implicit 'cast to GAIM_FLOATing point' operator
//	operator GAIM_FLOAT () const {return scalar();}

};

#ifdef GAIM_PRODUCT_OM
class CLASSNAME_OM : public GAIM_OM_CLASSNAME {
public:
	CLASSNAME_OM() : GAIM_OM_CLASSNAME() {};
	~CLASSNAME_OM() {};

	CLASSNAME_OM(const CLASSNAME vectorImages[3]) : GAIM_OM_CLASSNAME(vectorImages) {};
	CLASSNAME_OM(const CLASSNAME *vectorImages[3]);
//	CLASSNAME_OM(const CLASSNAME &Spinor) : GAIM_OM_CLASSNAME(Spinor) {};

	inline int initOuterMorphism(const CLASSNAME vectorImages[3]) {
		return GAIM_OM_CLASSNAME::initOuterMorphism(vectorImages);
	}
	inline int initOuterMorphism(const CLASSNAME *vectorImages[3]) {
		return GAIM_OM_CLASSNAME::initOuterMorphism((const GAIM_CLASSNAME**)vectorImages);
	}
	inline int initSpinor2(const CLASSNAME &Sp) {
		return GAIM_OM_CLASSNAME::initSpinor2(Sp);
	}
};

CLASSNAME &om(const CLASSNAME_OM &L, const CLASSNAME &A);
inline CLASSNAME &operator*(const CLASSNAME_OM &L, const CLASSNAME &A) {return om(L, A);}
#endif // GAIM_PRODUCT_GP

#ifdef GAIM_PRODUCT_IGP
inline CLASSNAME &igp(const CLASSNAME &a, const CLASSNAME &b) {return gp(a, b.inverse());}
inline CLASSNAME &igp(const CLASSNAME &a, GAIM_FLOAT b) {return op((GAIM_FLOAT)1.0 / b, a);}
inline CLASSNAME &igp(GAIM_FLOAT a, const CLASSNAME &b) {return op(a, b.inverse());}
inline CLASSNAME &operator/(GAIM_FLOAT a, const CLASSNAME &b) {return igp(a, b);}
#endif // GAIM_PRODUCT_IGP

/*
#ifdef GAIM_PRODUCT_OM
CLASSNAME &operator*(const GAIM_OM_CLASSNAME &om, const CLASSNAME &a);
inline CLASSNAME &om(const GAIM_OM_CLASSNAME &om, const CLASSNAME &a) {return om * a;}
#endif  // GAIM_PRODUCT_OM
*/

