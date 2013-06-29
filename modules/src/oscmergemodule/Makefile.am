libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

oscmergemodule_auto.c: oscmergemodule.spec oscmergemodule.h
	$(PLUC) c @srcdir@/oscmergemodule.spec

oscmergemodule.h: oscmergemodule.spec
	$(PLUC) h @srcdir@/oscmergemodule.spec

lib_LTLIBRARIES = oscmergemodule.la

oscmergemodule_la_SOURCES = \
        oscmergemodule_auto.c \
        oscmergemodule.cpp \
        oscmergemodule.h \
        oscmergemodule.spec \
        oscmergemodule.xpm

oscmergemodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/osctype 


DISTCLEANFILES = oscmergemodule.h oscmergemodule_auto.c

#EXTRA_DIST = oscmergemodule.vcproj oscmergemodule.dsp oscmergemodule.mak oscmergemodule.dep

