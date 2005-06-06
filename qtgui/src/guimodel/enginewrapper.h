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

#ifndef INCLUDED_ENGINEWRAPPER_H
#define INCLUDED_ENGINEWRAPPER_H

#include <string>

//#include "interfaces/icontrolvaluesender.h"
//#include "interfaces/imodulestatisticssender.h"

#include "utils/autoptr.h"

#include "basic_types.h"

class ModuleConstructionDumbSenderNet;
class ModuleClassInfoSenderNet;
class ModuleDataSenderNet;
class GraphDataSenderNet;
class ControlValueSenderNet;
class ModuleStatisticsSenderNet;
class GraphNameSenderNet;

class ErrorSenderNet;
class ModelStatusSenderNet;

class RendererStatusSenderNet;

class ModelControlReceiverNet;
class RendererControlReceiverNet;
class EngineControlReceiverNet;

class IControlValueSender;
class IModuleStatisticsSender;
class IGraphNameSender;

class IErrorSender;
class IModelStatusSender;

class IRendererStatusSender;

class IRendererControlReceiver;
class IEngineControlReceiver;

class IModelControlReceiver;

class IErrorReceiver;

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
		    const std::string& locator, int port,
                    IErrorReceiver& log);
      ~EngineWrapper();
		
      void connect();
      void disconnect();
		
      void checkData();

      void synchronize() const;
		
      IControlValueSender& controlValueSender();
      IModuleStatisticsSender& moduleStatisticsSender();
      IGraphNameSender& graphNameSender();

      IErrorSender& errorSender();
      IModelStatusSender& modelStatusSender();
      IRendererStatusSender& rendererStatusSender();
		
      IRendererControlReceiver& rendererControlReceiver();
      IEngineControlReceiver& engineControlReceiver();

      IModelControlReceiver& modelControlReceiver();
		
      GraphModel& graphModel();
      ControlModel& controlModel();
      ModuleClassModel& moduleClassModel();
	  utils::AutoPtr<ControlValueDispatcher> controlValueDispatcher();
		
    private:
      std::string m_ipcType;
      std::string m_locator;
      int m_port;
		
      utils::AutoPtr<ModuleConstructionDumbSenderNet> mcdsn;
      utils::AutoPtr<ModuleClassInfoSenderNet> mcisn;
      utils::AutoPtr<ModuleDataSenderNet> mdsn;
      utils::AutoPtr<GraphDataSenderNet> gdsn;
      utils::AutoPtr<ControlValueSenderNet> cvsn;
      utils::AutoPtr<ModuleStatisticsSenderNet> mssn;
      utils::AutoPtr<GraphNameSenderNet> gnsn;

      utils::AutoPtr<ErrorSenderNet> esn;
      utils::AutoPtr<ModelStatusSenderNet> mstsn;
      utils::AutoPtr<RendererStatusSenderNet> rssn;

		
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
      utils::AutoPtr<CommandTagger> tagger10;
      utils::AutoPtr<CommandTagger> tagger13;
      utils::AutoPtr<CommandTagger> tagger14;
      utils::AutoPtr<CommandTagger> tagger15;
      

      utils::AutoPtr<PortTagger> portTagger1;
      utils::AutoPtr<PortTagger> portTagger2;
      utils::AutoPtr<PortTagger> portTagger3;
      utils::AutoPtr<PortTagger> portTagger4;
      utils::AutoPtr<PortTagger> portTagger5;
      utils::AutoPtr<PortTagger> portTagger6;
      utils::AutoPtr<PortTagger> portTagger7;
      utils::AutoPtr<PortTagger> portTagger10;
      utils::AutoPtr<PortTagger> portTagger13;
      utils::AutoPtr<PortTagger> portTagger14;
      utils::AutoPtr<PortTagger> portTagger15;
      

      utils::AutoPtr<PortDispatcher> portDispatcher;
      utils::AutoPtr<PortTagger> portTagger;
      utils::AutoPtr<net::Protocol> protocol;
      
      utils::AutoPtr<net::ISocket> socket;
      utils::AutoPtr<net::SocketAdaptor> socketAdaptor;
		
      utils::AutoPtr<ModelControlReceiverNet> mcrn;
      utils::AutoPtr<RendererControlReceiverNet> rcrn;
      utils::AutoPtr<EngineControlReceiverNet> ecrn;
		
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
