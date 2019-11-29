libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

jumpmodule_auto.c: jumpmodule.spec jumpmodule.h
	$(PLUC) c @srcdir@/jumpmodule.spec

jumpmodule.h: jumpmodule.spec
	$(PLUC) h @srcdir@/jumpmodule.spec

lib_LTLIBRARIES = jumpmodule.la

jumpmodule_la_SOURCES = 	jumpmodule_auto.c \
				jumpmodule.c \
				jumpmodule.h \
				jumpmodule.spec \
				jumpmodule.xpm

jumpmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype 

 

DISTCLEANFILES = jumpmodule.h jumpmodule_auto.c
EXTRA_DIST = jumpmodule.vcproj jumpmodule.dsp jumpmodule.mak jumpmodule.dep
