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

  virtual ~VideoFileDriver() {}

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
   * \throws std::invalid_argument if file can't be opened
   * \throws std::runtime_error if file has wrong format
   */
  virtual void load_file(const std::string& file_name, VideoInfo& info) = 0;

  /**
   * Closes the video file.
   *
   * Must not throw any exception.
   */
  virtual void close_file() = 0;

  virtual bool is_open() const = 0;  
  
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
                            uint_32* framebuffer, int width, int height) = 0;
};


#endif

