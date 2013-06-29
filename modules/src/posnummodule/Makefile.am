libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

posnummodule_auto.c: posnummodule.spec posnummodule.h
	$(PLUC) c @srcdir@/posnummodule.spec

posnummodule.h: posnummodule.spec
	$(PLUC) h @srcdir@/posnummodule.spec

lib_LTLIBRARIES = posnummodule.la

posnummodule_la_SOURCES = 	posnummodule_auto.c \
				posnummodule.c \
				posnummodule.h \
				posnummodule.spec \
				posnummodule.xpm

posnummodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/positiontype 

DISTCLEANFILES = posnummodule.h posnummodule_auto.c
EXTRA_DIST = posnummodule.vcproj posnummodule.dsp posnummodule.mak posnummodule.dep
