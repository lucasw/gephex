AC_INIT
AC_CONFIG_SRCDIR([base/src/utils/autoptr.h])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(gephex,0.0.4)
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CXX
AM_PROG_LIBTOOL

# gcc versions <= 2.95.2 don't have the standard c++ header
# sstream
AM_PATH_SSTREAM(have_sstream=yes, have_sstream=no)
# copy sstream_compat to sstream if sstream is missing:
if test "x$have_sstream" = "xno"
then
  echo "Using own sstream in util/include/compatibility"
  if ! cp $srcdir/util/include/compatibility/sstream_compat ./util/include/sstream;
  then
    AC_ERROR("Could not copy the sstream header!")
  fi
else
  # make sure there is no sstream header
  rm -f ./util/include/sstream
fi

# check for extra libs

# x11
AC_PATH_XTRA
AM_CONDITIONAL(HAVE_X11, test "x$no_x" != "xyes")
AH_TEMPLATE([HAVE_X11],  [build with x11 support])
if test "x$no_x" != "xyes"; then
	AC_DEFINE(HAVE_X11)
fi

# qt
AM_PATH_QT([2.3.0], have_qt=yes, have_qt=no)
AM_CONDITIONAL(HAVE_QT, test "x$have_qt" = "xyes")

# sdl
AM_PATH_SDL([1.1.0], have_sdl=yes, have_sdl=no)
AH_TEMPLATE([HAVE_SDL],  [build with sdl support])
AM_CONDITIONAL(HAVE_SDL, test "x$have_sdl" = "xyes")
if test "x$have_sdl" = "xyes"; then
        AC_DEFINE(HAVE_SDL)
fi

# SDL_image
AC_CHECK_HEADERS([SDL/SDL_image.h],
	have_sdl_image_header=yes,
	have_sdl_image_header=no)
AH_TEMPLATE([HAVE_SDL_IMAGE],  [build with libsdl_image support])
AM_CONDITIONAL(HAVE_SDL_IMAGE, test "x$have_sdl_image_header" = "xyes")
if test "x$have_sdl_image_header" = "xyes"; then
        AC_DEFINE(HAVE_SDL_IMAGE)
	AC_SUBST(SDL_IMAGE_LDFLAGS,"-lSDL_image")
fi

# SDL_ttf
AC_CHECK_HEADERS([SDL/SDL_ttf.h],
	have_sdl_ttf_header=yes,
	have_sdl_ttf_header=no)
AH_TEMPLATE([HAVE_SDL_TTF],  [build with libsdl true type font support])
AM_CONDITIONAL(HAVE_SDL_TTF, test "x$have_sdl_ttf_header" = "xyes")
if test "x$have_sdl_ttf_header" = "xyes"; then
        AC_DEFINE(HAVE_SDL_TTF)
	AC_SUBST(SDL_TTF_LDFLAGS,"-lSDL_ttf")
fi


# avifile
AM_PATH_AVIFILE([0.7.0], have_avifile=yes, have_avifile=no)
AM_CONDITIONAL(HAVE_AVIFILE, test "x$have_avifile" = "xyes")
AH_TEMPLATE([HAVE_AVIFILE], [Does libavifile exist on the system?])
if test "x$have_avifile" = "xyes"; then
        AC_DEFINE(HAVE_AVIFILE)
fi

# check for libmpeg3 
AC_CHECK_HEADERS([libmpeg3.h],have_mpeg3=yes,have_mpeg3=no)
AH_TEMPLATE([HAVE_MPEG3],  [build with libmpeg3 support])
AM_CONDITIONAL(HAVE_MPEG3, test "x$have_mpeg3" = "xyes")
if  test "x$have_mpeg3" = "xyes"; then 
	AC_DEFINE(HAVE_MPEG3) 
	AC_SUBST(MPEG3_LDFLAGS,[-lmpeg3]) 
fi

# OpenGL
AC_CHECK_HEADERS([GL/glx.h],have_glx=yes,have_glx=no)
AH_TEMPLATE([HAVE_GLX],  [build with gl output driver support])
AM_CONDITIONAL(HAVE_GLX, test "x$have_glx" = "xyes")
if test "x$have_glx" = "xyes"; then
	AC_DEFINE(HAVE_GLX)
	AC_SUBST(GLX_LDFLAGS, [-lgl])
fi

# libpng
AC_CHECK_HEADERS([png.h],have_png=yes,have_png=no)
AM_CONDITIONAL(HAVE_PNG, test "x$have_png" = "xyes")

# aalib
AC_CHECK_HEADERS([aalib.h],have_aalib_header=yes,have_aalib_header=no)
AC_CHECK_LIB(aa,aa_autoinit,  have_aalib_lib=yes, have_aalib_lib=no)
AM_CONDITIONAL(HAVE_AALIB, test "x$have_aalib_lib" = "xyes" && test "x$have_aalib_header" = "xyes" )

