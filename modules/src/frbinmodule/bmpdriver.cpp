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

#include "bmpdriver.h"

#include <string>
#include <stdexcept>
#include <memory>
#include <cstdlib>
#include <cstdio>

//----------------------------------------------------------------------


#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#define snprintf _snprintf
#endif

#include "libscale.h"

/*-------------structs needed for loading bitmaps-----------------------*/

typedef struct bitmapFileHeader_{
  int_16  bfType;		//0x4D42 for .bmp
  uint_32 bfSize;		//size of bmp in bytes
  int_16  bfReserved1;
  int_16  bfReserved2;
  uint_32 bfOffBits;    //Offset in *bytes* (not bits) from fileheader to bmp-bits (includes palette)
} BitmapFileHeader;

typedef struct bitmapInfoHeader_
{
  uint_32 biSize;
  int_32 biWidth;	  //width of bmp in pixels
  int_32 biHeight;	  //height
  int_16 biPlanes;	  //number of colorplanes
  int_16 biBitCount;	  //bits per pixel
  uint_32 biCompression;  //compression-type
  uint_32 biSizeImage;	  //size of img in bytes
  int_32 biXPelsPerMeter;
  int_32 biYPelsPerMeter;
  uint_32 biClrUsed;	  //number of colors used by bmp
  uint_32 biClrImportant; //number of important colors
} BitmapInfoHeader;

//used for loading 8bit palletized fuckers
typedef struct rgbQuad_{
  uint_8 b;
  uint_8 g;
  uint_8 r;
  uint_8 unused;
} RGBQuad, *RGBQuadPtr;

typedef struct bitmapFile_{
  BitmapFileHeader fileHeader;
  BitmapInfoHeader infoHeader;
  void *data;
} BitmapFile, *BitmapFilePtr;


/*-------------structs needed for loading bitmaps end-------------------*/

/** 
 * Converts a bitmap from 8, 16, 24 or 32 bit to 32 bit format.
 * newData must be allocated an be >= than width*height*4.
 */
static int convert32(uint_8* newData,
	      const uint_8* data, int_32 width, int_32 height,
	      int_16 bpp, RGBQuadPtr pal)
{
  //note: the lines are 4byte-aligned, so
  //if width is not divisible by 4 we have to do something...
  int padding = (width*(bpp >> 3)) & 0x03;
  int x,y;

  padding = (padding == 0) ? 0 : 4 - padding;
	
  if (!(bpp == 8 || bpp == 16 || bpp == 24 || bpp == 32) )
    {
      return 0;
    }
	
  //	newData = (unsigned char*) malloc( size );
	
  switch (bpp)
    {
    case 8:
      {
		  for (y = 0; y < height; ++y)
		  {
		    for (x = 0; x < width; ++x)
			{
			  RGBQuadPtr quad = pal + *data;
			  
			  *(newData+0) = quad->b;
			  *(newData+1) = quad->g;
			  *(newData+2) = quad->r;
			  *(newData+3) = 0;//pal[*data]->unused;
			  ++data;
			  newData+= 4;
			}
			data += padding;
		  }
	  }
      break;
    case 16:		
      {
		for (y = 0; y < height; ++y)
		  {
		    for (x = 0; x < width; ++x)
			{
			  int_16 t = *(uint_16*) data;
			  *(newData+0) = (t & 63) << 3;
			  *(newData+1) = ((t >> 5) & 127) << 2;
			  *(newData+2) = ((t >> 11) & 63) << 3;
			  *(newData+3) = 0;
				
			  newData += 4;
			  data += 2;
			}
			data += padding;
		  }
	  }
      break;
    case 24:
      {		  	  		  
		  for (y = 0; y < height; ++y)
		  {
		    for (x = 0; x < width; ++x)
			{
			  *(newData+0) = *(data+0);
			  *(newData+1) = *(data+1);
	          *(newData+2) = *(data+2);
	          *(newData+3) = 0;
				
	          newData += 4;
	          data += 3;
			}
			data += padding;
		  }
	  }
      break;
    case 32:
      {
	const unsigned char* end = data + height * width * 4;
	while ( data != end )
	  {
	    *(newData+0) = *(data+0);
	    *(newData+1) = *(data+1);
	    *(newData+2) = *(data+2);
	    *(newData+3) = *(data+3);

	    newData += 4;
	    data += 4;
	  }
      } break;	
    }
	
  return 1;
}

