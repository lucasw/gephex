#include "propertywidgetfactory.h"
#include "propertywidget.h"

#include <string>
#include <stdexcept>

// buildin propertywidgets
#include "propertywidgets/colorselectorwidget.h"
#include "propertywidgets/comboboxwidget.h"
#include "propertywidgets/fileselectorwidget.h"
#include "propertywidgets/fontselectorwidget.h"
#include "propertywidgets/lineeditwidget.h"
#include "propertywidgets/numberselectorwidget.h"
#include "propertywidgets/radiobuttonwidget.h"
#include "propertywidgets/videowallselectorwidget.h"

namespace gui
{

  PropertyWidgetFactory::PropertyWidgetFactory()
  {
		// add new PropertyWidgets here
		registerPropertyWidgetConstructor(new PropertyLineEditWidgetConstructor());
		registerPropertyWidgetConstructor(new PropertyFileSelectorWidgetConstructor());
		registerPropertyWidgetConstructor(new PropertyComboBoxWidgetConstructor());
		registerPropertyWidgetConstructor(new PropertyFontSelectorWidgetConstructor());
		registerPropertyWidgetConstructor(new PropertyColorSelectorWidgetConstructor());
		registerPropertyWidgetConstructor(new PropertyNumberSelectorWidgetConstructor());
		registerPropertyWidgetConstructor(new PropertyRadioButtonWidgetConstructor());
		registerPropertyWidgetConstructor(new PropertyVideoWallWidgetConstructor());
  }

  PropertyWidgetFactory::~PropertyWidgetFactory()
  {
  }

	void PropertyWidgetFactory::registerPropertyWidgetConstructor(PropertyWidgetConstructor* constr)
	{
    #ifndef NDEBUG
	  //    std::cout << "registerProperty : " << constr->getType() << " - " << constr->getID() << std::endl;
    #endif
    propertyMapper[constr->getType()].push_back(PropertyWidgetInfo(constr->getID()));
    ID2ConstrMapper[constr->getID()]=constr;
	}

  PropertyWidget*
  PropertyWidgetFactory::createPropertyWidget(QWidget* parent,
					      const std::map<std::string,
					      std::string>& params,
					      const std::string& propertyType,
					      int nodeID,int inIndex,
					      int controlID,
					      IModelControlReceiver& mo) const
  {
  std::map<std::string,PropertyWidgetConstructor*>::const_iterator it=
    ID2ConstrMapper.find(propertyType);

  if (it==ID2ConstrMapper.end())
    throw std::runtime_error("unknown propertyType : (PropertyWidgetFactory::createPropertyWidget)");
  else
    return it->second->construct(parent,it->second->getName(), controlID,nodeID, inIndex,params,mo);
  }

  const std::list<PropertyWidgetInfo>&
  PropertyWidgetFactory::getCompatibleWidgetTypes(const std::string& type)
    const
  {
    std::map<std::string,std::list<PropertyWidgetInfo> >::const_iterator 
      it = propertyMapper.find(type);
		
    if (it == propertyMapper.end())
      {
	throw std::runtime_error("Property not found...sure this exists..?");
      }
		
    return it->second;
  }
	
} // end of namespace gui

