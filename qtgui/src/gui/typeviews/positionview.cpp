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

#include "positionview.h"

#include <sstream>
#include <iostream>

#include <QtGui/qlayout.h>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

#include "utils/buffer.h"

namespace gui
{


  class KleinesFeld : public QWidget
  {
    Q_OBJECT
  public:
    KleinesFeld(QWidget* parent,
                const QSize& preferredSize,
                const QSize& minimumSize);

    void setPos(const QPoint& p);

    QPoint pos() const
    {
      return m_pos;
    }

    QSize sizeHint() const
    {
      return m_preferredSize;
    }

    QSize minimumSizeHint() const
    {
      return m_minimumSize;
    }

  signals:
    void posChanged(const QPoint&);

  protected:
    void paintEvent(QPaintEvent* pe);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

  private:
    void drawCuteLittleCross(const QPoint& p, QPainter& painter);

    QPoint m_pos;
    QSize  m_preferredSize;
    QSize  m_minimumSize;
  };


  class PositionView : public gui::TypeView
  {
    Q_OBJECT
  public:
    PositionView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_setValueCalled(false)
    {
      static const int PREFERRED_WIDTH  = 160;
      static const int PREFERRED_HEIGHT = 120;
      static const int MIN_WIDTH  = 40;
      static const int MIN_HEIGHT = 30;


      m_mausFresser = new KleinesFeld(this,
                                      QSize(PREFERRED_WIDTH,
                                            PREFERRED_HEIGHT),
                                      QSize(MIN_WIDTH,
                                            MIN_HEIGHT));

      m_mausFresser->setSizeIncrement(4, 3);

      m_layout->addWidget(m_mausFresser);
      m_mausFresser->show();

      connect(m_mausFresser,
              SIGNAL(posChanged(const QPoint&)),
	      this, SLOT(kleinesfeldChanged(const QPoint&)));
    }

    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    
      double x;
      double y;
      is >> x;
      is >> y;

      QPoint newPos
        = QPoint(static_cast<int>(m_mausFresser->width()*x + 0.5),
                 static_cast<int>(m_mausFresser->height()*y + 0.5));

      if (m_mausFresser->pos() != newPos)
        {
          m_setValueCalled = true;
          m_mausFresser->setPos(newPos);
        }
    }

public slots:
void kleinesfeldChanged(const QPoint& p)
    {
      if (!m_setValueCalled)
        {
          if (p.x()<0 || p.x() >= width() || p.y() < 0 || p.y() >= height())
            {
              return;
            }
	
          double x = ((double) p.x() / m_mausFresser->width());
          double y = ((double) p.y() / m_mausFresser->height());
		
          std::ostringstream os;
		
          os << x << " " << y;
          const std::string str = os.str();
          const char* txt = str.c_str();
          utils::Buffer
            b = utils::Buffer(reinterpret_cast<const unsigned char*>(txt),
                              str.length() + 1);
          emit valueChanged(b);
        }
      else
        {
          m_setValueCalled = false;
        }
    }

  private:
    KleinesFeld* m_mausFresser;
    bool m_setValueCalled;
  };

  // constructor klass

  PositionViewConstructor::PositionViewConstructor():
    TypeViewConstructor("position input","pos_field")
  {
  }
		
  TypeView*
  PositionViewConstructor::construct(QWidget* parent,
				     const ParamMap& params) const
  {
    return new PositionView(parent,params);
  }



  KleinesFeld::KleinesFeld(QWidget* parent,
                           const QSize& preferredSize,
                           const QSize& minimumSize)
    : QWidget(parent),
      m_pos(preferredSize.width()/2, preferredSize.height()/2),
      m_preferredSize(preferredSize),
      m_minimumSize(minimumSize)
  {
    setSizePolicy(QSizePolicy::MinimumExpanding,
                  QSizePolicy::MinimumExpanding);
  }

  /**************************************************************************/

  void KleinesFeld::paintEvent(QPaintEvent* /*pe*/)
  {
    QPainter mainPainter(this);
    QPen pen1(Qt::SolidLine);
    pen1.setColor(QColor(0,0,0));
    mainPainter.setPen(pen1);
    drawCuteLittleCross(m_pos,mainPainter);
  }


  void KleinesFeld::mouseMoveEvent(QMouseEvent* e)
  {
    setPos(e->pos());
    // The parent widget must not receive this event
    // see comment below
    //QWidget::mouseMoveEvent(e);
  }
  
  /*
   * These function are overloaded to prevent the default implementation
   * from propagating the events to the parent widget.
   * This has happened with qt >= 3.0 (but not 2.3).
   * TODO: verify this works with qt 2.3
   */
  void KleinesFeld::mousePressEvent(QMouseEvent* e)
  {
    setPos(e->pos());
  }

  void KleinesFeld::mouseReleaseEvent(QMouseEvent* /*e*/)
  {
  }

  void KleinesFeld::drawCuteLittleCross(const QPoint& p, QPainter& painter)
  {
    static const int SIZE = 3;
    painter.drawLine(p.x()-SIZE, p.y()-SIZE, p.x()+SIZE, p.y()+SIZE);
    painter.drawLine(p.x()-SIZE, p.y()+SIZE, p.x()+SIZE, p.y()-SIZE);
  }

  void KleinesFeld::setPos(const QPoint& p)
  {
    if (p != m_pos)
      {
        m_pos = p;

        emit posChanged(m_pos);
        update();
      }
  }


}

#include "positionview_moc_cpp.cpp"
