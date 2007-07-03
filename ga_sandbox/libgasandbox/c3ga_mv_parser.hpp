#ifndef INC_c3ga_mv_parser_hpp_
#define INC_c3ga_mv_parser_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (2006-11-01): "c3ga_parser.g" -> "c3ga_mv_parser.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "c3ga_mv_parserTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

ANTLR_BEGIN_NAMESPACE(c3ga)
class CUSTOM_API c3ga_mv_parser : public ANTLR_USE_NAMESPACE(antlr)LLkParser, public c3ga_mv_parserTokenTypes
{
public:
	void initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory );
protected:
	c3ga_mv_parser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k);
public:
	c3ga_mv_parser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf);
protected:
	c3ga_mv_parser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k);
public:
	c3ga_mv_parser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer);
	c3ga_mv_parser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state);
	int getNumTokens() const
	{
		return c3ga_mv_parser::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return c3ga_mv_parser::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return c3ga_mv_parser::tokenNames;
	}
	public: mv  multivector();
	public: float  sign();
	public: std::pair<float, unsigned int>  basis_element();
public:
	ANTLR_USE_NAMESPACE(antlr)RefAST getAST()
	{
		return returnAST;
	}
	
protected:
	ANTLR_USE_NAMESPACE(antlr)RefAST returnAST;
private:
	static const char* tokenNames[];
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 12;
#else
	enum {
		NUM_TOKENS = 12
	};
#endif
	
	static const unsigned long _tokenSet_0_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_2;
};

ANTLR_END_NAMESPACE
#endif /*INC_c3ga_mv_parser_hpp_*/
