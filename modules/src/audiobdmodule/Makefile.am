libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

audiobdmodule_auto.c: audiobdmodule.spec audiobdmodule.h
	$(PLUC) c @srcdir@/audiobdmodule.spec

audiobdmodule.h: audiobdmodule.spec
	$(PLUC) h @srcdir@/audiobdmodule.spec

lib_LTLIBRARIES = audiobdmodule.la

audiobdmodule_la_SOURCES = \
        audiobdmodule_auto.c \
        audiobdmodule.c \
        audiobdmodule.h \
        audiobdmodule.spec \
        audiobdmodule.xpm

audiobdmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype 


DISTCLEANFILES = audiobdmodule.h audiobdmodule_auto.c
EXTRA_DIST = audiobdmodule.vcproj audiobdmodule.dsp audiobdmodule.mak audiobdmodule.dep
