#include "controller.h"

#include <iostream>

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
#include "filesystem.h"



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
  
  /**
   * Just a hack to automatically load all types that exist.
   */
class AutoTypeLoader : public ITypeClassNameReceiver
{
public:
  AutoTypeLoader(ITypeClassLoaderControlReceiver& typLoader)
    : m_typLoader(typLoader)
    {
    }
  
  void typeClassNameExists(const std::string& name)
    {
      m_typLoader.loadTypeClass(name);
    }
 private:
  ITypeClassLoaderControlReceiver& m_typLoader;
};



/**
 * Returns a vector of all files in a directory, that have a certain
 * file ending.
 */
std::vector<std::string> getFilesInDir(const std::string& dirName,
				       const std::string& ending);

// connect a porttagger and a commandtagger with their receiving
// and sending objects
 void initTaggers(PortTagger& portTagger, CommandTagger& commandTagger,
		  net::Protocol& protocol,
		  PortDispatcher& portDispatcher, int port);




#if defined(OS_WIN32)
const std::string MODULE_ENDING = ".dll";
const std::string TYPE_ENDING = ".dll";
#elif defined(OS_POSIX)
const std::string MODULE_ENDING = ".so";
const std::string TYPE_ENDING = ".so";
#else
#error "unknown OS"
#endif



  std::vector<std::string> getFilesInDir(const std::string& dirName,
					 const std::string& ending)
  {
    std::list<utils::DirEntry> entries;
    utils::FileSystem::listDir(dirName, entries);
    
    std::vector<std::string> fileNames;
    
    for (std::list<utils::DirEntry>::const_iterator it = entries.begin();
	 it != entries.end(); ++it)
    {
      std::string name = it->getName();
      
      if (name.length() > ending.length() 
	  && name.substr(name.length()-ending.length(),
			 ending.length()) == ending)
	
	fileNames.push_back(dirName + name);
    }
    
    return fileNames;
  }
  
