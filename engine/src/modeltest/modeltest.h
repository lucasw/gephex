#ifndef __MODELTEST_H__
#define __MODELTEST_H__

#include "TestFramework/easytest.h"

class ModelTest : public EasyTest
{
public:
  ModelTest();
  virtual ~ModelTest();

  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};



#endif