#include "typeview.h"

#include <qwidget.h>
#include <qtooltip.h>

#include <iostream>

namespace gui 
{

TypeView::TypeView(QWidget* parent, const ParamMap& params)
  : QWidget(parent, "TypeView", 0), m_params(params)
{
  setFocusPolicy(QWidget::ClickFocus);

  ParamMap::const_iterator it = m_params.find("help");
  if (it != m_params.end())
    {
      std::string toolTip = it->second;
      
      QToolTip::add(this,toolTip.c_str());
    }
}

TypeView::~TypeView()
{
  //std::cout << "ljsdhlksdgh" << std::endl;
}


TypeViewConstructor::TypeViewConstructor(const std::string& name,
					 const std::string& viewID)
  : m_name(name),m_viewID(viewID)
{
}

TypeViewConstructor::~TypeViewConstructor()
{
}

const std::string& TypeViewConstructor::getName()
{
  return m_name;
}

const std::string& TypeViewConstructor::getViewID()
{
  return m_viewID;
}

}
