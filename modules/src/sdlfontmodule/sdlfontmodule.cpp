extern "C"
{
#include "sdlfontmodule.h"
#include "SDL.h"
#include "SDL_ttf.h"
}

#include <string>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0x0000ff00
#define gmask 0x00ff0000
#define bmask 0xff000000
#define amask 0x000000ff
#else
#define rmask 0x00ff0000
#define gmask 0x0000ff00
#define bmask 0x000000ff
#define amask 0xff000000
#endif

static const int DEFAULT_POINT_SIZE = 18;

using namespace std;

static logT s_log;

enum scroll_mode_t
  {
    VERTICAL=0,HORIZONTAL,SINE,STATIC
  };

typedef struct _MyInstance {

  int dummy; // replace this with your favourite vars
  int height;
  TTF_Font* font;
  SDL_Surface* scratch;
  SDL_Surface* text;
  SDL_Color lastColor;


  string* lastText;
  string* lastFont;
  int lastXSize;
  int lastYSize;
  int lastPointSize;

  int underlined;
  int bold;
  int italic;
} MyInstance, *MyInstancePtr;

//void checkDims(int w, int h, MyInstance* my, char* data);

int my_SDL_init()
{
  if((SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO) == 0)
    {
      if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
	  if(SDL_InitSubSystem(SDL_INIT_VIDEO)==-1)
	    {
	      return 0;
	    }
	}
    }
    
    return 1;
}

int init(logT log_function)
{
  s_log = log_function;

  //cout << "Initializing SDL-subsystem...." << endl;
  if(!my_SDL_init())
    {
      s_log(0,"Initializing SDL-subsystem failed...");
      return 0;
    }
  //cout << "Initializing SDL-subsystem....done" << endl;


  if ( TTF_Init() < 0 ) 
    {
      s_log(0, "Initializing TTF-subsystem failed....");
      return 0;
    }
  return 1;
}

void shutDown(void)
{
  TTF_Quit();
}

scroll_mode_t effectType(const string& which)
{
  if(which == "vertical_scroll")
    {
      return VERTICAL;
    }
  else if(which == "horizontal_scroll") 
    {
      return HORIZONTAL;
    }
  else if(which == "sine_scroll")
    {
      return SINE;
    }
  else if(which == "static")
    {
      return STATIC;
    }
  else return STATIC;
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  if (my == 0)
  {
	  s_log(0, "Could not allocate memory for MyInstance struct\n");
	  return 0;
  }
  
  my->lastText = new string("null");
  my->lastFont = new string("null");
  my->lastColor.r = my->lastColor.g = my->lastColor.b = 0;
  my->scratch = 0;
  my->font = 0;
  my->text = 0;
  my->lastXSize = my->lastYSize = 0;
  my->lastPointSize = 10;
  my->underlined = my->bold = my->italic = 0;
  return my;
}

void destruct(MyInstance* my)
{
  if(my->lastFont)
    delete my->lastFont;
  if(my->lastText)
    delete my->lastText;
  if(my->scratch)
    {
      SDL_FreeSurface(my->scratch);
      my->scratch = 0;
    }
  
  if(my->text)
    {
      SDL_FreeSurface(my->text);
      my->text = 0;
    }

  if(my->font)
    TTF_CloseFont(my->font);
  my->font = 0;
  free(my);
}

static int file_ok(const char* file_name)
{
	if (file_name == 0)
		return 0;

	if (strlen(file_name) == 0)
		return 0;

	FILE* file = fopen(file_name, "rb");

	if (file == 0)
		return 0;

	fclose(file);
	return 1;
}

