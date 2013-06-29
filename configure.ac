AC_INIT

AC_PREREQ(2.59) dnl force autoconf version
AC_CONFIG_SRCDIR([base/src/utils/autoptr.h])
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE(gephex,0.4.5)
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

# autoheader kram:
AH_TOP([#ifndef INCLUDED_CONFIG_H
#define INCLUDED_CONFIG_H

#if defined(__GNUC__)
#define COMP_GCC
#endif])

AH_BOTTOM([#endif])


AH_TEMPLATE([OS_WIN32],  [native win32 build])
AH_TEMPLATE([OS_CYGWIN], [CYGWIN build])
AH_TEMPLATE([OS_DARWIN], [Darwin build])
AH_TEMPLATE([OS_LINUX],  [Linux build])
AH_TEMPLATE([OS_BSD],    [*BSD build])
AH_TEMPLATE([OS_SOLARIS],[Sun Solaris build])
AH_TEMPLATE([OS_POSIX],  [Any Posix compliant system])

AH_TEMPLATE([CPU_I386],  [Intel x86 compatible CPU >= 386])

AH_TEMPLATE([OPT_INCLUDE_MMX],
            [Include MMX support (only for x86 compatible CPUs)])
AH_TEMPLATE([OPT_SERIALIZE_FRAMEBUFFER],
            [Serialize the FrameBuffer-Type])

#AC_CANONICAL_HOST
AC_MSG_NOTICE([processing host variable $host])

AC_MSG_CHECKING([for processor type])

# processor detection
case $host in
i[[3456]]86-*-*)
  AC_DEFINE([CPU_I386])
  CPU=i386
  AC_MSG_RESULT([80x86 processor detected (x >= 3).])
 ;;
*)
  AC_MSG_RESULT([non x86 processor detected])
esac

AM_CONDITIONAL(OS_DARWIN, false)

AM_CONDITIONAL(SHARED_USE_DEF_FILE, false)

SHAREDLIBEXT=so
AC_MSG_CHECKING([for OS])
# os detection
case $host in
*-*-darwin*)
  AC_DEFINE([OS_DARWIN])
  AC_DEFINE([OS_POSIX])
  AC_MSG_RESULT([Darwin detected.])
  AM_CONDITIONAL(OS_DARWIN, true)
  SHARED_COMP_FLAGS="-fno-common"
  SHARED_LD_FLAGS="-bundle -undefined dynamic_lookup"
 ;;
*-*-linux*)
  AC_DEFINE([OS_LINUX])
  AC_DEFINE([OS_POSIX])
  AC_MSG_RESULT([Linux detected.])
  SHARED_COMP_FLAGS="-fpic"
  SHARED_LD_FLAGS="-shared -fpic"
 ;;
*-*-*bsd*)
  AC_DEFINE([OS_BSD])
  AC_DEFINE([OS_POSIX])
  AC_MSG_RESULT([*BSD detected.])
  SHARED_COMP_FLAGS="-fpic"
  SHARED_LD_FLAGS="-shared -fpic"
 ;;
 *mingw* )
  AC_DEFINE([OS_WIN32])
  AC_MSG_RESULT([MinGW detected])
  SHAREDLIBEXT=dll
  QTLIBEXT=a
  os_windows=yes
  LIB_SOCKET_FLAGS="-lws2_32"
  SHARED_COMP_FLAGS=
  SHARED_LD_FLAGS="-shared"
  AM_CONDITIONAL(SHARED_USE_DEF_FILE, true)
 ;;
*)
 AC_MSG_RESULT([Unknown OS! Assuming Posix combatibility])
 AC_DEFINE([OS_POSIX])
 SHARED_COMP_FLAGS="-fpic"
 SHARED_LD_FLAGS="-shared -fpic"
esac

AM_CONDITIONAL(OS_WINDOWS, test "x$os_windows" != "x")

if test "x$QTLIBEXT" = "x"; then
  QTLIBEXT=$SHAREDLIBEXT
fi

# export the detected shared library extensions for use in
# Makefile.am fields
AC_SUBST(SHAREDLIBEXT)
AC_MSG_NOTICE([Shared library extension is "$SHAREDLIBEXT"])
AC_MSG_NOTICE([QT library extension is "$QTLIBEXT"])

