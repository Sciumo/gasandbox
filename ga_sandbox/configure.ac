dnl Process this file with autoconf to produce a configure script.
AC_INIT()
AM_INIT_AUTOMAKE(ga_sandbox, 1.0.7)
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
#MDL_HAVE_OPENGL
#AX_CHECK_GLUT
#GNASH_PATH_OPENGL
GLUT_LIBS="-lglut"
AC_SUBST(GLUT_LIBS)
AQSIS_CHECK_FLTK
AC_CHECK_FILE(/usr/local/lib/libantlr.a, ANTLR_LIBS="/usr/local/lib/libantlr.a", AC_CHECK_FILE(/usr/lib/libantlr.a, ANTLR_LIBS="/usr/lib/libantlr.a", AC_CHECK_FILE(/opt/local/lib/libantlr.a, ANTLR_LIBS="/opt/local/lib/libantlr.a", -lantlr)))
AC_SUBST(ANTLR_LIBS)

AC_OUTPUT(
	Makefile \
	vs.net/Makefile \
	vs2005/Makefile \
	vs2008/Makefile \
	\
	qhull-2003.1/Makefile \
	qhull-2003.1/src/Makefile \
	qhull-2003.1/html/Makefile \
	qhull-2003.1/eg/Makefile \
	qhull-2003.1/vs.net/Makefile \
	\
	libgasandbox/Makefile \
	\
	libgasandbox_no_opt/Makefile \
	\
	chap1/Makefile \
	chap1/ex1/Makefile\
	\
	chap2/Makefile \
	chap2/ex1/Makefile\
	chap2/ex2/Makefile\
	chap2/ex3/Makefile\
	\
	chap3/Makefile \
	chap3/ex1/Makefile\
	chap3/ex2/Makefile\
	chap3/ex3/Makefile\
	chap3/ex4/Makefile\
	\
	chap4/Makefile \
	chap4/ex1/Makefile \
	chap4/ex2/Makefile \
	chap4/ex3/Makefile \
	\
	chap5/Makefile \
	chap5/ex1/Makefile \
	chap5/ex2/Makefile \
	chap5/ex3/Makefile \
	\
	chap6/Makefile \
	chap6/ex1/Makefile \
	chap6/ex2/Makefile \
	\
	chap7/Makefile \
	chap7/ex1/Makefile \
	chap7/ex2/Makefile \
	chap7/ex3/Makefile \
	chap7/ex4/Makefile \
	chap7/ex5/Makefile \
	\
	chap8/Makefile \
	\
	chap10/Makefile \
	chap10/ex1/Makefile \
	chap10/ex2/Makefile \
	chap10/ex3/Makefile \
	\
	chap11/Makefile \
	chap11/ex1/Makefile \
	chap11/ex2/Makefile \
	chap11/ex3/Makefile \
	chap11/ex4/Makefile \
	\
	chap12/Makefile \
	chap12/ex1/Makefile \
	chap12/ex2/Makefile \
	chap12/ex3/Makefile \
	\
	chap13/Makefile \
	chap13/ex1/Makefile \
	chap13/ex2/Makefile \
	chap13/ex3/Makefile \
	chap13/ex4/Makefile \
	\
	chap14/Makefile \
	chap14/ex1/Makefile \
	chap14/ex2/Makefile \
	chap14/ex3/Makefile \
	chap14/ex4/Makefile \
	\
	chap15/Makefile \
	chap15/ex1/Makefile \
	chap15/ex2/Makefile \
	chap15/ex3/Makefile \
	\
	chap16/Makefile \
	chap16/ex1/Makefile \
	chap16/ex2/Makefile \
	chap16/ex3/Makefile \
	chap16/ex4/Makefile \
	\
	solutions/Makefile \
	\
	solutions/chap2/Makefile \
	solutions/chap2/ex2/Makefile \
	\
	solutions/chap3/Makefile \
	solutions/chap3/ex2/Makefile \
	\
	solutions/chap6/Makefile \
	solutions/chap6/ex1/Makefile \
	\
	solutions/chap7/Makefile \
	solutions/chap7/ex4/Makefile \
	solutions/chap7/ex5/Makefile \
	\
	solutions/chap11/Makefile \
	solutions/chap11/ex4/Makefile \
	\
	solutions/chap13/Makefile \
	solutions/chap13/ex2/Makefile \
	\
	solutions/chap14/Makefile \
	solutions/chap14/ex2/Makefile \
	\
	solutions/vs.net/Makefile \
	solutions/vs2005/Makefile \
	solutions/vs2008/Makefile \
	\
	attic/Makefile\
	attic/gaigen2hp/Makefile \
	\
	screenshots/Makefile \
	\
	ext_include/Makefile \
	lib_win32/Makefile \
	\
	xcode/Makefile \
	xcode/GA_Sandbox.xcodeproj/Makefile \
	)
