/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
  
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

#include "y4minmodule.h"

#include <string.h>
#include <assert.h>

#if defined(_MSC_VER)
#include <io.h>
#define O_RDONLY _O_RDONLY
#define O_NDELAY 0
#else
#include <unistd.h>
#include <sys/select.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libcolorconv.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

//---------------------------------------------------------------------

static logT s_log;

static const int INVALID_HANDLE = -1;

static int my_max(int a, int b)
{
  return (a < b) ? b : a;
}

//---------------------------------------------------------------------

typedef enum  {NONE, YUV420P, BGRA8888} color_model_t;

struct stream_info
{
  color_model_t color_model;
  int width;
  int height;
  double fps;
  char c;
  double A;
};

static void info_print(const struct stream_info* info)
{
  printf("%s WXH = %ix%i, fps = %f, I = %c, A = %f\n",
         info->color_model == YUV420P ? "YUV420P" : "BGRA8888",
         info->width, info->height, info->fps, info->c, info->A);
}

struct scan_status
{
  int stream_header_read;
  int frame_header_read;
};

struct res_queue
{
  uint8_t* buf;
  int buf_size;
  int buf_len;  
};


static int queue_init(struct res_queue* q, int size_hint)
{
  q->buf_size = (size_hint > 0) ? size_hint : 1024;
  q->buf_len  = 0;
  q->buf      = (uint8_t*) malloc(q->buf_size);

  if (q->buf == 0)
    return 0;
  else
    return 1;
}

static void queue_flush(struct res_queue* q)
{
  q->buf_len = 0;
}

static void queue_free(struct res_queue* q)
{
  if (q->buf)
    {
      free(q->buf);
      q->buf = 0;
    }

  q->buf_size = q->buf_len = 0;
}

static int queue_reserve(struct res_queue* q, int len)
{
  int new_len = q->buf_len + len;
  if (new_len > q->buf_size)
    {
      int new_size = my_max(new_len, (int) (q->buf_size * 1.2));

      uint8_t* new_buf = (uint8_t*) malloc(new_size);
      if (new_buf == 0)
        return 0;

      memcpy(new_buf, q->buf, q->buf_len);
      free(q->buf);
      q->buf      = new_buf;
      q->buf_size = new_size;
    }

  assert(new_len <= q->buf_size);

  return 1;
}

static int queue_put(struct res_queue* q, const uint8_t* data, int len)
{
  if (queue_reserve(q, len) == 0)
    return 0;

  memcpy(q->buf, data, len);

  q->buf_len += len;
  return 1;
}

static int queue_get(struct res_queue* q, uint8_t* dst, int len)
{
  if (q->buf_len < len || len <= 0)
    return 0;

  if (dst)
    memcpy(dst, q->buf, len);

  q->buf_len -= len;

  if (q->buf_len > 0)
    memmove(q->buf, q->buf + len, q->buf_len);

  assert(q->buf_len >= 0);

  return 1;
}

typedef struct _MyInstance 
{ 
  StringType filename;
  int        file_handle;

  struct stream_info info;

  struct res_queue queue;
  
  struct scan_status status;

  FrameBufferType scaled_fb;
} MyInstance, *MyInstancePtr;

static int get_frame_size(int w, int h, color_model_t cm)
{
  switch(cm)
    {
    case YUV420P:
      return (w*h*6)/4;
    case BGRA8888:
      return w*h*4;
    default:
      assert(!"invalid color model in get_frame_size()");
      return 0;
    }
}

//---------------------------------------------------------------------

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

//---------------------------------------------------------------------


static int open_file(const char* fname)
{
  int handle;

  handle = open(fname, O_RDONLY | O_NDELAY);
  return handle;
}

static void close_file(int file_handle)
{
  close(file_handle);
}

MyInstance* construct()
{
  MyInstance* my = (MyInstance*) malloc(sizeof(MyInstance));

  if (my == 0)
    {
      s_log(0, "Could not allocate memory for MyInstance struct\n");
      return 0;
    }

  
  string_initInstance(&my->filename);
  string_charAssign(&my->filename, "");

  my->file_handle = INVALID_HANDLE;

  queue_init(&my->queue, 320*240*2);

  my->info.width = my->info.height = 0;

  my->info.color_model = NONE;

  my->status.stream_header_read = 0;
  my->status.frame_header_read = 0;


  framebuffer_initInstance(&my->scaled_fb);

  return my;
}

void destruct(MyInstance* my)
{
  if (my->file_handle != INVALID_HANDLE)
    close_file(my->file_handle);

  string_destroyInstance(&my->filename);

  queue_free(&my->queue);

  framebuffer_destroyInstance(&my->scaled_fb);

  free(my);
}

