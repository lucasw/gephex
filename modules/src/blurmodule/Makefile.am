libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

blurmodule_auto.c: blurmodule.spec blurmodule.h
	$(PLUC) c @srcdir@/blurmodule.spec

blurmodule.h: blurmodule.spec
	$(PLUC) h @srcdir@/blurmodule.spec

lib_LTLIBRARIES = blurmodule.la

blurmodule_la_SOURCES = 	blurmodule_auto.c \
				blurmodule.c \
				blurmodule.h \
				blurmodule.spec \
				blurmodule.xpm

blurmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype 

DISTCLEANFILES = blurmodule.h blurmodule_auto.c
EXTRA_DIST = blurmodule.vcproj blurmodule.dsp blurmodule.mak blurmodule.dep