AC_SUBST(SHARED_COMP_FLAGS)
AC_SUBST(SHARED_LD_FLAGS)

# gcc versions <= 2.95.2 don't have the standard c++ header
# sstream
AM_PATH_SSTREAM(have_sstream=yes, have_sstream=no)
# copy sstream_compat to sstream if sstream is missing:
if test "x$have_sstream" = "xno"
then
  AC_MSG_NOTICE([Using own sstream in util/include/compatibility])
  if ! cp $srcdir/util/include/compatibility/sstream_compat ./util/include/sstream;
  then
    AC_MSG_ERROR([Could not copy the sstream header!])
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

# directx
AM_PATH_DX([8.0], have_dx=yes, have_dx=no)
AM_CONDITIONAL(HAVE_DX, test "x$have_dx" = "xyes")

# qt
AM_PATH_QT([4.1.0], $QTLIBEXT, have_qt=yes, have_qt=no)
AM_CONDITIONAL(HAVE_QT, test "x$have_qt" = "xyes")

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


# Checks for typedefs, structures, and compiler characteristics.
# AC_C_CONST

# Checks for library functions.

# not needed! the sources are built at 'make dist' time
#check for python
#AC_CHECK_TOOL(PYTHON, python, -)
#if test $PYTHON = "-"; then
#	AC_MSG_ERROR([Python is required for base to build!]); 
#fi


# optional libraries

CHECK_EXTRA_LIB([GL],
                [AC_CHECK_HEADER([GL/glx.h],have_gl=yes,have_gl=no)],
                [no], [with_gl], [have_gl], [use_gl])
AM_CONDITIONAL([WITH_GL], test "x$use_gl" = "xyes")

CHECK_EXTRA_LIB([SDL], [AM_PATH_SDL([1.1.0], have_sdl=yes, have_sdl=no)],
                [yes], [with_sdl], [have_sdl], [use_sdl])
AM_CONDITIONAL([WITH_SDL], test "x$use_sdl" = "xyes")

CHECK_EXTRA_LIB([SDL_IMAGE],
                [ac_save_CFLAGS="$CFLAGS"
                 ac_save_CPPFLAGS="$CPPFLAGS"
                 CFLAGS="$CFLAGS $SDL_CFLAGS"
                 CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
                 AC_CHECK_HEADER([SDL_image.h],
                             	  have_sdl_image=yes,
                                  have_sdl_image=no)
                 CFLAGS="$ac_save_CFLAGS"
                 CPPFLAGS="$ac_save_CPPFLAGS"],
                [yes], [with_sdl_image], [have_sdl_image], [use_sdl_image],
                [AC_SUBST(SDL_IMAGE_LDFLAGS,"-lSDL_image")])
AM_CONDITIONAL([WITH_SDL_IMAGE], test "x$use_sdl_image" = "xyes")

CHECK_EXTRA_LIB([SDL_TTF],
                [ac_save_CFLAGS="$CFLAGS"
                 ac_save_CPPFLAGS="$CPPFLAGS"
                 CFLAGS="$CFLAGS $SDL_CFLAGS"
                 CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
                 AC_CHECK_HEADER([SDL_ttf.h],
                                  have_sdl_ttf=yes,
	                          have_sdl_ttf=no)
                 CFLAGS="$ac_save_CFLAGS"
                 CPPFLAGS="$ac_save_CPPFLAGS"],
                [yes], [with_sdl_ttf], [have_sdl_ttf], [use_sdl_ttf],
                [AC_SUBST(SDL_TTF_LDFLAGS, "-lSDL_ttf")])
AM_CONDITIONAL([WITH_SDL_TTF], test "x$use_sdl_ttf" = "xyes")

# avifile
CHECK_EXTRA_LIB([AVIFILE],
                [AM_PATH_AVIFILE([0.7.0], have_avifile=yes, have_avifile=no)],
                [no], [with_avifile], [have_avifile], [use_avifile])
AM_CONDITIONAL([WITH_AVIFILE], test "x$use_avifile" = "xyes")

# check for libmpeg3 
CHECK_EXTRA_LIB([MPEG3],
                [AC_CHECK_HEADER([libmpeg3.h],have_mpeg3=yes,have_mpeg3=no)],
                [no], [with_mpeg3], [have_mpeg3], [use_mpeg3],
                [AC_SUBST(MPEG3_LDFLAGS,"-lmpeg3")])
