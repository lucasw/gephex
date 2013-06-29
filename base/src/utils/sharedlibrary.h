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

#ifndef INCLUDED_SHARED_LIBRARAY_H
#define INCLUDED_SHARED_LIBRARAY_H

#include <string>
#include <memory>

namespace utils
{

  class SharedLibraryImpl;

  /**
   * With SharedLibrary you can dynamically load libraries.
   * Each SharedLibrary object corresponds to one dynamically
   * loaded library.
   * On creation, the library is opened.
   * On destruction, the library is closed.
   */
  class SharedLibrary 
  {
  private:
    SharedLibrary(const SharedLibrary&); //not impl.
    SharedLibrary& operator=(const SharedLibrary&); //not impl.

  public:
    
    /**
     * Creates a new SharedLibrary and tries to open it.
     * @param path the complete path to the library
     * @throw std::runtime_error if path could not be opened
     */
    SharedLibrary(const std::string& path);

    /**
     * Destroys the shared library and closes it.
     */
    ~SharedLibrary();

    /**
     * Loads a symbol of the shared library.
     * @name the name of the symbol
     * @return the pointer to the symbol in the library.
     *     If the symbol is not found, 0 is returned.
     */
    void* loadSymbol(const std::string& name) const;

  private:
    std::auto_ptr<SharedLibraryImpl> m_impl;

    std::string m_TODOName;
  };

}
#endif


