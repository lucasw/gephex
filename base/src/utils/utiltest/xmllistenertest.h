#ifndef INCLUDED_XML_LISTENER_TEST_H
#define INCLUDED_XML_LISTENER_TEST_H

#include "../TestFramework/easytest.h"

class XMLListenerTest : public EasyTest
{
public:
  XMLListenerTest();
  virtual ~XMLListenerTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif