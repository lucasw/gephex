posnummodule_auto.c: posnummodule.spec posnummodule.h
	python $(top_builddir)/pluc.py c posnummodule.spec

posnummodule.h: posnummodule.spec
	python $(top_builddir)/pluc.py h posnummodule.spec

lib_LTLIBRARIES = posnummodule.la
posnummodule_la_SOURCES = posnummodule_auto.c posnummodule.c posnummodule.h posnummodule.spec posnummodule.xpm


posnummodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types   -I $(baseincludedir)/engine
