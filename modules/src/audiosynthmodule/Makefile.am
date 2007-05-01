libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

audiosynthmodule_auto.c: audiosynthmodule.spec audiosynthmodule.h
	$(PLUC) c @srcdir@/audiosynthmodule.spec

audiosynthmodule.h: audiosynthmodule.spec
	$(PLUC) h @srcdir@/audiosynthmodule.spec

lib_LTLIBRARIES = audiosynthmodule.la

audiosynthmodule_la_SOURCES = \
        audiosynthmodule_auto.c \
        audiosynthmodule.cpp \
        audiosynthmodule.h \
        audiosynthmodule.spec \
	synth.h \
	synth.cpp \
        audiosynthmodule.xpm

audiosynthmodule_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/envtype \
           -I@srcdir@/../../../types/src/lfotype \
           -I@srcdir@/../../../types/src/stringtype 


DISTCLEANFILES = audiosynthmodule.h audiosynthmodule_auto.c
EXTRA_DIST = audiosynthmodule.vcproj audiosynthmodule.dsp audiosynthmodule.mak audiosynthmodule.dep
