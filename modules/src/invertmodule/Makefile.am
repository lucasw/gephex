invertmodule_auto.c: invertmodule.spec invertmodule.h
	python $(top_builddir)/pluc.py c invertmodule.spec

invertmodule.h: invertmodule.spec
	python $(top_builddir)/pluc.py h invertmodule.spec

lib_LTLIBRARIES = invertmodule.la
invertmodule_la_SOURCES = invertmodule_auto.c invertmodule.c invertmodule.h invertmodule.spec invertmodule.xpm

invertmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine 
