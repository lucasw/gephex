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

#include "macosxmidiindriver.h"

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>

#include <pthread.h>

#include <CoreMIDI/MIDIServices.h>

//-------------------------------------------------------------------------

static const size_t MIDI_BUF_SIZE = 2048;

static void sReceiveMidi(const MIDIPacketList *pktlist,
			 void *refCon, void */*connRefCon*/);

//-------------------------------------------------------------------------

struct MacOSXMidiInDriver::Impl
{
  Impl() : m_client(0), m_inPort(0)
  {
    pthread_mutex_init(&m_mutex, 0);
  }

  bool is_open() const 
  {
    return m_client != 0;
  }

  void open(int device)
  {
    std::ostringstream os;
    os << "gephex-0.4 midi device " << device;
    
    const std::string device_name = os.str();

    CFStringRef name = CFStringCreateWithBytes(0,
  	                 reinterpret_cast<const UInt8*>(device_name.c_str()),
			 device_name.length(),
			 kCFStringEncodingUTF8,
			 false);

    OSStatus err = MIDIClientCreate(name, NULL, NULL, &m_client);

    CFRelease(name);

    if (err != 0)
      throw std::runtime_error("Could not create midi client");
	

    os << " input";
    const std::string input_name = os.str();

    CFStringRef in_name = CFStringCreateWithBytes(0,
  	                 reinterpret_cast<const UInt8*>(input_name.c_str()),
			 input_name.length(),
			 kCFStringEncodingUTF8,
			 false);

    //    err = MIDIInputPortCreate(m_client, CFSTR("Input port"),
    //		      sReceiveMidi, (void*)this, &m_inPort);
    err =  MIDIDestinationCreate(m_client, 
				 in_name, 
				 sReceiveMidi, (void*)this,
				 &m_inPort);

    CFRelease(in_name);

    if (err != 0)
      {
	MIDIClientDispose(m_client);
	m_client = 0;
	throw std::runtime_error("Could not create midi port");
      }
	
#if 0
    // open connections from all sources
    // TODO: what exactly is connected here?
    int n = MIDIGetNumberOfSources();
    printf("%d sources\n", n);
   
    for (int i = 0; i < n; ++i)
      {
	MIDIEndpointRef src = MIDIGetSource(i);
	MIDIPortConnectSource(m_inPort, src, NULL);
      }
#endif
  }

  void close()
  {
    //MIDIPortDispose(m_inPort);
    MIDIEndpointDispose(m_inPort);
    m_inPort = 0;

    MIDIClientDispose(m_client);
    m_client = 0;
  }

  int read_buffer(unsigned char* data, int data_size);
  
  //puts a byte into the static buffer
  void put_bytes(const std::vector<unsigned char>& data);

private:
  
  MIDIClientRef m_client;
  //MIDIPortRef m_inPort;
  MIDIEndpointRef m_inPort;

  std::vector<unsigned char> m_buffer;

  pthread_mutex_t m_mutex;
};

//-------------------------------------------------------------------------

MacOSXMidiInDriver::MacOSXMidiInDriver()
  : m_impl(new Impl())
{
}

MacOSXMidiInDriver::~MacOSXMidiInDriver()
{
  if (this->is_open())
    close();
}

void MacOSXMidiInDriver::open(device_id_t device)
{
  if (this->is_open())
    throw std::logic_error("Device already open");

  m_impl->open(device);
}

void MacOSXMidiInDriver::close()
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  m_impl->close();
}

int MacOSXMidiInDriver::read(unsigned char* data, int data_size)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");
 
  return m_impl->read_buffer(data, data_size);
}

bool MacOSXMidiInDriver::is_open() const
{
  return m_impl->is_open();
}

//------------------------------------------------------------------

int MacOSXMidiInDriver::Impl::read_buffer(unsigned char* data, int data_size)
{
  pthread_mutex_lock(&m_mutex);
  
  assert(m_buffer.size() <= INT_MAX);

  const int bytes_copied = std::min(data_size,
				    static_cast<int>(m_buffer.size()));

  std::copy(m_buffer.begin(),
	    m_buffer.begin() + bytes_copied,
	    data);

  m_buffer.erase(m_buffer.begin(), m_buffer.begin() + bytes_copied);

  pthread_mutex_unlock(&m_mutex);

  return bytes_copied;
}

void MacOSXMidiInDriver::Impl::put_bytes(const std::vector<unsigned char>& data)
{
  pthread_mutex_lock(&m_mutex);

  const size_t to_copy = std::min(data.size(),
				  MIDI_BUF_SIZE - m_buffer.size());
  
  m_buffer.insert(m_buffer.end(), data.begin(), data.begin() + to_copy);

  pthread_mutex_unlock(&m_mutex);
}

//--------------------------------------------------------------------


static void sReceiveMidi(const MIDIPacketList *pktlist,
			 void *refCon, void */*connRefCon*/)
{
  MacOSXMidiInDriver::Impl* 
    m = reinterpret_cast<MacOSXMidiInDriver::Impl*>(refCon);

  const MIDIPacket* packet = pktlist->packet;

  std::vector<unsigned char> tmp;

  for (unsigned int j = 0; j < pktlist->numPackets; ++j)
    {
      tmp.insert(tmp.end(),
		 packet->data,
		 packet->data + packet->length);

      packet = MIDIPacketNext(const_cast<MIDIPacket*>(packet));
    }
	
  m->put_bytes(tmp);
}
