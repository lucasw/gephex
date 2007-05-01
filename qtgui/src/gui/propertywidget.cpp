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

#include "propertywidget.h"

#include <QtGui/QWidget>
//#include <QtGui/qtooltip.h>
#include <QtGui/QBoxLayout>

#include "interfaces/imodelcontrolreceiver.h"

#include "typeview.h"

namespace gui 
{

  PropertyWidget::PropertyWidget(QWidget* parent,
                                 Qt::WFlags fl, 
                                 int nodeID, int inIndex, int controlID, 
                                 IModelControlReceiver& mcr_,
                                 const ParamMap& params,
                                 const TypeViewConstructor& con)
    : QWidget(parent,  fl), m_controlID(controlID), m_nodeID(nodeID),
      m_inputIndex(inIndex), mcr(mcr_), m_view(0)
  {
    setFocusPolicy(Qt::ClickFocus);
  
    m_view = con.construct(this, params);

    QHBoxLayout* l = new QHBoxLayout(this);
    l->setMargin(2);
    l->setSpacing(0);
    
    l->addWidget(m_view);

    connect(m_view, SIGNAL(valueChanged(const utils::Buffer&)),
            this, SLOT(changeValue(const utils::Buffer&)));

    show();
  }

  PropertyWidget::~PropertyWidget()
  {
  }

  void PropertyWidget::controlValueChanged(int /*nodeID*/,int /*intputIndex*/,
                                           const utils::Buffer& newValue)
  {
    m_view->valueChange(newValue);
  }

  int PropertyWidget::getControlID() const
  {
    return m_controlID;
  }

  int PropertyWidget::getNodeID() const
  {
    return m_nodeID;
  }

  int PropertyWidget::getInputIndex() const
  {
    return m_inputIndex;
  }

  void PropertyWidget::setValue(const utils::Buffer& b)
  {
    mcr.setInputValue(m_nodeID, m_inputIndex, b);
  }
  void PropertyWidget::changeValue(const utils::Buffer& b)
  {
    setValue(b);
  }

  void PropertyWidget::syncInputValuesStarted()
  {
  }

  void PropertyWidget::syncInputValuesFinished()
  {
  }

}
