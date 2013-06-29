libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

colorizemodule_auto.c: colorizemodule.spec colorizemodule.h
	$(PLUC) c @srcdir@/colorizemodule.spec

colorizemodule.h: colorizemodule.spec
	$(PLUC) h @srcdir@/colorizemodule.spec

lib_LTLIBRARIES = colorizemodule.la

colorizemodule_la_SOURCES = \
        colorizemodule_auto.c \
        colorizemodule.c \
        colorizemodule.h \
        colorizemodule.spec \
        colorizemodule.xpm

colorizemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/rgbtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = colorizemodule.h colorizemodule_auto.c

#EXTRA_DIST = colorizemodule.dsp colorizemodule.mak colorizemodule.dep

