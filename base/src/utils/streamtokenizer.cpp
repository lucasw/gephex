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

#include "streamtokenizer.h"

#include <iostream>

namespace utils
{
StreamTokenizer::StreamTokenizer(std::istream& input)
								 : m_input(input)
{
}

static bool goto_first_not_of(std::istream& s, const std::string& str)
{
	char c;
	while (s.get(c))
	{
		if (str.find(c) == std::string::npos)
		{
			s.unget();
			return true;
		}
	}
	
	return false;
}

static std::string goto_first_of(std::istream& s, const std::string& str)
{
	std::string result;
	char c;
	while (s.get(c))
	{
		if (str.find(c) != std::string::npos)
		{
			break;
		}
		result += c;
	}
	
	return result;
}
std::string StreamTokenizer::next(const std::string& delim)
{
	std::string token;
	
	if (m_input)
    {
		// start of found token
		bool first = goto_first_not_of(m_input,delim);
		
		if(first)
		{
			// length of found token
			token = goto_first_of(m_input,delim);
		}
    }
	
	return token;
}

} // end of namespace utils
