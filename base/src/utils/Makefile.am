TESTS=utilstest

check_PROGRAMS = utilstest

noinst_LIBRARIES = libutils.a

libutils_a_SOURCES = \
		stringtokenizer.cpp \
		structscanner.cpp \
		filesystem.cpp \
		structreader.cpp \
		buffer.cpp \
		itokenizer.cpp \
		streamtokenizer.cpp \
		bufferutils.cpp \
		xmlutils.cpp \
		streamlogger.cpp \
		outbytestream.cpp \
		inbytestream.cpp \
		outbytestreamutils.cpp \
		inbytestreamutils.cpp \
		bufferstream.cpp \
		string_.cpp \
		sharedlibrary.cpp \
		timing.cpp

noinst_HEADERS = \
		autoptr.h \
		buffer.h \
		bufferutils.h \
		filesystem.h \
		ilogger.h \
		istructtokenlistener.h \
		itokenizer.h \
		streamlogger.h \
		streamtokenizer.h \
		stringtokenizer.h \
		structreader.h \
		structscanner.h \
		xmlutils.h \
		outbytestream.h \
		inbytestream.h \
		outbytestreamutils.h \
		inbytestreamutils.h \
		bufferstream.h \
		block.h \
		string_.h \
		sharedlibrary.h \
		timing.h

INCLUDES = \
	-I @srcdir@/.. \
	-I@top_srcdir@/util/include \
	-I@top_builddir@/util/include

utilstest_SOURCES = \
	testmain.cpp \
	stringtokenizertest.cpp \
	structreadertest.cpp \
	streamtokenizertest.cpp \
	structscannertest.cpp \
	buffertest.cpp \
	filesystemtest.cpp \
        autoptrtest.cpp \
        bytestreamtest.cpp \
	bufferstreamtest.cpp \
	sharedlibrarytest.cpp \
	autoptrtest.h \
	bufferstreamtest.h \
	buffertest.h \
	bytestreamtest.h \
	filesystemtest.h \
	streamtokenizertest.h \
	stringtokenizertest.h \
	structreadertest.h \
	structscannertest.h \
	sharedlibrarytest.h

if NEED_DL
LIB_DL_FLAGS = -ldl
endif

utilstest_LDADD = \
	-L@builddir@/../TestFramework \
	-L@builddir@ \
        -ltestframework \
	-lutils $(LIB_DL_FLAGS)

utilstest_DEPENDENCIES = \
	@builddir@/../TestFramework/libtestframework.a \
	@builddir@/libutils.a





