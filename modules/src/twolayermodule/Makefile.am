libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

twolayermodule_auto.c: twolayermodule.spec twolayermodule.h
	$(PLUC) c @srcdir@/twolayermodule.spec

twolayermodule.h: twolayermodule.spec
	$(PLUC) h @srcdir@/twolayermodule.spec

lib_LTLIBRARIES = twolayermodule.la

twolayermodule_la_SOURCES = \
        twolayermodule_auto.c \
        twolayermodule.cpp \
        twolayermodule.h \
        twolayermodule.spec \
        twolayermodule.xpm

twolayermodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype 


DISTCLEANFILES = twolayermodule.h twolayermodule_auto.c
EXTRA_DIST = twolayermodule.vcproj twolayermodule.dsp twolayermodule.mak twolayermodule.dep
