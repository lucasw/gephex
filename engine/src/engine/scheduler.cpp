#include "scheduler.h"

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
	    bool result = tMax->task->run();

	    tMax->timeLastCall = t;
				
	    if (!result)
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
