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

namespace utils {
  class StructReader;
}

namespace gui
{
  class EngineWrapper;
  class PicSwitch;
  class ModuleClassView;
  class ModuleClassTabView;
  class GraphNameView;
  class SequenceNameView;
  class PlaylistNameView;
  class PropertyView;
  class IPropertyDescription;
  class EditorWidget;
  class SequenceEditor;
  class DllSelectorDialog;
  class SequenceActionManager;
  class LogWindow;
  class Playlist;
  class ActionSequencerWrapper;

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
	
      void action(int);
	
      void startStop();
      void displayStatusText(const std::string& s);

      void displayProperties(const IPropertyDescription&);
      void displayErrorMessage(const std::string& text);

      void setCaption(const std::string&);


      private slots:
	void pollNetwork();
	
    private:
      void buildMenuBar(void);
      void buildModuleBar(void);
      void buildSceleton(void);
      void fillSceleton(void);

      void unbuildModuleBar(void);
      void clearSceleton(void);

      void connectToRealEngine() throw (std::runtime_error);
      void disconnectFromRealEngine() throw (std::runtime_error);
	
      // widgets
      QWidget* centralWidget;
      QSplitter* splitVertical;
      QSplitter* splitHorizontal;
      SequenceEditor* sequenceEditor;
      EditorWidget* editorWidget;
      QTabWidget* leftTab;
      QTabWidget* belowTab;
      QWidget* editor;

      LogWindow* logWindow;

      EngineWrapper* engineWrapper;

      bool running;
      bool connected;	
	
      ModuleClassView* moduleClassView;
      ModuleClassTabView* moduleClassTabView;
      SequenceActionManager* sam;
      GraphNameView* graphNameView;
      SequenceNameView* sequenceNameView;
      PlaylistNameView* playlistNameView;

      enum {FILE_QUIT, CONNECT_ENGINE, 
	    DISCONNECT_ENGINE, SHUTDOWN_ENGINE, SYNCHRONIZE_ENGINE,
	    STARTSTOP_ENGINE, WINDOW_DLL_SELECTOR, WINDOW_PLAYLIST};
	
      QPopupMenu* effectMenue;
      PicSwitch* switcher;

      PropertyView* propertyView;
	
      QPopupMenu* windows;

      int propertyTabID;

      DllSelectorDialog* m_dllSelector;

      Playlist* m_playlist;

      ActionSequencerWrapper* sequencerWrapper;
      ActionSequencerWrapper* playlistWrapper;

      StructReaderPtr m_config;
    };

} // end of namespace gui

#endif


