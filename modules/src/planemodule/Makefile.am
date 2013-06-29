libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

planemodule_auto.c: planemodule.spec planemodule.h
	$(PLUC) c @srcdir@/planemodule.spec

planemodule.h: planemodule.spec
	$(PLUC) h @srcdir@/planemodule.spec

lib_LTLIBRARIES = planemodule.la

planemodule_la_SOURCES = \
        planemodule_auto.c \
        planemodule.c \
        planemodule.h \
        planemodule.spec \
        planemodule.xpm

planemodule_la_LDFLAGS = -module -avoid-version -no-undefined

planemodule_la_LIBADD = -lgrid -L@builddir@/../libgrid

planemodule_la_DEPENDENCIES = @builddir@/../libgrid/libgrid.a

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/positiontype 


DISTCLEANFILES = planemodule.h planemodule_auto.c
EXTRA_DIST = planemodule.vcproj planemodule.dsp planemodule.mak planemodule.dep
