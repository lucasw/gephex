#ifndef INCLUDED_IPROTOCOL_INTERPRETER_H
#define INCLUDED_IPROTOCOL_INTERPRETER_H

namespace utils{
  class Buffer;
}

namespace net
{

  /**
   * Is called by Protocol, whenever data arrives. 
   */
  template <typename KEY>
  class IProtocolInterpreter
  {
  public:
    virtual void dataReceived(const KEY& command, const utils::Buffer&) = 0;
  };

} //end of namespace

#endif
