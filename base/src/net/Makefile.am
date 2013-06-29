EXTRA_DIST = net.vcproj net.dsp net.mak net.dep \
	fhsocket.cpp fhsocket.h \
	namedpipeserversocket.cpp namedpipeserversocket.h \
	namedpipeclientsocket.cpp namedpipeclientsocket.h \
	namedpipesockettest.cpp namedpipesockettest.h

TESTS=nettest

check_PROGRAMS = nettest
noinst_LIBRARIES = libgphxnetwork.a

if OS_WINDOWS
PLT_SOURCS = \
	namedpipeclientsocket.cpp \
	namedpipeserversocket.cpp \
	fhsocket.cpp

PLT_HEADRS = \
	namedpipeclientsocket.h \
	namedpipeserversocket.h \
	fhsocket.h
else
PLT_SOURCS = \
	domainserversocket.cpp \
	domainclientsocket.cpp
PLT_HEADRS = \
	domainserversocket.h \
	domainclientsocket.h
endif

libgphxnetwork_a_SOURCES = \
		netexceptions.cpp \
		protocol.cpp \
		tagutils.cpp \
		isocket.cpp \
		sotimeout.cpp \
		socketutils.cpp \
		tcpserversocket.cpp \
		tcpclientsocket.cpp \
		fdsocket.cpp \
		socketadaptor.cpp \
		convertbin.cpp $(PLT_SOURCS)

noinst_HEADERS = \
		protocol.h \
		idatalistener.h \
		isender.h \
		netexceptions.h \
		itagger.h \
		itaginterpreter.h \
		tagger.h \
		tagger.cpp \
		tagutils.h \
		isocket.h \
		socketutils.h \
		sotimeout.h \
		iclientsocket.h \
		iserversocket.h \
		tcpclientsocket.h \
		tcpserversocket.h \
		fdsocket.h \
		socketadaptor.h \
		tagdispatcher.h \
		tagdispatcher.cpp \
		protocoltest.h \
		tcpsockettest.h \
		tagdispatchertest.h \
		taggertest.h \
		domainsockettest.h \
		convertbin.h $(PLT_HEADRS)

INCLUDES = -I @srcdir@/.. -I @srcdir@/../../../util/include

nettest_SOURCES = \
		testmain.cpp \
		block.h \
		tcpsockettest.cpp \
		protocoltest.cpp \
		taggertest.cpp \
		tagdispatchertest.cpp \
		domainsockettest.cpp \
		tcpsockettest.h \
		protocoltest.h \
		taggertest.h \
		tagdispatchertest.h \
		domainsockettest.h

nettest_LDADD = \
	-L@builddir@/../TestFramework \
	-L@builddir@/../utils \
	-L@builddir@ \
	-ltestframework \
	-lgphxnetwork \
	-lutils 

nettest_DEPENDENCIES = \
	@builddir@/../TestFramework/libtestframework.a \
	@builddir@/../utils/libutils.a  \
	@builddir@/libgphxnetwork.a
