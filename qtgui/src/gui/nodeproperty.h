#ifndef _INCLUDED_NODE_PROPERTY_H__
#define _INCLUDED_NODE_PROPERTY_H__

#include <vector>
#include <map>
#include <string>
#include <qdialog.h>

//#include "controlchangelistener.h"
#include "base/ipropertydescription.h"

#include "utils/autoptr.h"

class IModelControlReceiver;

namespace gui
{

class ModuleInfo;
class InputPlugWidget;
class TypeViewFactory;
class ControlValueDispatcher;

/**
 * This class describes the properties of a module.
 */
class NodeProperty : public IPropertyDescription
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
  TypeViewFactory* factory;
  std::list<PropertyEntry> m_entries;
  std::list<std::list<const IWidgetConstructor*> > m_ctorsList;

  void addProperty(InputPlugWidget& in, ControlValueDispatcher&,
		   IModelControlReceiver&);


};

} // end of namespace gui

#endif
