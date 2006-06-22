sandbindir = $(bindir)/ga_sandbox

sandbin_PROGRAMS = chap12ex1

AM_CPPFLAGS = -I../.. $(GL_CFLAGS)

chap12ex1_LDADD = $(GL_LIBS) \
	../../libgasandbox/libgasandbox.a \
	../../libgasandbox/libgasandboxparse.a  \
	/usr/local/lib/libantlr.a

chap12ex1_SOURCES = chap12ex1.cpp readopticaldata.cpp reconstruct.cpp

noinst_HEADERS = opticaldata.h readopticaldata.h

sandbin_DATA = chap12data.txt
EXTRA_DIST = chap12data.txt
