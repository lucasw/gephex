libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

color2numbermodule_auto.c: color2numbermodule.spec color2numbermodule.h
	$(PLUC) c @srcdir@/color2numbermodule.spec

color2numbermodule.h: color2numbermodule.spec
	$(PLUC) h @srcdir@/color2numbermodule.spec

lib_LTLIBRARIES = color2numbermodule.la

color2numbermodule_la_SOURCES = \
        color2numbermodule_auto.c \
        color2numbermodule.c \
        color2numbermodule.h \
        color2numbermodule.spec \
        color2numbermodule.xpm

color2numbermodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/rgbtype 


DISTCLEANFILES = color2numbermodule.h color2numbermodule_auto.c
EXTRA_DIST = color2numbermodule.vcproj color2numbermodule.dsp color2numbermodule.mak color2numbermodule.dep
