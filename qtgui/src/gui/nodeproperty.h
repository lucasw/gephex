#ifndef _INCLUDED_NODE_PROPERTY_H__
#define _INCLUDED_NODE_PROPERTY_H__

#include <vector>
#include <map>
#include <string>
#include <qdialog.h>

//#include "controlchangelistener.h"
#include "ipropertydescription.h"

#include "utils/autoptr.h"

class QTable;

class IModelControlReceiver;

namespace gui
{

class ModuleInfo;
class InputPlugWidget;
class PropertyWidgetFactory;
class PropertyWidget;
class ControlValueDispatcher;

struct TempPropertyInfo
{
	std::map<std::string,std::string> params;
	std::string widgetType;
	int cell;
	std::string name;
};


class NodeProperty: public IPropertyDescription
{
public:
  NodeProperty(const ModuleInfo& _info, 
	       std::vector<utils::AutoPtr<InputPlugWidget> >& ins,
	       ControlValueDispatcher& dispatcher,
	       IModelControlReceiver&);
  
  virtual ~NodeProperty();  

  virtual std::list<PropertyEntry> getEntries() const;


private:
  const ModuleInfo& info;
  std::vector<utils::AutoPtr<InputPlugWidget> >& inPlugs;

  //	ControlDispatcher* controller;
  PropertyWidgetFactory* factory;
  std::list<PropertyEntry> m_entries;
  std::list<std::list<const IWidgetConstructor*> > m_ctorsList;

  void addProperty(InputPlugWidget& in, ControlValueDispatcher&,
		   IModelControlReceiver&);


};

} // end of namespace gui

#endif
