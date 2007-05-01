#include "coreaudiohelpers.h"

#include <pthread.h>

MutexPOSIX::MutexPOSIX()
{
  m_mutex = new char[sizeof(pthread_mutex_t)];
  pthread_mutex_init((pthread_mutex_t*) m_mutex,0);
}

MutexPOSIX::~MutexPOSIX()
{
  pthread_mutex_destroy((pthread_mutex_t*) m_mutex);
  delete[] (char*) m_mutex;
}

void MutexPOSIX::acquire()
{
  pthread_mutex_lock((pthread_mutex_t*) m_mutex);
}

void MutexPOSIX::release()
{
  pthread_mutex_unlock((pthread_mutex_t*) m_mutex);
}

struct print_devname
{
  print_devname(logT logger) : m_logger(logger) {}

  void operator()(AudioDeviceID id) const
  {
    char buf[1024] = {0};
    UInt32 maxlen = sizeof(buf);

    OSStatus err = AudioDeviceGetProperty(id, 0, true,
					  kAudioDevicePropertyDeviceName,
					  &maxlen, buf);

    char buf2[2048] = {0};

    sprintf(buf2, " - Device Name: '%s'\n", buf);
    m_logger(2, buf2);
  }

  logT m_logger;
};

AudioDeviceID GetDeviceID(logT logger, int dev)
{
  UInt32 propsize;
  OSStatus err;

  err = AudioHardwareGetPropertyInfo(kAudioHardwarePropertyDevices,
				     &propsize,
				     NULL);

  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Can not list audio devices");
    }

  int nDevices = propsize / sizeof(AudioDeviceID);
  std::vector<AudioDeviceID> devids(nDevices);

  err = AudioHardwareGetProperty(kAudioHardwarePropertyDevices,
				 &propsize,
				 &devids[0]);

  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Can not get list of audio devices");
    }

  std::for_each(devids.begin(), devids.end(), print_devname(logger));

  return (0 <= dev && dev < nDevices) ? devids[dev] : kAudioDeviceUnknown;
}


print_format:: print_format(logT logger, const char* title)
  : m_logger(logger), m_title(title) {}

void print_format::operator()(const AudioStreamBasicDescription& format) const
{
  char buffer[1024] = {0};
  
  char formatID[5] = {0};
  memcpy(formatID, &format.mFormatID, sizeof(format.mFormatID));

  sprintf(buffer,
	  "%sSampleRate       = %f\n"
	  "FormatID         = %s\n"
	  "FormatFlags      = %X\n"
	  "BytesPerPacket   = %i\n"
	  "FramesPerPacket  = %i\n"
	  "BytesPerFrame    = %i\n"
	  "ChannelsPerFrame = %i\n"
	  "BitsPerChannel   = %i\n",
	  m_title,
	  format.mSampleRate,
	  formatID,
	  format.mFormatFlags,
	  format.mBytesPerPacket,
	  format.mFramesPerPacket,
	  format.mBytesPerFrame,
	  format.mChannelsPerFrame,
	  format.mBitsPerChannel);

  m_logger(2, buffer);
}

struct print_configuration
{
  print_configuration(logT logger) : m_logger(logger) {}

  void operator()(const AudioBufferList& buffer) const
  {
    char buf[1024] = {0};

    sprintf(buf,
	    " - AudioBufferList, numBuffers     = %i\n",
	    buffer.mNumberBuffers);

    m_logger(2, buf);

    for (int i = 0; i < buffer.mNumberBuffers; ++i)
      {
	sprintf(buf,
		"   + buffer #channels = %i, data byte size = %i\n",
		buffer.mBuffers[i].mNumberChannels,
		buffer.mBuffers[i].mDataByteSize);

	m_logger(2, buf);
      }
  }

  logT m_logger;
  const char* m_title;
}; 

void print_info(AudioDeviceID devid, logT logger, bool isInput)
{
  UInt32 safetyOffset;
  UInt32 propsize = sizeof(safetyOffset);
  OSStatus err = AudioDeviceGetProperty(devid, 0, isInput,
					kAudioDevicePropertySafetyOffset,
					&propsize, &safetyOffset);

  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not get safety offset");
    }

  char bbb[128] = {0};
  sprintf(bbb, "Safety Offset = %i frames", safetyOffset);
  logger(2, bbb);

  AudioStreamBasicDescription format;
  propsize = sizeof(format);
  err = AudioDeviceGetProperty(devid, 0, isInput,
			       kAudioDevicePropertyStreamFormat,
			       &propsize, &format);

  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not get audio format");
    }

  print_format pf(logger, "Audio Device Stream format\n");
  pf(format);	

  std::vector<AudioStreamBasicDescription> formats
    = get_prop_list<AudioStreamBasicDescription>(devid,
						 kAudioDevicePropertyStreamFormats,
						 isInput);

  std::for_each(formats.begin(), formats.end(),
		print_format(logger, "Supported device stream format\n"));

  std::vector<AudioStreamID> streams 
    = get_prop_list<AudioStreamID>(devid,
				   kAudioDevicePropertyStreams,
				   isInput);

  for (std::vector<AudioStreamID>::const_iterator it = streams.begin();
       it != streams.end(); ++it)
    {    
      AudioStreamBasicDescription format;
      propsize = sizeof(format);
      err = AudioStreamGetProperty(*it, 0,
				   kAudioStreamPropertyPhysicalFormat,
				   &propsize, &format);

      if (err != kAudioHardwareNoError)
	{
	  throw std::runtime_error("Could not get physical stream format");
	}

      print_format pf(logger, "Physical Stream format\n");
      pf(format);

      std::vector<AudioStreamBasicDescription> stream_formats
	= get_stream_prop_list<AudioStreamBasicDescription>(*it,
							    kAudioStreamPropertyPhysicalFormats);

      std::for_each(stream_formats.begin(), stream_formats.end(),
		    print_format(logger, "Supported physical stream format\n"));
	
    }

  std::vector<AudioBufferList> configuration 
    = get_prop_list<AudioBufferList>(devid,
				     kAudioDevicePropertyStreamConfiguration,
				     isInput);

  std::for_each(configuration.begin(), configuration.end(),
		print_configuration(logger));
}

