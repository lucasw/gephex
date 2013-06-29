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

#ifndef INCLUDED_CAPTURE_DRIVER_H
#define INCLUDED_CAPTURE_DRIVER_H

#include "basic_types.h"

class CaptureDriver
{
 public:
  
  virtual ~CaptureDriver() {};
  /**   
   * 
   * \param device the device number of the file   
   *
   * \throws std::invalid_argument if device can't be opened
   */
  virtual void open(int device) = 0;

  virtual void close() = 0;  
  
  /**   
   * Returns information about the current status.
   *
   * \param width the width of the captured stream
   * \param height the height of the captured stream
   * \param new_frame is true if there is a new frame (since the last call
   *                  of decode_frame)
   *
   * \throw std::logic_error if the driver is not open
   */
  virtual void status(int& width, int& height, bool& new_frame) const = 0;

  virtual bool is_open() const = 0;

  /**
   * Decodes a frame into the framebuffer.
   *
   * \param framebuffer the buffer the image is copied to
   *        the size must be at least width*height*4.
   *   
   * \throws std::invalid_argument if no device is open
   * \throws std::runtime_error if something bad happens
   */
  virtual void decode_frame(uint_32* framebuffer, int width, int height) = 0;
};


#endif

