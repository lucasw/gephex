EXTRA_DIST = envtype.dsp envtype.mak envtype.dep envtype.def

includedir = @includedir@/gephex/types
libdir = @libdir@/gephex/types
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = envtype.la

envtype_la_SOURCES = envtype.c
envtype_la_LDFLAGS = -module -avoid-version

include_HEADERS = envtype.h




