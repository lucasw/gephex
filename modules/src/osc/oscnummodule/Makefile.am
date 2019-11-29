libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

oscnummodule_auto.c: oscnummodule.spec oscnummodule.h
	$(PLUC) c @srcdir@/oscnummodule.spec

oscnummodule.h: oscnummodule.spec
	$(PLUC) h @srcdir@/oscnummodule.spec

lib_LTLIBRARIES = oscnummodule.la

oscnummodule_la_SOURCES = \
        oscnummodule_auto.c \
        oscnummodule.cpp \
        oscnummodule.h \
        oscnummodule.spec \
        oscnummodule.xpm

oscnummodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/osctype 

DISTCLEANFILES = oscnummodule.h oscnummodule_auto.c

#EXTRA_DIST = oscnummodule.vcproj oscnummodule.dsp oscnummodule.mak oscnummodule.dep

