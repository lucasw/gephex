#ifndef INET_PROTOCOL_H
#define INET_PROTOCOL_H


//#include <stdexcept>
namespace utils{
	class Buffer;
}

namespace net
{

/**
 * Abstrakte Oberklasse fuer NetProtocol
 */
class INetProtocol
{
public:
  /**
   * Schickt einen Befehl raus.
   */
  virtual void sendCommand(const char command[4],const utils::Buffer& b) = 0;
};

} //end of namespace

#endif

