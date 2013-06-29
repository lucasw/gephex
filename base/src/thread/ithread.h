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

#ifndef INCLUDED_ITHREAD_H
#define INCLUDED_ITHREAD_H

namespace thread
{

class IRunnable;

//-----------------------------------------------------------------------------

// A simple thread class. After construction, a new thread has been created 
// thats not yet running. 
// After start() is invoked the run() method of the runner is started
// in this new thread. The thread exits when run() returns.
class IThread 
{
private:

  IThread(const IThread &); //not implemented
  IThread & operator=(const IThread &); //not implemented

protected:
  volatile bool _isRunning;
  IRunnable& m_runner;

public:
  // create a new (stopped) thread
  IThread(IRunnable& runner);
  virtual ~IThread();

  // start the thread (the run() method is called)
  // dont override!
  void start();

  // true, while the thread executes the run() method
  // false before and afterwards
  // dont override!
  bool isRunning() const;

  // let the current thread sleep for millis ms.
  //virtual void sleep(int millis) = 0;

  // tell the scheduler to continue with another thread
  //virtual void yield() = 0;
};

//-----------------------------------------------------------------------------

} // end of namespace
#endif
