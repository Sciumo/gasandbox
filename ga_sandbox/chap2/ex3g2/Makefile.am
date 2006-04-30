bin_PROGRAMS = chap2ex3

#FLTK = TEMP!
AM_CPPFLAGS = -I../.. $(AQSIS_FLTK_CFLAGS)

#FLTK = TEMP! (2x)
chap2ex3_LDADD = $(GL_LIBS) $(AQSIS_FLTK_LIBS) -lfltk_gl ../../libgasandbox/libgasandbox.a

chap2ex3_SOURCES = hpindex.cpp  timing.cpp \
	fields.cpp  glwindow.cpp  main.cpp


noinst_HEADERS = fields.h  gaigenhl.h  glwindow.h  hpindex.h  main.h  timing.h

EXTRA_DIST = gaigenhl.cpp  
