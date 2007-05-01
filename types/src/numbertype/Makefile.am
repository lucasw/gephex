EXTRA_DIST = numbertype.vcproj numbertype.dsp numbertype.mak numbertype.dep numbertype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  = -I @srcdir@/../../../engine/src/engine \
	    -I @srcdir@/../../../util/include

lib_LTLIBRARIES = numbertype.la

numbertype_la_SOURCES = numbertype.c
numbertype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = numbertype.h
