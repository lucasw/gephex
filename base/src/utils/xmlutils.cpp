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

#include "xmlutils.h"

#include <iostream>
#include <stdexcept>


namespace utils
{

  static bool is_whitespace(char c)
  {
    static std::string WHITESPACES = " \t\n\r";  
    return WHITESPACES.find(c) != std::string::npos;
  }

  namespace xml
  {

    static Iterator scan_string(Iterator begin, 
                                Iterator end,
                                const std::string& s)
    {
      Iterator i = begin;
      while (i != end && is_whitespace(*i))
        ++i;

      for (std::string::const_iterator j = s.begin(); j != s.end(); ++j)
        {
          if (i == end || *i != *j)
            {
              std::string msg = "scan_string failed: expected '";
              msg += s + "'\n";
              if (i != end)
                {
                  msg += "*i = " ;
                  msg += *i;
                  msg += "\n";
                }
              msg += "*j = ";
              msg += *j;
              msg += "\n";
            throw std::runtime_error(msg.c_str());
            }

          ++i;
        }
      //      std::cout << "matched " << s << "\n";

      return i;
    }

    static Iterator scan_pcdata(Iterator begin, Iterator end, std::string& b)
    {
      Iterator i = begin;
      int len = 0;
      while (i != end && !(*i == '<' || *i == '>'))
        {
          ++i;
          ++len;
        }

      if (i == end)
        throw std::runtime_error("unexpected end at scan_pcdata");

      if (len == 0)
        {
          b = std::string("");
        }
      else
        {
          char* data = new char[len];
          int index = 0;
          for (Iterator j = begin; j != i; ++j, ++index)
            {
              data[index] = *j;
            }
      
          b = std::string(data, len);
          delete[] data;
        }
      return i;
    }

    std::string next_tag_name(Iterator begin, Iterator end)
    {
      std::string tag_name;
      Iterator i = begin;
      i = scan_string(i, end, "<");
      i = scan_pcdata(i, end, tag_name);
      i = scan_string(i, end, ">");

      return tag_name;
    }

    Iterator tagOpens(Iterator begin, 
                      Iterator end,
                      const std::string& tag_name)
    {
      Iterator i = begin;
      i = scan_string(i, end, "<");
      i = scan_string(i, end, tag_name);
      i = scan_string(i, end, ">");
      
      //      std::cout << "matched tag open <" << tag_name << ">\n";
      return i;
    }

    Iterator tagCloses(Iterator begin,
                   Iterator end,
                   const std::string& tag_name)
    {
      Iterator i = begin;
      i = scan_string(i, end, "<");
      i = scan_string(i, end, "/");
      i = scan_string(i, end, tag_name);
      i = scan_string(i, end, ">");
      
      //      std::cout << "matched tag close <" << tag_name << ">\n";
      return i;
    }

    Iterator leafTag(Iterator begin,
                 Iterator end,
                 const std::string& tag_name,
                 std::string& b)
    {
      Iterator i = begin;
      i = tagOpens(i, end, tag_name);
      i = scan_pcdata(i, end, b);
      i = tagCloses(i, end, tag_name);      
        
      //      std::cout << "matched leaf tag <" << tag_name << "> '" << b << "'\n";
      return i;
    }
  }

  void checktag(std::istream& s,const std::string& giventag)
  {
#ifndef NDEBUG
    //std::cout << "checktag :" << giventag << std::endl;
#endif
    std::string tag; //empty string
    char c;
    if (!s.get(c)) 
      {
	throw std::runtime_error("could not scan tag");
	//todo fehler behandlung
      }

    while (s && (c == ' ' || c == '\t' || c == '\n'))
      s.get(c);

    if (c!='<') 
      {
	throw std::runtime_error("could not scan tag");
	//todo fehler behandlung
      }

    tag += c;
    while (true)
      {
	if (!s.get(c)) 
	  {
	    //todo fehler behandlung
	    break;
	  } 

	tag+=c;

	if (c=='>') 
	  break;
      }
    // std::cout << "found :" << tag << std::endl;
    if (giventag != tag) 
      {
	throw std::runtime_error("could not scan tag");
      }
  }

  bool checktagloop(std::istream& s,const std::string& looptag,
		    const std::string& exittag)
  {
    //std::cout << "checktagloop :" << looptag << " or " << exittag << "\n";
    std::string tag; //empty string
    char c;
    if (!s.get(c)) 
      {
	throw std::runtime_error("could not scan tag (loop)");
	//todo fehler behandlung
      }

    while (s && (c == ' ' || c == '\t' || c == '\n'))
      s.get(c);

    if (c!='<') 
      {
	throw std::runtime_error("could not scan tag (loop)");
	//todo fehler behandlung
      }
    tag += c;

    while (true)
      {
	if (!s.get(c)) 
	  break;
	//todo fehler behandlung

	tag += c;

	if ( c == '>') 
	  break;
      }

    if (!(tag == looptag || tag == exittag)) 
      {
	std::string msg = "could not scan tag (loop): " + tag;
	throw std::runtime_error(msg.c_str());
      }

    // std::cout << "checktagloop :tag was : " << tag << "\n";
    return (tag == looptag); // loop again
  }

  void extractbetweenTags(std::istream& s,std::string& extracted)
  {
    // std::cout << "extractbetweentags :\n";
    std::string tmp;
    char c;
    while(s.get(c))
      {
	// std::cout << "read char:-" << c <<"-\n";
	if(c=='<')
	  {
	    // put back char
	    // std::cout << "unget:-" << c << "-\n";
	    s.putback(c);
	    break;
	  }
	tmp += c; // add char to string
      }
    extracted=tmp;
    // std::cout << "extracted :" << extracted;
  }

}

