starfield_auto.c: starfield.spec starfield.h
	python $(top_builddir)/pluc.py c starfield.spec

starfield.h: starfield.spec
	python $(top_builddir)/pluc.py h starfield.spec

lib_LTLIBRARIES = libstarfield.la
libstarfield_la_SOURCES = starfield_auto.c starfield.c starfield.h starfield.spec starfield.xpm

libstarfield_la_LDFLAGS = -module -avoid-version

INCLUDES = -I$(baseincludedir) -I$(baseincludedir)/types -I$(baseincludedir)/engine
