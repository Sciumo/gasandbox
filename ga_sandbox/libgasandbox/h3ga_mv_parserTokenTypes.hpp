#ifndef INC_h3ga_mv_parserTokenTypes_hpp_
#define INC_h3ga_mv_parserTokenTypes_hpp_

ANTLR_BEGIN_NAMESPACE(h3ga)
/* $ANTLR 2.7.7 (2006-11-01): "h3ga_parser.g" -> "h3ga_mv_parserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API h3ga_mv_parserTokenTypes {
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
#endif /*INC_h3ga_mv_parserTokenTypes_hpp_*/
