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

#include "stringtokenizer.h"

namespace utils
{

StringTokenizer::StringTokenizer(const std::string& input,
				 std::string::size_type pos)
  : m_input(input), m_pos(pos)
{
}

std::string StringTokenizer::next(const std::string& delim)
{
	std::string token;
	
	if (m_pos != std::string::npos)
    {
		// start of found token
		std::string::size_type first = m_input.find_first_not_of(delim.c_str(), 
			m_pos);
		
		if( first != std::string::npos )
		{
			// length of found token
			std::string::size_type num = m_input.find_first_of(delim.c_str(),
				first) - first;
			// do all the work off to the side
			token = m_input.substr( first, num );
			
			// done; now commit using
			// nonthrowing operations only
			m_pos = first+num;
			if( m_pos != std::string::npos ) 
				++m_pos;
			if( m_pos >= m_input.size() ) 
				m_pos = std::string::npos;
		}
    }
	
	return token;
}

std::string::size_type StringTokenizer::getPos() const
{
	return m_pos;
}

const std::string& StringTokenizer::getString() const
{
	return m_input;
}

} // end of namespace utils
