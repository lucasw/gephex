#ifndef INCLUDED_VIDE_FILE_DRIVER_H
#define INCLUDED_VIDE_FILE_DRIVER_H

#include <string>
#include <list>

#include "basic_types.h"

struct VideoInfo
{
  int num_frames; // TODO: what happens here if you play a stream?
  int width;
  int height;
};

class VideoFileDriver
{
 public:
  
  /**
   * Loads a video file
   *
   * Note that only videos that are 32bpp or can be converted to it
   * are allowed for now.
   * 
   * \param file_name the name of the file
   * \param VideoInfo a struct that is filled in with info about this
   *             video
   *
   * \throws std::invalid_argument if file can't be opened as a video
   */
  virtual void load_file(const std::string& file_name, VideoInfo& info) = 0;
  
  
  /**
   * Decodes a frame into the framebuffer.
   *
   * \param frame_number the frame that is decoded
   * \param framebuffer the buffer the image is copied to
   *        the size must be at least width*height*4.
   *
   * \throws std::range_error if frame_number is not in the valid range 
   *                          for this video
   * \throws std::invalid_argument if no video is loaded
   * \throws std::runtime_error if something bad happens
   */
  virtual void decode_frame(unsigned int frame_number,
                            uint_32* framebuffer) = 0;
};


#endif

