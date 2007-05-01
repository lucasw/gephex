libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

audiospecmodule_auto.c: audiospecmodule.spec audiospecmodule.h
	$(PLUC) c @srcdir@/audiospecmodule.spec

audiospecmodule.h: audiospecmodule.spec
	$(PLUC) h @srcdir@/audiospecmodule.spec

lib_LTLIBRARIES = audiospecmodule.la

audiospecmodule_la_SOURCES = \
        audiospecmodule_auto.c \
        audiospecmodule.cpp \
	fft.hh \
        audiospecmodule.h \
        audiospecmodule.spec \
        audiospecmodule.xpm

EXTRA_DIST = fft.cpp \
	audiospecmodule.vcproj audiospecmodule.dsp audiospecmodule.mak audiospecmodule.dep

audiospecmodule_la_LDFLAGS = -module -avoid-version -no-undefined
audiospecmodule_la_LIBADD = -lstdc++

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = audiospecmodule.h audiospecmodule_auto.c

