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

#include "coreaudiooutdriver.h"

#include <deque>
#include <stdexcept>
#include <stdio.h>

#include <CoreAudio/CoreAudio.h>

#include "coreaudioconvert.h"
#include "coreaudiohelpers.h"


//--------------------------------------------------------------------------


struct CoreAudioOutDriver::Impl
{
  enum IOProcState
    { kOff,
      kStarting,
      kRunning,
      kStopRequested
    };

  Impl() : m_outputProcState(kOff),
	   m_ID(kAudioDeviceUnknown),
	   m_min_buffer(0) {}

  void new_data(const unsigned char* data, UInt32 numBytes)
  {
    MutexHolder mh(m_mutex);

    // Buffer at most 2 s of audio samples
    const size_t MAX_BUFFER = static_cast<size_t>(2*m_input_format.mBytesPerFrame*m_format.mSampleRate);

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

    if (m_outputProcState == kOff &&
	m_buffer.size() >= m_min_buffer)
      {
	start_audio();
      }
  }


  int read(unsigned char* data, int num_samples)
  {
    MutexHolder mh(m_mutex);

    //    m_logger(2, "Read request...");

    if (m_outputProcState == kRunning &&
	m_buffer.size() < num_samples * m_input_format.mBytesPerFrame)
      {
	stop_audio();
	return 0;
      }

    const UInt32 inputDataSizeBytes = my_min(num_samples * m_input_format.mBytesPerFrame,
					     m_buffer.size());

    std::vector<unsigned char> input_data(m_buffer.begin(),
					  m_buffer.begin() + inputDataSizeBytes);

    m_buffer.erase(m_buffer.begin(),
		   m_buffer.begin() + inputDataSizeBytes);

    int outputDataSizeBytes = num_samples*m_format.mBytesPerFrame;

    OSStatus err;

    err = m_converter->convert(&input_data[0],
			       input_data.size(),
			       data,
			       outputDataSizeBytes);


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

    return outputDataSizeBytes / m_format.mBytesPerFrame;

  }

  static OSStatus OutputIOProc(AudioDeviceID          inDevice,
			       const AudioTimeStamp*  /*inNow*/,
			       const AudioBufferList* /*inputData*/,
			       const AudioTimeStamp*  /*inInputTime*/,
			       AudioBufferList*	      outputData,
			       const AudioTimeStamp*  /*inOutputTime*/,
			       void*                  inClientData)
  {
    Impl* impl = reinterpret_cast<Impl*>(inClientData);
	
    switch (impl->m_outputProcState)
      {
      case kStarting:
	impl->m_outputProcState = kRunning;
	break;
      case kStopRequested:
	AudioDeviceStop(inDevice, OutputIOProc);
	impl->m_outputProcState = kOff;
	return noErr;
      default:
	break;
      }

    /*
    char buf[512] = {0};
    sprintf(buf, "Received %i bytes of audio data\n",
	    inputData->mBuffers[0].mDataByteSize);
	    impl->m_logger(2, buf);*/

    impl->read(reinterpret_cast<unsigned char*>(outputData->mBuffers[0].mData),
	       outputData->mBuffers[0].mDataByteSize / impl->m_format.mBytesPerFrame);


    return noErr;
  }

  void start_audio()
  {
    if (m_outputProcState != kOff)
      return;

    m_logger(2, "Starting audio...");

    m_outputProcState = Impl::kStarting;

    //AudioDeviceAddIOProc(m_ID, Impl::OutputIOProc, this);
    AudioDeviceStart(m_ID, Impl::OutputIOProc);

    m_logger(2, "Done!");
  }



  void stop_audio()
  {
    if (m_outputProcState != kRunning)
      return;

    m_logger(2, "Stopping audio...");

    m_outputProcState = Impl::kStopRequested;

    //AudioDeviceRemoveIOProc(m_ID, Impl::OutputIOProc);

    m_logger(2, "Done!");
  }

  volatile IOProcState        m_outputProcState;
  AudioDeviceID               m_ID;
  AudioStreamBasicDescription m_format;
  AudioStreamBasicDescription m_input_format;
  logT                        m_logger;

  IConverter*                 m_converter;

  int                         m_min_buffer;
private:
  MutexPOSIX                  m_mutex;
  std::deque<unsigned char>   m_buffer;

};

namespace
{
  template <typename T> T my_max(T a, T b) { return a >= b ? a : b; }
}

//--------------------------------------------------------------------------

CoreAudioOutDriver::CoreAudioOutDriver()
  : m_impl(new Impl())
{
}

CoreAudioOutDriver::~CoreAudioOutDriver()
{
  if (this->is_open())
    this->close();
}

