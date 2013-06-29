libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

numenvmodule_auto.c: numenvmodule.spec numenvmodule.h
	$(PLUC) c @srcdir@/numenvmodule.spec

numenvmodule.h: numenvmodule.spec
	$(PLUC) h @srcdir@/numenvmodule.spec 

lib_LTLIBRARIES = numenvmodule.la

numenvmodule_la_SOURCES = 	numenvmodule_auto.c \
				numenvmodule.c \
				numenvmodule.h \
				numenvmodule.spec \
				numenvmodule.xpm

numenvmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/envtype

 

DISTCLEANFILES = numenvmodule.h numenvmodule_auto.c
EXTRA_DIST = numenvmodule.vcproj numenvmodule.dsp numenvmodule.mak numenvmodule.dep
