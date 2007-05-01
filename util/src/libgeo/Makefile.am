EXTRA_DIST = libgeo.vcproj libgeo.dsp libgeo.mak libgeo.dep

noinst_LIBRARIES = libgeo.a

libgeo_a_SOURCES = libgeo.c

noinst_HEADERS = libgeo.h

INCLUDES = 	-I @srcdir@/.. \
		-I @srcdir@/../../include

TESTS=geotest

check_PROGRAMS = geotest

geotest_SOURCES = geotest.c

geotest_LDADD = -lgeo -L@builddir@



