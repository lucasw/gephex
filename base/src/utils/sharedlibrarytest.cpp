#include "sharedlibrarytest.h"

#include <iostream>

#include "config.h"
#include "sharedlibrary.h"

/*---------------------------------------------------------------------------*/

SharedLibraryTest::SharedLibraryTest()
  : EasyTest("SharedLibraryTest","")
{
}

SharedLibraryTest::~SharedLibraryTest()
{
}

void SharedLibraryTest::pre() throw(std::runtime_error)
{
}

void SharedLibraryTest::run() throw(std::runtime_error)
{
#if defined(OS_WIN32)
  const std::string LIB_NAME = "addmodule.dll";
#elif defined(OS_POSIX)
  const std::string LIB_NAME = "addmodule.so";
#endif
 
  utils::SharedLibrary* sl;

  try {
    sl = new utils::SharedLibrary(LIB_NAME);

    void* dummy = sl->loadSymbol("getSpec");

    if (dummy == 0)
      throw std::runtime_error("Could not resolve getSpec!");

    delete sl;
  }
  catch (std::runtime_error& e) {
    std::string msg = "First run: ";
    msg += e.what();
    throw std::runtime_error(msg.c_str());
  }

  try {
    //Test if loading again after unloading succeeds:
    sl = new utils::SharedLibrary(LIB_NAME);

    void* dummy = sl->loadSymbol("getSpec");

    if (dummy == 0)
      throw std::runtime_error("Could not resolve getSpec!");

    typedef const char* (*getSpecT) (void);
    getSpecT getSpec = (getSpecT) (dummy);
    
    std::string spec = getSpec();

    std::cout << spec << std::endl;
    delete sl;
  }
  catch (std::runtime_error& e) {
    std::string msg = "Second run: ";
    msg += e.what();
    throw std::runtime_error(msg.c_str());
  }

}

void SharedLibraryTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
