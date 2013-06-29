EXTRA_DIST = envtype.vcproj envtype.dsp envtype.mak envtype.dep envtype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = envtype.la

envtype_la_SOURCES = envtype.c
envtype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = envtype.h
