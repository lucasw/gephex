AC_INIT
AC_CONFIG_SRCDIR([base/src/utils/autoptr.h])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(gephex,0.0.4alpha)
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CXX
AM_PROG_LIBTOOL

AM_PROG_LEX
AC_PROG_YACC

# gcc versions <= 2.95.2 don't have the standard c++ header
# sstream
AM_PATH_SSTREAM(have_sstream=yes, have_sstream=no)
# copy sstream_compat to sstream if sstream is missing:
if test "x$have_sstream" = "xno"
then
  echo "Using own sstream in util/include"
  if ! cp $srcdir/util/include/sstream_compat ./util/include/sstream;
  then
    AC_ERROR("Could not copy the sstream header!")
  fi
else
  # make sure there is no sstream header
  rm -f ./util/include/sstream
fi

AM_PATH_QT([2.3.0], have_qt=yes, have_qt=no)
AM_CONDITIONAL(HAVE_QT, test "x$have_qt" = "xyes")

AM_PATH_SDL([1.1.0], have_sdl=yes, have_sdl=no)
AM_CONDITIONAL(HAVE_SDL, test "x$have_sdl" = "xyes")

AM_PATH_AVIFILE([0.7.0], have_avifile=yes, have_avifile=no)
AM_CONDITIONAL(HAVE_AVIFILE, test "x$have_avifile" = "xyes")

# TODO: add better tests for these libraries!
AC_CHECK_HEADERS([libmpeg3.h],have_mpeg3=yes,have_mpeg3=no)
AC_CHECK_HEADERS([GL/glx.h],have_glx=yes,have_glx=no)
AC_CHECK_HEADERS([png.h],have_png=yes,have_png=no)
AC_CHECK_HEADERS([linux/videodev.h],with_v4l=yes,with_v4l=no)

AM_CONDITIONAL(HAVE_MPEG3, test "x$have_mpeg3" = "xyes")
AM_CONDITIONAL(HAVE_GLX, test "x$have_glx" = "xyes")
AM_CONDITIONAL(HAVE_PNG, test "x$have_png" = "xyes")
AM_CONDITIONAL(WITH_V4L, test "x$with_v4l" = "xyes")

# Checks for libraries.
#check wether -ldl is needed:
AC_CHECK_LIB(dl, dlopen,  need_dl=yes, need_dl=no)
AM_CONDITIONAL(NEED_DL, test "x$need_dl" = "xyes")
if test "x$need_dl" = "xyes"
then
  echo Using -ldl
else
  echo Omitting -ldl
fi

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
AH_TEMPLATE([OS_LINUX],  [Linux])
AH_TEMPLATE([OS_BSD],    [*BSD])
AH_TEMPLATE([OS_SOLARIS],[Sun Solaris])
AH_TEMPLATE([OS_POSIX],  [Any Posix compliant system])

AH_TEMPLATE([CPU_I386],  [Intel x86 compatible CPU >= 386])

AH_TEMPLATE([OPT_INCLUDE_MMX],
            [Include MMX support (only for x86 compatible CPUs)])
AH_TEMPLATE([OPT_SERIALIZE_FRAMEBUFFER],
            [Serialize the FrameBuffer-Type])

#AC_CANONICAL_HOST
echo Checking host type... $host

# processor detection
case $host in
i[[3456]]86-*-*)
  AC_DEFINE([CPU_I386])
  echo "80x86 processor detected (x >= 3)."
 ;;
esac

# os detection
case $host in
*-*-solaris*)
  AC_DEFINE([OS_SOLARIS])
  AC_DEFINE([OS_POSIX])
  echo "Solaris OS detected."
  ;;
*-*-darwin*)
  AC_DEFINE([OS_DARWIN])
  AC_DEFINE([OS_POSIX])
 echo "Darwin OS detected."
 ;;
*-*-linux*)
  AC_DEFINE([OS_LINUX])
  AC_DEFINE([OS_POSIX])
 echo "Linux OS detected."
 ;;
