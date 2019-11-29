libdir = @gphx_module_lib_dir@

PLUC=python @top_srcdir@/modules/pluc.py

audiooutmodule_auto.c: audiooutmodule.spec audiooutmodule.h
	$(PLUC) c @srcdir@/audiooutmodule.spec

audiooutmodule.h: audiooutmodule.spec
	$(PLUC) h @srcdir@/audiooutmodule.spec

lib_LTLIBRARIES = audiooutmodule.la


if WITH_ASOUNDLIB
ALSALIB_sOURCES = \
        alsaoutdriver.cpp \
	alsaoutdriver.h
ALSALIB_lDFLAGS = -lasound
endif

if WITH_OSS
OSS_sOURCES = \
	ossoutdriver.cpp \
	ossoutdriver.h
endif

if OS_DARWIN
MAC_sOURCES = \
	coreaudiooutdriver.cpp \
	coreaudiooutdriver.h \
	../audioinmodule/coreaudioconvert.h \
	../audioinmodule/coreaudioconvert.cpp \
	../audioinmodule/coreaudiohelpers.cpp \
	../audioinmodule/coreaudiohelpers.h

MAC_lDFLAGS = -framework CoreAudio -framework AudioToolBox
endif

if OS_WINDOWS
W32_sOURCES = \
	outbuffer.c \
	outbuffer.h \
	waveoutdriver.cpp \
	waveoutdriver.h
endif

audiooutmodule_la_SOURCES = \
        audiooutmodule_auto.c \
        audiooutmodule.cpp \
        audiooutmodule.h \
	../audioinmodule/a_cvt.cpp \
	../audioinmodule/a_cvt.h \
        audiooutmodule.spec \
        audiooutmodule.xpm \
	audiooutdriver.h $(OSS_sOURCES) $(ALSALIB_sOURCES) $(MAC_sOURCES) $(W32_sOURCES)

audiooutmodule_la_LDFLAGS = -module -avoid-version -no-undefined $(MAC_lDFLAGS)
audiooutmodule_la_LIBADD = $(ALSALIB_lDFLAGS)

INCLUDES = -I@srcdir@/../../../engine/src/engine \
           -I@srcdir@/../../../util/include \
           -I@srcdir@/../../../types/src/audiotype \
           -I@srcdir@/../../../types/src/numbertype \
           -I@srcdir@/../../../types/src/stringtype \
           -I@srcdir@/../audioinmodule 

DISTCLEANFILES = audiooutmodule.h audiooutmodule_auto.c
EXTRA_DIST = audiooutmodule.vcproj audiooutmodule.dsp audiooutmodule.mak audiooutmodule.dep
