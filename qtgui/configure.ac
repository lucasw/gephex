dnl Process this file with autoconf to produce a configure script.
AC_INIT(src/gui/main.cpp)
AM_INIT_AUTOMAKE(gephex-qtgui,0.0.1)

AM_CONFIG_HEADER(config.h)

dnl Checks for programs.
AC_PROG_CXX

AM_PROG_LIBTOOL  

dnl Checks for libraries.
dnl Replace `main' with a function in -ldl:
dnl AC_CHECK_LIB(dl, main)
dnl Replace `main' with a function in -ltestframework:
dnl AC_CHECK_LIB(testframework, main)


dnl autoheader kram:
AH_TOP([#ifndef INCLUDED_CONFIG_H
#define INCLUDED_CONFIG_H])

AH_BOTTOM([#endif])


dnl Checks for header files.
AC_CHECK_HEADER(windows.h,AC_DEFINE(OS_WIN32,1,[Operating System is Windows]),
			  AC_DEFINE(OS_POSIX,1,[Any Posix Operating System]))

dnl Checks for typedefs, structures, and compiler characteristics.
dnl AC_C_CONST

dnl Checks for library functions.


AC_OUTPUT(
Makefile
src/Makefile
src/guimodel/Makefile
src/gui/Makefile
src/gui/controlwidgets/Makefile
src/gui/propertywidgets/Makefile
)
