#include "nodelcontrolreceivertest.h"

#include <iostream>

#include "modelcontrolreceivernet.h"
#include "modelcontrolsendernet.h"
#include "net/inetprotocol.h"
#include "net/icommandinterpreter.h"
#include "utils/buffer.h"

class MyNetProtocol : public net::INetProtocol
{
private:
  net::ICommandInterpreter* cip;
public:
  MyNetProtocol(net::ICommandInterpreter& ip)
    : cip(&ip)
  {
  }

  virtual void sendCommand(const char command[4],const utils::Buffer& b)
  {
    cip->commandReceived(command,b);
  }
};


class DummyReceiver: public IModelControlReceiver
{
public:
	DummyReceiver() {}
  virtual void addModule(const std::string& moduleClassName)
  {
	  name = moduleClassName;
  }

  virtual void connectModules(int moduleID1,int outputIndex,
		       int moduleID2,int inputIndex)
  {
  }
  
  virtual void disconnectModules(int moduleID,int inputIndex)
  {
  }

  virtual void deleteModule(int moduleID)
  {
  }

  virtual void setModuleData(int moduleID,int type,const utils::Buffer& buf)
  {}

  virtual void unSetModuleData(int moduleID,int type)
  {}

  virtual void changeGraph(const std::string& name)
  {
  }

  // legt neuen gr an, alter graph bleibt aktiv
  virtual void newGraph(const std::string& name)
  {
  }

  virtual void synchronize() const
  {
  }

	std::string name;
	utils::Buffer b;

};

std::string NodelControlReceiverTest::getName() const
{
	return "NodelControlReceiverTest";
}

std::string NodelControlReceiverTest::getDescription() const
{
	return "";
}

void NodelControlReceiverTest::pre() throw(std::runtime_error)
{
}

void NodelControlReceiverTest::run() throw(std::runtime_error)
{
  ModelControlSenderNet mcsn;
  DummyReceiver bla;
  MyNetProtocol np(mcsn);
  ModelControlReceiverNet mcrn(np);
		
  mcsn.registerModelControlReceiver(bla);	

  mcrn.addModule("testname");
  if (bla.name != "testname")
	  throw std::runtime_error("Falscher Fehler"); 
		
}	

void NodelControlReceiverTest::post() throw(std::runtime_error)
{
}


