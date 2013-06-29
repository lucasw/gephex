#ifndef INCLUDED_COREAUDIO_CONVERT_H
#define INCLUDED_COREAUDIO_CONVERT_H

#include <CoreAudio/CoreAudio.h>
#include <AudioToolbox/AudioConverter.h>

class IConverter
{
 public:
  virtual ~IConverter() = 0;

  virtual OSStatus convert(const unsigned char* input_data,
			   int num_input_bytes,
			   unsigned char* output_data,
			   int& size_output_buffer) = 0;
};

class StereoFloatToMono16LEPCM : public IConverter
{
public:
  OSStatus convert(const unsigned char* input_data,
		   int num_input_bytes,
		   unsigned char* output_data,
		   int& size_output_buffer);
};


class Mono16LEPCMToStereoFloat : public IConverter
{
public:
  OSStatus convert(const unsigned char* input_data,
		   int num_input_bytes,
		   unsigned char* output_data,
		   int& size_output_buffer);
};

class CoreAudioConverterBase : public IConverter
{
public:
  CoreAudioConverterBase(const AudioStreamBasicDescription& sourceFormat,
			 const AudioStreamBasicDescription& destFormat);

  ~CoreAudioConverterBase();

protected:
  AudioConverterRef           m_converter;
  AudioStreamBasicDescription m_sourceFormat;
  AudioStreamBasicDescription m_destFormat;  
};

class SimpleConverter : public CoreAudioConverterBase
{
public:
  SimpleConverter(const AudioStreamBasicDescription& sourceFormat,
		  const AudioStreamBasicDescription& destFormat);

  OSStatus convert(const unsigned char* input_data,
		   int num_input_bytes,
		   unsigned char* output_data,
		   int& size_output_buffer);
};


class ComplexConverter : public CoreAudioConverterBase
{
public:
  ComplexConverter(const AudioStreamBasicDescription& sourceFormat,
		   const AudioStreamBasicDescription& destFormat);

  OSStatus convert(const unsigned char* input_data,
		   int num_input_bytes,
		   unsigned char* output_data,
		   int& size_output_buffer);
};

#endif
