#include "netprotocol.h"
#include <cassert>

#include "icommandinterpreter.h"
#include "isender.h"

#include "utils/buffer.h"

//TODO: alles plattformabhängig ab hier

namespace net
{

NetProtocol::NetProtocol()
  : m_sender(0), m_commandInterpreter(0),
    bufferBegin(new unsigned char[1024]),
    bufferPos(bufferBegin),bufferEnd(bufferBegin+1024)
{
}

NetProtocol::NetProtocol(ICommandInterpreter& _cI)
  : m_sender(0), m_commandInterpreter(&_cI),
    bufferBegin(new unsigned char[1024]),
    bufferPos(bufferBegin),bufferEnd(bufferBegin+1024)
{
}

NetProtocol::~NetProtocol()
{
  delete[] bufferBegin;
}

void NetProtocol::setCommandInterpreter(ICommandInterpreter& interpreter)
{
  m_commandInterpreter = &interpreter;
}

void NetProtocol::setSender(ISender& sender)
{
  m_sender = &sender;
}

struct Header
{
  int packetLen;
  int version;
  char command[5];
  int dataLen;
};

void NetProtocol::sendCommand(const char command[4],const utils::Buffer& buf)
{
  static Header header;

  header.packetLen = sizeof(Header) + buf.getLen();
  header.version = 1;
  memcpy(header.command,command,4);
  header.command[4] = 0;
  header.dataLen = buf.getLen();
	
  m_sender->send(utils::Buffer((unsigned char*) &header, sizeof(header)) + buf);
}

static int max(int a,int b)
{
  return (a < b) ? b : a;
}

void NetProtocol::read(const unsigned char*& dataPos,
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

void NetProtocol::dataReceived(const utils::Buffer& buf)
{
  const unsigned char* dataBegin = buf.getPtr();
  int len = buf.getLen();

  const unsigned char* dataEnd = dataBegin+len;
  const unsigned char* dataPos= dataBegin;

  int bytesLeft = len;

  Header* header = 0;

  while(dataPos < dataEnd) // noch weitere daten da
    {
      if (bufferPos < bufferBegin+sizeof(Header)) //header noch nicht gelesen
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
	  header = (Header*) bufferBegin; //kann sich bei read aendern!

	  if (bufferPos-bufferBegin+bytesLeft < header->packetLen) 
	    { // Paket nicht ganz da
	      // lesen sovielwie geht
	      read(dataPos,dataEnd,bytesLeft,bytesLeft);
	      assert(dataPos == dataEnd); // alles gelesen
	      header = (Header*) bufferBegin; //kann sich bei read aendern!
	    }
	  else // ganzes Paket da
	    {
	      // ganzes paket lesen
	      read(dataPos,dataEnd,header->packetLen-(bufferPos-bufferBegin),
		   bytesLeft);
	      header = (Header*) bufferBegin; //kann sich bei read aendern!
	      bufferPos = bufferBegin;
				
	      // Paket parsen
	      if (header->version == 1 && m_commandInterpreter != 0)
		{
		  m_commandInterpreter->commandReceived(header->command,
							utils::Buffer(bufferBegin
							+sizeof(Header),
							header->packetLen
							-sizeof(Header)));
		}
	    }

	} 
	
    } // while
}


} //end of namespace

