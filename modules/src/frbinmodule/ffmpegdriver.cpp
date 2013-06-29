/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2008

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

#include "ffmpegdriver.h"

#include <string>
#include <stdexcept>
#include <sstream>
#include <memory>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>

#if defined _MSC_VER
#define EMULATE_INTTYPES
#endif

extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
}

#include "libscale.h"

//----------------------------------------------------------------------

static int estimate_duration(AVFormatContext* av_fc, int stream_index,
                             double fps,
                             double* duration,
                             double* start_time);

static void open_stream(AVFormatContext* av_fc, int stream_index);
static void close_stream(AVFormatContext* av_fc, int stream_index);
static void dump_stream_info(AVFormatContext *s);

static int seek_to_second(AVFormatContext* st, int stream_index, double sec);

//----------------------------------------------------------------------

static int next_video_frame(AVPacket* pkt, AVFormatContext* fc,
                            int video_stream_index)
{
  pkt->stream_index = -1;
  int counter = 17;
  // read next video packet
  while (pkt->stream_index != video_stream_index)
    {
      if (pkt->data)
        av_free_packet(pkt);

      if (av_read_frame(fc, pkt) < 0)
        {
          std::cerr << "Error while reading frame\n";
          return -1;
        }

      --counter;

      if (counter == 0)
        {
          av_free_packet(pkt);
          std::cerr << "Could not read video data";
          return -1;
        }
    }

  if (pkt->size == 0)
    {
      std::cerr << "Nothing to read";
      return -1;
    }

  return 1;
}


static int decode(AVFormatContext* fc, int video_stream_index, 
                  AVFrame* frame, AVPacket* pkt, int *got_frame)
{
    AVStream* video_stream = fc->streams[video_stream_index];
    *got_frame = 0; 

    if (video_stream->codec->codec_id == CODEC_ID_RAWVIDEO)
      {
        avpicture_fill((AVPicture *)frame,
                       pkt->data, 
                       video_stream->codec->pix_fmt,
                       video_stream->codec->width,
                       video_stream->codec->height);
        frame->pict_type = FF_I_TYPE;

        *got_frame = 1;
#if defined FFMPEGDRIVER_PRINT_DEBUG
        std::cout << "raw video\n";
#endif
      }
    else
      {
        int len = avcodec_decode_video(video_stream->codec,
                                       frame, got_frame,
                                       pkt->data,
                                       pkt->size);
        if (len < 0)
          {
            std::cerr << "Error while decoding frame\n";
            return -1;
          }
        else
          {
#if defined FFMPEGDRIVER_PRINT_DEBUG
            std::cout << "decoded " << len << " bytes\n";
#endif
            if (len != pkt->size)
              {
                std::cerr << "Did not decode whole frame packet!\n";
              }
          }
      }

    return 1;
}

static int decode_to_timestamp(AVFormatContext* fc,
                               int video_stream_index,
                               double wanted_timestamp, double fps,
                               AVPacket* pkt, AVFrame* frame,
                               double* timestamp)
{
  double frame_duration = 1.0 / fps;
  double current_timestamp = wanted_timestamp - 2*frame_duration;

  int counter = 0;

  AVStream* video_stream = fc->streams[video_stream_index];
  double time_base = av_q2d(video_stream->time_base);

  while (fabs(current_timestamp - wanted_timestamp) >= 0.98*frame_duration)
    {
      int ret = next_video_frame(pkt, fc, video_stream_index);
      
      if (ret < 0)
          return -1;

      int got_frame = 0;
      ret = decode(fc, video_stream_index, frame, pkt, &got_frame);

      if (got_frame)
        current_timestamp = ((double) pkt->pts) * time_base;
      av_free_packet(pkt);

      if (ret < 0)
        return -1;

      if (pkt->pts == AV_NOPTS_VALUE)
        {
          std::cerr << "Invalid pts in packet\n";
          return -1;
        }

      ++counter;
    }

#if defined FFMPEGDRIVER_PRINT_DEBUG    
  std::cout << "decoded " << counter << " frames\n";
#endif

  *timestamp = current_timestamp;
  return 1;
}


