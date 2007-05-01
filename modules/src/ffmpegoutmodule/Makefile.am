libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

ffmpegoutmodule_auto.c: ffmpegoutmodule.spec ffmpegoutmodule.h
	$(PLUC) c @srcdir@/ffmpegoutmodule.spec

ffmpegoutmodule.h: ffmpegoutmodule.spec
	$(PLUC) h @srcdir@/ffmpegoutmodule.spec

lib_LTLIBRARIES = ffmpegoutmodule.la

ffmpegoutmodule_la_SOURCES = \
        ffmpegoutmodule_auto.c \
        ffmpegoutmodule.cpp \
        ffmpegoutmodule.h \
        ffmpegoutmodule.spec \
        ffmpegoutmodule.xpm \
	ffmpegwriter.cpp \
	ffmpegwriter.h

ffmpegoutmodule_la_DEPENDENCIES = @builddir@/../libscale/libscale.a 


ffmpegoutmodule_la_LDFLAGS = -module -avoid-version -no-undefined @FFMPEG_LDFLAGS@ -L@builddir@/../libscale

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I@srcdir@/../../../modules/src/libscale \
	   @FFMPEG_CFLAGS@


DISTCLEANFILES = ffmpegoutmodule.h ffmpegoutmodule_auto.c

EXTRA_DIST = ffmpegoutmodule.vcproj ffmpegoutmodule.dsp ffmpegoutmodule.mak ffmpegoutmodule.dep
