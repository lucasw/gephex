numposmodule_auto.c: numposmodule.spec numposmodule.h
	python $(top_builddir)/pluc.py c numposmodule.spec

numposmodule.h: numposmodule.spec
	python $(top_builddir)/pluc.py h numposmodule.spec 

lib_LTLIBRARIES = numposmodule.la
numposmodule_la_SOURCES = numposmodule_auto.c numposmodule.c numposmodule.h numposmodule.spec numposmodule.xpm


numposmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

