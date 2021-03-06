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

#include "logwindow.h"

namespace gui {
LogWindow::LogWindow(QWidget *parent) : QTextEdit(parent) { setReadOnly(true); }

void LogWindow::error(const std::string &text) {
  std::string msg = "@error@ " + text;
  append(msg.c_str());
}

void LogWindow::warning(const std::string &text) {
  std::string msg = "@warning@ " + text;
  append(msg.c_str());
}

void LogWindow::log(const std::string &text) {
  std::string msg = "@log@ " + text;
  append(msg.c_str());
}
} // namespace gui
