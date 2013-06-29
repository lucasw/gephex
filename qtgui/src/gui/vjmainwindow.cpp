/* This source file is a part of the GePhex Project.

  Copyright (C) 2001-2006

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

#include <sstream>
#include <iostream>

#include <QtCore/QSettings>
#include <QtGui/qmenubar.h>
#include <QtGui/qlayout.h>
#include <QtGui/qtabwidget.h>
#include <QtGui/qstatusbar.h>
#include <QtGui/qsplitter.h>
#include <QtCore/qtimer.h>
#include <QtGui/QDockWidget>
#include <QtGui/QCloseEvent>

#include "base/propertyview.h"
#include "base/logwindow.h"
#include "base/keyboardmanager.h"

#include "editor/editorwidget.h"

#include "moduleclassview.h"

#include "graphnameview.h"

#include "picswitch.h"

#include "dialogs/aboutdialog.h"
#include "dialogs/changesdialog.h"
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
  
  VJMainWindow::VJMainWindow(QWidget* parent,
                             const utils::ConfigManager& config,
                             const std::string& ipc_locator,
                             const std::string& conf_base_dir)
			     
    : QMainWindow(parent),
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
    QCoreApplication::setOrganizationName("gephex");
    QCoreApplication::setOrganizationDomain("gephex.org");
    QCoreApplication::setApplicationName("gephex-gui");

    readSettings();

    createActions();

    buildMenuBar();
    
    switcher = new PicSwitch(statusBar(),
                             roter_mann,
			     gruener_mann);

    statusBar()->addPermanentWidget(switcher);
    
    connect(switcher, SIGNAL(clicked(int)), this, SLOT(startStop()));
    
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
		    this, SLOT(pollNetwork()));
    timer->start(20);
  }


  VJMainWindow::~VJMainWindow()
  {
    writeSettings();

    delete graphNameView;

    //TODO: the kbmanager is currently not used (set to 0)
    // if it is activated, there is a problem with the order of deletion:
    // the dtor of NodeWidget unregisters itself from the keyboardmanager,
    // but the keyboardmanager gets deleted before the nodewidgets
    // (they get deleted by qt).
    // Possible solution: keep keyboardmanager in a utils::AutoPtr.
  }

  void VJMainWindow::closeEvent(QCloseEvent* event)
  {
    event->accept();
  }

  namespace
  {
    QPoint pmax(const QPoint& a, const QPoint& b)
    {
      return QPoint(a.x() >= b.x() ? a.x() : b.x(),
		    a.y() >= b.y() ? a.y() : b.y());
    }
  }

  void VJMainWindow::writeSettings()
  {
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());

    settings.setValue("mainWindowState", saveState());

    // They all float down here...
    settings.setValue("propertyDockFloating", m_propDock->isFloating());
    settings.setValue("graphDockFloating", m_graphDock->isFloating());
    settings.setValue("logDockFloating", m_logDock->isFloating());

    settings.setValue("propertyDockPos", pmax(QPoint(0, 20),m_propDock->pos()));
    settings.setValue("propertyDockSize", m_propDock->size());
    
    settings.setValue("graphDockPos", pmax(QPoint(0, 20), m_graphDock->pos()));
    settings.setValue("graphDockSize", m_graphDock->size());

    settings.setValue("logDockPos", pmax(QPoint(0, 20), m_logDock->pos()));
    settings.setValue("logDockSize", m_logDock->size());
    settings.setValue("logDockHidden", m_logDock->isHidden());
  }

  void VJMainWindow::readSettings()
  {
    QSettings settings;
    QPoint position = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size      = settings.value("size", QSize(640, 480)).toSize();

    resize(size);
    move(position);

    m_winState = settings.value("mainWindowState").toByteArray();

    m_propDockFloating = settings.value("propertyDockFloating").toBool();
    m_propDockSize = settings.value("propertyDockSize",QSize(100,400)).toSize();
    m_propDockPos = settings.value("propertyDockPos",QPoint(0, 0)).toPoint();

    m_graphDockFloating = settings.value("graphDockFloating").toBool();
    m_graphDockSize = settings.value("graphDockSize", QSize(100,400)).toSize();
    m_graphDockPos = settings.value("graphDockPos", QPoint(0,0)).toPoint();

    m_logDockFloating = settings.value("logDockFloating").toBool();
    m_logDockSize = settings.value("logDockSize", QSize(100,400)).toSize();
    m_logDockPos = settings.value("logDockPos", QPoint(0,0)).toPoint();

    m_logDockHidden = settings.value("logDockHidden", false).toBool();
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
    quitAction= new QAction("QuitAction", this);
    quitAction->setText("Quit");
    quitAction->setToolTip ("exit the application");
    quitAction->setShortcut(QString("Ctrl+Q"));
    quitAction->setEnabled(true);
    connect(quitAction, SIGNAL(triggered()),
	    this, SLOT(quitSlot()));

    newGraphAction= new QAction("NewGraphAction", this);
    newGraphAction->setText("New Graph");
    newGraphAction->setToolTip ("create a new graph");
    newGraphAction->setEnabled(false);
    connect(newGraphAction,SIGNAL(triggered()),this,SLOT(newGraph()));

    rendererStateAction= new QAction("RendererStateAction", this);
    rendererStateAction->setText("start/stop rendering");
    rendererStateAction->setToolTip ("starts and stops the renderer");
    rendererStateAction->setEnabled(false);
    rendererStateAction->setShortcut(QString("Ctrl+ "));
    rendererStateAction->setCheckable( false );
    connect(rendererStateAction, SIGNAL(triggered()),
	    this,SLOT(setRendererState( )));      

    connectToEngineAction= new QAction("ConnectToEngineAction", this);
    connectToEngineAction->setText("Connect");
    connectToEngineAction->setToolTip ("connect to the engine");
    connectToEngineAction->setEnabled(false);
    connect(connectToEngineAction,SIGNAL(triggered()),
	    this,SLOT(connectToEngine()));

    disConnectToEngineAction= new QAction("disConnectToEngineAction", this);
    disConnectToEngineAction->setText("Disconnect");
    disConnectToEngineAction->setToolTip ("disconnect from the engine");
    disConnectToEngineAction->setEnabled(false);
    connect(disConnectToEngineAction,SIGNAL(triggered()),
	    this,SLOT(disconnectFromEngine()));

    synchronizeEngineAction= new QAction("synchronizeEngineAction", this);
    synchronizeEngineAction->setText("Sync");
    synchronizeEngineAction->setToolTip ("sync the gui with the engine");
    synchronizeEngineAction->setEnabled(false);
    connect(synchronizeEngineAction,SIGNAL(triggered()),
	    this,SLOT(synchronize()));
    
    shutDownEngineAction= new QAction("shutDownEngineAction", this);
    shutDownEngineAction->setText("kill the engine");
    shutDownEngineAction->setToolTip ("terminates the engine process");
    shutDownEngineAction->setEnabled(false);
    connect(shutDownEngineAction,SIGNAL(triggered()),
	    this,SLOT(shutDown()));

    /*    keyGrabStateAction= new QAction(this,"keyGrabStateAction");
    keyGrabStateAction->setText("Grab keyboard");
    keyGrabStateAction->setToolTip ("turn the keygrabber on/off");
    keyGrabStateAction->setEnabled(false);
    keyGrabStateAction->setCheckable ( true );
    connect(keyGrabStateAction,SIGNAL(toggled(bool)),
    this,SLOT(setKeyGrabState( bool )));*/
    
    aboutAction= new QAction("aboutAction", this);
    aboutAction->setText("About GePhex");
    //aboutAction->setToolTip ("shows some stuff");
    aboutAction->setEnabled(true);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(aboutSlot()));

    changesAction= new QAction("changesAction", this);
    changesAction->setText("Changes");
    changesAction->setToolTip ("Shows changes to previous version");
    changesAction->setEnabled(true);
    connect(changesAction,SIGNAL(triggered()),this,SLOT(changesSlot()));

    m_showLogAction = new QAction("showLogAction", this);
    m_showLogAction->setText("Show Message Window");
    m_showLogAction->setCheckable( true );
    m_showLogAction->setToolTip("Shows/hides the Message Window");
    connect(m_showLogAction, SIGNAL(triggered()), this, SLOT(showLogSlot()));
  }
  
  void VJMainWindow::buildMenuBar(void)
  {
    QMenu* file = menuBar()->addMenu("&File");
    file->addAction(quitAction);

    QMenu* server = menuBar()->addMenu("&Server");
    server->addAction(connectToEngineAction);
    server->addAction(disConnectToEngineAction);
    //server->addAction(synchronizeEngineAction);
    server->addAction(shutDownEngineAction);

    /*
    QPopupMenu* graphMenu = new QPopupMenu(this);
    menuBar()->insertItem("Graphs",graphMenu,2,2);
    newGraphAction->addTo(graphMenu);
    */

    QMenu* startstop = menuBar()->addMenu("&Engine");
    startstop->addAction(rendererStateAction);

    /*QPopupMenu* keyboard = new QPopupMenu(this);
      menuBar()->insertItem("Keyboard", keyboard,4,4);
      keyGrabStateAction->addTo(keyboard);*/

    effectMenue = menuBar()->addMenu("&Effects");

    QMenu* windows = menuBar()->addMenu("&Windows");
    windows->addAction(m_showLogAction);

    help = menuBar()->addMenu("&Help");
    help->addAction(aboutAction);
    help->addAction(changesAction);

    menuBar()->show();
  }


  void VJMainWindow::buildModuleBar(void)
  {
    moduleClassView = new ModuleClassView(effectMenue);

    // moduleClassView->show();
    engineWrapper->moduleClassModel().registerModuleClassView(*moduleClassView);
    //engineWrapper->moduleClassModel().registerModuleClassView(*moduleClassTabView);
  }

  void VJMainWindow::unbuildModuleBar()
  {
    // the effectmenue clears itself
    // when they receive the syncStarted call
    engineWrapper->moduleClassModel().unregisterModuleClassViews();	
    
    //engineWrapper->moduleClassNameSender().unregisterModuleClassNameReceiver(); //TODO der wird beim naechsten register automatisch ueberschrieben
    
    //delete effectMenue;
    
    effectMenue->clear();
  }

  void VJMainWindow::buildSceleton()
  {
    m_graphDock = new QDockWidget("Graphs",this);
    m_graphDock->setObjectName("graphDock");
    graphNameView = new GraphNameView(m_graphDock,
				      engineWrapper->modelControlReceiver(),
                                      *logWindow);
    m_graphDock->setWidget(graphNameView->widget());

    m_graphDock->setFeatures(QDockWidget::DockWidgetMovable |
			     QDockWidget::DockWidgetFloatable);

    addDockWidget(Qt::RightDockWidgetArea,m_graphDock);

    m_graphDock->resize(m_graphDockSize);
    if (m_graphDockFloating)
      {
        m_graphDock->setFloating(true);
        m_graphDock->move(m_graphDockPos);
      }



    m_propDock = new QDockWidget("Properties",this);
    m_propDock->setObjectName("propDock");
    propertyView = new PropertyView(m_propDock);
    m_propDock->setWidget(propertyView);

    m_propDock->setFeatures(QDockWidget::DockWidgetMovable |
                          QDockWidget::DockWidgetFloatable);

    addDockWidget(Qt::LeftDockWidgetArea, m_propDock);

    m_propDock->resize(m_propDockSize);
    if (m_propDockFloating)
      {
        m_propDock->setFloating(true);
        m_propDock->move(m_propDockPos);
      }

    m_logDock = new QDockWidget("Messages", this);
    m_logDock->setObjectName("logDock");
    logWindow = new LogWindow(m_logDock);
    m_logDock->setWidget(logWindow);
    addDockWidget(Qt::BottomDockWidgetArea, m_logDock);

    m_logDock->resize(m_logDockSize);
    if (m_logDockFloating)
      {
        m_logDock->setFloating(true);
        m_logDock->move(m_logDockPos);
      }

    if (m_logDockHidden)
      {
        m_logDock->hide();
      }


    engineWrapper->errorSender().registerErrorReceiver(*logWindow);
    m_error_proxy->set_client(logWindow);

    engineWrapper->graphNameSender().registerGraphNameReceiver(*graphNameView);


    editorWidget = new EditorWidget(this,
				    engineWrapper->graphModel(),
				    engineWrapper->modelControlReceiver(),
				    engineWrapper->controlModel(),
				    *moduleClassView,
				    engineWrapper->controlValueDispatcher(),
				    engineWrapper->moduleStatisticsSender(),
				    engineWrapper->modelStatusSender(),
				    &*m_kbManager, *logWindow,
				    m_config.get_string_param("media_path"));

    editorWidget->setObjectName("editorWidget");

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
    setCentralWidget(editorWidget);

    restoreState(m_winState);
  }

  void VJMainWindow::clearSceleton()
  {
    delete graphNameView;
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

	statusBar()->showMessage("connecting to the engine ...");

	buildModuleBar();
        buildSceleton();
	
	try
	  {
	    this->connectToRealEngine();
	  }
	catch (std::runtime_error& e) 
	  {
	    // start engine
            statusBar()->showMessage("trying to spawn gephex-engine...");
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

            statusBar()->showMessage("trying to connect...");
            // try to connect
	    this->connectToRealEngine();
	  }


	statusBar()->showMessage("connected");

        connected=true;
      } 
    catch(std::runtime_error& e) 
      {
        std::cout << e.what() << "\n";
	displayErrorMessage(e.what());
        connectToEngineAction->setEnabled(true);
        utils::Timing::sleep(1000);
        //this->clearSceleton();
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
		
    statusBar()->showMessage("disconnected");
  }


  void VJMainWindow::startStop()
  {
    setRendererState();
  }


  void VJMainWindow::displayStatusText(const std::string& s)
  {
    statusBar()->showMessage(s.c_str(),2500);
  }


  void VJMainWindow::displayProperties(const IPropertyDescription& pd)
  {
    try {
      propertyView->displayProperties(pd);
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
    QWidget::setWindowTitle(text.c_str());
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

  void VJMainWindow::changesSlot()
  {
    ChangesDialog* dlg = new ChangesDialog(this);
    dlg->show();
  }

  void VJMainWindow::showLogSlot()
  {
    if (m_logDock->isHidden())
      m_logDock->show();
    else
      m_logDock->hide();
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
