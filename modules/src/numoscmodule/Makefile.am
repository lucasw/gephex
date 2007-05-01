libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

numoscmodule_auto.c: numoscmodule.spec numoscmodule.h
	$(PLUC) c @srcdir@/numoscmodule.spec

numoscmodule.h: numoscmodule.spec
	$(PLUC) h @srcdir@/numoscmodule.spec

lib_LTLIBRARIES = numoscmodule.la

numoscmodule_la_SOURCES = \
        numoscmodule_auto.c \
        numoscmodule.cpp \
        numoscmodule.h \
        numoscmodule.spec \
        numoscmodule.xpm

numoscmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/osctype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype 


DISTCLEANFILES = numoscmodule.h numoscmodule_auto.c

#EXTRA_DIST = numoscmodule.vcproj numoscmodule.dsp numoscmodule.mak numoscmodule.dep

