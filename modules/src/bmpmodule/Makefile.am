bmpmodule_auto.c: bmpmodule.spec bmpmodule.h
	python $(top_builddir)/pluc.py c bmpmodule.spec

bmpmodule.h: bmpmodule.spec
	python $(top_builddir)/pluc.py h bmpmodule.spec

lib_LTLIBRARIES = bmpmodule.la
bmpmodule_la_SOURCES = bmpmodule_auto.c bmpmodule.c bmpmodule.h  bmpmodule.spec bmpmodule.xpm


bmpmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I$(baseincludedir) -I$(baseincludedir)/types -I$(baseincludedir)/engine

