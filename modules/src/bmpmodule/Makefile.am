libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

bmpmodule_auto.c: bmpmodule.spec bmpmodule.h
	$(PLUC) c @srcdir@/bmpmodule.spec

bmpmodule.h: bmpmodule.spec
	$(PLUC) h @srcdir@/bmpmodule.spec

lib_LTLIBRARIES = bmpmodule.la
bmpmodule_la_SOURCES = 	bmpmodule_auto.c \
			bmpmodule.c \
			bmpmodule.h \
			bmpmodule.spec \
			bmpmodule.xpm


bmpmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype \
		-I @srcdir@/../../../types/src/stringtype 

DISTCLEANFILES = bmpmodule.h bmpmodule_auto.c
