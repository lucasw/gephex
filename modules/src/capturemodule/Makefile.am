libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py

capturemodule_auto.c: capturemodule.spec capturemodule.h
	$(PLUC) c @srcdir@/capturemodule.spec

capturemodule.h: capturemodule.spec
	$(PLUC) h @srcdir@/capturemodule.spec

lib_LTLIBRARIES = capturemodule.la

capturemodule_la_SOURCES = \
        capturemodule_auto.c \
        capturemodule.cpp \
        capturemodule.h \
        capturemodule.spec \
        capturemodule.xpm \
	capturedriver.h \
	v4lcapturedriver.cpp \
	v4lcapturedriver.h \
	v4l1.h \
	v4l1.cpp \
	colorconv.h \
	colorconv.cpp \
	videodev.h

capturemodule_la_LDFLAGS = -module -avoid-version -no-undefined -lscale
capturemodule_la_LIBADD= -L@builddir@/../libscale

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I@srcdir@/../libscale	


DISTCLEANFILES = capturemodule.h capturemodule_auto.c

EXTRA_DIST = capturemodule.dsp capturemodule.mak capturemodule.dep dshowcapturedriver.cpp dshowcapturedriver.h
