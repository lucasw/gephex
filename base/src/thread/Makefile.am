noinst_LIBRARIES = libthread.a
libthread_a_SOURCES = ithread.cpp imutex.cpp threadposix.cpp ithread.h imutex.h irunnable.h ithreadutil.h thread.h threadposix.h

INCLUDES = -I @srcdir@/..

TESTS= threadtest

check_PROGRAMS = threadtest

threadtest_SOURCES = testmain.cpp threadtest.cpp  threadtest.h 

threadtest_LDADD = ../TestFramework/libtestframework.a libthread.a -lpthread
