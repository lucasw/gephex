#ifndef INCLUDED_IDATA_TREE_PERSISTOR
#define INCLUDED_IDATA_TREE_PERSISTOR

/**
 * The interface IDataTreePersistor describes the functionality
 * needed to store a DataTree persistently.
 */

#include "datatreetypes.h"

class DataTree;

class IDataTreePersistor
{
public:

	/**
	 * Loads the persistent Data into the DataTree. This is called once
	 * at startup.
	 * @param tree The tree that is loaded.
	 */
	virtual void loadDataTree(DataTree& tree) = 0;


	/**
	 * The DataTree notifies the persistor that the content of an inode
	 * has changed. The persistor can write the change back at once or
	 * delay the write (at most until the next call of flush()).
	 * @param inode The number of the changed INode
	 * @param tree The tree whose INode has changed.
	 */
	virtual void iNodeHasChanged(DataTreeTypes::INodeNumber& inode,
				     const DataTree& tree) = 0;

	/**
	 * The DataTree notifies the persistor that an inode has been 
	 * created. The persistor can write the change back at once or
	 * delay the write (at most until the next call of flush()).
	 * @param inode The number of the created INode
	 * @param tree The tree whose INode has changed.
	 */
	virtual void iNodeCreated(DataTreeTypes::INodeNumber& inode,
				  const DataTree& tree) = 0;

	/**
	 * The DataTree notifies the persistor that an inode has been
	 * deleted. The persistor can write the change back at once or
	 * delay the write (at most until the next call of flush()).
	 * @param inode The number of the deleted INode
	 * @param tree The tree whose INode has changed.
	 */
	virtual void iNodeDeleted(DataTreeTypes::INodeNumber& inode,
				  const DataTree& tree) = 0;

	/**
	 * Writes back all changes. After a call of flush(),
	 * a call of loadDataTree(newTree) must result in newTree being
	 * equal to the original tree.
	 * @param tree The tree that is flushed
	 */
	virtual void flush(const DataTree& tree) = 0;
};

#endif
