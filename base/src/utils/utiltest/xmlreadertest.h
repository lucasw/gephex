#ifndef INCLUDED_XML_READER_TEST_H
#define INCLUDED_XML_READER_TEST_H

#include "../TestFramework/easytest.h"

class XMLReaderTest : public EasyTest
{
public:
  XMLReaderTest();
  virtual ~XMLReaderTest();
  
  virtual void pre() throw(std::runtime_error);
  virtual void run() throw(std::runtime_error);
  virtual void post() throw(std::runtime_error);
};

#endif