AM_CONDITIONAL([WITH_MPEG3], test "x$use_mpeg3" = "xyes")

# libpng
CHECK_EXTRA_LIB([LIBPNG],
                [AC_CHECK_HEADER([png.h],have_libpng=yes,have_libpng=no)],
                [no], [with_libpng], [have_libpng], [use_libpng])
AM_CONDITIONAL([WITH_LIBPNG], test "x$use_libpng" = "xyes")

# aalib
CHECK_EXTRA_LIB([AALIB],
                [AC_CHECK_HEADER([aalib.h],have_aalib=yes,have_aalib=no)],
                [yes], [with_aalib], [have_aalib], [use_aalib])
AM_CONDITIONAL([WITH_AALIB], test "x$use_aalib" = "xyes")

# alsalib
CHECK_EXTRA_LIB([ASOUNDLIB],
                [AC_CHECK_HEADER([alsa/asoundlib.h],
                                  have_asoundlib=yes,have_asoundlib=no)],
                [yes], [with_asoundlib], [have_asoundlib], [use_asoundlib])
AM_CONDITIONAL([WITH_ASOUNDLIB], test "x$use_asoundlib" = "xyes")

# video4linux
CHECK_EXTRA_LIB([V4L],
                [AM_PATH_V4L(have_v4l=yes,have_v4l=no)],
                [yes], [with_v4l], [have_v4l], [use_v4l])
AM_CONDITIONAL([WITH_V4L], test "x$use_v4l" = "xyes")

# oss
CHECK_EXTRA_LIB([OSS],
                [AC_CHECK_HEADER([sys/soundcard.h],have_oss=yes,have_oss=no)],
                [yes], [with_oss], [have_oss], [use_oss])
AM_CONDITIONAL([WITH_OSS], test "x$use_oss" = "xyes")

# audio (oss or alsa)
AM_CONDITIONAL(WITH_ANY_AUDIO_SUPPORT, test "x$use_asoundlib" = "xyes" || test "x$use_oss" = "xyes" || test "x$OS_WINDOWS" != "x" || test "x$OS_DARWIN" != "x")

# joystick.h
CHECK_EXTRA_LIB([LINUX_JOYSTICK],
                [AC_CHECK_HEADER([linux/joystick.h],
                                  have_linux_joystick=yes,
                                  have_linux_joystick=no)],
                [yes], [with_linux_joystick], [have_linux_joystick],
                [use_linux_joystick])
AM_CONDITIONAL([WITH_LINUX_JOYSTICK], test "x$use_linux_joystick" = "xyes")


# joystick (linux or sdl)
AM_CONDITIONAL(WITH_JOYSTICK, test "x$use_linux_joystick" = "xyes" || test "x$use_sdl" = "xyes")

# ffmpeg
CHECK_EXTRA_LIB([FFMPEG],
                [if test -d $srcdir/contrib/ffmpeg; then have_ffmpeg=yes; else have_ffmpeg=no; fi],
                [yes], [with_ffmpeg], [have_ffmpeg], [use_ffmpeg])
AM_CONDITIONAL([WITH_FFMPEG], test "x$use_ffmpeg" = "xyes")

AC_ARG_ENABLE(mmx,
     [AC_HELP_STRING([--enable-mmx],
                     [turn on MMX support
                      (still runs on x86 that don't have MMX) [default=yes]])],
     [case "${enableval}" in
       yes)
         enable_mmx=yes
       ;;
       no)
         enable_mmx=no
       ;;
       *)
         AC_MSG_ERROR(bad value ${enableval} for --enable-mmx)
       ;;
     esac],[enable_mmx=yes])

     if test "x$enable_mmx" = "xyes" && test "x$CPU" = "xi386"
     then
       	 AC_MSG_NOTICE([MMX support active])
         AC_DEFINE(OPT_INCLUDE_MMX)
     else
	 enable_mmx=no
	 AC_MSG_NOTICE([MMX support turned off])
     fi

     AM_CONDITIONAL(OPT_INCLUDE_MMX, test "x$enable_mmx" = "xyes")

AC_ARG_ENABLE(serialize-framebuffer,
     [AC_HELP_STRING([--enable-serialize-framebuffer],
                     [turn on serialization of the framebuffer type
                      (for previews in the gui) [default=no]])],
     [case "${enableval}" in
       yes)
       	 AC_MSG_NOTICE([framebuffer serialization activated]) 
         enable_serframe=yes
         AC_DEFINE(OPT_SERIALIZE_FRAMEBUFFER)
       ;;
       no)
	 AC_MSG_NOTICE([framebuffer serialization deactivated])
         enable_serframe=no
       ;;
       *)
         AC_MSG_ERROR(bad value ${enableval} for --enable-serialize-framebuffer)
       ;;
     esac],[enable_serframe=no])
     AM_CONDITIONAL(OPT_SERIALIZE_FRAMEBUFFER,
                    test "x$enable_serframe" = "xyes")


