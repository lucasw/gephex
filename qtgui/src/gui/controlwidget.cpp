#include "controlwidget.h"

#include <qtooltip.h>
#include <qlabel.h>

namespace gui
{

  ControlWidget::ControlWidget(QWidget* parent, 
			       const std::string& name,
			       int controlID, int nodeID,
			       int inIndex)
    : QFrame(parent,name.c_str(),0), m_name(name),
      m_controlID(controlID), m_nodeID(nodeID),
      m_inputIndex(inIndex), m_label(0)
  {
    setFrameStyle(QFrame::Box|QFrame::Sunken);
    setLineWidth(2);
    setMidLineWidth(0);
    setName(name);
  }

  ControlWidget::~ControlWidget()
  {
    //TODO qt paranoia!
    m_label->parentWidget()->removeChild(m_label);
    delete m_label;
  }

  QWidget* ControlWidget::getLabel()
  {
    return m_label;
  }

  void ControlWidget::valueChanged(const utils::Buffer& b)
  {
    emit valueChanged(m_nodeID, m_inputIndex, b);
  }

  void ControlWidget::setName(const std::string& newName)
  {
    m_name = newName;
    std::string toolTipText = m_name;
    QToolTip::add(this,toolTipText.c_str());
	
    QWidget* parent;
    bool move = false;
    if ( m_label != 0 )
      {		
	parent = m_label->parentWidget();
	parent->removeChild(m_label);
	delete m_label;
	m_label = 0;
      }
    else
      {
	move = true;
	parent = parentWidget();
      }

    m_label = new QLabel(newName.c_str(), parent);

    m_label->show();
    if ( move )
      {		
	m_label->move(pos().x(), pos().y() - m_label->height());	
      }
	
  }

  void ControlWidget::mouseMoveEvent(QMouseEvent* e)
  {
    if(dragMode){
      emit moved(this, mapToParent(e->pos()-clickedPos));
    }	
  }


  void ControlWidget::mousePressEvent(QMouseEvent* e)
  {
    clickedPos = e->pos();
    if(e->button() == LeftButton)
      {
	dragMode = true;
      }
    else if (e->button() == RightButton)
      {
	emit beenRightClicked(this, e->pos());
      }
  }

  void ControlWidget::mouseReleaseEvent(QMouseEvent* e)
  {
    if (dragMode)
      {
	dragMode = false;
	emit released(this,mapToParent(e->pos()-clickedPos));
      }
  }

  void ControlWidget::syncInputValuesStarted()
  {
  }

  void ControlWidget::syncInputValuesFinished()
  {
  }

  //---------------------------
  //  ControlWidgetConstructor
  //---------------------------


  ControlWidgetConstructor::ControlWidgetConstructor(const std::string& type,
						     const std::string& name,
						     const std::string& id):
    m_type(type),m_name(name),m_id(id)
  {
  }

  const std::string& ControlWidgetConstructor::getType()
  {
    return m_type;
  }

  const std::string& ControlWidgetConstructor::getName()
  {
    return m_name;
  }

  const std::string& ControlWidgetConstructor::getID()
  {
    return m_id;
  }


  ControlWidgetConstructor::~ControlWidgetConstructor()
  {
  }

}

