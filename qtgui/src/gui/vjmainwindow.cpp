#include "vjmainwindow.h"

#include <qmenubar.h>
#include <qlayout.h>
#include <qtabwidget.h>
#include <qstatusbar.h>
#include <qsplitter.h>
#include <qtimer.h>

#include "moduleclassview.h"
//#include "moduleclasstabview.h"
#include "graphnameview.h"
#include "sequencenameview.h"
#include "playlistnameview.h"
#include "editorwidget.h"
#include "picswitch.h"
#include "propertyview.h"
#include "dllselectordialog.h"
#include "logwindow.h"
#include "playlist.h"

#include "sequenceeditor.h"

#include "interfaces/ienginecontrolreceiver.h"
#include "interfaces/irenderercontrolreceiver.h"
#include "interfaces/isequencercontrolreceiver.h"
#include "interfaces/igraphnamesender.h"
#include "interfaces/imoduleclassnamesender.h"
#include "interfaces/isequencenamesender.h"
#include "interfaces/isequenceupdatesender.h"
#include "interfaces/ierrorsender.h"
#include "interfaces/irendererstatussender.h"
#include "interfaces/isequencerstatussender.h"

#include "guimodel/enginewrapper.h"
#include "guimodel/moduleclassmodel.h"
#include "guimodel/actionsequencerwrapper.h"

#include "rot_klein.xpm"
#include "gruen_klein.xpm"

#include "utils/structreader.h"

namespace gui
{

