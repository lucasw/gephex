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

#include "threadtest.h"

#include <iostream>

/*---------------------------------------------------------------------------*/

#include "threadposix.h"
#include "irunnable.h"

ThreadTest::ThreadTest()
  : EasyTest("ThreadTest","")
{
}

ThreadTest::~ThreadTest()
{
}

thread::IThreadUtil* tu;

class SimpleRunner : public thread::IRunnable
{
  char *name;

public:
  int count;


  SimpleRunner(char *);
  virtual void run();
};

SimpleRunner::SimpleRunner(char *iname) : count(0) 
{
  name = new char[strlen(iname) +1];
  strcpy(name,iname);
}

void SimpleRunner::run() 
{
  while(count < 3) 
    {
	  std::cout << "This is " << name << "\n";
      tu->sleep(100 * 1000);
      ++count;
    }
}

/*---------------------------------------------------------------------------*/

void ThreadTest::pre() throw(std::runtime_error)
{
}

void ThreadTest::post() throw(std::runtime_error)
{
}

void ThreadTest::run() throw(std::runtime_error) 
{
  tu = new thread::ThreadUtilPOSIX();

  SimpleRunner s1("Thread #1"), s2("Thread #2");

  thread::IThread* t1 = new thread::ThreadPOSIX(s1);
  thread::IThread* t2 = new thread::ThreadPOSIX(s2);

  std::cout << "Sleeping..." << std::endl;
  tu->sleep(2000*1000);
  std::cout << "Starting Threads..." << std:: endl;

  t1->start();
  t2->start();

  while (t1->isRunning() || t2->isRunning()) 
    {
    }
  
  if (!(s1.count == 3 && s2.count == 3))
    {
      throw std::runtime_error("Error");
    }
   

  delete t1;
  delete t2;
  //  cout << "Threads have terminated, exiting...\n";
}

/*---------------------------------------------------------------------------*/
