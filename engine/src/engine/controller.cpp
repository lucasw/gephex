/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

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

#include "controller.h"

#if defined (HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_POSIX)
#include "domainserversocket.h"
#elif defined(OS_WIN32)
#include "namedpipeserversocket.h"
#endif

#include "netlogger.h"
#include "buffer.h"

#include <iostream>

namespace engine
{

  // A task that accepts one connection on a serversocket
  class Acceptor : public ITask
  {
  public:
    Acceptor(net::IServerSocket& serverSocket, net::ISocket*& socket);
    bool run();
     
  private:
    net::IServerSocket* m_serverSocket;
    net::ISocket** m_socket;
  };
  
  auto_stop_task::auto_stop_task(Controller* ctrl, unsigned int ttl)
    : m_ctrl(ctrl), m_ttl(ttl), m_time(0)
  {
  }
      
  bool auto_stop_task::run()
  {
    ++m_time;

#if (ENGINE_VERBOSITY > 0)
    if (m_ttl != 0)
      std::cout << m_time << std::endl;
#endif
    
    if (m_time == m_ttl)
      m_ctrl->shutDown();
    return true;
    
}




  // connect a porttagger and a commandtagger with their receiving
  // and sending objects
  void initTaggers(PortTagger& portTagger, CommandTagger& commandTagger,
                   net::Protocol& protocol,
                   PortDispatcher& portDispatcher, int port);

  
  void initTaggers(PortTagger& portTagger, CommandTagger& commandTagger,
                   net::Protocol& protocol,
                   PortDispatcher& portDispatcher, int port)
  {
    portTagger.registerSender(protocol);		
    portTagger.setTag(port);
    commandTagger.registerSender(portTagger);

    portDispatcher.registerListener(port, commandTagger);
  }
  
  Controller::Controller(const utils::ConfigManager& config_)
    : config(config_),
      m_finished(false),
      m_port(config.get_int_param("ipc_port")),
      tagger1(modelControlSender),      
      tagger2(rendererControlSender),        
      tagger3(engineControlSender),
      tagger4(modelControlSender),
      tagger5(modelControlSender),
      tagger7(modelControlSender),

      tagger10(modelControlSender),
      
      tagger13(modelControlSender),
      tagger14(modelControlSender),
      tagger15(modelControlSender),

      portTagger(portDispatcher),
      protocol(portTagger),
      socket(0),
      netPoller(protocol, connection_down),

      moduleReceiver(tagger1),
      moduleClassInfoReceiver(tagger2),
      moduleDataReceiver(tagger3),
      graphDataReceiver(tagger15),
      controlValueReceiver(tagger4),
      moduleStatisticsReceiver(tagger5),
      graphNameReceiver(tagger7),      

      errorReceiver(tagger10),

      modelStatusReceiver(tagger13),
      rendererStatusReceiver(tagger14),

      logger(new engine::NetLogger(errorReceiver)),

