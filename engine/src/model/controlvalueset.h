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

#ifndef INCLUDED_CONTROLVALUESET_H
#define INCLUDED_CONTROLVALUESET_H

#include <string>
#include <map>
#include "utils/buffer.h"

namespace model
{

  class ControlValueSet 
    {
    public: 
      typedef int NodeID;
      typedef int InputIndex;
      typedef std::pair<NodeID,InputIndex> Control;
      typedef std::map<Control, utils::Buffer> ControlMap;

      typedef ControlMap::const_iterator const_iterator;

      /**
       * Create a new control value set for a graph
       */
      ControlValueSet(const std::string& id, const std::string& name);

      /**
       * destroys the set
       */
      ~ControlValueSet();

      /**
       * get the unique ID of the control-value set
       */
      std::string getID() const;

      /**
       * get the name of the control-value set
       */
      std::string getName() const;
      
      /**
       * change Name for the control-value set
       */
      void setName(const std::string& name);

      /**
       * add or change the value for the control
       */
      void setControlValue(NodeID nodeID, InputIndex inputIndex,
			   const utils::Buffer& value);

      /**
       * Removes the control-value pair from the set
       */
      void deleteControlValue(NodeID nodeID, InputIndex inputIndex);

      /**
       * get the iterator of the first control - value pair
       */
      const_iterator begin() const;

      /**
       * get the iterator of the control - value pair behind the last valid one
       */
      const_iterator end() const;

      /**
       * Get the control - value pair or the end() iterator if not found
       * /param key a pair of NodeID and InputIndex
       */
      const_iterator find(const Control& key) const;
	
    private:
      /**
       * unique id that cant be changed
       */
      const std::string m_id;

      /**
       * Name of the snapshot that is visible to the user
       */
      std::string m_name;

      /**
       * the stored values
       */
      ControlMap values;
    };

}
#endif
