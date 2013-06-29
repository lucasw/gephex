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

#ifndef INCLUDED_VJMAINWINDOW_H
#define INCLUDED_VJMAINWINDOW_H

#include <map>
#include <string>
#include <stdexcept>
#include <memory>

#include <QtGui/qmainwindow.h>

#include "interfaces/irendererstatusreceiver.h"

#include "utils/autoptr.h"

class QMenu;
class QTabWidget;
class QSplitter;
class QAction;
class QDockWidget;

namespace utils 
{
  class StructReader;
  class ConfigManager;
}

namespace gui
{
  class EngineWrapper;
  class PicSwitch;
  class ModuleClassView;
  class ModuleClassTabView;
  class GraphNameView;
  class PropertyView;
  class IPropertyDescription;
  class EditorWidget;
  class LogWindow;  
  class KeyboardManager;

  class ProxyErrorReceiver;

  class VJMainWindow : public QMainWindow, public IRendererStatusReceiver
  {
    Q_OBJECT
  public: 

    typedef utils::AutoPtr<utils::StructReader> StructReaderPtr;


    VJMainWindow(QWidget* parent,
                 const utils::ConfigManager& config,
                 const std::string& ipc_locator,
                 const std::string& conf_base_dir);

    virtual ~VJMainWindow();

    virtual void started();
    virtual void stopped();
    virtual void renderedGraphChanged( const std::string& graphID );
	
 signals:
    void quitSignal(void);

    void renderedGraphChangedSignal( const std::string& graphID );
	
  public slots:
    void connectToEngine();
    void disconnectFromEngine();
	
    void startStop();
    void displayStatusText(const std::string& s);

    void displayProperties(const IPropertyDescription&);
    void undisplayProperties();
    void displayErrorMessage(const std::string& text);

    void setCaption(const std::string&);
    void newGraph();


  private slots:
    void quitSlot();
    void pollNetwork();
    void setRendererState();
    //      void setKeyGrabState(bool state);
    void shutDown();
    void synchronize();
    void aboutSlot();
    void changesSlot();

    void showLogSlot();
	
  private:

    void closeEvent(QCloseEvent* event);

    void writeSettings();
    void readSettings();

    void createActions(void);
    void buildMenuBar(void);
    void buildModuleBar(void);
    void buildSceleton(void);

    void unbuildModuleBar(void);
    void clearSceleton(void);

    void connectToRealEngine() throw (std::runtime_error);
    void disconnectFromRealEngine() throw (std::runtime_error);
      
    // Actions
    QAction* quitAction;
      
    QAction* newGraphAction;
    QAction* rendererStateAction;
    QAction* connectToEngineAction;
    QAction* disConnectToEngineAction;
    QAction* synchronizeEngineAction;
    QAction* shutDownEngineAction;
    //      QAction* keyGrabStateAction;
    QAction* aboutAction;
    QAction* changesAction;
    QAction* m_showLogAction;
      
    // widgets
    EditorWidget* editorWidget;
    LogWindow* logWindow;

    std::auto_ptr<ProxyErrorReceiver> m_error_proxy;
    std::auto_ptr<EngineWrapper> engineWrapper;

    bool running;
    bool connected;	
	
    ModuleClassView* moduleClassView;      
    GraphNameView* graphNameView;      

    enum {CONNECT_ENGINE, 
          DISCONNECT_ENGINE, SHUTDOWN_ENGINE, SYNCHRONIZE_ENGINE,
          STARTSTOP_ENGINE,
          KEYGRAB_ON, KEYGRAB_OFF};
	
    QMenu* effectMenue;
    QMenu* graphMenue;
    PicSwitch* switcher;

    PropertyView* propertyView;
	
    QMenu* help;

    int propertyTabID;

    const utils::ConfigManager& m_config;

    KeyboardManager* m_kbManager;

    std::string m_conf_base_dir;

    // members below are used for reading settings

    QByteArray   m_winState;

    QDockWidget* m_propDock;
    QDockWidget* m_graphDock;
    QDockWidget* m_logDock;

    bool   m_propDockFloating;
    QSize  m_propDockSize;
    QPoint m_propDockPos;

    bool   m_graphDockFloating;
    QSize  m_graphDockSize;
    QPoint m_graphDockPos;

    bool   m_logDockFloating;
    QSize  m_logDockSize;
    QPoint m_logDockPos;

    bool   m_logDockHidden;
  };

} // end of namespace gui

#endif
