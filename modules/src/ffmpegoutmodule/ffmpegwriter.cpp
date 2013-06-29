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

#include "ffmpegwriter.h"
#include <iostream>
#include <string>
#include <stdexcept>


FFMpegWriter::FFMpegWriter(const std::string &filename, int xres, int yres, 
			   std::string encoding)
  : outfile(filename), encstr(encoding), x_res(xres), y_res(yres)
{
  std::cout << "creating new ffmpeg writer " << filename << " " 
	    << xres << "x" << yres 
	    << ", encoding: " << encoding << std::endl;

  av_register_all();

  initEncoderMap();
  initEncoder();
  initStream();
}

FFMpegWriter::~FFMpegWriter()
{
  std::cout << "deleting ffmpeg writer " << std::endl;

  cleanup();
}

void FFMpegWriter::writeFrame(uint32_t *frame)
{
  AVFrame *frameRGB = avcodec_alloc_frame();
  avpicture_fill((AVPicture *)frameRGB, (uint8_t *)frame, PIX_FMT_RGBA32, x_res, y_res);
  
  write_video_frame(oc, video_st, frameRGB);

  av_free(frameRGB);
}


std::string FFMpegWriter::getFilename()
{
  return outfile;
}

int FFMpegWriter::getXres()
{
  return x_res;
}

int FFMpegWriter::getYres()
{
  return y_res;
}

std::string FFMpegWriter::getEncoding()
{
  return encstr;
}

void FFMpegWriter::initEncoderMap()
{
  encmap["DIVX High"]  = std::make_pair(800000, std::string("avi") );
  encmap["DIVX Low"]   = std::make_pair(200000, std::string("avi") );
  encmap["MPEG2 High"] = std::make_pair(800000, std::string("mpeg"));
  encmap["MPEG2 Low"]  = std::make_pair(200000, std::string("mpeg"));
  encmap["RM High"]    = std::make_pair(800000, std::string("rm"));
  encmap["RM Low"]     = std::make_pair(200000, std::string("rm"));
  encmap["MOV High"]   = std::make_pair(800000, std::string("mov"));
  encmap["MOV Low"]    = std::make_pair(200000, std::string("mov"));
}


void FFMpegWriter::initEncoder()
{
  encmap_t::const_iterator enc = encmap.find(encstr);

  if ( enc == encmap.end() )
    throw std::runtime_error( "unkown encoder format" );
  
  fmt = guess_format( enc->second.second.c_str(), NULL, NULL);
  bps = enc->second.first;

  // use mpeg if unable to guess
  if (fmt == NULL)
  {
    std::cout << "unable to guess file format, trying mpeg..." << std::endl;
    fmt = guess_format("mpeg", NULL, NULL);
    bps = 400000;
  }

  // mpeg not available
  if (fmt == NULL)
  {
    std::runtime_error("error initializing mpeg encoder!");
  }
  else
  {
    std::cout << "encoder initialized." << std::endl;
    std::cout << "format info (short name / extensions / bitrate): "
	      << fmt->name << " / " << fmt->extensions 
	      << " / " << bps << std::endl;
  }

  // allocate memory for output format context
  oc = av_alloc_format_context();
  if (oc == NULL) 
  {
    throw std::runtime_error("ffmpeg: memory error allocating format context");
  }
  
  // set output format
  oc->oformat = fmt;
}

void FFMpegWriter::initStream()
{

  // create the video stream
  video_st = add_video_stream(oc, fmt->video_codec);

  // set parameters for output format context
  av_set_parameters(oc, NULL);

  // blah blah stuff
  //  dump_format(oc, 0, outfile.c_str(), 1);

  // do final setup stuff...
  open_video(oc, video_st);

  /* open the output file, if needed */
  if (!(fmt->flags & AVFMT_NOFILE)) 
  {
    if (url_fopen(&oc->pb, outfile.c_str(), URL_WRONLY) < 0) 
      {
	std::runtime_error("Could not open outfile");
      }
  }

  // write file header if needed
  av_write_header(oc);
}

void FFMpegWriter::cleanup()
{
  close_video(oc, video_st);

  av_write_trailer(oc);

  /* free the streams */
  for(int i = 0; i < oc->nb_streams; i++) 
  {
    av_freep(&oc->streams[i]);
  }

  if (!(fmt->flags & AVFMT_NOFILE)) 
  {
    /* close the output file */
    url_fclose(oc->pb);
  }

  /* free the stream */
  av_free(oc);
}







