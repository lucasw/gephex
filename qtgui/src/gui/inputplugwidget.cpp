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

#include <qtooltip.h>

namespace gui
{

  InputPlugWidget::InputPlugWidget(QWidget* parent, const char* name,
				   const QPixmap& free_, const QPixmap& busy_, 
				   std::string _name, std::string _type,
				   const ParamMap& params,
				   int _index, int _ID, bool _inP)
    : PlugWidget(parent,name,_name,_type,_index,_ID, free_, busy_),
      inPropertyDialog(_inP), m_params(params)
  {
    std::string toolTipText = _name + ":" + _type;
    QToolTip::add(this,toolTipText.c_str());
    setBackgroundPixmap(freePic);
  }


  void InputPlugWidget::mouseMoveEvent(QMouseEvent* e)
  {
    if (lineDrawMode)
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
    if (lineDrawMode)
      {
	lineDrawMode = false;
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
    if(e->button() == LeftButton)
      {
	emit beginLineDraw();
	lineDrawMode = true;
      }
    else if(e->button() == RightButton)
      {
	emit beenRightClicked(this);
      }
  }


} // end of namespace gui
