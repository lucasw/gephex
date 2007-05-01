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

#ifndef INCLUDED_GRAPH_EDITOR_WINDOW_H
#define INCLUDED_GRAPH_EDITOR_WINDOW_H

#include <string>

#include <QtGui/QScrollArea>

#include "utils/autoptr.h"

class IModelControlReceiver;
class IErrorReceiver;

namespace gui
{

  class GraphModel;
  class IModuleInfoBaseStation;
  class ControlValueDispatcher;
  class GraphEditor;
  class KeyboardManager;

  class GraphEditorWindow : public QScrollArea
  {
  public:
    GraphEditorWindow(QWidget* parent,
		      GraphModel& contr,
		      const IModuleInfoBaseStation&,
                      const utils::AutoPtr<ControlValueDispatcher>& dispatcher_,
		      IModelControlReceiver&,
		      KeyboardManager* kbManager,
                      IErrorReceiver& log,
		      const std::string& media_path);

    GraphEditor* graphEditor();

  private:
    GraphEditor* m_graphEditor;
  };


} // end of namespace gui

#endif

