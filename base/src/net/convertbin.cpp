#include "convertbin.h"

namespace net
{
    void convert_uint32_to_le(uint_32 i, unsigned char raw[4])
    {
      raw[0] = static_cast<unsigned char>((i & 0x000000ff) >> 0);
      raw[1] = static_cast<unsigned char>((i & 0x0000ff00) >> 8);
      raw[2] = static_cast<unsigned char>((i & 0x00ff0000) >> 16);
      raw[3] = static_cast<unsigned char>((i & 0xff000000) >> 24);
    }

    uint_32 convert_uint32_from_le(const unsigned char* raw_data)
    {
      return raw_data[0] | (raw_data[1] << 8) | (raw_data[2] << 16)
        | (raw_data[3] << 24);
    }
}
