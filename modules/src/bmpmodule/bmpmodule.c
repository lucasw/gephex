#include "bmpmodule.h"

#include <stdlib.h>
#include <stdio.h>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#define snprintf _snprintf
#endif


static logT s_log;
typedef struct _MyInstance {
	
  StringType oldFileName;

  int_32 xres_orig;
  int_32 yres_orig;
	
} MyInstance, *MyInstancePtr;

/*-------------structs needed for loading bitmaps-----------------------*/

typedef struct bitmapFileHeader_{
  int_16  bfType;		//0x4D42 for .bmp
  uint_32 bfSize;		//size of bmp in bytes
  int_16  bfReserved1;
  int_16  bfReserved2;
  uint_32 bfOffBits;	        //Offset in bytes from fileheader to bmp-bits
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
int convert32(uint_8* newData,
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
void flip(uint_32* data, int_32 width, int_32 height)
{
	int bps = width*4;
	uint_32* buffer = malloc(bps);
	int y;
	for (y = height/2; y >= 0; --y)
	{
		memcpy(buffer, data + y*width, bps);
		memcpy(data +y*width, data +(height-y-1)*width, bps);
		memcpy(data + (height-y-1)*width, buffer, bps);
	}
	free(buffer);
}

/**
 * Scales a bitmap to a new resolution.
 */
int scale(uint_32* result, const uint_32* data, int_32 width,
	  int_32 height, int_32 newWidth, int_32 newHeight)
{	
  int_32 x,y;
  double alpha = (double) width / (double) newWidth;
  double beta = (double) height / (double) newHeight;
	
  if (newWidth == width && newHeight == height)
    {
      memcpy(result,data,width*height*4);
    }
  else
    {
		
      for (y = 0; y < newHeight; ++y)
	{
	  for (x = 0; x < newWidth; ++x)
	    {						
	      int_32 x_, y_;
	      uint_32 temp;
	      x_ = (int) (alpha * (double) x);
	      y_ = (int) (beta * (double) y);
				
	      temp = data[x_ + (width*y_)];
	      result[x + (newWidth*y)] = temp;
	    }
	}
    }
  return 1;
}

// assumes that data is stored in little endian format
void read16bit(int_16* dst, FILE* file)
{
  char c;

  fread(&c, 1, 1, file);
  *dst = c;

  fread(&c, 1, 1, file);
  *dst |= (c << 8);
}

// assumes that data is stored in little endian format
void read32bit(int_32* dst, FILE* file)
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
void read32bit_u(uint_32* dst, FILE* file)
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

/**
* loads a bitmap, returns 1 on success, 0 on failure
**/
int loadBmp(InstancePtr inst, StringType* filename)
{
  FILE* file=0;
  BitmapFile bitmap;
  RGBQuad palette[256];
  int_32 size;
	
  //open file
  if ( (file = fopen(filename->text, "rb")) == 0 )
    {       
      return 0;
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

      s_log(0, buffer);
      fclose(file);      
      return 0;
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


  {
    char buffer[256];
    snprintf(buffer, sizeof(buffer),
		     "BitsPerPixel: '%i', Size: %ix%i",
	         bitmap.infoHeader.biBitCount,
			 bitmap.infoHeader.biWidth,
			 bitmap.infoHeader.biHeight);

    s_log(2, buffer);
  }
	
  size = bitmap.infoHeader.biSizeImage;
	
  if(bitmap.infoHeader.biBitCount == 8)
    {
      //read Palette Info
	  int clr_used = bitmap.infoHeader.biClrUsed; 
	  int n_colors =  clr_used ? clr_used : 1 << bitmap.infoHeader.biBitCount;
      int colors_read = fread(palette,
			             sizeof(RGBQuad), n_colors, file);

	    if(ferror(file))
		{
         s_log(0, "Read error");
		}
		

	  if (colors_read != n_colors)
	  {
		  s_log(0, "Could not read the whole palette!");
	  }
    }
	
  if(bitmap.infoHeader.biBitCount==8 || bitmap.infoHeader.biBitCount==16 || 
     bitmap.infoHeader.biBitCount==24 || bitmap.infoHeader.biBitCount==32)
    {
      int_32 height = bitmap.infoHeader.biHeight;
      int_32 width  = bitmap.infoHeader.biWidth;
      int_32 out_width, out_height;
      int result;
      unsigned char* newData;

      inst->my->xres_orig = width;
      inst->my->yres_orig = height;

      result = fseek(file, -size, SEEK_END);
	  if (result)
	  {
		  s_log(0, "Could not seek to bitmap data");		  
		  return 0;
	  }
		
      bitmap.data = malloc(size);
      
	  fread(bitmap.data, size, 1, file);

      fclose(file);

      newData = (uint_8*) malloc(height*width*4);
		
      result = convert32(newData,(uint_8*)bitmap.data, width, height,
			             bitmap.infoHeader.biBitCount, palette);
			
      free(bitmap.data);
		
      if (result == 0)
	{ 
	  char buffer[128];
	  snprintf(buffer, sizeof(buffer),
		  "Unsupported BitsPerPixel value: '%d'",
		  bitmap.infoHeader.biBitCount);

	  s_log(0, buffer);	  
	  return 0;
	}

	flip((uint_32*) newData, width, height);

      if ((int) inst->in_x_size->number > 0 &&
	  (int) inst->in_y_size->number > 0)
	{
	  out_width  = trim_int(inst->in_x_size->number,0, 1024);
	  out_height = trim_int(inst->in_y_size->number,0, 1024);
	}
      else
	{
	  out_width  = width;
	  out_height = height;
	}

      {
	FrameBufferAttributes attribs;		
	attribs.xsize = out_width;
	attribs.ysize = out_height;
	framebuffer_changeAttributes(inst->out_r, &attribs);
      }
				
      result = scale(inst->out_r->framebuffer,(uint_32*)newData, width, height,
		     inst->out_r->xsize, inst->out_r->ysize);
		
      free(newData);
		
      if ( result == 0 )
	{
	  s_log(0, "Error while scaling!");
	  return 0;
	}
		
    }
  
  return 1;
}

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
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
	
  my->oldFileName.text = (char*) malloc(1);
  strcpy(my->oldFileName.text,"");
	
  my->xres_orig = 0;
  my->yres_orig = 0;
	
  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my->oldFileName.text);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
	
  // Add your effect here!
  if (strcmp(my->oldFileName.text,inst->in_file->text) != 0)
    {
      string_assign(&my->oldFileName, inst->in_file);

      if(!loadBmp(inst, inst->in_file))
	{
	  char buffer[128];
	  snprintf(buffer, sizeof(buffer), "Could not load bmp '%s'",
		   inst->in_file->text);
	  s_log(0, buffer);
	  return;
	}
    }

  {
    int xs = trim_int(inst->in_x_size->number, 0, 1024);
    int ys = trim_int(inst->in_y_size->number, 0 , 1024);

    if (xs != inst->out_r->xsize || ys != inst->out_r->ysize)
      {
	FrameBufferAttributes attribs;
	if (xs == 0 || ys == 0)
	  {
	    attribs.xsize = my->xres_orig;
	    attribs.ysize = my->yres_orig;
	  }
	else
	  {
	    attribs.xsize = trim_int(inst->in_x_size->number, 0, 1024);
	    attribs.ysize = trim_int(inst->in_y_size->number, 0, 1024);
	  }
	framebuffer_changeAttributes(inst->out_r, &attribs);
      }
  }
}