      pModel(config.get_string_param("graph_path"), logger),
      pRenderer(logger),
      first_time(true),
      ttl(config.get_int_param("ttl")),
      auto_stop(this,ttl)
  {
    net::IServerSocket* serverSocket;

    std::string ipcType = config.get_string_param("ipc_type");
    
    if (ipcType == "inet")
      {
#if (ENGINE_VERBOSITY > 0)
	std::cout << "IPC type: inet" << std::endl;
	std::cout << "Opening serverSocket on port " << m_port << std::endl;
#endif
	serverSocket = new net::TCPServerSocket(m_port);
      }
#if defined(OS_POSIX)
    else if (ipcType == "unix")
      {
	std::string nodePrefix 
	  = config.get_string_param("ipc_unix_node_prefix");
							 
#if (ENGINE_VERBOSITY > 0)
	std::cout << "IPC type: unix" << std::endl;
	std::cout << "Opening serverSocket on " << nodePrefix << ", "
		  << "port = " << m_port << std::endl;
#endif
 	serverSocket = new net::DomainServerSocket(nodePrefix, m_port);
      }
#elif defined(OS_WIN32)
    else if (ipcType == "namedpipe")
      {		
#if (ENGINE_VERBOSITY > 0)
	std::cout << "IPC type: namedpipe" << std::endl;
	std::cout << "Opening serverSocket on port " << m_port << std::endl;
#endif
	serverSocket = new net::NamedPipeServerSocket(m_port);
      }
#endif
    else
      {
	throw std::runtime_error("Unsupported or missing ipc type");
      }


    m_serverSocket = utils::AutoPtr<net::IServerSocket>(serverSocket);

    acceptor = utils::AutoPtr<Acceptor>(new Acceptor(*m_serverSocket, socket));

    bufferedSender = utils::AutoPtr<BufferedSender>(new BufferedSender());
    protocol.registerSender(&*bufferedSender);
    netPoller.set_sender(&*bufferedSender);

    initTaggers(portTagger1, tagger1, protocol, portDispatcher, m_port);
    initTaggers(portTagger2, tagger2, protocol, portDispatcher, m_port+1);
    initTaggers(portTagger3, tagger3, protocol, portDispatcher, m_port+2);
    initTaggers(portTagger4, tagger4, protocol, portDispatcher, m_port+3);
    initTaggers(portTagger5, tagger5, protocol, portDispatcher, m_port+4);
    initTaggers(portTagger7, tagger7, protocol, portDispatcher, m_port+6);
    initTaggers(portTagger10, tagger10, protocol, portDispatcher, m_port+9);
    initTaggers(portTagger13, tagger13, protocol, portDispatcher, m_port+12);
    initTaggers(portTagger14, tagger14, protocol, portDispatcher, m_port+13);
    initTaggers(portTagger15, tagger15, protocol, portDispatcher, m_port+14);

    pModel.registerModuleConstructionSmartReceiver(pRenderer);
    pModel.registerModuleConstructionDumbReceiver(moduleReceiver);
    pModel.registerModuleDataReceiver(moduleDataReceiver);
    pModel.registerGraphNameReceiver(graphNameReceiver);
    pModel.registerRendererControlReceiver(pRenderer);
    pModel.registerControlValueReceiver(controlValueReceiver);
    pModel.registerModuleStatisticsReceiver(moduleStatisticsReceiver);
    pModel.registerModelStatusReceiver(modelStatusReceiver);

    pModel.registerGraphDataReceiver(graphDataReceiver);
		
    pRenderer.registerSmartControlValueReceiver(pModel);
    pRenderer.registerModuleStatisticsSmartReceiver(pModel);
    pRenderer.registerRendererStatusReceiver(rendererStatusReceiver);
		
    modelControlSender.registerModelControlReceiver(pModel);
    rendererControlSender.registerRendererControlReceiver(pRenderer);

    engineControlSender.registerEngineControlReceiver(*this);

    int rendererInterval = config.get_int_param("renderer_interval");
    int netInterval = config.get_int_param("net_interval");

    scheduler.addTask(*acceptor, 500);
    scheduler.addTask(*this,250);
    scheduler.addTask(netPoller,netInterval);

    std::list<ITask*> t_list;
    t_list.push_back(&auto_stop);
    t_list.push_back(&pRenderer);
    
    augmented_render_task =
      utils::AutoPtr<synced_tasks>(new synced_tasks(t_list));
    
    scheduler.addTask(*augmented_render_task,rendererInterval);

    // load plugins
    pDllLoader= utils::AutoPtr<dllloader::DllLoader>
      (new dllloader::DllLoader(logger,
		     moduleClassInfoReceiver,
		     pModel,
		     pRenderer,
		     pRenderer,
		     config.get_string_param("module_path"),
		     config.get_string_param("type_path"),
		     config.get_string_param("frei0r_path")));

#if (ENGINE_VERBOSITY > 0)
        std::cout << "Reading graphs...";
    std::cout.flush();
#endif
    pModel.updateFileSystem();
#if (ENGINE_VERBOSITY > 0)
    std::cout << "   done\n";
#endif
    std::string render_graph_id=config.get_string_param("render_graph_id");
    std::string render_snap_id =config.get_string_param("render_snap_id");

    //create graph and snapshot if they don't already exist
    if( !pModel.check_for_graph_id(render_graph_id) )
      {
#if (ENGINE_VERBOSITY > 0)
	std::cout << "create new graph: " << render_graph_id << std::endl;
#endif
	pModel.newGraphWithID(render_graph_id, render_graph_id, false);
      }
	
    if( !pModel.check_for_snap_id(render_graph_id,render_snap_id) )
      {
#if (ENGINE_VERBOSITY > 0)
	std::cout << "create new snap: " << render_graph_id << " "
		  << render_snap_id << std::endl;
#endif
	pModel.newControlValueSetWithID(render_graph_id,
					render_snap_id,
					render_snap_id);
      }
				    
    // activate the graph/snapshot combination
    pModel.changeRenderedGraph(render_graph_id, 
			       render_snap_id);
    
    pModel.changeEditGraph(render_graph_id, 
			   render_snap_id);

    
    // start the render if option is set or if in timeout mode
    if (config.get_bool_param("autostart") || ttl != 0)
      pRenderer.start();
  }
	
