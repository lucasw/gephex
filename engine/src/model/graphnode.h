#ifndef INCLUDED_GRAPHNODE_H
#define INCLUDED_GRAPHNODE_H

#include <map>
#include <list>
#include "utils/buffer.h"

#include <iosfwd>


class IModuleClassSpec;


namespace model
{

class GraphNode
{
	GraphNode(const GraphNode&); //nicht impl.
	GraphNode& operator=(const GraphNode&); //nicht impl.
public:
	GraphNode(const IModuleClassSpec& spec,int moduleID);
	~GraphNode();

	void setData(int type,const utils::Buffer&);
	void unSetData(int type);

	int moduleID() const;
	const IModuleClassSpec& spec() const;

	const std::map<int,utils::Buffer>& data() const;

	std::list<int> moduleDataList() const;

private:
	int m_id;
	const IModuleClassSpec* m_spec;
	std::map<int,utils::Buffer> m_datas;
};



}

#endif
