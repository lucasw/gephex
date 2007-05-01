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

#if defined (HAVE_CONFIG_H)
#include "config.h"
#endif

#include <iostream>
#include <stdexcept>
#include <algorithm>

#if defined(OS_WIN32)
#include "windows.h" //for Sleep and signal handling
void my_se_translator(unsigned int u, EXCEPTION_POINTERS* p);
#elif defined(OS_POSIX)
#include <signal.h>
#endif

#include "configmanager.h"
#include "controller.h"

// this global variable is needed for the signal handling
static engine::Controller* s_controller;

#if defined(OS_POSIX)
typedef void (*sighandler_t)(int);
void signal_handler (int signum)
{
  std::cout << "Got signal " << signum << " trying to exit!" <<std::endl;

  // ignore sigpipe
  if (signum == SIGPIPE)
    {
      std::cout << "Ignoring SIGPIPE!" << std::endl;
      return;
    }

  if (s_controller && !s_controller->finished())
    {
      s_controller->shutDown();
    }
} 

class Signals
{
public:
  Signals(){}
  
  void setSignal(int signum, sighandler_t handler)
  {
    SignalMapT::const_iterator it = oldSignalHandlers.find(signum); 
    if (it != oldSignalHandlers.end())
      {
	throw std::runtime_error("signalhandler is already changed");
      }
    
    sighandler_t oldsh = signal(signum, handler);
    if (oldsh == SIG_ERR)
      {
	throw std::runtime_error("can't set signalhandler");
      }
    else
      {
	// remember old handler
	oldSignalHandlers.insert(std::make_pair(signum, oldsh));
      }
  }

  ~Signals()
  {
    std::for_each(oldSignalHandlers.begin(),
                  oldSignalHandlers.end(),
                  SetSig());
  }

private:
  typedef std::map<int,sighandler_t> SignalMapT;
  SignalMapT oldSignalHandlers;

  // the "why don't local classes have external linkage" position
  struct SetSig
  {
    void operator()(SignalMapT::value_type& it)
    { 
      ::signal(it.first, it.second); 
    }
  };
};
#elif defined(OS_WIN32)
BOOL signal_handler(DWORD fdwCtrlType) 
{ 
  /*switch (fdwCtrlType) 
    { 
    case CTRL_C_EVENT: 
    case CTRL_CLOSE_EVENT: 
    case CTRL_BREAK_EVENT: 
    case CTRL_LOGOFF_EVENT: 
    case CTRL_SHUTDOWN_EVENT: 
    default: */
  //std::cout<<"Signal caught!"<<std::endl;			
  if (s_controller && !s_controller->finished())
    {
      s_controller->shutDown();
    }
  return TRUE;
  //} 
} 
 
#endif

void printWelcome()
{
const char* logo = 
  "       ---             _           ---\n"
  "    ----              | |            ----\n"
  "  ----   __ _ ___ _ __| |  ___ _  __  ----\n"
  " -----  / _' | - \\ '_ \\ |_/ - \\ \\/ /  -----\n"
  "------ | (_| | --/ |_) |  \\ --/>  <   ------\n"
  " -----  \\__. | \\_| .__/ |' |\\_/ /\\ \\  -----\n"
  "  ----   ._' |\\__/ |  |_||_|__//  \\_| ----\n"
  "   ----  |__/    |_|                 ----\n"
  "      ---                          ---\n";

 std::cout << "                  welcome to...\n"
           << logo << "\n"
           << "[version:    \"" << VERSION << "\"]\n"
           << "[build time: \"" __DATE__ << " - " __TIME__ "\"]\n";
}

static std::string get_cfile_name()
{
#if defined(OS_WIN32)
  return "../gephex.conf";
#elif defined(OS_POSIX)
  const char* HOME_STR = getenv("HOME");

  if (HOME_STR == 0)
    throw std::runtime_error("Could not read $HOME");

  return std::string(HOME_STR) + "/.gephex/0.4/gephex.conf";
#endif
}