  Controller::~Controller()
  {
    try
      {
	disconnect();
      }
    catch (std::runtime_error& e)
      {
	std::cerr << "Error during cleanup: " << e.what() << std::endl;
      }
    catch (...)
      {
	std::cerr << "Unknown error during cleanup " << std::endl;
      }
  }
	
  bool Controller::finished() const
  {
    return m_finished;
  }
	
  void Controller::disconnect()
  {
    if (socket != 0)
      {
#if (ENGINE_VERBOSITY > 0)
        std::cout << "connection down\n";
#endif
        delete socket;
        socket = 0;			  
        first_time = true;
        netPoller.set_socket(0);
        bufferedSender->disable();
        protocol.reset();
      }
  }

  void Controller::shutDown()
  {
    m_finished = true;
    scheduler.stop();
  }

  void Controller::start()
  {
    while (!m_finished)
      {
	try 
	  {
	    scheduler.run();
	  }
	catch (std::runtime_error& e)
	  {
	    logger->error("Engine Exception Handler", e.what());
	  }
      }
  }
  
  bool Controller::run()
  {
    try 
      {
        // here comes what happens after the connection to the gui is
        // established
        if (socket != 0 && first_time)
          {
#if (ENGINE_VERBOSITY > 0)
            std::cout << "connection up\n";
#endif
            netPoller.set_socket(socket);
            bufferedSender->enable();			  
			  
            connection_down = false;			  
            first_time = false;

	    // announce loaded plugins
	    pDllLoader->synchronize();
          }

        if (connection_down && !first_time)
          {
            disconnect();	  
          }
      }
    catch (std::runtime_error& e)
      {
        logger->error("Engine Exception Handler", e.what());
        return false;
      }
		
    return true;
  }

  Acceptor::Acceptor(net::IServerSocket& serverSocket, net::ISocket*& socket)
    : m_serverSocket(&serverSocket), m_socket(&socket)
  {
    m_serverSocket->setSoTimeout(0);
    m_serverSocket->listen();
  }

  bool Acceptor::run()
  {
    if (*m_socket == 0)
      {
        *m_socket = m_serverSocket->accept();
        if (*m_socket != 0)
          {
            (*m_socket)->setSoTimeout(0);	
          }
      }

    return true;
  }

  NetPoller::NetPoller(net::IDataListener& listener, 
                       bool& connection_down)
    : m_socket(0), m_listener(listener), m_buffered_sender(0),
      m_connection_down(connection_down)
  {
    m_connection_down = false;
  }

  void NetPoller::set_socket(net::ISocket* socket)
  {
    m_socket = socket;
  }

  void NetPoller::set_sender(BufferedSender* bsender)
  {
    m_buffered_sender = bsender;
  }

  static int min_(int a, int b)
  {
    return (a < b) ? a : b;
  }

  bool NetPoller::run() 
  {
    if (m_connection_down || m_socket == 0)
      return true;

    try {
      // first send data from the bufferedsender

      if (m_buffered_sender != 0)
        {			 
          int max_size = 20000;
          int bytes_left = m_buffered_sender->len();
          int len = min_(bytes_left, max_size);
          
          if (len > 0)
            m_socket->send(m_buffered_sender->consume(len));
	  }

      // now receive data
      utils::Buffer b;
      m_socket->receive(b);
      m_listener.dataReceived(b);
    }
    catch(...)
      {
        m_connection_down = true;
      }
    return true;
  }
}
