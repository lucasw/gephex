#ifndef INCLUDED_CONVERT_BIN_H
#define INCLUDED_CONVERT_BIN_H

#include "basic_types.h"
/**
 *
 * Some functions to convert primitive data types to
 * and from a binary representation in little endian format.
 *
 */
namespace net
{
  /**
   * Casts the uint_32 to a raw representation in little endian
   * format.
   */
  void convert_uint32_to_le(uint_32 i, unsigned char raw[4]);

  /**
   * "Casts" an uint_32 from raw memory in a standard conforming
   * and platform independent way.
   * The memory is assumed to contain the uint_32 in little endian
   * format.
   * (Simply casting lead to bus errors on sparc32)
   */    
  uint_32 convert_uint32_from_le(const unsigned char* raw_data);
}

#endif
