libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

stringtokenizermodule_auto.c: stringtokenizermodule.spec stringtokenizermodule.h
	$(PLUC) c @srcdir@/stringtokenizermodule.spec

stringtokenizermodule.h: stringtokenizermodule.spec
	$(PLUC) h @srcdir@/stringtokenizermodule.spec

lib_LTLIBRARIES = stringtokenizermodule.la

stringtokenizermodule_la_SOURCES = \
        stringtokenizermodule_auto.c \
        stringtokenizermodule.cpp \
        stringtokenizermodule.h \
        stringtokenizermodule.spec \
        stringtokenizermodule.xpm

stringtokenizermodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = stringtokenizermodule.h stringtokenizermodule_auto.c
EXTRA_DIST = stringtokenizermodule.vcproj stringtokenizermodule.dsp stringtokenizermodule.mak stringtokenizermodule.dep
