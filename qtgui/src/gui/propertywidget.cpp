#include "propertywidget.h"
#include "interfaces/imodelcontrolreceiver.h"

#include <iostream>

#include <qwidget.h>
#include <qtooltip.h>
#include <qlayout.h>

#include "typeview.h"

namespace gui 
{

PropertyWidget::PropertyWidget(QWidget* parent, const char* name, WFlags fl, 
			       int nodeID, int inIndex, int controlID, 
			       IModelControlReceiver& mcr_,
			       const ParamMap& params,
			       const TypeViewConstructor& con)
  : QWidget(parent, name, fl), m_controlID(controlID), m_nodeID(nodeID),
    m_inputIndex(inIndex), mcr(mcr_), m_view(0)
{
  setFocusPolicy(QWidget::ClickFocus);
  
  m_view = con.construct(this, params);

  QHBoxLayout* l = new QHBoxLayout(this);
    
  m_view->show();
  l->addWidget(m_view);

  connect(m_view, SIGNAL(valueChanged(const utils::Buffer&)),
	  this, SLOT(changeValue(const utils::Buffer&)));
  }

PropertyWidget::~PropertyWidget()
{
  //std::cout << "ljsdhlksdgh" << std::endl;
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
