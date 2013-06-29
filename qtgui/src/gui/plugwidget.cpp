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

#include <QtGui/QMouseEvent>
#include <QtGui/qpainter.h>

namespace gui
{
  PlugWidget::PlugWidget(QWidget* parent,
			 const std::string& name,
			 const std::string& type, 
			 int index,
			 int ID,
			 const QPixmap& free_, 
			 const QPixmap& busy_)
    : QWidget(parent),
      m_name(name), m_type(type), m_index(index), m_ID(ID), m_status(PLUG_FREE),
      m_lineDrawMode(false),
      m_freePic(free_), m_busyPic(busy_), m_pixmap(free_)
  {
    this->setFixedSize(8, 8);
    this->setMouseTracking(true);
  }

  void PlugWidget::mousePressEvent(QMouseEvent* e)
  {
    if(e->button() == Qt::LeftButton)
      {
	m_lineDrawMode = true;
      }
  }

  void PlugWidget::paintEvent(QPaintEvent*)
  {
    QPainter p(this);
    p.drawPixmap(0, 0, m_pixmap);
    p.drawRect(QRect(0, 0, width()-1, height()-1));
  }

  void PlugWidget::setStatus(PlugStatus status)
  {
    m_status = status;
    switch (status)
      {
      case PLUG_FREE:
        {
          m_pixmap = m_freePic;
        }
        break;
      case PLUG_CONNECTED:
        {
          m_pixmap = m_busyPic;
        }
        break;
      }
    update();
  }

  void PlugWidget::highlight()
  {
    QPixmap hp(m_busyPic);
    hp.fill(Qt::yellow);

    m_pixmap = hp;
    update();
  }

  void PlugWidget::removeHighlight()
  {
    setStatus(m_status);
  }

} // end of namespace gui
