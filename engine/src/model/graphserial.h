/* This source file is a part of the GePhex Project.

  Copyright (C) 2001-2003 

  Georg Seidel <georg@gephex.org> 
  Martin Bayer <martin@gephex.org> 
  Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#ifndef INCLUDED_GRAPH_SERIAL_H
#define INCLUDED_GRAPH_SERIAL_H

#include <iosfwd>
#include "specmap.h"

namespace utils
{
  class ILogger;
}

namespace model
{
  class Graph;
  class GraphNode;
  class GraphConnection;
  
  std::ostream& operator<<(std::ostream& s, const model::Graph&);
  std::istream& deserializeGraph(std::istream& s, model::Graph&,
                                 const SpecMap& specMap,
                                 utils::ILogger& logger,
                                 bool noDummy = true);
}

#endif
