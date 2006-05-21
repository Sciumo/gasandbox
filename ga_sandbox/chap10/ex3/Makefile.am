sandbindir = $(bindir)/ga_sandbox

sandbin_PROGRAMS = chap10ex3

AM_CPPFLAGS = -I../.. $(GL_CFLAGS)

chap10ex3_LDADD = $(GL_LIBS) \
	../../libgasandbox/libgasandbox.a ../../libgasandbox/libgasandboxparse.a \
	/usr/local/lib/libantlr.a

chap10ex3_SOURCES = chap10ex3.cpp extcalibrefine.cpp readcalibrationdata.cpp

noinst_HEADERS = extcalibrefine.h readcalibrationdata.h

sandbin_DATA = calibration_data.txt