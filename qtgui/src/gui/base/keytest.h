#ifndef INCLUDED_KEY_TEST_H
#define INCLUDED_KEY_TEST_H

#include "easytest.h"

class KeyTest : public EasyTest
{
public:
  KeyTest();
  virtual ~KeyTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
