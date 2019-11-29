libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

flashmodule_auto.c: flashmodule.spec flashmodule.h
	$(PLUC) c @srcdir@/flashmodule.spec

flashmodule.h: flashmodule.spec
	$(PLUC) h @srcdir@/flashmodule.spec

lib_LTLIBRARIES = flashmodule.la
flashmodule_la_SOURCES = 	flashmodule_auto.c \
				flashmodule.c \
				flashmodule.h \
				flashmodule.spec \
				flashmodule.xpm

flashmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype 

DISTCLEANFILES = flashmodule.h flashmodule_auto.c
EXTRA_DIST = flashmodule.vcproj flashmodule.dsp flashmodule.mak flashmodule.dep
