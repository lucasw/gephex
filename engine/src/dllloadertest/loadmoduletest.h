#ifndef INCLUDED_LOADMODULE_TEST_H
#define INCLUDED_LOADMODULE_TEST_H

#include "../TestFramework/easytest.h"

class LoadModuleTest : public EasyTest
{
public:
  LoadModuleTest();
  virtual ~LoadModuleTest();

  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif

