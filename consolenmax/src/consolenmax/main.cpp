#include <iostream>
#include <string>
#include <sstream>

#include "net/netprotocol.h"
#include "net/netstream.h"
#include "net/icommandinterpreter.h"
#include "net/commandmux.h"
#include "thread/irunnable.h"

#include "utils/buffer.h"


#include "thread/thread.h"

#ifdef LINUX
//#include "thread/threadposix.h"

#endif
//#ifdef WIN32
//#include "thread/threadwindows.h"
//#endif

class Listener : public net::ICommandInterpreter
{
public:

  virtual void commandReceived(const std::string&,const utils::Buffer& b)
  {
    std::cout << b.getPtr() << std::endl;
  }

  /*  virtual std::string getCommand() const
  {
    return "____";
    }*/
};

class Net : public thread::IRunnable
{
  net::NetStream* ns;
public:
  Net(net::NetStream& _ns) : ns(&_ns) {}

  virtual void run()
  {
    /*
#ifdef LINUX
    thread::IThreadUtil* tu = new thread::ThreadUtilPOSIX();
#endif
#ifdef WIN32
    thread::IThreadUtil* tu = new thread::ThreadUtilWINDOWS();
#endif
    */
    while (true)
      {
	ns->checkData(10000);
	//tu->sleep((int) 1e5);
      }
  }
};

int main (int argc, char* argv[])
{

  std::string host = "localhost";
  int port = 7777;
  if (argc >= 2)
    {
      host = argv[1];
    }
  if (argc >= 3)
    {
	  std::istringstream is(argv[2]);
      is >> port;
    }

  std::cout << "host = " << host << std::endl;
  std::cout << "port = " << port << std::endl;

  net::CommandMux cmux;
  net::NetProtocol np(cmux);
  net::NetStream ns(1234,np,false);
  np.setSender(ns);

  Listener l;
  cmux.setDefaultCommandListener(l);

  Net netListener(ns);
  
  try 
    {
      ns.connectTo(host,port);
    }
  catch (std::runtime_error& e)
    {
      std::cerr << "Error while connecting: " << e.what() << std::endl;
      return -1;
    }

  //#ifdef LINUX
  //  thread::IThread* thread = new thread::ThreadPOSIX(netListener);
  //#endif
  //#ifdef WIN32
  //  thread::IThread* thread = new thread::ThreadWINDOWS(netListener);
  //#endif

  thread::IThread* thread = new thread::Thread(netListener);

  thread->start();

  const int BUF_LEN = 1024;
  char buf[BUF_LEN];
	
  bool stop = false;
  while (std::cin.getline(buf,BUF_LEN) && !stop)
    {
      std::istringstream line(buf);
		
      std::string command;
      line >> command;
      
      std::string data;
      std::string tmp;
      while (line >> tmp) {data += " " + tmp;}
      np.sendCommand(command.c_str(),utils::Buffer(data.c_str(),data.length()+1));
    }
  return 0;
}
