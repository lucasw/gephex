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

#include "grapheditorwindow.h"

#include <qscrollview.h>

#include "grapheditor.h"

namespace gui
{

GraphEditorWindow::GraphEditorWindow(QWidget* parent, const char* name, 
				     WFlags fl, GraphModel& graphModel,
				     const IModuleInfoBaseStation& base,
					 const utils::AutoPtr<ControlValueDispatcher>& dispatcher,
				     IModelControlReceiver& mod,
				     KeyboardManager* kbManager,
                                     IErrorReceiver& log,
				     const std::string& media_path)
  : QMainWindow(parent,name,fl)
{
  QScrollView* graphScroller = new QScrollView(this);

  m_graphEditor = new GraphEditor(graphScroller->viewport(),"graph",
				  0,graphModel,base,dispatcher,mod,
				  kbManager, log, media_path);
  
  this->setCaption("Graph");
  
  graphScroller->addChild(m_graphEditor);
  m_graphEditor->resize(2000,2000);
  graphScroller->resize(200, 400);
  this->resize(400,200);
  graphScroller->center(1000,1000);

  this->setCentralWidget(graphScroller);
}

GraphEditor* GraphEditorWindow::graphEditor()
{
  return m_graphEditor;
}

} // end of namespace gui

