libdir = @libdir@/gephex/modules

PLUC=python @top_srcdir@/modules/pluc.py

addmodule_auto.c: addmodule.spec addmodule.h
	$(PLUC) c @srcdir@/addmodule.spec

addmodule.h: addmodule.spec
	$(PLUC) h @srcdir@/addmodule.spec

lib_LTLIBRARIES = addmodule.la

addmodule_la_SOURCES = \
        addmodule_auto.c \
        addmodule.c \
        addmodule.h \
        addmodule.spec \
        addmodule.xpm

addmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = addmodule.h addmodule_auto.c
