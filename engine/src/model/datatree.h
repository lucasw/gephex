#ifndef INCLUDED_DATA_TREE_H
#define INCLUDED_DATA_TREE_H

#include <iosfwd>
#include <stdexcept>

#include <list>
#include <map>

#include "utils/buffer.h"

#include "datatreetypes.h"

class INode;

/**
 * This class is a low level repository for hierarchical and typed data.
 * It will be used to store all data in the engine that must be
 * persistent or that must be made available to other components
 * in the engine.
 *
 * In the future an notifier mechanism will be implemented, that will allow
 * other components to receive notifies about changes of the content or
 * the structure of the data in the tree.
 */
class DataTree
{
private:
  DataTree(const DataTree&); // nicht impl.
  DataTree& DataTree::operator=(const DataTree&); // nicht impl.

public:	
  static const int ROOT;	

  /**
   * Constructs new DataTree object. Creates the ROOT node
   */
  DataTree();

  ~DataTree();

  /**
   * Create new object as a child of parent.
   * The root node with inode-nr ROOT always exists.
   * @param parent The inode number of the parent object.
   *               Use DataTree::ROOT for top level Objects.
   * @param object INode to add
   * @throw std::runtime_error if parent does not exist.
   * @returns The inode of the new object
   */
  DataTreeTypes::INodeNumber createObject(DataTreeTypes::INodeNumber parent,
					  INode* object) 
    throw (std::runtime_error);
  
  /**
   * Deletes an object. The whole subtree with root inode is deleted
   * recursively. The ROOT must not be deleted.
   * @param inode The inode number of the object to be deleted.
   * @throw std::runtime_error if inode does not exist or inode == ROOT.
   */
  void deleteObject(DataTreeTypes::INodeNumber inode)
    throw (std::runtime_error);

  /**
   * Returns the type of an object.
   * @param inode The inode number of the object.
   * @throw std::runtime_error if inode does not exist.
   * @returns the type of inode
   */
  DataTreeTypes::INodeType getType(DataTreeTypes::INodeNumber inode) const
    throw (std::runtime_error);

  /** 
   * Returns an iterator that points to the first child of 
   * an inode. The order of iteration is undefined.
   * @param inode The inode number
   * @returns an iterator that points to the first child of 
   *          inode.
   * @throw std::runtime_error if inode does not exist.
   */
  DataTreeTypes::INodeIterator beginChildren(DataTreeTypes::INodeNumber inode)
    const throw (std::runtime_error);

  /** 
   * Returns an iterator that points to the position after the 
   * last child.
   * @param inode The inode number
   * @returns an iterator that points behind the last child of 
   *          inode.
   * @throw std::runtime_error if inode does not exist.
   */
  DataTreeTypes::INodeIterator endChildren(DataTreeTypes::INodeNumber inode)
    const throw (std::runtime_error);

  /**
   * Stores data in an inode. Previously stored data is overwritten.
   * @param inode The inode number
   * @param b The data that is stored
   * @throw std::runtime_error if inode does not exist.
   */
  void setData(int inode, const utils::Buffer& b) throw (std::runtime_error);

  /**
   * Returns the data stored in an inode.
   * @param inode The inode number
   * @returns A buffer that contains the stored data of the inode
   *          (can be empty)
   * @throw std::runtime_error if inode does not exist.
   */
  const utils::Buffer& getData(int inode) const throw (std::runtime_error);

private:
  // Mapping from INode Numbers to InodeControlBlocks
  struct INodeControlBlock;
  typedef std::map<DataTreeTypes::INodeNumber, INodeControlBlock*> INodeMap;
  INodeMap inodes;
  // stores the maximum of all INode Numbers. used to generate unique
  // numbers
  DataTreeTypes::INodeNumber maxINodeNr;
};

/**
 * Streams a textual representation of the tree to an ostream.
 * This is only for debugging purposes
 * @param stream ostream to with the tree representation is send
 * @param tree The Tree to be streamed
 * @returns The Stream with the tree representation appended
 */
std::ostream& operator<<(std::ostream& stream, const DataTree& tree);

#endif
