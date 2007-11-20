lib_LIBRARIES = libgasandbox.a libgasandboxparse.a

libgasandbox_a_CPPFLAGS = $(OPENGL_CFLAGS) 


#-I/opt/local/include


libgasandbox_a_includedir       = $(includedir)/libgasandbox
libgasandbox_a_include_HEADERS = \
	draw.h \
	e2ga.h e2ga_draw.h e2ga_util.h \
	e3ga.h e3ga_util.h e3ga_draw.h \
	h3ga.h h3ga_util.h h3ga_draw.h \
	c2ga.h c2ga_util.h c2ga_draw.h \
	c3ga.h c3ga_util.h c3ga_draw.h \
	mv_analyze.h common.h     geosphere.h  mvtypebase.h \
	timing.h glut_util.h gl_util.h gabits.h c2gatoc3ga.h

libgasandbox_a_SOURCES =  \
	draw.cpp \
	mv_analyze.cpp mv_analyze_e2ga.cpp mv_analyze_e3ga.cpp mv_analyze_h3ga.cpp mv_analyze_c2ga.cpp mv_analyze_c3ga.cpp \
	e2ga.cpp e2ga_draw.cpp \
	e3ga.cpp e3ga_util.cpp e3ga_draw.cpp \
	h3ga.cpp h3ga_util.cpp h3ga_draw.cpp \
	c2ga.cpp c2ga_util.cpp c2ga_draw.cpp \
	c3ga.cpp c3ga_util.cpp c3ga_draw.cpp \
	geosphere.cpp timing.cpp \
	glut_util.cpp gl_util.cpp c2gatoc3ga.cpp




libgasandboxparse_a_includedir       = $(includedir)/libgasandbox
libgasandboxparse_a_include_HEADERS = \
	e2ga_parse.h e2ga_mv_lexer.hpp e2ga_mv_lexerTokenTypes.hpp e2ga_mv_parser.hpp e2ga_mv_parserTokenTypes.hpp \
	e3ga_parse.h e3ga_mv_lexer.hpp e3ga_mv_lexerTokenTypes.hpp e3ga_mv_parser.hpp e3ga_mv_parserTokenTypes.hpp \
	h3ga_parse.h h3ga_mv_lexer.hpp h3ga_mv_lexerTokenTypes.hpp h3ga_mv_parser.hpp h3ga_mv_parserTokenTypes.hpp \
	c2ga_parse.h c2ga_mv_lexer.hpp c2ga_mv_lexerTokenTypes.hpp c2ga_mv_parser.hpp c2ga_mv_parserTokenTypes.hpp \
	c3ga_parse.h c3ga_mv_lexer.hpp c3ga_mv_lexerTokenTypes.hpp c3ga_mv_parser.hpp c3ga_mv_parserTokenTypes.hpp 

libgasandboxparse_a_SOURCES =  \
	e2ga_parse.cpp e2ga_mv_lexer.cpp e2ga_mv_parser.cpp \
	e3ga_parse.cpp e3ga_mv_lexer.cpp e3ga_mv_parser.cpp \
	h3ga_parse.cpp h3ga_mv_lexer.cpp h3ga_mv_parser.cpp \
	c2ga_parse.cpp c2ga_mv_lexer.cpp c2ga_mv_parser.cpp \
	c3ga_parse.cpp c3ga_mv_lexer.cpp c3ga_mv_parser.cpp 



EXTRA_DIST = \
	e2ga.gs2 e3ga.gs2 h3ga.gs2 c2ga.gs2 c3ga.gs2 \
	e2ga.gp2 e3ga.gp2 h3ga.gp2 c2ga.gp2 c3ga.gp2 \
	e2ga_lexer.g e2ga_parser.g \
	e3ga_lexer.g e3ga_parser.g \
	h3ga_lexer.g h3ga_parser.g \
	c2ga_lexer.g c2ga_parser.g \
	c3ga_lexer.g c3ga_parser.g \
	e2ga_mv_lexerTokenTypes.txt \
	e2ga_mv_parserTokenTypes.txt \
	e3ga_mv_lexerTokenTypes.txt \
	e3ga_mv_parserTokenTypes.txt \
	h3ga_mv_lexerTokenTypes.txt \
	h3ga_mv_parserTokenTypes.txt \
	c2ga_mv_lexerTokenTypes.txt \
	c2ga_mv_parserTokenTypes.txt \
	c3ga_mv_lexerTokenTypes.txt \
	c3ga_mv_parserTokenTypes.txt
