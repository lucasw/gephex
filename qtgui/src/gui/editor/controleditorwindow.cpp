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

#include "controleditorwindow.h"

#include <qscrollview.h>

#include "controleditor.h"


namespace gui
{

  ControlEditorWindow::ControlEditorWindow(QWidget* parent,const char* name,
					   WFlags fl, 
					   ControlModel& controlModel,
					   IModelControlReceiver& model,
					   const utils::AutoPtr<ControlValueDispatcher>& disp,
					   const std::string& media_path)
    : QMainWindow(parent,name,fl)
  {
    QScrollView* controlScroller = new QScrollView(this);
    m_controlEditor = new ControlEditor(controlScroller->viewport(),
					"control",0,
					controlModel,model,disp,
					media_path);

    controlScroller->addChild(m_controlEditor);
    this->setCaption("Controls");

    m_controlEditor->resize(1000,1000);
    controlScroller->resize(200, 400);
    this->resize(400, 200);
    controlScroller->center(500,500);

    this->setCentralWidget(controlScroller);
  }

  ControlEditor* ControlEditorWindow::controlEditor()
  {
    return m_controlEditor;
  }

} // end of namespace gui