void initTaggers(PortTagger& portTagger, CommandTagger& commandTagger,
			net::Protocol& protocol,
			PortDispatcher& portDispatcher, int port)
{
  portTagger.registerSender(protocol);		
  portTagger.setTag(port);
  commandTagger.registerSender(portTagger);

  portDispatcher.registerListener(port, commandTagger);
}
  
  Controller::Controller(const EngineConfig& config_)
    : m_finished(false),
      config(config_),
      m_port(config.port),      
      tagger1(modelControlSender),      
      tagger2(rendererControlSender),        
      tagger3(engineControlSender),
      tagger4(modelControlSender),
      tagger5(modelControlSender),
      tagger6(moduleClassLoaderControlSender),
      tagger7(modelControlSender),
      tagger8(sequencerControlSender),
      tagger9(playlistControlSender),
      tagger10(modelControlSender),
      tagger11(modelControlSender),
      tagger12(modelControlSender),
      tagger13(modelControlSender),
      tagger14(modelControlSender),
      tagger15(modelControlSender),
      tagger16(modelControlSender),

      portTagger(portDispatcher),
      protocol(portTagger),
      socket(0),
      netPoller(socketAdaptor),
		
      moduleReceiver(tagger1),
      moduleClassInfoReceiver(tagger2),
      moduleDataReceiver(tagger3),
      controlValueReceiver(tagger4),
      moduleStatisticsReceiver(tagger5),
      moduleClassNameReceiver(tagger6),
      graphNameReceiver(tagger7),
      sequenceUpdateReceiver(tagger8),
      sequenceNameReceiver(tagger9),
      errorReceiver(tagger10),
      playlistUpdateReceiver(tagger11),
      playlistNameReceiver(tagger12),
      modelStatusReceiver(tagger13),
      rendererStatusReceiver(tagger14),
      sequencerStatusReceiver(tagger15),
	  logger(new engine::NetLogger(errorReceiver)),

      playlistStatusReceiver(tagger16),
      pModel(config.graphDir),
      pRenderer(logger),
      pDllLoader(logger),
      pSequencer(config.sequDir),
      pPlayList(config.plDir)

  {
    
    net::IServerSocket* serverSocket;

    std::string ipcType = config.ipcType;
    
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
	  = config.ipcUnixNodePrefix;
							 
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

    socketAdaptor.registerDataListener(protocol);

    initTaggers(portTagger1, tagger1, protocol, portDispatcher, m_port);
    initTaggers(portTagger2, tagger2, protocol, portDispatcher, m_port+1);
    initTaggers(portTagger3, tagger3, protocol, portDispatcher, m_port+2);
    initTaggers(portTagger4, tagger4, protocol, portDispatcher, m_port+3);
    initTaggers(portTagger5, tagger5, protocol, portDispatcher, m_port+4);
    initTaggers(portTagger6, tagger6, protocol, portDispatcher, m_port+5);
    initTaggers(portTagger7, tagger7, protocol, portDispatcher, m_port+6);
    initTaggers(portTagger8, tagger8, protocol, portDispatcher, m_port+7);
    initTaggers(portTagger9, tagger9, protocol, portDispatcher, m_port+8);
    initTaggers(portTagger10, tagger10, protocol, portDispatcher, m_port+9);
    initTaggers(portTagger11, tagger11, protocol, portDispatcher, m_port+10);
    initTaggers(portTagger12, tagger12, protocol, portDispatcher, m_port+11);
    initTaggers(portTagger13, tagger13, protocol, portDispatcher, m_port+12);
    initTaggers(portTagger14, tagger14, protocol, portDispatcher, m_port+13);
    initTaggers(portTagger15, tagger15, protocol, portDispatcher, m_port+14);
    initTaggers(portTagger16, tagger16, protocol, portDispatcher, m_port+15);

    pModel.registerModuleConstructionSmartReceiver(pRenderer);
    pModel.registerModuleConstructionDumbReceiver(moduleReceiver);
    pModel.registerModuleDataReceiver(moduleDataReceiver);
    pModel.registerGraphNameReceiver(graphNameReceiver);
    pModel.registerRendererControlReceiver(pRenderer);
    pModel.registerControlValueReceiver(controlValueReceiver);
    pModel.registerModuleStatisticsReceiver(moduleStatisticsReceiver);
    pModel.registerModelStatusReceiver(modelStatusReceiver);
		
    pRenderer.registerSmartControlValueReceiver(pModel);
    pRenderer.registerModuleStatisticsSmartReceiver(pModel);
    pRenderer.registerRendererStatusReceiver(rendererStatusReceiver);
		
    pDllLoader.registerModuleClassReceiver(pRenderer);
    pDllLoader.registerModuleClassSpecReceiver(pModel);
    pDllLoader.registerModuleClassInfoReceiver(moduleClassInfoReceiver);
    pDllLoader.registerTypeClassReceiver(pRenderer);
		
    modelControlSender.registerModelControlReceiver(pModel);
    rendererControlSender.registerRendererControlReceiver(pRenderer);
    moduleClassLoaderControlSender.registerModuleClassLoaderControlReceiver(pDllLoader);
    sequencerControlSender.registerSequencerControlReceiver(pSequencer);
    playlistControlSender.registerSequencerControlReceiver(pPlayList);

    sf = utils::AutoPtr<AutoTypeLoader>(new AutoTypeLoader(pDllLoader));
    pDllLoader.registerModuleClassNameReceiver(moduleClassNameReceiver);
    pDllLoader.registerTypeClassNameReceiver(*sf);

    pSequencer.registerModelControlReceiver(pModel);
    pSequencer.registerSequenceUpdateReceiver(sequenceUpdateReceiver);
    pSequencer.registerSequenceNameReceiver(sequenceNameReceiver);
    pSequencer.registerSequencerStatusReceiver(sequencerStatusReceiver);

    pPlayList.registerModelControlReceiver(pModel);
    pPlayList.registerSequenceUpdateReceiver(playlistUpdateReceiver);
    pPlayList.registerSequenceNameReceiver(playlistNameReceiver);
    pPlayList.registerSequencerStatusReceiver(playlistStatusReceiver);

    engineControlSender.registerEngineControlReceiver(*this);

    int rendererInterval = config.rendererInterval;
    int netInterval = config.netInterval;
    int sequencerInterval = config.sequencerInterval;

    scheduler.addTask(*acceptor, 300);
    scheduler.addTask(*this,350);
    scheduler.addTask(netPoller,netInterval);
    scheduler.addTask(pRenderer,rendererInterval);
    scheduler.addTask(pSequencer,sequencerInterval);
  }
	
  Controller::~Controller()
  {
    try
      {
	this->pDllLoader.unloadAll();
	disconnect();
      }
    catch (std::runtime_error& e)
      {
	std::cerr << "Fehler beim Aufräumen: " << e.what() << std::endl;
      }
    catch (...)
      {
	std::cerr << "Unbekannter Fehler beim Aufräumen: " << std::endl;
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
	delete socket;
	socket = 0;
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
	/*	catch(...)
	  {
	    logger->error("Oh oh....", "Oh oh oh...");
	    }*/
      }
  }
	
  bool Controller::run()
  { 
    try 
      {
	// here comes what happens after the connection to the gui is
	// there
	if (socket != 0)
	  {
	    socketAdaptor.setSocket(*socket);
	    protocol.registerSender(*socket);

	    std::vector<std::string> modules = 
	      getFilesInDir(config.moduleDirs,MODULE_ENDING);

	    std::vector<std::string> types =
	      getFilesInDir(config.typeDirs,TYPE_ENDING);

	    pDllLoader.readDlls(modules, types);
				
	    pModel.updateFileSystem();
				
	    pModel.newGraph("default");	    
				
	    pSequencer.updateFileSystem();
	    pSequencer.createSequence("default");
				
	    pPlayList.updateFileSystem();
	    pPlayList.createSequence("default");	    
				
	    return false;
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
    *m_socket = m_serverSocket->accept();

    if (*m_socket != 0)
      {
	(*m_socket)->setSoTimeout(0);
	return false; //terminate if accept succeeded
      }


    return true;
  }

  NetPoller::NetPoller(net::SocketAdaptor& adaptor)
    : m_adaptor(&adaptor) 
  {
  }

  bool NetPoller::run() 
  {
    m_adaptor->run();
    return true;
  }

}
