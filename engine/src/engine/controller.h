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
#include "sequenceupdatereceivernet.h"
#include "sequencenamereceivernet.h"
#include "errorreceivernet.h"
#include "rendererstatusreceivernet.h"

#include "buffer.h"
#include "tagger.h"
#include "tagutils.h"
#include "protocol.h"
#include "tagdispatcher.h"
#include "socketadaptor.h"

#include "tcpserversocket.h"

#include "modelcontrolsendernet.h"
#include "renderercontrolsendernet.h"
#include "moduleclassloadercontrolsendernet.h"
#include "enginecontrolsendernet.h"
#include "sequencercontrolsendernet.h"
#include "sequencerstatusreceivernet.h"

#include "autoptr.h"
#include "model.h"
#include "renderer.h"
#include "dllloader.h"
#include "sequencer.h"
#include "scheduler.h"

#include "engineconfig.h"

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
      NetPoller(net::SocketAdaptor& adaptor);
      bool run(); 
    private:
      net::SocketAdaptor* m_adaptor;
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
      CommandTagger tagger8;
      CommandTagger tagger9;
      CommandTagger tagger10;
      CommandTagger tagger11;
      CommandTagger tagger12;
      CommandTagger tagger13;
      CommandTagger tagger14;
      CommandTagger tagger15;
      CommandTagger tagger16;

      PortTagger portTagger1;
      PortTagger portTagger2;
      PortTagger portTagger3;
      PortTagger portTagger4;
      PortTagger portTagger5;
      PortTagger portTagger6;
      PortTagger portTagger7;
      PortTagger portTagger8;
      PortTagger portTagger9;
      PortTagger portTagger10;
      PortTagger portTagger11;
      PortTagger portTagger12;
      PortTagger portTagger13;
      PortTagger portTagger14;
      PortTagger portTagger15;
      PortTagger portTagger16;

      utils::AutoPtr<net::IServerSocket> m_serverSocket;
  
      PortDispatcher portDispatcher;
      PortTagger portTagger;
      net::Protocol protocol;

      net::ISocket* socket;
      net::SocketAdaptor socketAdaptor;
      utils::AutoPtr<Acceptor> acceptor;
      NetPoller netPoller;
	
      ModelControlSenderNet modelControlSender;
      RendererControlSenderNet rendererControlSender;
      ModuleClassLoaderControlSenderNet moduleClassLoaderControlSender;
      EngineControlSenderNet engineControlSender;
      SequencerControlSenderNet sequencerControlSender;
      SequencerControlSenderNet playlistControlSender;
    
      ModuleConstructionDumbReceiverNet moduleReceiver;
      ModuleClassInfoReceiverNet moduleClassInfoReceiver;
      ModuleDataReceiverNet moduleDataReceiver;
      ControlValueReceiverNet controlValueReceiver;
      ModuleStatisticsReceiverNet moduleStatisticsReceiver;
      ModuleClassNameReceiverNet moduleClassNameReceiver;
	
      GraphNameReceiverNet graphNameReceiver;
      SequenceUpdateReceiverNet sequenceUpdateReceiver;
      SequenceNameReceiverNet sequenceNameReceiver;
	
      ErrorReceiverNet errorReceiver;
	
      SequenceUpdateReceiverNet playlistUpdateReceiver;
      SequenceNameReceiverNet playlistNameReceiver;  
	
      ModelStatusReceiverNet modelStatusReceiver;
      RendererStatusReceiverNet rendererStatusReceiver;
      SequencerStatusReceiverNet sequencerStatusReceiver;
      SequencerStatusReceiverNet playlistStatusReceiver;
	
      utils::AutoPtr<utils::ILogger> logger;

      model::Model pModel;
      renderer::Renderer pRenderer;
      dllloader::DllLoader pDllLoader;
      sequencer::Sequencer pSequencer;
      sequencer::Sequencer pPlayList;
	
      utils::AutoPtr<AutoTypeLoader> sf;
      engine::Scheduler scheduler;
    };

}

#endif