/* add a video output stream */
AVStream *FFMpegWriter::add_video_stream(AVFormatContext *oc, int codec_id)
{
    AVCodecContext *c;
    AVStream *st;

    st = av_new_stream(oc, 0);
    if (!st) {
        fprintf(stderr, "Could not alloc stream\n");
        exit(1);
    }
    
    c = st->codec;
    c->codec_id = (CodecID)codec_id;
    c->codec_type = CODEC_TYPE_VIDEO;

    /* put sample parameters */
    c->bit_rate = bps;
    /* resolution must be a multiple of two */
    c->width = x_res;  
    c->height = y_res;
    /* frames per second */
    //    c->frame_rate = 25;  
    //    c->frame_rate_base = 1;
    c->gop_size = 12; /* emit one intra frame every twelve frames at most */

    // to kick???
    { 
      if (c->codec_id == CODEC_ID_MPEG2VIDEO) {
        /* just for testing, we also add B frames */
        c->max_b_frames = 2;
      }
      if (c->codec_id == CODEC_ID_MPEG1VIDEO){
        /* needed to avoid using macroblocks in which some coeffs overflow 
           this doesnt happen with normal video, it just happens here as the 
           motion of the chroma plane doesnt match the luma plane */
        c->mb_decision=2;
      }
    }

    // some formats want stream headers to be seperate
    if(!strcmp(oc->oformat->name, "mp4") || !strcmp(oc->oformat->name, "mov") || !strcmp(oc->oformat->name, "3gp"))
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;
    
    return st;
}


void FFMpegWriter::open_video(AVFormatContext *oc, AVStream *st)
{
    AVCodec *codec;
    AVCodecContext *c;

    c = st->codec;

    /* find the video encoder */
    codec = avcodec_find_encoder(c->codec_id);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }

    /* open the codec */
    if (avcodec_open(c, codec) < 0) {
        fprintf(stderr, "could not open codec\n");
        exit(1);
    }

    video_outbuf = NULL;
    if (!(oc->oformat->flags & AVFMT_RAWPICTURE)) {
        /* allocate output buffer */
        /* XXX: API change will be done */
        video_outbuf_size = 200000;
        video_outbuf = (uint8_t *)malloc(video_outbuf_size);
    }

    /* allocate the encoded raw picture */
    picture = alloc_picture(c->pix_fmt, c->width, c->height);
    if (!picture) {
        fprintf(stderr, "Could not allocate picture\n");
        exit(1);
    }

    /* if the output format is not YUV420P, then a temporary YUV420P
       picture is needed too. It is then converted to the required
       output format */
    tmp_picture = NULL;
    if (c->pix_fmt != PIX_FMT_YUV420P) {
        tmp_picture = alloc_picture(PIX_FMT_YUV420P, c->width, c->height);
        if (!tmp_picture) {
            fprintf(stderr, "Could not allocate temporary picture\n");
            exit(1);
        }
    }
}


AVFrame *FFMpegWriter::alloc_picture(int pix_fmt, int width, int height)
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;
    
    picture = avcodec_alloc_frame();
    if (!picture)
        return NULL;
    size = avpicture_get_size(pix_fmt, width, height);
    picture_buf = (uint8_t *)malloc(size);
    if (!picture_buf) {
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)picture, picture_buf, 
                   pix_fmt, width, height);

    return picture;
}
    

void FFMpegWriter::close_video(AVFormatContext *oc, AVStream *st)
{
    avcodec_close(st->codec);
    av_free(picture->data[0]);
    av_free(picture);
    if (tmp_picture) {
      av_free(tmp_picture->data[0]);
      av_free(tmp_picture);
    }
    av_free(video_outbuf);
}



void FFMpegWriter::write_video_frame(AVFormatContext *oc, AVStream *st, AVFrame *picture_ptr)
{
    int out_size, ret;
    AVCodecContext *c;

    AVFrame *final_picture;
        
    c = st->codec;

    // convert the rgba32 input image to codec-format
    img_convert((AVPicture *)picture, c->pix_fmt, 
		(AVPicture *)picture_ptr, PIX_FMT_RGBA32,
		c->width, c->height);

    final_picture = picture;
    
    if (oc->oformat->flags & AVFMT_RAWPICTURE) {
        /* raw video case. The API will change slightly in the near
           futur for that */
        AVPacket pkt;
        av_init_packet(&pkt);
        
        pkt.flags |= PKT_FLAG_KEY;
        pkt.stream_index= st->index;
        pkt.data= (uint8_t *)final_picture;
        pkt.size= sizeof(AVPicture);
        
        ret = av_write_frame(oc, &pkt);
    } else {
        /* encode the image */
        out_size = avcodec_encode_video(c, video_outbuf, video_outbuf_size, final_picture);
        /* if zero size, it means the image was buffered */
        if (out_size != 0) {
            AVPacket pkt;
            av_init_packet(&pkt);
            
            pkt.pts= c->coded_frame->pts;
            if(c->coded_frame->key_frame)
                pkt.flags |= PKT_FLAG_KEY;
            pkt.stream_index= st->index;
            pkt.data= video_outbuf;
            pkt.size= out_size;
            
            /* write the compressed frame in the media file */
            ret = av_write_frame(oc, &pkt);
        } else {
            ret = 0;
        }
    }
    if (ret != 0) {
        fprintf(stderr, "Error while writing video frame\n");
        exit(1);
    }
}
