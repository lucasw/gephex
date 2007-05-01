#ifndef INCLUDED_COREAUDIO_HELPER_H
#define INCLUDED_COREAUDIO_HELPER_H

#include <vector>
#include <stdexcept>

#include <CoreAudio/CoreAudio.h>

template <typename T>
T my_min(T a, T b) { return a <= b ? a : b; }

class MutexPOSIX
{
 public:
  MutexPOSIX();
  ~MutexPOSIX();

  void acquire();

  void release();

    
 private:
  MutexPOSIX(const MutexPOSIX&); // not implemented;
  MutexPOSIX& operator=(const MutexPOSIX&); // not implemented;

  void* m_mutex;
};

class MutexHolder
{
 public:
  MutexHolder(MutexPOSIX& mutex) : m_mutex(mutex)
    {
      m_mutex.acquire();
    }

    ~MutexHolder()
      {
	m_mutex.release();
      }

 private:
    MutexPOSIX& m_mutex;
};

typedef void (*logT)(int, const char*);

AudioDeviceID GetDeviceID(logT logger, int dev);

struct print_format
{
  print_format(logT logger,
	       const char* title);

  void operator()(const AudioStreamBasicDescription& format) const;

  logT m_logger;
  const char* m_title;
};

template <typename T>
std::vector<T> get_prop_list(AudioDeviceID devID, AudioDevicePropertyID pID,
			     bool isInput)
{
  OSStatus err;
  UInt32 propsize;
  
  Boolean outWritable;
  err = AudioDeviceGetPropertyInfo(devID, 0, isInput,
				   pID, 
				   &propsize, &outWritable);
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not property info");
    }

  std::vector<T> elems(propsize / sizeof(T));
  err = AudioDeviceGetProperty(devID, 0, isInput,
			       pID,
			       &propsize, &elems[0]);
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not read stream infor");
    }

  return elems;
}

template <typename T>
std::vector<T> get_stream_prop_list(AudioStreamID sID, AudioDevicePropertyID pID)
{
  OSStatus err;
  UInt32 propsize;

  Boolean outWritable;
  err = AudioStreamGetPropertyInfo(sID, 0,
				   pID, 
				   &propsize, &outWritable);
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not get property info");
    }

  std::vector<T> elems(propsize / sizeof(T));
  err = AudioStreamGetProperty(sID, 0,
			       pID,
			       &propsize, &elems[0]);
  if (err != kAudioHardwareNoError)
    {
      throw std::runtime_error("Could not read grr");
    }

  return elems;
}


void print_info(AudioDeviceID devid, logT logger, bool isInput);

#endif
