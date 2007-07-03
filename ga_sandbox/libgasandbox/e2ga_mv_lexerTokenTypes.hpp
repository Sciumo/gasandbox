#ifndef INC_e2ga_mv_lexerTokenTypes_hpp_
#define INC_e2ga_mv_lexerTokenTypes_hpp_

ANTLR_BEGIN_NAMESPACE(e2ga)
/* $ANTLR 2.7.7 (2006-11-01): "e2ga_lexer.g" -> "e2ga_mv_lexerTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API e2ga_mv_lexerTokenTypes {
#endif
	enum {
		EOF_ = 1,
		WS_ = 4,
		MINUS = 5,
		PLUS = 6,
		GP = 7,
		OP = 8,
		BASIS_VECTOR = 9,
		INT = 10,
		NUMBER = 11,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
ANTLR_END_NAMESPACE
#endif /*INC_e2ga_mv_lexerTokenTypes_hpp_*/
