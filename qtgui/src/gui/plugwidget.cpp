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

#include "plugwidget.h"

namespace gui
{
  PlugWidget::PlugWidget(QWidget* parent, const char* name,
			 std::string _name, std::string _type, 
			 int _index, int _ID, const QPixmap& free_, 
			 const QPixmap& busy_)
    : QWidget(parent,name,WStyle_Customize|WStyle_NoBorder/*|WStyle_Dialog*/),
      name(_name), type(_type), index(_index), ID(_ID), m_status(PLUG_FREE),
      lineDrawMode(false), freePic(free_), busyPic(busy_)
  {
    this->setFixedSize(8, 8);
    this->setBackgroundPixmap(freePic);
    this->setMouseTracking(true);
  }

  void PlugWidget::mousePressEvent(QMouseEvent* e)
  {
    if(e->button() == LeftButton)
      {
	emit beginLineDraw();
	lineDrawMode = true;
      }
  }


  void PlugWidget::setStatus(PlugStatus status)
  {
    m_status = status;
    switch (status)
      {
      case PLUG_FREE:
        setBackgroundPixmap(freePic);
        break;
      case PLUG_CONNECTED:
        setBackgroundPixmap(busyPic);
        break;
      }
  }

  void PlugWidget::highlight()
  {
    QPixmap hp(busyPic);
    hp.fill(Qt::yellow);
    setBackgroundPixmap(hp);
  }

  void PlugWidget::removeHighlight()
  {
    setStatus(m_status);
  }

} // end of namespace gui
