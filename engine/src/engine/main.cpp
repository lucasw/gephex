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

#include "engineconfig.h"
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
      _set_se_translator( my_se_translator );
      if (SetConsoleCtrlHandler( (PHANDLER_ROUTINE) signal_handler, TRUE) == 0)
	throw std::runtime_error("Could not set control handler!"); 
#endif

      engine::EngineConfig config;

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
