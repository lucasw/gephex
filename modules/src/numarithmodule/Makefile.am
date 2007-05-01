libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

numarithmodule_auto.c: numarithmodule.spec numarithmodule.h
	$(PLUC) c @srcdir@/numarithmodule.spec

numarithmodule.h: numarithmodule.spec
	$(PLUC) h @srcdir@/numarithmodule.spec

lib_LTLIBRARIES = numarithmodule.la

numarithmodule_la_SOURCES = \
        numarithmodule_auto.c \
        numarithmodule.c \
        numarithmodule.h \
        numarithmodule.spec \
        numarithmodule.xpm

numarithmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = numarithmodule.h numarithmodule_auto.c
EXTRA_DIST = numarithmodule.vcproj numarithmodule.dsp numarithmodule.mak numarithmodule.dep
