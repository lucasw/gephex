#include "texmodule.h"
#include "gfxutil.h"
#include <d3d8.h>
#include <d3dx8.h>


typedef struct _MyInstance {

	int dummy; // replace this with your favourite vars
	LPDIRECT3DDEVICE8 device;
	LPDIRECT3DTEXTURE8 tex;
	StringType		oldFileName;	
} MyInstance, *MyInstancePtr;

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
	
	my->oldFileName.text = (char*)malloc(1);
	strcpy(my->oldFileName.text,"");
	
	// Add your initialization here
	if(FAILED(WindowHandler::create(640,480,false)))
		printf("Couldn't initialize windowhandler\n");

	my->device = WindowHandler::getDirectXDevice();
	
	if(NULL==my->device)
		printf("Couldn't obtain valid directx device\n");

	return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

bool loadPic(InstancePtr inst, StringType* filename)
{
	if(inst->my->tex)
		inst->my->tex->Release();
	
	if(FAILED(D3DXCreateTextureFromFile(inst->my->device, filename->text, 
		&inst->my->tex)))
	{
		printf("Creation of Texture failed\n");
		return false;
	}

	LPDIRECT3DSURFACE8 surf;
	inst->my->tex->GetSurfaceLevel(0, &surf);

	D3DSURFACE_DESC desc;
	surf->GetDesc(&desc);

	int width = desc.Width;
	int height = desc.Height;
	int out_width = 0;
	int out_height = 0;

	D3DLOCKED_RECT d3dlr;
	surf->LockRect(&d3dlr, NULL, NULL);
	
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

		//TODO: copy pixels to framebuffer, or use different framebuffertype
	

	surf->UnlockRect();

	surf->Release();

	return true;
}

void update(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	MyInstancePtr my = inst->my;
	
	// Add your effect here!
	if (strcmp(my->oldFileName.text,inst->in_file->text) != 0)
    {
		if(!loadPic(inst, inst->in_file))
		{
			printf("Fehler beim Bildchen laden...\n");	
		}
		
		string_assign(&my->oldFileName,inst->in_file);
    }
	
	{
		int xs = inst->in_x_size->number;
		int ys = inst->in_y_size->number;
		
		if (xs != inst->out_r->xsize || ys != inst->out_r->ysize)
		{
			if (xs == 0 || ys == 0)
				loadPic(inst, inst->in_file);
			else
			{
				FrameBufferAttributes attribs;
				attribs.xsize = inst->in_x_size->number;
				attribs.ysize = inst->in_y_size->number;
				
				framebuffer_changeAttributes(inst->out_r, &attribs);
			}
		}
	}
}

