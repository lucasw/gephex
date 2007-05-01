EXTRA_DIST = model.vcproj model.dsp model.mak model.dep

baseincludedir = @includedir@/gephex
libdir = @libdir@/gephex
includedir = $(baseincludedir)/model

INCLUDES= \
	-I @srcdir@/.. \
	-I @srcdir@/../../../base/src \
	-I @builddir@/../../../base/src \
	-I @top_srcdir@/util/include \
	-I @top_builddir@/util/include


noinst_LIBRARIES = libmodel.a

libmodel_a_SOURCES = \
	model.cpp \
        model.h \
        graph.cpp \
        graphnode.cpp \
        graphconnection.cpp \
        controlvalueset.cpp \
        graphfilesystem.cpp \
        graphserial.cpp \
	graphparser.cpp \
        controlvalueset.h \
        graphconnection.h \
        graphfilesystem.h \
        graph.h \
        graphnode.h \
        graphserial.h \
        specmap.h \
	graphparser.h

noinst_HEADERS = model.h

TESTS=modeltest

check_PROGRAMS = modeltest
modeltest_SOURCES = \
	testmain.cpp \
	graphparsertest.cpp \
	graphparsertest.h

modeltest_LDFLAGS = \
	-L$(libdir) \
	-L../../../base/src/TestFramework \
	-L../../../base/src/utils

modeltest_LDADD = -ltestframework libmodel.a -lutils