# required programs

if test "x$enable_mmx" = "xyes"; then
	AC_PATH_PROG(NASM, nasm)
	if test "x$NASM" = "x"; then
        	AC_MSG_ERROR([*** 'nasm' missing, please install or fix your 
\$PATH ***
Note: you can disable mmx by using the "--disable-mmx" parameter. In this
case nasm will not be required.])
	fi

        NASM_FLAGS="-f elf -O1"
        AC_SUBST(NASM)
        AC_SUBST(NASM_FLAGS)
fi


AC_ARG_VAR([FRBINCACHE],
           [The size of the cache of the image source module in MB])
if test "x$FRBINCACHE" != "x"; then
AC_DEFINE_UNQUOTED([FRBINMODULE_CACHE_SIZE], $FRBINCACHE, [Size of the cache the frbinmodule uses (in MB)])
fi;

if test "x$use_ffmpeg" = "xyes"; then
 FFMPEG_CONFIGURE_FLAGS="--prefix=$prefix --disable-ffserver --disable-ffplay --enable-shared --enable-memalign-hack" 
#--disable-risky"

 echo Preparing ffmpeg configure call...
 
 # If building with builddir != srcdir, ffmpegs configure wants to be
 # called with an absolute path.
 # Also, we have to do some workarounds (doc dir is missing for example).
 if test "x${srcdir}" != x.; then
   pwd
   (mkdir contrib && mkdir contrib/ffmpeg) || true
    
   if ! test -e contrib/ffmpeg/doc
   then
      mkdir contrib/ffmpeg/doc
      echo "all:" > contrib/ffmpeg/doc/Makefile
   fi

   TMPDIR=`pwd` && cd ${srcdir} && absolute_srcdir=`pwd` && cd $TMPDIR

   FFMPEG_CONFIG_DIR="${absolute_srcdir}/contrib/ffmpeg"

   AC_SUBST(FFMPEG_DIR,"${absolute_srcdir}/contrib/ffmpeg") #TODO
 else
   FFMPEG_CONFIG_DIR="."
   AC_SUBST(FFMPEG_DIR,"../../../contrib/ffmpeg") #TODO
 fi

 # get absolute path of builddir
 abs_builddir=`pwd`

 AC_SUBST(FFMPEG_LDFLAGS,"${abs_builddir}/contrib/ffmpeg/libavformat/libavformat.a ${abs_builddir}/contrib/ffmpeg/libavcodec/libavcodec.a ${abs_builddir}/contrib/ffmpeg/libavutil/libavutil.a -lz")

 AC_SUBST(FFMPEG_CFLAGS,"-I${FFMPEG_DIR} -D__STDC_CONSTANT_MACROS")

 echo Calling ffmpeg configure with flags:
 echo "${FFMPEG_CONFIG_DIR}/configure $FFMPEG_CONFIGURE_FLAGS"
 cd contrib/ffmpeg/ || exit 1
 ${FFMPEG_CONFIG_DIR}/configure $FFMPEG_CONFIGURE_FLAGS
 cd ../..
fi

# set gphx_module_lib_dir and gphx_type_lib_dir
test "x$prefix" = xNONE && prefix=$ac_default_prefix
AC_SUBST(gphx_module_lib_dir, '$(prefix)/lib/gephex-0.4/modules')
AC_SUBST(gphx_type_lib_dir, '$(prefix)/lib/gephex-0.4/types')

# check for xmlto, docbook2x and docbook xslt (in that order)

AC_MSG_CHECKING([command to convert from docbook to man])

docbooktoxman=""
if test -e `which xmlto`
then
  docbooktoxman="`which xmlto` man"
