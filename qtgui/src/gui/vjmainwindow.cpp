/* This source file is a part of the GePhex Project.

  Copyright (C) 2001-2003 

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

#include "vjmainwindow.h"

#include <iostream>
#include <sstream>

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

#include "graphnameview.h"

#include "picswitch.h"

#include "dialogs/dllselectordialog.h"

#include "dialogs/aboutdialogimpl.h"
#include "dialogs/changesdialogimpl.h"
#include "dialogs/newgraphdialog.h"

#include "interfaces/ienginecontrolreceiver.h"
#include "interfaces/irenderercontrolreceiver.h"
#include "interfaces/igraphnamesender.h"
#include "interfaces/imoduleclassnamesender.h"
#include "interfaces/ierrorsender.h"
#include "interfaces/irendererstatussender.h"
#include "interfaces/imodelcontrolreceiver.h"

#include "guimodel/enginewrapper.h"
#include "guimodel/moduleclassmodel.h"
#include "guimodel/controlvaluedispatcher.h"

#include "rot_klein.xpm"
#include "gruen_klein.xpm"

#include "utils/structreader.h"
#include "utils/spawn.h"
#include "utils/timing.h"
#include "utils/configmanager.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

namespace gui
{

  class ProxyErrorReceiver : public IErrorReceiver
  {
  public:
    ProxyErrorReceiver() : m_client(0) {};

    void set_client(IErrorReceiver* client)
    {
      m_client = client;
    }

    void error(const std::string& text)
    {
      if (m_client)
        m_client->error(text);
    }

    void warning(const std::string& text)
    {
      if (m_client)
        m_client->warning(text);
    }

    void log(const std::string& text)
    {
      if (m_client)
        m_client->log(text);
    }

  private:
    IErrorReceiver* m_client;
  };
  
  VJMainWindow::VJMainWindow(QWidget* parent, const char* name,
                             const utils::ConfigManager& config,
                             const std::string& ipc_locator,
                             const std::string& conf_base_dir)
			     
    : QMainWindow(parent,name),
      m_error_proxy(new ProxyErrorReceiver()),
      engineWrapper(new EngineWrapper(config.get_string_param("ipc_type"),
                                      ipc_locator,
                                      config.get_int_param("ipc_port"),
                                      *m_error_proxy)),
      running(false), connected(false), 
      moduleClassView(0), graphNameView(0),
      m_config(config),
      m_kbManager(0),
      m_conf_base_dir(conf_base_dir)
  {
    createWindows();
    createActions();

    buildMenuBar();
    
    switcher = new PicSwitch(statusBar(), "switcher!",
                             roter_mann, gruener_mann);

    statusBar()->addWidget(switcher,0,TRUE);
    
    buildSceleton();
    
    connect(switcher, SIGNAL(clicked(int)), this, SLOT(startStop()));
    
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
		    this, SLOT(pollNetwork()));
    timer->start(20);
  }


  VJMainWindow::~VJMainWindow()
  {
    delete graphNameView;

    //TODO: the kbmanager is currently not used (set to 0)
    // if it is activated, there is a problem with the order of deletion:
    // the dtor of NodeWidget unregisters itself from the keyboardmanager,
    // but the keyboardmanager gets deleted before the nodewidgets
    // (they get deleted by qt).
    // Possible solution: keep keyboardmanager in a utils::AutoPtr.
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

  void VJMainWindow::quitSlot()
  {
	
	emit quitSignal();
  }

  void VJMainWindow::pollNetwork()
  {
    try
      {	  
	if (connected)
	  engineWrapper->checkData();	 
      }
    catch (std::exception& e)
      {
    	displayErrorMessage(e.what());
        disconnectFromEngine();
      }
    catch(...)
      {
	displayErrorMessage("AAAAAdArgHHHHHHHHHHHHHHH");
        disconnectFromEngine();
      }
  }

  void VJMainWindow::connectToRealEngine() throw (std::runtime_error)
  {
    engineWrapper->connect();
    showPlugInManagerAction->setEnabled(true);
    
    rendererStateAction->setEnabled(true);
    //keyGrabStateAction->setEnabled(true);

    newGraphAction->setEnabled(true);

    connectToEngineAction->setEnabled(false);
    disConnectToEngineAction->setEnabled(true);
    //synchronizeEngineAction->addTo(server);
    shutDownEngineAction->setEnabled(true);
  }

  void VJMainWindow::disconnectFromRealEngine() throw (std::runtime_error)
  {
    engineWrapper->disconnect();
    showPlugInManagerAction->setEnabled(false);
    
    rendererStateAction->setEnabled(false);
    //    keyGrabStateAction->setEnabled(false);

    newGraphAction->setEnabled(false);

    connectToEngineAction->setEnabled(true);
    disConnectToEngineAction->setEnabled(false);
    //synchronizeEngineAction->addTo(server);
    shutDownEngineAction->setEnabled(false);
  }

  void VJMainWindow::createActions()
  {
    quitAction= new QAction(this,"QuitAction");
    quitAction->setText("Quit");
    quitAction->setToolTip ("exit the application");
    quitAction->setAccel(Qt::CTRL+Qt::Key_Q);
    quitAction->setEnabled(true);
    connect(quitAction, SIGNAL(activated()),
		    this, SLOT(quitSlot()));

    newGraphAction= new QAction(this,"NewGraphAction");
    newGraphAction->setText("New Graph");
    newGraphAction->setToolTip ("create a new graph");
    //newGraphAction->setAccel(Qt::CTRL+Qt::Key_Q);
    newGraphAction->setEnabled(false);
    connect(newGraphAction,SIGNAL(activated()),this,SLOT(newGraph()));

    showPlugInManagerAction= new QAction(this,"ShowPlugInManagerAction",false);
    showPlugInManagerAction->setText("PlugIn Manager");
    showPlugInManagerAction->setToolTip ("show the plugin-manager dialog");
    showPlugInManagerAction->setEnabled(false);
    showPlugInManagerAction->setToggleAction ( true );
    connect(showPlugInManagerAction,SIGNAL(toggled(bool)),
	    m_dllSelector,SLOT(setShown ( bool )));  
    
    rendererStateAction= new QAction(this,"RendererStateAction",false);
    rendererStateAction->setText("start/stop rendering");
    rendererStateAction->setToolTip ("starts and stops the renderer");
    rendererStateAction->setEnabled(false);
    rendererStateAction->setAccel(Qt::CTRL + Qt::Key_Space);
    rendererStateAction->setToggleAction ( false );
    connect(rendererStateAction, SIGNAL(activated()),
	    this,SLOT(setRendererState( )));      

    connectToEngineAction= new QAction(this,"ConnectToEngineAction");
    connectToEngineAction->setText("Connect");
    connectToEngineAction->setToolTip ("connect to the engine");
    connectToEngineAction->setEnabled(false);
    connect(connectToEngineAction,SIGNAL(activated()),
	    this,SLOT(connectToEngine()));

    disConnectToEngineAction= new QAction(this,"disConnectToEngineAction");
    disConnectToEngineAction->setText("Disconnect");
    disConnectToEngineAction->setToolTip ("disconnect from the engine");
    disConnectToEngineAction->setEnabled(false);
    connect(disConnectToEngineAction,SIGNAL(activated()),
	    this,SLOT(disconnectFromEngine()));

    synchronizeEngineAction= new QAction(this,"synchronizeEngineAction");
    synchronizeEngineAction->setText("Sync");
    synchronizeEngineAction->setToolTip ("sync the gui with the engine");
    synchronizeEngineAction->setEnabled(false);
    connect(synchronizeEngineAction,SIGNAL(activated()),
	    this,SLOT(synchronize()));
    
    shutDownEngineAction= new QAction(this,"shutDownEngineAction");
    shutDownEngineAction->setText("kill the engine");
    shutDownEngineAction->setToolTip ("terminates the engine process");
    shutDownEngineAction->setEnabled(false);
    connect(shutDownEngineAction,SIGNAL(activated()),
	    this,SLOT(shutDown()));

    /*    keyGrabStateAction= new QAction(this,"keyGrabStateAction");
    keyGrabStateAction->setText("Grab keyboard");
    keyGrabStateAction->setToolTip ("turn the keygrabber on/off");
    keyGrabStateAction->setEnabled(false);
    keyGrabStateAction->setToggleAction ( true );
    connect(keyGrabStateAction,SIGNAL(toggled(bool)),
    this,SLOT(setKeyGrabState( bool )));*/
    
    aboutAction= new QAction(this,"aboutAction");
    aboutAction->setText("About GePhex");
    //aboutAction->setToolTip ("shows some stuff");
    //aboutAction->setAccel(Qt::CTRL+Qt::Key_A);
    aboutAction->setEnabled(true);
    connect(aboutAction,SIGNAL(activated()),this,SLOT(aboutSlot()));

    changesAction= new QAction(this,"changesAction");
    changesAction->setText("Changes");
    changesAction->setToolTip ("Shows changes to previous version");
    //changesAction->setAccel(Qt::CTRL+Qt::Key_A);
    changesAction->setEnabled(true);
    connect(changesAction,SIGNAL(activated()),this,SLOT(changesSlot()));
  }
  
  
  void VJMainWindow::createWindows()
  {
    m_dllSelector = 
      new DllSelectorDialog(this,"PlugIn Manager Dialog",0,
			    engineWrapper->moduleClassLoaderControlReceiver(),
			    true);

    connect(m_dllSelector, SIGNAL(status(const std::string&)),
            this, SLOT(displayStatusText(const std::string&)));

    connect(m_dllSelector, SIGNAL(closed()),
            this, SLOT(dll_selector_closed()));
    
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
    //synchronizeEngineAction->addTo(server);
    shutDownEngineAction->addTo(server);

    /*
    QPopupMenu* graphMenu = new QPopupMenu(this);
    menuBar()->insertItem("Graphs",graphMenu,2,2);
    newGraphAction->addTo(graphMenu);
    */

    QPopupMenu* startstop = new QPopupMenu(this);
    menuBar()->insertItem("Engine",startstop,3,3);
    rendererStateAction->addTo(startstop);

    /*QPopupMenu* keyboard = new QPopupMenu(this);
      menuBar()->insertItem("Keyboard", keyboard,4,4);
      keyGrabStateAction->addTo(keyboard);*/

    windows = new QPopupMenu(this);
    menuBar()->insertItem("Windows",windows,5,5);
    showPlugInManagerAction->addTo(windows);    

    effectMenue = new QPopupMenu(this);
    menuBar()->insertItem("Effects",effectMenue,6,6);

    help = new QPopupMenu(this);
    menuBar()->insertItem("Help", help,7,7);
    aboutAction->addTo(help);
    changesAction->addTo(help);
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
    // the dllselector and effectmenue clear themselves
    // when they receive the syncStarted call
    engineWrapper->moduleClassModel().unregisterModuleClassViews();	
    
    //engineWrapper->moduleClassNameSender().unregisterModuleClassNameReceiver(); //TODO der wird beim naechsten register automatisch ueberschrieben
    
    //delete m_dllSelector;
    //delete effectMenue;
    
    effectMenue->clear();
    m_dllSelector->clear();
  }

  void VJMainWindow::buildSceleton()
  {
    centralWidget = new QWidget(this, "CentralWidget");
	
    splitVertical = new QSplitter(Qt::Vertical, centralWidget,
                                  "SplitVertical");
	
    splitHorizontal = new QSplitter(Qt::Horizontal, splitVertical,
                                    "SplitHorizontal");

    leftTab = new QTabWidget(splitHorizontal,"LeftTab");
    leftTab->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,
                                       QSizePolicy::Maximum));
	

    editor = new QWidget(splitHorizontal, "space for editor");
