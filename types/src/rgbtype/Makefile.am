EXTRA_DIST = rgbtype.dsp rgbtype.mak rgbtype.dep rgbtype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../base/src \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = rgbtype.la

rgbtype_la_SOURCES = rgbtype.c
rgbtype_la_LDFLAGS = -module -avoid-version

include_HEADERS = rgbtype.h




