dnl Process this file with autoconf to produce a configure script.
AC_INIT(src/numbertype/numbertype.c)
AM_INIT_AUTOMAKE(gephex-types,0.0.1)

dnl Checks for programs.
AC_PROG_CXX

AC_DISABLE_STATIC
AM_PROG_LIBTOOL

dnl Checks for libraries.
dnl Replace `main' with a function in -ldl:
dnl AC_CHECK_LIB(dl, main)
dnl Replace `main' with a function in -ltestframework:
dnl AC_CHECK_LIB(testframework, main)

dnl Checks for header files.
AC_CHECK_HEADER(windows.h,AC_DEFINE(WIN32),AC_DEFINE(LINUX))

dnl Checks for typedefs, structures, and compiler characteristics.
dnl AC_C_CONST

dnl Checks for library functions.

baseincludedir=[${includedir}/gephex]
AC_SUBST(baseincludedir)
includedir=[${includedir}/gephex/types]
AC_SUBST(includedir)
libdir=[${libdir}/gephex/types]
AC_SUBST(libdir)


AC_OUTPUT(
Makefile
src/Makefile
src/numbertype/Makefile
src/stringtype/Makefile
src/framebuffertype/Makefile
src/positiontype/Makefile
src/rgbtype/Makefile
src/miditype/Makefile
)