else
  GUESS_DOCBOOK2MAN="`which docbook2x-man` `which docbook2man`"

  for cmd in $GUESS_DOCBOOK2MAN
  do
    if test -e $cmd
    then
      docbooktoxman=$cmd
      break
    fi
  done
fi

if test "x$docbooktoxman" = "x"; then
  AC_MSG_RESULT([not found])
else
  AC_MSG_RESULT([assuming $docbooktoxman])
fi

AC_SUBST(docbooktoxman)

AC_MSG_CHECKING([docbook xsl dir])

GUESS_DOCBOOK_XSL_DIRS="/sw/share/xml/xsl/docbook-xsl /usr/share/xml/docbook/stylesheet/nwalsh"

docbook_xsl_dir=""
for dir in $GUESS_DOCBOOK_XSL_DIRS
do
  if test -e $dir/html/docbook.xsl
  then
    docbook_xsl_dir=$dir
    break
  fi
done

if test "x$docbook_xsl_dir" = "x"; then
  AC_MSG_RESULT([not found])
else
  AC_MSG_RESULT([assuming $docbook_xsl_dir])
fi

AC_SUBST(docbook_xsl_dir)

AC_CONFIG_FILES([Makefile
base/Makefile
base/src/Makefile
base/src/TestFramework/Makefile
base/src/interfaces/Makefile
base/src/net/Makefile
base/src/netinterfaces/Makefile
base/src/thread/Makefile
base/src/utils/Makefile
build/Makefile
build/dummy/Makefile
contrib/Makefile
data/Makefile
data/gephex-wrapper
data/gephex.conf.default
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
modules/src/capturemodule/Makefile
modules/src/centermodule/Makefile
modules/src/chromakeymodule/Makefile
modules/src/color2numbermodule/Makefile
modules/src/colorizemodule/Makefile
modules/src/diffmodule/Makefile
modules/src/doepfermodule/Makefile
modules/src/dplmodule/Makefile
modules/src/ffmpegoutmodule/Makefile
modules/src/flashmodule/Makefile
modules/src/flipflopmodule/Makefile
modules/src/font3Dmodule/Makefile
modules/src/fpsmodule/Makefile
modules/src/frbinmodule/Makefile
modules/src/frboutmodule/Makefile
modules/src/funparsemodule/Makefile
modules/src/gradnormmodule/Makefile
modules/src/ifsgenmodule/Makefile
modules/src/ifsmodule/Makefile
modules/src/ifsxfadermodule/Makefile
modules/src/imagebuffermodule/Makefile
modules/src/imagewritermodule/Makefile
modules/src/imgarithmodule/Makefile
modules/src/isingnoizemodule/Makefile
modules/src/joystickmodule/Makefile
modules/src/jumpmodule/Makefile
modules/src/libdshow/Makefile
modules/src/libgrid/Makefile
modules/src/libmidi/Makefile
modules/src/libscale/Makefile
modules/src/libcolorconv/Makefile
modules/src/midiinmodule/Makefile
modules/src/midiccdecmodule/Makefile
modules/src/midinotedecmodule/Makefile
modules/src/midikeyrangedecmodule/Makefile
modules/src/midiprgchdecmodule/Makefile
modules/src/midipitchwdecmodule/Makefile
modules/src/mirrormodule/Makefile
modules/src/netcontrolmodule/Makefile
modules/src/noisemodule/Makefile
modules/src/numarithmodule/Makefile
modules/src/number2colormodule/Makefile
modules/src/numbermodule/Makefile
modules/src/numenvmodule/Makefile
modules/src/numlfomodule/Makefile
modules/src/numposmodule/Makefile
modules/src/numxfadermodule/Makefile
modules/src/oscinmodule/Makefile
modules/src/oscoutmodule/Makefile
modules/src/oscnummodule/Makefile
modules/src/oscmergemodule/Makefile
modules/src/numoscmodule/Makefile
modules/src/overlaymodule/Makefile
modules/src/pixelizemodule/Makefile
modules/src/planemodule/Makefile
modules/src/plasmamodule/Makefile
modules/src/pongmodule/Makefile
modules/src/posnummodule/Makefile
modules/src/rangeconvertmodule/Makefile
modules/src/resultmodule/Makefile
modules/src/rotozoommodule/Makefile
modules/src/sdlfontmodule/Makefile
modules/src/signalgenmodule/Makefile
modules/src/signalplotmodule/Makefile
modules/src/staticcolormodule/Makefile
modules/src/stringtokenizermodule/Makefile
modules/src/timesourcemodule/Makefile
modules/src/tunnelmodule/Makefile
modules/src/twolayermodule/Makefile
modules/src/xfademodule/Makefile
modules/src/y4minmodule/Makefile
modules/src/yuv4mpeg2module/Makefile
effectvmodules/Makefile
effectvmodules/src/Makefile
effectvmodules/src/libeffectv/Makefile
effectvmodules/src/effectvedgemodule/Makefile
effectvmodules/src/effectvagingmodule/Makefile
effectvmodules/src/effectvburnmodule/Makefile
effectvmodules/src/effectvcyclemodule/Makefile
effectvmodules/src/effectvdotmodule/Makefile
effectvmodules/src/effectvfiremodule/Makefile
effectvmodules/src/effectvlensmodule/Makefile
effectvmodules/src/effectvlifemodule/Makefile
effectvmodules/src/effectvpuzzlemodule/Makefile
effectvmodules/src/effectvquarkmodule/Makefile
effectvmodules/src/effectvsparkmodule/Makefile
effectvmodules/src/effectv1dmodule/Makefile
effectvmodules/src/effectvspiralmodule/Makefile
effectvmodules/src/effectvbaltanmodule/Makefile
effectvmodules/src/effectvdizzymodule/Makefile
effectvmodules/src/effectvrndmmodule/Makefile
effectvmodules/src/effectvstreakmodule/Makefile
effectvmodules/src/effectvblurzoommodule/Makefile
effectvmodules/src/effectvmatrixmodule/Makefile
effectvmodules/src/effectvpupmodule/Makefile
effectvmodules/src/effectvscrollmodule/Makefile
effectvmodules/src/effectvtransformmodule/Makefile
effectvmodules/src/effectvchameleonmodule/Makefile
effectvmodules/src/effectvmosaicmodule/Makefile
effectvmodules/src/effectvrdsmodule/Makefile
effectvmodules/src/effectvshagadelicmodule/Makefile
effectvmodules/src/effectvwarholmodule/Makefile
effectvmodules/src/effectvdicemodule/Makefile
effectvmodules/src/effectvnervousmodule/Makefile
effectvmodules/src/effectvrevmodule/Makefile
effectvmodules/src/effectvsimuramodule/Makefile
effectvmodules/src/effectvwarpmodule/Makefile
effectvmodules/src/effectvdiffmodule/Makefile
effectvmodules/src/effectvnoisemodule/Makefile
effectvmodules/src/effectvripplemodule/Makefile
effectvmodules/src/effectvpredatormodule/Makefile
effectvmodules/src/effectvholomodule/Makefile
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
types/src/fonttype/Makefile
types/src/framebuffertype/Makefile
types/src/ifstype/Makefile
types/src/lfotype/Makefile
types/src/miditype/Makefile
types/src/numbertype/Makefile
types/src/osctype/Makefile
types/src/positiontype/Makefile
types/src/rgbtype/Makefile
types/src/stringtype/Makefile
util/Makefile
util/include/Makefile
util/include/compatibility/Makefile
util/src/Makefile
util/src/cpuinfo/Makefile
util/src/joystick_midi_net/Makefile
util/src/libgeo/Makefile
util/src/libjoystick/Makefile
util/src/misc/Makefile
doc/Makefile
doc/images/Makefile
])
AC_OUTPUT



if test "x$have_qt" != "xyes"; then
  AC_MSG_WARN([No QT support found.
*** The GUI (graphical user interface) will not be built!
*** Note: most linux distributions split qt into two packages:
*** one containing only the libraries needed to run binary qt
*** applications and one containing all the headers and tools
*** needed to compile qt applications from source.
*** Obviously, you need *both* packages in that case.
*** If you know you have qt installed, try to run configure 
*** again with the "--with-qt-(lib|bin|inc)dir=<YOUR QT DIRS>" flags.
*** For details see "./configure --help".
*** Also we would appreciate your feedback in that case,
*** to improve our autoconf test for qt.
*** Sorry for the inconvinience.])
fi
