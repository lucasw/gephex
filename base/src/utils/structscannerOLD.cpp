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

//TODO Unterschied zwischen string::size() und string::length() nachschauen
#include "structscanner.h"

#include "stringtokenizer.h"

StructScanner::StructScanner(IStructTokenListener& listener)
: m_listener(listener)
{
}

static std::string trim(const std::string& s, const std::string& delim)
{
	std::string::size_type pos = s.find_first_not_of(delim);

	if (pos == std::string::npos)
		return std::string();

	std::string::size_type pos2 = s.find_first_of(delim,pos);
	if (pos2 == std::string::npos)
		return s.substr(pos,s.length());

	return s.substr(pos,pos2);
}

void StructScanner::divideNameFromContent(const std::string& text,
										  std::string& name,std::string& content) const
{
	std::string::size_type pos = text.find('{');
	if (pos == std::string::npos)
	{
		throw std::runtime_error("Fehler beim scannen: { nicht vorhanden!");
	}

	name = trim(text.substr(0,pos)," \n\t");

	std::string::size_type pos2 = text.rfind('}');
	if (pos2 == std::string::npos)
	{
		throw std::runtime_error("Fehler beim scannen: } nicht vorhanden!");
	}

	content = text.substr(pos+1,pos2);
}

void StructScanner::processName(const std::string& name) const
{
	m_listener.scannedStructName(name);
}

void StructScanner::processContent(const std::string& content) const
{
	StringTokenizer st(content);

	std::string var = st.next(";=");
	while (var != "")
	{
		std::string value = st.next("';");
		m_listener.scannedPair(trim(var,"\n\t "),value);

		var = trim(st.next("=")," \n\t");
	}

	/*std::string::size_type pos = content.find("=");

	if (content[pos+1] == '\'')
	{
	}
	else
	{
		StringTokenizer st(content,pos+1);
		value = st.next(" \n\t");
	}*/
}


void StructScanner::scan(const std::string& text) const throw (std::runtime_error)
{
	std::string name;
	std::string content;

	divideNameFromContent(text,name,content);

	processName(name);

	processContent(content);
}

