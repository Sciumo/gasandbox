sandbindir = $(bindir)/ga_sandbox

sandbin_PROGRAMS = chap12ex3

AM_CPPFLAGS = -I../.. $(GL_CFLAGS)

chap12ex3_LDADD = $(GL_LIBS) \
	../../libgasandbox/libgasandbox.a \
	../../libgasandbox/libgasandboxparse.a  \
	/usr/local/lib/libantlr.a

chap12ex3_SOURCES = chap12ex3.cpp readopticaldata.cpp reconstruct.cpp

noinst_HEADERS = opticaldata.h readopticaldata.h

sandbin_DATA = silly_moves.txt
EXTRA_DIST = silly_moves.txt
