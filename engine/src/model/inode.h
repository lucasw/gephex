#ifndef INCLUDED_INODE_H
#define INCLUDED_INODE_H

#include "datatreetypes.h"

class DataTree;

namespace utils {
  class Buffer;
}

class INode
{
public:

  /**
   * Is called after the INode was attached as a child INode in the tree
   * @param myInodeNr INodeNummber of the INode
   * @param dataTree The DataTree
   */
  virtual void attached(DataTreeTypes::INodeNumber myINodeNr,
			DataTree& dataTree) = 0;

  /**
   * Attaches a new INode as a Child of the INode
   * @param childINode Number of the new Inode
   * @param dataTree the Tree in which the two INodes are
   * @returns true if the Node can be attached else false
   */
  virtual bool addChild(DataTreeTypes::INodeNumber childINode,
			DataTree& dataTree) = 0;

  /**
   *
   *
   */
  virtual void delChild(DataTreeTypes::INodeNumber childINode,
			DataTree& dataTree) = 0;

  /**
   * Stores data. Previously stored data is overwritten.	 
   * @param b The data that is stored	 
   */
  virtual void setData(const utils::Buffer& b) = 0;

  /**
   * Returns the data stored in an inode.	 
   * @returns A buffer that contains the stored data of the inode
   *          (can be empty)	 
   */
  virtual const utils::Buffer& getData() const = 0;

  /**
   * Returns the type of an object.     
   * @returns the type of inode
   */
  virtual DataTreeTypes::INodeType getType() const = 0;

  /** 
   * Returns an iterator that points to the first child of 
   * an inode. The order of iteration is undefined.	 
   * @returns an iterator that points to the first child of 
   *          inode.	 
   */
  virtual DataTreeTypes::INodeIterator
  beginChildren(const DataTree& dataTree) const = 0;

  /** 
   * Returns an iterator that points to the position after the 
   * last child.	 
   * @returns an iterator that points behind the last child of 
   *          inode.	 
   */
  virtual DataTreeTypes::INodeIterator
  endChildren(const DataTree& dataTree) const = 0;

  /**
   * Tells the inode that it is deleted from the tree.
   */
  virtual void deleteINode(DataTree& dataTree) = 0;       

};

#endif
