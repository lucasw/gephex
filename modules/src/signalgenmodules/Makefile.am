signalgenmodule_auto.c: signalgenmodule.spec signalgenmodule.h
	python $(top_builddir)/pluc.py c signalgenmodule.spec

signalgenmodule.h: signalgenmodule.spec
	python $(top_builddir)/pluc.py h signalgenmodule.spec

lib_LTLIBRARIES = signalgenmodule.la
signalgenmodule_la_SOURCES = signalgenmodule_auto.c signalgenmodule.c signalgenmodule.h signalgenmodule.spec signalgenmodule.xpm

signalgenmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types  -I $(baseincludedir)/engine

