running cat aclocal/avifile.m4 aclocal/qt.m4 aclocal/sdl.m4 aclocal/sstream.m4 ...
# AM_PATH_AVIFILE 0.1.0
# CXXFLAGS and LIBS for avifile

# modified from the below version by georg for GePhex
# cahnges: perform ACTION-IF-FOUND and ACTION-IF-NOT-FOUND

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

AC_DEFUN(AM_PATH_AVIFILE,
[
    AC_REQUIRE([AC_PROG_CXX])
    AC_REQUIRE([AC_PATH_XTRA])
    HAVE_AVIFILE=no

    dnl first look for avifile-config
    AC_PATH_PROG(AVIFILE_CONFIG, avifile-config, no)
    min_avifile_version=ifelse([$1], ,0.7.0, $1)
    if test "x$AVIFILE_CONFIG" != "xno"; then
	dnl now that we have it, we need to save libs and cflags
	AVIFILE_LDFLAGS=`avifile-config --libs`
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
])

dnl qt.m4
dnl Adapted to GePhex by Georg Seidel <georg.seidel@web.de>
dnl Changes made: 
dnl    -added minimum version check
dnl    -replaced AC_ERROR with AC_MSG_RESULT
dnl    -moved evaluation of ACTION-IF-FOUND and ACTION-IF-NOT-FOUND
dnl     to the end
dnl
dnl TODO: is it ok to just check fot libqt.so? what about libqt-mt.so?
dnl     
dnl Original version from Rik Hemsley:
dnl   Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>

dnl AM_PATH_QT(MINIMUM_VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN(AM_PATH_QT,
[
AC_CHECKING([for Qt ...])

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

saved_LD_LIBRARY_PATH="$LD_LIBRARY_PATH"
saved_LIBRARY_PATH="$LIBRARY_PATH"
saved_CXXFLAGS="$CXXFLAGS"
saved_LDFLAGS="$LDFLAGS"
saved_LIBS="$LIBS"

HAVE_QT=no
min_qt_version=ifelse([$1], ,2.3.0, $1)

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

  GUESS_QT_INC_DIRS="$QTDIR/include /usr/include /usr/include/qt /usr/include/qt2 /usr/include/qt3 /usr/local/include /usr/local/include/qt /usr/local/include/qt2 /usr/X11R6/include/ /usr/X11R6/include/qt /usr/X11R6/include/X11/qt /usr/X11R6/include/qt2 /usr/X11R6/include/X11/qt2"

  for dir in $GUESS_QT_INC_DIRS
  do
    if test -e $dir/qt.h
    then
      qt_incdir=$dir
      AC_MSG_RESULT([assuming $dir])
      break
    fi
  done

fi

dnl If we weren't given qt_libdir, have a guess.

AC_MSG_CHECKING([library path])

if test "x$qt_libdir" != "x"
then
  AC_MSG_RESULT([specified as $qt_libdir])
else

  GUESS_QT_LIB_DIRS="$QTDIR/lib /usr/lib /usr/local/lib /usr/X11R6/lib /usr/local/qt/lib"

  for dir in $GUESS_QT_LIB_DIRS
  do
    if test -e $dir/libqt.so
    then
      qt_libdir=$dir
      AC_MSG_RESULT([assuming $dir/libqt.so])
      break
    fi
  done
fi

dnl If we weren't given qt_bindir, have a guess.

AC_MSG_CHECKING([binary directory])

if test "x$qt_bindir" != "x"
then
  AC_MSG_RESULT([specified as $qt_bindir])
else

  GUESS_QT_BIN_DIRS="$QTDIR/bin /usr/bin /usr/local/bin /usr/local/bin/qt2 /usr/X11R6/bin"

  for dir in $GUESS_QT_BIN_DIRS
  do
    if test -x $dir/moc -a -x $dir/uic
    then
      qt_bindir=$dir
      AC_MSG_RESULT([assuming $dir])
      break
    fi
  done
fi

dnl ifelse is talked about in m4 docs

if test "x$qt_incdir" = "x"
then
  AC_MSG_RESULT([Can't find includes])
elif test "x$qt_libdir" = "x"
then
  AC_MSG_RESULT([Can't find library])
elif test "x$qt_bindir" = "x"
then
  AC_MSG_RESULT([Can't find moc and/or uic])
else
  HAVE_QT=yes
fi

  LDFLAGS="$LDFLAGS -L$qt_libdir"
  LIBS="$LIBS -lqt"
  CXXFLAGS="$CXXFLAGS -I$qt_incdir"
  LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$qt_libdir"

dnl we got this far, now start checking if we have the right version
if test "x$HAVE_QT" = "xyes"
then
  AC_MSG_CHECKING(for qt - version >= $min_qt_version)
	dnl now run a short C app that tells us if the version is ok or not
	AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <qglobal.h>

int
main ()
{
  int major, minor, micro;
  char ver[50];

  //system ("touch conf.qttest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  strncpy(ver, "$min_qt_version", sizeof(ver) - 1);
  if (sscanf(ver, "%d.%d.%d", &major, &minor, &micro) != 3)
  {
    printf ("%s, bad version string\n", "$min_qt_version");
    exit (1);
  }

  if ( QT_VERSION >= major*100 + minor*10 + micro )
    return 0;
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
        HAVE_QT=no
    ])
fi

if test "x$HAVE_QT" = "xyes"
then
  AC_MSG_CHECKING([if a Qt program links])

  found_qt="no"

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

  if test "x$found_qt" = "xyes"
  then
    QT_CXXFLAGS="-I$qt_incdir"
    QT_LIBS="-L$qt_libdir -lqt"
    MOC="$qt_bindir/moc"
    UIC="$qt_bindir/uic"
    HAVE_QT=yes
  else
    HAVE_QT=no
  fi

  if test "x$HAVE_QT" = "xyes"
  then
    ifelse([$2], , :, [$2])
  else
    ifelse([$3], , :, [$3])
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
])
# Configure paths for SDL
# Adapted for GePhex 4/2003
#  changes: added AC_HELP_STRING

# Sam Lantinga 9/21/99
# stolen from Manish Singh
# stolen back from Frank Belew
# stolen from Manish Singh
# Shamelessly stolen from Owen Taylor

dnl AM_PATH_SDL([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for SDL, and define SDL_CFLAGS and SDL_LIBS
dnl
AC_DEFUN(AM_PATH_SDL,
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
    SDL_CFLAGS=`$SDL_CONFIG $sdlconf_args --cflags`
    SDL_LIBS=`$SDL_CONFIG $sdlconf_args --libs`

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
      LIBS="$LIBS $SDL_LIBS"
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
          LIBS="$LIBS $SDL_LIBS"
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
     SDL_CFLAGS=""
     SDL_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(SDL_CFLAGS)
  AC_SUBST(SDL_LIBS)
  rm -f conf.sdltest
])
dnl tests wether the sstream header exists
dnl AM_PATH_SSTREAM([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN(AM_PATH_SSTREAM,
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