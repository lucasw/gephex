libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

audiowavegenmodule_auto.c: audiowavegenmodule.spec audiowavegenmodule.h
	$(PLUC) c @srcdir@/audiowavegenmodule.spec

audiowavegenmodule.h: audiowavegenmodule.spec
	$(PLUC) h @srcdir@/audiowavegenmodule.spec

lib_LTLIBRARIES = audiowavegenmodule.la

audiowavegenmodule_la_SOURCES = \
        audiowavegenmodule_auto.c \
        audiowavegenmodule.c \
        audiowavegenmodule.h \
        audiowavegenmodule.spec \
        audiowavegenmodule.xpm

audiowavegenmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = audiowavegenmodule.h audiowavegenmodule_auto.c
EXTRA_DIST = audiowavegenmodule.vcproj audiowavegenmodule.dsp audiowavegenmodule.mak audiowavegenmodule.dep
