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
}

#endif
