/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

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


#include <iostream>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include <qapplication.h>
#include <qmessagebox.h>
#include <qpixmap.h>

#ifdef OS_WIN32
#include <qwindowsstyle.h>
#include <memory>
typedef QWindowsStyle GePhexStyle;
#else
#include <qmotifstyle.h>
typedef QMotifStyle GePhexStyle;
#endif

#include "ownstyle.h"
#include "guiconfig.h"
#include "vjmainwindow.h"

//---------------------------------------------------------------------

static const char* logo_data[] = { 
"40 40 8 1",
"# c #000200",
"a c #8e908d",
"b c #970d17",
". c #9ea09d",
"c c #c0121d",
"d c #e5171d",
"e c #eb2121",
"f c #ff0000",
"........................................",
"#######################################.",
"#######################################.",
"#######################################a",
"#######################################a",
"##########bbbbbbbbbbbbbbbbbb###########a",
"##########bbbbbbbbbbbbbbbbbb###########a",
"##########bbbbbccccccccccccc###########a",
"##########bbbccddddddddddddd###########a",
"##########bbbcdddddddddddddd###########a",
"##########bbcddeeeeeeeeeeeed###########a",
"####bbbbbb######dddeee######ccbbbb#####a",
"####bbbbbb######ccddee######cbbbbb#####a",
"####bbbbbc######bbcdee######bbbbbc#####a",
"####bbbccd######bbcdee######bbbccd#####a",
"####bbbcdd######bbcdde######bbbcdd#####a",
"####bbcdde######bbcdde######bbcdde#####a",
"####bbcddedcbbbbbbcdeedcbbbbbbcdee#####a",
"####bbcddedcbbbbbbcdeedcbbbbbbcdee#####a",
"####bbcddeddccccccddeeddccccccddee#####a",
"####bbcdeeeddddddddeeeeddddddddeee#####a",
"####bbcdeeeeeeeeeeeeffeeeeeeeeeeee#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffeeeeeeeeefffeeeeeeeeeee#####a",
"####bbcdee######dddeef######dddeee#####a",
"####bbcdde######ccddee######ccddee#####a",
"####bbcdde######bbcdee######bbcdee#####a",
"####bbcdde######bbcdee######bbcdee#####a",
"####bbcdde######bbcdde######bbcdde#####a",
"####bbcddd######bbcddd######bbcddd#####a",
"#######################################a",
"#######################################a",
"#######################################a",
"#######################################a",
".aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};


//---------------------------------------------------------------------

int main( int argc, char** argv )
{
  QApplication app( argc, argv );

  app.setStyle( new gui::OwnStyle<GePhexStyle>() );
  
  try
    {
      gui::GuiConfig config;

      gui::VJMainWindow mainWin ( 0, "GePhex main window", config );

      mainWin.setIcon(QPixmap(logo_data));

      app.connect(&mainWin, SIGNAL(quitSignal(void)), &app, SLOT(quit(void)));
      app.setMainWidget(&mainWin);

      mainWin.resize(640, 480);
      mainWin.show();    

      mainWin.connectToEngine();

      int ret = app.exec();
      
      return ret;
    }
  catch (std::runtime_error& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      QMessageBox::critical(0, "Fatal Error", e.what());
    }

}

//---------------------------------------------------------------------