#if QT_VERSION >= 300
    editor->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,
                                      QSizePolicy::Maximum));

    splitHorizontal->setResizeMode(editor, QSplitter::FollowSizeHint);
    splitHorizontal->setResizeMode(leftTab, QSplitter::FollowSizeHint);
#endif
    belowTab = new QTabWidget(splitVertical, "BelowTab");
    belowTab->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,
                                        QSizePolicy::Minimum));
    splitVertical->setResizeMode(belowTab,QSplitter::FollowSizeHint);
    
    logWindow = new LogWindow(belowTab);
    engineWrapper->errorSender().registerErrorReceiver(*logWindow);
    belowTab->addTab(logWindow, "Messages");

    m_error_proxy->set_client(logWindow);

    setCentralWidget(centralWidget);

    // layout
    QVBoxLayout* topLayout = new QVBoxLayout(centralWidget);
    topLayout->addWidget(splitVertical);	

    centralWidget->show();
  }

  void VJMainWindow::fillSceleton(void)
  {

    graphNameView = new GraphNameView(leftTab,
				      engineWrapper->modelControlReceiver(),
                                      *logWindow);
    engineWrapper->graphNameSender().registerGraphNameReceiver(*graphNameView);

    editorWidget = new EditorWidget(editor,"Editorwidget",
				    engineWrapper->graphModel(),
				    engineWrapper->modelControlReceiver(),
				    engineWrapper->controlModel(),
				    *moduleClassView,
                                    /* *moduleClassTabView,*/
				    engineWrapper->controlValueDispatcher(),
				    engineWrapper->moduleStatisticsSender(),
				    engineWrapper->modelStatusSender(),
				    &*m_kbManager, *logWindow,
				    m_config.get_string_param("media_path"));

    editorWidget->show();
    QVBoxLayout* editorLayout = new QVBoxLayout(editor);
    editorLayout->addWidget(editorWidget);    

    propertyView = new PropertyView(leftTab);
    leftTab->addTab(propertyView,"Properties");
    propertyTabID = leftTab->currentPageIndex();
    leftTab->addTab(graphNameView->widget(),"Graphs");
    
    
    connect(editorWidget,SIGNAL(statusText(const std::string&)),
	    this,SLOT(displayStatusText(const std::string&)));

    connect(editorWidget,
            SIGNAL(displayProperties(const IPropertyDescription&)),
	    this,
            SLOT(displayProperties(const IPropertyDescription&)));

    connect(editorWidget,SIGNAL(undisplayProperties()),
	    this,SLOT(undisplayProperties()));

    connect(editorWidget,SIGNAL(newEditGraph(const std::string&,
					     const std::string&)),
	    graphNameView->signalObject(),
	    SLOT(editGraphChanged(const std::string&,const std::string&)));

    connect(this,SIGNAL(renderedGraphChangedSignal(const std::string&)),
	    graphNameView->signalObject(),
	    SLOT(renderedGraphChanged(const std::string&)));

    connect(graphNameView->signalObject(), SIGNAL(undisplayProperties()),
            this, SLOT(undisplayProperties()));

    engineWrapper->rendererStatusSender().registerRendererStatusReceiver(*this);
  }

  void VJMainWindow::clearSceleton()
  {

    if (graphNameView)
      {
        delete graphNameView;
        graphNameView = 0;
      }

    if (centralWidget) 
      {
	//this->removeChild(centralWidget);
	delete centralWidget;
	centralWidget = 0;
        buildSceleton();	
      }
  }

  void VJMainWindow::newGraph()
  {
    const std::string newGraphName = NewGraphDialog::open("newGraph");
    
    if (newGraphName!="")
      engineWrapper->modelControlReceiver().newGraph(newGraphName);
  }
  
  /**
   * Verbindet zur engine und baut die toolbar des Graphen zusammen
   **/
  void VJMainWindow::connectToEngine()
  {
    try
      {
	if (connected)
	  {
	    throw std::runtime_error("already connected");
	  }
	
	statusBar()->message("connecting to the engine ...");

        buildModuleBar();
        fillSceleton();

	try
	  {
	    this->connectToRealEngine();
	  }
	catch (std::runtime_error& e) 
	  {
	    // start engine
            statusBar()->message("trying to spawn gephex-engine...");
            std::vector<std::string> args;
            std::string binary_name =
              m_config.get_string_param("engine_binary");

#if defined(OS_POSIX)
            std::ostringstream arg;

            arg << binary_name
                << " --ipc_type=" << m_config.get_string_param("ipc_type")
                << " --ipc_port=" << m_config.get_int_param("ipc_port");

            args.push_back(arg.str());
            //            std::cout << arg.str() << "\n";

            binary_name = m_conf_base_dir  + "/run_in_terminal.sh";
#else
            std::ostringstream arg1;
            arg1 << "--ipc_type=" << m_config.get_string_param("ipc_type");
            
            args.push_back(arg1.str());
            
            std::ostringstream arg2;
            arg2 << "--ipc_port=" << m_config.get_int_param("ipc_port");

            args.push_back(arg2.str());
#endif

            //            std::cout << "binary_name = " << binary_name  << "\n";
            utils::spawn(binary_name, args);

            // give engine some time to start up
            utils::Timing::sleep(1000);

            statusBar()->message("trying to connect...");
            // try to connect
	    this->connectToRealEngine();
	  }


	statusBar()->message("connected");

        connected=true;
      } 
    catch(std::runtime_error& e) 
      {
        std::cout << e.what() << "\n";
	displayErrorMessage(e.what());
        connectToEngineAction->setEnabled(true);
        utils::Timing::sleep(1000);
        this->clearSceleton();
        this->unbuildModuleBar();
      }
  }


  void VJMainWindow::disconnectFromEngine(void)
  {
    if (!connected)
      {	
	displayErrorMessage("not connected with the engine");
        return;
      }
    connected = false;
		
    this->disconnectFromRealEngine();

    this->clearSceleton();

    this->unbuildModuleBar();
		
    statusBar()->message("disconnected");
  }


  void VJMainWindow::startStop()
  {
    setRendererState();
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

  void VJMainWindow::undisplayProperties()
  {
    try {
      propertyView->undisplayProperties();      
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
    AboutDialog* dlg = new AboutDialogImpl(this);
    dlg->show();
  }

  void VJMainWindow::changesSlot()
  {
    ChangesDialog* dlg = new ChangesDialog(this);
    dlg->show();
  }

  void VJMainWindow::dll_selector_closed()
  {
    showPlugInManagerAction->setOn(false);
  }

  void VJMainWindow::shutDown()
  {
    if (connected)
      engineWrapper->engineControlReceiver().shutDown();    
  }

  /*  void VJMainWindow::setKeyGrabState(bool state)
  {
    if (state)
      m_kbManager->turnOn();
    else
      m_kbManager->turnOff();
      }*/

  void VJMainWindow::setRendererState()
  {
    if (!connected)
      return;
    try 
      {
	if (!running)
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
