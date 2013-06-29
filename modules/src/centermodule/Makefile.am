libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

centermodule_auto.c: centermodule.spec centermodule.h
	$(PLUC) c @srcdir@/centermodule.spec

centermodule.h: centermodule.spec
	$(PLUC) h @srcdir@/centermodule.spec

lib_LTLIBRARIES = centermodule.la

centermodule_la_SOURCES = \
        centermodule_auto.c \
        centermodule.c \
        centermodule.h \
        centermodule.spec \
        centermodule.xpm

centermodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/positiontype \
           -I@srcdir@/../../../types/src/framebuffertype 


DISTCLEANFILES = centermodule.h centermodule_auto.c
EXTRA_DIST = centermodule.vcproj centermodule.dsp centermodule.mak centermodule.dep