static int scan_const_string(const uint8_t* data, int len, const char* str)
{
  int str_len = strlen(str);
  const char* data_str = (const char*) data;
  int i;

  if (len < str_len)
    return 0;

  for (i = 0; i < str_len; ++i)
    {
      if (data_str[i] != str[i])
        return 0;
    }

  return str_len;
}

static int is_numeric(char c)
{
  return (c >= '0' && c <= '9');
}

static int to_int(char c)
{
  return (int) (c - '0');
}
static int scan_uint(const uint8_t* data, int len, int* dst)
{
  const char* data_str = (const char*) data;
  int index  = 0;
  int result = 0;

  if (len < 0)
    return 0;

  while (index < len && is_numeric(data_str[index]))
    {
      result = 10*result + to_int(data_str[index]);
      ++index;
    }

  *dst = result;
  return index;
}

static int scan_char(const uint8_t* data, int len, char* c)
{
  if (len < 1)
    return 0;

  *c = ((const char*) data)[0];
  return 1;
}

static int scan_rational(const uint8_t* data, int len, int* nom, int* denom)
{
  int retval;
  const uint8_t* ptr = data;
  int bytes_left = len;

  retval = scan_uint(ptr, bytes_left, nom);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_const_string(ptr, bytes_left, ":");
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_uint(ptr, bytes_left, denom);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  return len - bytes_left;
}

static int scan_named_rational(const uint8_t* data, int len, 
                               const char* name, double* val)
{
  int retval;
  int nom, denom;
  const uint8_t* ptr = data;
  int bytes_left = len;

  retval = scan_const_string(ptr, bytes_left, name);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_rational(ptr, bytes_left, &nom, &denom);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  if (val)
    {
      if (denom == 0)
        *val = 0;
      else
        *val = nom / (double) denom;
    }

  return len - bytes_left;
}

static int scan_framerate(const uint8_t* data, int len, double* fps)
{
  return scan_named_rational(data, len, " F", fps);
}

static int scan_A(const uint8_t* data, int len, double* fps)
{
  return scan_named_rational(data, len, " A", fps);
}

static int scan_stream_header(const uint8_t* data, int len,
                              struct stream_info* info)
{
  color_model_t cm = YUV420P;
  int retval;
  int bytes_left = len;
  const uint8_t* ptr = data;

  if (len < 32)
    return 0;

  retval = scan_const_string(ptr, bytes_left, "YUV4MPEG2");
  if (retval == 0) 
    {
      retval = scan_const_string(ptr, bytes_left, "BGRA8888");
      cm     = BGRA8888;
    }
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }
  
  retval = scan_const_string(ptr, bytes_left, " W");
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_uint(ptr, bytes_left, &info->width);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_const_string(ptr, bytes_left, " H");
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_uint(ptr, bytes_left, &info->height);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_framerate(ptr, bytes_left, &info->fps);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_const_string(ptr, bytes_left, " I");
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_char(ptr, bytes_left, &info->c);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_A(ptr, bytes_left, &info->A);
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  retval = scan_const_string(ptr, bytes_left, "\n");
  if (retval == 0) return 0; else { bytes_left -= retval; ptr += retval; }

  info->color_model = cm;

  info_print(info);

  assert(len - bytes_left == ptr - data);

  return len - bytes_left;
}

static int scan_frame_header(uint8_t* data, int len)
{
  return scan_const_string(data, len, "FRAME\n");
}

