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

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "enginewrapper.h"

#include "netinterfaces/controlvaluesendernet.h"
#include "netinterfaces/modulestatisticssendernet.h"
#include "netinterfaces/moduleclassinfosendernet.h"
#include "netinterfaces/moduledatasendernet.h"
#include "netinterfaces/graphdatasendernet.h"
#include "netinterfaces/moduleconstructiondumbsendernet.h"
#include "netinterfaces/graphnamesendernet.h"
#include "netinterfaces/rendererstatussendernet.h"

#include "netinterfaces/errorsendernet.h"
#include "netinterfaces/modelstatussendernet.h"

#include "netinterfaces/modelcontrolreceivernet.h"
#include "netinterfaces/modelcontrolreceivernet.h"
#include "netinterfaces/renderercontrolreceivernet.h"
#include "netinterfaces/enginecontrolreceivernet.h"

#include "net/isocket.h"
#include "net/protocol.h"
#include "net/tagger.h"
#include "net/tagutils.h"
#include "net/tagdispatcher.h"
#include "net/socketadaptor.h"

#include "net/tcpclientsocket.h"
#if defined(OS_POSIX)
#include "net/domainclientsocket.h"
#elif defined(OS_WIN32)
#include "net/namedpipeclientsocket.h"
#endif


#include "graphmodel.h"
#include "controlmodel.h"
#include "moduleclassmodel.h"
#include "controlvaluedispatcher.h"
#include "moduledatadispatcher.h"

namespace gui
{
  EngineWrapper::EngineWrapper(const std::string& ipcType,
			       const std::string& locator, int port,
                               IErrorReceiver& log)
    : m_ipcType(ipcType), m_locator(locator), m_port(port),
      mcdsn(new ModuleConstructionDumbSenderNet()), 
      mcisn(new ModuleClassInfoSenderNet()),
      mdsn(new ModuleDataSenderNet()),
      gdsn(new GraphDataSenderNet()),
      cvsn(new ControlValueSenderNet()),
      mssn(new ModuleStatisticsSenderNet()),
      gnsn(new GraphNameSenderNet()),
      esn(new ErrorSenderNet()),
      mstsn(new ModelStatusSenderNet()),
      rssn(new RendererStatusSenderNet()),      

      tagger1(new CommandTagger(*mcdsn)), 
      tagger2(new CommandTagger(*mcisn)),
      tagger3(new CommandTagger(*mdsn)),
      tagger4(new CommandTagger(*cvsn)),
      tagger5(new CommandTagger(*mssn)),
      tagger7(new CommandTagger(*gnsn)),
      tagger10(new CommandTagger(*esn)),      
      tagger13(new CommandTagger(*mstsn)),
      tagger14(new CommandTagger(*rssn)),
      tagger15(new CommandTagger(*gdsn)),


      portTagger1(new PortTagger()),
      portTagger2(new PortTagger()),
      portTagger3(new PortTagger()),
      portTagger4(new PortTagger()),
      portTagger5(new PortTagger()),
      portTagger7(new PortTagger()),
      portTagger10(new PortTagger()),      
      portTagger13(new PortTagger()),
      portTagger14(new PortTagger()),
      portTagger15(new PortTagger()),


      portDispatcher(new PortDispatcher()),
      portTagger(new PortTagger(*portDispatcher)),
      protocol(new net::Protocol(*portTagger)),
      socket(0),
      socketAdaptor(new net::SocketAdaptor()),

      mcrn(new ModelControlReceiverNet(*tagger1)),
      rcrn(new RendererControlReceiverNet(*tagger2)),
      ecrn(new EngineControlReceiverNet(*tagger3)),
      
      gModel(new GraphModel(*mcrn)), 
      cModel(new ControlModel(*mcrn, log)),
      classModel(new ModuleClassModel()),
      dispatcher(new ControlValueDispatcher(*mcrn)),
      moduleDataDispatcher(new ModuleDataDispatcher(*gModel,*cModel))
  {

    socketAdaptor->registerDataListener(*protocol);

    initTaggers(*portTagger1, *tagger1, *protocol, *portDispatcher, m_port);
    initTaggers(*portTagger2, *tagger2, *protocol, *portDispatcher, m_port+1);
    initTaggers(*portTagger3, *tagger3, *protocol, *portDispatcher, m_port+2);
    initTaggers(*portTagger4, *tagger4, *protocol, *portDispatcher, m_port+3);
    initTaggers(*portTagger5, *tagger5, *protocol, *portDispatcher, m_port+4);
    initTaggers(*portTagger7, *tagger7, *protocol, *portDispatcher, m_port+6);
    initTaggers(*portTagger10,*tagger10,*protocol, *portDispatcher, m_port+9);
    initTaggers(*portTagger13,*tagger13,*protocol, *portDispatcher, m_port+12);
    initTaggers(*portTagger14,*tagger14,*protocol, *portDispatcher, m_port+13);
    initTaggers(*portTagger15,*tagger15,*protocol, *portDispatcher, m_port+14);

		
    mcisn->registerModuleClassInfoReceiver(*classModel);
    mcdsn->registerModuleConstructionDumbReceiver(*gModel);
    mdsn->registerModuleDataReceiver(*moduleDataDispatcher);
    cvsn->registerControlValueReceiver(*dispatcher);
    gdsn->registerGraphDataReceiver(*cModel);
  }
	
	
  EngineWrapper::~EngineWrapper()
  {
  }
	
