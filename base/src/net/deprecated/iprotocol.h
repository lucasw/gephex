#ifndef INCLUDED_IPROTOCOL_H
#define INCLUDED_IPROTOCOL_H


//#include <stdexcept>
namespace utils{
	class Buffer;
}

namespace net
{

/**
 * Abstrakte Oberklasse fuer Protocol
 */
template <typename Key>
class IProtocol
{
public:
  /**
   * Schickt einen Befehl raus.
   */
  virtual void send(const Key&, const utils::Buffer& b) = 0;
};

} //end of namespace

#endif

