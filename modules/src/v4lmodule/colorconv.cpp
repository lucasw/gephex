#include "colorconv.h"

// debug
#include <cassert>
#include <algorithm>

int rv_tab[256];
int gv_tab[256];
int gu_tab[256];
int bu_tab[256];

void init_tabs()
{
  for (int i=0;i!=256;++i)
    {
      rv_tab[i]=static_cast<int>( 1.4075 * (i - 128));
      gv_tab[i]=static_cast<int>(-0.7169 * (i - 128));
      gu_tab[i]=static_cast<int>(-0.3455 * (i - 128));
      bu_tab[i]=static_cast<int>( 1.7790 * (i - 128));
    }
}

uint32_t rgba2bgra (uint32_t& in)
{
  uint32_t out;
  uint8_t* in_b=reinterpret_cast<uint8_t*>(&in);
  uint8_t* out_b=reinterpret_cast<uint8_t*>(&out);
  out_b[0]=in_b[2];
  out_b[1]=in_b[1];
  out_b[2]=in_b[0];
  out_b[3]=0;
  return out;
}


void rgb32_2_bgra(uint8_t* to, uint8_t* from, unsigned int xSize, unsigned int ySize)
{
  uint32_t* to_ = reinterpret_cast<uint32_t*>( to );
  uint32_t* from_ = reinterpret_cast<uint32_t*>( from );
  std::transform(from_,from_+xSize*ySize,to_,rgba2bgra);
}

void yuv411p_2_bgra(uint8_t* to, uint8_t* from, unsigned int xSize, unsigned int ySize)
{
  // the u and v planes are just 1/4 as big as the y plane
  assert(xSize%2==0);
  assert(ySize%2==0);

  //bgra is hardcoded coded here
  const int offset_blue = 0;
  const int offset_green = 1;
  const int offset_red = 2;
  const int offset_alpha = 3;

  const uint8_t* y= from;// pixel 0 upper left
  const uint8_t* u = y + (xSize*ySize); // the u plane follows the y block
  const uint8_t* v = u + (xSize*ySize/4);  // the v plane follows the u block

  uint8_t* t =to;

  int line=ySize/2;
  while(line!=0)
    {
      --line;
      int pixel=xSize/2;
      while(pixel!=0)
	{	
	  --pixel;
	  
	  int rv = rv_tab[*v];
	  int gv = gv_tab[*v];
	  int gu = gu_tab[*u];
	  int bu = bu_tab[*u];
	  
	  *(t+0+offset_red)  =std::max(0,std::min(255,(*(y+0))+rv));
	  *(t+0+offset_green)=std::max(0,std::min(255,(*(y+0))+gv+gu));
	  *(t+0+offset_blue) =std::max(0,std::min(255,(*(y+0))+bu));
	  *(t+0+offset_alpha)=0;

	  *(t+(4+offset_red))  =std::max(0,std::min(255,(*(y+1))+rv));
	  *(t+(4+offset_green))=std::max(0,std::min(255,(*(y+1))+gv+gu));
	  *(t+(4+offset_blue)) =std::max(0,std::min(255,(*(y+1))+bu));
	  *(t+(4+offset_alpha))=0;

	  *(t+(xSize*4+offset_red))=std::max(0,std::min(255,*(y+xSize)+rv));
	  *(t+(xSize*4+offset_green))=std::max(0,std::min(255,*(y+xSize)+gv+gu));
	  *(t+(xSize*4+offset_blue)) =std::max(0,std::min(255,*(y+xSize)+bu));
	  *(t+(xSize*4+offset_alpha))=0;


	  *(t+((xSize+1)*4+offset_red))  =std::max(0,std::min(255,*(y+(xSize+1))+rv));
	  *(t+((xSize+1)*4+offset_green))=std::max(0,std::min(255,*(y+(xSize+1))+gv+gu));
	  *(t+((xSize+1)*4+offset_blue)) =std::max(0,std::min(255,*(y+(xSize+1))+bu));
	  *(t+((xSize+1)*4+offset_alpha))=0;
	  
	  // increment pointers
	  ++u;
	  ++v;

	  y+=2;
	  t+=8;
	}
      
      // increment pointers
      y+=xSize;
      t+=xSize*4;
      
    }
}

