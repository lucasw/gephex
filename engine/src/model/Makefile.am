baseincludedir = @includedir@/gephex
libdir = @libdir@/gephex
includedir = $(baseincludedir)/model

INCLUDES= -I.. -I $(baseincludedir)

noinst_LIBRARIES = libmodel.a

libmodel_a_SOURCES = model.cpp \
                     model.h \
                     graph.cpp \
                     graphnode.cpp \
                     graphconnection.cpp \
                     controllvalueset.cpp \
                     datatree.cpp \
                     datatree.h \
                     datatreetypes.h\
                     persistentinode.cpp \
                     persistentinode.h \
                     standardinode.cpp \
                     standardinode.h \
                     debugpersistor.cpp \
                     debugpersistor.h \
                     idatatreepersistor.h \
                     inode.h \
                     graphfilesystem.cpp \
                     graphserial.cpp \
                     controllvalueset.h \
                     graphconnection.h \
                     graphfilesystem.h \
                     graph.h \
                     graphnode.h \
                     graphserial.h \
                     specmap.h

noinst_HEADERS = model.h

noinst_PROGRAMS = modeltest
modeltest_SOURCES = testmain.cpp datatreetest.cpp datatreetest.h
modeltest_LDFLAGS = -L$(libdir)
modeltest_LDADD = -ltestframework libmodel.a -lutils

