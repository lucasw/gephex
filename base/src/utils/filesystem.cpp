#include "filesystem.h"

#include "config.h"

#if defined(OS_WIN32)
#include <direct.h>
#include <io.h>
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

DirEntry::DirEntry(const std::string& name,int type,int size)
  : m_name(name), m_type(type), m_size(size)
{
}

const std::string& DirEntry::getName() const
{
  return m_name;
}

int DirEntry::getType() const
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
    throw std::runtime_error(std::string("Could not open directory")+spec);
	
  do
    {
		int type;
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
    throw std::runtime_error(std::string("Could not open directory")+path);

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
      int type = S_ISREG(st.st_mode) ? DirEntry::FILE : DirEntry::DIRECTORY;
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
  //TODO
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
