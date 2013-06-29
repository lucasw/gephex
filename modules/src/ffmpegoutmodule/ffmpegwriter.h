/* This source file is a part of the GePhex Project.

 Copyright (C) 2004

 Michael Mandl <mandlm@gephex.org>
 
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

#ifndef ffmpegwriter_h
#define ffmpegwriter_h

#include <iostream>
#include <map>

#if defined _MSC_VER
#define EMULATE_INTTYPES
#endif

extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
}

class FFMpegWriter
{
 public:
  FFMpegWriter(const std::string &filename, int xres, int yres, 
	       std::string encoding);
  ~FFMpegWriter();

  void writeFrame(uint32_t *frame);
  std::string getFilename();
  int getXres();
  int getYres();
  std::string getEncoding();

 private:

  void initEncoder();
  void initEncoderMap();
  void initStream();
  void cleanup();

  void open_video(AVFormatContext *oc, AVStream *st);
  AVStream *add_video_stream(AVFormatContext *oc, int codec_id);
  AVFrame *alloc_picture(int pix_fmt, int width, int height);
  void close_video(AVFormatContext *oc, AVStream *st);
  void write_video_frame(AVFormatContext *oc, AVStream *st, AVFrame *picture_ptr);

  std::string outfile;
  std::string encstr;
  int fps;
  int x_res, y_res;
  unsigned int bps;

  typedef std::map<std::string, std::pair<int, std::string> > encmap_t;
  encmap_t encmap;

  uint8_t *video_outbuf;
  int video_outbuf_size;
  AVFrame *picture, *tmp_picture;
  int frame_count;

  AVOutputFormat *fmt;
  AVFormatContext *oc;
  AVStream *audio_st, *video_st;


};




#endif
