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
