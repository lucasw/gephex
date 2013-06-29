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

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QPixmap>
#include <QtGui/QIcon>

#ifdef OS_WIN32
#include <memory>
#endif

#include "vjmainwindow.h"

#include "utils/configmanager.h"

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

  static std::string get_conf_base_dir()
  {
#if defined(OS_WIN32)
    return "../";
#elif defined(OS_POSIX)
    const char* HOME_STR = getenv("HOME");

    if (HOME_STR == 0)
      throw std::runtime_error("Could not read $HOME");

    return std::string(HOME_STR) + "/.gephex/0.4/";
#endif		
  }

  static std::string get_cfile_name()
  {
    return get_conf_base_dir() + "gephex.conf";
  }

//---------------------------------------------------------------------

int main( int argc, const char* argv[] )
{
  QApplication app( argc, (char**) argv );

  try
    {
      using namespace utils;
      ConfigManager::ParamList params;
      config_param_t::ParamValue def;

      params.push_back(config_param_t("media_path",
                                      config_param_t::STRING_PARAM,
                                      "common",
                                      "List of directories that contain "
                                      "videos, images and fonts "
                                      "(separated by ';')", 0));

      params.push_back(config_param_t("ipc_type",
                                      config_param_t::STRING_PARAM,
                                      "gui",
                                      "Communication mechanism (inet, unix, or"
                                      " namedpipe)", 0));

      params.push_back(config_param_t("ipc_inet_hostname",
                                      config_param_t::STRING_PARAM,
                                      "gui",
                                      "Hostname of engine (inet only)", 0));

      def.s = ".";
      params.push_back(config_param_t("ipc_namedpipe_servername",
                                      config_param_t::STRING_PARAM,
                                      "gui",
                                      "Servername of engine (namedpipe only)",
                                      &def));


      def.s = "/tmp/gephex_socket";
      params.push_back(config_param_t("ipc_unix_node_prefix",
                                      config_param_t::STRING_PARAM,
                                      "gui",
                                      "Path and prefix of the unix nodes "
                                      "in the filesystem (unix only)", &def));

      params.push_back(config_param_t("ipc_port",
                                      config_param_t::INT_PARAM,
                                      "gui",
                                      "Port on which the gui connects to the "
                                      "engine", 0));

      params.push_back(config_param_t("engine_binary",
                                      config_param_t::STRING_PARAM,
                                      "gui",
                                      "Full path of the gephex engine ", 0));


      utils::ConfigManager config(get_cfile_name(), argc, argv, params);

      // If the help message was requested, we simply return
      if (config.help_requested())
	return 0;

      std::string ipc_type = config.get_string_param("ipc_type");
      std::string ipc_locator = "";
        if (ipc_type == "inet")
          {
            ipc_locator = config.get_string_param("ipc_inet_hostname");
          }
        else if (ipc_type == "unix")
          {
            ipc_locator = config.get_string_param("ipc_unix_node_prefix");
          }
    
        else if (ipc_type == "namedpipe")
          {
            ipc_locator = config.get_string_param("ipc_namedpipe_servername");
          }
        else
          {
            throw std::runtime_error("Unknown IPC Type: " + ipc_type);
          }

      gui::VJMainWindow mainWin ( 0,
				  config,
                                  ipc_locator,
				  get_conf_base_dir());

      app.setWindowIcon(QIcon(QPixmap(logo_data)));

      app.connect(&mainWin, SIGNAL(quitSignal(void)), &app, SLOT(quit(void)));

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
