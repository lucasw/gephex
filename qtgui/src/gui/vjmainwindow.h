#ifndef INCLUDED_VJMAINWINDOW_H
#define INCLUDED_VJMAINWINDOW_H

#include <map>
#include <string>
#include <stdexcept>

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

  class VJMainWindow : public QMainWindow, public IRendererStatusReceiver
    {
      Q_OBJECT
	public: 

      typedef utils::AutoPtr<utils::StructReader> StructReaderPtr;


      VJMainWindow(QWidget* parent, const char* name,
		   const std::string& ipcType,
		   const std::string& locator, int port,
		   StructReaderPtr& config);

      ~VJMainWindow();

      virtual void started(  );
      virtual void stopped(  );
      virtual void renderedGraphChanged( const std::string& graphID );
	
    signals:
      void quitSignal(void);

      void renderedGraphChangedSignal( const std::string& graphID );
	
      public slots:
	void connectToEngine(void);
      void disconnectFromEngine(void);
	
      void startStop();
      void displayStatusText(const std::string& s);

      void displayProperties(const IPropertyDescription&);
	  void undisplayProperties();
      void displayErrorMessage(const std::string& text);

      void setCaption(const std::string&);


      private slots:
	void pollNetwork();
      void setRendererState(bool state);
      void setKeyGrabState(bool state);
      void shutDown();
      void synchronize();
	  void aboutSlot();
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
      
      QAction* rendererStateAction;
      QAction* connectToEngineAction;
      QAction* disConnectToEngineAction;
      QAction* synchronizeEngineAction;
      QAction* shutDownEngineAction;
      QAction* keyGrabStateAction;
	  QAction* aboutAction;
      
      // widgets
      QWidget* centralWidget;
      QSplitter* splitVertical;
      QSplitter* splitHorizontal;
      EditorWidget* editorWidget;
      QTabWidget* leftTab;
      QTabWidget* belowTab;
      QWidget* editor;

      LogWindow* logWindow;

      EngineWrapper* engineWrapper;

      bool running;
      bool connected;	
	
      ModuleClassView* moduleClassView;      
      GraphNameView* graphNameView;      

      enum {CONNECT_ENGINE, 
	    DISCONNECT_ENGINE, SHUTDOWN_ENGINE, SYNCHRONIZE_ENGINE,
	    STARTSTOP_ENGINE, WINDOW_DLL_SELECTOR,
	    KEYGRAB_ON, KEYGRAB_OFF};
	
      QPopupMenu* effectMenue;
      PicSwitch* switcher;

      PropertyView* propertyView;
	
      QPopupMenu* windows;
	  QPopupMenu* help;

      int propertyTabID;

      DllSelectorDialog* m_dllSelector;

      StructReaderPtr m_config;

      KeyboardManager* m_kbManager;
    };

} // end of namespace gui

#endif


