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

#include "sharedlibrary.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <windows.h>
#elif defined(OS_POSIX)
#include <dlfcn.h>
#endif

#include <stdexcept>
//#include <cstdlib>

//#include <iostream>


namespace utils
{
  struct SharedLibraryImpl
  {

#if defined(OS_WIN32)
  typedef HINSTANCE HandleType;
#elif defined(OS_POSIX)
  typedef void* HandleType;
#endif 

    HandleType handle;


    SharedLibraryImpl()
      : handle(0)
    {
    }
  };    

  SharedLibrary::SharedLibrary(const std::string& path)
    : m_impl(new SharedLibraryImpl()), m_TODOName(path)
  {
    //    std::cout << "Loading '" << m_TODOName << "'" << std::endl;
#if defined(OS_WIN32)
    m_impl->handle = LoadLibrary(path.c_str());
#elif defined(OS_LINUX)
    m_impl->handle = dlopen(path.c_str(), RTLD_NOW);
#elif defined(OS_BSD)
    m_impl->handle = dlopen(path.c_str(), DL_LAZY);
#elif defined(OS_POSIX)
    m_impl->handle = dlopen(path.c_str(), 0);
#endif

    if (m_impl->handle == 0)
      {
#if defined(OS_WIN32)
	std::string msg = "Could not load shared libraray '" + path +"'";
#elif defined(OS_POSIX)
	std::string msg = "Could not load shared libraray '" + path +"': "
	  + std::string(dlerror());
#endif
	throw std::runtime_error(msg.c_str()); 
      }
  }

  SharedLibrary::~SharedLibrary()
  {
    //    std::cout << "Unloading '" << m_TODOName << "'" << std::endl;
#if defined(OS_WIN32)
    FreeLibrary(m_impl->handle);
#elif defined(OS_POSIX)
    dlclose(m_impl->handle);
#endif
  }
  
  void* SharedLibrary::loadSymbol(const std::string& name) const
  {
#if defined(OS_WIN32)
    return (void*) GetProcAddress(m_impl->handle,name.c_str());
#elif defined(OS_POSIX)
    return dlsym(m_impl->handle,name.c_str());
#endif
  }

}
