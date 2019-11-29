libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

audioaddmodule_auto.c: audioaddmodule.spec audioaddmodule.h
	$(PLUC) c @srcdir@/audioaddmodule.spec

audioaddmodule.h: audioaddmodule.spec
	$(PLUC) h @srcdir@/audioaddmodule.spec

lib_LTLIBRARIES = audioaddmodule.la

audioaddmodule_la_SOURCES = \
        audioaddmodule_auto.c \
        audioaddmodule.c \
        audioaddmodule.h \
        audioaddmodule.spec \
        audioaddmodule.xpm

audioaddmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype 


DISTCLEANFILES = audioaddmodule.h audioaddmodule_auto.c
EXTRA_DIST = audioaddmodule.vcproj audioaddmodule.dsp audioaddmodule.mak audioaddmodule.dep
