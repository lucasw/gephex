libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

timesourcemodule_auto.c: timesourcemodule.spec timesourcemodule.h
	$(PLUC) c @srcdir@/timesourcemodule.spec

timesourcemodule.h: timesourcemodule.spec
	$(PLUC) h @srcdir@/timesourcemodule.spec

lib_LTLIBRARIES = timesourcemodule.la

timesourcemodule_la_SOURCES = \
        timesourcemodule_auto.c \
        timesourcemodule.cpp \
        timesourcemodule.h \
        timesourcemodule.spec \
        timesourcemodule.xpm

timesourcemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = timesourcemodule.h timesourcemodule_auto.c

EXTRA_DIST = timesourcemodule.vcproj timesourcemodule.dsp timesourcemodule.mak timesourcemodule.dep
