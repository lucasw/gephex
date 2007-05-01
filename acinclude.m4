# AM_PATH_AVIFILE 0.1.0
# CXXFLAGS and LIBS for avifile

# modified from the below version by georg for GePhex
# changes: perform ACTION-IF-FOUND and ACTION-IF-NOT-FOUND
#          filter out -Wl,-rpath,... option in AVIFILE_LDFLAGS

# taken from Autostar Sandbox, http://autostars.sourceforge.net/
# constructed by careful cross-pollination from various sources and lots of
# hard labour

dnl Usage:
dnl AM_PATH_AVIFILE(MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for avifile, and defines
dnl - AVIFILE_CXXFLAGS (C++ compiler flags)
dnl - AVIFILE_LDFLAGS (linker flags, stripping and path)
dnl as well as set HAVE_AVIFILE to yes or no
dnl
dnl FIXME: should define AVIFILE_VERSION
dnl
dnl prerequisites:
dnl - working C++ compiler
dnl - usable libstdc++
dnl - AC_PATH_XTRA

AC_DEFUN([AM_PATH_AVIFILE],
[
    AC_REQUIRE([AC_PROG_CXX])
    AC_REQUIRE([AC_PATH_XTRA])
    HAVE_AVIFILE=no

    dnl first look for avifile-config
    AC_PATH_PROG(AVIFILE_CONFIG, avifile-config, no)
    min_avifile_version=ifelse([$1], ,0.7.0, $1)
    if test "x$AVIFILE_CONFIG" != "xno"; then
	dnl now that we have it, we need to save libs and cflags
        dnl we remove the -rpath flag from the LD_FLAGS, because
        dnl debian does not like this
	AVIFILE_LDFLAGS=`avifile-config --libs | \
            sed 's/-Wl,-rpath,[[^ ]]* //g'`
	AVIFILE_CXXFLAGS=`avifile-config --cflags`
	AC_SUBST(AVIFILE_LDFLAGS)
	AC_SUBST(AVIFILE_CXXFLAGS)
	HAVE_AVIFILE=yes
    fi

    dnl we got this far, now start checking if we have the right version
    if test x$HAVE_AVIFILE = xyes ; then
	AC_MSG_CHECKING(for avifile - version >= $min_avifile_version)
	dnl first get the version number from avifile-config
	avifile_major_version=`$AVIFILE_CONFIG $avifile_args --version | \
	     sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
	avifile_minor_version=`$AVIFILE_CONFIG $avifile_args --version | \
	     sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
	avifile_micro_version=`$AVIFILE_CONFIG $avifile_config_args --version | \
	     sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

	dnl now run a short C app that tells us if the version is ok or not
	dnl all of this is boilerplate code from other examples
	rm -f conf.avifiletest
	AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main ()
{
  int major, minor, micro;
  char ver[50];

  system ("touch conf.avifiletest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  strncpy(ver, "$min_avifile_version", sizeof(ver) - 1);
  if (sscanf(ver, "%d.%d.%d", &major, &minor, &micro) != 3)
  {
    printf ("%s, bad version string\n", "$min_avifile_version");
    exit (1);
  }
  if (($avifile_major_version > major) ||
     (($avifile_major_version == major) && ($avifile_minor_version > minor)) ||
     (($avifile_major_version == major) && ($avifile_minor_version == minor) && ($avifile_micro_version >= micro)))
    return 0;
  else
  {
    printf ("\n*** 'avifile-config --version' returned %d.%d.%d, but the minimum version\n", $avifile_major_version, $avifile_minor_version, $avifile_micro_version);
    printf ("*** of AVIFILE required is %d.%d.%d. If avifile-config is correct, then it is\n", major, minor, micro);
    printf ("*** best to upgrade to the required version.\n");
    printf ("*** If avifile-config was wrong, set the environment variable AVIFILE_CONFIG\n");
    printf ("*** to point to the correct copy of avifile-config, and remove the file\n");
    printf ("*** config.cache (if it exists) before re-running configure\n");
    return 1;
  }
}
    ],
    [
	AC_MSG_RESULT(yes)
	HAVE_AVIFILE=yes
    ],
    [
        HAVE_AVIFILE=no
    ])
    fi

    if test x$HAVE_AVIFILE = xyes ; then
        dnl now try to compile a sample test app

	dnl first save whatever language we're currently testing in
	dnl AC_LANG_SAVE
	dnl AC_LANG_CPLUSPLUS
	AC_LANG_PUSH(C++)
	ac_save_CXXFLAGS=$CXXFLAGS
	ac_save_LDFLAGS=$LDFLAGS
	dnl add X flags, because it looks like avifile needs libXv and libXxf86vm
	CXXFLAGS="$CXXFLAGS $AVIFILE_CXXFLAGS"
	LDFLAGS="$LDFLAGS $AVIFILE_LDFLAGS $X_LIBS -lXv -lXxf86vm"

	AC_MSG_CHECKING(compilation of avifile test program)
	dnl try the compile
	AC_TRY_LINK([
#include <stdio.h>
#include <stdlib.h>
#include <avifile.h>
#include <creators.h>
	], [
/* function body */
IVideoDecoder *decoder;
BITMAPINFOHEADER bh;

decoder = Creators::CreateVideoDecoder(bh) ],
	[ AC_MSG_RESULT(succeeded) ],
	[ AC_MSG_RESULT(failed) ; HAVE_AVIFILE=no ] )
	AC_LANG_RESTORE
	CXXFLAGS="$ac_save_CXXFLAGS"
	LDFLAGS="$ac_save_LDFLAGS"
    fi

    if test "x$HAVE_AVIFILE" = "xyes"
    then
      ifelse([$2], , :, [$2])
    else
      ifelse([$3], , :, [$3])
    fi
    rm -f conf.avifiletest
])
dnl dx.m4
dnl set directx compiler and linker flags
dnl Note: the variable DXSDK_DIR must be set
dnl or --with-dxsdk-dir must be given
dnl
dnl AM_PATH_DX(MINIMUM_VERSION, 
dnl            [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN([AM_PATH_DX],
[
AC_CHECKING([for DirectX ...])

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

saved_LD_LIBRARY_PATH="$LD_LIBRARY_PATH"
saved_LIBRARY_PATH="$LIBRARY_PATH"
saved_CXXFLAGS="$CXXFLAGS"
saved_LDFLAGS="$LDFLAGS"
saved_LIBS="$LIBS"

HAVE_DX=no
min_dx_version=ifelse([$1], ,8.0, $1)

AC_ARG_WITH([dxsdk-dir],
  [AC_HELP_STRING([--with-dxsdk-dir=PFX],
                  [Prefix where DirectX is installed (optional, if not given, the environment variable DXSDK_DIR is used)])],
  dxsdk_dir="$withval",
  dxsdk_dir=""
)

dnl Check whether the headers can be found

if test "x$dxsdk_dir" = "x"
then
  dxsdk_dir=$DXSDK_DIR
  AC_MSG_NOTICE([using environment variable DXSDK_DIR...])
fi

AC_MSG_NOTICE([looking in $dxsdk_dir/Include ...])

if test -e $dxsdk_dir/Include/ddraw.h
then
  HAVE_DX=yes
  DX_CXXFLAGS="-I$dxsdk_dir/Include"
  DX_LIBS="-L$dxsdk_dir/Lib -lddraw"

  AC_MSG_RESULT([found in $dxsdk_dir])
else
  AC_MSG_RESULT([not found])
  HAVE_DX=no
fi

if test "x$HAVE_DX" = "xyes"
then
  ifelse([$2], , :, [$2])
else
  ifelse([$3], , :, [$3])
fi

AC_SUBST(DX_CXXFLAGS)
AC_SUBST(DX_LIBS)

AC_LANG_RESTORE()

LD_LIBRARY_PATH="$saved_LD_LIBRARY_PATH"
LIBRARY_PATH="$saved_LIBRARY_PATH"
CXXFLAGS="$saved_CXXFLAGS"
LDFLAGS="$saved_LDFLAGS"
LIBS="$saved_LIBS"
dnl rm -f conf.qttest
])

dnl 
dnl CHECK_EXTRA_LIB([LIB-NAME], [LIB-CHECK], [DEFAULT],
dnl                 [WITH_VAR_NAME], [TEST_VAR_NAME], [USE_VAR_NAME],
dnl                 [ACTION_IF_USED])
dnl
dnl Checks for a library and sets automake conditionals and C defines in
dnl config.h based on the result.
dnl
dnl LIB-NAME:  the name used for output, the AM_CONDITIONAL and the AC_DEFINE
dnl LIB-CHECK: the autoconf code to perform the check for the library.
dnl            it must set the variable TEST_VAR_NAME to yes or no
dnl DEFAULT:   yes if the library should be used by default, no if not
dnl WITH_VAR_NAME: the name of the variable that should be set to indicate
dnl                wether the user wants this library (as specified with
dnl                a --with-LIB-NAME option to configure)
dnl TEST_VAR_NAME: the name of the variable that is set by LIB-CHECK to
dnl                indicate wether the library is present
dnl USE_VAR_NAME:  the name of the variable that is set to yes if
dnl                WITH_VAR_NAME = yes and TEST_VAR_NAME = yes (otherwise
dnl                it is set to no)
dnl ACTION_IF_USED: [optional] an action to be performed if USE_VAR_NAME=yes
dnl
dnl This macro first adds a command line switch to configure (with
dnl AC_ARG_WITH) which allows the user to turn the use of the library 
dnl on or off.
dnl If the library should be used, the LIB-CHECK is performed to check
dnl wether the library is available.
dnl If this test is successful, an AC_DEFINE "WITH_<LIB-NAME>" is set to 1
dnl and the optional ACTION-IF-USED is performed.
dnl In any case, an AM_CONDITIONAL "WITH_<LIB-NAME>" is set depending on
dnl the value of USE_VAR_NAME.
dnl
AC_DEFUN([CHECK_EXTRA_LIB],
[
AC_MSG_NOTICE([checking for $1])

AC_ARG_WITH([$1],
	    [AC_HELP_STRING([--with-$1],
		            [Turn on $1 support (default=$3).])],
            [case "${withval}" in
       yes)
       	 AC_MSG_NOTICE([$1 support turned on])
         [$4]=yes
       ;;
       no)
	 AC_MSG_NOTICE([$1 support turned off])
         [$4]=no
       ;;
       *)
         AC_MSG_ERROR([bad value ${withval} for --with-$1])
       ;;
     esac],[[$4]=[$3]])


if test "x$[$4]" = "xyes"; then
  ifelse([$2], , :, [$2])
  if test "x$[$5]" = "xyes"; then
    [$6]=yes
    AC_DEFINE([WITH_$1], [1], [build with $1 support])
    ifelse([$7], , :, [$7])
    AC_MSG_NOTICE([$1 is active])
  else
    [$6]=no
    AC_MSG_WARN([No $1 support found.])
    AC_MSG_NOTICE([$1 is not active])
  fi
else
  [$6]=no
  AC_MSG_NOTICE([$1 is not active])
fi

])
dnl qt.m4
dnl Adapted to GePhex by Georg Seidel <georg.seidel@web.de>
dnl Changes made: 
dnl    - added support for Darwin (made shared library extension a
dnl      new parameter
dnl    - added check for libqt-mt
dnl    - added minimum version check
dnl    - replaced AC_ERROR with AC_MSG_RESULT
dnl    - moved evaluation of ACTION-IF-FOUND and ACTION-IF-NOT-FOUND
dnl      to the end
dnl    - added a lot more guess dirs
dnl    - adapted to qt4 only
dnl    - adapted to mac os x frameworks
dnl     
dnl Original version from Rik Hemsley:
dnl   Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>


dnl AM_PATH_QT(MINIMUM_VERSION, LIBEXT, 
dnl            [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN([AM_PATH_QT],
[
AC_CHECKING([for Qt ...])

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

saved_LD_LIBRARY_PATH="$LD_LIBRARY_PATH"
saved_LIBRARY_PATH="$LIBRARY_PATH"
saved_CXXFLAGS="$CXXFLAGS"
saved_LDFLAGS="$LDFLAGS"
saved_LIBS="$LIBS"

# the test looks inside the following files to find the qt headers, libs
# and binaries
GUESS_QT_INC_DIRS="$QTDIR/include $QTDIR/include/qt /usr/include /usr/include/qt  /usr/include/qt4 /usr/local/include /usr/local/include/qt /usr/local/include/qt4 /usr/X11R6/include/ /usr/X11R6/include/qt /usr/X11R6/include/X11/qt /usr/X11R6/include/qt4 /usr/lib/qt/include /usr/lib/qt4/include /usr/lib/qt-4/include /usr/lib/qt-4.0/include /usr/lib/qt-4.1/include /usr/lib/qt-4.2/include /sw/include/qt"

GUESS_QT_LIB_DIRS="$QTDIR/lib /usr/lib /usr/local/lib /usr/X11R6/lib /usr/local/qt/lib /usr/lib/qt/lib /usr/lib/qt4/lib /usr/lib/qt-4/lib /usr/lib/qt-4.0/lib /usr/lib/qt-4.1/lib /usr/lib/qt-4.2/lib /usr/lib/qt-4.3/lib /usr/lib/qt-4.4/lib /sw/lib"

GUESS_QT_BIN_DIRS="$QTDIR/bin /usr/bin /usr/local/bin /usr/local/bin/qt4 /usr/X11R6/bin /usr/lib/qt/bin /usr/lib/qt4/bin /usr/lib/qt-4/bin /usr/lib/qt-340/bin /usr/lib/qt-4.1/bin /usr/lib/qt-4.2/bin /usr/lib/qt-4.3/bin /usr/lib/qt-4.4/bin /sw/bin"

HAVE_QT=no
min_qt_version=ifelse([$1], ,4.0.0, $1)

AC_ARG_WITH([qt-libdir],
  [AC_HELP_STRING([--with-qt-libdir=PFX],
                  [Prefix where Qt library is installed (optional)])],
  qt_libdir="$withval",
  qt_libdir=""
)

AC_ARG_WITH([qt-incdir],
  [AC_HELP_STRING([--with-qt-incdir=PFX],
                  [Prefix where Qt includes are installed (optional)])],
  qt_incdir="$withval",
  qt_incdir=""
)

AC_ARG_WITH([qt-bindir],
  [AC_HELP_STRING([--with-qt-bindir=PFX],
                  [Prefix where moc and uic are installed (optional)])],
  qt_bindir="$withval",
  qt_bindir=""
)

AC_MSG_CHECKING([include path])

dnl If we weren't given qt_incdir, have a guess.

if test "x$qt_incdir" != "x"
then
  AC_MSG_RESULT([specified as $qt_incdir])
else

  for dir in $GUESS_QT_INC_DIRS
  do
    if test -e $dir/qobject.h || test -e $dir/Qt/qobject.h
    then
      qt_incdir="$dir -I$dir/QtCore"
      AC_MSG_RESULT([assuming $dir])
      break
    fi

    if test -e $dir/../lib/QtCore.framework/Headers/qobject.h
    then
      qt_incdir="$dir/../lib/QtCore.framework/Headers -F$dir/../lib"
      AC_MSG_RESULT([using frameworks, assuming $dir])
      break
    fi

  done

  if test "x$qt_incdir" = "x"
  then
    AC_MSG_RESULT([not found])
  fi

fi

dnl If we weren't given qt_libdir, have a guess.

AC_MSG_CHECKING([library path])

if test "x$qt_libdir" != "x"
then
  AC_MSG_RESULT([specified as $qt_libdir])
else
  for dir in $GUESS_QT_LIB_DIRS
  do
    if test -e $dir/libQtCore.$2
    then
      qt_libdir=$dir
      qt_ld_flag="-lQtCore -lQtGui"
      AC_MSG_RESULT([assuming $dir])
      break
    fi

    if test -e $dir/libQtCore4.$2
    then
      qt_libdir=$dir
      qt_ld_flag="-lQtCore4 -lQtGui4"
      AC_MSG_RESULT([assuming $dir])
      break
    fi

    dnl Look for frameworks

    if test -e $dir/QtCore.framework
    then
      qt_libdir=$dir
      qt_ld_flag="-F$dir -framework QtCore -framework QtGui"
      AC_MSG_RESULT([using frameworks, assuming $dir])
      break
    fi
  done

  if test "x$qt_ld_flag" = "x"
  then
    AC_MSG_RESULT([not found])
  fi

fi


dnl If we weren't given qt_bindir, have a guess.

AC_MSG_CHECKING([binary directory])

if test "x$qt_bindir" != "x"
then
  AC_MSG_RESULT([specified as $qt_bindir])
else

  for dir in $GUESS_QT_BIN_DIRS
  do
    if test -x $dir/moc -a -x $dir/uic
    then
      qt_bindir=$dir
      AC_MSG_RESULT([assuming $dir])
      break
    fi
  done

  if test "x$qt_bindir" = "x"
  then
    AC_MSG_RESULT([not found])
  fi
fi

dnl ifelse is talked about in m4 docs

if test "x$qt_incdir" = "x"
then
  AC_MSG_RESULT([Can't find includes])
elif test "x$qt_ld_flag" = "x"
then
  AC_MSG_RESULT([Can't find library])
elif test "x$qt_bindir" = "x"
then
  AC_MSG_RESULT([Can't find moc and/or uic])
else
  HAVE_QT=yes
fi

LDFLAGS="$LDFLAGS -L$qt_libdir"
LIBS="$LIBS $qt_ld_flag"

CXXFLAGS="$CXXFLAGS -I$qt_incdir"

LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$qt_libdir"

dnl we got this far, now start checking if we have the right version
if test "x$HAVE_QT" = "xyes"
then
  AC_MSG_CHECKING(for qt - version >= $min_qt_version)
	dnl now run a short C app that tells us if the version is ok or not
        rm -f conf.qttest
	AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <QtCore/qglobal.h>

int
main ()
{
  int major, minor, micro;
  char ver[50];

  system ("touch conf.qttest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  strncpy(ver, "$min_qt_version", sizeof(ver) - 1);
  if (sscanf(ver, "%d.%d.%d", &major, &minor, &micro) != 3)
  {
    printf ("%s, bad version string\n", "$min_qt_version");
    exit (1);
  }

  if ( QT_VERSION >= major*100 + minor*10 + micro )
  {
    printf("%s - ", QT_VERSION_STR);
    return 0;
  }
  else
  {
    printf("\n*** Version of QT found is too old: QT_VERSION is %i.\n",
            QT_VERSION);
    printf("*** Upgrade QT and remove the file config.cache (if it exists)\n");
    printf("*** before re-running configure\n");
    return 1;
  }
}
    ],
    [
	AC_MSG_RESULT(yes)
	HAVE_QT=yes
    ],
    [
	AC_MSG_RESULT(no)
        HAVE_QT=no
    ])
fi

found_qt="no"

if test "x$HAVE_QT" = "xyes"
then
  if test -f conf.qttest ; then
      found_qt="yes"
  else
      AC_MSG_CHECKING([Could not run QT test program, checking if a Qt program links...])

      AC_TRY_LINK([
       #include <qstring.h>
      ],
      [
       QString s("Hello, world!");
       qDebug(s.latin1());
      ],
      found_qt="yes"
      AC_MSG_RESULT([ok]),
      AC_MSG_RESULT([failed - check config.log for details])
      )
  fi

  if test "x$found_qt" = "xyes"
  then
    QT_CXXFLAGS="-I$qt_incdir"

    QT_LIBS="-L$qt_libdir $qt_ld_flag"
    MOC="$qt_bindir/moc"
    UIC="$qt_bindir/uic"
    HAVE_QT=yes
  else
    HAVE_QT=no
  fi

  if test "x$HAVE_QT" = "xyes"
  then
    ifelse([$3], , :, [$3])
  else
    ifelse([$4], , :, [$4])
  fi
  
fi

AC_SUBST(QT_CXXFLAGS)
AC_SUBST(QT_LIBS)
AC_SUBST(MOC)
AC_SUBST(UIC)

AC_LANG_RESTORE()

LD_LIBRARY_PATH="$saved_LD_LIBRARY_PATH"
LIBRARY_PATH="$saved_LIBRARY_PATH"
CXXFLAGS="$saved_CXXFLAGS"
LDFLAGS="$saved_LDFLAGS"
LIBS="$saved_LIBS"
rm -f conf.qttest
])
# Configure paths for SDL
#
# Adapted for GePhex 4/2003
#  changes: -added AC_HELP_STRING, SDL_PREFIX
#           -changed SDL_LIBS to SDL_LD_FLAGS
#
# Sam Lantinga 9/21/99
# stolen from Manish Singh
# stolen back from Frank Belew
# stolen from Manish Singh
# Shamelessly stolen from Owen Taylor

dnl AM_PATH_SDL([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for SDL, and define SDL_CFLAGS, SDL_LD_FLAGS, and SDL_PREFIX
dnl
AC_DEFUN([AM_PATH_SDL],
[dnl 
dnl Get the cflags and libraries from the sdl-config script
dnl
AC_ARG_WITH([sdl-prefix],
            [AC_HELP_STRING([--with-sdl-prefix=PFX],
                            [Prefix where SDL is installed (optional)])],
            sdl_prefix="$withval", sdl_prefix="")

AC_ARG_WITH([sdl-exec-prefix],
            [AC_HELP_STRING([--with-sdl-exec-prefix=PFX],
                            [Exec prefix where SDL is installed (optional)])],
            sdl_exec_prefix="$withval", sdl_exec_prefix="")

AC_ARG_ENABLE([sdltest],
              [AC_HELP_STRING([--disable-sdltest],
                              [Do not try to compile and run a test SDL
                               program])],
		    , enable_sdltest=yes)

  if test x$sdl_exec_prefix != x ; then
     sdl_args="$sdl_args --exec-prefix=$sdl_exec_prefix"
     if test x${SDL_CONFIG+set} != xset ; then
        SDL_CONFIG=$sdl_exec_prefix/bin/sdl-config
     fi
  fi
  if test x$sdl_prefix != x ; then
     sdl_args="$sdl_args --prefix=$sdl_prefix"
     if test x${SDL_CONFIG+set} != xset ; then
        SDL_CONFIG=$sdl_prefix/bin/sdl-config
     fi
  fi

  AC_REQUIRE([AC_CANONICAL_TARGET])
  AC_PATH_PROG(SDL_CONFIG, sdl-config, no)
  min_sdl_version=ifelse([$1], ,0.11.0,$1)
  AC_MSG_CHECKING(for SDL - version >= $min_sdl_version)
  no_sdl=""
  if test "$SDL_CONFIG" = "no" ; then
    no_sdl=yes
  else
    SDL_PREFIX=`$SDL_CONFIG $sdlconf_args --prefix`
    SDL_CFLAGS=`$SDL_CONFIG $sdlconf_args --cflags`
    SDL_LD_FLAGS=`$SDL_CONFIG $sdlconf_args --libs`

    sdl_major_version=`$SDL_CONFIG $sdl_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    sdl_minor_version=`$SDL_CONFIG $sdl_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    sdl_micro_version=`$SDL_CONFIG $sdl_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_sdltest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $SDL_CFLAGS"
      LIBS="$LIBS $SDL_LD_FLAGS"
dnl
dnl Now check if the installed SDL is sufficiently new. (Also sanity
dnl checks the results of sdl-config to some extent
dnl
      rm -f conf.sdltest
      AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"

char*
my_strdup (char *str)
{
  char *new_str;
  
  if (str)
    {
      new_str = (char *)malloc ((strlen (str) + 1) * sizeof(char));
      strcpy (new_str, str);
    }
  else
    new_str = NULL;
  
  return new_str;
}

int main (int argc, char *argv[])
{
  int major, minor, micro;
  char *tmp_version;

  /* This hangs on some systems (?)
  system ("touch conf.sdltest");
  */
  { FILE *fp = fopen("conf.sdltest", "a"); if ( fp ) fclose(fp); }

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_sdl_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_sdl_version");
     exit(1);
   }

   if (($sdl_major_version > major) ||
      (($sdl_major_version == major) && ($sdl_minor_version > minor)) ||
      (($sdl_major_version == major) && ($sdl_minor_version == minor) && ($sdl_micro_version >= micro)))
    {
      return 0;
    }
  else
    {
      printf("\n*** 'sdl-config --version' returned %d.%d.%d, but the minimum version\n", $sdl_major_version, $sdl_minor_version, $sdl_micro_version);
      printf("*** of SDL required is %d.%d.%d. If sdl-config is correct, then it is\n", major, minor, micro);
      printf("*** best to upgrade to the required version.\n");
      printf("*** If sdl-config was wrong, set the environment variable SDL_CONFIG\n");
      printf("*** to point to the correct copy of sdl-config, and remove the file\n");
      printf("*** config.cache before re-running configure\n");
      return 1;
    }
}

],, no_sdl=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CFLAGS="$ac_save_CFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_sdl" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$SDL_CONFIG" = "no" ; then
       echo "*** The sdl-config script installed by SDL could not be found"
       echo "*** If SDL was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the SDL_CONFIG environment variable to the"
       echo "*** full path to sdl-config."
     else
       if test -f conf.sdltest ; then
        :
       else
          echo "*** Could not run SDL test program, checking why..."
          CFLAGS="$CFLAGS $SDL_CFLAGS"
          LIBS="$LIBS $SDL_LD_FLAGS"
          AC_TRY_LINK([
#include <stdio.h>
#include "SDL.h"

int main(int argc, char *argv[])
{ return 0; }
#undef  main
#define main K_and_R_C_main
],      [ return 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding SDL or finding the wrong"
          echo "*** version of SDL. If it is not finding SDL, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means SDL was incorrectly installed"
          echo "*** or that you have moved SDL since it was installed. In the latter case, you"
          echo "*** may want to edit the sdl-config script: $SDL_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     SDL_PREFIX=""
     SDL_CFLAGS=""
     SDL_LD_FLAGS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(SDL_PREFIX)
  AC_SUBST(SDL_CFLAGS)
  AC_SUBST(SDL_LD_FLAGS)
  rm -f conf.sdltest
])
dnl tests wether the sstream header exists
dnl AM_PATH_SSTREAM([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN([AM_PATH_SSTREAM],
[
AC_MSG_CHECKING(for sstream header...)

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

AC_TRY_COMPILE([#include <sstream>],[std::ostringstream os; os << "hallo";],
               have_sstream=yes, have_sstream=no)

if test "x$have_sstream" = "xyes"
then
  AC_MSG_RESULT(ok)
  ifelse([$1], , :, [$1])
else
  AC_MSG_RESULT(missing)
  ifelse([$2], , :, [$2])
fi

AC_LANG_RESTORE()
])
dnl tests wether the v4l videodev header exists
dnl AM_PATH_V4L([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN([AM_PATH_V4L],
[
AC_MSG_CHECKING(for v4l header...)

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

dnl AC_CHECK_HEADER([modules/src/v4lmodule/videodev.h],have_videodev_header=yes,have_videodev_header=no)

dnl if test "x$have_videodev_header" = "xyes"
dnl then
  AC_MSG_CHECKING(found header, checking wether it compiles)
  AC_TRY_COMPILE([#include <cstdlib>
                #include <linux/types.h>],[],
               videodev_h_compiles=yes,videodev_h_compiles=no)

  if test "x$videodev_h_compiles" = "xyes"
  then
    AC_MSG_RESULT(ok)
    ifelse([$1], , :, [$1])
  else
    AC_MSG_RESULT(does not compile)
    ifelse([$2], , :, [$2])
  fi
dnl else
dnl   AC_MSG_RESULT(missing)
dnl   ifelse([$2], , :, [$2])
dnl fi

AC_LANG_RESTORE()
])
