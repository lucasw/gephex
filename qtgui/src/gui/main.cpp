
#include <qapplication.h>

#include <fstream>
#include <iostream>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#ifdef OS_WIN32
#include <qwindowsstyle.h>
#else
#include <qmotifstyle.h>
#endif

#include "qmessagebox.h"

#include "ownstyle.h"
#include "vjmainwindow.h"

#include "utils/structreader.h"
#include "utils/autoptr.h"

typedef utils::AutoPtr<utils::StructReader> StructReaderPtr;
typedef utils::StructReader::ConfigMap ConfigMap;
static StructReaderPtr readConfigFile(const std::string& fileName)
{
  std::ifstream file(fileName.c_str());
	
  if (!file)
    throw std::runtime_error("Konnte Config file '" + fileName
			     + "' nicht öffnen.");
	
  std::string text;
	
  std::getline(file,text,(char) 255);
	
  file.close();
	
  StructReaderPtr sr(new utils::StructReader(text));
	
  return sr;
}

int main( int argc, char** argv )
{
  QApplication app( argc, argv );

#if (QT_VERSION < 300) && defined(OS_WIN32)
  app.setStyle( new gui::OwnStyle<QWindowsStyle>() );

#elif (QT_VERSION < 300) && !defined(OS_WIN32)
	
  app.setStyle( new gui::OwnStyle<QMotifStyle>() );
#endif


#if QT_VERSION >= 300
  // qt3 doesnt like the style template
  //app.setStyle( new gui::OwnStyle<QMotifStyle>() );
#endif

  try
    {
    std::string configFileName;
#ifdef OS_WIN32
    configFileName = "../guiw.conf";
#endif
#ifdef OS_POSIX
      std::string home = getenv("HOME");
      configFileName = home + "/.gephex/gui.conf";
#endif
      StructReaderPtr sr = readConfigFile(configFileName);
      std::string ipcLocator;

      std::string ipcType = sr->getStringValue("ipc_type");
	 if (ipcType == "inet")
	{
	  ipcLocator = sr->getStringValue("ipc_inet_hostname");
	}
     else if (ipcType == "unix")
	{
	  ipcLocator = sr->getStringValue("ipc_unix_node_prefix");
	}
      
	  else if (ipcType == "namedpipe")
	  {
	   ipcLocator = sr->getStringValue("ipc_namedpipe_servername");
	  }
      else
	{
	  throw std::runtime_error("Unknown IPC Type: " + ipcType);
	}
      
      int port = sr->getIntValue("ipc_port");

      gui::VJMainWindow *mainWin = new gui::VJMainWindow(0,"HauptFenster",
							 ipcType,
							 ipcLocator, port,
							 sr);
    
      //mainWin->setFixedSize(640, 480);

      app.connect(mainWin,SIGNAL(quitSignal(void)), &app,SLOT(quit(void)));
      app.setMainWidget(mainWin);
      mainWin->resize(640, 480);
      mainWin->show();

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

