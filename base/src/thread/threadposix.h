#ifndef INCLUDED_THREAD_POSIX_H
#define INCLUDED_THREAD_POSIX_H

#include "ithread.h"
#include "imutex.h"
#include "ithreadutil.h"

namespace thread
{

//-----------------------------------------------------------------------------

class ThreadPOSIX : public IThread
{
private:
  static void* callbackWrapper(void *);

  void runWrapper();

  ThreadPOSIX(const ThreadPOSIX &); //not implemented
  ThreadPOSIX & operator =(const ThreadPOSIX &); //not implemented
public:
  ThreadPOSIX(IRunnable& runner);
  virtual ~ThreadPOSIX();
};

//-----------------------------------------------------------------------------

class ThreadUtilPOSIX : public IThreadUtil
{
 public:
  virtual void sleep(unsigned long microsecs);
};

//-----------------------------------------------------------------------------

//TODO: Exceptions (see the Implementation)
class MutexPOSIX : public IMutex
{
  void* m_mutex;

  MutexPOSIX(const MutexPOSIX&); // not implemented;
  MutexPOSIX& operator=(const MutexPOSIX&); // not implemented;
public:
  MutexPOSIX();
  virtual ~MutexPOSIX();

  virtual void lock();
  virtual void unlock();
};

} // end of namespace

#endif


