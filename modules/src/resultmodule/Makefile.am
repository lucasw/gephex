resultmodule_auto.c: resultmodule.spec resultmodule.h
	python $(top_builddir)/pluc.py c resultmodule.spec

resultmodule.h: resultmodule.spec
	python $(top_builddir)/pluc.py h resultmodule.spec

lib_LTLIBRARIES = resultmodule.la
resultmodule_la_SOURCES = resultmodule_auto.c resultmodule.c resultmodule.h  resultmodule.spec  resultmodule_icon.xpm

resultmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types  -I $(baseincludedir)/engine 

