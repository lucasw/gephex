#include "controlwidgetfactory.h"

#include <stdexcept>

#include "controlwidget.h"

#include "controlwidgets/sliderwidget.h"
#include "controlwidgets/comboboxwidget.h"
#include "controlwidgets/dialwidget.h"
#include "controlwidgets/positionwidget.h"
#include "controlwidgets/lineeditwidget.h"
#include "controlwidgets/videowallcontrolwidget.h"

namespace gui
{
  ControlWidgetFactory::ControlWidgetFactory()
  {
		// add new ControlWidgets here
		registerControlWidgetConstructor(new LineEditWidgetConstructor());
		registerControlWidgetConstructor(new ComboBoxWidgetConstructor());
		registerControlWidgetConstructor(new DialWidgetConstructor());
		registerControlWidgetConstructor(new PositionControlWidgetConstructor());
		registerControlWidgetConstructor(new HSliderWidgetConstructor());
		registerControlWidgetConstructor(new VSliderWidgetConstructor());
		//		registerControlWidgetConstructor(new VideoWallControlWidgetConstructor());
 }

  void ControlWidgetFactory::registerControlWidgetConstructor(ControlWidgetConstructor* constr)
	{
		// check for double registration of id
		std::map<std::string,ControlWidgetConstructor*>::const_iterator it=
			m_constructorMap.find(constr->getID());

		if (it==m_constructorMap.end())
		{
			m_constructorMap[constr->getID()]=constr; // add
      std::list<ControlWidgetInfo>& wlist = controlMapper[constr->getType()];
			wlist.push_back(ControlWidgetInfo(constr->getID(),constr->getName()));
		}
		else
		{
			throw std::runtime_error("double registration (ControlWidgetFactory::registerControlWidgetConstructor)");
		}


	}

  ControlWidget* ControlWidgetFactory::createControlWidget(QWidget* parent,
							  const std::string& name,
							   const std::string& widgetID,
							   int nodeID,
							   int inIndex,
							   int controlID) const
  {
 		// search widgetID in ConstructorMap
    std::map<std::string,ControlWidgetConstructor*>::const_iterator it=
	    m_constructorMap.find(widgetID);
		if (it!=m_constructorMap.end())
			return it->second->construct(parent,name.c_str(),controlID,nodeID,inIndex);
		else 	
       throw std::runtime_error(std::string("unknown ControlWidgetID: ")+widgetID);
  }

  std::list<ControlWidgetInfo>
  ControlWidgetFactory::getCompatibleControls(const std::string& type) const
  {
    std::map<std::string,std::list<ControlWidgetInfo> >::const_iterator 
      it = controlMapper.find(type);

    if (it == controlMapper.end())
      {
	std::list<ControlWidgetInfo> emptyList;
	return emptyList;
      }
    else
      {
	return it->second;
      }
  }

}


