libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py

gradnormmodule_auto.c: gradnormmodule.spec gradnormmodule.h
	$(PLUC) c @srcdir@/gradnormmodule.spec

gradnormmodule.h: gradnormmodule.spec
	$(PLUC) h @srcdir@/gradnormmodule.spec

lib_LTLIBRARIES = gradnormmodule.la

gradnormmodule_la_SOURCES = \
        gradnormmodule_auto.c \
        gradnormmodule.cpp \
        gradnormmodule.h \
        gradnormmodule.spec \
        gradnormmodule.xpm

gradnormmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype 


DISTCLEANFILES = gradnormmodule.h gradnormmodule_auto.c
