numxfadermodule_auto.c: numxfadermodule.spec numxfadermodule.h
	python $(top_builddir)/pluc.py c numxfadermodule.spec

numxfadermodule.h: numxfadermodule.spec
	python $(top_builddir)/pluc.py h numxfadermodule.spec

lib_LTLIBRARIES = numxfadermodule.la
numxfadermodule_la_SOURCES = numxfadermodule_auto.c numxfadermodule.c numxfadermodule.h numxfadermodule.spec numxfadermodule.xpm

numxfadermodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

