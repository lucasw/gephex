#ifndef INCLUDED_GRAPHCONNECTION_H
#define INCLUDED_GRAPHCONNECTION_H

#include <iosfwd>

namespace model
{

class GraphConnection
{
	GraphConnection(const GraphConnection&); //nicht impl.
	GraphConnection& operator=(const GraphConnection&); //nicht impl.
public:
	GraphConnection(int id1,int outIndex,int id2,int inIndex);

	int id1() const;
	int id2() const;

	int outIndex() const;
	int inIndex() const;

private:
	int m_id1;
	int m_outIndex;
	int m_id2;
	int m_inIndex;
};

}

#endif
