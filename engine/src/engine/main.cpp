#if defined (HAVE_CONFIG_H)
#include "config.h"
#endif

#include <iostream>
#include <stdexcept>
#include <algorithm>

#if defined(OS_WIN32)
#include "windows.h" //for Sleep and signal handling
#elif defined(OS_POSIX)
#include <signal.h>
#endif


#include "engineconfig.h"
#include "controller.h"

engine::Controller* controller;

//typedef void (*sighandler_t)(int);

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

  if (controller && !controller->finished())
    {
      controller->shutDown();
    }
} 

class Signals
{
private:
  typedef std::map<int,sighandler_t> SignalMapT;
  SignalMapT oldSignalHandlers;

  // the "why dooesnt local classes have external linkage" position
  struct SetSig
  {
    void operator()(SignalMapT::value_type& it)
    { 
      ::signal(it.first,it.second); 
    }
  };

public:
  Signals(){}
  
  void setSignal(int signum, sighandler_t handler)
  {
    SignalMapT::const_iterator it 
      = oldSignalHandlers.find(signum); 
    if (it!=oldSignalHandlers.end())
      {
	throw std::runtime_error("signalhandler is already changed");
      }
    
    sighandler_t oldsh=signal(signum,handler);
    if (oldsh==SIG_ERR)
      {
	throw std::runtime_error("can't set signalhandler");
      }
    else
      {
	// remember old handler
	oldSignalHandlers[signum]=oldsh;
      }
  }

  ~Signals()
  {
    std::for_each(oldSignalHandlers.begin(),
    	  oldSignalHandlers.end(),
    	  SetSig());
  }
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
  if (controller && !controller->finished())
    {
      controller->shutDown();
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

 std::cout << "                  welcome to..." << std::endl 
           << logo << std::endl << "(version" << VERSION << ")" << std::endl;
}

int main(int /*argc*/,char* /*argv[]*/)
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
#elif defined(OS_WIN32)
      if (SetConsoleCtrlHandler( (PHANDLER_ROUTINE) signal_handler, TRUE) == 0)
	throw std::runtime_error("Could not set control handler!"); 
#endif

      engine::EngineConfig config;

      engine::Controller ctrl(config);
      controller = &ctrl; // publish for signalhandling
      ctrl.start();
    }
  catch (std::exception& e)
    {
      std::cerr << "catched known exception: " << e.what() << std::endl;
      return -1;
    }
  catch (...)
    {
      std::cerr << "catched unknown exception." << std::endl;
      return -1;
    }
 
  return 0;
}
