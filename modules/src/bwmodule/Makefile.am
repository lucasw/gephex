bwmodule_auto.c: bwmodule.spec bwmodule.h
	python $(top_builddir)/pluc.py c bwmodule.spec

bwmodule.h: bwmodule.spec
	python $(top_builddir)/pluc.py h bwmodule.spec

lib_LTLIBRARIES = bwmodule.la
bwmodule_la_SOURCES = bwmodule_auto.c bwmodule.c bwmodule.h bwmodule.spec bwmodule.xpm


bwmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

