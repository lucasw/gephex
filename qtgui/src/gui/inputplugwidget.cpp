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

#include "inputplugwidget.h"

#include <QtGui/QMouseEvent>

namespace gui
{

  InputPlugWidget::InputPlugWidget(QWidget* parent,
				   const QPixmap& free_, const QPixmap& busy_, 
				   const std::string& name,
				   const std::string& type,
				   const ParamMap& params,
				   int index, int ID, bool inP)
    : PlugWidget(parent,name,type,index,ID, free_, busy_),
      inPropertyDialog(inP), m_params(params)
  {
    std::string toolTipText = name + ":" + type;
    setToolTip(toolTipText.c_str());
  }


  void InputPlugWidget::mouseMoveEvent(QMouseEvent* e)
  {
    if (m_lineDrawMode)
      {
	emit redrawLine(this->pos()+parentWidget()->pos() 
                        + QPoint(this->width() / 2,this->height() / 2),
			this->pos()+e->pos()+parentWidget()->pos());
      }
    else
      {
	emit underMouse(this);
      }
  }


  void InputPlugWidget::mouseReleaseEvent(QMouseEvent* e)
  {
    if (m_lineDrawMode)
      {
	m_lineDrawMode = false;
	emit connectionRequestFromInput(this,
					e->pos()+this->pos()
                                        +parentWidget()->pos());
      }
  }

  void InputPlugWidget::setInvisible()
  {
    if (inPropertyDialog)
      return;
    //    assert(!inPropertyDialog);
    //    emit wannaBeAProperty(getIndex());

    this->hide();
    inPropertyDialog = true;
  }

  void InputPlugWidget::setVisible()
  {
    if (!inPropertyDialog)
      return;
    //    assert(inPropertyDialog);
    //    emit dontWannaBeAProperty(getIndex());

    this->show();
    inPropertyDialog = false;
  }

  bool InputPlugWidget::isVisible() const
  {
    return !inPropertyDialog;
  }

  const InputPlugWidget::ParamMap& InputPlugWidget::getParams() const
  {
    return m_params;
  }
  
  void InputPlugWidget::mousePressEvent(QMouseEvent* e)
  {
    if(e->button() == Qt::LeftButton)
      {
	m_lineDrawMode = true;
      }
    else if(e->button() == Qt::RightButton)
      {
	emit beenRightClicked(this);
      }
  }


} // end of namespace gui
