#ifndef INCLUDED_XML_UTILS_H
#define INCLUDED_XML_UTILS_H

#include <iosfwd>
#include <string>

namespace utils
{
  void checktag(std::istream& s,const std::string& giventag);

  bool checktagloop(std::istream& s,const std::string& looptag,
                    const std::string& exittag);

  void extractbetweenTags(std::istream& s,std::string& extracted);

  namespace xml
  {
    typedef std::string::const_iterator Iterator;
    Iterator tagOpens(Iterator begin, 
                  Iterator end,
                  const std::string& tag_name);

    Iterator tagCloses(Iterator begin,
                   Iterator end,
                   const std::string& tag_name);

    Iterator leafTag(Iterator begin,
                 Iterator end,
                 const std::string& tag_name,
                 std::string& b);

    /**
     * Returns the name of the next tag.
     * Note: for a closing tag "</xxx>" the string "/xxx" is returned.
     */
    std::string next_tag_name(Iterator begin, Iterator end);
  }
}

#endif
