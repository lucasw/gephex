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

#include "coreaudiodriver.h"

#include <unistd.h>

#include <sstream>
#include <stdexcept>
#include <deque>
#include <vector>

#include <CoreAudio/CoreAudio.h>

#include "coreaudioconvert.h"
#include "coreaudiohelpers.h"

/**
 * See http://developer.apple.com/documentation/MusicAudio/Reference/CACoreAudioReference/index.html
 */

struct CoreAudioDriver::Impl
{
  enum IOProcState
    { kOff,
      kStarting,
      kRunning,
      kStopRequested
    };

  Impl() : m_inputProcState(kOff), m_ID(kAudioDeviceUnknown) {}

  void new_data(const unsigned char* data, UInt32 numBytes)
  {
    MutexHolder mh(m_mutex);

    // Buffer at most 100 ms of audio samples
    const size_t MAX_BUFFER = static_cast<size_t>((m_format.mBytesPerFrame*m_format.mSampleRate) / 10);

    assert(numBytes < MAX_BUFFER);

    if (m_buffer.size() + numBytes > MAX_BUFFER)
      {
	const size_t toRemove = my_min(m_buffer.size(),
				       m_buffer.size()+numBytes-MAX_BUFFER);

	m_buffer.erase(m_buffer.begin(),
		       m_buffer.begin() + toRemove);
      }

    m_buffer.insert(m_buffer.end(),
		    data,
		    data + numBytes);

    assert(m_buffer.size() <= MAX_BUFFER);
  }


  int read(unsigned char* data, int num_samples)
  {
    MutexHolder mh(m_mutex);

    //    m_logger(2, "Read request...");

    if (m_buffer.size() == 0)
      return 0;

    const UInt32 inputDataSizeBytes = my_min(num_samples * m_format.mBytesPerFrame,
					     m_buffer.size());

    std::vector<unsigned char> input_data(m_buffer.begin(),
					  m_buffer.begin() + inputDataSizeBytes);

    m_buffer.erase(m_buffer.begin(),
		   m_buffer.begin() + inputDataSizeBytes);

    int outputDataSizeBytes = num_samples*m_desired_format.mBytesPerFrame;

    OSStatus err;

    err = m_converter->convert(&input_data[0], input_data.size(),
			       data, outputDataSizeBytes);


    if (err != kAudioHardwareNoError)
      {
	char buf[1024] = {0};
	sprintf(buf,
		"Conversion failed, num_samples=%i, inputDataSize = %i\n"
		"buffer_size = %i, outputDataSize = %i (err=0x%lX (= %i))",
		num_samples,
		inputDataSizeBytes,
		m_buffer.size(),
		outputDataSizeBytes,
		err, err);

	m_logger(0, buf);
	return 0;
      }
    /*
    char buf[512] = {0};
    sprintf(buf, "Converted %i bytes to %i bytes (num_samples=%i)",
	    inputDataSizeBytes, outputDataSizeBytes, num_samples);
	    m_logger(2, buf);*/

    return outputDataSizeBytes / m_desired_format.mBytesPerFrame;

  }

  static OSStatus InputIOProc(AudioDeviceID          inDevice,
			      const AudioTimeStamp*  /*inNow*/,
			      const AudioBufferList* inputData,
			      const AudioTimeStamp*  /*inInputTime*/,
			      AudioBufferList*	      /*outOutputData*/,
			      const AudioTimeStamp*  /*inOutputTime*/,
			      void*                  inClientData)
  {
    Impl* impl = reinterpret_cast<Impl*>(inClientData);
	
    switch (impl->m_inputProcState)
      {
      case CoreAudioDriver::Impl::kStarting:
	impl->m_inputProcState = CoreAudioDriver::Impl::kRunning;
	break;
      case CoreAudioDriver::Impl::kStopRequested:
	AudioDeviceStop(inDevice, InputIOProc);
	impl->m_inputProcState = CoreAudioDriver::Impl::kOff;
	return noErr;
      default:
	break;
      }

    /*
    char buf[512] = {0};
    sprintf(buf, "Received %i bytes of audio data\n",
	    inputData->mBuffers[0].mDataByteSize);
	    impl->m_logger(2, buf);*/

    impl->new_data(reinterpret_cast<const unsigned char*>(inputData->mBuffers[0].mData),
		   inputData->mBuffers[0].mDataByteSize);


    return noErr;
  }

  volatile IOProcState        m_inputProcState;
  AudioDeviceID               m_ID;
  AudioStreamBasicDescription m_format;
  AudioStreamBasicDescription m_desired_format;
  AudioInDriver::logT         m_logger;

  IConverter*                 m_converter;

private:
  MutexPOSIX                  m_mutex;
  std::deque<unsigned char>   m_buffer;

};

