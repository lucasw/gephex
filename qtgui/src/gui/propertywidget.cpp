#include "propertywidget.h"
#include "interfaces/imodelcontrolreceiver.h"

#include <qwidget.h>
#include <qtooltip.h>

#include <iostream>

namespace gui 
{

PropertyWidget::PropertyWidget(QWidget* parent, const char* name, WFlags fl, 
			       int nodeID, int inIndex, int controlID, 
				   IModelControlReceiver& mcr_,const std::map<std::string,std::string>& params)
  : QWidget(parent, name, fl), m_controlID(controlID), m_nodeID(nodeID),
    m_inputIndex(inIndex), mcr(mcr_)
{
	setFocusPolicy(QWidget::ClickFocus);	

	
	std::map<std::string, std::string>::const_iterator it = params.find("help");
	if (it != params.end())
	{
		std::string toolTip = it->second;

		QToolTip::add(this,toolTip.c_str());
	}
	
}

PropertyWidget::~PropertyWidget()
{
  //std::cout << "ljsdhlksdgh" << std::endl;
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

void PropertyWidget::syncInputValuesStarted()
{
}

void PropertyWidget::syncInputValuesFinished()
{
}

PropertyWidgetConstructor::PropertyWidgetConstructor(const std::string& type,const std::string& name,const std::string& id)
  :m_type(type),m_name(name),m_id(id)
{
}

PropertyWidgetConstructor::~PropertyWidgetConstructor()
{
}

const std::string& PropertyWidgetConstructor::getType()
{
  return m_type;
}

const std::string& PropertyWidgetConstructor::getName()
{
  return m_name;
}

const std::string& PropertyWidgetConstructor::getID()
{
  return m_id;
}

}


