sandbindir = $(bindir)/ga_sandbox

sandbin_PROGRAMS = chap3ex4

AM_CPPFLAGS = -I../.. $(OPENGL_CFLAGS)

chap3ex4_LDADD = $(OPENGL_LIBS) $(GLUT_LIBS) ../../libgasandbox/libgasandbox.a

chap3ex4_SOURCES = chap3ex4.cpp

noinst_HEADERS = 

sandbin_DATA = image2.raw image3.raw
EXTRA_DIST = image2.raw image3.raw
