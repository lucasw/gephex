#ifndef INCLUDED_THREAD_WINDOWS_H
#define INCLUDED_THREAD_WINDOWS_H

#include "ithread.h"
#include "imutex.h"
#include "ithreadutil.h"

#include <windows.h> //TODO

namespace thread
{

//-----------------------------------------------------------------------------

class ThreadWINDOWS : public IThread
{
private:
  static DWORD WINAPI callbackWrapper(void *);
  HANDLE hThread;

  void runWrapper();

  ThreadWINDOWS(const ThreadWINDOWS &); //not implemented
  ThreadWINDOWS & operator =(const ThreadWINDOWS &); //not implemented
public:
  ThreadWINDOWS(IRunnable& runner);
  virtual ~ThreadWINDOWS();

};

//-----------------------------------------------------------------------------

class ThreadUtilWINDOWS : public IThreadUtil
{
 public:
  virtual void sleep(unsigned long microsecs);
};

//-----------------------------------------------------------------------------

//TODO: Exceptions (see the Implementation)
class MutexWINDOWS : public IMutex
{
  HANDLE hMutex;

  MutexWINDOWS(const MutexWINDOWS&); // not implemented;
  MutexWINDOWS& operator=(const MutexWINDOWS&); // not implemented;
public:
  MutexWINDOWS();
  virtual ~MutexWINDOWS();

  virtual void lock();
  virtual void unlock();
};

} // end of namespace

#endif
