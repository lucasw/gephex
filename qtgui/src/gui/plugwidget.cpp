#include "plugwidget.h"

namespace gui
{

  PlugWidget::PlugWidget(QWidget* parent, const char* name,
			 std::string _name, std::string _type, 
			 int _index, int _ID, const QPixmap& free_, 
			 const QPixmap& busy_)
    : QWidget(parent,name,WStyle_Customize|WStyle_NoBorder/*|WStyle_Dialog*/),
    name(_name), type(_type), index(_index), ID(_ID), lineDrawMode(false), 
    freePic(free_), busyPic(busy_)
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


  void PlugWidget::setPixmap(bool which)
  {
    if(which)
      setBackgroundPixmap(freePic);
    else
      setBackgroundPixmap(busyPic);
  }


} // end of namespace gui





