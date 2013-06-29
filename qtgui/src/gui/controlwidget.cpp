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

#include "controlwidget.h"

#include <QtGui/qlabel.h>
#include <QtGui/qlayout.h>
#include <QtGui/QMouseEvent>
#include "typeview.h"

namespace gui
{

  ControlWidget::ControlWidget(QWidget* parent, 
			       const std::string& name,
			       int controlID, int nodeID,
			       int inIndex,
			       const ParamMap& params,
			       const TypeViewConstructor* con)
    : QFrame(parent), m_name(name),
      m_controlID(controlID), m_nodeID(nodeID),
      m_inputIndex(inIndex), dragMode(false), m_label(0), m_view(0)
  {
    setFrameStyle(QFrame::Box|QFrame::Sunken);
    setLineWidth(1);
    setMidLineWidth(0);

    m_view = con->construct(this, params);

    QHBoxLayout* l = new QHBoxLayout(this);
    l->setMargin(2);
    l->setSpacing(0);

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
//	m_label->parentWidget()->removeChild(m_label);
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
    setToolTip(toolTipText.c_str());
	
    QWidget* parent;
    bool move = false;
    if ( m_label != 0 )
      {		
	parent = m_label->parentWidget();
//	parent->removeChild(m_label);
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
    if (dragMode)
      {
        emit moved(this, e->globalPos()-clickedPos);
      }
  }

  void ControlWidget::mousePressEvent(QMouseEvent* e)
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

  void ControlWidget::mouseReleaseEvent(QMouseEvent* e)
  {
    if (dragMode)
      {
	dragMode = false;
	emit released(this, e->globalPos()-clickedPos);
      }
  }

  void ControlWidget::syncInputValuesStarted()
  {
  }

  void ControlWidget::syncInputValuesFinished()
  {
  }

}
