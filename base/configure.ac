# Process this file with autoconf to produce a configure script.
AC_INIT(src/utils/autoptr.h)
AM_INIT_AUTOMAKE(gephex-base,0.0.1)

AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CXX

AM_PROG_LIBTOOL  


# Checks for libraries.
# Replace `main' with a function in -ldl:
# AC_CHECK_LIB(dl, main)
# Replace `main' with a function in -ltestframework:
# AC_CHECK_LIB(testframework, main)

# autoheader kram:
AH_TOP([#ifndef INCLUDED_CONFIG_H
#define INCLUDED_CONFIG_H

#if defined(__GNUC__)
#define COMP_GCC
#endif])

AH_BOTTOM([#endif])

AH_TEMPLATE([OS_WIN32],  [Windows halt])
AH_TEMPLATE([OS_CYGWIN], [CYGWIN halt])
AH_TEMPLATE([OS_DARWIN], [Darwin])
AH_TEMPLATE([OS_POSIX],  [Any Posix compliant system])
AH_TEMPLATE([CPU_I386],  [Intel x86 CPU >= 386])


AC_CANONICAL_HOST
echo $host

# processor detection
case $host in
i[[3456]]86-*-*)
  AC_DEFINE([CPU_I386])
  echo "80x86 processor detexted (x >= 3)."
 ;;
esac

# os detection
case $host in
*-*-darwin*)
  AC_DEFINE([OS_DARWIN])
  AC_DEFINE([OS_POSIX])
 echo "Darwin OS detected."
 ;;
*gnu* )
 AC_DEFINE([OS_POSIX])
 echo "Posix OS detected."
 ;;
*cygwin* )
 AC_DEFINE([OS_POSIX])
 AC_DEFINE([OS_CYGWIN])
 echo "Cygwin OS detected."
esac

# Checks for typedefs, structures, and compiler characteristics.
# AC_C_CONST

# Checks for library functions.

#check for python
AC_CHECK_TOOL(PYTHON, python, -)
if test $PYTHON = "-"; then
	AC_ERROR([Python is required for base to build!]); 
fi


AC_OUTPUT(
Makefile
src/Makefile
src/interfaces/Makefile
src/TestFramework/Makefile
src/thread/Makefile
src/utils/Makefile
src/net/Makefile
src/netinterfaces/Makefile
)
