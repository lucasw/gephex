#ifndef INCLUDED_SHARED_LIBRARY_TEST_H
#define INCLUDED_SHARED_LIBRARY_TEST_H

#include "../TestFramework/easytest.h"

class SharedLibraryTest : public EasyTest
{
public:
  SharedLibraryTest();
  virtual ~SharedLibraryTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif
