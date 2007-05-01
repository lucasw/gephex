libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

y4moutputmodule_auto.c: y4moutputmodule.spec y4moutputmodule.h
	$(PLUC) c @srcdir@/y4moutputmodule.spec

y4moutputmodule.h: y4moutputmodule.spec
	$(PLUC) h @srcdir@/y4moutputmodule.spec

lib_LTLIBRARIES = y4moutputmodule.la

y4moutputmodule_la_SOURCES = \
        y4moutputmodule_auto.c \
        y4moutputmodule.cpp \
        y4moutputmodule.h \
        y4moutputmodule.spec \
        y4moutputmodule.xpm

y4moutputmodule_la_DEPENDENCIES = @builddir@/../libscale/libscale.a \
			       @builddir@/../libcolorconv/libcolorconv.a


y4moutputmodule_la_LDFLAGS = -module -avoid-version -no-undefined -L@builddir@/../libscale -L@builddir@/../libcolorconv  @builddir@/../libcolorconv/libcolorconv.a @builddir@/../libscale/libscale.a

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype \
	   -I@srcdir@/../../../modules/src/libcolorconv \
	   -I@srcdir@/../../../modules/src/libscale

DISTCLEANFILES = y4moutputmodule.h y4moutputmodule_auto.c

EXTRA_DIST = y4moutputmodule.vcproj y4moutputmodule.dsp y4moutputmodule.mak y4moutputmodule.dep
