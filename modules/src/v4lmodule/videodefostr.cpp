#include "videodefostr.h"

#include <linux/videodev.h> // video4linux interface

std::ostream& operator<<(std::ostream&s , const video_capability cap)
{
  s << "struct video_capability" << std::endl;
  s << "{" << std::endl;
  s << "  char name[32] = " << cap.name << std::endl;
  s << "  int type = " << cap.type << " = "<< std::endl;	
  s << "  {" << std::endl;	
  if (cap.type&VID_TYPE_CAPTURE) s << "    Can capture" << std::endl;
  if (cap.type&VID_TYPE_TUNER) s << "    Can tune" << std::endl;
  if (cap.type&VID_TYPE_TELETEXT) s << "    Can teletext" << std::endl;
  if (cap.type&VID_TYPE_OVERLAY) s << "    Can overlay onto frame buffer" << std::endl;
  if (cap.type&VID_TYPE_CHROMAKEY) s << "    Can overlay by chromakey" << std::endl;
  if (cap.type&VID_TYPE_CLIPPING) s << "    Can clip" << std::endl;
  if (cap.type&VID_TYPE_FRAMERAM) s << "    Can use the frame buffer memory" << std::endl;
  if (cap.type&VID_TYPE_MONOCHROME) s << "    Can Monochrome only" << std::endl;
  if (cap.type&VID_TYPE_SUBCAPTURE) s << "    Can capture subareas of the image" << std::endl;
  if (cap.type&VID_TYPE_MPEG_DECODER) s << "    Can decode MPEG streams" << std::endl;
  if (cap.type&VID_TYPE_MPEG_ENCODER) s << "    Can encode MPEG streams" << std::endl;
  if (cap.type&VID_TYPE_MJPEG_DECODER) s << "    Can decode MJPEG streams" << std::endl;
  if (cap.type&VID_TYPE_MJPEG_ENCODER) s << "    Can encode MJPEG streams" << std::endl;
  s << "  }" << std::endl;	
  s << "  int channels = " << cap.channels << std::endl;
  s << "  int audios = " << cap.audios << std::endl;
  s << "  int maxwidth = " << cap.maxwidth << std::endl;
  s << "  int maxheight = " << cap.maxheight << std::endl;
  s << "  int minwidth = " << cap.minwidth << std::endl;
  s << "  int minheight = " << cap.minheight << std::endl;
  s << "}" << std::endl;
  return s;
}

std::ostream& operator<<(std::ostream&s , const video_window vidwin)
{
  s << "struct video_window" << std::endl;
  s << "{" << std::endl;
  s << "  __u32	x = " << vidwin.x << std::endl;
  s << "  __u32	y = " << vidwin.y << std::endl;
  s << "  __u32	width = " << vidwin.width << std::endl;
  s << "  __u32	height = " << vidwin.height << std::endl;
  s << "}" << std::endl;
  return s;
}

std::ostream& operator<<(std::ostream&s , const video_mbuf mbuf)
{
  s << "struct video_mbuf" << std::endl;
  s << "{" << std::endl;
  s << "  int size = " << mbuf.size << std::endl;
  s << "  int frames = " << mbuf.frames << std::endl;
  for (int i=0;i<mbuf.frames;i++)
    s << "  int offsets["<<i<<"] = " << mbuf.offsets[i]<< std::endl;
  s << "}" << std::endl;
  return s;
}

std::ostream& operator<<(std::ostream&s , const video_channel channel)
{
  s << "struct video_channel" << std::endl;
  s << "{" << std::endl;
  s << "  int channel = " << channel.channel << std::endl;
  s << "  char name[32] = " << channel.name << std::endl;
  s << "  int tuners = " << channel.tuners << std::endl;
  s << "  __u32  flags = " << channel.flags << " = " << std::endl;
  s << "  {" << std::endl;
  if (channel.flags&VIDEO_VC_TUNER) s << "    Channel has a tuner" << std::endl;
  if (channel.flags&VIDEO_VC_AUDIO) s << "    Channel has audio" << std::endl;
  s << "  }" << std::endl;
  s << "  __u16  type = " << channel.type << " = ";
  if (channel.type&VIDEO_TYPE_TV) s << "TV" << std::endl;
  if (channel.type&VIDEO_TYPE_CAMERA) s << "CAMERA" << std::endl;
  s << "  __u16  norm = " << channel.norm << " = ";
  switch (channel.norm)
    {
    case(VIDEO_MODE_PAL): s << "PAL" << std::endl; break;
    case(VIDEO_MODE_NTSC): s << "NTSC" << std::endl; break;
    case(VIDEO_MODE_SECAM): s << "SECAM" << std::endl; break;
    case(VIDEO_MODE_AUTO): s << "AUTO" << std::endl; break;
    default: s << "?" << std::endl;
    }
  return s;
}

std::ostream& operator<<(std::ostream&s , const video_picture p)
{
  s << "struct video_picture" << std::endl;
  s << "{" << std::endl;
  s << "brightness= " << p.brightness << std::endl;
  s << "hue= " << p.hue << std::endl;
  s << "colour= " << p.colour << std::endl;
  s << "contrast= " << p.contrast << std::endl;
  s << "whiteness= " << p.whiteness << std::endl;
  s << "depth= " << p.depth << std::endl;
  s << "palette= " << p.palette << "(";
  // todo
  s << ")" << std::endl;
  return s;
}

