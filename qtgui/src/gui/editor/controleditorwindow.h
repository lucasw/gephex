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

#ifndef INCLUDED_CONTROL_EDITOR_WINDOW_H
#define INCLUDED_CONTROL_EDITOR_WINDOW_H

#include <string>

#include <qmainwindow.h>

#include "utils/autoptr.h"

class IModelControlReceiver;

namespace gui
{
  class ControlEditor;
  class ControlModel;
  class ControlValueDispatcher;

class ControlEditorWindow : public QMainWindow
{
public:
  ControlEditorWindow(QWidget* parent, const char* name, WFlags fl,
		      ControlModel& cModel, IModelControlReceiver& model,
			  const utils::AutoPtr<ControlValueDispatcher>& disp,
		      const std::string& media_path);

  ControlEditor* controlEditor();

private:
  ControlEditor* m_controlEditor;
};

} // end of namespace gui

#endif
