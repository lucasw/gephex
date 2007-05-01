libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

signalplotmodule_auto.c: signalplotmodule.spec signalplotmodule.h
	$(PLUC) c @srcdir@/signalplotmodule.spec

signalplotmodule.h: signalplotmodule.spec
	$(PLUC) h @srcdir@/signalplotmodule.spec

lib_LTLIBRARIES = signalplotmodule.la

signalplotmodule_la_SOURCES = \
        signalplotmodule_auto.c \
        signalplotmodule.c \
        signalplotmodule.h \
        signalplotmodule.spec \
        signalplotmodule.xpm

signalplotmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = signalplotmodule.h signalplotmodule_auto.c

EXTRA_DIST = signalplotmodule.vcproj signalplotmodule.dsp signalplotmodule.mak signalplotmodule.dep

