#include "bmpmodule.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct _MyInstance {
	
  StringType oldFileName;

  int xres_orig;
  int yres_orig;
	
} MyInstance, *MyInstancePtr;

/*-------------structs needed for loading bitmaps-----------------------*/

typedef struct bitmapFileHeader_{
  short int bfType;		//0x4D42 for .bmp
  unsigned int bfSize;		//size of bmp in bytes
  short int bfReserved1;
  short int bfReserved2;
  unsigned int bfOffBits;	//Offset in bytes from fileheader to bmp-bits
}BitmapFileHeader;

typedef struct bitmapInfoHeader_
{
  unsigned int biSize;
  int biWidth;				//width of bmp in pixels
  int biHeight;				//height
  short int biPlanes;	//number of colorplanes
  short int bibitCount;	//bits per pixel
  unsigned int biCompression; //compression-type
  unsigned int biSizeImage;	//size of img in bytes
  int biXPelsPerMeter;
  int biYPelsPerMeter;
  unsigned int biClrUsed;		//number of colors used by bmp
  unsigned int biClrImportant;//number of important colors
}BitmapInfoHeader;

//used for loading 8bit palletized fuckers
typedef struct rgbQuad_{
  unsigned char b;
  unsigned char g;
  unsigned char r;
  unsigned char unused;
}RGBQuad, *RGBQuadPtr;

typedef struct bitmapFile_{
  BitmapFileHeader fileHeader;
  BitmapInfoHeader infoHeader;
  void *data;
}BitmapFile, *BitmapFilePtr;


/*-------------structs needed for loading bitmaps end-------------------*/

/** 
 * Converts a bitmap from 8, 16, 24 or 32 bit to 32 bit format.
 * newData must be allocated an be >= than width*height*4.
 */
int convert32(unsigned char* newData,
	      const unsigned char* data, int width, int height, int bpp, RGBQuadPtr pal)
{
  //int size = height * width * 4 * sizeof(unsigned char);	
	
  if (!(bpp == 8 || bpp == 16 || bpp == 24 || bpp == 32) )
    {
      return 0;
    }
	
  //	newData = (unsigned char*) malloc( size );
	
  switch (bpp)
    {
    case 8:
      {
	const unsigned char* end = data + width * height;
	while(data!= end)
	  {	
	    *(newData+0) = pal[*data].r;
	    *(newData+1) = pal[*data].g;
	    *(newData+2) = pal[*data].b;
	    *(newData+3) = 0;//pal[*data]->unused;
	    ++data;
	    newData+= 4;
	  }
      }
      break;
    case 16:		
      {
	const unsigned char* end = data + height * width * 2;
	while ( data != end )
	  {
	    short int t = *(short int*) data;
	    *(newData+0) = (t & 63) << 3;
	    *(newData+1) = ((t >> 5) & 127) << 2;
	    *(newData+2) = ((t >> 11) & 63) << 3;
	    *(newData+3) = 0;
				
	    newData += 4;
	    data += 2;
	  }
      }
      break;
    case 24:
      {
	const unsigned char* end = data + height * width * 3;
	while ( data != end )
	  {
	    *(newData+0) = *(data+0);
	    *(newData+1) = *(data+1);
	    *(newData+2) = *(data+2);
	    *(newData+3) = 0;
				
	    newData += 4;
	    data += 3;
	  }
      }
      break;
    case 32:
      {
	const unsigned char* end = data + height * width * 4;
	while ( data != end )
	  {
	    *(newData+0) = *(data+2);
	    *(newData+1) = *(data+1);
	    *(newData+2) = *(data+0);
	    *(newData+3) = *(data+3);
				
	    newData += 4;
	    data += 4;
	  }
      } break;	
    }
	
  return 1;
}

/**
 * Scales a bitmap to a new resolution.
 */
int scale(int* result, const int* data, int width,
	  int height, int newWidth, int newHeight)
{	
  int x,y;
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
	      int x_, y_, temp;
	      x_ = (int) (alpha * (double) x);
	      y_ = (int) (beta * (double) y);
				
	      temp = data[x_ + (width*y_)];
	      result[x + (newWidth*y)] = temp;
	    }
	}
    }
  return 1;
}

void readShort(short int* dst, FILE* file)
{
}

void readInt(int* dst, FILE* file)
{
}

