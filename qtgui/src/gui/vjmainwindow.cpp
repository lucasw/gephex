#include "vjmainwindow.h"

#include <qmenubar.h>
#include <qlayout.h>
#include <qtabwidget.h>
#include <qstatusbar.h>
#include <qsplitter.h>
#include <qtimer.h>
#include <qaction.h>

#include "base/propertyview.h"
#include "base/logwindow.h"
#include "base/keyboardmanager.h"

#include "editor/editorwidget.h"

#include "moduleclassview.h"
//#include "moduleclasstabview.h"
#include "graphnameview.h"
#include "sequencenameview.h"
#include "playlistnameview.h"
#include "picswitch.h"

#include "dllselectordialog.h"
#include "playlist.h"

#include "sequenceeditor.h"

#include "aboutdialog.h"

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
      sequenceNameView(0), sequencerWrapper(0), m_config(config),
      m_kbManager(new KeyboardManager())
  {
    createWindows();
    createActions();

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
    delete m_kbManager;
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
    showPlugInManagerAction->setEnabled(true);
    showPlayListAction->setEnabled(true);
    rendererStateAction->setEnabled(true);
	keyGrabStateAction->setEnabled(true);
  }

  void VJMainWindow::disconnectFromRealEngine() throw (std::runtime_error)
  {
    engineWrapper->disconnect();
    connected = false;
    showPlugInManagerAction->setEnabled(false);
    showPlayListAction->setEnabled(false);
    rendererStateAction->setEnabled(false);
	keyGrabStateAction->setEnabled(false);
  }

  void VJMainWindow::createActions()
  {
    quitAction= new QAction(this,"QuitAction");
    quitAction->setText("quit");
    quitAction->setToolTip ("exit the application");
    quitAction->setAccel(Qt::CTRL+Qt::Key_Q);
    quitAction->setEnabled(true);
    connect(quitAction,SIGNAL(activated()),this,SIGNAL(quitSignal()));


    showPlugInManagerAction= new QAction(this,"ShowPlugInManagerAction",false);
    showPlugInManagerAction->setText("PlugIn Manager");
    showPlugInManagerAction->setToolTip ("show the PlugIn Manager Dialog");
    showPlugInManagerAction->setEnabled(false);
    showPlugInManagerAction->setToggleAction ( true );
    connect(showPlugInManagerAction,SIGNAL(toggled(bool)),
	    m_dllSelector,SLOT(setShown ( bool )));  
    
    showPlayListAction= new QAction(this,"ShowPlayListAction",false);
    showPlayListAction->setText("Playlist");
    showPlayListAction->setToolTip ("show the Playlist Dialog");
    showPlayListAction->setEnabled(false);
    showPlayListAction->setToggleAction ( true );
    connect(showPlayListAction,SIGNAL(toggled(bool)),
	    m_playlist,SLOT(setShown ( bool )));  

    
    rendererStateAction= new QAction(this,"RendererStateAction",false);
    rendererStateAction->setText("Render state");
    rendererStateAction->setToolTip ("toggle renderer state");
    rendererStateAction->setEnabled(false);
    rendererStateAction->setAccel(Qt::Key_Space);
    rendererStateAction->setToggleAction ( true );
    connect(rendererStateAction,SIGNAL(toggled(bool)),
	    this,SLOT(setRendererState( bool )));      

    connectToEngineAction= new QAction(this,"ConnectToEngineAction");
    connectToEngineAction->setText("connect");
    connectToEngineAction->setToolTip ("connect to the engine");
    connectToEngineAction->setEnabled(false);
    connect(connectToEngineAction,SIGNAL(activated()),
	    this,SLOT(connectToEngine()));

    disConnectToEngineAction= new QAction(this,"disConnectToEngineAction");
    disConnectToEngineAction->setText("disconnect");
    disConnectToEngineAction->setToolTip ("disconnect from the engine");
    disConnectToEngineAction->setEnabled(false);
    connect(disConnectToEngineAction,SIGNAL(activated()),
	    this,SLOT(disconnectFromEngine()));

    synchronizeEngineAction= new QAction(this,"synchronizeEngineAction");
    synchronizeEngineAction->setText("sync");
    synchronizeEngineAction->setToolTip ("sync the gui with the engine");
    synchronizeEngineAction->setEnabled(false);
    connect(synchronizeEngineAction,SIGNAL(activated()),
	    this,SLOT(synchronize()));


    shutDownEngineAction= new QAction(this,"shutDownEngineAction");
    shutDownEngineAction->setText("stop the engine");
    shutDownEngineAction->setToolTip ("shut the engine down");
    shutDownEngineAction->setEnabled(false);
    connect(shutDownEngineAction,SIGNAL(activated()),
	    this,SLOT(shutDown()));

    keyGrabStateAction= new QAction(this,"keyGrabStateAction");
    keyGrabStateAction->setText("grab keyboard");
    keyGrabStateAction->setToolTip ("turn the keygrabber on/off");
    keyGrabStateAction->setEnabled(false);
    keyGrabStateAction->setToggleAction ( true );
    connect(keyGrabStateAction,SIGNAL(toggled(bool)),
	    this,SLOT(setKeyGrabState( bool )));


	aboutAction= new QAction(this,"aboutAction");
    aboutAction->setText("about");
    aboutAction->setToolTip ("shows some stuff");
    aboutAction->setAccel(Qt::CTRL+Qt::Key_A);
    aboutAction->setEnabled(true);
    connect(aboutAction,SIGNAL(activated()),this,SLOT(aboutSlot()));
  }
  
  
  void VJMainWindow::createWindows()
  {
    m_dllSelector = 
      new DllSelectorDialog(this,"PlugIn Manager Dialog",0,
			    engineWrapper->moduleClassLoaderControlReceiver(),
			    true);

	connect(m_dllSelector, SIGNAL(status(const std::string&)),
		    this, SLOT(displayStatusText(const std::string&)));

    m_playlist = new Playlist(this, engineWrapper->playlistControlReceiver(),
			      *playlistWrapper);
  }

  
  void VJMainWindow::buildMenuBar(void)
  {
    QPopupMenu* file = new QPopupMenu(this);
    menuBar()->insertItem("File",file,1,1);
    quitAction->addTo(file);

    QPopupMenu* server = new QPopupMenu(this);
    menuBar()->insertItem("Server",server,2,2);
    connectToEngineAction->addTo(server);
    disConnectToEngineAction->addTo(server);
    synchronizeEngineAction->addTo(server);
    shutDownEngineAction->addTo(server);

    QPopupMenu* startstop = new QPopupMenu(this);
    menuBar()->insertItem("Engine",startstop,3,3);
    rendererStateAction->addTo(startstop);

    QPopupMenu* keyboard = new QPopupMenu(this);
    menuBar()->insertItem("Keyboard", keyboard,4,4);
    keyGrabStateAction->addTo(keyboard);


    windows = new QPopupMenu(this);
    menuBar()->insertItem("Windows",windows,5,5);
    showPlugInManagerAction->addTo(windows);
    showPlayListAction->addTo(windows);

	effectMenue = new QPopupMenu(this);
    menuBar()->insertItem("Effekte",effectMenue,6,6);

	help = new QPopupMenu(this);
	menuBar()->insertItem("Help", help,7,7);
	aboutAction->addTo(help);
  }


  void VJMainWindow::buildModuleBar(void)
  {
	  //moved to buildMenuBar
    //effectMenue = new QPopupMenu(this);
    //menuBar()->insertItem("Effekte",effectMenue,6,6);
  
    moduleClassView = new ModuleClassView(effectMenue);



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
    //delete effectMenue;
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
	leftTab->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum));
	

    editor = new QWidget(splitHorizontal,"PLATZ FUER EDITOR");
