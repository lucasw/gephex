#include "threadposix.h"

#include <cassert>

#include <pthread.h>
#include <unistd.h> // for usleep()

#include "irunnable.h"

#include <iostream>

namespace thread
{

//-----------------------------------------------------------------------------

void* ThreadPOSIX::callbackWrapper(void *data) 
{
  ((ThreadPOSIX *) data)->runWrapper();
  return 0;
}

void ThreadPOSIX::runWrapper() 
{
  // fly a few waiting loops until the thread has been started...
  //TODO: this could be done better with a lock or something...
  //  std::cout << "hier1" << std::endl;
  while (!isRunning()) {}
  //  std::cout << "hier2" << std::endl;
  m_runner.run();
  //  std::cout << "hier3" << std::endl;
  _isRunning = false;
}

ThreadPOSIX::ThreadPOSIX(IRunnable& runner)
  : IThread(runner)
{
  pthread_t t;
  pthread_create(&t,0,callbackWrapper,this);
}

ThreadPOSIX::~ThreadPOSIX()
{
  //TODO: should the thread destry itself?
}

//-----------------------------------------------------------------------------

void ThreadUtilPOSIX::sleep(unsigned long microseconds)
{
  usleep(microseconds);
}

//-----------------------------------------------------------------------------

MutexPOSIX::MutexPOSIX()
{
  m_mutex = new char[sizeof(pthread_mutex_t)];
  pthread_mutex_init((pthread_mutex_t*) m_mutex,0);
}

MutexPOSIX::~MutexPOSIX()
{
  pthread_mutex_destroy((pthread_mutex_t*) m_mutex);
  delete[] (char*) m_mutex;
}

void MutexPOSIX::lock()
{
  pthread_mutex_lock((pthread_mutex_t*) m_mutex);
}

void MutexPOSIX::unlock()
{
  pthread_mutex_unlock((pthread_mutex_t*) m_mutex);
}

} // end of namespace

//-----------------------------------------------------------------------------


