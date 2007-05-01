EXTRA_DIST = utils.vcproj utils.dsp utils.mak utils.dep

TESTS=utilstest

check_PROGRAMS = utilstest

noinst_LIBRARIES = libutils.a

libutils_a_SOURCES = \
	buffer.cpp \
	bufferstream.cpp \
	bufferutils.cpp \
	circularbuffer.cpp \
	configfile.cpp \
	configmanager.cpp \
	filesystem.cpp \
	itokenizer.cpp \
	sharedlibrary.cpp \
	spawn.cpp \
	streamlogger.cpp \
	streamtokenizer.cpp \
	string_.cpp \
	stringtokenizer.cpp \
	structreader.cpp \
	structscanner.cpp \
	timing.cpp \
	xmlutils.cpp

noinst_HEADERS = \
	autoptr.h \
	block.h \
	buffer.h \
	bufferstream.h \
	bufferutils.h \
	circularbuffer.h \
	configfile.h \
	configmanager.h \
	filesystem.h \
	ilogger.h \
	istructtokenlistener.h \
	itokenizer.h \
	sharedlibrary.h \
	spawn.h \
	streamlogger.h \
	streamtokenizer.h \
	string_.h \
	stringtokenizer.h \
	structreader.h \
	structscanner.h \
	timing.h \
	xmlutils.h

INCLUDES = \
	-I @srcdir@/.. \
	-I@top_srcdir@/util/include \
	-I@top_builddir@/util/include

utilstest_SOURCES = \
	autoptrtest.cpp \
	autoptrtest.h \
	bufferstreamtest.cpp \
	bufferstreamtest.h \
	buffertest.cpp \
	buffertest.h \
	circularbuffertest.cpp \
	circularbuffertest.h \
	filesystemtest.cpp \
	filesystemtest.h \
	sharedlibrarytest.cpp \
	sharedlibrarytest.h \
	streamtokenizertest.cpp \
	streamtokenizertest.h \
	stringtokenizertest.cpp \
	stringtokenizertest.h \
	structreadertest.cpp \
	structreadertest.h \
	structscannertest.cpp \
	structscannertest.h \
	testmain.cpp \
	xmlutilstest.cpp \
	xmlutilstest.h

utilstest_LDADD = \
	-L@builddir@/../TestFramework \
	-L@builddir@ \
        -ltestframework \
	-lutils $(LIB_DL_FLAGS)

utilstest_DEPENDENCIES = \
	@builddir@/../TestFramework/libtestframework.a \
	@builddir@/libutils.a
