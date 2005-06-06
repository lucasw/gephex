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

#ifndef INCLUDED_CONTROLLER_H
#define INCLUDED_CONTROLLER_H

#include "ienginecontrolreceiver.h"
#include "itask.h"
#include "isocket.h"

#include "moduleconstructiondumbreceivernet.h"
#include "moduleclassinforeceivernet.h"
#include "moduledatareceivernet.h"
#include "graphdatareceivernet.h"
#include "controlvaluereceivernet.h"
#include "modulestatisticsreceivernet.h"
#include "modelstatusreceivernet.h"
#include "graphnamereceivernet.h"
#include "errorreceivernet.h"
#include "rendererstatusreceivernet.h"

#include "buffer.h"
#include "tagger.h"
#include "tagutils.h"
#include "protocol.h"
#include "tagdispatcher.h"

#include "tcpserversocket.h"

#include "modelcontrolsendernet.h"
#include "renderercontrolsendernet.h"
#include "enginecontrolsendernet.h"

#include "autoptr.h"
#include "model.h"
#include "renderer.h"
#include "dllloader.h"
#include "scheduler.h"
#include "synced_tasks.h"

#include "configmanager.h"

#include "bufferedsender.h"

namespace utils
{
  class ILogger;
}

namespace engine
{
  typedef net::Tagger<std::string, net::StringTagUtil> CommandTagger;
  typedef net::Tagger<uint_32, net::UInt32TagUtil> PortTagger;
  typedef net::TagDispatcher<uint_32> PortDispatcher;

  class Acceptor;
  class Controller;

  class auto_stop_task: public ITask
    {
    public:
      auto_stop_task(Controller* ctrl, unsigned int ttl);
      bool run();
    private:
      Controller* m_ctrl;
      unsigned int m_time;
      unsigned int m_ttl;
    };
  
  class NetPoller : public ITask
    {
    public:
		NetPoller(net::IDataListener& p, bool& connection_down);

	  void set_socket(net::ISocket* socket);
	  void set_sender(BufferedSender* sender);

      bool run(); 
    private:
      net::ISocket* m_socket;
	  net::IDataListener& m_listener;
	  BufferedSender* m_buffered_sender;
	  bool& m_connection_down;
    };

  class Controller : public IEngineControlReceiver, public ITask
    {
    public:
      Controller(const utils::ConfigManager& config);
      virtual ~Controller();
      virtual bool finished() const;
      void disconnect();
      void shutDown();
      void start();
      bool run();
  
    private:
      utils::ConfigManager config;
      volatile bool m_finished;
      int m_port;
      CommandTagger tagger1;
      CommandTagger tagger2;
      CommandTagger tagger3;
      CommandTagger tagger4;
      CommandTagger tagger5;
      CommandTagger tagger7;
      
      CommandTagger tagger10;
      
      CommandTagger tagger13;
      CommandTagger tagger14;
      CommandTagger tagger15;

      PortTagger portTagger1;
      PortTagger portTagger2;
      PortTagger portTagger3;
      PortTagger portTagger4;
      PortTagger portTagger5;
      PortTagger portTagger6;
      PortTagger portTagger7;
      
      PortTagger portTagger10;
      
      PortTagger portTagger13;
      PortTagger portTagger14;
      PortTagger portTagger15;

      utils::AutoPtr<net::IServerSocket> m_serverSocket;
  
      PortDispatcher portDispatcher;
      PortTagger portTagger;
      net::Protocol protocol;

      net::ISocket* socket;      
      utils::AutoPtr<Acceptor> acceptor;
	  utils::AutoPtr<BufferedSender> bufferedSender;

	  bool connection_down;
      NetPoller netPoller;
	
      ModelControlSenderNet modelControlSender;
      RendererControlSenderNet rendererControlSender;
      EngineControlSenderNet engineControlSender;
    
      ModuleConstructionDumbReceiverNet moduleReceiver;
      ModuleClassInfoReceiverNet moduleClassInfoReceiver;
      ModuleDataReceiverNet moduleDataReceiver;
      GraphDataReceiverNet graphDataReceiver;
      ControlValueReceiverNet controlValueReceiver;
      ModuleStatisticsReceiverNet moduleStatisticsReceiver;
	
      GraphNameReceiverNet graphNameReceiver;
	
      ErrorReceiverNet errorReceiver;
		
      ModelStatusReceiverNet modelStatusReceiver;
      RendererStatusReceiverNet rendererStatusReceiver;
	
      utils::AutoPtr<utils::ILogger> logger;

      model::Model pModel;

      utils::AutoPtr<dllloader::DllLoader> pDllLoader;
      renderer::Renderer pRenderer;
      
      utils::AutoPtr<synced_tasks> augmented_render_task;
      engine::Scheduler scheduler;

      bool first_time;
      unsigned int ttl;
      auto_stop_task auto_stop;
    };

}

#endif
