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

#include <qlayout.h>
#include <qpainter.h>


#include "utils/buffer.h"

namespace gui
{


  class KleinesFeld : public QWidget
  {
    Q_OBJECT
  public:
    KleinesFeld(QWidget* parent, int xsize_, int ysize_);
    void setPos(const QPoint& p);

  signals:
    void posChanged(const QPoint&);

  protected:
    void paintEvent(QPaintEvent* pe);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

  private:
    void drawCuteLittleCross(const QPoint& p, QPainter& painter);
    QPoint pos, oldPos;
    QPainter mainPainter;
    int xsize;
    int ysize;
  };


  class PositionView : public gui::TypeView
  {
    Q_OBJECT
  public:
    PositionView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_setValueCalled(false)
    {
      this->resize(160, 120);

      m_mausFresser = new KleinesFeld(this,width()-10,height()-10);
      m_mausFresser->show();

      QBoxLayout* layout = new QBoxLayout(this, QBoxLayout::TopToBottom);

      layout->addWidget(m_mausFresser);

      connect(m_mausFresser, SIGNAL(posChanged(const QPoint&)),
	      this, SLOT(kleinesfeldChanged(const QPoint&)));
    }

    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    
      double x;
      double y;
      is >> x;
      is >> y;

      int x_ = (int) (m_mausFresser->width()  * x);

      int y_ = (int) (m_mausFresser->height() * y);

      m_setValueCalled = true;
      m_mausFresser->setPos(QPoint(x_,y_));
    }

public slots:
   void kleinesfeldChanged(const QPoint& p)
    {
    if (!m_setValueCalled)
      {
	if(p.x()<0 || p.x() >= width() || p.y() < 0 || p.y() >= height())
	  {
	    return;
	  }
	
	double x = ((double) p.x() / m_mausFresser->width());
	double y = ((double) p.y() / m_mausFresser->height());
		
	std::ostringstream os;
		
	os << x << " " << y;
	std::string str = os.str();
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



  KleinesFeld::KleinesFeld(QWidget* parent, int xsize_, int ysize_)
    : QWidget(parent,"kleines feld"), oldPos(-100,-100),
      xsize(xsize_), ysize(ysize_)
  {
    this->resize(xsize,ysize);
  }

  /**************************************************************************/

  void KleinesFeld::paintEvent(QPaintEvent* /*pe*/)
  {
    mainPainter.begin(this);
    QPen pen1(SolidLine);
    pen1.setColor(QColor(0,0,0));
    mainPainter.setPen(pen1);
    RasterOp rop = mainPainter.rasterOp();
    mainPainter.setRasterOp(Qt::CopyROP);
    this->drawCuteLittleCross(pos,mainPainter);
    mainPainter.setRasterOp(rop);
    mainPainter.end();	
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
  void KleinesFeld::mousePressEvent(QMouseEvent*) {};  
  void KleinesFeld::mouseReleaseEvent(QMouseEvent* e) {};


  void KleinesFeld::drawCuteLittleCross(const QPoint& p, QPainter& painter)
  {
    static const int SIZE = 3;
    painter.drawLine(p.x()-SIZE, p.y()-SIZE, p.x()+SIZE, p.y()+SIZE);
    painter.drawLine(p.x()-SIZE, p.y()+SIZE, p.x()+SIZE, p.y()-SIZE);
  }

  void KleinesFeld::setPos(const QPoint& p)
  {		
    pos = p;	
    mainPainter.begin(this);
    QPen pen1(SolidLine);
    pen1.setColor(this->backgroundColor());

    mainPainter.setPen(pen1);
    RasterOp rop = mainPainter.rasterOp();

    mainPainter.setRasterOp(Qt::XorROP);
		
    if (oldPos != pos)
      {
	this->drawCuteLittleCross(oldPos,mainPainter);
	this->drawCuteLittleCross(pos,mainPainter);
      }

    mainPainter.setRasterOp(rop);
		
    mainPainter.end();

    oldPos = pos;

    //    std::cout << "New position = (" << pos.x() << "," << pos.y()
    //      << ")" << std::endl;
	
    emit posChanged(pos);
    //repaint();
  }


}

#include "positionview_moc_cpp.cpp"
