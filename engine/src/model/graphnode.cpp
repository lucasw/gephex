/* This source file is a part of the GePhex Project.

  Copyright (C) 2001-2003 

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

#include "graphnode.h"

#include "interfaces/imoduleclassspec.h"
//#include "utils/bufferutils.h"

namespace model
{
  
  GraphNode::GraphNode(const IModuleClassSpec& spec,int moduleID)
    : m_id(moduleID), m_spec(&spec)
  {
  }
  
  
  GraphNode::~GraphNode()
  {
  }	
  
  
  void GraphNode::setData(int type,const utils::Buffer& b)
  {
    m_datas[type] = b;
  }
  
  
  void GraphNode::unSetData(int type)
  {
    m_datas.erase(type);
  }
  
  
  int GraphNode::moduleID() const
  {
    return m_id;
  }
  
  
  const IModuleClassSpec& GraphNode::spec() const
  {
    return *m_spec;
  }
  
  
  const std::map<int,utils::Buffer>& GraphNode::data() const
  {
    return m_datas;
  }
  
  
  std::list<int> GraphNode::moduleDataList() const
  {
    std::list<int> dataList;
    
    for (std::map<int,utils::Buffer>::const_iterator it = m_datas.begin();
	 it != m_datas.end(); ++it)
      {
	dataList.push_back(it->first);
      }
    
    return dataList;
  }

}
