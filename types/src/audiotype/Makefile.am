EXTRA_DIST = audiotype.dsp audiotype.mak audiotype.dep audiotype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = audiotype.la

audiotype_la_SOURCES = audiotype.c
audiotype_la_LDFLAGS = -module -avoid-version

include_HEADERS = audiotype.h




