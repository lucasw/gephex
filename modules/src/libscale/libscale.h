#ifndef INCLUDED_LIB_SCALE_H
#define INCLUDED_LIB_SCALE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "basic_types.h"

  typedef uint_8 ls_adjust_pal[256];

  /**
   * Inits a colorspace adjustment.
   */
  void ls_set_adjustment(ls_adjust_pal pal,
                         double bright,
                         double contrast,
                         double gamma,
                         int invert);

  /**
   * Copying with colorspace adjustment.
   */
  void ls_cpy_adjust(uint_32* dst, const uint_32* src,
                     int width, int height, const ls_adjust_pal);

  /**
   * Scaling with mirroring and colorspace adjustment.
   */
  void ls_scale32m_adjust(uint_32* dst,       int dwidth, int dheight,
                          const uint_32* src, int swidth, int sheight,
                          int mirrorx, int mirrory, const ls_adjust_pal pal);

  /**
   * Scaling with mirroring
   */
  void ls_scale32m(uint_32* dst,       int dwidth, int dheight,
                   const uint_32* src, int swidth, int sheight,
                   int mirrorx, int mirrory);

  void ls_scale32(uint_32* dst,       int dwidth, int dheight,
                  const uint_32* src, int swidth, int sheight);

#ifdef __cplusplus
}
#endif

#endif
