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
	emit redrawLine(this->pos()+parentWidget()->pos(),
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
					e->pos()+this->pos()+parentWidget()->pos());
      }
  }

  void InputPlugWidget::setVisible()
  {
    if (inPropertyDialog)
      return;
    //    assert(!inPropertyDialog);
    //    emit wannaBeAProperty(getIndex());

    this->hide();
    inPropertyDialog = true;
  }

  void InputPlugWidget::setInvisible()
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
