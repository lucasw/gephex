#include "a_cvt.h"

#include <algorithm>

namespace
{
  static const double MAX_VAL = (1<<15) - 1;

  bool is_little_endian()
  {
    const int test = 0x01020304;
    const unsigned char* mask = reinterpret_cast<const unsigned char*>(&test);
    return mask[0] == 0x04;
  }

  int16_t swap_endian_16(int16_t v)
  {
    int16_t result;
    unsigned char* dst_mask = reinterpret_cast<unsigned char*>(&result);
    const unsigned char* src_mask = reinterpret_cast<const unsigned char*>(&v);
    dst_mask[0] = src_mask[1];
    dst_mask[1] = src_mask[0];

    return result;
  }

  double c_16le_to_double_le(int16_t v)
  {
    return static_cast<double>(v) / MAX_VAL;
  }

  double c_16le_to_double_be(int16_t v)
  {
    return c_16le_to_double_le(swap_endian_16(v));
  }

  int16_t c_double_to_16le_le(double v)
  {
    return static_cast<int16_t>(v * MAX_VAL + 0.5);
  }

  int16_t c_double_to_16le_be(double v)
  {
    return swap_endian_16(c_double_to_16le_le(v));
  }
}

void a_cvt_16le_to_double_mono(const int16_t* src,
			       double* dst,
			       int num_samples)
{
  if (is_little_endian())
    {
      std::transform(src, src + num_samples,
		     dst,
		     c_16le_to_double_le);
    }
  else
    {
      std::transform(src, src + num_samples,
		     dst,
		     c_16le_to_double_be);
    }
}

void a_cvt_double_to_16le_mono(const double* src,
			       int16_t* dst,
			       int num_samples)
{
  if (is_little_endian())
    {
      std::transform(src, src + num_samples,
		     dst,
		     c_double_to_16le_le);
    }
  else
    {
      std::transform(src, src + num_samples,
		     dst,
		     c_double_to_16le_be);
    }
}