namespace
{
  void logger(int, const char* s)
  {
    printf("%s\n", s);
  }
}

void CoreAudioOutDriver::open(device_id_t device,
			      int sample_rate,
			      sample_format form,
			      int channels,
			      int num_samples,
			      int num_periods)
{
  if (this->is_open())
    throw std::logic_error("Device already open");


  if (form != SF_16LE)
    throw std::invalid_argument("Unknown sample format");

  m_impl->m_logger = logger;

  AudioDeviceID devid = GetDeviceID(logger, device);

  if (devid == kAudioDeviceUnknown)
    throw std::invalid_argument("Unknown device id");

  OSStatus err;
  const bool isInput = false;
  UInt32 propsize;
  
  AudioValueRange bufferRange;

  // check that the desired value is within the allowed range
  propsize = sizeof(bufferRange);
  err = AudioDeviceGetProperty(devid, 0, false,
			       kAudioDevicePropertyBufferFrameSizeRange,
			       &propsize,
			       &bufferRange);


  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not get buffer range");
    }

  propsize = sizeof(UInt32);
  UInt32 frames = my_min<int>(my_max<int>(num_samples,
					  (int) bufferRange.mMinimum),
			      (int) bufferRange.mMaximum);

  err = AudioDeviceSetProperty(devid, NULL, 0, isInput,
			       kAudioDevicePropertyBufferFrameSize,
			       propsize, &frames);
    
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not set buffer size");
    }


  propsize = sizeof(frames);
  err = AudioDeviceGetProperty(devid, 0, isInput,
			       kAudioDevicePropertyBufferFrameSize,
			       &propsize, &frames);
    
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not read buffer size");
    }

  char bbc[256] = {0};
  sprintf(bbc, "Buffer size in frames: %i", frames);
  logger(2, bbc);

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
  memset(&m_impl->m_input_format, 0, sizeof(m_impl->m_input_format));
  

  // set channels, format to SF_16LE

  m_impl->m_input_format.mSampleRate       = sample_rate;
  m_impl->m_input_format.mFormatID         = kAudioFormatLinearPCM;
  m_impl->m_input_format.mFormatFlags
         = kLinearPCMFormatFlagIsSignedInteger |
           kLinearPCMFormatFlagIsPacked;

  m_impl->m_input_format.mBytesPerPacket   = 2*channels;
  m_impl->m_input_format.mFramesPerPacket  = 1;
  m_impl->m_input_format.mBytesPerFrame    = m_impl->m_input_format.mBytesPerPacket;
  m_impl->m_input_format.mChannelsPerFrame = channels;
  m_impl->m_input_format.mBitsPerChannel   = 16;

#define USE_COMPLEX_AUDIO_CONVERTER
  //#define USE_SIMPLE_AUDIO_CONVERTER

#if defined(USE_SIMPLE_AUDIO_CONVERTER)
  m_impl->m_converter = new SimpleConverter(m_impl->m_input_format,
					    m_impl->m_format);
#elif defined (USE_COMPLEX_AUDIO_CONVERTER)
  m_impl->m_converter = new ComplexConverter(m_impl->m_input_format,
					     m_impl->m_format);
#else
    // TODO: this works only for 2 channels float to 1 channel mono 16LE!
  m_impl->m_converter = new Mono16LEPCMToStereoFloat;
#endif

  print_format pf1(logger, "Device Format\n");
  pf1(m_impl->m_format);

  print_format pf2(logger, "Input Format\n");
  pf2(m_impl->m_input_format);

  // Set the buffer latency (audio output is only started after
  // the buffer contains m_min_buffer samples).
  m_impl->m_min_buffer = num_samples*num_periods;
  m_impl->m_ID = devid;

  AudioDeviceAddIOProc(devid, Impl::OutputIOProc, m_impl.get());
}


void CoreAudioOutDriver::close()
{
  if (!this->is_open())
    return;

  m_impl->m_logger(2, "Closing audio...");

  if (!this->is_open())
    return;

  m_impl->stop_audio();
	
  while (m_impl->m_outputProcState != Impl::kOff)
    usleep(5000);
	
  AudioDeviceRemoveIOProc(m_impl->m_ID, Impl::OutputIOProc);

  m_impl->m_ID = kAudioDeviceUnknown;
  delete m_impl->m_converter;
  m_impl->m_converter = 0;
}

int CoreAudioOutDriver::write(const unsigned char* data, int num_samples)
{
  if (!this->is_open())
    throw std::logic_error("Device not open");

  m_impl->new_data(data, num_samples*m_impl->m_input_format.mBytesPerFrame);
  return num_samples;
}

bool CoreAudioOutDriver::is_open() const
{
  return m_impl->m_ID != kAudioDeviceUnknown;
}
