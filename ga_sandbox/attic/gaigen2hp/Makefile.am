bin_PROGRAMS = gaigen2hp

AM_CPPFLAGS = -I../.. $(AQSIS_FLTK_CFLAGS)

gaigen2hp_LDADD = $(GL_LIBS) $(AQSIS_FLTK_LIBS) ../../libgasandbox/libgasandbox.a

gaigen2hp_SOURCES = hpindex.cpp  \
	fields.cpp  glwindow.cpp  main.cpp

noinst_HEADERS = fields.h  glwindow.h  hpindex.h  main.h

