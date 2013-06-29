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

#ifndef _INCLUDED_NODE_PROPERTY_H__
#define _INCLUDED_NODE_PROPERTY_H__

#include <vector>
#include <map>
#include <string>
#include <QtGui/qdialog.h>

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
               const utils::AutoPtr<ControlValueDispatcher>& dispatcher,
	       IModelControlReceiver&,
	       const std::string& media_path);
  
  virtual ~NodeProperty();  

  virtual std::list<PropertyEntry> getEntries() const;


private:
  const ModuleInfo& info;
  std::vector<utils::AutoPtr<InputPlugWidget> >& inPlugs;

  //	ControlDispatcher* controller;
  TypeViewFactory* factory;
  std::list<PropertyEntry> m_entries;
  std::list<std::list<const IWidgetConstructor*> > m_ctorsList;

  void addProperty(InputPlugWidget& in,
                   const utils::AutoPtr<ControlValueDispatcher>&,
		   IModelControlReceiver&);


};

} // end of namespace gui

#endif
