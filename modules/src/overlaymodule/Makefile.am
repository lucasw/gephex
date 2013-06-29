libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

overlaymodule_auto.c: overlaymodule.spec overlaymodule.h
	$(PLUC) c @srcdir@/overlaymodule.spec

overlaymodule.h: overlaymodule.spec
	$(PLUC) h @srcdir@/overlaymodule.spec

lib_LTLIBRARIES = overlaymodule.la

overlaymodule_la_SOURCES = \
        overlaymodule_auto.c \
        overlaymodule.cpp \
        overlaymodule.h \
        overlaymodule.spec \
        overlaymodule.xpm

overlaymodule_la_LDFLAGS = -module -avoid-version -no-undefined
overlaymodule_la_LIBADD = -lstdc++

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = overlaymodule.h overlaymodule_auto.c
EXTRA_DIST = overlaymodule.vcproj overlaymodule.dsp overlaymodule.mak overlaymodule.dep
