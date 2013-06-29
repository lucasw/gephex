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

#include "moduleclassspec.h"


ModuleClassSpec::ModuleClassSpec(int mClassID, const std::vector<int>& ins,const std::vector<int>& outs)
 : m_moduleClassID(mClassID), m_inputs(ins), m_outputs(outs)
{
}

	//std::string identifier() const;
const std::vector<int>& ModuleClassSpec::inputs() const
{
	return m_inputs;
}

const std::vector<int>& ModuleClassSpec::outputs() const
{
	return m_outputs;
}

const int ModuleClassSpec::moduleClassID() const
{
	return m_moduleClassID;
}

IModuleClassSpec* ModuleClassSpec::clone() const
{
	return new ModuleClassSpec(*this);
}