#ifndef INCLUDED_CONTROLLER_H
#define INCLUDED_CONTROLLER_H

#include "ienginecontrolreceiver.h"
#include "itypeclassnamereceiver.h"
#include "imoduleclassnamereceiver.h"
#include "itask.h"
#include "isocket.h"

#include "moduleconstructiondumbreceivernet.h"
#include "moduleclassinforeceivernet.h"
#include "moduledatareceivernet.h"
#include "controlvaluereceivernet.h"
#include "modulestatisticsreceivernet.h"
#include "moduleclassnamereceivernet.h"
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
#include "moduleclassloadercontrolsendernet.h"
#include "enginecontrolsendernet.h"

#include "autoptr.h"
#include "model.h"
#include "renderer.h"
#include "dllloader.h"
#include "scheduler.h"

#include "engineconfig.h"

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

  class AutoTypeLoader;
  class Acceptor;

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
      Controller(const EngineConfig& config);
      virtual ~Controller();
      virtual bool finished() const;
      void disconnect();
      void shutDown();
      void start();
      bool run();
  
    private:
      EngineConfig config;
      volatile bool m_finished;
      int m_port;
      CommandTagger tagger1;
      CommandTagger tagger2;
      CommandTagger tagger3;
      CommandTagger tagger4;
      CommandTagger tagger5;
      CommandTagger tagger6;
      CommandTagger tagger7;
      
      CommandTagger tagger10;
      
      CommandTagger tagger13;
      CommandTagger tagger14;      

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
      ModuleClassLoaderControlSenderNet moduleClassLoaderControlSender;
      EngineControlSenderNet engineControlSender;
    
      ModuleConstructionDumbReceiverNet moduleReceiver;
      ModuleClassInfoReceiverNet moduleClassInfoReceiver;
      ModuleDataReceiverNet moduleDataReceiver;
      ControlValueReceiverNet controlValueReceiver;
      ModuleStatisticsReceiverNet moduleStatisticsReceiver;
      ModuleClassNameReceiverNet moduleClassNameReceiver;
	
      GraphNameReceiverNet graphNameReceiver;

	
      ErrorReceiverNet errorReceiver;
	
	
      ModelStatusReceiverNet modelStatusReceiver;
      RendererStatusReceiverNet rendererStatusReceiver;
	
      utils::AutoPtr<utils::ILogger> logger;

      model::Model pModel;
      renderer::Renderer pRenderer;
      dllloader::DllLoader pDllLoader;
	
      utils::AutoPtr<AutoTypeLoader> sf;
      engine::Scheduler scheduler;

	  bool first_time;
    };

}

#endif
