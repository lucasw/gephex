#ifndef INCLUDED_ISTRUCT_TOKEN_LISTENER_H
#define INCLUDED_ISTRUCT_TOKEN_LISTENER_H

#include <string>

namespace utils
{

class IStructTokenListener
{
 public: 
	 enum {TYPE_STRING, TYPE_BOOL, TYPE_NUMBER };
  virtual void beginStruct() = 0;
  virtual void endStruct() = 0;
  virtual void scannedStructName(const std::string& name) = 0;
  virtual void scannedPair(const std::string& name,
			   const std::string& value, int type) = 0;
};

} //end of namespace utils

#endif
