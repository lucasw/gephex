INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

v4lmodule_auto.c: v4lmodule.spec v4lmodule.h
	python $(top_builddir)/pluc.py c v4lmodule.spec

v4lmodule.h: v4lmodule.spec
	python $(top_builddir)/pluc.py h v4lmodule.spec

lib_LTLIBRARIES = v4lmodule.la
v4lmodule_la_SOURCES = v4lmodule_auto.c v4lmodule.cpp v4lmodule.h v4l.h iframegrabber.h v4l.cpp videodefostr.cpp videodefostr.h v4lmodule.spec v4lmodule.xpm

v4lmodule_la_LDFLAGS = -module -avoid-version



