/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

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

#include "moduleinfo.h"

#include "xpm.h"

namespace gui
{

  ModuleInfo::ModuleInfo(const ModuleInfo& mi) 
    : identifier(mi.identifier), name(mi.name), group(mi.group),
      inputs(mi.inputs), outputs(mi.outputs), pixmap(0)
  {
    if (mi.pixmap != 0)
      pixmap = utils::AutoPtr<Xpm>(new Xpm(*mi.pixmap));
  }

  ModuleInfo::ModuleInfo(const std::string& _identifier,
			 const std::string& _name,
			 const std::string& group_,
			 const std::vector<PlugInfo >& _inputs,
			 const std::vector<PlugInfo >& _outputs, 
			 utils::AutoPtr<Xpm>& _pixmap)
    : identifier(_identifier), name(_name), group(group_),
      inputs(_inputs), outputs(_outputs), 
      pixmap(_pixmap)
  {    
  }


  ModuleInfo& ModuleInfo::operator=(const ModuleInfo& mi)
  {
    if (this == &mi)
      return *this;

    identifier = mi.identifier;
    name = mi.name;
    inputs = mi.inputs;
    outputs = mi.outputs;	
    /*if (mi.pixmap != 0)
      pixmap = new Xpm(*mi.pixmap);
    else
      pixmap = 0;*/
    pixmap = mi.pixmap;

    return *this;
  }

  ModuleInfo::~ModuleInfo()
  {    
  }

  std::string ModuleInfo::getName() const { return name; }
  std::string ModuleInfo::getIdentifier() const { return identifier; }
  std::string ModuleInfo::getGroup() const { return group; }

  const std::vector<PlugInfo>& ModuleInfo::getInputs() const { return inputs; }
  const std::vector<PlugInfo>& ModuleInfo::getOutputs() const { return outputs; }
  const Xpm& ModuleInfo::getIcon() const { return *&*pixmap; }

}
