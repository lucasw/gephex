noinst_LIBRARIES = libthread.a
libthread_a_SOURCES = ithread.cpp imutex.cpp threadposix.cpp ithread.h imutex.h irunnable.h ithreadutil.h thread.h threadposix.h

INCLUDES = -I ..

noinst_PROGRAMS = threadtest

threadtest_SOURCES = testmain.cpp threadtest.cpp  threadtest.h 

threadtest_LDADD = ../TestFramework/libtestframework.la libthread.a -lpthread