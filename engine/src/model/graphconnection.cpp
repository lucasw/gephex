#include "graphconnection.h"

#include <iostream>

namespace model
{

GraphConnection::GraphConnection(int id1,int outIndex,int id2,int inIndex)
  : m_id1(id1), m_outIndex(outIndex), m_id2(id2), m_inIndex(inIndex)
{
}

int GraphConnection::id1() const
{
	return m_id1;
}

int GraphConnection::id2() const
{
	return m_id2;
}

int GraphConnection::outIndex() const
{
	return m_outIndex;
}

int GraphConnection::inIndex() const
{
	return m_inIndex;
}


}
