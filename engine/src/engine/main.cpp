
#if defined (HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include "windows.h" //for Sleep and signal handling
#elif defined(OS_POSIX)
#include <signal.h>
#endif

#include <iostream>
#include <fstream>

#include "model/model.h"
#include "renderer/renderer.h"
#include "dllloader/dllloader.h"
#include "sequencer/sequencer.h"

#include "net/isocket.h"
#include "net/protocol.h"
#include "net/tagger.h"
#include "net/tagutils.h"
#include "net/tagdispatcher.h"
#include "net/socketadaptor.h"

#include "net/tcpserversocket.h"
#if defined(OS_POSIX)
#include "net/domainserversocket.h"
#elif defined(OS_WIN32)
#include "net/namedpipeserversocket.h"
#endif

#include "interfaces/itypeclassnamereceiver.h"
#include "interfaces/imoduleclassnamereceiver.h"
#include "interfaces/ienginecontrolreceiver.h"

#include "netinterfaces/modelcontrolsendernet.h"
#include "netinterfaces/renderercontrolsendernet.h"
#include "netinterfaces/moduleclassloadercontrolsendernet.h"
#include "netinterfaces/enginecontrolsendernet.h"
#include "netinterfaces/sequencercontrolsendernet.h"
#include "netinterfaces/sequencerstatusreceivernet.h"

#include "netinterfaces/moduleconstructiondumbreceivernet.h"
#include "netinterfaces/moduleclassinforeceivernet.h"
#include "netinterfaces/moduledatareceivernet.h"
#include "netinterfaces/controlvaluereceivernet.h"
#include "netinterfaces/modulestatisticsreceivernet.h"
#include "netinterfaces/moduleclassnamereceivernet.h"
#include "netinterfaces/modelstatusreceivernet.h"
#include "netinterfaces/graphnamereceivernet.h"
#include "netinterfaces/sequenceupdatereceivernet.h"
#include "netinterfaces/sequencenamereceivernet.h"
#include "netinterfaces/errorreceivernet.h"
#include "netinterfaces/rendererstatusreceivernet.h"

#include "utils/structreader.h"
#include "utils/autoptr.h"
//#include "utils/streamlogger.h"
#include "utils/filesystem.h"
#include "utils/buffer.h"

#include "netlogger.h"

#include "interfaces/itask.h"
#include "scheduler.h"

#if defined(OS_WIN32)
const std::string MODULE_ENDING = ".dll";
const std::string TYPE_ENDING = ".dll";
#elif defined(OS_POSIX)
const std::string MODULE_ENDING = ".so";
const std::string TYPE_ENDING = ".so";
#else
#error "Uknown OS"
#endif

/**
 * Just a hack to automatically load all types that exist.
 */
class StupidFuck : public ITypeClassNameReceiver//,
//public IModuleClassNameReceiver
{
public:
  StupidFuck(/*IModuleClassLoaderControlReceiver& modLoader,*/
	     ITypeClassLoaderControlReceiver& typLoader)
    : /*m_modLoader(modLoader),*/ m_typLoader(typLoader)
  {
  }
	
  void typeClassNameExists(const std::string& name)
  {
    m_typLoader.loadTypeClass(name);
  }
	
  /*void moduleClassNameExists(const std::string& name)
    {
    m_modLoader.loadModuleClass(name);
    }*/
	
private:
  //IModuleClassLoaderControlReceiver& m_modLoader;
  ITypeClassLoaderControlReceiver& m_typLoader;
};


/**
 * Returns a vector of all files in a directory, that have a certain
 * file ending.
 */
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

typedef net::Tagger<std::string, net::StringTagUtil> CommandTagger;
typedef net::Tagger<uint_32, net::UInt32TagUtil> PortTagger;
typedef net::TagDispatcher<uint_32> PortDispatcher;

// connect a porttagger and a commandtagger with their receiving
// and sending objects
static void initTaggers(PortTagger& portTagger, CommandTagger& commandTagger,
			net::Protocol& protocol,
			PortDispatcher& portDispatcher, int port)
{
  portTagger.registerSender(protocol);		
  portTagger.setTag(port);
  commandTagger.registerSender(portTagger);

  portDispatcher.registerListener(port, commandTagger);
}

// A task that accepts one connection on a serversocket
class Acceptor : public ITask
{
public:
  Acceptor(net::IServerSocket& serverSocket, net::ISocket*& socket)
    : m_serverSocket(&serverSocket), m_socket(&socket)
  {
    m_serverSocket->setSoTimeout(0);
    m_serverSocket->listen();
  }

  bool run()
  {
    *m_socket = m_serverSocket->accept();

    if (*m_socket != 0)
      {
	(*m_socket)->setSoTimeout(0);
	return false; //terminate if accept succeeded
      }


    return true;
  }

private:
  net::IServerSocket* m_serverSocket;
  net::ISocket** m_socket;
};

class NetPoller : public ITask
{
public:
  NetPoller(net::SocketAdaptor& adaptor)
    : m_adaptor(&adaptor) {}

  bool run() {
    m_adaptor->run();
    return true;
  }

private:
  net::SocketAdaptor* m_adaptor;
};

