#include "nodeproperty.h"

#include <qtable.h>
#include <qpushbutton.h>
#include <qlayout.h>
//#include <qslider.h>

#include "propertywidgetfactory.h"
#include "propertywidgetconstructor.h"
#include "hidebuttonconstructor.h"
//#include "propertywidget.h"
//#include "nodewidget.h"
#include "inputplugwidget.h"

#include "guimodel/moduleinfo.h"
//#include "guimodel/controlvaluedispatcher.h"

#include "utils/structreader.h"


namespace gui
{


NodeProperty::NodeProperty(const ModuleInfo& _info, 
			   std::vector<utils::AutoPtr<InputPlugWidget> >& ins,
			   ControlValueDispatcher& dispatcher,
			   IModelControlReceiver& mcr)
  : info(_info), inPlugs(ins),
    factory(new PropertyWidgetFactory()) //TODO: is this wanted???
{
	
  const std::vector<PlugInfo>& in = _info.getInputs();
	
  for (unsigned int i= 0; i < in.size(); ++i)
    {
      addProperty(*ins[i], dispatcher, mcr);
    }
}

NodeProperty::~NodeProperty()
{
  delete factory;
}

std::list<PropertyEntry> NodeProperty::getEntries() const
{
  return m_entries;
}

void NodeProperty::addProperty(InputPlugWidget& in,
			       ControlValueDispatcher& dispatcher,
			       IModelControlReceiver& model)
{
  int inputIndex = in.getIndex();
  const PlugInfo& current = info.getInputs()[inputIndex];
  utils::StructReader sr(current.params);
  
  std::string widgetTypeStr = "";
  try
    {
      widgetTypeStr = sr.getStringValue("widget_type");      
    }
  catch(...)
    { 
      try
	{
	  const std::list<PropertyWidgetInfo>& compWidgets 
	    = factory->getCompatibleWidgetTypes(in.getType());
	
	  widgetTypeStr = compWidgets.begin()->getName();
	}
      catch(...)
	{
	}
    }

  if (widgetTypeStr == "")
    return;


  int nodeID = in.getID();
  m_ctorsList.push_back(std::list<const IWidgetConstructor*>());
  std::list<const IWidgetConstructor*>& ctors = m_ctorsList.back();
  
  ctors.push_back(new PropertyWidgetConstr(widgetTypeStr,
						current.params,
						nodeID,inputIndex,-1,
						*factory, dispatcher,
						model));

  ctors.push_back(new HideButtonConstructor(in));
      
  m_entries.push_back(PropertyEntry(current.name,ctors));


}

} // end of namespace gui
