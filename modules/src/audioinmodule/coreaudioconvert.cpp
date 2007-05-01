#include "coreaudioconvert.h"

#include <stdexcept>
#include <climits>
#include <stdint.h>

namespace
{
  template <typename T>
  T my_min(T a, T b) { return a <= b ? a : b; }

  class ConversionHelper
  {
  public:
    ConversionHelper(AudioConverterRef converter,
		     const unsigned char* input_data,
		     int num_input_data_bytes,
		     int sourceChannels,
		     int sourceBytesPerPacket,
		     int destChannels,
		     int destBytesPerPacket)
      : m_converter(converter),
	m_data(input_data),
	m_num_data_bytes(num_input_data_bytes),
	m_sourceChannels(sourceChannels),
	m_sourceBytesPerPacket(sourceBytesPerPacket),
	m_destChannels(destChannels),
	m_destBytesPerPacket(destBytesPerPacket),
	m_pos(0)
    {}

    OSStatus convert(unsigned char* output_data, UInt32* output_size_bytes)
    {
      AudioBufferList bufferList;
      bufferList.mNumberBuffers = 1;
      bufferList.mBuffers[0].mNumberChannels = m_destChannels;
      bufferList.mBuffers[0].mDataByteSize   = *output_size_bytes;
      bufferList.mBuffers[0].mData           = output_data;

      UInt32 ioOutputDataPacketSize = m_num_data_bytes / m_sourceBytesPerPacket;
 
      OSStatus err = AudioConverterFillComplexBuffer(m_converter,
						     inputProc,
						     this,
						     &ioOutputDataPacketSize,
						     &bufferList,
						     0);

      if (err != kAudioHardwareNoError)
	return err;

      assert(m_pos == m_num_data_bytes);

      *output_size_bytes = ioOutputDataPacketSize*m_destBytesPerPacket;

      return kAudioHardwareNoError;
    }

    static OSStatus inputProc(AudioConverterRef inAudioConverter, 
			      UInt32* ioNumberDataPackets, 
			      AudioBufferList* ioData, 
			      AudioStreamPacketDescription** /*outDataPacketDescription*/, 
			      void* inUserData)

    {
      ConversionHelper* helper = reinterpret_cast<ConversionHelper*>(inUserData);

      if (ioData->mNumberBuffers != 1)
	return kAudioConverterErr_InvalidInputSize;

      int numBytes = my_min<int>(*ioNumberDataPackets * helper->m_sourceBytesPerPacket,
				 helper->m_num_data_bytes - helper->m_pos);
      
      ioData->mBuffers[0].mNumberChannels = helper->m_sourceChannels;

      ioData->mBuffers[0].mData           = (numBytes > 0) ? &helper->m_data[helper->m_pos] : 0;

      ioData->mBuffers[0].mDataByteSize   = numBytes;

      helper->m_pos += numBytes;

      *ioNumberDataPackets = numBytes / helper->m_sourceBytesPerPacket;

      return noErr;
    }

  private:
    AudioConverterRef    m_converter;
    const unsigned char* m_data;
    int                  m_num_data_bytes;
    int                  m_sourceChannels;
    int                  m_sourceBytesPerPacket;
    int                  m_destChannels;
    int                  m_destBytesPerPacket;
    int                  m_pos;
  };
}

IConverter::~IConverter() {}

OSStatus StereoFloatToMono16LEPCM::convert(const unsigned char* input_data,
					   int num_input_bytes,
					   unsigned char* output_data,
					   int& size_output_buffer)
{
  const int inputDataSizeBytes = my_min(num_input_bytes,
					size_output_buffer * 8 / 2);

  // This works only for 2 channels float to 1 channel mono 16LE!
  const float scale = 0.5*SHRT_MAX; // TODO

  const float* src = reinterpret_cast<const float*>(input_data);
  int16_t* dst = reinterpret_cast<int16_t*>(output_data);

  for (int i = inputDataSizeBytes / 8; i > 0; --i)
    {
      const int16_t tmp = static_cast<int16_t>(scale * *(src++) * *(src++));
      char* d = reinterpret_cast<char*>(dst++);
      d[1] = static_cast<char>(tmp & 0xFF);
      d[0] = static_cast<char>((tmp >> 8) & 0xFF);
    }

  size_output_buffer = inputDataSizeBytes * 2 / 8;

  return kAudioHardwareNoError;
}

OSStatus Mono16LEPCMToStereoFloat::convert(const unsigned char* input_data,
					   int num_input_bytes,
					   unsigned char* output_data,
					   int& size_output_buffer)
{
  const int inputDataSizeBytes = my_min(num_input_bytes,
					size_output_buffer * 2 / 8);

  // This works only for 1 channel mono 16LE to 2 channels float!
  const float scale = 1.0 / SHRT_MAX; // TODO

  const int16_t* src = reinterpret_cast<const int16_t*>(input_data);
  float* dst = reinterpret_cast<float*>(output_data);

  for (int i = inputDataSizeBytes / 2; i > 0; --i)
    {
      *(dst++) = scale * *(src);
      *(dst++) = scale * *(src++); // TODO: endianness!
    }

  size_output_buffer = inputDataSizeBytes * 8 / 2;

  return kAudioHardwareNoError;
}

CoreAudioConverterBase::CoreAudioConverterBase(const AudioStreamBasicDescription& sourceFormat,
					       const AudioStreamBasicDescription& destFormat)
  : m_sourceFormat(sourceFormat), m_destFormat(destFormat)
  {
    OSStatus err = AudioConverterNew(&m_sourceFormat,
				     &m_destFormat,
				     &m_converter);
  
    if (err != kAudioHardwareNoError)
      {
	throw std::runtime_error("Could not create audio converter");
      }
  }

CoreAudioConverterBase::~CoreAudioConverterBase()
{
  AudioConverterDispose(m_converter);
}

SimpleConverter::SimpleConverter(const AudioStreamBasicDescription& sourceFormat,
				 const AudioStreamBasicDescription& destFormat)
  : CoreAudioConverterBase(sourceFormat, destFormat)
{}

OSStatus SimpleConverter::convert(const unsigned char* input_data,
				  int num_input_bytes,
				  unsigned char* output_data,
				  int& size_output_buffer)
{
  const int inputDataSizeBytes = my_min(num_input_bytes,
					size_output_buffer * 8 / 2);
  
  UInt32 outputDataSizeBytes = size_output_buffer;

  OSStatus err = AudioConverterConvertBuffer(m_converter,
					     inputDataSizeBytes,
					     input_data,
					     &outputDataSizeBytes,
					     output_data);

  size_output_buffer = outputDataSizeBytes;

  return err;
}

ComplexConverter::ComplexConverter(const AudioStreamBasicDescription& sourceFormat,
				   const AudioStreamBasicDescription& destFormat)
  : CoreAudioConverterBase(sourceFormat, destFormat)
{}

OSStatus ComplexConverter::convert(const unsigned char* input_data,
				   int num_input_bytes,
				   unsigned char* output_data,
				   int& size_output_buffer)
{
  ConversionHelper helper(m_converter,
			  input_data,
			  num_input_bytes,
			  m_sourceFormat.mChannelsPerFrame,
			  m_sourceFormat.mBytesPerPacket,
			  m_destFormat.mChannelsPerFrame,
			  m_destFormat.mBytesPerPacket);

  UInt32 outputDataSizeBytes = size_output_buffer;

  OSStatus err = helper.convert(output_data, &outputDataSizeBytes);

  size_output_buffer = outputDataSizeBytes;

  return err;
}
