#include "positionwidget.h"

#include "qlayout.h"

#include <sstream>

#include "utils/buffer.h"

namespace gui
{



  KleinesFeld::KleinesFeld(QWidget* parent, int xsize_, int ysize_)
    : QWidget(parent,"kleines feld"), oldPos(-100,-100),
      xsize(xsize_), ysize(ysize_)
  {
    this->resize(xsize,ysize);
  }


  void KleinesFeld::paintEvent(QPaintEvent* pe)
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
    QWidget::mouseMoveEvent(e);
  }


  void KleinesFeld::drawCuteLittleCross(const QPoint& p, QPainter& painter)
  {
    static const int SIZE = 4;
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
	
    emit posChanged(pos);
    //repaint();
  }




  PositionControlWidget::PositionControlWidget(QWidget* parent,
					       const std::string& name,
					       int id,
					       int nodeID,int inIndex)
    : ControlWidget(parent, name, id, nodeID, inIndex), itWasMe(false)
  {
    this->resize(160, 120);

    mausFresser = new KleinesFeld(this,width(),height());
    mausFresser->show();

    QBoxLayout* layout = new QBoxLayout(this,QBoxLayout::TopToBottom,10);
    layout->addWidget(mausFresser);

    connect(mausFresser, SIGNAL(posChanged(const QPoint&)),
	    this, SLOT(postNewPoint(const QPoint&)));
  }

  void PositionControlWidget::postNewPoint(const QPoint& p)
  {
    if (!itWasMe)
      {
	if(p.x()<0||p.x()>=width()||p.y()<0||p.y()>=height())
	  {
	    return;
	  }
		
	unsigned int x = (unsigned int)((double)p.x()/width() 
					* (double)UINT_MAX);

	unsigned int y = (unsigned int)((double)(height() - p.y())/height()
					* (double)UINT_MAX);
		
	std::ostringstream os;
		
	os << x << " " << y;
	std::string str = os.str();
		
	valueChanged(utils::Buffer(reinterpret_cast<const unsigned char*>(str.c_str()),
				   str.length()+1));
      }
    else
      {
	itWasMe = false;
      }
  }
  
  void PositionControlWidget::controlValueChanged(int nodeID,int intputIndex,
						  const utils::Buffer& newValue)
  {
    itWasMe = true;
    std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    
    unsigned int x;
    unsigned int y;
    is >> x;
    is >> y;

    double x_ = ((double) width() * x) / (double) UINT_MAX;
    double y_ = (double) height() - ((double) height() * y)
      / (double) UINT_MAX;
    mausFresser->setPos(QPoint(x_,y_));
  }

  // constructor klass

  PositionControlWidgetConstructor::PositionControlWidgetConstructor():
    ControlWidgetConstructor("typ_PositionType","Positionsfeld","pos_field")
  {
  }
		
  ControlWidget*
  PositionControlWidgetConstructor::construct(QWidget* parent,
					      const std::string& name,
					      int controlID,
					      int nodeID,
					      int inputIndex)
  {
    return new PositionControlWidget(parent,name,controlID,nodeID,inputIndex);
  }





}
