#ifndef INCLUDED_DATA_TREE_TYPES_H
#define INCLUDED_DATA_TREE_TYPES_H

#include <list>

struct DataTreeTypes
{
  typedef int INodeNumber;
  typedef int INodeType;
  typedef std::list<INodeNumber>::const_iterator INodeIterator;
};

#endif
