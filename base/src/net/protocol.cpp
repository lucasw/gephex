#include "protocol.h"
#include <cassert>

#if defined(HAVE_CONFIG_H)
  #include "config.h"
#endif

// for the min and max templates
#if defined (COMP_VC)
  #include "minmax.h"
#else 
  #include <algorithm> 
#endif

#include "utils/buffer.h"
#include "basic_types.h"

//TODO: alles plattformabhängig ab hier
// man muesste die endianess und das padding von Header
// durch den compiler berücksichtigen...

namespace net
{
  using std::max;

  static const uint_32 PROT_VERSION = 1;
  static const int BUFFER_SIZE = 1024;

  Protocol::Protocol()
    : m_sender(0), m_listener(0),
      bufferBegin(new unsigned char[BUFFER_SIZE]),
      bufferPos(bufferBegin),bufferEnd(bufferBegin+BUFFER_SIZE)
  {
  }

  Protocol::Protocol(IDataListener& dl)
    : m_sender(0), m_listener(&dl),
      bufferBegin(new unsigned char[BUFFER_SIZE]),
      bufferPos(bufferBegin),bufferEnd(bufferBegin+BUFFER_SIZE)
  {
  }

  Protocol::~Protocol()
  {
    delete[] bufferBegin;
  }

  void Protocol::registerListener(IDataListener& listener)
  {
    m_listener = &listener;
  }

  void Protocol::registerSender(ISender& sender)
  {
    m_sender = &sender;
  }

  namespace {
    struct Header
    {
      uint_32 packetLen;
      uint_32 version;
      uint_32 dataLen;
    };
  }

  int Protocol::send(const utils::Buffer& buf)
  {
    static Header header;

    header.packetLen = sizeof(header) + buf.getLen();
    header.version = PROT_VERSION;
    header.dataLen = buf.getLen();
	
    if (m_sender)
      return
	m_sender->send(utils::Buffer(reinterpret_cast<unsigned char*>(&header),
				     sizeof(header)) + buf);
    else
      return 0;
  }

  void Protocol::read(const unsigned char*& dataPos,
				       const unsigned char* dataEnd,
				       int bytesToRead, int& bytesLeft)
  {
    if (bytesToRead == 0)
      return;

    assert(bytesToRead > 0);

    if (bufferPos+bytesToRead > bufferEnd)
      {
	int currentSize = bufferEnd - bufferBegin;
	int posDistance = bufferPos - bufferBegin;
	int newSize = max((int) (currentSize*1.3 + 1),
			       (int) (bufferPos-bufferBegin+bytesToRead+1));

	unsigned char* newBuffer = new unsigned char[newSize];
	memcpy(newBuffer,bufferBegin,posDistance);

	delete[] bufferBegin;
	bufferBegin = newBuffer;
	bufferPos = bufferBegin + posDistance;
	bufferEnd = bufferBegin + newSize;
      }

    assert(bufferPos+bytesToRead <= bufferEnd);
    assert(dataPos+bytesToRead <= dataEnd);
    memcpy(bufferPos,dataPos,bytesToRead);
    bufferPos += bytesToRead;
    dataPos   += bytesToRead;
    bytesLeft -= bytesToRead;
  }

  void Protocol::dataReceived(const utils::Buffer& buf)
  {
    const unsigned char* dataBegin = buf.getPtr();
    int len = buf.getLen();

    const unsigned char* dataEnd = dataBegin+len;
    const unsigned char* dataPos= dataBegin;

    int bytesLeft = len;

    Header* header = 0;

    while(dataPos < dataEnd) // noch weitere daten da
      {
	//header noch nicht gelesen?
	if (bufferPos < bufferBegin+sizeof(Header))
	  {
	    // header vervollständigen
	    if (bufferPos-bufferBegin+bytesLeft < (int) sizeof(Header)) 
	      { // kann header nicht fertig lesen
		// soviel wie geht lesen
		read(dataPos,dataEnd,bytesLeft,bytesLeft);
		assert(dataPos == dataEnd); //alles gelesen
	      } 
	    else // header kann ganz gelesen werden
	      {
		// header fertig lesen
		read(dataPos,dataEnd,bufferBegin-bufferPos+sizeof(Header),
		     bytesLeft);
		assert(bufferPos == sizeof(Header)+bufferBegin);
	      }
	  
	  }
	else // nach header
	  {
	    // bufferbegin kann sich bei read aendern!
	    header = reinterpret_cast<Header *>(bufferBegin);

	    if (static_cast<uint_32>(bufferPos-bufferBegin+bytesLeft)
		< header->packetLen) 
	      { // Paket nicht ganz da
		// lesen sovielwie geht
		read(dataPos,dataEnd,bytesLeft,bytesLeft);
		assert(dataPos == dataEnd); // alles gelesen
		// bufferbegin kann sich bei read aendern!
		header = reinterpret_cast<Header *>(bufferBegin);
	      }
	    else // ganzes Paket da
	      {
		// ganzes paket lesen
		read(dataPos,dataEnd,header->packetLen-(bufferPos-bufferBegin),
		     bytesLeft);
	      
		// bufferbegin header kann sich bei read aendern!
		header = reinterpret_cast<Header *>(bufferBegin);

		bufferPos = bufferBegin;
				
		// Paket parsen
		if (header->version == PROT_VERSION && m_listener != 0)
		  {		  
		    m_listener->dataReceived(utils::Buffer(bufferBegin
							      +sizeof(Header),
							      header->packetLen
							      -sizeof(Header)));
		  }
		else if (header->version != PROT_VERSION)
		  {
		    // TODO: Fehlerbehandlung
		  }
	      }

	  } 
	
      } // while
  }


} //end of namespace
