libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

starfield_auto.c: starfield.spec starfield.h
	$(PLUC) c @srcdir@/starfield.spec

starfield.h: starfield.spec
	$(PLUC) h @srcdir@/starfield.spec

lib_LTLIBRARIES = libstarfield.la

libstarfield_la_SOURCES = 	starfield_auto.c \
				starfield.c \
				starfield.h \
				starfield.spec \
				starfield.xpm

libstarfield_la_LDFLAGS = -module -avoid-version

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/rgbtype \
		-I @srcdir@/../../../types/src/framebuffertype 

 

DISTCLEANFILES = starfield.h starfield_auto.c
