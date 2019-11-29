libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

oscoutmodule_auto.c: oscoutmodule.spec oscoutmodule.h
	$(PLUC) c @srcdir@/oscoutmodule.spec

oscoutmodule.h: oscoutmodule.spec
	$(PLUC) h @srcdir@/oscoutmodule.spec

lib_LTLIBRARIES = oscoutmodule.la

oscoutmodule_la_SOURCES = \
        oscoutmodule_auto.c \
        oscoutmodule.cpp \
        oscoutmodule.h \
        oscoutmodule.spec \
        oscoutmodule.xpm

oscoutmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
	   -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/osctype 


DISTCLEANFILES = oscoutmodule.h oscoutmodule_auto.c

#EXTRA_DIST = oscoutmodule.vcproj oscoutmodule.dsp oscoutmodule.mak oscoutmodule.dep