#if QT_VERSION >= 300
	editor->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum));

	splitHorizontal->setResizeMode(editor, QSplitter::FollowSizeHint);
	splitHorizontal->setResizeMode(leftTab, QSplitter::FollowSizeHint);
#endif
    belowTab = new QTabWidget(splitVertical,"Unterer Tab");
	belowTab->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,
		QSizePolicy::Minimum));
	splitVertical->setResizeMode(belowTab,QSplitter::FollowSizeHint);
    
    logWindow = new LogWindow(belowTab);
    engineWrapper->errorSender().registerErrorReceiver(*logWindow);
    belowTab->addTab(logWindow,"Messages");

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

    sequenceEditor = new SequenceEditor(belowTab,"Sequencer",0,
					engineWrapper->sequencerControlReceiver(),
					*sequencerWrapper);

    sequencerWrapper->registerSequencerControlReceiver(engineWrapper->sequencerControlReceiver());
    sequencerWrapper->registerSceneChangeListener(*sequenceEditor);

    engineWrapper->sequencerStatusSender().registerSequencerStatusReceiver(*sequenceEditor);

    belowTab->addTab(sequenceEditor, "Sequencer");

    engineWrapper->sequenceUpdateSender().registerSequenceUpdateReceiver(*sequencerWrapper);

    graphNameView = new GraphNameView(leftTab,
				      engineWrapper->modelControlReceiver(),
				      *sequencerWrapper,
                                      *logWindow);

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
				    engineWrapper->modelStatusSender(),
				    *m_kbManager, *logWindow);

    editorWidget->show();
    QVBoxLayout* editorLayout = new QVBoxLayout(editor);
    editorLayout->addWidget(editorWidget);


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
    leftTab->addTab(propertyView,"Properties");
    propertyTabID = leftTab->currentPageIndex();
    leftTab->addTab(graphNameView->widget(),"Graphs");
    leftTab->addTab(sequenceNameView->widget(),"Sequences");
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
	    throw std::runtime_error("already connected");
	  }

	statusBar()->message("connect to the rendering engine ...");		
		
	buildModuleBar();

	this->connectToRealEngine();
				
	fillSceleton();

	statusBar()->message("Ready");
		
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
	throw std::runtime_error("not connected with the engine");
      }
		
    this->disconnectFromRealEngine();

    this->clearSceleton();

    this->unbuildModuleBar();
		
    // menuumbauen
    statusBar()->message("not connected with the engine");
  }


  void VJMainWindow::startStop()
  {
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
    if (logWindow)
    	logWindow->error(text);
  }


  void VJMainWindow::setCaption(const std::string& text)
  {
	  QWidget::setCaption(text.c_str());
  }


  void VJMainWindow::synchronize()
  {
    engineWrapper->synchronize();
  }

  void VJMainWindow::aboutSlot()
  {
	  AboutDialog* dlg = new AboutDialog(this);
	  dlg->show();
  }


  void VJMainWindow::shutDown()
  {
    engineWrapper->engineControlReceiver().shutDown();
    disconnectFromEngine();
  }


  void VJMainWindow::setKeyGrabState(bool state)
  {
    if (state)
      m_kbManager->turnOn();
    else
      m_kbManager->turnOff();
  }


  void VJMainWindow::setRendererState(bool state)
  {
    assert(connected);
    
    try 
      {
	if (state)
	  engineWrapper->rendererControlReceiver().start();
	else
	  engineWrapper->rendererControlReceiver().stop();
      }
    catch (std::runtime_error& err)
      {
	displayErrorMessage(err.what());
      }
  }
} //end of namespace gui