# alsalib
AC_CHECK_HEADERS([alsa/asoundlib.h],have_asoundlib_header=yes,have_asoundlib_header=no)
AC_CHECK_LIB(asound, snd_pcm_open,  have_asoundlib_lib=yes, have_asoundlib_lib=no)
if test "x$have_asoundlib_lib" = "xyes" && test "x$have_asoundlib_header" = "xyes";
then
have_asoundlib=yes
else
have_asoundlib=no
fi
AM_CONDITIONAL(HAVE_ASOUNDLIB, test "x$have_asoundlib" = "xyes")

# video4linux
AM_PATH_V4L(have_v4l=yes,have_v4l=no)
AM_CONDITIONAL(HAVE_V4L, test "x$have_v4l" = "xyes")

# oss
AC_CHECK_HEADERS([sys/soundcard.h],have_sys_soundcard_h=yes,have_sys_soundcard_h=no)
AM_CONDITIONAL(HAVE_OSS, test "x$have_sys_soundcard_h" = "xyes")


# audio (oss or alsa)
AM_CONDITIONAL(HAVE_ASOUNDLIB_OR_OSS, test "x$have_asoundlib" = "xyes" || test "x$have_sys_soundcard_h" = "xyes")

# joystick.h
AC_CHECK_HEADERS([linux/joystick.h],have_linux_joystick_h=yes,have_linux_joystick_h=no)
AM_CONDITIONAL(HAVE_LINUX_JOYSTICK, test "x$have_linux_joystick_h" = "xyes")

# joystick (linux or sdl)
AM_CONDITIONAL(HAVE_JOYSTICK, test "x$have_linux_joystick_h" = "xyes" || test "x$have_sdl" = "xyes")

# Checks for libraries.
AC_CHECK_LIB(dl,dlopen,
   LIB_DL_FLAGS="-ldl"
)
AC_SUBST(LIB_DL_FLAGS)

AC_CHECK_LIB(posix4, main,
   LIB_POSIX4_FLAGS="-lposix4"
)
AC_SUBST(LIB_POSIX4_FLAGS)

AC_CHECK_LIB(socket, socket)
AC_CHECK_FUNC(connect,,[AC_CHECK_LIB(socket,connect,
   LIB_SOCKET_FLAGS="-lsocket"
)])
AC_SUBST(LIB_SOCKET_FLAGS)

have_nanosleep=0
AC_CHECK_FUNC(nanosleep,have_nanosleep=1,[AC_CHECK_LIB(rt,nanosleep,
  [LIB_EXTRA_FLAGS="-lrt"; have_nanosleep=1]
  ,[AC_CHECK_LIB(posix4,nanosleep,
    [LIB_EXTRA_FLAGS="-lposix4"; have_nanosleep=1]
)])])
AC_SUBST(LIB_EXTRA_FLAGS)

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

AC_ARG_VAR([FRBINCACHE],
           [The size of the cache of the image source module in MB])
if test "x$FRBINCACHE" != "x"; then
AC_DEFINE_UNQUOTED([FRBINMODULE_CACHE_SIZE], $FRBINCACHE, [Size of the cache the frbinmodule uses (in MB)])
fi;