static int scan_data(uint8_t* data, int len,
                     struct stream_info* info,
                     struct scan_status* status,
                     int xsize, int ysize,
                     FrameBufferType* scaled_fb,
                     FrameBufferType* out)
{
  int retval;
  int bytes_left = len;
  uint8_t* ptr   = data;
  int framesize;

  if (status->stream_header_read == 0)
    {
      // try to read the stream header
      retval = scan_stream_header(ptr, bytes_left, info);

      if (retval == 0)
        {
          s_log(0, "Could not read stream header");
          return -1;
        }
      bytes_left -= retval;
      ptr        += retval;
      status->stream_header_read = 1;
    }

  if (status->frame_header_read == 0)
    {
      retval = scan_frame_header(ptr, bytes_left);

      if (retval == 0)
        {
          s_log(0, "Could not read frame header");
          return -1;
        }
      bytes_left -= retval;
      ptr        += retval;
      status->frame_header_read = 1;
    }

  framesize = get_frame_size(info->width, info->height, info->color_model);
  if (bytes_left >= framesize)   // whole frame available
    {
      int need_scale;
      FrameBufferAttributes attribs;
      uint32_t* target = 0;

      if (xsize == 0 || ysize == 0)
        {
          xsize = info->width;
          ysize = info->height;
        }

      need_scale = (xsize != info->width || ysize != info->height);

      // resize output
      attribs.xsize = xsize;
      attribs.ysize = ysize;
      framebuffer_changeAttributes(out, &attribs);

      if (need_scale)
        {
          if (scaled_fb->framebuffer == 0)
            framebuffer_initInstance(scaled_fb);

          attribs.xsize = info->width;
          attribs.ysize = info->height;
          framebuffer_changeAttributes(scaled_fb, &attribs);
          target = scaled_fb->framebuffer;
        }
      else
        {
          target = out->framebuffer;
        }

      if (info->color_model == YUV420P)
        cvt_yuv420p_to_bgra((uint8_t*) target, ptr,
                            info->width, info->height);
      else
        memcpy(target, ptr, get_frame_size(info->width,info->height,
                                           info->color_model));

      if (need_scale)
        {
          attribs.xsize = xsize;
          attribs.ysize = ysize;

          framebuffer_convertType(out, scaled_fb, &attribs);
        }
      else
        {
          if (scaled_fb->framebuffer)
            framebuffer_destroyInstance(scaled_fb);
        }

      bytes_left -= framesize;
      ptr        += framesize;
      status->frame_header_read  = 0;
    }

  assert(ptr - data == len - bytes_left);
  return len - bytes_left;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int xsize = trim_int(inst->in_x_size->number, 0 , 1024);
  int ysize = trim_int(inst->in_y_size->number, 0 , 1024);

  const char* new_filename = inst->in_fname->text;
  const char* old_filename = my->filename.text;

  int new_data = 0;
  int read_size;
  int retval;
  int scanned_bytes;
    
  //check if file changed
  if (my->file_handle == INVALID_HANDLE ||
      strcmp(new_filename,old_filename) != 0)
    {
      if (my->file_handle != INVALID_HANDLE)
        {
          close_file(my->file_handle);
          my->file_handle = INVALID_HANDLE;
        }

      my->file_handle = open_file(new_filename);
      string_assign(&my->filename, inst->in_fname);
      my->info.width = my->info.height = 0;
      my->info.color_model             = NONE;
      my->status.stream_header_read    = 0;
      my->status.frame_header_read     = 0;
      queue_flush(&my->queue);
    }
        
  if (my->file_handle == INVALID_HANDLE)
    {
      s_log(0, "No open file to read from");
      return;
    }

#ifdef _MSC_VER
  new_data = 1;
#else
  // select to check if handle can be read
  {
    fd_set rfds;
    struct timeval tv;
    int retval;

    tv.tv_sec = tv.tv_usec = 0; // just poll

    FD_ZERO(&rfds);
    FD_SET(my->file_handle , &rfds);

    retval = select(my->file_handle + 1, &rfds, 0, 0, &tv);

    if (retval == -1)
      {
        s_log(0, "error in select");
        return;
      }

    new_data = FD_ISSET(my->file_handle, &rfds);
  }
  if (new_data == 0)
      s_log(2, "No new data");
#endif

  
  if (new_data)
    {
      // read all available data into the queue
      // has the width and height info already been read?
      if (my->info.width == 0 || my->info.height == 0 ||
          my->info.color_model == NONE)
        read_size = get_frame_size(320,240, YUV420P) + 40;
      else
        read_size = get_frame_size(my->info.width,
                                   my->info.height,
                                   my->info.color_model) + 6
          - my->queue.buf_len;

      // make sure we have enough space in the queue
      retval = queue_reserve(&my->queue, read_size);
      if (retval == 0)
        {
          s_log(0, "Could not reserve space in queue");
          return;
        }

      read_size = read(my->file_handle,
                       my->queue.buf + my->queue.buf_len,
                       read_size);
  
      if (read_size == -1) // Error
        {
          s_log(0, "Error at read");
          close_file(my->file_handle);
          my->file_handle = INVALID_HANDLE;
          return;
        }
      else if (read_size == 0) //EOF
        {
          s_log(1, "EOF at read");
          close_file(my->file_handle);
          my->file_handle = INVALID_HANDLE;
          return;
        }
      else
        {
          my->queue.buf_len += read_size;
        }
    }

  scanned_bytes = 0;
  if (my->queue.buf_len != 0)
    {
      // scan the queue
      scanned_bytes = scan_data(my->queue.buf,
                                my->queue.buf_len,
                                &my->info,
                                &my->status,
                                xsize, ysize,
                                &my->scaled_fb,
                                inst->out_result);

      if (scanned_bytes > 0)
        queue_get(&my->queue, 0, scanned_bytes);
    }
}

//---------------------------------------------------------------------