  VJMainWindow::VJMainWindow(QWidget* parent, const char* name,
			     const std::string& ipcType,
			     const std::string& locator, int port,
			     StructReaderPtr& config)
    : QMainWindow(parent,name),
      engineWrapper(new EngineWrapper(ipcType, locator, port)),
      running(false), connected(false), 
      moduleClassView(0), moduleClassTabView(0), sam(0), graphNameView(0),
      sequenceNameView(0), sequencerWrapper(0), m_config(config)
  {
    buildMenuBar();

    switcher = new PicSwitch(statusBar(),"switcher!",roter_mann,gruener_mann);

    statusBar()->addWidget(switcher,0,TRUE);

    buildSceleton();
  
    connect(switcher,SIGNAL(clicked(int)),this,SLOT(startStop()));
  
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(pollNetwork()));
    timer->start(5);
  }

  VJMainWindow::~VJMainWindow()
  {
    delete engineWrapper;
    delete graphNameView;
    delete sequenceNameView;
    delete playlistNameView;
    delete sequencerWrapper;
    delete playlistWrapper;
  }

  void VJMainWindow::started()
  {
    switcher->setPic(1);
    running = true;
  }

  void VJMainWindow::stopped()
  {
    switcher->setPic(0);
    running = false;
  }

  void VJMainWindow::renderedGraphChanged( const std::string& graphID )
  {
    emit renderedGraphChangedSignal( graphID );
  }

  void VJMainWindow::pollNetwork()
  {
    try
      {	  
	if (connected)
	  engineWrapper->checkData();	 
      }
    catch (std::runtime_error& e)
      {
	displayErrorMessage(e.what());
      }
  }

  void VJMainWindow::connectToRealEngine() throw (std::runtime_error)
  {
    engineWrapper->connect();
	
    connected=true;
  }

  void VJMainWindow::disconnectFromRealEngine() throw (std::runtime_error)
  {
    engineWrapper->disconnect();
  
    connected = false;
  }

  void VJMainWindow::buildMenuBar(void)
  {
    QPopupMenu* file = new QPopupMenu(this);

    //TODO: removed "advanced" options
    /*    QPopupMenu* fileImport = new QPopupMenu(file);
    fileImport->insertItem("image",1);
    fileImport->insertItem("video",1);
    file->insertItem("import",fileImport);
    file->insertSeparator();*/
    file->insertItem("quit",FILE_QUIT);
    menuBar()->insertItem("File",file);
    connect(file,SIGNAL(activated(int)),this,SLOT(action(int)));

    //TODO: removed "advanced" options
    QPopupMenu* server = new QPopupMenu(this);
    server->insertItem("connect",CONNECT_ENGINE);
    server->insertItem("disconnect",DISCONNECT_ENGINE);
    server->insertItem("synchronize",SYNCHRONIZE_ENGINE);
    server->insertItem("shutdown",SHUTDOWN_ENGINE);
    menuBar()->insertItem("Server",server);
    connect(server,SIGNAL(activated(int)),this,SLOT(action(int)));

    //TODO: removed "advanced" options
        QPopupMenu* startstop = new QPopupMenu(this);
    startstop->insertItem("start/stop",STARTSTOP_ENGINE);
    menuBar()->insertItem("Engine",startstop);
    connect(startstop,SIGNAL(activated(int)),this,SLOT(action(int)));

    windows = new QPopupMenu(this);
    windows->insertItem("Dlls Laden/Entladen",WINDOW_DLL_SELECTOR);
    windows->insertItem("Playlist", WINDOW_PLAYLIST);
    connect(windows, SIGNAL(activated(int)), this, SLOT(action(int)));
    menuBar()->insertItem("Windows",windows);
  }

  void VJMainWindow::buildModuleBar(void)
  {
    effectMenue = new QPopupMenu(this);
    menuBar()->insertItem("Effekte",effectMenue);
  
    moduleClassView = new ModuleClassView(effectMenue);


    m_dllSelector = 
      new DllSelectorDialog(this,"böla",0,
			    engineWrapper->moduleClassLoaderControlReceiver(),
			    true);

    engineWrapper->moduleClassNameSender().registerModuleClassNameReceiver(*m_dllSelector);

    // moduleClassView->show();
    engineWrapper->moduleClassModel().registerModuleClassView(*moduleClassView);
    engineWrapper->moduleClassModel().registerModuleClassView(*m_dllSelector);
	//engineWrapper->moduleClassModel().registerModuleClassView(*moduleClassTabView);
  }

  void VJMainWindow::unbuildModuleBar()
  {
    engineWrapper->moduleClassModel().unregisterModuleClassViews();
    //engineWrapper->moduleClassNameSender().unregisterModuleClassNameReceiver(); //TODO der wird beim naechsten register automatisch ueberschrieben

    delete m_dllSelector;
    delete effectMenue;
  }

  void VJMainWindow::buildSceleton()
  {
    centralWidget = new QWidget(this,"CentralWidget");
	


    splitVertical = new QSplitter(Vertical,centralWidget);
	//moduleClassTabView = new ModuleClassTabView(splitVertical);

    splitHorizontal = new QSplitter(splitVertical);	
	//splitHorizontal->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,
	//	QSizePolicy::Minimum));
	//splitVertical->setResizeMode(splitHorizontal,QSplitter::FollowSizeHint);

    leftTab = new QTabWidget(splitHorizontal,"Linker Tab");

    editor = new QWidget(splitHorizontal,"PLATZ FUER EDITOR");

    belowTab = new QTabWidget(splitVertical,"Unterer Tab");
	belowTab->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,
		QSizePolicy::Minimum));
	splitVertical->setResizeMode(belowTab,QSplitter::FollowSizeHint);
    
    logWindow = new LogWindow(belowTab);
    engineWrapper->errorSender().registerErrorReceiver(*logWindow);
    belowTab->addTab(logWindow,"Meldungen");

    setCentralWidget(centralWidget);
  
    // layout
    QVBoxLayout* topLayout = new QVBoxLayout(centralWidget);
    topLayout->addWidget(splitVertical);	

    engineWrapper->rendererStatusSender().registerRendererStatusReceiver(*this);
  }

  void VJMainWindow::fillSceleton(void)
  {
    sequencerWrapper = new ActionSequencerWrapper();
    playlistWrapper = new ActionSequencerWrapper();

    sequenceEditor = new SequenceEditor(belowTab,"Sequenzer",0,
					engineWrapper->sequencerControlReceiver(),
					*sequencerWrapper);

    sequencerWrapper->registerSequencerControlReceiver(engineWrapper->sequencerControlReceiver());
    sequencerWrapper->registerSceneChangeListener(*sequenceEditor);

    engineWrapper->sequencerStatusSender().registerSequencerStatusReceiver(*sequenceEditor);

    belowTab->addTab(sequenceEditor, "Sequencer");

    engineWrapper->sequenceUpdateSender().registerSequenceUpdateReceiver(*sequencerWrapper);

    graphNameView = new GraphNameView(leftTab,
				      engineWrapper->modelControlReceiver(),
				      *sequencerWrapper);

    sequenceNameView = 
      new SequenceNameView(leftTab,
			   engineWrapper->sequencerControlReceiver(),
			   *playlistWrapper);

    connect(sequenceEditor,SIGNAL(newEditSequence(const std::string&)),
	    sequenceNameView->signalObject(),
	    SLOT(editSequenceChanged(const std::string&)));

    engineWrapper->graphNameSender().registerGraphNameReceiver(*graphNameView);

    engineWrapper->sequenceNameSender().registerSequenceNameReceiver(*sequenceNameView);

    editorWidget = new EditorWidget(editor,"Editorwidget",
				    engineWrapper->graphModel(),
				    engineWrapper->modelControlReceiver(),
				    engineWrapper->controlModel(),
				    *moduleClassView,
					/* *moduleClassTabView,*/
				    engineWrapper->controlValueDispatcher(),
				    engineWrapper->moduleStatisticsSender(),
				    engineWrapper->modelStatusSender());

    editorWidget->show();
    QVBoxLayout* editorLayout = new QVBoxLayout(editor);
    editorLayout->addWidget(editorWidget);

    m_playlist = new Playlist(this, engineWrapper->playlistControlReceiver(),
			      *playlistWrapper);

    playlistWrapper->registerSceneChangeListener(*m_playlist);
    playlistWrapper->registerSequencerControlReceiver(engineWrapper->playlistControlReceiver());

    engineWrapper->playlistUpdateSender().registerSequenceUpdateReceiver(*playlistWrapper);

    engineWrapper->playlistStatusSender().registerSequencerStatusReceiver(*m_playlist);
    m_playlist->hide();

    playlistNameView = 
      new PlaylistNameView(leftTab,
			   engineWrapper->playlistControlReceiver());

    engineWrapper->playlistNameSender().registerSequenceNameReceiver(*playlistNameView);

    connect( m_playlist, SIGNAL(editPlaylistChanged( const std::string& )),
	     playlistNameView->signalObject(),
	     SLOT(editPlaylistChanged( const std::string& )) );


    propertyView = new PropertyView(leftTab);
    leftTab->addTab(propertyView,"Eigenschaften");
    propertyTabID = leftTab->currentPageIndex();
    leftTab->addTab(graphNameView->widget(),"Graphen");
    leftTab->addTab(sequenceNameView->widget(),"Sequenzen");
    leftTab->addTab(playlistNameView->widget(),"Playlists");
    
    connect(editorWidget,SIGNAL(statusText(const std::string&)),
	    this,SLOT(displayStatusText(const std::string&)));

    connect(editorWidget,SIGNAL(properties(const IPropertyDescription&)),
	    this,SLOT(displayProperties(const IPropertyDescription&)));

    connect(editorWidget,SIGNAL(newEditGraph(const std::string&,
					     const std::string&)),
	    graphNameView->signalObject(),
	    SLOT(editGraphChanged(const std::string&,const std::string&)));

    connect(this,SIGNAL(renderedGraphChangedSignal(const std::string&)),
	    graphNameView->signalObject(),
	    SLOT(renderedGraphChanged(const std::string&)));


  }

  void VJMainWindow::clearSceleton()
  {
    if (centralWidget) 
      {
	this->removeChild(centralWidget);
	delete centralWidget;
	centralWidget = 0;
      }
    buildSceleton();
  }

  /**
   * Verbindet zur engine und baut die toolbar des Graphen zusammen
   **/
  void VJMainWindow::connectToEngine(void)
  {
    try
      {
	if (connected)
	  {
	    throw std::runtime_error("schon mit der Engine verbunden");
	  }

	statusBar()->message("mit der Engine verbinden ...");		
		
	buildModuleBar();

	this->connectToRealEngine();
				
	fillSceleton();

	statusBar()->message("Bereit");
		
      } 
    catch(std::runtime_error& e) 
      {
	displayErrorMessage(e.what());
      }
  }

  void VJMainWindow::disconnectFromEngine(void)
  {
    if (!connected)
      {	
	throw std::runtime_error("nicht mit der Engine verbunden");
      }
		
    this->disconnectFromRealEngine();

    this->clearSceleton();

    this->unbuildModuleBar();
		
    // menuumbauen
    statusBar()->message("nicht mit der Engine verbunden");
  }

  void VJMainWindow::startStop()
  {
    this->action(STARTSTOP_ENGINE);
  }

  void VJMainWindow::displayStatusText(const std::string& s)
  {
    statusBar()->message(s.c_str(),2500);
  }

  void VJMainWindow::displayProperties(const IPropertyDescription& pd)
  {
    try {
      propertyView->displayProperties(pd);
      leftTab->setCurrentPage(propertyTabID);
    }
    catch (std::runtime_error& e)
      {
	displayErrorMessage(e.what());
      }
  }

  void VJMainWindow::displayErrorMessage(const std::string& text)
  {
    logWindow->exceptionThrown(text);
  }

  void VJMainWindow::setCaption(const std::string& text)
  {
	  QWidget::setCaption(text.c_str());
  }

  void VJMainWindow::action(int actionID){
    switch (actionID)
      {
      case CONNECT_ENGINE:
	connectToEngine();
	break;

      case DISCONNECT_ENGINE:
	disconnectFromEngine();
	break;

      case SYNCHRONIZE_ENGINE:
	engineWrapper->synchronize();
	break;
      case SHUTDOWN_ENGINE:
	engineWrapper->engineControlReceiver().shutDown();
	disconnectFromEngine();
	break;

      case STARTSTOP_ENGINE:
	if (connected) 
	  {
	    try 
	      {
		if (running)
		  {
		    engineWrapper->rendererControlReceiver().stop();
		  }
		else
		  {
		    engineWrapper->rendererControlReceiver().start();
		  }
	      } 
	    catch (std::runtime_error& err)
	      {
		displayErrorMessage(err.what());
	      }
	  }
	break;
	
      case FILE_QUIT:
	quitSignal();
	break;
	
      case WINDOW_DLL_SELECTOR:
	{
	  m_dllSelector->show();
	} break;
	 case WINDOW_PLAYLIST:
	{
	  m_playlist->show();
	} break;
      default:
	throw std::runtime_error("unbekannter Befehl");
      }	  

  
  }

} //end of namespace gui
