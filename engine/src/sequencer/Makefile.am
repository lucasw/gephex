baseincludedir = @includedir@/gephex
libdir = @libdir@/gephex
includedir = $(baseincludedir)/sequencer

INCLUDES= \
	-I @srcdir@/.. \
	-I @srcdir@/../../../base/src \
	-I @builddir@/../../../base/src  \
	-I @top_srcdir@/util/include \
	-I @top_builddir@/util/include

noinst_LIBRARIES = libsequencer.a

libsequencer_a_SOURCES = \
	sequencer.cpp \
	sequence.cpp \
	sequenceserial.cpp \
	sequencefilesystem.cpp \
	sequencefilesystem.h \
	sequence.h \
	sequenceserial.h

noinst_HEADERS = sequencer.h



