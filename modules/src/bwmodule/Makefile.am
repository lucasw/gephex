libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

bwmodule_auto.c: bwmodule.spec bwmodule.h
	$(PLUC) c @srcdir@/bwmodule.spec

bwmodule.h: bwmodule.spec
	$(PLUC) h @srcdir@/bwmodule.spec

lib_LTLIBRARIES = bwmodule.la

bwmodule_la_SOURCES = \
        bwmodule_auto.c \
        bwmodule.c \
        bwmodule.h \
        bwmodule.spec \
        bwmodule.xpm

bwmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype 


DISTCLEANFILES = bwmodule.h bwmodule_auto.c
EXTRA_DIST = bwmodule.vcproj bwmodule.dsp bwmodule.mak bwmodule.dep
