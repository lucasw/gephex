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

#include "nodeproperty.h"

#include <iostream>

#include "typeviewfactory.h"
#include "propertywidgetconstructor.h"
#include "hidebuttonconstructor.h"
#include "inputplugwidget.h"

#include "guimodel/moduleinfo.h"

#include "utils/structreader.h"


namespace gui
{

NodeProperty::NodeProperty(const ModuleInfo& _info, 
			   std::vector<utils::AutoPtr<InputPlugWidget> >& ins,
			   const utils::AutoPtr<ControlValueDispatcher>& dispatcher,
			   IModelControlReceiver& mcr,
			   const std::string& media_path)
  : info(_info), inPlugs(ins),
    factory(new TypeViewFactory(media_path)) //TODO: is this wanted???
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
                               const utils::AutoPtr<ControlValueDispatcher>& dispatcher,
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
	  TypeViewFactory::TypeViewInfoList compWidgets 
	    = factory->getCompatibleViews(in.getType());
	
	  if (!compWidgets.empty())
	    widgetTypeStr = compWidgets.begin()->getID();
	}
      catch(...)
	{
	}
    }

  if (widgetTypeStr == "")
    return;

  try
    {
      TypeViewConstructor* con = factory->getConstructor(widgetTypeStr);

      int nodeID = in.getID();
      m_ctorsList.push_back(std::list<const IWidgetConstructor*>());
      std::list<const IWidgetConstructor*>& ctors = m_ctorsList.back();

      ctors.push_back(new PropertyWidgetConstr(con,
					       current.params,
					       nodeID,inputIndex,-1,
					       dispatcher,  model));

      ctors.push_back(new HideButtonConstructor(in));
      
      m_entries.push_back(PropertyEntry(current.name,ctors));
    }
  catch (std::runtime_error& e)
    {
      std::cerr << e.what() << std::endl; //TODO
    }

}

} // end of namespace gui
