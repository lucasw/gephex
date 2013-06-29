EXTRA_DIST = positiontype.vcproj positiontype.dsp positiontype.mak positiontype.dep \
	positiontype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = positiontype.la

positiontype_la_SOURCES = positiontype.c
positiontype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = positiontype.h
