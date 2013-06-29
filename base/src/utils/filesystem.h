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

#ifndef INCLUDED_FILE_SYSTEM_H
#define INCLUDED_FILE_SYSTEM_H

#include <string>
#include <list>
#include <stdexcept>

namespace utils
{

  /**
   * Platform independent filesystem services
   */


  /**
   * Specifies one entry that is returned by the FileSystem::listDir()
   * command.
   */
  class DirEntry
    {
    public:
      enum FileType { DIRECTORY, FILE };

      /**
       * Create a new DirEntry.
       * @param name name of the file/directory.
       * @param type wether its a file or directory (FILE | DIRECTORY).
       * @param size size of the file/driectory in bytes.
       */
      DirEntry(const std::string& name, FileType type, int size);

      /**
       * ...
       * @return name of the file/dir
       */
      const std::string& getName() const;

      /**
       * Returns wether this is a file or a directory.
       * @return FILE if this is a file or DIRECTORY if this is
       *         a directory
       */
      FileType getType() const;
	
      /**
       * ...
       * @return the size in bytes.
       */
      int getSizeInBytes() const;

    private:
      std::string m_name;
      FileType m_type;
      int m_size;
    };

  /**
   * The class FileSystem provides some primitive file system
   * services. Its main purpose is to hide platform specific
   * file system libraries.
   */
  class FileSystem
    {
    public:

      /**
       * Creates a new Directory.
       * @param path the name of the new dir
       * @throw TODO
       */
      static void makeDir(const std::string& path) throw (std::runtime_error);


      /**
       * Deletes a Directory. Files cant be deleted with this function.
       * @param path the name of the dir
       * @throw TODO
       */
      static void removeDir(const std::string& path)
	throw (std::runtime_error);

      /**
       * Lists the contents of a Directory.
       * @param path the name of the dir
       * @throw TODO
       */
      static void listDir(const std::string& path,std::list<DirEntry>& entries)
	throw (std::runtime_error);

      /**
       * Deletes a file. Directories cant be deleted with this function.
       * @param path the name of the file
       * @throw TODO
       */
      static void removeFile(const std::string& path);

      /**
       * Returns true, if path exists, false otherwise.
       */
      static bool exists(const std::string& path);
    };

} // end of namespace utils

#endif
