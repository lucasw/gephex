#ifndef INCLUDED_THREAD_TEST_H
#define INCLUDED_THREAD_TEST_H

#include "TestFramework/easytest.h"

class ThreadTest : public EasyTest
{
public:
  ThreadTest();
  virtual ~ThreadTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
