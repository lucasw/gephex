#include "labelwidget.h"

#include <QtGui/QMouseEvent>

namespace gui
{
  LabelWidget::LabelWidget(QWidget* parent, int id, const std::string& text)
    : QLabel(text.c_str(), parent), m_id(id), dragMode(false)
  {
    adjustSize();
  }

  int LabelWidget::id() const
  {
    return m_id;
  }


  void LabelWidget::mouseMoveEvent(QMouseEvent* e)
  {
    if (dragMode)
      {
        emit moved(this, e->globalPos()-clickedPos);
      }
  }


  void LabelWidget::mousePressEvent(QMouseEvent* e)
  {
    clickedPos = e->pos();
    if(e->button() == Qt::LeftButton)
      {
	dragMode = true;
        this->raise();
      }
    else if (e->button() == Qt::RightButton)
      {
	emit beenRightClicked(this, e->globalPos());
      }
  }

  void LabelWidget::mouseReleaseEvent(QMouseEvent* e)
  {
    if (dragMode)
      {
	dragMode = false;
	emit released(this, e->globalPos()-clickedPos);
      }
  }

}
