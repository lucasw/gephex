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


