#include "commandmux.h"

#include "icommandlistener.h"

namespace net
{

CommandMux::CommandMux()
  : listener(), defaultListener(0)
{
}

CommandMux::~CommandMux()
{
}

void CommandMux::addCommandListener(ICommandListener& l) 
  throw (std::runtime_error)
{
  std::string command = l.getCommand();
  std::map<std::string,ICommandListener*>::const_iterator 
    i = listener.find(command);

  if (i != listener.end())
    {
      throw std::runtime_error("Listener für das Kommando existiert bereits");
    }

  listener[command] = &l;
}

void CommandMux::setDefaultCommandListener(ICommandInterpreter& l)
{
  defaultListener = &l;
}

ICommandInterpreter* CommandMux::getDefaultCommandListener() const
{
  return defaultListener;
}

void CommandMux::removeCommandListener(ICommandListener& l)
{
  std::string command = l.getCommand();

  if (listener.erase(command) == 0)
    throw std::runtime_error("Konnte den Listener nicht finden.");
}

void CommandMux::commandReceived(const std::string& command,const utils::Buffer& buf)
{
  std::map<std::string,ICommandListener*>::const_iterator 
    i = listener.find(command);

  if (i != listener.end())
    {
      ICommandListener* current = (*i).second;
      current->commandReceived(command,buf);
    }
  else if (defaultListener != 0)
    {
      defaultListener->commandReceived(command,buf);
    }
}

} //end of namespace
