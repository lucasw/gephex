EXTRA_DIST = framebuffertype.vcproj framebuffertype.dsp framebuffertype.mak framebuffertype.dep framebuffertype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include


lib_LTLIBRARIES = framebuffertype.la

framebuffertype_la_SOURCES = framebuffertype.c
framebuffertype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = framebuffertype.h
