#ifndef INCLUDED_SCHEDULER_TEST_H
#define INCLUDED_SCHEDULER_TEST_H

#include "TestFramework/easytest.h"

class SchedulerTest : public EasyTest
{
public:
  SchedulerTest();
  virtual ~SchedulerTest();

  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};


#endif
