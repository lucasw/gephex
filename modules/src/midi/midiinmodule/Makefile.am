libdir = @gphx_module_lib_dir@

PLUC=python @srcdir@/../../pluc.py

midiinmodule_auto.c: midiinmodule.spec midiinmodule.h
	$(PLUC) c @srcdir@/midiinmodule.spec

midiinmodule.h: midiinmodule.spec
	$(PLUC) h @srcdir@/midiinmodule.spec

lib_LTLIBRARIES = midiinmodule.la

if WITH_ASOUNDLIB
ALSALIB_sOURCES = \
        alsamidiindriver.cpp \
	alsamidiindriver.h \
        alsaseqmidiindriver.cpp \
	alsaseqmidiindriver.h
ALSALIB_lDFLAGS = -lasound
endif

if WITH_OSS
OSS_sOURCES = \
	ossmidiindriver.h \
	ossmidiindriver.cpp
endif

if OS_WINDOWS
WIN32_sOURCES = \
	wavemidiindriver.cpp \
	wavemidiindriver.h
endif

if OS_DARWIN
DARWIN_sOURCES = \
	macosxmidiindriver.cpp \
	macosxmidiindriver.h
DARWIN_lDFLAGS = -framework CoreMIDI -framework CoreFoundation
endif

midiinmodule_la_SOURCES = \
	midiinmodule_auto.c \
	midiinmodule.cpp \
	midiinmodule.h \
	midiinmodule.spec \
	midiinmodule.xpm \
	midiindriver.h $(OSS_sOURCES) $(ALSALIB_sOURCES) $(WIN32_sOURCES) $(DARWIN_sOURCES)

midiinmodule_la_LDFLAGS = -module -avoid-version -no-undefined $(DARWIN_lDFLAGS)
midiinmodule_la_LIBADD = $(ALSALIB_lDFLAGS)

INCLUDES = -I @srcdir@/../../../engine/src/engine \
	   -I @srcdir@/../../../util/include \
	   -I @srcdir@/../../../types/src/numbertype \
	   -I @srcdir@/../../../types/src/miditype \
	   -I @srcdir@/../../../types/src/stringtype

DISTCLEANFILES = midiinmodule.h midiinmodule_auto.c
EXTRA_DIST = midiinmodule.vcproj midiinmodule.dsp midiinmodule.mak midiinmodule.dep