int fontChanged(MyInstance* my, const char* font, 
		int bold, int italic, int underlined,
		int psize = DEFAULT_POINT_SIZE)
{  
  if(my->font)
  {
    TTF_CloseFont(my->font);
	my->font = 0;
  }

  if (!file_ok(font))
	  return 0;

  my->font = TTF_OpenFont(font, psize);
  if ( my->font == NULL ) {
    s_log(0, "could not open font!");
    return 0;
  }

  int style = 0;
  if(bold)
    style |= TTF_STYLE_BOLD;
  if(italic)
    style |= TTF_STYLE_ITALIC;
  if(underlined)
    style |= TTF_STYLE_UNDERLINE;

  TTF_SetFontStyle(my->font, style);  

  return 1;
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int pos_x      = 0;
  int pos_y      = 0;
  int width      = inst->in_b->xsize;
  int height     = inst->in_b->ysize;

  int options    = trim_int(inst->in_options->number, 0, (1u<<31)-1);
  int bold       = options&1;
  int italic     = options&2;
  int underlined = options&4;

  int point_size    = trim_int(inst->in_point_size->number, 0, 256);
  double effectTime = trim_double(inst->in_effect_time->number, 0, 1);

  int patch = trim_int(inst->in_patch->number,0,16);
  
  //cpy input to output... only if not patching.
  if (patch == 0)
    {
      //scale outputframebuffer to inputframebuffer size
      FrameBufferAttributes attribs;
  
      attribs.xsize = width;
      attribs.ysize = height;
      framebuffer_changeAttributes(inst->out_r, &attribs);

      memcpy(inst->out_r->data, inst->in_b->data,
             attribs.xsize*attribs.ysize*4);
    }
  
  if(strlen(inst->in_text_->text) == 0)
    return;

  if(width != my->lastXSize || height != my->lastYSize )
    {
      my->lastXSize = width;
      my->lastYSize = height;
      if (my->scratch)
	  SDL_FreeSurface(my->scratch);

      my->scratch = SDL_CreateRGBSurface(SDL_SWSURFACE, 
					 width, 
					 height,
					 32,rmask, gmask, bmask, amask);      
    }
  
    
  bool renderFont  = false;
  if (my->font == 0 || *my->lastFont != inst->in_font->text || bold != my->bold ||
	  italic != my->italic || underlined != my->underlined ||
	  point_size != my->lastPointSize)
  {
	  if (fontChanged(my, inst->in_font->text, 
	                  bold, italic, underlined, point_size) == 0)
	  {
		  return;
	  }
	  
	  *my->lastFont = inst->in_font->text;
	  my->lastPointSize = point_size;
	  my->bold = bold;
	  my->italic = italic;
	  my->underlined = underlined;
	  renderFont = true;
  }
    
  string text = string(inst->in_text_->text);

  SDL_Color col;
  col.r = (Uint8) (inst->in_color->r * 255.f);
  col.g = (Uint8) (inst->in_color->g * 255.f);
  col.b = (Uint8) (inst->in_color->b * 255.f);

  //  SDL_Surface* text = 0;
  if(text !=  *my->lastText || col.r != my->lastColor.r 
     || col.g != my->lastColor.g || col.b != my->lastColor.b || renderFont)
    {
      
      /*cout << "textchanged..was: "<<*my->lastText<<" is: "
	<< inst->in_text_->text <<endl;*/

      *my->lastText = text;
      my->lastColor = col;

      if(!my->scratch)
	{
	  s_log(0, "ARGH!!! scratch texture in font is NULL! PAAANIC!!");
	  return;
	}
      if(my->text)
	{
	  SDL_FreeSurface(my->text);
	  my->text = 0;
	}

      my->text = 
	//	TTF_RenderText_Solid(my->font, inst->in_text_->text, col);  
	TTF_RenderText_Blended(my->font, inst->in_text_->text, col);        
      
    }

  if(!my->text)
	{
	  s_log(0,"Call to TTF_RenderText_Solid returned NULL-surface, returning...");
	  return;
	}
  
  //switch on effect type  
  switch(effectType(inst->in_scroll->text))
    {
      // no scrolling, get position of text from position field
    case STATIC:
      pos_x = (int)((width-my->text->w) *inst->in_pos->x);
      pos_y = (int)((height-my->text->h) *inst->in_pos->y);
      break;
      // scroll horizontal, advance font horizontal according to time
    case HORIZONTAL:
      pos_y = (int)((height-my->text->h )*inst->in_pos->y);
      pos_x = (int)((1.0 - effectTime)*(width+my->text->w) - my->text->w);
      break;
    }

  //  cout << "pos_x: " <<pos_x<<", pos_y: "<<pos_y<<endl;
  // determine destination rectangle
  SDL_Rect rect;
  rect.x = pos_x;
  rect.y = pos_y;
  rect.w = my->text->w;
  rect.h = my->text->h;

  // this is a bit of a hack.
  void* pixels = my->scratch->pixels;  
  my->scratch->pixels = (void*)inst->out_r->data;

  SDL_BlitSurface(my->text, 0, my->scratch, &rect);

  my->scratch->pixels = pixels;
  
  //  SDL_FreeSurface(text);  
}

//---------------------------------------------------------------------

void patchLayout(Instance* inst, int out2in[])
{
  if (trim_int(inst->in_patch->number,0,16) == 1)
    out2in[out_r] = in_b;
}
