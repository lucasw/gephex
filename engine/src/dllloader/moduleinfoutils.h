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

#ifndef INCLUDED_MODULE_INFO_UTILS_H
#define INCLUDED_MODULE_INFO_UTILS_H

#include <vector>
#include <string>

class ModuleAttributes;

namespace utils {
class Buffer;
}


namespace dllloader
{

/**
 * Verschafft Zugang zu Zusatzinformationen ueber Dlls. Das sind
 * die Informationen die von der engine nicht benoetigt werden.
 * Der von getInfo() zurückgelieferte Buffer wird geparst
 * und mit zusaetzlichen Informationen (eindeutiger Name, Typen der 
 * Plugs) erweitert.
 */
struct ModuleInfo
{
 static utils::Buffer enrichInfo(const char* data,int len,
				 const std::string& name,
				 const std::vector<std::string>& inNames,
				 const std::vector<std::string>& outNames);

};

}
#endif
