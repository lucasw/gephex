/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "persistentinode.h"

PersistentINode::PersistentINode(DataTreeTypes::INodeType type,
                                 IDataTreePersistor& persistor)
        : StandardINode(type), m_persistor(persistor)
{
}


PersistentINode::~PersistentINode()
{
}

void PersistentINode::attached(DataTreeTypes::INodeNumber myINodeNr,
			       DataTree& dataTree)
{
  StandardINode::attached(myINodeNr, dataTree);
}

bool PersistentINode::addChild(DataTreeTypes::INodeNumber childINode,
			       DataTree& dataTree)
{
  return StandardINode::addChild(childINode, dataTree);
}

void PersistentINode::setData(const utils::Buffer& b)
{
  StandardINode::setData(b);
}

void PersistentINode::deleteINode(DataTree& dataTree)
{
  StandardINode::deleteINode(dataTree);
}

void PersistentINode::delChild(DataTreeTypes::INodeNumber childINode,
			       DataTree& dataTree)
{
  StandardINode::delChild(childINode, dataTree);
}
