#include "debugpersistor.h"

#include <iostream>

#include "datatree.h"

#include "utils/bufferutils.h"


DebugPersistor::DebugPersistor(std::ostream& s)
 : m_stream(s)
{
	m_stream << "DebugPersistor created" << std::endl;
}

DebugPersistor::~DebugPersistor()
{
	m_stream << "DebugPersistor deleted" << std::endl;
}
	
void DebugPersistor::loadDataTree(DataTree& tree)
{
	m_stream << "DebugPersistor (loadDataTree)" << std::endl;
}

void DebugPersistor::iNodeHasChanged(DataTreeTypes::INodeNumber& inode,
						 const DataTree& tree)
{
	m_stream << "DebugPersistor iNodeHasChanged:" << std::endl;

	m_stream << "INode-Nr: " << inode << std::endl;

	m_stream << "Data: " << tree.getData(inode) << std::endl;
}

void DebugPersistor::iNodeCreated(DataTreeTypes::INodeNumber& inode,
				  const DataTree& tree)
{
	m_stream << "DebugPersistor iNodeCreated:" << std::endl;

	m_stream << "INode-Nr: " << inode << std::endl;
}

void DebugPersistor::iNodeDeleted(DataTreeTypes::INodeNumber& inode,
				  const DataTree& tree)
{
	m_stream << "DebugPersistor iNodeDeleted:" << std::endl;

	m_stream << "INode-Nr: " << inode << std::endl;
}

void DebugPersistor::flush(const DataTree&)
{
	m_stream << "DebugPersistor flushed" << std::endl;
}
