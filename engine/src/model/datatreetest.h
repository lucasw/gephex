#ifndef __DATATREETEST_H__
#define __DATATREETEST_H__

#include "TestFramework/easytest.h"

class DataTreeTest : public EasyTest
{
public:
  DataTreeTest();
  virtual ~DataTreeTest();

  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};



#endif