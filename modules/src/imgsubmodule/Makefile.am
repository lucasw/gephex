imgsubmodule_auto.c: imgsubmodule.spec imgsubmodule.h
	python $(top_builddir)/pluc.py c imgsubmodule.spec

imgsubmodule.h: imgsubmodule.spec
	python $(top_builddir)/pluc.py h imgsubmodule.spec

lib_LTLIBRARIES = imgsubmodule.la
imgsubmodule_la_SOURCES = imgsubmodule_auto.c imgsubmodule.c imgsubmodule.h imgsubmodule.spec imgsubmodule.xpm

imgsubmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

