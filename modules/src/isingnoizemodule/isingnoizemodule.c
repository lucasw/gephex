#include "isingnoizemodule.h"

#include <string.h>
#include <math.h>

static logT s_log;

struct IsingField {
  char* s;
  int xsize;
  int ysize;
};

static void init_field(struct IsingField* f, int xsize, int ysize);
static void destroy_field(struct IsingField* f);
static void do_step(struct IsingField* f, uint_32 bf[3]);
static void copy_field(const struct IsingField* f, uint_32* framebuffer);

#define MY_RAND_MAX UINT32_MAX

static uint_32 x_n = 1;

/**
 * Got the parameters for this LCG from:
 * http://crypto.mat.sbg.ac.at/results/karl/server/node4.html
 *
 * Original results from:
 *  D.E. Knuth.
 *  The Art of Computer Programming, volume 2: Seminumerical Algorithms.
 *  Addison-Wesley, Reading, MA, 2nd edition, 1981.
 */
__inline static uint_32 my_rand()
{
  x_n *= 3039177861;

  return x_n;
}

typedef struct _MyInstance {

  struct IsingField f;

  int old_xsize;
  int old_ysize;

  double old_temp;
  double old_b_gr;
  double old_s_gr;

  uint_32 bf[3];

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

static void set_bf(uint_32 bf[3], double t, double b, double s)
{
  /*  {
    char buffer[128];

    snprintf(buffer, sizeof(buffer), "Changing bf: (t,b,s)=(%f,%f,%f)\n",
	     t, b, s);

    s_log(2, buffer);
    }*/

  bf[0] = (uint_32) (0.5 * MY_RAND_MAX);

  if (t > 0)
    {
      bf[1] = (uint_32) (exp(-b/t)*MY_RAND_MAX);
      bf[2] = (uint_32) (exp(-s/t)*MY_RAND_MAX);
    }
  else
    {
      bf[1] = bf[2] = 0;
    }

}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
  
  my->old_xsize = 0;
  my->old_ysize = 0;
  my->old_temp  = 0;
  my->old_b_gr  = 0;
  my->old_s_gr  = 0;
  set_bf(my->bf, my->old_temp, my->old_b_gr, my->old_s_gr);

  init_field(&my->f, my->old_xsize, my->old_ysize);
  return my;
}

void destruct(MyInstance* my)
{
  destroy_field(&my->f);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  int xsize = trim_int(inst->in_outx->number, 0, 1024);
  int ysize = trim_int(inst->in_outy->number, 0, 1024);
  double temp = inst->in_temp->number;
  double b_gr = inst->in_border_growth->number;
  double s_gr = inst->in_spont_growth->number;

  if (xsize != my->old_xsize || ysize != my->old_ysize)
    {
      destroy_field(&my->f);
      init_field(&my->f, xsize, ysize);
      my->old_xsize = xsize;
      my->old_ysize = ysize;

      s_log(2, "Changing resolution");
    }

  if (temp != my->old_temp ||
      b_gr != my->old_b_gr ||
      s_gr != my->old_s_gr)
    {
      set_bf(my->bf, temp, b_gr, s_gr);
      
      my->old_temp = temp;
      my->old_b_gr = b_gr;
      my->old_s_gr = s_gr;
    }

  {
    FrameBufferAttributes attr;
    attr.xsize = xsize;
    attr.ysize = ysize;
    framebuffer_changeAttributes(inst->out_r, &attr);
  }


  do_step(&my->f, my->bf);

  copy_field(&my->f, inst->out_r->framebuffer);
}

/****************************************************************************/

static void init_field(struct IsingField* f, int xsize, int ysize)
{
  int x, y;
  f->s = (char*) malloc(xsize*ysize);

  f->xsize = xsize;
  f->ysize = ysize;

  //  memset(

  for (y = 1; y < ysize-1; ++y)
    {
      int y_base = y*xsize;
      for (x = 1; x < xsize-1; ++x) 
	{
	  f->s[x + y_base] = (my_rand() < MY_RAND_MAX/2) ? -1 : 1;
	}
      f->s[y_base] = f->s[xsize-1 + y_base] = 1;
    }

  // set first and last line to black
  memset(f->s, 1, xsize);
  memset(f->s + (ysize-1)*xsize, 1, xsize);
}

static void destroy_field(struct IsingField* f)
{
  if (f->s != 0)
    {
      free(f->s);
      f->s = 0;
      // plain paranoia...
      f->xsize = 0;
      f->ysize = 0;
    }
}

static void do_step(struct IsingField* f, uint_32 bf[3])
{
  int x, y;
  int xsize = f->xsize;
  int ysize = f->ysize;

  // start on second pixel of the second line (f->s[1][1]):
  char* current = f->s + xsize + 1;

  for (y = ysize-2; y > 0; --y)
    {
      for (x = xsize-2; x > 0; --x)
	{
	  int sum =
	    current[-xsize] + current[xsize] +
	    current[-1] + current[1];
	  
	  int e = *current * sum;

	  if (e < 0 || my_rand() < bf[e>>1])
	    {
	      *current *= -1;
	    }

	  ++current;
	}
      // skip last pixel of this line and first pixel of next line:
      current += 2;
    }
}

static void copy_field(const struct IsingField* f, uint_32* framebuffer)
{
  int i;
  char* s = f->s;
  uint_32* fr = framebuffer;

  for (i = (f->xsize)*(f->ysize)-1; i >= 0; --i)
    {
      *(fr++) = *(s++);	  
    }
}
