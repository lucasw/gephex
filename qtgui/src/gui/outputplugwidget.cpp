#include "outputplugwidget.h"

#include <qtooltip.h>

namespace gui
{

  OutputPlugWidget::OutputPlugWidget(QWidget* parent, const char* name, 
				     const QPixmap& free_,
				     const QPixmap& busy_,
				     std::string _name, std::string _type,
				     int _index, int _ID)
    : PlugWidget(parent,name,_name,_type,_index,_ID, free_, busy_) 
  {
    std::string toolTipText = _name + ":" + _type;
    QToolTip::add(this,toolTipText.c_str());
    setBackgroundPixmap(freePic);
  }


  void OutputPlugWidget::mouseMoveEvent(QMouseEvent* e)
  {
    if (lineDrawMode)
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
    if (lineDrawMode)
      {
	lineDrawMode = false;
	emit connectionRequestFromOutput(this,e->pos()+this->pos()+
					 parentWidget()->pos());	
      }
  }


} // end of namespace gui
