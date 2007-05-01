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
