#ifndef INCLUDED_FRAME_CACHE_H
#define INCLUDED_FRAME_CACHE_H

#include <string>
#include <memory>

#include "basic_types.h"

class FrameCache
{
 public:
  FrameCache(int size_in_mbytes);
  
  ~FrameCache();

  /**
   * Store one frame in the cache.
   * The cache is new owner of framebuffer, so don't modify
   * it afterwards (and don't delete it!!!)
   *
   * framebuffer must have been allocated with new[].
   */
  void store(const std::string& file_name, int frame_number,
             int width, int height, uint_32* framebuffer);

  /**
   * Returns 0 on cache miss.
   */
  uint_32* lookup(const std::string& file_name, int frame_number,
                  int width, int height) const;

  void flush();

 private:
  class Impl;
  std::auto_ptr<Impl> m_impl;
};
#endif
