#ifndef INCLUDED_GRAPH_SERIAL_H
#define INCLUDED_GRAPH_SERIAL_H

#include <iosfwd>

//#include <string>
//#include <map>

#include "specmap.h"

namespace model
{
  class Graph;
  class GraphNode;
  class GraphConnection;

  std::ostream& operator<< (std::ostream& s, const GraphNode& node);
  std::ostream& operator<<(std::ostream& s, const GraphConnection&);

  std::ostream& operator<<(std::ostream& s, const model::Graph&);
  //std::istream& operator>>(std::istream& s, model::Graph&);
  std::istream& deserializeGraph (std::istream& s, model::Graph&,
								  const SpecMap& specMap,
								  bool noDummy = true);
}

#endif
