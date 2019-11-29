libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

audioenergymodule_auto.c: audioenergymodule.spec audioenergymodule.h
	$(PLUC) c @srcdir@/audioenergymodule.spec

audioenergymodule.h: audioenergymodule.spec
	$(PLUC) h @srcdir@/audioenergymodule.spec

lib_LTLIBRARIES = audioenergymodule.la

audioenergymodule_la_SOURCES = \
        audioenergymodule_auto.c \
        audioenergymodule.cpp \
        audioenergymodule.h \
        audioenergymodule.spec \
        audioenergymodule.xpm \
	fft.hh

EXTRA_DIST = fft.cpp \
             audioenergymodule.vcproj audioenergymodule.dsp audioenergymodule.mak audioenergymodule.dep

audioenergymodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = audioenergymodule.h audioenergymodule_auto.c

