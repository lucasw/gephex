#ifndef INCLUDED_PROTOCOL_H
#define INCLUDED_PROTOCOL_H

#include <map>
#include <string>
#include <stdexcept>

#include "idatalistener.h"
#include "isender.h"

namespace utils {
  class Buffer;
}

namespace net
{

/**
 * The Protocol class makes sure that data sent/received through
 * it is sent/received in complete packages only.
 *
 * Some implementation of ISender don't have the property that
 * data is sent in whole packages. They repackage the data and it may
 * be received in multiple smaller packages.
 *
 * The Protocol class can simply be inserted into the sender/receiver
 * chain (because it implements ISender and IDataListener) and makes
 * sure that data is delivered in whole packages only.
 *
 */
class Protocol : public ISender, public IDataListener
{
public:
  Protocol();
  Protocol(IDataListener&);

  virtual ~Protocol();

  /**
   * Sets the data-istener, to whom received data is forwarded.
   * @param listener the data-listener that receives incoming data.
   */
  void registerListener(IDataListener& listener);
  
  /**
   * Sets the sender which is used for forwarding the data. 
   * The sender has to be set before send() is called.
   * @param sender The sender that is used for forwarding
   */
  void registerSender(ISender& sender);

  virtual int send(const utils::Buffer&);

  virtual void dataReceived(const utils::Buffer& buf);

private:
  ISender* m_sender;
  IDataListener* m_listener;

  unsigned char* bufferBegin;
  unsigned char* bufferPos;
  unsigned char* bufferEnd;

  void read(const unsigned char*& dataPos,const unsigned char* dataEnd,
	    int bytesToRead, int& bytesLeft);
};


} //end of namespace

#endif