int main(int argc, const char* argv[])
{
  printWelcome();
  try
    {
#if defined(OS_POSIX)
      Signals signals;
      signals.setSignal(SIGINT,  signal_handler);
      signals.setSignal(SIGTERM, signal_handler);
      signals.setSignal(SIGABRT, signal_handler);
      signals.setSignal(SIGPIPE, signal_handler);
#elif defined(OS_WIN32) && defined(COMP_VC)
      _set_se_translator( my_se_translator );
      if (SetConsoleCtrlHandler( (PHANDLER_ROUTINE) signal_handler, TRUE) == 0)
	throw std::runtime_error("Could not set control handler!"); 
#endif

      using namespace utils;

      ConfigManager::ParamList params;

      config_param_t::ParamValue def;

      params.push_back(config_param_t("media_path",
                                   config_param_t::STRING_PARAM,
                                   "common",
                                   "List of directories that contain "
                                   "videos, images and fonts "
                                   "(separated by ';')", 0));

      params.push_back(config_param_t("graph_path",
                                      config_param_t::STRING_PARAM,
                                      "engine",
                                      "List of directories that contain "
                                      "gephex graph files (separated by ';')",
                                      0));

      params.push_back(config_param_t("module_path",
                                   config_param_t::STRING_PARAM,
                                   "engine",
                                   "Directory that contains gephex modules",
                                      0));

      def.s = "";
      params.push_back(config_param_t("frei0r_path",
				      config_param_t::STRING_PARAM,
				      "engine",
				      "Directory that contains frei0r effects",
                                      &def));

      params.push_back(config_param_t("type_path",
                                   config_param_t::STRING_PARAM,
                                   "engine",
                                   "Directory that contains gephex types",
                                      0));

      params.push_back(config_param_t("ipc_type",
                                   config_param_t::STRING_PARAM,
                                   "engine",
                                   "Communication mechanism (inet, unix, or "
                                   "namedpipe)", 0));

      params.push_back(config_param_t("ipc_port",
                                   config_param_t::INT_PARAM,
                                   "engine",
                                   "Port on which the engine listens for the "
                                   "gui", 0));

      params.push_back(config_param_t("renderer_interval",
                                   config_param_t::INT_PARAM,
                                   "engine",
                                   "The interval between two updates of the "
                                   "rendered graph (in ms)", 0));


      params.push_back(config_param_t("net_interval",
                                   config_param_t::INT_PARAM,
                                   "engine",
                                   "The interval between polling the "
                                   "connection the gui (in ms)", 0));

      def.s = "/tmp/gephex_socket";
      params.push_back(config_param_t("ipc_unix_node_prefix",
                                      config_param_t::STRING_PARAM,
                                      "engine",
                                      "Path and prefix of the unix nodes "
                                      "in the filesystem (unix only)", &def));

      def.b = false;
      params.push_back(config_param_t("autostart",
                                      config_param_t::BOOL_PARAM,
                                      "engine",
                                      "Automatically start the "
                                      "rendering", &def));


      def.s = "default";
      params.push_back(config_param_t("render_graph_id",
                                      config_param_t::STRING_PARAM,
                                      "engine",
                                      "The graph that is initially "
                                      "loaded", &def));

      params.push_back(config_param_t("render_snap_id",
                                      config_param_t::STRING_PARAM,
                                      "engine",
                                      "The snapshot that is initially "
                                      "active", &def));

      def.i = 0; // no timeout
      params.push_back(config_param_t("ttl",
                                      config_param_t::INT_PARAM,
                                      "engine",
                                      "Timeout"
                                      , &def));

      utils::ConfigManager config(get_cfile_name(), argc, argv, params);

      // If the help message was requested, we simply return
      if (config.help_requested())
	return 0;

      // This is a hack to communicate the media path to
      // loaded modules.
      static const char* GEPHEX_MEDIA_PATH = "GEPHEX_MEDIA_PATH";
      std::string media_path = config.get_string_param("media_path");

#if defined(OS_POSIX)
      int ret = setenv(GEPHEX_MEDIA_PATH, media_path.c_str(), 1);
      if (ret == -1)
#elif defined(OS_WIN32)
      BOOL ret = SetEnvironmentVariable(GEPHEX_MEDIA_PATH,
                                        media_path.c_str());
      if (ret == 0)
#endif
        throw std::runtime_error("Could not set GEPHEX_MEDIA_PATH");

      engine::Controller ctrl(config);
      s_controller = &ctrl; // publish for signalhandling
      ctrl.start();
    }
  catch (std::exception& e)
    {
      s_controller = 0;
      std::cerr << "catched known exception: " << e.what() << std::endl;
      return -1;
    }
  catch (...)
    {
      s_controller = 0;
      std::cerr << "catched unknown exception." << std::endl;
      return -1;
    }
  s_controller = 0;
  return 0;
}

// vc structured exception stuff
//-----------------------------------------------------------------

#if defined (OS_WIN32) && defined(COMP_VC)
void my_se_translator(unsigned int u, EXCEPTION_POINTERS* p)
{
	std::string msg = "Structured exception caught: ";
    switch(p->ExceptionRecord->ExceptionCode)
	{
		case EXCEPTION_ACCESS_VIOLATION: msg += "acces violation"; break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: msg += "array bounds exceeded"; break;
		case EXCEPTION_BREAKPOINT: msg += "A breakpoint was encountered. "; break;
		case EXCEPTION_DATATYPE_MISALIGNMENT: msg += "The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on. "; break;
		case EXCEPTION_FLT_DENORMAL_OPERAND: msg += "One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value. "; break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO: msg += "The thread tried to divide a floating-point value by a floating-point divisor of zero. "; break;
		case EXCEPTION_FLT_INEXACT_RESULT: msg += "The result of a floating-point operation cannot be represented exactly as a decimal fraction. "; break;
		case EXCEPTION_FLT_INVALID_OPERATION: msg += "This exception represents any floating-point exception not included in this list. "; break;
		case EXCEPTION_FLT_OVERFLOW: msg += "The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type. "; break;
		case EXCEPTION_FLT_STACK_CHECK: msg += "The stack overflowed or underflowed as the result of a floating-point operation. "; break;
		case EXCEPTION_FLT_UNDERFLOW: msg += "The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type. "; break;
		case EXCEPTION_ILLEGAL_INSTRUCTION: msg += "The thread tried to execute an invalid instruction. "; break;
		case EXCEPTION_IN_PAGE_ERROR: msg += "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network. "; break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO: msg += "The thread tried to divide an integer value by an integer divisor of zero. "; break;
		case EXCEPTION_INT_OVERFLOW: msg += "The result of an integer operation caused a carry out of the most significant bit of the result. "; break;
		case EXCEPTION_INVALID_DISPOSITION: msg += "An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception. "; break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION: msg += "The thread tried to continue execution after a noncontinuable exception occurred. "; break;
		case EXCEPTION_PRIV_INSTRUCTION: msg += "The thread tried to execute an instruction whose operation is not allowed in the current machine mode. "; break;
		case EXCEPTION_SINGLE_STEP: msg += "A trace trap or other single-instruction mechanism signaled that one instruction has been executed. "; break;
		case EXCEPTION_STACK_OVERFLOW: msg += "The thread used up its stack"; break;
		default:
			msg += "unkown exception code";
	}
			
	throw std::runtime_error(msg.c_str());
	}
#endif
