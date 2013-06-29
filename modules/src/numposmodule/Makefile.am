libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

numposmodule_auto.c: numposmodule.spec numposmodule.h
	$(PLUC) c @srcdir@/numposmodule.spec

numposmodule.h: numposmodule.spec
	$(PLUC) h @srcdir@/numposmodule.spec 

lib_LTLIBRARIES = numposmodule.la

numposmodule_la_SOURCES = 	numposmodule_auto.c \
				numposmodule.c \
				numposmodule.h \
				numposmodule.spec \
				numposmodule.xpm

numposmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/positiontype

 

DISTCLEANFILES = numposmodule.h numposmodule_auto.c
EXTRA_DIST = numposmodule.vcproj numposmodule.dsp numposmodule.mak numposmodule.dep
