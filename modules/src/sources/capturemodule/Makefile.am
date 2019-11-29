libdir = @gphx_module_lib_dir@

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
	v4l2capturedriver.cpp \
	v4l2capturedriver.h \
	v4l1.h \
	v4l1.cpp \
	videodev.h \
	videodev2.h

capturemodule_la_LDFLAGS = -module -avoid-version -no-undefined -lscale -lcolorconv
capturemodule_la_LIBADD= -L@builddir@/../libscale -L@builddir@/../libcolorconv

capturemodule_la_DEPENDENCIES = @builddir@/../libscale/libscale.a \
			       @builddir@/../libcolorconv/libcolorconv.a

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I@srcdir@/../libscale \
	   -I@srcdir@/../libcolorconv	


DISTCLEANFILES = capturemodule.h capturemodule_auto.c

EXTRA_DIST = capturemodule.vcproj capturemodule.dsp capturemodule.mak capturemodule.dep dshowcapturedriver.cpp dshowcapturedriver.h
