#include "datatree.h"

#include <iostream>
#include <stack>
#include <algorithm>

#include "idatatreepersistor.h"

#include "utils/bufferutils.h"

#include "inode.h"
#include "standardinode.h"


const int DataTree::ROOT=0;

/**
 * internal datastrukture for maintaining inodes in the datatree
 */
struct DataTree::INodeControlBlock
{
public:
  /**
   * Constructor
   */
  INodeControlBlock(INode* inode_,DataTreeTypes::INodeNumber num,
		    DataTreeTypes::INodeNumber parent);
    
  // attributes
  INode* inode; // pointer to data
  DataTreeTypes::INodeNumber iNodeNr;  // INodeNr of the node
  DataTreeTypes::INodeNumber parentINodeNr; // INodeNr of the nodes parent
};


DataTree::INodeControlBlock::INodeControlBlock(INode* inode_,
					       DataTreeTypes::INodeNumber num,
                                               DataTreeTypes::INodeNumber parent)
  :inode(inode_), iNodeNr(num),parentINodeNr(parent)
{
}


DataTree::DataTree()
{
  // create Rootnode
  INode* newINodePtr = new StandardINode(0);

  // create ControlBlock for the node
  INodeControlBlock* block = new INodeControlBlock(newINodePtr, ROOT, ROOT);

  // insert it in the tree
  inodes.insert(std::make_pair(ROOT,block));

  // set max node to INodeNR because it is the first one
  maxINodeNr = ROOT;
}

DataTree::~DataTree()
{
  for(INodeMap::iterator it=inodes.begin();it!=inodes.end();++it)
    {
      INodeControlBlock* block = it->second;

      delete block->inode;
      delete block;
    }
}


DataTreeTypes::INodeNumber
DataTree::createObject(DataTreeTypes::INodeNumber parent, INode* object)
  throw (std::runtime_error)
{
  // search for parent
  INodeMap::const_iterator it = inodes.find(parent);
  if (it==inodes.end())
    throw std::runtime_error("cant find parentinode"
			     "(DataTree::createObject())");

  // calculate a new unique for the new inode
  DataTreeTypes::INodeNumber newINodeNr(maxINodeNr + 1);

  // get INode from controllblock
  INodeControlBlock* block = it->second;

  if (block->inode->addChild(newINodeNr,(*this)))
    {
      INodeControlBlock* nBlock 
	= new INodeControlBlock(object,newINodeNr,parent);

      inodes.insert(std::make_pair(newINodeNr,nBlock));

      maxINodeNr = newINodeNr;

      return newINodeNr;
    }
  else // cant be added
    {
      throw std::runtime_error("can't add INode (DataTree::createObject())");
    }
}

void DataTree::deleteObject(DataTreeTypes::INodeNumber inode) 
  throw (std::runtime_error)
{
  // you cant delete the root node
  if (inode == ROOT)
    throw std::runtime_error("cant delete ROOT at DataTree::deleteObject()");

  // search for the object   
  INodeMap::iterator inodeInGlobalMapIt = inodes.find(inode);
  if (inodeInGlobalMapIt==inodes.end())
    throw std::runtime_error("cant find inode (DataTree::deleteObject())");

  // get the controllblock and the inode pointer for the object  
  INodeControlBlock* block = inodeInGlobalMapIt->second;
  INode* inodePtr = block->inode;

  // do sucide
  inodePtr->deleteINode( *this );

  // search for the parent of the node
  INodeMap::const_iterator parentInGlobalMapIt
    = inodes.find(block->parentINodeNr);

  if (parentInGlobalMapIt==inodes.end())
    throw std::runtime_error("cant find parent inode "
			     "(DataTree::deleteObject())");

  // get parent inode  
  INode* parentPtr = (*parentInGlobalMapIt).second->inode;

  (*parentPtr).delChild(inode, (*this) );

  /*std::list<DataTreeTypes::INodeNumber>::iterator inodeInParentListIt = std::find(parentPtr->children.begin(),parentPtr->children.end(),inode);
    if (inodeInParentListIt==parentPtr->children.end()) throw std::runtime_error("cant find inode in parent list (DataTree::deleteObject())");

    parentPtr->children.erase(inodeInParentListIt);		


    std::stack<DataTreeTypes::INodeNumber > stack;

    stack.push(inode);

    while (!stack.empty())
    {
    DataTreeTypes::INodeNumber inode = stack.top();
    stack.pop();

    INodeMap::iterator inodeInGlobalMapIt = inodes.find(inode);
    if (inodeInGlobalMapIt==inodes.end()) throw std::runtime_error("cant find inode (DataTree::deleteObject())");
    INode* inodePtr = (*inodeInGlobalMapIt).second;

    for (INodeIterator it = inodePtr->children.begin(); it != inodePtr->children.end(); ++it)
    {
    stack.push(*it);
    }

    delete inodeInGlobalMapIt->second;
    inodes.erase(inodeInGlobalMapIt);
    m_persistor.iNodeDeleted(inode, *this);
    }
	
  */

  delete inodeInGlobalMapIt->second;
  inodes.erase(inodeInGlobalMapIt);
}

