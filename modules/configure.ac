dnl Process this file with autoconf to produce a configure script.
AC_INIT(src/addmodule/addmodule.spec)
AM_INIT_AUTOMAKE(gephex-modules,0.0.1)

AM_CONFIG_HEADER(config.h)

dnl Checks for programs.
AC_PROG_CXX

AC_DISABLE_STATIC
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


baseincludedir=[${includedir}/gephex]
AC_SUBST(baseincludedir)
includedir=[${includedir}/gephex]
AC_SUBST(includedir)
libdir=[${libdir}/gephex/modules]
AC_SUBST(libdir)

AC_OUTPUT(
Makefile
src/Makefile
src/libgrid/Makefile
src/libmidi/Makefile
src/tunnelmodule/Makefile
src/rotozoommodule/Makefile
src/blurmodule/Makefile
src/addmodule/Makefile
src/resultmodule/Makefile
src/numbermodule/Makefile
src/gloutmodule/Makefile
src/bmpmodule/Makefile
src/invertmodule/Makefile
src/sdloutputmodule/Makefile
src/xfademodule/Makefile
src/plasma/Makefile
src/cubesmodule/Makefile
src/bwmodule/Makefile
src/signalgenmodules/Makefile
src/starfield/Makefile
src/imgsubmodule/Makefile
src/imgaddmodule/Makefile
src/imgmulmodule/Makefile
src/staticcolormodule/Makefile
src/numposmodule/Makefile
src/posnummodule/Makefile
src/functions/Makefile
src/functions/jumpmodule/Makefile
src/functions/numxfadermodule/Makefile
src/colorcyclermodule/Makefile
src/flashmodule/Makefile
src/joystickmodule/Makefile
src/avifilemodule/Makefile
src/v4lmodule/Makefile
src/netcontrol/Makefile
src/midiinmodule/Makefile
src/doepfermodule/Makefile
)

#src/hsvmodule/Makefile
#src/splitmodule/Makefile
#src/combinemodule/Makefile
#src/interference/Makefile

