/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef STANDARDINODE_H
#define STANDARDINODE_H

#include "inode.h"

#include "utils/buffer.h"

class StandardINode : public INode
{
public:

  /**
   * Constructor of a persistant INode
   * @param type_ TypeID of the new Node
   */
  StandardINode(DataTreeTypes::INodeType type_);

  virtual ~StandardINode();

  // from INode
  virtual void attached(DataTreeTypes::INodeNumber myINodeNr,
			DataTree& dataTree);

  virtual bool addChild(DataTreeTypes::INodeNumber childINode,
			DataTree& dataTree);

  virtual void setData(const utils::Buffer& b);

  virtual const utils::Buffer& getData() const;

  virtual DataTreeTypes::INodeType getType() const;

  virtual DataTreeTypes::INodeIterator
  beginChildren(const DataTree& dataTree) const;

  virtual DataTreeTypes::INodeIterator
  endChildren(const DataTree& dataTree) const;

  virtual void deleteINode(DataTree& dataTree);

  virtual void delChild(DataTreeTypes::INodeNumber childINode,
			DataTree& dataTree);

private:
  //DataTreeTypes::INodeNumber m_parent;
  DataTreeTypes::INodeType m_type;
  std::list<DataTreeTypes::INodeNumber> m_children;
  utils::Buffer m_buf;
};

#endif