/**
 * flips the image vertically
 */
static void flip(uint_32* data, int_32 width, int_32 height)
{
	int bps = width*4;
	uint_32* buffer = new uint_32[width];
	int y;
	for (y = height/2; y >= 0; --y)
	{
		memcpy(buffer, data + y*width, bps);
		memcpy(data +y*width, data +(height-y-1)*width, bps);
		memcpy(data + (height-y-1)*width, buffer, bps);
	}
	delete[] buffer;
}

// assumes that data is stored in little endian format
static void read16bit(int_16* dst, FILE* file)
{
  char c;

  fread(&c, 1, 1, file);
  *dst = c;

  fread(&c, 1, 1, file);
  *dst |= (c << 8);
}

// assumes that data is stored in little endian format
static void read32bit(int_32* dst, FILE* file)
{
  unsigned char c;

  fread(&c, 1, 1, file);
  *dst = c;

  fread(&c, 1, 1, file);
  *dst |= (c << 8);

  fread(&c, 1, 1, file);
  *dst |= (c << 16);

  fread(&c, 1, 1, file);
  *dst |= (c << 24);
}

// assumes that data is stored in little endian format
static void read32bit_u(uint_32* dst, FILE* file)
{
  unsigned char c;

  fread(&c, 1, 1, file);
  *dst = c;

  fread(&c, 1, 1, file);
  *dst |= (c << 8);

  fread(&c, 1, 1, file);
  *dst |= (c << 16);

  fread(&c, 1, 1, file);
  *dst |= (c << 24);
}


//----------------------------------------------------------------------

class BMPDriverImpl
{
public:
  BMPDriverImpl()    
	  : m_data(0), m_width(0), m_height(0)
  {

  }

  ~BMPDriverImpl()
  {
	  close();
  }
  