/**
* loads a bitmap, returns 1 on success, 0 on failure
**/
int loadBmp(InstancePtr inst, StringType* filename)
{
  FILE* file=0;
  BitmapFilePtr bitmap = (BitmapFilePtr) malloc(sizeof(*bitmap));
  RGBQuadPtr palette = (RGBQuadPtr)malloc(256*sizeof(RGBQuad));
  int size;
	
  //open file
  if ( (file = fopen(filename->text, "r")) == 0 )
    {
      //fclose(file);
      free(bitmap);
      return 0;
    }
	
  fread(&bitmap->fileHeader.bfType, 2, 1, file);
  fread(&bitmap->fileHeader.bfSize, 4, 1, file);
  fread(&bitmap->fileHeader.bfReserved1, 2, 1, file);
  fread(&bitmap->fileHeader.bfReserved1, 2, 1, file);
  fread(&bitmap->fileHeader.bfOffBits, 4, 1, file);
	
  //check if the file is a bitmap
  if(bitmap->fileHeader.bfType != 0x4D42)
    {
      fclose(file);
      free(bitmap);
      return 0;
    }
	
  //it is, read infosection
  fread(&bitmap->infoHeader.biSize, 4, 1, file);
  fread(&bitmap->infoHeader.biWidth, 4, 1, file);
  fread(&bitmap->infoHeader.biHeight, 4, 1, file);
  fread(&bitmap->infoHeader.biPlanes, 2, 1, file);
  fread(&bitmap->infoHeader.bibitCount, 2, 1, file);
  fread(&bitmap->infoHeader.biCompression, 4, 1, file);
  //TODO: dummy test
  //printf("%d\n", bitmap->infoHeader.biCompression); 
  fread(&bitmap->infoHeader.biSizeImage, 4, 1, file);
  fread(&bitmap->infoHeader.biXPelsPerMeter, 4, 1, file);
  fread(&bitmap->infoHeader.biYPelsPerMeter, 4, 1, file);
  fread(&bitmap->infoHeader.biClrUsed, 4, 1, file);
  fread(&bitmap->infoHeader.biClrImportant, 4, 1, file);
	
  size = bitmap->infoHeader.biHeight*bitmap->infoHeader.biWidth
    *(bitmap->infoHeader.bibitCount/8);
	
  if(bitmap->infoHeader.bibitCount == 8)
    {
      //read Palette Info
      fread(palette, sizeof(RGBQuad), 256, file);	
    }
	
  if(bitmap->infoHeader.bibitCount==8 || bitmap->infoHeader.bibitCount==16 || 
     bitmap->infoHeader.bibitCount==24 || bitmap->infoHeader.bibitCount==32)
    {
      int height = bitmap->infoHeader.biHeight;
      int width = bitmap->infoHeader.biWidth;
      int	out_width, out_height;
      int result;
      unsigned char* newData;

      inst->my->xres_orig = width;
      inst->my->yres_orig = height;

      fseek(file, -size, SEEK_END);
		
      bitmap->data = malloc(size);
		
      fread(bitmap->data, size, 1, file);
		
      fclose(file);		

      newData = malloc(height*width*4);
		
      result = convert32(newData,bitmap->data,width,height,
			 bitmap->infoHeader.bibitCount, palette);
			
      free(bitmap->data);
		
      if (result == 0)
	{				
	  printf("nicht unterstuetzte bpps... %d\n",
		 bitmap->infoHeader.bibitCount);			
	  free(bitmap);
	  return 0;
	}

      if ((int) inst->in_x_size->number > 0 && (int) inst->in_y_size->number > 0)
	{
	  out_width = inst->in_x_size->number;
	  out_height = inst->in_y_size->number;
	}
      else
	{
	  out_width = width;
	  out_height = height;
	}

      {
	FrameBufferAttributes attribs;		
	attribs.xsize = out_width;
	attribs.ysize = out_height;
	framebuffer_changeAttributes(inst->out_r, &attribs);
      }
				
      result = scale(inst->out_r->framebuffer,(int*)newData, width, height,
		     inst->out_r->xsize, inst->out_r->ysize);
		
      free(newData);
		
      if ( result == 0 )
	{
	  printf("Fehler beim scalen!\n");				   			
	  free(bitmap);
	  return 0;
	}
		
    }
	
  free(bitmap);	
  free(palette);
  return 1;
}

int init(logT log_function)
{
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
	
  my->oldFileName.text = malloc(1);
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
      if(!loadBmp(inst, inst->in_file))
	{
	  printf("Fehler beim Bitmapladen...\n");	
	}
		
      string_assign(&my->oldFileName,inst->in_file);
    }

  {
    int xs = inst->in_x_size->number;
    int ys = inst->in_y_size->number;

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
	    attribs.xsize = inst->in_x_size->number;
	    attribs.ysize = inst->in_y_size->number;			
	  }
	framebuffer_changeAttributes(inst->out_r, &attribs);
      }
  }
}
