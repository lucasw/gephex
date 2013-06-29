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

#include "classinfotest.h"

#include <iostream>
#include <string>

#include "moduleclassinforeceivernet.h"
#include "moduleclassinfosendernet.h"
#include "inetprotocol.h"
#include "icommandinterpreter.h"
#include "buffer.h"

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

  mcirn.moduleClassLoaded("testclassname",utils::Buffer("Hello",6));
  if (bla.mcname != "testclassname" || strcmp(bla.b.getPtr(),"Hello") != 0)
	  throw std::runtime_error("Wrong error (?)"); 
		
}	

void ClassInfoTest::post() throw(std::runtime_error)
{
}
