#ifndef INCLUDED_ENGINEWRAPPER_H
#define INCLUDED_ENGINEWRAPPER_H

#include <string>

//#include "interfaces/icontrolvaluesender.h"
//#include "interfaces/imodulestatisticssender.h"
//#include "interfaces/imoduleclassnamesender.h"

#include "utils/autoptr.h"

#include "basic_types.h"

class ModuleConstructionDumbSenderNet;
class ModuleClassInfoSenderNet;
class ModuleDataSenderNet;
class ControlValueSenderNet;
class ModuleStatisticsSenderNet;
class ModuleClassNameSenderNet;
class GraphNameSenderNet;
class SequenceUpdateSenderNet;
class SequenceNameSenderNet;
class ErrorSenderNet;
class ModelStatusSenderNet;
class SequencerStatusSenderNet;
class RendererStatusSenderNet;

class ModelControlReceiverNet;
class RendererControlReceiverNet;
class ModuleClassLoaderControlReceiverNet;
class EngineControlReceiverNet;
class SequencerControlReceiverNet;

class IControlValueSender;
class IModuleClassNameSender;
class IModuleStatisticsSender;
class IGraphNameSender;
class ISequenceUpdateSender;
class ISequenceNameSender;
class IErrorSender;
class IModelStatusSender;
class ISequencerStatusSender;
class IRendererStatusSender;

class IModuleClassLoaderControlReceiver;
class IRendererControlReceiver;
class IEngineControlReceiver;
class ISequencerControlReceiver;
class IModelControlReceiver;

namespace net
{
  template <typename Key, class Serializer>
  class Tagger;

  template <typename Tag>
  class TagDispatcher;

  class Protocol;
  class ISocket;
  class SocketAdaptor;

  class StringTagUtil;
  class UInt32TagUtil;
}

namespace gui
{
  class GraphModel;
  class ControlModel;
  class ModuleClassModel;
  class ControlValueDispatcher;
  class ModuleDataDispatcher;

  /**
   * Die Klase EngineWrapper stellt die Interfaces bereit, die die gui von
   * der Engine braucht. Ausserdem kümmert sie sich um den ganzen
   * Netzwerkmist.
   */
  class EngineWrapper
    {
    public:
      EngineWrapper(const std::string& ipcType,
		    const std::string& locator, int port);
      ~EngineWrapper();
		
      void connect();
      void disconnect();
		
      void checkData();

      void synchronize() const;
		
      IControlValueSender& controlValueSender();
      IModuleClassNameSender& moduleClassNameSender();
      IModuleStatisticsSender& moduleStatisticsSender();
      IGraphNameSender& graphNameSender();
      ISequenceUpdateSender& sequenceUpdateSender();
      ISequenceNameSender& sequenceNameSender();
      IErrorSender& errorSender();
      IModelStatusSender& modelStatusSender();
      IRendererStatusSender& rendererStatusSender();
      ISequencerStatusSender& sequencerStatusSender();
      ISequenceNameSender& playlistNameSender();
      ISequencerStatusSender& playlistStatusSender();
      ISequenceUpdateSender& playlistUpdateSender();
		
      IModuleClassLoaderControlReceiver& moduleClassLoaderControlReceiver();
      IRendererControlReceiver& rendererControlReceiver();
      IEngineControlReceiver& engineControlReceiver();
      ISequencerControlReceiver& sequencerControlReceiver();
      ISequencerControlReceiver& playlistControlReceiver();
      IModelControlReceiver& modelControlReceiver();
		
      GraphModel& graphModel();
      ControlModel& controlModel();
      ModuleClassModel& moduleClassModel();
      ControlValueDispatcher& controlValueDispatcher();
		
    private:
      std::string m_ipcType;
      std::string m_locator;
      int m_port;
		
