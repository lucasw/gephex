/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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
