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

#include "controlvalueset.h"

namespace model
{

  ControlValueSet::ControlValueSet(const std::string& id,
                                   const std::string& name)
    : m_id(id), m_name(name) {}

  std::string ControlValueSet::getID() const
  {
    return m_id;
  }

  std::string ControlValueSet::getName() const
  {
    return m_name;
  }

  void ControlValueSet::setName(const std::string& name)
  {
    m_name = name;
  }

  ControlValueSet::~ControlValueSet()
  {
  }

  void ControlValueSet::setControlValue(int nodeID,int inputIndex,
                                        const utils::Buffer& value)
  {
    values[std::make_pair(nodeID,inputIndex)] = value;
  }

  void ControlValueSet::deleteControlValue(int nodeID,int inputIndex)
  {
    ControlMap::iterator it = values.find(std::make_pair(nodeID, inputIndex));

    if (it != values.end())
      {
	values.erase(it);
      }
  }

  ControlValueSet::const_iterator ControlValueSet::begin() const
  {
    return values.begin();
  }

  ControlValueSet::const_iterator ControlValueSet::end() const
  {
    return values.end();
  }

  ControlValueSet::const_iterator
  ControlValueSet::find(const Control& pair) const
  {
    return values.find(pair);
  }


}
