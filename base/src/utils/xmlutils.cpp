#include "xmlutils.h"

#include <iostream>
#include <stdexcept>

namespace utils
{

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

    while (s && (c == ' ' || c == '\t'))
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

    while (s && (c == ' ' || c == '\t'))
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