      utils::AutoPtr<ModuleConstructionDumbSenderNet> mcdsn;
      utils::AutoPtr<ModuleClassInfoSenderNet> mcisn;
      utils::AutoPtr<ModuleDataSenderNet> mdsn;
      utils::AutoPtr<ControlValueSenderNet> cvsn;
      utils::AutoPtr<ModuleStatisticsSenderNet> mssn;
      utils::AutoPtr<ModuleClassNameSenderNet> mcnsn;
      utils::AutoPtr<GraphNameSenderNet> gnsn;
      utils::AutoPtr<SequenceUpdateSenderNet> susn;
      utils::AutoPtr<SequenceNameSenderNet> snsn;
      utils::AutoPtr<SequenceUpdateSenderNet> plusn;
      utils::AutoPtr<ErrorSenderNet> esn;
      utils::AutoPtr<SequencerStatusSenderNet> sssn;
      utils::AutoPtr<SequencerStatusSenderNet> plssn;
      utils::AutoPtr<ModelStatusSenderNet> mstsn;
      utils::AutoPtr<RendererStatusSenderNet> rssn;
      utils::AutoPtr<SequenceNameSenderNet> plnsn;
		
      typedef net::Tagger<std::string, net::StringTagUtil> CommandTagger;
      typedef net::Tagger<uint_32, net::UInt32TagUtil> PortTagger;
      typedef net::TagDispatcher<uint_32> PortDispatcher;

      utils::AutoPtr<CommandTagger> tagger1;
      utils::AutoPtr<CommandTagger> tagger2;
      utils::AutoPtr<CommandTagger> tagger3;
      utils::AutoPtr<CommandTagger> tagger4;
      utils::AutoPtr<CommandTagger> tagger5;
      utils::AutoPtr<CommandTagger> tagger6;
      utils::AutoPtr<CommandTagger> tagger7;
      utils::AutoPtr<CommandTagger> tagger8;
      utils::AutoPtr<CommandTagger> tagger9;
      utils::AutoPtr<CommandTagger> tagger10;
      utils::AutoPtr<CommandTagger> tagger11;
      utils::AutoPtr<CommandTagger> tagger12;
      utils::AutoPtr<CommandTagger> tagger13;
      utils::AutoPtr<CommandTagger> tagger14;
      utils::AutoPtr<CommandTagger> tagger15;
      utils::AutoPtr<CommandTagger> tagger16;

      utils::AutoPtr<PortTagger> portTagger1;
      utils::AutoPtr<PortTagger> portTagger2;
      utils::AutoPtr<PortTagger> portTagger3;
      utils::AutoPtr<PortTagger> portTagger4;
      utils::AutoPtr<PortTagger> portTagger5;
      utils::AutoPtr<PortTagger> portTagger6;
      utils::AutoPtr<PortTagger> portTagger7;
      utils::AutoPtr<PortTagger> portTagger8;
      utils::AutoPtr<PortTagger> portTagger9;
      utils::AutoPtr<PortTagger> portTagger10;
      utils::AutoPtr<PortTagger> portTagger11;
      utils::AutoPtr<PortTagger> portTagger12;
      utils::AutoPtr<PortTagger> portTagger13;
      utils::AutoPtr<PortTagger> portTagger14;
      utils::AutoPtr<PortTagger> portTagger15;
      utils::AutoPtr<PortTagger> portTagger16;

      utils::AutoPtr<PortDispatcher> portDispatcher;
      utils::AutoPtr<PortTagger> portTagger;
      utils::AutoPtr<net::Protocol> protocol;
      
      utils::AutoPtr<net::ISocket> socket;
      utils::AutoPtr<net::SocketAdaptor> socketAdaptor;
		
      utils::AutoPtr<ModelControlReceiverNet> mcrn;
      utils::AutoPtr<RendererControlReceiverNet> rcrn;
      utils::AutoPtr<ModuleClassLoaderControlReceiverNet> mclcrn;
      utils::AutoPtr<EngineControlReceiverNet> ecrn;
      utils::AutoPtr<SequencerControlReceiverNet> scrn;
      utils::AutoPtr<SequencerControlReceiverNet> plcrn;
		
      utils::AutoPtr<GraphModel> gModel;
      utils::AutoPtr<ControlModel> cModel;
      utils::AutoPtr<ModuleClassModel> classModel;
		
      utils::AutoPtr<ControlValueDispatcher> dispatcher;
      utils::AutoPtr<ModuleDataDispatcher> moduleDataDispatcher;

      static void initTaggers(PortTagger& portTagger,
			      CommandTagger& commandTagger,
			      net::Protocol& protocol,
			      PortDispatcher& portDispatcher, int port);
    };
	
} // end of namespace gui

#endif
