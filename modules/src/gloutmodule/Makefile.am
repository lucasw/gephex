libdir = @libdir@/gephex/modules

PLUC=python @srcdir@/../../pluc.py

gloutmodule_auto.c: gloutmodule.spec gloutmodule.h
	$(PLUC) c @srcdir@/gloutmodule.spec

gloutmodule.h: gloutmodule.spec
	$(PLUC) h @srcdir@/gloutmodule.spec

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

INCLUDES = 	-I @srcdir@/../../../engine/src/engine \
		-I @srcdir@/../../../util/include \
		-I @srcdir@/../../../types/src/numbertype \
		-I @srcdir@/../../../types/src/framebuffertype 

 

DISTCLEANFILES = gloutmodule.h gloutmodule_auto.c
