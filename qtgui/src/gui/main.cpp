#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <qapplication.h>
#include <qmessagebox.h>
#include <qsound.h>

#ifdef OS_WIN32
#include <qwindowsstyle.h>
#else
#if QT_VERSION < 300
#include <qmotifstyle.h>
#endif
#endif

#if defined(OS_WIN32)
static const char* INTRO_PATH = "../data/intro.wav";
#elif defined(OS_POSIX)
//TODO: prefix!
static const char* INTRO_PATH = "../share/gephex/sounds/intro.wav";
#endif

#include "ownstyle.h"
#include "vjmainwindow.h"
#include "guiconfig.h"
#include <iostream>

int main( int argc, char** argv )
{
  QApplication app( argc, argv );

#if (QT_VERSION < 300) && defined(OS_WIN32)
  app.setStyle( new gui::OwnStyle<QWindowsStyle>() );

#elif (QT_VERSION < 300) && !defined(OS_WIN32)
	
  app.setStyle( new gui::OwnStyle<QMotifStyle>() );
#endif

  try
    {
      gui::GuiConfig config = gui::createGuiConfig();

      gui::VJMainWindow *mainWin = new gui::VJMainWindow(0,
							 "HauptFenster",
							 config.ipcType,
							 config.ipcLocator,
							 config.port,
							 config.sr);
    
      app.connect(mainWin,SIGNAL(quitSignal(void)), &app,SLOT(quit(void)));
      app.setMainWidget(mainWin);
      mainWin->resize(640, 480);
      mainWin->show();

    /*  if (QSound::available())
	QSound::play(INTRO_PATH);
      else
	std::cerr << "KEIN SOUND!!!" << std::endl;*/

      mainWin->connectToEngine();

      int ret = app.exec();
    
      return ret;

    }
  catch (std::runtime_error& e)
    {
      std::cerr << "Fehler: " << e.what() << std::endl;
	  QMessageBox::critical(0,"Schlimmer Fehler", e.what());
      //      getchar();   
    }

}