//--------------------------------------------------------------------------

CoreAudioDriver::CoreAudioDriver()
  : m_impl(new Impl())
{
}

CoreAudioDriver::~CoreAudioDriver()
{
  if (this->is_open())
    this->close();
}

void CoreAudioDriver::open(logT logger,
			   device_id_t device,
			   int sample_rate,
			   sample_format form,
			   int channels)
{
  // TODO: hog mode needed?

  static const UInt32 NUM_FRAMES = 1024*2;

  if (this->is_open())
    throw std::logic_error("Device already open");

  if (form != SF_16LE)
    throw std::invalid_argument("Unknown sample format");

  m_impl->m_logger = logger;

  AudioDeviceID devid = GetDeviceID(logger, device);

  if (devid == kAudioDeviceUnknown)
    throw std::invalid_argument("Unknown device id");

  OSStatus err;
  const bool isInput = true;
  UInt32 propsize;
  
  propsize = sizeof(UInt32);
  UInt32 frames = NUM_FRAMES;
  err = AudioDeviceSetProperty(devid, NULL, 0, isInput,
			       kAudioDevicePropertyBufferFrameSize,
			       propsize, &frames);
    
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not set buffer size");
    }

  Float64 sampleRate = sample_rate;
  propsize = sizeof(sampleRate);
  err = AudioDeviceSetProperty(devid, NULL, 0, isInput,
			       kAudioDevicePropertyNominalSampleRate,
			       propsize, &sampleRate);
    
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not set sample rate");
    }

  print_info(devid, logger, isInput);

  propsize = sizeof(m_impl->m_format);
  err = AudioDeviceGetProperty(devid, 0, isInput,
			       kAudioDevicePropertyStreamFormat,
			       &propsize,
			       &m_impl->m_format);

  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not get audio format");
    }


  // Desired format
  memset(&m_impl->m_desired_format, 0, sizeof(m_impl->m_desired_format));
  

  // set channels, format to SF_16LE

  m_impl->m_desired_format.mSampleRate       = sample_rate;
  m_impl->m_desired_format.mFormatID         = kAudioFormatLinearPCM;
  m_impl->m_desired_format.mFormatFlags
         = kLinearPCMFormatFlagIsSignedInteger |
           kLinearPCMFormatFlagIsPacked;

  m_impl->m_desired_format.mBytesPerPacket   = 2*channels;
  m_impl->m_desired_format.mFramesPerPacket  = 1;
  m_impl->m_desired_format.mBytesPerFrame    = m_impl->m_desired_format.mBytesPerPacket;
  m_impl->m_desired_format.mChannelsPerFrame = channels;
  m_impl->m_desired_format.mBitsPerChannel   = 16;

#define USE_COMPLEX_AUDIO_CONVERTER


#if defined(USE_SIMPLE_AUDIO_CONVERTER)
  m_impl->m_converter = new SimpleConverter(m_impl->m_format,
					    m_impl->m_desired_format);
#elif defined (USE_COMPLEX_AUDIO_CONVERTER)
  m_impl->m_converter = new ComplexConverter(m_impl->m_format,
					     m_impl->m_desired_format);

#else
    // TODO: this works only for 2 channels float to 1 channel mono 16LE!
  m_impl->m_converter = new StereoFloatToMono16LEPCM;
#endif

  print_format pf1(logger, "Device Format\n");
  pf1(m_impl->m_format);

  print_format pf2(logger, "Desired Format\n");
  pf2(m_impl->m_desired_format);

  m_impl->m_logger(2, "Starting audio...");

  m_impl->m_inputProcState = Impl::kStarting;

  AudioDeviceAddIOProc(devid, Impl::InputIOProc, m_impl.get());
  AudioDeviceStart(devid, Impl::InputIOProc);

  m_impl->m_ID = devid;
  m_impl->m_logger(2, "Done!");
}


void CoreAudioDriver::close()
{
  m_impl->m_logger(2, "Closing audio...");

  if (!this->is_open())
    return;

  m_impl->m_inputProcState = Impl::kStopRequested;
	
  while (m_impl->m_inputProcState != Impl::kOff)
    usleep(5000);
	
  AudioDeviceRemoveIOProc(m_impl->m_ID, Impl::InputIOProc);
	
  m_impl->m_ID = kAudioDeviceUnknown;
  delete m_impl->m_converter;
  m_impl->m_converter = 0;
}

int CoreAudioDriver::read(unsigned char* data, int num_samples)
{
  return m_impl->read(data, num_samples);
}

bool CoreAudioDriver::is_open() const
{
  return m_impl->m_ID != kAudioDeviceUnknown;
}

