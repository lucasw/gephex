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

#include "outputplugwidget.h"

#include <QtGui/QMouseEvent>

namespace gui
{

  OutputPlugWidget::OutputPlugWidget(QWidget* parent,
				     const QPixmap& free_,
				     const QPixmap& busy_,
				     const std::string& name,
				     const std::string& type,
				     int index, int ID)
    : PlugWidget(parent,name,type,index,ID, free_, busy_) 
  {
    std::string toolTipText = name + ":" + type;
    setToolTip(toolTipText.c_str());
  }


  void OutputPlugWidget::mouseMoveEvent(QMouseEvent* e)
  {
    if (m_lineDrawMode)
      {
       emit redrawLine(this->pos()+parentWidget()->pos() + QPoint(this->width() / 2,this->height() / 2),
			this->pos()+e->pos()+parentWidget()->pos());
      }
    else
      {
	emit underMouse(this);
      }
  }

  void OutputPlugWidget::mouseReleaseEvent(QMouseEvent* e)
  {
    if (m_lineDrawMode)
      {
	m_lineDrawMode = false;
	emit connectionRequestFromOutput(this,e->pos()+this->pos()+
					 parentWidget()->pos());	
      }
  }


} // end of namespace gui
