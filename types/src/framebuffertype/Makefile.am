EXTRA_DIST = framebuffertype.dsp framebuffertype.mak framebuffertype.dep framebuffertype.def

includedir = @includedir@/gephex/types
libdir = @libdir@/gephex/types
INCLUDES  = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include


lib_LTLIBRARIES = framebuffertype.la

framebuffertype_la_SOURCES = framebuffertype.c
framebuffertype_la_LDFLAGS = -module -avoid-version

include_HEADERS = framebuffertype.h


