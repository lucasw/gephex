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

#include <cassert>

#include "structscanner.h"
#include "stringtokenizer.h"

namespace utils
{

  static std::string ownSubstr(const std::string& content,
			       std::string::size_type begin,
			       std::string::size_type end)
  {
    std::string result;

    for (std::string::size_type i = begin; i < end; ++i)
      {
	result += content[i];
      }

    return result;
  }


  StructScanner::StructScanner(IStructTokenListener& listener)
    : m_listener(listener)
  {
  }

  static std::string trim(const std::string& s, const std::string& delim)
  {
    std::string::size_type pos = s.find_first_not_of(delim);

    if (pos == std::string::npos)
      return std::string();

    std::string::size_type pos2 = 0;
    for (int i = s.length()-1; i >= 0; --i)
      {
	std::string::size_type doof = delim.find(s[i]);
	if (doof == std::string::npos)
	  {
	    pos2 = i+1;
	    break;
	  }
      }
    if (pos2 <= pos)
      return "";

    return ownSubstr(s,pos,pos2);
  }

  void StructScanner::divideNameFromContent(const std::string& text,
					    std::string& name,
					    std::string& content) const
  {
    std::string::size_type pos = text.find('{');
    if (pos == std::string::npos)
      {
	std::string msg = "Fehler beim scannen: { nicht vorhanden! (";
	msg += text;
	msg += ")";
	throw std::runtime_error(msg.c_str());
      }

    name = trim(text.substr(0,pos)," \n\t");

    std::string::size_type pos2 = text.rfind('}');
    if (pos2 == std::string::npos)
      {
	std::string msg = "Fehler beim scannen: } nicht vorhanden! (";
	msg += text;
	msg += ")";
	throw std::runtime_error(msg.c_str());
      }

    content = ownSubstr(text,pos+1,pos2);
  }

  void StructScanner::processName(const std::string& name) const
  {
    m_listener.scannedStructName(name);
  }

  static bool is_whitespace(char c)
  {
    return c == ' ' || c == '\t' || c == '\n';
  }

  void StructScanner::processContent(const std::string& content) const
  {
    /*StringTokenizer st(content);

      std::string var = st.next(";=");
      while (var != "")
      {
      std::string value = st.next("';");
      m_listener.scannedPair(trim(var,"\n\t "),value,
      IStructTokenListener::TYPE_STRING);

      var = trim(st.next("=")," \n\t");
      }*/

    std::string::size_type index = 0;

    while (index < content.length())
      {
	std::string::size_type pos = content.find('=',index);
	if (pos == std::string::npos)
	  {
	    break;
	  }

	std::string var = ownSubstr(content,index,pos);

	std::string value;

	pos++; //first position after '='
	while (pos < content.length() && is_whitespace(content[pos]))
	  ++pos;
	       
	if (content[pos] == '[')
	  {
	    std::string::size_type pos2 = findNextClosingBracket(content,
								 pos+1);
	    if (pos2 == std::string::npos)
	      {
		//TODO
	      }

	    value = ownSubstr(content,pos+1,pos2);
	    assert(content[pos2] == ']');

	    index = pos2+1;
	  }
	else
	  {
	    StringTokenizer st(content,pos);
	    value = st.next("; \n\t");
	    index = st.getPos();
	  }

	m_listener.scannedPair(trim(var,"{;\n\t "),trim(value,";"),
			       IStructTokenListener::TYPE_STRING);
      }
  }

  std::string::size_type 
  StructScanner::findNextClosingBracket(const std::string& content,
					std::string::size_type n) const
  {
    int level = 1;
    for (std::string::size_type i = n; i < content.length(); ++i)
      {
	switch (content[i])
	  {
	  case '[':
	    ++level;
	    break;
	  case ']':
	    --level;
	    break;
	  }
	if (level == 0)
	  {
	    return i;
	  }
      }

    return std::string::npos;
  }

  void StructScanner::scan(const std::string& text) const 
    throw (std::runtime_error)
  {
    std::string name;
    std::string content;

    divideNameFromContent(text,name,content);

    processName(name);

    processContent(content);
  }

} // end of namespace utils
