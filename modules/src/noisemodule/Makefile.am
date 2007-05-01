libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

noisemodule_auto.c: noisemodule.spec noisemodule.h
	$(PLUC) c @srcdir@/noisemodule.spec

noisemodule.h: noisemodule.spec
	$(PLUC) h @srcdir@/noisemodule.spec

lib_LTLIBRARIES = noisemodule.la

noisemodule_la_SOURCES = \
        noisemodule_auto.c \
        noisemodule.cpp \
        noisemodule.h \
        noisemodule.spec \
        noisemodule.xpm

noisemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../util/src/misc \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = noisemodule.h noisemodule_auto.c

EXTRA_DIST = noisemodule.vcproj noisemodule.dsp noisemodule.mak noisemodule.dep