*-*-*bsd*)
  AC_DEFINE([OS_BSD])
  AC_DEFINE([OS_POSIX])
 echo "BSD OS detected."
 ;;
*gnu* )
 AC_DEFINE([OS_POSIX])
 echo "Posix OS detected."
 ;;
*cygwin* )
 AC_DEFINE([OS_POSIX])
 AC_DEFINE([OS_CYGWIN])
 echo "Cygwin OS detected."
 ;;
*)
 echo UNKNWON OS! Assuming Posix combatibility... 
 AC_DEFINE([OS_POSIX])
esac

# Checks for typedefs, structures, and compiler characteristics.
# AC_C_CONST

# Checks for library functions.

# not needed! the sources are built at 'make dist' time
#check for python
#AC_CHECK_TOOL(PYTHON, python, -)
#if test $PYTHON = "-"; then
#	AC_MSG_ERROR([Python is required for base to build!]); 
#fi


AC_ARG_ENABLE(mmx,
     [AC_HELP_STRING([--enable-mmx],
                     [Turn on MMX support.
                      Still runs on x86 that don't have MMX!])],
     [case "${enableval}" in
       yes)
       	 echo "MMX support activated" 
         enable_mmx=yes
         AC_DEFINE(OPT_INCLUDE_MMX)
       ;;
       no)
	 echo "MMX support turned off"
         enable_mmx=no
       ;;
       *)
         AC_MSG_ERROR(bad value ${enableval} for --enable-mmx)
       ;;
     esac],[enable_mmx=no])
     AM_CONDITIONAL(OPT_INCLUDE_MMX, test "x$enable_mmx" = "xyes")

AC_ARG_ENABLE(serialize-framebuffer,
     [AC_HELP_STRING([--enable-serialize-framebuffer],
                     [Serialize the framebuffer type
                      (for previews in the gui).])],
     [case "${enableval}" in
       yes)
       	 echo "Framebuffer serialization activated" 
         enable_serframe=yes
         AC_DEFINE(OPT_SERIALIZE_FRAMEBUFFER)
       ;;
       no)
	 echo "Framebuffer serialization deactivated"
         enable_serframe=no
       ;;
       *)
         AC_MSG_ERROR(bad value ${enableval} for --enable-serialize-framebuffer)
       ;;
     esac],[enable_serframe=no])
     AM_CONDITIONAL(OPT_SERIALIZE_FRAMEBUFFER,
                    test "x$enable_serframe" = "xyes")

AC_ARG_WITH(effectv,
     [AC_HELP_STRING([--with-effectv=dir],
                     [Compile with effectv. Needs effectv source files.
                      You must provide the effectv src dir.
                      Example: --with-effectv=/home/georg/effectv-0.38])],
     [case "${withval}" in
        no)
           with_effectv=no
        ;;
        *) 
           EFFECTV_SRC_DIR=${withval}

           AC_MSG_CHECKING(for EffecTV src dir ${withval})
           if (test ! -d ${withval} || test ! -d ${withval}/effects)
           then
             AC_MSG_RESULT(failed)
             echo "*** No such effectv src dir: $EFFECTV_SRC_DIR"
             echo "*** Disabling effectv support!"
             with_effectv=no
           else
             AC_MSG_RESULT(ok)
             AC_SUBST(EFFECTV_SRC_DIR)
             echo EffecTV support enabled
             echo EffecTV src dir = $EFFECTV_SRC_DIR
             with_effectv=yes
           fi
         ;;
      esac],[with_effectv=no])
AM_CONDITIONAL(EFFECTV, test "x$with_effectv" = "xyes")

