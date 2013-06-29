noinst_LIBRARIES = libthread.a

if OS_WINDOWS
PLT_SOURCS = \
	threadwindows.cpp \
	threadwindows.h
else
PLT_SOURCS = \
	threadposix.cpp \
	threadposix.h

PLT_LBS = -lpthread
endif

libthread_a_SOURCES = \
	ithread.cpp \
	imutex.cpp \
	ithread.h \
	imutex.h \
	irunnable.h \
	ithreadutil.h \
	thread.h $(PLT_SOURCS)

INCLUDES = -I @srcdir@/..

TESTS= threadtest

check_PROGRAMS = threadtest

threadtest_SOURCES = testmain.cpp threadtest.cpp threadtest.h 

threadtest_LDADD = ../TestFramework/libtestframework.a libthread.a $(PLT_LBS)
