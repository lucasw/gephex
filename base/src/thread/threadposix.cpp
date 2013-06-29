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


