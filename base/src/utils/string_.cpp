#include "string_.h"

#include <iostream>

#include "xmlutils.h"

namespace utils
{
  
  String::String(const std::string& s)
    : m_data(s)
  {
  }

  const String& String::operator=(const String& str)
  {
    m_data = str.m_data;

    return *this;
  }

  std::ostream& operator<<(std::ostream& s, const utils::String& str)
  {
    s << "<str>";
    s << "<l>" << str.length() << "</l>";
    s << "<d>";
    for (const char* i = str.c_str(); i != str.c_str()+ str.length();++i)
      {
	s << *i;
      }
    s << "</d>";
    s << "</str>";

    return s;    
  }

  std::istream& operator>>(std::istream& s, utils::String& str)
  {
    checktag(s,"<str>");
    checktag(s,"<l>");
    unsigned int length; // bufferlength
    s >> length;
    checktag(s,"</l>");
    checktag(s,"<d>");
    std::string temp;
    for (unsigned int i = 0; i != length; ++i)
      {
	temp += s.get();
      }
    checktag(s,"</d>");
    checktag(s,"</str>");

    str = String(temp);

    return s;
  }
}
