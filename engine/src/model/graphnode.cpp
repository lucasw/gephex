#include "graphnode.h"

#include "interfaces/imoduleclassspec.h"
#include "utils/bufferutils.h"
#include <iostream>

namespace model
{

GraphNode::GraphNode(const IModuleClassSpec& spec,int moduleID)
	: m_id(moduleID), m_spec(&spec)
{
}

GraphNode::~GraphNode()
{
}	

void GraphNode::setData(int type,const utils::Buffer& b)
{
	m_datas[type] = b;
}

void GraphNode::unSetData(int type)
{
	m_datas.erase(type);
}

int GraphNode::moduleID() const
{
	return m_id;
}

const IModuleClassSpec& GraphNode::spec() const
{
	return *m_spec;
}

const std::map<int,utils::Buffer>& GraphNode::data() const
{
	return m_datas;
}

std::list<int> GraphNode::moduleDataList() const
{
	std::list<int> dataList;

	for (std::map<int,utils::Buffer>::const_iterator it = m_datas.begin();
		it != m_datas.end(); ++it)
	{
		dataList.push_back(it->first);
	}

	return dataList;
}


}