namespace
{
  bool is_big_endian()
  {
    const int test = 0x01020304;
    const unsigned char* mask = reinterpret_cast<const unsigned char*>(&test);
    return mask[0] == 0x01;
  }

  void switch_byteorder(uint32_t& v)
  {
    uint32_t tmp;

    const unsigned char* src = reinterpret_cast<unsigned char*>(&v);
    unsigned char* dst = reinterpret_cast<unsigned char*>(&tmp);

    dst[0] = src[3];
    dst[1] = src[2];
    dst[2] = src[1];
    dst[3] = src[0];

    v = tmp;
  }
}

//----------------------------------------------------------------------

struct FFMpegDriverImpl
{
  FFMpegDriverImpl()
    : av_fc(0), file_name(""),
      m_width(0), m_height(0), m_num_frames(0),
      video_stream_index(-1), m_frame(0), m_fps(25),
      m_scale_buf(0), m_scale_buf_size(0),
      m_start_time(0), m_current_timestamp(0)
  {
    av_register_all();    // register all decoders
  }

  ~FFMpegDriverImpl()
  {
    close();
  }

  void open(const std::string& filename, VideoInfo& info)
  {
    std::cerr << "load_file_start:'" << filename << "'\n";

    AVFormatParameters params;
    
    memset(&params, 0, sizeof(params));
    params.initial_pause = 1;

    // open input file without format or bufffer size
    // (let ffmpeg try autodetection)
    int err = av_open_input_file(&av_fc,
                                 filename.c_str(), 
                                 0,
                                 0,
                                 &params);

    if (err < 0)
      {
        std::cerr << "err = " << err << "\n";
        throw std::runtime_error("could not open file");
      }
  
    err = av_find_stream_info(av_fc);
    if (err < 0)
      {
        close();
        throw std::runtime_error("Could not find codec parameters\n");
      }

  
    // look for the video stream
    int stream_index = -1;
    for (int i = 0; i < av_fc->nb_streams; i++)
      {
        AVCodecContext* enc = av_fc->streams[i]->codec;
        if (enc->codec_type == CODEC_TYPE_VIDEO)
          {
            stream_index = i;
            break;
          }
      }

    if (stream_index == -1)
      {
        close();
        throw std::runtime_error("Could not find any video streams in file");
      }

    // some debug info
    dump_format(av_fc, 0, filename.c_str(), 0);
    dump_stream_info(av_fc);

    try
      {
        open_stream(av_fc, stream_index);
        video_stream_index = stream_index;
      }
    catch (...)
      {
        close();
        throw;
      }

    AVCodecContext* enc = av_fc->streams[video_stream_index]->codec;
    if (enc->width == 0)
      {
        close();
        throw std::runtime_error("No width and height");
      }

    AVStream* video_stream = av_fc->streams[video_stream_index];

    m_fps = av_q2d(video_stream->r_frame_rate);
    double duration_s;
    int ret = estimate_duration(av_fc, video_stream_index, m_fps,
                                &duration_s, &m_start_time);
    if (ret < 0)
      {
        close();
        throw std::runtime_error("Could not estimate stream duration");
      }

    int num_frames = static_cast<int>(floor(av_q2d(video_stream->r_frame_rate) * duration_s));

    info.width  = enc->width;
    info.height = enc->height;
    info.num_frames = num_frames;

    m_width  = info.width;
    m_height = info.height;
    m_num_frames = info.num_frames;

    std::cout << "(width x height) = (" << info.width
              << "x" << info.height <<")\n";
    std::cout << "#frames = " << info.num_frames << "\n";

    m_current_timestamp = -100;

    std::cout << "duration  : " << duration_s
              << "s (" << (double) video_stream->duration * av_q2d(video_stream->time_base)
              << " s)\n";
    std::cout << "start_time: " << m_start_time << " s\n";
    std::cout << "fps       : " << m_fps << "\n";

    std::cout << "timebase  : " 
              << av_q2d(video_stream->time_base) << "\n";

    m_frame = avcodec_alloc_frame();
    file_name = filename;
    m_bytes_left = 0;

    m_scale_buf = 0;
    m_scale_buf_size = 0;
  }

