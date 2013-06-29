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

#ifndef INCLUDED_PROPERTY_WIDGET_CONSTR_H
#define INCLUDED_PROPERTY_WIDGET_CONSTR_H

#include <string>
#include <map>

#include "base/iwidgetconstructor.h"

#include "utils/autoptr.h"

class IModelControlReceiver;

namespace gui
{

  class TypeViewConstructor;
  class ControlValueDispatcher;
  class PropertyWidget;

  /**
   * Diese Klasse wird benutzt um PropertyWidgets für die
   * PropertyView zu erzeugen.
   */

class PropertyWidgetConstr : public IWidgetConstructor
{
public:
  PropertyWidgetConstr(const TypeViewConstructor* con,
		       const std::map<std::string, std::string>& params,
		       int nodeID,int inIndex, int controlID,
		       const utils::AutoPtr<ControlValueDispatcher>& cvd,
		       IModelControlReceiver&);

  virtual ~PropertyWidgetConstr();

  virtual QWidget* constructWidget(QWidget* parent) const;

  virtual void destroyWidget(QWidget* w) const;

private:
  const TypeViewConstructor* m_viewConstructor;
  const std::map<std::string, std::string>& m_params;
  int m_nodeID;
  int m_inputIndex;
  int m_controlID;
  utils::AutoPtr<ControlValueDispatcher> m_dispatcher;
  IModelControlReceiver& mcr;
  PropertyWidget* w;
};

} // end of namespace gui

#endif
