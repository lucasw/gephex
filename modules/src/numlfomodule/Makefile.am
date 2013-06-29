libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

numlfomodule_auto.c: numlfomodule.spec numlfomodule.h
	$(PLUC) c @srcdir@/numlfomodule.spec

numlfomodule.h: numlfomodule.spec
	$(PLUC) h @srcdir@/numlfomodule.spec 

lib_LTLIBRARIES = numlfomodule.la

numlfomodule_la_SOURCES = 	numlfomodule_auto.c \
				numlfomodule.c \
				numlfomodule.h \
				numlfomodule.spec \
				numlfomodule.xpm

numlfomodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/lfotype

 

DISTCLEANFILES = numlfomodule.h numlfomodule_auto.c
EXTRA_DIST = numlfomodule.vcproj numlfomodule.dsp numlfomodule.mak numlfomodule.dep