  void EngineWrapper::connect()
  {
    typedef utils::AutoPtr<net::IClientSocket> ClientSocketPtr;
    if (socket == 0)
      {
	ClientSocketPtr clientSocket;
	if (m_ipcType == "inet")
	  {
	    clientSocket = ClientSocketPtr(new net::TCPClientSocket());
	  }
#if defined(OS_POSIX)
	else if (m_ipcType == "unix")
	  {
            clientSocket = ClientSocketPtr(new net::DomainClientSocket());
	  }
#elif defined(OS_WIN32)
	else if (m_ipcType == "namedpipe")
          {
            clientSocket = ClientSocketPtr(new net::NamedPipeClientSocket());
          }
#endif
	else
	{
	    throw std::runtime_error("Unknown ipcType '" + m_ipcType + "' at "
				     "EngineWrapper::connect()");
	  }

	//set to blocking...
	clientSocket->setSoTimeout(-1);

	net::ISocket* s = clientSocket->connect(m_locator, m_port);

	if (s == 0)
		throw std::runtime_error("Could not connect");

    socket = utils::AutoPtr<net::ISocket>(s);
    socket->setSoTimeout(0);
    protocol->registerSender(&*socket);
    socketAdaptor->setSocket(&*socket);
    synchronize();
      }
  }
	
  void EngineWrapper::disconnect()
  {
    dispatcher->clear();
    ecrn->disconnect();
    protocol->reset();

    //netDispatcher->disconnect();
    //TODO
    socket = utils::AutoPtr<net::ISocket>(0);
  }

  void EngineWrapper::checkData()
  {
    if (socket)
      {
        int num_tries = 100;
        int data_left;

        do
          {
            data_left = socketAdaptor->run();
            --num_tries;
          } while (data_left && num_tries > 0);
      }
  }

  void EngineWrapper::synchronize() const
  {
    mcrn->synchronize();
    rcrn->synchronize();
  }
	
  IControlValueSender& EngineWrapper::controlValueSender()
  {
    return *cvsn;
  }
	
  IModuleStatisticsSender& EngineWrapper::moduleStatisticsSender()
  {
    return *mssn;
  }

  IGraphNameSender& EngineWrapper::graphNameSender()
  {
    return *gnsn;
  }


  IErrorSender& EngineWrapper::errorSender()
  {
    return *esn;
  }

  IModelStatusSender& EngineWrapper::modelStatusSender()
  {
    return *mstsn;
  }

  IRendererStatusSender& EngineWrapper::rendererStatusSender()
  {
    return *rssn;
  }

  IRendererControlReceiver& EngineWrapper::rendererControlReceiver()
  {
    return *rcrn;
  }

  IEngineControlReceiver& EngineWrapper::engineControlReceiver()
  {
    return *ecrn;
  }

  
  IModelControlReceiver& EngineWrapper::modelControlReceiver()
  {
    return *mcrn;
  }
	
  GraphModel& EngineWrapper::graphModel()
  {
    return *gModel;
  }
	
  ControlModel& EngineWrapper::controlModel()
  {
    return *cModel;
  }
	
  ModuleClassModel& EngineWrapper::moduleClassModel()
  {
    return *classModel;
  }
	
  utils::AutoPtr<ControlValueDispatcher> EngineWrapper::controlValueDispatcher()
  {
    return dispatcher;
  }

  void EngineWrapper::initTaggers(PortTagger& portTagger,
				  CommandTagger& commandTagger,
				  net::Protocol& protocol,
				  PortDispatcher& portDispatcher, int port)
  {
    portTagger.registerSender(protocol);		
    portTagger.setTag(port);
    commandTagger.registerSender(portTagger);

    portDispatcher.registerListener(port, commandTagger);
  }

	
} // end of namespace gui
