/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "standardinode.h"

StandardINode::StandardINode(DataTreeTypes::INodeType type_)
  : m_type(type_)
{
}


StandardINode::~StandardINode()
{
}

  // from INode
void StandardINode::attached(DataTreeTypes::INodeNumber myINodeNr,
			DataTree& dataTree)
{
}

bool StandardINode::addChild(DataTreeTypes::INodeNumber childINode,
			     DataTree& dataTree)
{
  m_children.push_back(childINode);
  return true;
}

void StandardINode::setData(const utils::Buffer& b)
{
  m_buf = b;
}

const utils::Buffer& StandardINode::getData() const
{
  return m_buf;
}

DataTreeTypes::INodeType StandardINode::getType() const
{
  return m_type;
}

DataTreeTypes::INodeIterator
StandardINode::beginChildren(const DataTree& dataTree) const
{
  return m_children.begin();
}

DataTreeTypes::INodeIterator
StandardINode::endChildren(const DataTree& dataTree) const
{
  return m_children.end();
}

void StandardINode::deleteINode(DataTree& dataTree)
{
}

void StandardINode::delChild(DataTreeTypes::INodeNumber childINode,
			     DataTree& dataTree)
{
  m_children.remove(childINode);
}

