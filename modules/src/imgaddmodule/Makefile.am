imgaddmodule_auto.c: imgaddmodule.spec imgaddmodule.h
	python $(top_builddir)/pluc.py c imgaddmodule.spec

imgaddmodule.h: imgaddmodule.spec
	python $(top_builddir)/pluc.py h imgaddmodule.spec

lib_LTLIBRARIES = imgaddmodule.la
imgaddmodule_la_SOURCES = imgaddmodule_auto.c imgaddmodule.c imgaddmodule.h imgaddmodule.spec imgaddmodule.xpm

imgaddmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types  -I $(baseincludedir)/engine

