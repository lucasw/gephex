#include "threadwindows.h"

#include <cassert>
#include "irunnable.h"

namespace thread
{

// stupid wrapper
DWORD WINAPI ThreadWINDOWS::callbackWrapper(void *data) 
{
  ((ThreadWINDOWS *) data)->runWrapper();
  return 0;
}

void ThreadWINDOWS::runWrapper() 
{
  // fly a few waiting loops until the thread has been started...
  //TODO: this could be done better with a lock or something...
  while (!isRunning()) {}
  m_runner.run();
  _isRunning = false;
}

ThreadWINDOWS::ThreadWINDOWS(IRunnable& runner)
  : IThread(runner)
{
  hThread = CreateThread(NULL, 0, callbackWrapper, this, 0, 0);
  if(hThread==INVALID_HANDLE_VALUE){
    MessageBox(NULL, "Thread Creation failed mysteriously!", "Error", MB_OK);
  }
}

ThreadWINDOWS::~ThreadWINDOWS()
{
	CloseHandle(hThread);
}

//-----------------------------------------------------------------------------

void ThreadUtilWINDOWS::sleep(unsigned long microseconds)
{
  Sleep(microseconds/1000); 
}

//-----------------------------------------------------------------------------

MutexWINDOWS::MutexWINDOWS()
{
  hMutex = CreateMutex (NULL, FALSE, TEXT("ConsolenMaxMutex"));
  if(hMutex==INVALID_HANDLE_VALUE){
    MessageBox(NULL, "Mutex Creation failed", "Error", MB_OK);
  }
}

MutexWINDOWS::~MutexWINDOWS()
{
  //??
  if (! ReleaseMutex (hMutex))
    {
      MessageBox(NULL, "Releasing of Mutex object failed", "Error", MB_OK);
    }	
}

void MutexWINDOWS::lock()
{
  //wahrscheinlich bullshit so
  //ja, denk ich auch
  WaitForSingleObject(hMutex, INFINITE);
}

void MutexWINDOWS::unlock()
{
  ReleaseMutex(hMutex);
}

} // end of namespace thread
//-----------------------------------------------------------------------------