  void load(const std::string& filename, VideoInfo& info)
  {
	  FILE* file=0;
	  BitmapFile bitmap;
	  RGBQuad palette[256];
	  int_32 size;
	  
	  //open file
	  if ( (file = fopen(filename.c_str(), "rb")) == 0 )
	  {       
		  throw std::invalid_argument("Could not open file");
	  }
	  
	  read16bit  (&bitmap.fileHeader.bfType,      file);
	  read32bit_u(&bitmap.fileHeader.bfSize,      file);
	  read16bit  (&bitmap.fileHeader.bfReserved1, file);
	  read16bit  (&bitmap.fileHeader.bfReserved2, file);
	  read32bit_u(&bitmap.fileHeader.bfOffBits,   file);
	  
	  //check if the file is a bitmap
	  if(bitmap.fileHeader.bfType != 0x4D42)
	  {
		  char buffer[128];
		  snprintf(buffer, sizeof(buffer),
			  "Wrong bfType in fileheader: '%X'",
			  bitmap.fileHeader.bfType);
		  
		  fclose(file);
		  throw std::runtime_error(buffer);
	  }
	  
	  //it is, read infosection
	  read32bit_u(&bitmap.infoHeader.biSize,          file);
	  read32bit  (&bitmap.infoHeader.biWidth,         file);
	  read32bit  (&bitmap.infoHeader.biHeight,        file);
	  read16bit  (&bitmap.infoHeader.biPlanes,        file);
	  read16bit  (&bitmap.infoHeader.biBitCount,      file);
	  read32bit_u(&bitmap.infoHeader.biCompression,   file);
	  read32bit_u(&bitmap.infoHeader.biSizeImage,     file);
	  read32bit  (&bitmap.infoHeader.biXPelsPerMeter, file);
	  read32bit  (&bitmap.infoHeader.biYPelsPerMeter, file);
	  read32bit_u(&bitmap.infoHeader.biClrUsed,       file);
	  read32bit_u(&bitmap.infoHeader.biClrImportant,  file);
	  
	  
      // biSizeImage seems to be 0 in some bmps
      //	  size = bitmap.infoHeader.biSizeImage;

	  //note: the lines are 4byte-aligned, so
	  //if width is not divisible by 4 we have to do something...
	  int padding = (bitmap.infoHeader.biWidth*(bitmap.infoHeader.biBitCount >> 3)) & 0x03;	  	  
	  padding = (padding == 0) ? 0 : 4 - padding;

      size = (bitmap.infoHeader.biWidth*bitmap.infoHeader.biBitCount/8
		       +padding)* bitmap.infoHeader.biHeight;	  
	  	  

	  if (size + bitmap.fileHeader.bfOffBits > bitmap.fileHeader.bfSize)
		  {
			fclose(file);
			throw std::runtime_error("Bitmap header not ok");
		  }

	  if(bitmap.infoHeader.biBitCount == 8)
	  {
		  //read Palette Info
		  int colors_used = (bitmap.fileHeader.bfOffBits - 14 - bitmap.infoHeader.biSize) / sizeof(RGBQuad);
		  if (colors_used < 0 || colors_used > 256)
		  {
			  fclose(file);
			  throw std::runtime_error("Could not calculate palette size");
		  }
		  int colors_read = fread(palette, sizeof(RGBQuad), colors_used, file);
		  
		  if(ferror(file))
		  {
			  fclose(file);
			  throw std::runtime_error("Read error");
		  }
		  
		  
		  if (colors_read != colors_used)
		  {
			  fclose(file);
			  throw std::runtime_error("Could not read the whole palette!");
		  }
	  }

	  if(!(bitmap.infoHeader.biBitCount==8 || bitmap.infoHeader.biBitCount==16 || 
		  bitmap.infoHeader.biBitCount==24 || bitmap.infoHeader.biBitCount==32))
	  {
		  fclose(file);
		  throw std::runtime_error("Unsupported biBitCount");
	  }

	  
	  m_height = bitmap.infoHeader.biHeight;
	  m_width  = bitmap.infoHeader.biWidth;	  
	  
	  info.height = m_height;
	  info.width  = m_width;
	  info.num_frames = 1;
	  
	  /*int result = fseek(file, bitmap.fileHeader.bfOffBits, 0);
	  if (result)
	  {
		  throw std::runtime_error("Could not seek to bitmap data");
	  }*/
	  
	  bitmap.data = malloc(size);

	  if (bitmap.data == 0)
	  {
		  fclose(file);
		  throw std::runtime_error("Could not allocate memory");
	  }
	  
	  int bytes_read = fread(bitmap.data, 1, size, file);

	  if (bytes_read < size)
	  {
		  free(bitmap.data);
		  fclose(file);
		  throw std::runtime_error("Error when reading bitmap data");
	  }
	  
	  fclose(file);
	  
	  m_data = new uint_32[m_height*m_width];
	  
	  int result = convert32((uint_8*) m_data,(uint_8*)bitmap.data, m_width, m_height,
		  bitmap.infoHeader.biBitCount, palette);
	  
	  free(bitmap.data);
	  
	  if (result == 0)
	  { 
		  char buffer[128];
		  snprintf(buffer, sizeof(buffer),
			  "Unsupported BitsPerPixel value: '%d'",
			  bitmap.infoHeader.biBitCount);
		  
		  throw std::runtime_error(buffer);		  
	  }
	  
	  flip(m_data, m_width, m_height);

  }

  void close()
  {
	  if (m_data != 0)
	  {
	    delete[] m_data;
	    m_data = 0;
	  }
  }

  void grab_frame(uint_32* frb, int frame, int width, int height)
  {	  	  
	if (m_data == 0)
		throw std::runtime_error("No bmp loaded");

	if (frame != 0)
		throw std::range_error("No such frame in bmp (only 0 is valid)");

        ls_scale32(frb, width, height, m_data, m_width, m_height);
  }

  bool is_open() const
  {
	  return m_data != 0;
  }

private:
  uint_32* m_data;
  int_32 m_width;
  int_32 m_height;
  
};

//----------------------------------------------------------------------

BMPDriver::BMPDriver()
	: m_impl(new BMPDriverImpl())
{
}

BMPDriver::~BMPDriver()
{
}

std::list<std::string> BMPDriver::supported_extensions()
{
	std::list<std::string> el;
	el.push_back("bmp");	

	return el;
}

void BMPDriver::load_file(const std::string& file_name, VideoInfo& info)
{
  if (m_impl->is_open())
    throw std::logic_error("Driver already open");
  m_impl->load(file_name, info);
}

void BMPDriver::close_file()
{
  if (m_impl->is_open())
    m_impl->close();
}

bool BMPDriver::is_open() const
{
  return m_impl->is_open();
}
  
void BMPDriver::decode_frame(unsigned int frame_number, uint_32* framebuffer,
							 int width, int height)
{
  if (!m_impl->is_open())
    throw std::logic_error("Driver not open");

  m_impl->grab_frame(framebuffer, frame_number, width, height);
}

 
