/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PERSISTENTINODE_H
#define PERSISTENTINODE_H

#include "standardinode.h"

class IDataTreePersistor;

class PersistentINode : public StandardINode
{
public:

  /**
   * Constructor of a persistant INode
   * @param parent_ INodeNumber of parent Inode
   * @param type_ TypeID of the new Node
   * @param persistor Object to make the Inode persistant
   */
  PersistentINode(DataTreeTypes::INodeType type_,
		  IDataTreePersistor& persistor);


  virtual ~PersistentINode();
  // from INode
  virtual void attached(DataTreeTypes::INodeNumber myINodeNr,
			DataTree& dataTree);

  virtual bool addChild(DataTreeTypes::INodeNumber childINode,
			DataTree& dataTree);

  virtual void setData(const utils::Buffer& b);
  virtual void deleteINode(DataTree& dataTree);
  virtual void delChild(DataTreeTypes::INodeNumber childINode,
			DataTree& dataTree);

private:
  IDataTreePersistor& m_persistor;
};


#endif
