#ifndef ICOMMAND_INTERPRETER
#define ICOMMAND_INTERPRETER

#include <string>

namespace utils{
	class Buffer;
}

namespace net
{

class ICommandInterpreter
{
public:
  virtual void commandReceived(const std::string& command,const utils::Buffer&) = 0;
};

} //end of namespace

#endif
