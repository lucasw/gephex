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
#elif defined(OS_DARWIN)
#include <mach-o/dyld.h>
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
#elif defined(OS_DARWIN) || defined(OS_POSIX)
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
#elif defined(OS_DARWIN)
    m_impl->handle 
      = DarwinComp::dlopen(path.c_str(),
			   DarwinComp::RTLD_LAZY);
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
#elif defined(OS_DARWIN)
    DarwinComp::dlclose(m_impl->handle);
#elif defined(OS_POSIX)
    dlclose(m_impl->handle);
#endif
  }
  
  void* SharedLibrary::loadSymbol(const std::string& name) const
  {
#if defined(OS_WIN32)
    return GetProcAddress(m_impl->handle,name.c_str());
#elif defined (OS_DARWIN)
    return DarwinComp::dlsym(m_impl->handle, name.c_str());
#elif defined(OS_POSIX)
    return dlsym(m_impl->handle,name.c_str());
#endif
  }

#if defined(OS_DARWIN)
  struct DarwinComp {
    static const int RTLD_LAZY=	0x1;
    static const int RTLD_NOW=	0x2;
    static const int RTLD_LOCAL=	0x4;
    static const int RTLD_GLOBAL=	0x8;
    static const int RTLD_NOLOAD=	0x10;
    static const int RTLD_NODELETE=	0x80;

    /* dlopen */
    static void* dlopen(const char *path, int mode)
    {
      void *module = 0;
      NSObjectFileImage ofi = 0;
      NSObjectFileImageReturnCode ofirc;

      /* If we got no path, the app wants the global namespace, use -1 as the marker
	 in this case */
      if (!path)
	return (void *)-1;

      /* Create the object file image, works for things linked with the -bundle arg to ld */
      ofirc = NSCreateObjectFileImageFromFile(path, &ofi);
      switch (ofirc)
	{
	case NSObjectFileImageSuccess:
	  /* It was okay, so use NSLinkModule to link in the image */
	  module = NSLinkModule(ofi, path,
				NSLINKMODULE_OPTION_RETURN_ON_ERROR
				| (mode & RTLD_GLOBAL) ? 0 : NSLINKMODULE_OPTION_PRIVATE
				| (mode & RTLD_LAZY) ? 0 : NSLINKMODULE_OPTION_BINDNOW);
	  NSDestroyObjectFileImage(ofi);
	  break;
	case NSObjectFileImageInappropriateFile:
	  /* It may have been a dynamic library rather than a bundle, try to load it */
	  module = (void *)NSAddImage(path, NSADDIMAGE_OPTION_RETURN_ON_ERROR);
	  break;
	default:
	  /* God knows what we got */
	  //error(0, "Can not open \"%s\"", path);
	  return 0;
	}
      if (!module)
      //error(0, "Can not open \"%s\"", path);
      return module;

    }

    /* dlsymIntern is used by dlsym to find the symbol */
    static void *dlsymIntern(void *handle, const char *symbol)
    {
      NSSymbol nssym = 0;
      /* If the handle is -1, if is the app global context */
      if (handle == (void *)-1)
	{
	  /* Global context, use NSLookupAndBindSymbol */
	  if (NSIsSymbolNameDefined(symbol))
	    {
	      nssym = NSLookupAndBindSymbol(symbol);
	    }

	}
      /* Now see if the handle is a struch mach_header* or not, use NSLookupSymbol in image
	 for libraries, and NSLookupSymbolInModule for bundles */
      else
	{
	  /* Check for both possible magic numbers depending on x86/ppc byte order */
	  if ((((struct mach_header *)handle)->magic == MH_MAGIC) ||
	      (((struct mach_header *)handle)->magic == MH_CIGAM))
	    {
	      if (NSIsSymbolNameDefinedInImage((struct mach_header *)handle, symbol))
		{
		  nssym = NSLookupSymbolInImage((struct mach_header *)handle,
						symbol,
						NSLOOKUPSYMBOLINIMAGE_OPTION_BIND
						| NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR);
		}

	    }
	  else
	    {
	      nssym = NSLookupSymbolInModule(handle, symbol);
	    }
	}
      if (!nssym)
	{
	  //error(0, "Symbol \"%s\" Not found", symbol);
	  return NULL;
	}
      return NSAddressOfSymbol(nssym);
    }

    static int dlclose(void *handle)
    {
      if ((((struct mach_header *)handle)->magic == MH_MAGIC) ||
	  (((struct mach_header *)handle)->magic == MH_CIGAM))
	{
	  //error(0, "Can't remove dynamic libraries on darwin");
	  return 0;
	}
      if (!NSUnLinkModule(handle, 0))
	{
	  //error(0, "unable to unlink module %s", NSNameOfModule(handle));
	  return 1;
	}
      return 0;
    }


    /* dlsym, prepend the underscore and call dlsymIntern */
    static void *dlsym(void *handle, const char *symbol)
    {
      static char undersym[257];	/* Saves calls to malloc(3) */
      int sym_len = strlen(symbol);
      void *value = NULL;
      char *malloc_sym = NULL;

      if (sym_len < 256)
	{
	  snprintf(undersym, 256, "_%s", symbol);
	  value = dlsymIntern(handle, undersym);
	}
      else
	{
	  malloc_sym = static_cast<char*>(malloc(sym_len + 2));
	  if (malloc_sym)
	    {
	      sprintf(malloc_sym, "_%s", symbol);
	      value = dlsymIntern(handle, malloc_sym);
	      free(malloc_sym);
	    }
	  else
	    {
	      //error(0, "Unable to allocate memory");
	    }
	}
      return value;
    }
  };
#endif

}
