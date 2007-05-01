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

#ifndef INCLUDED_CORE_AUDIO_DRIVER_H
#define INCLUDED_CORE_AUDIO_DRIVER_H

#include <memory>

#include "audioindriver.h"

class CoreAudioDriver : public AudioInDriver
{
public:
  CoreAudioDriver();
  virtual ~CoreAudioDriver();

  void open(logT logger,
	    device_id_t device,
	    int sample_rate,
	    sample_format format,
	    int channels);

  virtual void close();

  /**
   * Returns number of *samples* (not bytes) that have been read.
   * data must be big enough to hold num_samples samples
   */
  int read(unsigned char* data, int num_samples);

  bool is_open() const;

private:
  struct Impl;
  std::auto_ptr<Impl> m_impl;
};

#endif
