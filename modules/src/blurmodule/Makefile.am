blurmodule_auto.c: blurmodule.spec blurmodule.h
	python $(top_builddir)/pluc.py c blurmodule.spec

blurmodule.h: blurmodule.spec
	python $(top_builddir)/pluc.py h blurmodule.spec

lib_LTLIBRARIES = blurmodule.la
blurmodule_la_SOURCES = blurmodule_auto.c blurmodule.c blurmodule.h blurmodule.spec blurmodule.xpm


blurmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I$(baseincludedir) -I$(baseincludedir)/types -I$(baseincludedir)/engine

