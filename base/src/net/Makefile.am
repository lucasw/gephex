baseincludedir = @includedir@/gephex
includedir = @includedir@/gephex/net
libdir = @libdir@/gephex

noinst_PROGRAMS = nettest
lib_LIBRARIES = libnetwork.a

libnetwork_a_SOURCES = \
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
		domainserversocket.cpp \
		domainclientsocket.cpp
#commandmux.cpp netdispatcher.cpp  fileprotocol.cpp netprotocol.cpp clientnetsocket.cpp ervernetsocket.cpp tcpsocket.cpp udpsocket.cpp netdispatcher2.cpp


include_HEADERS = \
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
		domainserversocket.h \
		domainclientsocket.h \
		protocoltest.h \
		tcpsockettest.h \
		tagdispatchertest.h \
		taggertest.h \
		domainsockettest.h

INCLUDES = -I .. #${baseincludedir}

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


nettest_LDFLAGS = -L../TestFramework -L../utils -L.
nettest_LDADD =  -ltestframework -lnetwork -lutils 
