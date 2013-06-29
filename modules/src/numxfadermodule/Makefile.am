libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

numxfadermodule_auto.c: numxfadermodule.spec numxfadermodule.h
	$(PLUC) c @srcdir@/numxfadermodule.spec

numxfadermodule.h: numxfadermodule.spec
	$(PLUC) h @srcdir@/numxfadermodule.spec

lib_LTLIBRARIES = numxfadermodule.la

numxfadermodule_la_SOURCES = 	numxfadermodule_auto.c \
				numxfadermodule.c \
				numxfadermodule.h \
				numxfadermodule.spec \
				numxfadermodule.xpm

numxfadermodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype 

 

DISTCLEANFILES = numxfadermodule.h numxfadermodule_auto.c
EXTRA_DIST = numxfadermodule.vcproj numxfadermodule.dsp numxfadermodule.mak numxfadermodule.dep
