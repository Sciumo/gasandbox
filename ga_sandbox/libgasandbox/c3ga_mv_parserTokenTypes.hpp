#ifndef INC_c3ga_mv_parserTokenTypes_hpp_
#define INC_c3ga_mv_parserTokenTypes_hpp_

ANTLR_BEGIN_NAMESPACE(c3ga)
/* $ANTLR 2.7.7 (2006-11-01): "c3ga_parser.g" -> "c3ga_mv_parserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API c3ga_mv_parserTokenTypes {
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
#endif /*INC_c3ga_mv_parserTokenTypes_hpp_*/
