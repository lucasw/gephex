#EXTRA_DIST = osctype.vcproj osctype.dsp osctype.mak osctype.dep osctype.def

includedir = @includedir@/gephex/types
libdir = @gphx_type_lib_dir@
INCLUDES  =  	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include

lib_LTLIBRARIES = osctype.la

osctype_la_SOURCES = osctype.c
osctype_la_LDFLAGS = -module -avoid-version -no-undefined

include_HEADERS = osctype.h




