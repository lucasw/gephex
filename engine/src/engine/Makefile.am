baseincludedir = @includedir@/gephex
includedir = $(baseincludedir)/engine
libdir = @libdir@/gephex

include_HEADERS = dllmodule.h dlltype.h dllutils.h

INCLUDES= \
		-I.. \
		-I$(baseincludedir)

bin_PROGRAMS = engine

engine_SOURCES = \
		main.cpp \
		scheduler.cpp \
		netlogger.cpp \
		netlogger.h \
		scheduler.h

engine_LDADD = \
		-ldllloader \
		-lsequencer \
		-lmodel \
		-lrenderer \
		-lnetwork \
		-lnetinterfaces \
		-lutils \
		-ldl

engine_LDFLAGS = \
		-L../dllloader \
		-L../sequencer \
		-L../model \
		-L../renderer \
		-L$(libdir) \
		-L/sw/lib

noinst_PROGRAMS =  enginetest

enginetest_SOURCES = 	testmain.cpp \
			schedulertest.cpp \
			scheduler.cpp \
			schedulertest.h

enginetest_LDFLAGS = -L$(libdir)
enginetest_LDADD = -ltestframework -lutils