AC_CONFIG_FILES([Makefile
base/Makefile
base/src/Makefile
base/src/TestFramework/Makefile
base/src/interfaces/Makefile
base/src/net/Makefile
base/src/netinterfaces/Makefile
base/src/thread/Makefile
base/src/utils/Makefile
data/Makefile
doc/Makefile
doc/images/Makefile
engine/Makefile
engine/src/Makefile
engine/src/dllloader/Makefile
engine/src/engine/Makefile
engine/src/model/Makefile
engine/src/renderer/Makefile
examples/Makefile
examples/graphs/Makefile
examples/img/Makefile
modules/Makefile
modules/src/Makefile
modules/src/audioaddmodule/Makefile
modules/src/audiobdmodule/Makefile
modules/src/audioenergymodule/Makefile
modules/src/audioinmodule/Makefile
modules/src/audiooutmodule/Makefile
modules/src/audiospecmodule/Makefile
modules/src/audiosynthmodule/Makefile
modules/src/audiovismodule/Makefile
modules/src/audiowavegenmodule/Makefile
modules/src/blurmodule/Makefile
modules/src/bwmodule/Makefile
modules/src/color2number/Makefile
modules/src/diffmodule/Makefile
modules/src/doepfermodule/Makefile
modules/src/effecttvedgemodule/Makefile
modules/src/effectvagingmodule/Makefile
modules/src/effectvburnmodule/Makefile
modules/src/effectvcyclemodule/Makefile
modules/src/effectvdotmodule/Makefile
modules/src/effectvfiremodule/Makefile
modules/src/effectvlensmodule/Makefile
modules/src/effectvlifemodule/Makefile
modules/src/effectvpuzzlemodule/Makefile
modules/src/effectvquarkmodule/Makefile
modules/src/effectvsparkmodule/Makefile
modules/src/flashmodule/Makefile
modules/src/flipflopmodule/Makefile
modules/src/fpsmodule/Makefile
modules/src/frbinmodule/Makefile
modules/src/frboutmodule/Makefile
modules/src/functions/Makefile
modules/src/functions/jumpmodule/Makefile
modules/src/functions/numxfadermodule/Makefile
modules/src/gradnormmodule/Makefile
modules/src/ifsgenmodule/Makefile
modules/src/ifsmodule/Makefile
modules/src/ifsxfadermodule/Makefile
modules/src/imagebuffermodule/Makefile
modules/src/imagewritermodule/Makefile
modules/src/imgarithmodule/Makefile
modules/src/isingnoizemodule/Makefile
modules/src/joystickmodule/Makefile
modules/src/libeffectv/Makefile
modules/src/libeffectv/trick/Makefile
modules/src/libgrid/Makefile
modules/src/libmidi/Makefile
modules/src/libscale/Makefile
modules/src/midiinmodule/Makefile
modules/src/netcontrolmodule/Makefile
modules/src/numarithmodule/Makefile
modules/src/number2color/Makefile
modules/src/numbermodule/Makefile
modules/src/numenvmodule/Makefile
modules/src/numlfomodule/Makefile
modules/src/numposmodule/Makefile
modules/src/overlaymodule/Makefile
modules/src/pixelizemodule/Makefile
modules/src/planemodule/Makefile
modules/src/plasma/Makefile
modules/src/posnummodule/Makefile
modules/src/rangeconvertmodule/Makefile
modules/src/resultmodule/Makefile
modules/src/rotozoommodule/Makefile
modules/src/sdlfontmodule/Makefile
modules/src/signalgenmodules/Makefile
modules/src/staticcolormodule/Makefile
modules/src/stringtokenizermodule/Makefile
modules/src/tunnelmodule/Makefile
modules/src/twolayermodule/Makefile
modules/src/v4lmodule/Makefile
modules/src/xfademodule/Makefile
qtgui/Makefile
qtgui/src/Makefile
qtgui/src/gui/Makefile
qtgui/src/gui/base/Makefile
qtgui/src/gui/dialogs/Makefile
qtgui/src/gui/editor/Makefile
qtgui/src/gui/typeviews/Makefile
qtgui/src/guimodel/Makefile
types/Makefile
types/src/Makefile
types/src/audiotype/Makefile
types/src/envtype/Makefile
types/src/framebuffertype/Makefile
types/src/ifstype/Makefile
types/src/lfotype/Makefile
types/src/miditype/Makefile
types/src/numbertype/Makefile
types/src/positiontype/Makefile
types/src/rgbtype/Makefile
types/src/stringtype/Makefile
util/Makefile
util/include/Makefile
util/include/compatibility/Makefile
util/src/Makefile
util/src/cpuinfo/Makefile
util/src/joystick_net_midi/Makefile
util/src/libgeo/Makefile
util/src/libjoystick/Makefile
util/src/misc/Makefile
])
AC_OUTPUT
#
#modules/src/starfield/Makefile
#modules/src/libmpeg3module/Makefile

MISSING_LIB_TEXT="Some modules will not be compiled! Install the missing
library/headers and run configure again to activate these modules."

if test "x$have_sdl" != "xyes";  then
   echo Note: No SDL support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_sdl_image_header" != "xyes";  then
   echo Note: No SDL-image support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_sdl_ttf_header" != "xyes";  then
   echo Note: No SDL_ttf support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_avifile" != "xyes"; then
   echo Note: No Avifile support found.
   echo $MISSING_LIB_TEXT
fi

#if test "x$have_mpeg3" != "xyes"; then
#   echo Note: No Mpeg3 support found.
#   echo $MISSING_LIB_TEXT
#fi

#if test "x$have_glx" != "xyes"; then
#   echo Note: No OpenGL / GLX support found.
#   echo $MISSING_LIB_TEXT
#fi

if test "x$have_png" != "xyes"; then
   echo Note: No PNG support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_aalib_lib" != "xyes" || test "x$have_aalib_header" != "xyes"; then
   echo Note: No AALIB support found.
   echo $MISSING_LIB_TEXT
fi

if test "x$have_asoundlib" != "xyes"; then
   echo "Note: No ASOUNDLIB (ALSA) support found."
   echo $MISSING_LIB_TEXT
fi

if test "x$have_sys_soundcard_h" != "xyes"; then
   echo "Note: No OpenSoundSystem (OSS) support found."
   echo $MISSING_LIB_TEXT
fi

if test "x$have_v4l" != "xyes"; then
   echo "Note: No Video4Linux (v4l) support found."
   echo $MISSING_LIB_TEXT
fi

if test "x$have_qt" != "xyes"; then
  echo Note: No QT support found!! GUI will not be built!!!
  echo If you know you have qt installed, try to rerun configure with
  echo the "--with-qt-(lib|bin|inc)dir=<YOUR QT DIRS>" flags.
  echo For details do "./configure --help".
  echo Also we would appreciate your feedback in that case,
  echo to improve our autoconf test for qt.
  echo Sorry for the inconvinience.
fi