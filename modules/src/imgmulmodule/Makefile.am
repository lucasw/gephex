imgmulmodule_auto.c: imgmulmodule.spec imgmulmodule.h
	python $(top_builddir)/pluc.py c imgmulmodule.spec

imgmulmodule.h: imgmulmodule.spec
	python $(top_builddir)/pluc.py h imgmulmodule.spec

lib_LTLIBRARIES = imgmulmodule.la
imgmulmodule_la_SOURCES = imgmulmodule_auto.c imgmulmodule.c imgmulmodule.h imgmulmodule.spec imgmulmodule.xpm


imgmulmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types -I $(baseincludedir)/engine

