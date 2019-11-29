libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

fpsmodule_auto.c: fpsmodule.spec fpsmodule.h
	$(PLUC) c @srcdir@/fpsmodule.spec

fpsmodule.h: fpsmodule.spec
	$(PLUC) h @srcdir@/fpsmodule.spec

lib_LTLIBRARIES = fpsmodule.la

fpsmodule_la_SOURCES = 	fpsmodule_auto.c \
			fpsmodule.c \
			fpsmodule.h \
			fpsmodule.spec \
			fpsmodule.xpm

fpsmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype 

 

DISTCLEANFILES = fpsmodule.h fpsmodule_auto.c
EXTRA_DIST = fpsmodule.vcproj fpsmodule.dsp fpsmodule.mak fpsmodule.dep
