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
      throw std::runtime_error("Fehler");
    }
   

  delete t1;
  delete t2;
  //  cout << "Threads have terminated, exiting...\n";
}

/*---------------------------------------------------------------------------*/
