addmodule_auto.c: addmodule.spec addmodule.h
	python $(top_builddir)/pluc.py c addmodule.spec

addmodule.h: addmodule.spec
	python $(top_builddir)/pluc.py h addmodule.spec

lib_LTLIBRARIES = addmodule.la
addmodule_la_SOURCES = addmodule_auto.c addmodule.c addmodule.h addmodule.spec  addmodule_icon.xpm

addmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I$(baseincludedir) -I$(baseincludedir)/types -I$(baseincludedir)/engine