#include "classinfotest.h"

#include <iostream>
#include <string>

#include "moduleclassinforeceivernet.h"
#include "moduleclassinfosendernet.h"
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


class aDummyReceiver: public IModuleClassInfoReceiver
{
public:
	aDummyReceiver() {}
	virtual void moduleClassLoaded(const std::string& mcn, const utils::Buffer&);
	virtual void moduleClassUnloaded(const std::string &);

  virtual void syncStarted() {}
  virtual void syncFinished() {}
	std::string mcname;
	utils::Buffer b;

};

void aDummyReceiver::moduleClassLoaded(const std::string& mcn, const utils::Buffer& buf)
{
	mcname = mcn;
	b = buf;
}

void aDummyReceiver::moduleClassUnloaded(const std::string& mcn)
{
  //TODO
}

std::string ClassInfoTest::getName() const
{
	return "ClassInfoTest";
}

std::string ClassInfoTest::getDescription() const
{
	return "";
}

void ClassInfoTest::pre() throw(std::runtime_error)
{
}

void ClassInfoTest::run() throw(std::runtime_error)
{
  ModuleClassInfoSenderNet mcisn;
  aDummyReceiver bla;
  MyNetProtocol np(mcisn);
  ModuleClassInfoReceiverNet mcirn(np);
		
	mcisn.registerModuleClassInfoReceiver(bla);	

  mcirn.moduleClassLoaded("testclassname",utils::Buffer("Hallo",6));
  if (bla.mcname != "testclassname" || strcmp(bla.b.getPtr(),"Hallo") != 0)
	  throw std::runtime_error("Falscher Fehler"); 
		
}	

void ClassInfoTest::post() throw(std::runtime_error)
{
}
