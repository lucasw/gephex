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

#include "filesystem.h"

#include "config.h"

#if defined(OS_WIN32)
#include <direct.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#elif defined(OS_POSIX)
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#else
#error "Unknown OS!"
#endif

namespace utils
{

DirEntry::DirEntry(const std::string& name, FileType type,int size)
  : m_name(name), m_type(type), m_size(size)
{
}

const std::string& DirEntry::getName() const
{
  return m_name;
}

DirEntry::FileType DirEntry::getType() const
{
  return m_type;
}
	
int DirEntry::getSizeInBytes() const
{
  return m_size;
}


void FileSystem::makeDir(const std::string& path) throw (std::runtime_error)
{
#if defined(OS_WIN32)
  int error = _mkdir(path.c_str());
#elif defined(OS_POSIX)
  mode_t mt;
  mt=0777;
  int error = mkdir(path.c_str(),mt);
#else
#error "Unknown OS!"
#endif
  if (error != 0)
    {
      throw std::runtime_error("Could not create directory");
    }
}

void FileSystem::removeDir(const std::string& path) throw (std::runtime_error)
{
#if defined(OS_WIN32)
  int error = _rmdir(path.c_str());
#elif defined(OS_POSIX)
  int error = rmdir(path.c_str());
#else
#error "Unknown OS!"
#endif

  if (error != 0)
    {
      throw std::runtime_error("Could not remove directory");
    }
}

void FileSystem::listDir(const std::string& path,std::list<DirEntry>& entries)
  throw (std::runtime_error)
{
#if defined(OS_WIN32)
  struct _finddata_t c_file;
  long hFile;

  std::string spec = path + "/*";
	
  /* Find first .c file in current directory */
  if( (hFile = _findfirst( spec.c_str(), &c_file )) == -1 )
    throw std::runtime_error(std::string("Could not open directory ")+spec);
	
  do
    {
		DirEntry::FileType type;
		if (c_file.attrib & _A_SUBDIR)
			type = DirEntry::DIRECTORY;
		else 
			type =DirEntry::FILE;
      entries.push_back(DirEntry(c_file.name,type,c_file.size));
    } while( _findnext( hFile, &c_file ) == 0 );
	
  _findclose( hFile );
	

#elif defined(OS_POSIX)
  DIR* dstream = opendir(path.c_str());
  if (dstream == 0)
    throw std::runtime_error(std::string("Could not open directory ")+path);

  dirent* current = readdir(dstream);
  while (current != 0)
    {
      struct stat st;
      std::string fullname = path.c_str() + std::string("/") + current->d_name;
      int err = stat(fullname.c_str(),&st);      
      if (err != 0)
	{
	  //TODO
	  throw std::runtime_error(fullname + " JAJAJAJA");
	}
      DirEntry::FileType type =
        S_ISREG(st.st_mode) ? DirEntry::FILE
                            : DirEntry::DIRECTORY;

      int size = st.st_blocks * 512;
      entries.push_back(DirEntry(current->d_name,type,size));
      current = readdir(dstream);
    }
  closedir(dstream);
#else
#error "Unknown OS!"
#endif
}

void FileSystem::removeFile(const std::string& path)
{
  int error = remove(path.c_str());
  if (error != 0)
    {
      throw std::runtime_error("Could not remove file");
    }
}

bool FileSystem::exists(const std::string& path)
{
#if defined(OS_WIN32)
  struct _stat st;

  std::string p;
  char lastc = path[path.length() -1];
  if (lastc == '\\' || lastc == '/')
	  p = path.substr(0, path.length()-1);
  else
	  p = path;

  int err = _stat(p.c_str(),&st);      
  if (err != 0)
    {
      return false;
    }
  else
    {
      return true;
    }
  return true;
#elif defined(OS_POSIX)
  struct stat st;
  int err = stat(path.c_str(),&st);      
  if (err != 0)
    {
      return false;
    }
  else
    {
      return true;
    }
#else
#error "Unknown OS!"
#endif  
}
} // end of namespace utils