AC_CONFIG_FILES([Makefile
base/Makefile
base/src/Makefile
base/src/interfaces/Makefile
base/src/TestFramework/Makefile
base/src/thread/Makefile
base/src/utils/Makefile
base/src/net/Makefile
base/src/netinterfaces/Makefile
engine/Makefile
engine/src/Makefile
engine/src/sequencer/Makefile
engine/src/dllloader/Makefile
engine/src/model/Makefile
engine/src/renderer/Makefile
engine/src/engine/Makefile
types/Makefile
types/src/Makefile
types/src/numbertype/Makefile
types/src/ifstype/Makefile
types/src/stringtype/Makefile
types/src/framebuffertype/Makefile
types/src/positiontype/Makefile
types/src/rgbtype/Makefile
types/src/miditype/Makefile
modules/Makefile
modules/src/Makefile
modules/src/libgrid/Makefile
modules/src/libmidi/Makefile
modules/src/libeffectv/Makefile
modules/src/libeffectv/trick/Makefile
modules/src/tunnelmodule/Makefile
modules/src/planemodule/Makefile
modules/src/rotozoommodule/Makefile
modules/src/blurmodule/Makefile
modules/src/addmodule/Makefile
modules/src/bwmodule/Makefile
modules/src/submodule/Makefile
modules/src/resultmodule/Makefile
modules/src/numbermodule/Makefile
modules/src/gloutmodule/Makefile
modules/src/bmpmodule/Makefile
modules/src/invertmodule/Makefile
modules/src/sdloutputmodule/Makefile
modules/src/xfademodule/Makefile
modules/src/plasma/Makefile
modules/src/signalgenmodules/Makefile
modules/src/imgsubmodule/Makefile
modules/src/staticcolormodule/Makefile
modules/src/numposmodule/Makefile
modules/src/posnummodule/Makefile
modules/src/functions/Makefile
modules/src/functions/jumpmodule/Makefile
modules/src/functions/numxfadermodule/Makefile
modules/src/flashmodule/Makefile
modules/src/joystickmodule/Makefile
modules/src/avifilemodule/Makefile
modules/src/v4lmodule/Makefile
modules/src/ifsmodule/Makefile
modules/src/netcontrolmodule/Makefile
modules/src/midiinmodule/Makefile
modules/src/doepfermodule/Makefile
modules/src/fpsmodule/Makefile
modules/src/isingnoizemodule/Makefile
modules/src/imagewritermodule/Makefile
modules/src/flipflopmodule/Makefile
modules/src/diffmodule/Makefile
modules/src/ifsgenmodule/Makefile
modules/src/ifsxfadermodule/Makefile
modules/src/number2color/Makefile
modules/src/color2number/Makefile
modules/src/rangeconvertmodule/Makefile
modules/src/imagebuffermodule/Makefile
modules/src/x11outmodule/Makefile
modules/src/effecttvedgemodule/Makefile
modules/src/effectvfiremodule/Makefile
modules/src/effectvlensmodule/Makefile
modules/src/effectvpuzzlemodule/Makefile
modules/src/effectvlifemodule/Makefile
modules/src/effectvagingmodule/Makefile
modules/src/effectvburnmodule/Makefile
modules/src/overlaymodule/Makefile
qtgui/Makefile
qtgui/src/Makefile
qtgui/src/guimodel/Makefile
qtgui/src/gui/Makefile
qtgui/src/gui/base/Makefile
qtgui/src/gui/editor/Makefile
qtgui/src/gui/typeviews/Makefile
util/Makefile
util/src/Makefile
util/src/libjoystick/Makefile
util/src/joystick_net_midi/Makefile
util/src/cpuinfo/Makefile
util/src/libgeo/Makefile
util/include/Makefile
doc/Makefile
doc/images/Makefile
data/Makefile
])
AC_OUTPUT

#modules/src/starfield/Makefile
#modules/src/imgaddmodule/Makefile
#modules/src/imgmulmodule/Makefile
#modules/src/libmpeg3module/Makefile


MISSING_LIB_TEXT="Some modules will not be compiled! Install the missing
library and run configure again to activate these modules."

if test "x$have_sdl" != "xyes"; then
   echo Note: No SDL support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_avifile" != "xyes"; then
   echo Note: No Avifile support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_mpeg3" != "xyes"; then
   echo Note: No Mpeg3 support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_glx" != "xyes"; then
   echo Note: No OpenGL / GLX support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_png" != "xyes"; then
   echo Note: No PNG support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_qt" != "xyes"; then
  echo Note: No QT support!! GUI will not be built!!!
fi