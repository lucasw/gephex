gloutmodule_auto.c: gloutmodule.spec gloutmodule.h
	python $(top_builddir)/pluc.py c gloutmodule.spec

gloutmodule.h: gloutmodule.spec
	python $(top_builddir)/pluc.py h gloutmodule.spec

lib_LTLIBRARIES = gloutmodule.la
gloutmodule_la_SOURCES = \
		gloutmodule_auto.c \
		gloutmodule.c \
		gloutmodule.h \
		gloutmodule.spec \
		glmonitor.xpm \
		glxutil.c \
		glutil.h

gloutmodule_la_LIBADD = -lGL

gloutmodule_la_LDFLAGS = -module -avoid-version

INCLUDES = -I $(baseincludedir) -I $(baseincludedir)/types  -I $(baseincludedir)/engine

