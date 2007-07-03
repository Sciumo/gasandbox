/* $ANTLR 2.7.7 (2006-11-01): "h3ga_parser.g" -> "h3ga_mv_parser.cpp"$ */

	#include <iostream>
		#include <utility>
		#include <string>
		#include <antlr/String.hpp>
		#include <stdlib.h>
		#include "h3ga.h"
		using namespace std;

#include "h3ga_mv_parser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
ANTLR_BEGIN_NAMESPACE(h3ga)


	void mv_parserProcessBasisElement(float coordinates[16], float c, unsigned int bitmap) {
		if (bitmap > 31) {
			mv_throw_exception("mv_parserProcessBasisElement(): parse error", MV_EXCEPTION_ERROR);
		}

		int idx = mv_basisElementIndexByBitmap[bitmap];
		coordinates[idx] = c / (float)mv_basisElementSignByIndex[idx];

		//	printf("BE %f, %d\n", scale, bitmap);

	}

	void mv_parserProcessBasisVector(const std::string &bv, float &scale, unsigned int &bitmap) {
		unsigned int i;
		//	printf("BasisVector: %s\n", bv.c_str());
		for (i = 0; i < 5; i++) {
			if (mv_basisVectorNames[i] == bv) {
				unsigned int b = 1 << i;
				if (bitmap & b) { // bv ^ bv = 0
					scale = 0;
					return;
				}

				// add basis vector to bitmap	
				bitmap |= b;

				i++;
				for (; i < 5; i++) // compute sign flips due to anti commuting basis vectors
				if (bitmap & (1 << i)) scale = -scale;


				//printf("Result: %f, %d\n", scale, bitmap);
				return;
			}
		}
		if (i == 5) {
			// this should never execute, for the basis vector should always be found in MV_basisVectorNames
			// this depends on exceptions or not
			mv_throw_exception(("mv_parserProcessBasisVector(): unknown basis element: " + bv).c_str(), MV_EXCEPTION_ERROR);
		}
	}



h3ga_mv_parser::h3ga_mv_parser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
}

h3ga_mv_parser::h3ga_mv_parser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,2)
{
}

h3ga_mv_parser::h3ga_mv_parser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
}

h3ga_mv_parser::h3ga_mv_parser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,2)
{
}

h3ga_mv_parser::h3ga_mv_parser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,2)
{
}

mv  h3ga_mv_parser::multivector() {
	mv result;
	
		float coordinates[16];
		mv_zero(coordinates, 16); 
		std::pair<float, unsigned int> be; 
		float sg; 
		float scale = (float)1.0;
	
	
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == MINUS || LA(1) == PLUS)) {
				sg=sign();
				scale *= sg;
			}
			else {
				goto _loop3;
			}
			
		}
		_loop3:;
		} // ( ... )*
		be=basis_element();
		mv_parserProcessBasisElement(coordinates, scale * be.first, be.second);
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == MINUS || LA(1) == PLUS)) {
				scale=sign();
				{ // ( ... )*
				for (;;) {
					if ((LA(1) == MINUS || LA(1) == PLUS)) {
						sg=sign();
						scale *= sg;
					}
					else {
						goto _loop6;
					}
					
				}
				_loop6:;
				} // ( ... )*
				be=basis_element();
				mv_parserProcessBasisElement(coordinates, scale * be.first, be.second);
			}
			else {
				goto _loop7;
			}
			
		}
		_loop7:;
		} // ( ... )*
		
			result = mv_compress(coordinates/*, 0.0, 31*/);
		
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_0);
	}
	return result;
}

float  h3ga_mv_parser::sign() {
	float sg;
	sg = (float)1.0;
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case PLUS:
		{
			match(PLUS);
			break;
		}
		case MINUS:
		{
			match(MINUS);
			sg = -sg;
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_1);
	}
	return sg;
}

std::pair<float, unsigned int>  h3ga_mv_parser::basis_element() {
	std::pair<float, unsigned int> r;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	r.first = 1.0; r.second = 0;
	
	try {      // for error handling
		switch ( LA(1)) {
		case NUMBER:
		{
			t1 = LT(1);
			match(NUMBER);
			r.first = mv_stringToNumber(t1->getText().c_str());
			{
			switch ( LA(1)) {
			case GP:
			case OP:
			case BASIS_VECTOR:
			{
				{
				switch ( LA(1)) {
				case GP:
				{
					match(GP);
					break;
				}
				case OP:
				{
					match(OP);
					break;
				}
				case BASIS_VECTOR:
				{
					break;
				}
				default:
				{
					throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
				}
				}
				}
				{
				t2 = LT(1);
				match(BASIS_VECTOR);
				mv_parserProcessBasisVector(t2->getText(), r.first, r.second);
				}
				{ // ( ... )*
				for (;;) {
					if ((LA(1) == OP)) {
						match(OP);
						t3 = LT(1);
						match(BASIS_VECTOR);
						mv_parserProcessBasisVector(t3->getText(), r.first, r.second);
					}
					else {
						goto _loop13;
					}
					
				}
				_loop13:;
				} // ( ... )*
				break;
			}
			case ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE:
			case MINUS:
			case PLUS:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			break;
		}
		case BASIS_VECTOR:
		{
			{
			{
			t5 = LT(1);
			match(BASIS_VECTOR);
			mv_parserProcessBasisVector(t5->getText(), r.first, r.second);
			}
			{ // ( ... )*
			for (;;) {
				if ((LA(1) == OP)) {
					match(OP);
					t6 = LT(1);
					match(BASIS_VECTOR);
					mv_parserProcessBasisVector(t6->getText(), r.first, r.second);
				}
				else {
					goto _loop17;
				}
				
			}
			_loop17:;
			} // ( ... )*
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_2);
	}
	return r;
}

void h3ga_mv_parser::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* h3ga_mv_parser::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"WS_",
	"MINUS",
	"PLUS",
	"GP",
	"OP",
	"a basis vector",
	"INT",
	"a scalar",
	0
};

const unsigned long h3ga_mv_parser::_tokenSet_0_data_[] = { 2UL, 0UL, 0UL, 0UL };
// EOF 
const ANTLR_USE_NAMESPACE(antlr)BitSet h3ga_mv_parser::_tokenSet_0(_tokenSet_0_data_,4);
const unsigned long h3ga_mv_parser::_tokenSet_1_data_[] = { 2656UL, 0UL, 0UL, 0UL };
// MINUS PLUS BASIS_VECTOR NUMBER 
const ANTLR_USE_NAMESPACE(antlr)BitSet h3ga_mv_parser::_tokenSet_1(_tokenSet_1_data_,4);
const unsigned long h3ga_mv_parser::_tokenSet_2_data_[] = { 98UL, 0UL, 0UL, 0UL };
// EOF MINUS PLUS 
const ANTLR_USE_NAMESPACE(antlr)BitSet h3ga_mv_parser::_tokenSet_2(_tokenSet_2_data_,4);


ANTLR_END_NAMESPACE
