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

#include <qmainwindow.h>

#include "interfaces/irendererstatusreceiver.h"

#include "utils/autoptr.h"

class QPopupMenu;
class QTabWidget;
class QSplitter;
class QAction;

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
  class DllSelectorDialog;  
  class LogWindow;  
  class KeyboardManager;

  class ProxyErrorReceiver;

  class VJMainWindow : public QMainWindow, public IRendererStatusReceiver
    {
      Q_OBJECT
	public: 

      typedef utils::AutoPtr<utils::StructReader> StructReaderPtr;


      VJMainWindow(QWidget* parent, const char* name,
                   const utils::ConfigManager& config,
                   const std::string& ipc_locator,
                   const std::string& conf_base_dir);

      virtual ~VJMainWindow();

      virtual void started(  );
      virtual void stopped(  );
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
      void dll_selector_closed();
	
    private:
      void createActions(void);
      void createWindows();
      void buildMenuBar(void);
      void buildModuleBar(void);
      void buildSceleton(void);
      void fillSceleton(void);

      void unbuildModuleBar(void);
      void clearSceleton(void);

      void connectToRealEngine() throw (std::runtime_error);
      void disconnectFromRealEngine() throw (std::runtime_error);
      
      // Actions
      QAction* quitAction;
      QAction* showPlugInManagerAction;
      
      QAction* newGraphAction;
      QAction* rendererStateAction;
      QAction* connectToEngineAction;
      QAction* disConnectToEngineAction;
      QAction* synchronizeEngineAction;
      QAction* shutDownEngineAction;
      //      QAction* keyGrabStateAction;
	  QAction* aboutAction;
	  QAction* changesAction;
      
      // widgets
      QWidget* centralWidget;
      QSplitter* splitVertical;
      QSplitter* splitHorizontal;
      EditorWidget* editorWidget;
      QTabWidget* leftTab;
      QTabWidget* belowTab;
      QWidget* editor;

      LogWindow* logWindow;

      std::auto_ptr<ProxyErrorReceiver> m_error_proxy;
      std::auto_ptr<EngineWrapper> engineWrapper;

      bool running;
      bool connected;	
	
      ModuleClassView* moduleClassView;      
      GraphNameView* graphNameView;      

      enum {CONNECT_ENGINE, 
	    DISCONNECT_ENGINE, SHUTDOWN_ENGINE, SYNCHRONIZE_ENGINE,
	    STARTSTOP_ENGINE, WINDOW_DLL_SELECTOR,
	    KEYGRAB_ON, KEYGRAB_OFF};
	
      QPopupMenu* effectMenue;
      QPopupMenu* graphMenue;
      PicSwitch* switcher;

      PropertyView* propertyView;
	
      QPopupMenu* windows;
	  QPopupMenu* help;

      int propertyTabID;

      DllSelectorDialog* m_dllSelector;

      const utils::ConfigManager& m_config;

      KeyboardManager* m_kbManager;

      std::string m_conf_base_dir;
    };

} // end of namespace gui

#endif


