#ifndef INCLUDED_DEBUG_PERSISTOR
#define INCLUDED_DEBUG_PERSISTOR

#include <iosfwd>

#include "idatatreepersistor.h"

class DebugPersistor : public IDataTreePersistor
{
public:
	DebugPersistor(std::ostream& s);
	virtual ~DebugPersistor();
	
	virtual void loadDataTree(DataTree& tree);

	virtual void iNodeHasChanged(DataTreeTypes::INodeNumber& inode,
						 const DataTree& tree);

	virtual void iNodeCreated(DataTreeTypes::INodeNumber& inode,
							  const DataTree& tree);

	virtual void iNodeDeleted(DataTreeTypes::INodeNumber& inode,
							  const DataTree& tree);

	virtual void flush(const DataTree& tree);

private:
	std::ostream& m_stream;
};

#endif
