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


