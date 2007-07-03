#ifndef INC_e3ga_mv_lexer_hpp_
#define INC_e3ga_mv_lexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (2006-11-01): "e3ga_lexer.g" -> "e3ga_mv_lexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "e3ga_mv_lexerTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
ANTLR_BEGIN_NAMESPACE(e3ga)
class CUSTOM_API e3ga_mv_lexer : public ANTLR_USE_NAMESPACE(antlr)CharScanner, public e3ga_mv_lexerTokenTypes
{
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	e3ga_mv_lexer(ANTLR_USE_NAMESPACE(std)istream& in);
	e3ga_mv_lexer(ANTLR_USE_NAMESPACE(antlr)InputBuffer& ib);
	e3ga_mv_lexer(const ANTLR_USE_NAMESPACE(antlr)LexerSharedInputState& state);
	ANTLR_USE_NAMESPACE(antlr)RefToken nextToken();
	public: void mWS_(bool _createToken);
	public: void mMINUS(bool _createToken);
	public: void mPLUS(bool _createToken);
	public: void mGP(bool _createToken);
	public: void mOP(bool _createToken);
	public: void mBASIS_VECTOR(bool _createToken);
	protected: void mINT(bool _createToken);
	public: void mNUMBER(bool _createToken);
private:
	
};

ANTLR_END_NAMESPACE
#endif /*INC_e3ga_mv_lexer_hpp_*/
