#ifndef ICOMMAND_LISTENER
#define ICOMMAND_LISTENER

#include <string>

#include "icommandinterpreter.h"

namespace net
{

class ICommandListener : public ICommandInterpreter
{
public:
  virtual std::string getCommand() const = 0;
};

} //end of namespace

#endif
