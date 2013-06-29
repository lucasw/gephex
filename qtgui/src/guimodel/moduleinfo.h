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

#ifndef INCLUDED_MODULE_INFO_H
#define INCLUDED_MODULE_INFO_H

#include <string>
#include <vector>

#include "pluginfo.h"
#include "utils/autoptr.h"

namespace gui
{

class Xpm;

class ModuleInfo
{
public:
	ModuleInfo(const ModuleInfo& mi);

	ModuleInfo(const std::string& _identifer,const std::string& _name,
		const std::string& group, const std::vector<PlugInfo>& _inputs,
		const std::vector<PlugInfo>& _outputs, 
		utils::AutoPtr<Xpm>& _pixmap);
	
	ModuleInfo& operator=(const ModuleInfo& mi);
	
	~ModuleInfo();
	
	std::string getName() const;
	std::string getIdentifier() const;
	std::string getGroup() const;

	const std::vector<PlugInfo>& getInputs() const;
	const std::vector<PlugInfo>& getOutputs() const;
	const Xpm& getIcon() const;
	

private:
	std::string identifier;
	std::string name;
	std::string group;
	std::vector<PlugInfo> inputs;
	std::vector<PlugInfo> outputs;
	utils::AutoPtr<Xpm> pixmap;
};

} // end of namespace gui
#endif
