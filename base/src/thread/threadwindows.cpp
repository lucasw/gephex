/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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


