#ifndef INCLUDED_THREAD_H
#define INCLUDED_THREAD_H

#include "config.h"

#ifdef OS_WIN32
#include "threadwindows.h"
namespace thread {
  typedef ThreadWINDOWS Thread;
  typedef MutexWINDOWS Mutex;
}
#endif
#ifdef OS_POSIX
#include "threadposix.h"
namespace thread {
  typedef ThreadPOSIX Thread;
  typedef MutexPOSIX Mutex;
}
#endif


#endif
