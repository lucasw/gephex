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

#include "schedulertest.h"

#include <string>
#include <iostream>

#include "scheduler.h"

#include "interfaces/itask.h"

#include "utils/timing.h"

double doShit(int ttt)
{
  double t;
  for (int i = 0; i < ttt; ++i)
    {
      t = t*ttt-i;
    }

  return t;
}

class TimerTask : public ITask
{
public:
  TimerTask(const std::string& nam,unsigned long interval, int maxC)
    : name(nam), count(0), maxCount(maxC), last_time(0), iv(interval)
  {
  }

  virtual ~TimerTask() {}
  
  virtual bool run(void)
  {
    unsigned long t = utils::Timing::getTimeInMillis();

    if (count != 0)
      {
	int diff = (t - last_time) - iv;
	std::cout << name << " diff : " << diff 
		  << " = " << 100. * diff / (double) iv
		  << "%" << std::endl;
      }

    //    doShit(10000);

    last_time = t;
    ++count;

    return count > maxCount ? false : true;
  }

private:
  std::string name;
  int count;
  int maxCount;
  unsigned long last_time;
  unsigned long iv;


};

/*---------------------------------------------------------------------------*/

SchedulerTest::SchedulerTest()
  : EasyTest("SchedulerTest","")
{
}

SchedulerTest::~SchedulerTest()
{
}

void SchedulerTest::pre() throw(std::runtime_error)
{
}

void SchedulerTest::run() throw(std::runtime_error)
{  
  engine::Scheduler sq;

  TimerTask task1("task1",100,10);
  sq.addTask(task1,100);

  TimerTask task2("task2",200,5);
  sq.addTask(task2,200);

  TimerTask task3("task3",20,50);
  sq.addTask(task3,20);

  TimerTask task4("task4",10,100);
  sq.addTask(task4,10);

  TimerTask task5("task5",40,25);
  sq.addTask(task5,40);

  unsigned long start = utils::Timing::getTimeInMillis();

  sq.run();

  unsigned long end = utils::Timing::getTimeInMillis();

  double time = end - start;
  std::cout << "Zeit : " << time << "ms" << std::endl;
}

void SchedulerTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