DataTreeTypes::INodeType DataTree::getType(DataTreeTypes::INodeNumber inode)
  const throw (std::runtime_error)
{
  INodeMap::const_iterator inodeInGlobalMapIt = inodes.find(inode);
  if (inodeInGlobalMapIt == inodes.end())
    throw std::runtime_error("cant find inode (DataTree::getType())");

  INode* inodePtr = inodeInGlobalMapIt->second->inode;

  return inodePtr->getType();
}

DataTreeTypes::INodeIterator
DataTree::beginChildren(DataTreeTypes::INodeNumber inode)
  const throw (std::runtime_error)
{
  INodeMap::const_iterator inodeInGlobalMapIt = inodes.find(inode);

  if (inodeInGlobalMapIt == inodes.end())
    throw std::runtime_error("cant find inode (DataTree::beginChildren())");

  INode* inodePtr = inodeInGlobalMapIt->second->inode;

  return inodePtr->beginChildren( (*this) );
}


DataTreeTypes::INodeIterator
DataTree::endChildren(DataTreeTypes::INodeNumber inode) const
  throw (std::runtime_error)
{
  INodeMap::const_iterator inodeInGlobalMapIt = inodes.find(inode);

  if (inodeInGlobalMapIt == inodes.end())
    throw std::runtime_error("cant find inode (DataTree::endChildren())");

  INode* inodePtr = inodeInGlobalMapIt->second->inode;

  return inodePtr->endChildren( (*this) );
}

void DataTree::setData(int inode, const utils::Buffer& b)
  throw (std::runtime_error)
{
  INodeMap::const_iterator inodeInGlobalMapIt = inodes.find(inode);

  if (inodeInGlobalMapIt == inodes.end())
    throw std::runtime_error("cant find inode (DataTree::setData())");

  INode* inodePtr = inodeInGlobalMapIt->second->inode;

  inodePtr->setData(b);
}

const utils::Buffer& DataTree::getData(int inode) const
  throw (std::runtime_error)
{
  INodeMap::const_iterator inodeInGlobalMapIt = inodes.find(inode);

  if (inodeInGlobalMapIt == inodes.end())
    throw std::runtime_error("cant find inode (DataTree::getData())");

  INode* inodePtr = inodeInGlobalMapIt->second->inode;

  return inodePtr->getData();
}



// debug code for printing the tree to a stream
namespace {
  void printINode(std::ostream& s, const DataTree& tree, int depth,
		  DataTreeTypes::INodeNumber inode)
  {		
    for (int i = 0; i < depth; ++i)
      s << "  ";

    s << "INode: " << inode << "  -  Type: " << tree.getType(inode);
    s << " - Data: " << tree.getData(inode);
  }
}

std::ostream& operator<<(std::ostream& s, const DataTree& tree)
{
  std::stack<std::pair<DataTreeTypes::INodeNumber,int> > stack;

  stack.push(std::make_pair(DataTree::ROOT,0));

  while (!stack.empty())
    {
      DataTreeTypes::INodeNumber inode = stack.top().first;
      int depth		= stack.top().second;

      stack.pop();

      printINode(s,tree, depth,inode);
      s << std::endl;

      DataTreeTypes::INodeIterator it = tree.beginChildren(inode);
      DataTreeTypes::INodeIterator end = tree.endChildren(inode);
      for (; it != end; ++it)
	{
	  stack.push(std::make_pair(*it,depth + 1));
	}
    }

  s << std::endl;
  return s;
}
