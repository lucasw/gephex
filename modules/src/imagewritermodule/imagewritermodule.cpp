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

#include "imagewritermodule.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "png.h"

static logT s_log;

typedef struct _MyInstance {

 int framecount; 
 std::string oldPrefix;
} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = new MyInstance;

  // Add your initialization here
  my->framecount=1;

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  delete my;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  std::string prefix(inst->in_prefix->text);

  // if prefix has changed reset framecounter
  if (prefix!=my->oldPrefix)
    {
      my->framecount=1;
      my->oldPrefix=prefix;
    }

  std::ostringstream fileNameStream;
  fileNameStream << prefix;
  fileNameStream.fill('0');
  fileNameStream.width(5);
  fileNameStream << my->framecount;
  fileNameStream << ".png";

  ++my->framecount;

  std::string fileName=fileNameStream.str();

  int width=inst->in_in->xsize;
  int height=inst->in_in->ysize;
  png_byte *row_pointers[height];

  for (int i=0;i!=height;++i)
    {
      row_pointers[height-1-i]=reinterpret_cast<png_byte*> (inst->in_in->data)+i*width*4;
    }

  //std::cout << "writing image" << fileName << std::endl;

  FILE *fp = fopen(fileName.c_str(), "wb");
  if (!fp) 
    {
      throw std::runtime_error("could not open file to write!");
      return;
    }

  png_structp png_ptr = png_create_write_struct
    (PNG_LIBPNG_VER_STRING, NULL,
     NULL, NULL);
  if (!png_ptr)
    return;
  
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_write_struct(&png_ptr,
			     (png_infopp)NULL);
    return;
    }

  if (setjmp(png_ptr->jmpbuf)) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return;
  }

  png_init_io(png_ptr, fp);

  png_set_IHDR(png_ptr, info_ptr, width, height,
	     8,PNG_COLOR_TYPE_RGB_ALPHA,PNG_INTERLACE_NONE,
	     PNG_COMPRESSION_TYPE_DEFAULT,PNG_FILTER_TYPE_DEFAULT);

  png_set_invert_alpha(png_ptr);

  png_write_info(png_ptr, info_ptr);



  png_write_image(png_ptr, row_pointers);

  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);

  fclose(fp);

}
