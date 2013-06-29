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

#include "controleditor.h"


namespace gui
{

  ControlEditorWindow::ControlEditorWindow(QWidget* parent, 
					   ControlModel& controlModel,
					   IModelControlReceiver& model,
					   const utils::AutoPtr<ControlValueDispatcher>& disp,
					   const std::string& media_path)
    : QScrollArea(parent)
  {
    m_controlEditor = new ControlEditor(this,
					controlModel,
					model,
					disp,
					media_path);

    m_controlEditor->setMinimumSize(1000, 2000);
    
    setWidget(m_controlEditor);
    setWidgetResizable(true);
  }

  ControlEditor* ControlEditorWindow::controlEditor()
  {
    return m_controlEditor;
  }

} // end of namespace gui
