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

#include "spawn.h"

#include <stdexcept>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_POSIX)
#include <sys/types.h>
#include <unistd.h>
#elif defined(OS_WIN32)
#include <windows.h>
namespace utils { static std::string get_error_text(); }
#endif

//-------------------------------------------------------------------------

namespace utils
{

  static char** argv_from_vector(const std::string& exec_name,
                                 const std::vector<std::string>& args);

  static char* cmdline_from_vector(const std::string& exec_name,
	                               const std::vector<std::string>& args);

  //-------------------------------------------------------------------------

  void spawn(const std::string& exec_name,
             const std::vector<std::string>& args)
  {
#if defined(OS_POSIX)
    const pid_t pid( fork() );
    
    if (pid == -1)
      throw std::runtime_error("fork failed");

    if (pid!=0)
      {
        // create 0 terminated array of argument pointers
        char** argv = argv_from_vector(exec_name, args);
        
        execvp(exec_name.c_str(), argv);
        exit(0);
      }
#elif defined(OS_WIN32)
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
		
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    char* arg_string = cmdline_from_vector(exec_name, args);
		
    //TODO: args
    BOOL ret = CreateProcess(
                             exec_name.c_str(),   // name of executable module
                             arg_string,          // command line string
                             0,                   // SD
                             0,                   // SD
                             FALSE,               // handle inheritance option
                             CREATE_NEW_CONSOLE,  // creation flags
                             0,                   // new environment block
                             0,                   // current directory name
                             &si,                 // startup information
                             &pi                  // process information
                             );

    if (!ret)
      {
        throw std::runtime_error(get_error_text().c_str());
      }

    //TODO: the handles in pi must be freed when the process
    // is finished, but is it ok do close them here?
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
		
#else
    throw std::runtime_error("spawn not implemented");
#endif
  }

  //-----------------------------------------------------------------------

  /**
   * creates 0 terminated array of pointers to c strings
   * inserts exec_name as first argument
   */
  static char** argv_from_vector(const std::string& exec_name,
                                 const std::vector<std::string>& args)
  {
    int num_args = args.size();
    char** argv = new char*[num_args+2];

    argv[0] = strdup(exec_name.c_str());
    for (int i = 0; i < num_args; ++i)
      {
        argv[i+1] = strdup(args[i].c_str());
      }
    argv[num_args+1] = 0;

    return argv;
  }

  //-----------------------------------------------------------------------

  /**
   * Concatenates all arguments into one string (separated by whitespace).
   * Appends the exec_name as first argument
   */
  static char* cmdline_from_vector(const std::string& exec_name,
	                                     const std::vector<std::string>& args)
  {
    int num_args = args.size();
    std::string result = exec_name + " ";
    for (int i = 0; i < num_args; ++i)
      {
        result += args[i] + " ";
      }

	char* cmd_line = strdup(result.c_str());
    return cmd_line;
  }

  //-----------------------------------------------------------------------

#if defined(OS_WIN32)
  static std::string get_error_text()
  {
    LPVOID lpMsgBuf;
    FormatMessage( 
                  FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_FROM_SYSTEM | 
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR) &lpMsgBuf,
                  0,
                  NULL 
                  );

    char buffer[1024];
    _snprintf(buffer, sizeof(buffer), "%s", (LPCTSTR) lpMsgBuf);
    LocalFree( lpMsgBuf );

    return std::string(buffer, sizeof(buffer));
  }
#endif
}
