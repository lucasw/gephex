libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

dplmodule_auto.c: dplmodule.spec dplmodule.h
	$(PLUC) c @srcdir@/dplmodule.spec

dplmodule.h: dplmodule.spec
	$(PLUC) h @srcdir@/dplmodule.spec

lib_LTLIBRARIES = dplmodule.la

dplmodule_la_SOURCES = \
        dplmodule_auto.c \
        dplmodule.c \
        dplmodule.h \
        dplmodule.spec \
        dplmodule.xpm

dplmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = dplmodule.h dplmodule_auto.c
EXTRA_DIST = dplmodule.vcproj dplmodule.dsp dplmodule.mak dplmodule.dep