  void close()
  {
    if (m_scale_buf)
      {
        delete[] m_scale_buf;
        m_scale_buf = 0;
      }

    if (m_frame != 0)
      {
        av_free(m_frame);
        m_frame = 0;
      }

    if ( video_stream_index != -1 )
      {
        close_stream(av_fc, video_stream_index);
        video_stream_index = -1;
      }

    if ( av_fc != 0 )
      {
        av_close_input_file(av_fc);
        av_fc = 0;
      }

    file_name           = "";
    m_width = m_height  = m_num_frames = 0;
    m_scale_buf_size    = 0;
    m_current_timestamp = 0;
    m_start_time        = 0;
  }

  bool is_open() const
  {
    return av_fc != 0;
  }

  int num_frames() const
  {
    return m_num_frames;
  }

  void decode_frame(unsigned int frame_number,
                    uint_32* framebuffer,
                    int width, int height)
  {
    assert(av_fc != 0);

    double wanted_timestamp = m_start_time + ((double) frame_number) / m_fps;

    double frame_duration = 1.0 / m_fps;
    
    // do we have to seek?
    if (fabs(wanted_timestamp - m_current_timestamp) >= 0.98*frame_duration)
      {
#if defined FFMPEGDRIVER_PRINT_DEBUG
        std::cout << "Need to seek: wanted_timestamp =" << wanted_timestamp
                  << "s - m_current_timestamp = " << m_current_timestamp
                  << "s (frame_duration = " << frame_duration << "s)\n";

        std::cout << "seeking to frame " << frame_number 
                  << ", time " << wanted_timestamp << "s\n";
#endif

        // first seek to the nearest keyframe before wanted_timestamp
        int ret = seek_to_second(av_fc, video_stream_index, wanted_timestamp);

        if (ret < 0)
          {
            std::cerr << "Could not seek\n";
          }
      }
#if defined FFMPEGDRIVER_PRINT_DEBUG
    else
      {
        std::cout << "No need to seek: wanted_timestamp =" << wanted_timestamp
                  << "s - m_current_timestamp = " << m_current_timestamp
                  << "s (frame_duration = " << frame_duration
                  << "s, diff = "
                  << fabs(wanted_timestamp - m_current_timestamp) << "s)\n";
      }
#endif

    AVPacket pkt;
    pkt.stream_index = -1;
    pkt.data = 0;

    int ret = decode_to_timestamp(av_fc, video_stream_index, wanted_timestamp,
                                  m_fps, &pkt, m_frame, &m_current_timestamp);

    if (ret < 0)
      {
        throw std::runtime_error("Could not decode");
      }

    m_current_timestamp += frame_duration;

    av_free_packet(&pkt);

#if defined FFMPEGDRIVER_PRINT_DEBUG
    std::cout << "-> got frame\n";
#endif
    int dst_pix_fmt = PIX_FMT_RGBA32;
    AVPicture pict;

    AVStream* video_stream = av_fc->streams[video_stream_index];

    int cwidth  = video_stream->codec->width;
    int cheight = video_stream->codec->height;

    if (video_stream->codec->width == width &&
        video_stream->codec->height == height)
      {
        pict.data[0] = (uint_8*) framebuffer;
      }
    else
      {
        int size = cwidth*cheight*4;
        if (m_scale_buf == 0 || m_scale_buf_size < size)
          {
            if (m_scale_buf)
              delete[] m_scale_buf;
            
            m_scale_buf = new uint_8[size];
            m_scale_buf_size = size;
          }
        pict.data[0] = m_scale_buf;
      }

    pict.data[1] = pict.data[2] = pict.data[0];
    pict.linesize[0] = cwidth*4;
    pict.linesize[1] = pict.linesize[2] = 0;
    
    img_convert(&pict, dst_pix_fmt,
                (AVPicture *) m_frame,
                video_stream->codec->pix_fmt,
                video_stream->codec->width,
                video_stream->codec->height);
    
    if (cwidth != width || cheight != height)
      {
        ls_scale32(framebuffer, width, height,
                   reinterpret_cast<const uint_32*>(pict.data[0]),
                   cwidth, cheight);
      }
    else
      {
        if (m_scale_buf)
          {
            delete[] m_scale_buf;
            m_scale_buf = 0;
            m_scale_buf_size = 0;
          }
      }

    // Correct byte order on big endian machines (using the
    // correct pixel format crashes in img_convert).
    if (is_big_endian())
      {
	std::for_each(framebuffer, framebuffer + width*height,
		      switch_byteorder);
      }
  }

private:
  AVFormatContext* av_fc;

