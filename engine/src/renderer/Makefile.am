EXTRA_DIST = renderer.vcproj renderer.dsp renderer.mak renderer.dep

baseincludedir = @includedir@/gephex
libdir = @libdir@/gephex
includedir = $(baseincludedir)/renderer

INCLUDES= -I @srcdir@/.. -I @srcdir@/../../../base/src -I @builddir@/../../../base/src

noinst_LIBRARIES = librenderer.a
librenderer_a_SOURCES = renderer.cpp  runtimesystem.cpp modulefactory.cpp typefactory.cpp modulefactory.h runtimesystem.h typefactory.h

noinst_HEADERS = renderer.h

TESTS = renderertest

check_PROGRAMS = renderertest

renderertest_SOURCES = renderertest.cpp
renderertest_LDADD = 	librenderer.a \
			-L@builddir@/../../../base/src/utils \
			-lutils

renderertest_DEPENDENCIES = \
			@top_builddir@/base/src/utils/libutils.a




