#include "controlwidget.h"

#include <qtooltip.h>
#include <qlabel.h>
#include <qlayout.h>

#include "typeview.h"

namespace gui
{

  ControlWidget::ControlWidget(QWidget* parent, 
			       const std::string& name,
			       int controlID, int nodeID,
			       int inIndex,
			       const ParamMap& params,
			       const TypeViewConstructor* con)
    : QFrame(parent,name.c_str(),0), m_name(name),
      m_controlID(controlID), m_nodeID(nodeID),
      m_inputIndex(inIndex), m_label(0), m_view(0)
  {
    setFrameStyle(QFrame::Box|QFrame::Sunken);
    setLineWidth(2);
    setMidLineWidth(0);
    //    setName(name);

    m_view = con->construct(this, params);

    QSize size = m_view->size();
    this->resize(QSize(size.width()+4, size.height()+4));
    //    m_view->move(1,1);
    //    m_view->show();

    QHBoxLayout* l = new QHBoxLayout(this,2);
    l->addWidget(m_view);

    this->show();
    connect(m_view, SIGNAL(valueChanged(const utils::Buffer&)),
	    this, SLOT(changeValue(const utils::Buffer&)));
  }

  ControlWidget::~ControlWidget()
  {
    //TODO qt paranoia!
    if (m_label)
      {
	m_label->parentWidget()->removeChild(m_label);
	delete m_label;
      }
  }

  void ControlWidget::controlValueChanged(int /*nodeID*/,int /*intputIndex*/,
					  const utils::Buffer& newValue)
  {
    m_view->valueChange(newValue);
  }
  QWidget* ControlWidget::getLabel()
  {
    return m_label;
  }

  void ControlWidget::changeValue(const utils::Buffer& b)
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

}
