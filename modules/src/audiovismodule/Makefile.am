libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

audiovismodule_auto.c: audiovismodule.spec audiovismodule.h
	$(PLUC) c @srcdir@/audiovismodule.spec

audiovismodule.h: audiovismodule.spec
	$(PLUC) h @srcdir@/audiovismodule.spec

lib_LTLIBRARIES = audiovismodule.la

audiovismodule_la_SOURCES = \
        audiovismodule_auto.c \
        audiovismodule.c \
        audiovismodule.h \
        audiovismodule.spec \
        audiovismodule.xpm

audiovismodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/framebuffertype \
           -I@srcdir@/../../../types/src/audiotype 


DISTCLEANFILES = audiovismodule.h audiovismodule_auto.c
EXTRA_DIST = audiovismodule.vcproj audiovismodule.dsp audiovismodule.mak audiovismodule.dep
