rotozoommodule_auto.c: rotozoommodule.spec rotozoommodule.h
	python $(top_builddir)/pluc.py c rotozoommodule.spec

rotozoommodule.h: rotozoommodule.spec
	python $(top_builddir)/pluc.py h rotozoommodule.spec

lib_LTLIBRARIES = rotozoommodule.la
rotozoommodule_la_SOURCES = rotozoommodule_auto.c rotozoommodule.c rotozoommodule.h rotozoommodule.spec rotozoommodule.xpm

rotozoommodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types  -I $(baseincludedir)/engine

