#include "sequenceserial.h"

#include <iostream>
#include "sequence.h"
#include "utils/xmlutils.h"

namespace sequencer
{

  std::ostream& operator<< (std::ostream& s, const Sequence& sequ)
  {
    s << "<sequence>";
    s << "<id>" << sequ.id() << "</id>"; 
    s << "<name>" << sequ.name() << "</name>";
    s << "<actions>";
    for (Sequence::const_iterator it=sequ.begin();it !=sequ.end();++it)
      {
	s << "<action>";
	s << "<time>";
	s << sequ.actionTime(it->first);
	s << "</time>";
	s << "<command>";
        s << it->second->command();
	s << "</command>";
	s << "</action>";
      }
    s << "</actions>";
    s << "</sequence>";
    return s;
  }

  std::istream& operator>> (std::istream& s, Sequence& sequ)
  {
    using utils::checktag;
    using utils::checktagloop;
    using utils::extractbetweenTags;

    // parse and build
    checktag(s,"<sequence>");
    checktag(s,"<id>");
    std::string id;
    extractbetweenTags(s,id);
    sequ.setID(id);
    checktag(s,"</id>");
    checktag(s,"<name>");
    std::string name;
    extractbetweenTags(s,name);
    sequ.setName(name);
    checktag(s,"</name>");
    checktag(s,"<actions>");
    while (checktagloop(s,"<action>","</actions>"))
      {
	checktag(s,"<time>");
	int time;
	s>>time;
	checktag(s,"</time>");
	checktag(s,"<command>");
	std::string command;
	extractbetweenTags(s,command);
	checktag(s,"</command>");
	sequ.addAction(command, time);
	checktag(s,"</action>");
      } // </actions>
    checktag(s,"</sequence>");
    return s;
  }

}


