EXTRA_DIST = engine.vcproj engine.dsp engine.mak engine.dep

includedir = @includedir@/gephex
libdir = @libdir@/gephex

# Defines needed by some source files:

include_HEADERS = \
	dllmodule.h \
	dlltype.h \
	dllutils.h

AM_CPPFLAGS = \
	-I @srcdir@/.. \
	-I @srcdir@/../renderer \
	-I @srcdir@/../model \
	-I @srcdir@/../dllloader \
	-I @srcdir@/../../../base/src \
	-I @builddir@/../../../base/src/interfaces \
	-I @builddir@/../../../base/src \
	-I @srcdir@/../../../base/src/interfaces \
	-I @srcdir@/../../../base/src/netinterfaces \
	-I @builddir@/../../../base/src/netinterfaces \
	-I @srcdir@/../../../base/src/net \
	-I @srcdir@/../../../base/src/utils \
	-I @srcdir@/../../../util/include
	-I @builddir@/../../../util/include

bin_PROGRAMS = gephex-engine-real

gephex_engine_real_SOURCES = \
	main.cpp \
	scheduler.cpp \
	netlogger.cpp \
	netlogger.h \
	scheduler.h \
	controller.h \
	controller.cpp \
        bufferedsender.h \
        bufferedsender.cpp \
	synced_tasks.h

gephex_engine_real_LDADD = \
	-ldllloader \
	-lmodel \
	-lrenderer \
	-lgphxnetwork \
	-lnetinterfaces \
	-lutils $(LIB_DL_FLAGS) $(LIB_SOCKET_FLAGS) $(LIB_POSIX4_FLAGS) $(LIB_EXTRA_FLAGS)\
	-L@builddir@/../dllloader \
	-L@builddir@/../model \
	-L@builddir@/../renderer \
	-L$(libdir) \
	-L@builddir@/../../../base/src/TestFramework \
	-L@builddir@/../../../base/src/utils \
	-L@builddir@/../../../base/src/net \
	-L@builddir@/../../../base/src/netinterfaces \
	-L/sw/lib

gephex_engine_real_DEPENDENCIES = \
	@builddir@/../dllloader/libdllloader.a \
	@builddir@/../model/libmodel.a \
	@builddir@/../renderer/librenderer.a \
	@top_builddir@/base/src/net/libgphxnetwork.a \
	@top_builddir@/base/src/netinterfaces/libnetinterfaces.a \
	@top_builddir@/base/src/utils/libutils.a


TESTS = enginetest

check_PROGRAMS = enginetest


enginetest_SOURCES = testmain.cpp \
		     schedulertest.cpp \
		     scheduler.cpp \
		     schedulertest.h

enginetest_LDADD = -ltestframework \
                   -lutils \
		   -L$(libdir) \
	           -L@builddir@/../../../base/src/TestFramework \
	           -L@builddir@/../../../base/src/utils

enginetest_DEPENDENCIES = \
	@top_builddir@/base/src/TestFramework/libtestframework.a \
	@top_builddir@/base/src/utils/libutils.a


