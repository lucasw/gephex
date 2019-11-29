libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

mirrormodule_auto.c: mirrormodule.spec mirrormodule.h
	$(PLUC) c @srcdir@/mirrormodule.spec

mirrormodule.h: mirrormodule.spec
	$(PLUC) h @srcdir@/mirrormodule.spec

lib_LTLIBRARIES = mirrormodule.la

mirrormodule_la_SOURCES = \
        mirrormodule_auto.c \
        mirrormodule.c \
        mirrormodule.h \
        mirrormodule.spec \
        mirrormodule.xpm

mirrormodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = mirrormodule.h mirrormodule_auto.c

#EXTRA_DIST = mirrormodule.dsp mirrormodule.mak mirrormodule.dep

