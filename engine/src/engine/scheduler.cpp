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

#include "scheduler.h"

#include <iostream>
#include <cassert>

#include "interfaces/itask.h"

#include "utils/timing.h"

namespace engine
{
  struct TaskControlBlock
  {
    TaskControlBlock(ITask* _task, int _interval)
      : task(_task), interval(_interval), timeLastCall(0)
    {
      timeLastCall = utils::Timing::getTimeInMillis();
    }
		
    ITask* task;
    unsigned long interval;
    unsigned long timeLastCall;
  };
	
  Scheduler::Scheduler()
    : tasks(), m_stopped(false) /*, idleTask(0), maxSleep(0)*/
  {
  }
	
  Scheduler::~Scheduler()
  {
  }
	
  void Scheduler::addTask(ITask& task,int timeInMillis)
  {
    tasks.push_back(TaskControlBlockPtr(new TaskControlBlock(&task,
							     timeInMillis)));
  }
	
  void Scheduler::killTask(ITask& task) throw (std::runtime_error)
  {
    for (TaskList::iterator i = tasks.begin(); i != tasks.end(); ++i)
      {
	if ((*i)->task == &task)
	  {
	    tasks.remove(*i);				
	    return;
	  }
      }
		
    throw std::runtime_error("No such task at Scheduler::killTask()");
  }
	
  void Scheduler::changeTaskTime(ITask& task,int newTimeInMillis)
    throw (std::runtime_error)
  {
    for (TaskList::iterator i = tasks.begin(); i != tasks.end(); ++i)
      {
	if ((*i)->task == &task)
	  {
	    (*i)->interval = newTimeInMillis;
	    return;
	  }
      }

    throw std::runtime_error("Konnte den task nicht finden.");
  }
		
  void Scheduler::run()
  {
    bool stop = false;
		

    while (stop == false && m_stopped == false)
      {
	long diffMax;
	TaskControlBlock* tMax = 0;
			
	unsigned long t = utils::Timing::getTimeInMillis();
	for (TaskList::iterator i = tasks.begin(); i != tasks.end(); ++i)
	  {
	    TaskControlBlock* current = &**i;
	    long diffTime = t - (current->timeLastCall + current->interval);
	    if (tMax == 0 || diffTime > diffMax)
	      {
		diffMax = diffTime;
		tMax = current;
	      }
	  }

	if (diffMax >= 0)
	  {
		bool kill_task = false;
		try
		{
			bool result = tMax->task->run();
			tMax->timeLastCall = t;

			if (!result)			
				kill_task = true;			
		}
		catch (std::exception& e)
		{
			std::cerr << "scheduler.cpp: run threw exception: " << e.what() << "\n";
			kill_task = true;
		}
		catch (...)
		{
			std::cerr <<  "scheduler.cpp: run threw unknown exception\n";
			kill_task = true;
		}				

		if (kill_task)
		{
		   killTask(*tMax->task);
		}
	  }
	else if (diffMax < -5)
	  {	    
	    utils::Timing::sleep(-diffMax);
	  }	  

	if (tasks.empty()) 
	  stop = true;
      }
  }

  void Scheduler::stop()
  {
    m_stopped = true;
  }

} // end of namespace