  std::string file_name;
  int m_width;
  int m_height;
  int m_num_frames;

  int video_stream_index;

  AVFrame* m_frame;

  double m_fps;

  int m_bytes_left;

  uint_8* m_scale_buf;
  int m_scale_buf_size;

  double m_start_time;
  double m_current_timestamp;
};

FFMpegDriver::FFMpegDriver()
  : m_impl(new FFMpegDriverImpl())
{
}

FFMpegDriver::~FFMpegDriver()
{
}

std::list<std::string> FFMpegDriver::supported_extensions()
{
  std::list<std::string> el;
  el.push_back("avi");
  el.push_back("divx");
  el.push_back("mpg");
  el.push_back("mpeg");
  el.push_back("mov");
  el.push_back("wmv");
  el.push_back("rm");
  el.push_back("*");

  return el;
}

void FFMpegDriver::load_file(const std::string& file_name, VideoInfo& info)
{
  if (m_impl->is_open())
    throw std::logic_error("Driver already open");

  m_impl->open(file_name, info);
}

void FFMpegDriver::close_file()
{
  m_impl->close();
}

bool FFMpegDriver::is_open() const
{
  return m_impl->is_open();
}

void FFMpegDriver::decode_frame(unsigned int frame_number,
                                uint_32* framebuffer,
                                int width, int height)
{
  if (!m_impl->is_open())
    throw std::logic_error("No file loaded");

  if (frame_number >= m_impl->num_frames())
    throw std::range_error("frame_number out of range");

  m_impl->decode_frame(frame_number, framebuffer, width, height);
}

//----------------------------------------------------------------------

/* open a given stream.  */
static void open_stream(AVFormatContext* av_fc, int stream_index)
{
  assert (stream_index >= 0 && stream_index < av_fc->nb_streams);
    
  AVCodecContext* enc = av_fc->streams[stream_index]->codec;
    
  AVCodec* codec = avcodec_find_decoder(enc->codec_id);

  if (codec == 0)
    throw std::runtime_error("could not find decoder");

  enc->debug_mv        = 0; //0
  enc->debug           = 0; //0
  enc->workaround_bugs = 1;

  // Inform the codec that we can handle truncated bitstreams -- i.e.,
  // bitstreams where frame boundaries can fall in the middle of packets
  //  if(codec->capabilities & CODEC_CAP_TRUNCATED)
  //    enc->flags |= CODEC_FLAG_TRUNCATED;

  if (avcodec_open(enc, codec) < 0)
    throw std::runtime_error("avcodec_open failed");

  enc->thread_count = 1;

  assert(enc->codec_type == CODEC_TYPE_VIDEO);

}

static void close_stream(AVFormatContext* av_fc, int stream_index)
{
  AVCodecContext *enc;
    
  enc = av_fc->streams[stream_index]->codec;

  assert(enc->codec_type == CODEC_TYPE_VIDEO);

  avcodec_close(enc);
}