class Controller : public IEngineControlReceiver, public ITask
{
public:
  typedef utils::StructReader::ConfigMap ConfigMap;

  Controller(utils::StructReader& config, int port)
    : m_finished(false),
      m_config(config),
      m_port(port),      
		
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
      playlistStatusReceiver(tagger16),
      pModel(m_config.getStringValue("graph_dir")),
      pSequencer(m_config.getStringValue("sequence_dir")),
      pPlayList(m_config.getStringValue("playlist_dir")),
      logger(new engine::NetLogger(errorReceiver))
  {
    
    net::IServerSocket* serverSocket;

    std::string ipcType = m_config.getStringValue("ipc_type","inet");
    
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
	  = m_config.getStringValue("ipc_unix_node_prefix",
				    "/tmp/gephex_socket");
							 
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

    sf = utils::AutoPtr<StupidFuck>(new StupidFuck(pDllLoader));
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

    int rendererInterval = m_config.getIntValue("renderer_interval", 35);
    int netInterval = m_config.getIntValue("net_interval", 35);
    int sequencerInterval = m_config.getIntValue("sequencer_interval", 100);

    scheduler.addTask(*acceptor, 300);
    scheduler.addTask(*this,350);
    scheduler.addTask(netPoller,netInterval);
    scheduler.addTask(pRenderer,rendererInterval);
    scheduler.addTask(pSequencer,sequencerInterval);
  }
	
  virtual ~Controller()
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
	
  virtual bool finished() const
  {
    return m_finished;
  }
	
  void disconnect()
  {
    if (socket != 0)
      {
	delete socket;
	socket = 0;
      }
  }
	
  void shutDown()
  {
    m_finished = true;
    scheduler.stop();
  }
	
  void start()
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
	
  bool run()
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
	      getFilesInDir(m_config.getStringValue("module_dirs"),
			    MODULE_ENDING);

	    std::vector<std::string> types =
	      getFilesInDir(m_config.getStringValue("type_dirs"),TYPE_ENDING);

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
	
private:
  volatile bool m_finished;
	
  utils::StructReader m_config;
	
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
	
  model::Model pModel;
  renderer::Renderer pRenderer;
  dllloader::DllLoader pDllLoader;
  sequencer::Sequencer pSequencer;
  sequencer::Sequencer pPlayList;
	
  utils::AutoPtr<StupidFuck> sf;
  utils::AutoPtr<utils::ILogger> logger;
  engine::Scheduler scheduler;
};

static utils::AutoPtr<utils::StructReader> 
readConfigFile(const std::string& fileName)
{
  std::ifstream file(fileName.c_str());
	
  if (!file)
    throw std::runtime_error("Konnte Config file nicht öffnen.");
	
  std::string text;
	
  std::getline(file,text,(char) 255);
	
  file.close();
	
  utils::AutoPtr<utils::StructReader> sr(new utils::StructReader(text));

  return sr;
}

/**************************************************************************/


Controller* controller;

//typedef void (*sighandler_t)(int);

#if defined(OS_POSIX)
void signal_handler (int signum)
{
  std::cout << "Got signal " << signum << " trying to exit!" <<std::endl;

  // ignore sigpipe
  if (signum == SIGPIPE)
    {
      std::cout << "Ignoring SIGPIPE!" << std::endl;
      return;
    }

  if (controller && !controller->finished())
    {
      controller->shutDown();
    }
} 
#elif defined(OS_WIN32)
BOOL signal_handler(DWORD fdwCtrlType) 
{ 
  /*switch (fdwCtrlType) 
    { 
    case CTRL_C_EVENT: 
    case CTRL_CLOSE_EVENT: 
    case CTRL_BREAK_EVENT: 
    case CTRL_LOGOFF_EVENT: 
    case CTRL_SHUTDOWN_EVENT: 
    default: */
  //std::cout<<"Signal caught!"<<std::endl;			
  if (controller && !controller->finished())
    {
      controller->shutDown();
    }
  return TRUE;
  //} 
} 
 
#endif

int main(int /*argc*/,char* /*argv[]*/)
{
#if defined(OS_POSIX)
  signal(SIGINT,  signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGABRT, signal_handler);
  signal(SIGPIPE, signal_handler);
#elif defined(OS_WIN32)
  if (SetConsoleCtrlHandler( (PHANDLER_ROUTINE) signal_handler,
			     TRUE) == 0)
    {
      std::cerr<<"Could not set control handler!"<<std::endl; 
      return -1;
    }
#endif


  try
    {
      std::string configFileName;
#if defined(OS_WIN32)
      configFileName = "../enginew.conf";
#elif defined(OS_POSIX)
      std::string home = getenv("HOME");
      configFileName = home + "/.gephex/engine.conf";
#endif
		
      utils::AutoPtr<utils::StructReader> sr = readConfigFile(configFileName);
      
      int port = sr->getIntValue("ipc_port");
      controller = new Controller(*sr, port);
      controller->start();
		
    }
  catch (std::runtime_error& e)
    {
      std::cerr << "Fehler: " << e.what() << std::endl;
      //      getchar();   
    }

  if(controller)
    {
      delete controller;
      controller = 0;
    }
 
  return 0;
}
