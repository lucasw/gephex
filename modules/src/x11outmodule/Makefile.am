libdir = @libdir@/gephex/modules

PLUC=python $(top_srcdir)/modules/pluc.py

x11outmodule_auto.c: x11outmodule.spec x11outmodule.h
	$(PLUC) c $(srcdir)/x11outmodule.spec

x11outmodule.h: x11outmodule.spec
	$(PLUC) h $(srcdir)/x11outmodule.spec

lib_LTLIBRARIES = x11outmodule.la

x11outmodule_la_SOURCES = \
	x11outmodule_auto.c \
        x11outmodule.c \
        x11outmodule.h \
        x11outmodule.spec \
        x11outmodule.xpm \
        outputdriver.h \
	ximageoutput.h \
	ximageoutput.c \
	xshmoutput.h \
	xshmoutput.c \
	x11util.h \
	x11util.c

x11outmodule_la_LDFLAGS = -module -avoid-version -no-undefined -L/usr/X11R6/lib
x11outmodule_la_LIBADD = -lX11 -lXext

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/framebuffertype  \
           -I@srcdir@/../../../types/src/stringtype


DISTCLEANFILES = x11outmodule.h x11outmodule_auto.c
