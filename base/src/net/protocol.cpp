/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "protocol.h"

#include <iostream>

#include <cassert>
#include <cstdio>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

// for the min and max templates
// #if defined (COMP_VC) 
// vc7 gets confused with this, so only include for vc6
#if _MSC_VER == 1200  
#include "minmax.h"
#else 
#include <algorithm> 
#endif

#include "convertbin.h"
#include "utils/buffer.h"
#include "basic_types.h"

//TODO: padding of the header structure is not taken into account
// the header is stored in little endian format

static const unsigned int MAX_PACKET_LEN = 1024000;
namespace net
{
  using std::max;

  static const uint_32 PROT_VERSION = 1;
  static const int BUFFER_SIZE = 1024;

  Protocol::Protocol()
    : m_sender(0), m_listener(0),
      bufferBegin(new unsigned char[BUFFER_SIZE]),
      bufferPos(bufferBegin),bufferEnd(bufferBegin+BUFFER_SIZE),
      m_silent_mode(false)
  {
  }

  Protocol::Protocol(IDataListener& dl)
    : m_sender(0), m_listener(&dl),
      bufferBegin(new unsigned char[BUFFER_SIZE]),
      bufferPos(bufferBegin),bufferEnd(bufferBegin+BUFFER_SIZE),
      m_silent_mode(false)
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

  void Protocol::registerSender(ISender* sender)
  {
    m_sender = sender;
  }

  namespace
  {
    /**
     * Calculates a simple checksum from the header data.
     */
    uint_32 check_sum(uint_32 packetLen, uint_32 version, uint_32 dataLen)
    {
      return (packetLen << 13) + (version << 17) + (dataLen << 11);
    }


    struct Header
    {
      explicit Header(int data_len)
        : packetLen(data_len + sizeof(Header)), version(PROT_VERSION),
          dataLen(data_len), 
          checkSum(check_sum(packetLen, version, data_len))
      {
      }

      /**
       * "Casts" the header from raw memory in a standard conforming
       * and platform independent way.
       * The memory is assumed to contain the header in little endian
       * format without padding.
       * (Simply casting leads to bus errors on sparc32 when access is
       *  not properly aligned)
       */
      explicit Header(const unsigned char* raw_data)
      {
        packetLen = convert_uint32_from_le(raw_data + 0);
        version   = convert_uint32_from_le(raw_data + 4);
        dataLen   = convert_uint32_from_le(raw_data + 8);
        checkSum  = convert_uint32_from_le(raw_data + 12);
      }

      /**
       * Checks wether the checksum in the header matches and
       * if the header data is consistent.
       */
      bool ok() const
      {
        return (version == PROT_VERSION &&
                packetLen <= MAX_PACKET_LEN &&
                packetLen == dataLen + sizeof(Header) &&
                checkSum == check_sum(packetLen, version, dataLen));
      }

      /**
       * "Casts" the header to a raw representation in little endian
       * format.
       */
      utils::Buffer to_raw() const
      {
        unsigned char raw[sizeof(Header)];
        convert_uint32_to_le(packetLen, raw + 0);
        convert_uint32_to_le(version,   raw + 4);
        convert_uint32_to_le(dataLen,   raw + 8);
        convert_uint32_to_le(checkSum,  raw + 12);

        return utils::Buffer(raw, sizeof(raw));
      }

      uint_32 packetLen;
      uint_32 version;
      uint_32 dataLen;
      uint_32 checkSum;
    };


    // tries to find a valid header somwhere inside data
    int try_sync(const unsigned char* data, int data_len)
    {
      for (unsigned int i = 0; i < data_len - sizeof(Header); ++i)
        {
          Header test_header(data+i);
          if (test_header.ok())
            return i;
        }
      return -1;
    }
  }

  int Protocol::send(const utils::Buffer& buf)
  {
    // TODO: if buf.getLen()+sizeof(Header) > MAX_PACKET_LEN 
    // split the buffer in multiple packets each smaller than
    // MAX_PACKET_LEN
    Header header(buf.getLen());

    if (m_sender)
      {
        try {
          int len = m_sender->send(header.to_raw() + buf);
          m_silent_mode = false;
          return len;
        }
        catch (std::exception& e)
          {
            if (!m_silent_mode)
              {
                std::cerr << "protocol.cpp: send threw " << e.what() << "\n";
                std::cerr << "silent mode turned on\n";
                m_silent_mode = true;
              }
          }  
      }
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
    const unsigned char* dataPos = dataBegin;

    int bytesLeft = len;

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
	    Header header(bufferBegin);

	    // check if header is valid
	    if (!header.ok())
	      {
		fprintf(stderr, "protocol.cpp: out of sync!\n");
		fprintf(stderr, "pl = %i, dl = %i\n",
			header.packetLen,
			header.dataLen);
		fprintf(stderr, "Trying to resync protocol...\n");

		// Syncing will not work if the header is partly in this data 
                // packet and partly in the next.
                int syncPoint = try_sync(dataPos, dataEnd - dataPos);
		if (syncPoint == -1)
		  {
		    fprintf(stderr,
                            "Skipping whole packet (%i bytes)\n",
                            dataEnd - dataPos);
		    bufferPos = bufferBegin;
		    return;
		  }
		else
		  {
		    fprintf(stderr, "Skipping %i bytes\n", syncPoint);
		    dataPos   += syncPoint;
		    bytesLeft -= (syncPoint + sizeof(Header));;
		    bufferPos  = bufferBegin + sizeof(Header);
            
		    memcpy(bufferBegin, dataPos, sizeof(Header));
                    dataPos += sizeof(Header);
		    
		    header = Header(bufferBegin);
		    fprintf(stderr, "pl = %i, dl = %i\n",
			    header.packetLen,
			    header.dataLen);

		    if (bytesLeft == 0)
		      return;
		  }
	      }

	    if (static_cast<uint_32>(bufferPos-bufferBegin+bytesLeft)
		< header.packetLen) 
	      { // Paket nicht ganz da
		// lesen sovielwie geht
		read(dataPos,dataEnd,bytesLeft,bytesLeft);
		assert(dataPos == dataEnd); // alles gelesen
	      }
	    else // ganzes Paket da	      
              {
		// ganzes paket lesen
		read(dataPos, dataEnd,
                     header.packetLen-(bufferPos-bufferBegin),
		     bytesLeft);
	      
		bufferPos = bufferBegin;
				
		// Paket parsen
		if (header.version == PROT_VERSION && m_listener != 0)
		  {
                    try {
                      m_listener->dataReceived(utils::Buffer(bufferBegin
                                                             +sizeof(Header),
                                                             header.packetLen
                                                             -sizeof(Header)));
                    }
                    catch (std::exception& e)
                      {
                        fprintf(stderr, 
                                "protocol.cpp, dataReceived of listener "
                                "throwed: %s\n", e.what()); 
                      }
		  }
		else if (header.version != PROT_VERSION)
		  {
		    fprintf(stderr,
                            "protocol.cpp: ignoring wrong header version %i\n",
                            header.version);
		  }
	      }

	  } 
	
      } // while
  }

  void Protocol::reset()
  {
    bufferPos = bufferBegin;
  }

} //end of namespace
