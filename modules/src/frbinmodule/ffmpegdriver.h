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

#ifndef INCLUDED_FFMPEG_DRIVER
#define INCLUDED_FFMPEG_DRIVER

#include <memory>

#include "videofiledriver.h"

struct FFMpegDriverImpl;

class FFMpegDriver : public VideoFileDriver
{
 public:
  FFMpegDriver();
  virtual ~FFMpegDriver();
  
  static std::list<std::string> supported_extensions();
  
  void load_file(const std::string& file_name, VideoInfo& info);

  void close_file();
  
  bool is_open() const;  

  void decode_frame(unsigned int frame_number, uint_32* framebuffer,
	                int width, int height);
  
 private:
  std::auto_ptr<FFMpegDriverImpl> m_impl;
};
#endif
