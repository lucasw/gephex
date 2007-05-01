EXTRA_DIST = stringtype.vcproj stringtype.dsp stringtype.mak stringtype.dep stringtype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../base/src

lib_LTLIBRARIES = stringtype.la

stringtype_la_SOURCES = stringtype.c
stringtype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = stringtype.h
