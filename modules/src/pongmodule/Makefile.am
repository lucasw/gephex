libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

pongmodule_auto.c: pongmodule.spec pongmodule.h
	$(PLUC) c @srcdir@/pongmodule.spec

pongmodule.h: pongmodule.spec
	$(PLUC) h @srcdir@/pongmodule.spec

lib_LTLIBRARIES = pongmodule.la

pongmodule_la_SOURCES = \
        pongmodule_auto.c \
        pongmodule.cpp \
        pongmodule.h \
        pongmodule.spec \
        pongmodule.xpm

pongmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/positiontype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = pongmodule.h pongmodule_auto.c

EXTRA_DIST = pongmodule.vcproj pongmodule.dsp pongmodule.mak pongmodule.dep

