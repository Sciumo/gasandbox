lib_LIBRARIES = libgasandbox.a

libgasandbox_a_includedir       = $(includedir)/libgasandbox
libgasandbox_a_include_HEADERS = \
	draw.h  e2ga_draw.h  e3ga.h       e3ga_util.h  mv_analyze.h \
	common.h     e2ga.h  e2ga_util.h  e3ga_draw.h  geosphere.h  mvtypebase.h


EXTRA_DIST = e2ga.gs2 e3ga.gs2 e2ga_lexer.g e2ga_parser.g e3ga_lexer.g e3ga_parser.g \
	c3ga_draw.cpp main.cpp e2ga_mv_lexer.cpp e3ga_mv_lexer.cpp e2ga_mv_parser.cpp \
	e3ga_mv_parser.cpp  c3ga_draw.h  glut_util.h gl_util.h



libgasandbox_a_SOURCES =  \
	draw.cpp       mv_analyze.cpp \
	e2ga.cpp       e3ga.cpp            e3ga_util.cpp \
	e2ga_draw.cpp  e3ga_draw.cpp       geosphere.cpp \
	glut_util.cpp gl_util.cpp


libgasandbox_a_CFLAGS = 
