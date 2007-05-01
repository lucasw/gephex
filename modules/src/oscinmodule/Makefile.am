libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

oscinmodule_auto.c: oscinmodule.spec oscinmodule.h
	$(PLUC) c @srcdir@/oscinmodule.spec

oscinmodule.h: oscinmodule.spec
	$(PLUC) h @srcdir@/oscinmodule.spec

lib_LTLIBRARIES = oscinmodule.la

oscinmodule_la_SOURCES = \
        oscinmodule_auto.c \
        oscinmodule.cpp \
        oscinmodule.h \
        oscinmodule.spec \
        oscinmodule.xpm

oscinmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/osctype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype 


DISTCLEANFILES = oscinmodule.h oscinmodule_auto.c

#EXTRA_DIST = oscinmodule.vcproj oscinmodule.dsp oscinmodule.mak oscinmodule.dep