static void dump_stream_info(AVFormatContext *s)
{
  if (s->track != 0)
    std::cerr <<  "Track: "<< s->track << "\n";

  if (s->title[0] != '\0')
    std::cerr << "Title: " << s->title << "\n";

  if (s->author[0] != '\0')
    std::cerr << "Author: " << s->author << "\n";

  if (s->album[0] != '\0')
    std::cerr << "Album: " << s->album << "\n";

  if (s->year != 0)
    std::cerr <<  "Year: " << s->year << "\n";

  if (s->genre[0] != '\0')
    std::cerr << "Genre: " << s->genre << "\n";
}

//----------------------------------------------------------------------

static int estimate_duration(AVFormatContext* av_fc,
                             int stream_index,
                             double fps,
                             double* duration,
                             double* start_time)
{
  std::cout << "estimate_duration, stream_index = "
            << stream_index << ", fps = " << fps << "\n";

  double frame_duration = 1.0 / fps;
  AVStream* stream = av_fc->streams[stream_index];  

  const double time_base = av_q2d(stream->time_base);

  int64_t start_pts = stream->start_time;
  if (start_pts == AV_NOPTS_VALUE)
    {
      start_pts = 0;
    }
  else if (start_pts < 0)
    {
      std::cerr << "Invalid negative stream->start_time, assuming 0\n";
      start_pts = 0;
    }

  double duration_0 = ((stream->duration == AV_NOPTS_VALUE) ? frame_duration
    : ((double) stream->duration * time_base));

  // assume at least 25 frames
  if (duration_0 <= 0)
    duration_0 = frame_duration*25;

  std::cout << "duration_0 = "
            << duration_0
            << " (stream->duration * time_base = "
            << stream->duration << " * " << time_base << " = "
            << (double) stream->duration * time_base
            << ")\n";

  std::cout << "seeking until success...\n";

  int ret = seek_to_second(av_fc, stream_index, duration_0);

  int seek_count = 1;
  // decrease duration until seek succeeds
  while (ret < 0 && duration_0 >= frame_duration)
    {
      std::cout << ".\n";
      duration_0 -= frame_duration;
      ret = seek_to_second(av_fc, stream_index, duration_0);
      ++seek_count;
    }

  if (ret < 0)
    {
      std::cerr << "Could not find duration by seeking\n";
      return -1;
    }

  AVPacket pkt;
  // read frames until EOF

  std::cout << "reading until eof...\n";
  
  int read_count = 0;
  bool read_once = false;
  while (av_read_frame(av_fc, &pkt) >= 0)
    {
      read_once = true;
      //std::cout << ",\n";
      if (pkt.stream_index == stream_index)
        {
          if (pkt.pts == AV_NOPTS_VALUE)
            {
              std::cerr << "Frame lacks pts\n";
            }
          else
            {
              duration_0 = (double) (pkt.pts - start_pts) * time_base;
            }

        }
      
      if (pkt.data)
        av_free_packet(&pkt);

      ++read_count;
    }

  if (read_once)
    {
      std::cout << "#seeks = " << seek_count << ", #reads = " << read_count
                << "\n";
      *duration   = duration_0;
      *start_time = (double) start_pts * time_base;
      return 1;
    }
  else
    {
      std::cerr << "Could not read a frame\n";
      return -1;
    }
}

//----------------------------------------------------------------------


static int64_t get_timestamp(double ts_sec, const AVRational& time_base)
{
  return static_cast<int64_t>(ts_sec/av_q2d(time_base) + 0.5);
}

static int seek_to_second(AVFormatContext* av_fc, int stream_index,
                          double sec)
{
  AVStream* video_stream = av_fc->streams[stream_index];

  int64_t ts = get_timestamp(sec, video_stream->time_base);

  return av_seek_frame(av_fc, stream_index, ts, AVSEEK_FLAG_BACKWARD);
}

//----------------------------------------------------------------------
