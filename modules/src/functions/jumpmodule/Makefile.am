jumpmodule_auto.c: jumpmodule.spec jumpmodule.h
	python $(top_builddir)/pluc.py c jumpmodule.spec

jumpmodule.h: jumpmodule.spec
	python $(top_builddir)/pluc.py h jumpmodule.spec

lib_LTLIBRARIES = jumpmodule.la
jumpmodule_la_SOURCES = jumpmodule_auto.c jumpmodule.c jumpmodule.h jumpmodule.spec jumpmodule.xpm


jumpmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

