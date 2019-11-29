libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

y4minmodule_auto.c: y4minmodule.spec y4minmodule.h
	$(PLUC) c @srcdir@/y4minmodule.spec

y4minmodule.h: y4minmodule.spec
	$(PLUC) h @srcdir@/y4minmodule.spec

lib_LTLIBRARIES = y4minmodule.la

y4minmodule_la_SOURCES = \
        y4minmodule_auto.c \
        y4minmodule.cpp \
        y4minmodule.h \
        y4minmodule.spec \
        y4minmodule.xpm

y4minmodule_la_DEPENDENCIES = @builddir@/../libcolorconv/libcolorconv.a


y4minmodule_la_LDFLAGS = -module -avoid-version -no-undefined -L@builddir@/../libcolorconv  @builddir@/../libcolorconv/libcolorconv.a

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
	   -I@srcdir@/../../../modules/src/libcolorconv \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = y4minmodule.h y4minmodule_auto.c

EXTRA_DIST = y4minmodule.vcproj y4minmodule.dsp y4minmodule.mak y4minmodule.dep
