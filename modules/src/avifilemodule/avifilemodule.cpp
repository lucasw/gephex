#include "avifilemodule.h"

#include <string>
#include <stdexcept>
#include <sstream>
#include <memory>
#include <algorithm>
#include <iostream>

#include "avifile/avifile.h"

static logT s_log;

typedef struct _MyInstance 
{
  avm::IReadStream* videoStream;
  avm::IReadFile* videoFile;
  std::string fileName;
  int w;
  int h;
  uint_8** rows;
  int stream;
  avm::CImage* im;
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

  my->videoFile=0;
  my->videoStream=0;
  my->h=0;
  my->w=0;
  my->fileName="";
  return my;
}

void destruct(MyInstance* my)
{
  if(my->videoStream!=0) my->videoStream -> StopStreaming();
  //delete my->videoStream;;
  //delete my->videoFile;;
  delete my;
}

uint32_t bgra2rgba (uint32_t in)
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

struct bgr_t
{
  uint8_t bgr[3];
};

uint32_t bgr2rgba (bgr_t in)
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

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  std::string newFileName=std::string(inst->in_fileName->text);
  
  //check is filename changed
  if (my->fileName!=newFileName)
    { // close and open file
      my->fileName=newFileName;

      if (my->videoFile!=0)
	{
	  my->videoStream -> StopStreaming();
	  delete my->im;
	  //delete my->videoStream;
	  //delete my->videoFile;
	  my->videoStream=0;
	  my->videoFile=0;
	}

      my->videoFile = avm::CreateReadFile(my->fileName.c_str());
      try
	{

	  if(!my->videoFile->IsValid())
	    {
	      throw std::runtime_error("videoFile is not valid");	      
	    }

	  if(my->videoFile->IsRedirector())
	    {
	      throw std::runtime_error("not implemented");	      
	    }

	  if(!my->videoFile->IsOpened())
	    {
	      throw std::runtime_error("videoFile not opened");	      
	    }
	  
	  if(my->videoFile->VideoStreamCount()<1)
	    {
	      throw std::runtime_error("no VideoStream");	      
	    }

	  my->videoStream = my->videoFile->GetStream(0,avm::IStream::Video);
	  try
	    {
	      std::auto_ptr<avm::StreamInfo> sinfo(my->videoStream->GetStreamInfo());
	      my->w = sinfo->GetVideoWidth();
	      my->h = sinfo->GetVideoHeight();
	      //my->videoStream->SetDirection(true);
	      int error = my->videoStream -> StartStreaming();
	      if (error==-1)
		throw std::runtime_error("could not start streaming");	      

	      avm::BitmapInfo bi(my->w,my->h,32);
	      my->im = new avm::CImage(&bi);
	      
	    }
	  catch(std::runtime_error& e)
	    {
	      //delete my->videoStream;
	      my->videoStream=0;
	      throw;
	    }
	}
      catch(std::runtime_error& e)
	{
	  //delete my->videoFile;
	  my->videoFile=0;
	  s_log(2,e.what());
	}
    }
  else
    {
      
      if (my->videoFile!=0)
	{

	  int lastFrame=my->videoStream->GetPos()-1;
	  int pos; // frame nr to decode
	  if(!trim_bool(inst->in_seek->number))
	    {
	      pos = std::min(
			     my->videoStream->GetPos(),
			     my->videoStream->GetLength()-1
			     );
	    }
	  else
	    {
	      pos = trim_int(inst->in_position->number*
			     (my->videoStream->GetLength()-1.0),
			     0,
			     my->videoStream->GetLength()-1);
	      
	      //std::cout <<"pos: " << pos 
	      //	<<" prevkey: "<<my->videoStream->GetPrevKeyFrame(pos) 
	      //	<<" nextkey: "<<my->videoStream->GetNextKeyFrame(pos) 
	      //	<<" total: " <<my->videoStream->GetLength()
	      //	<< std::endl;
	    }

	  if(pos!=lastFrame)
	    {		  
	      // it is not the same frame as the last time 
	      // we must encode
	      if(my->videoStream->GetLength()!=0&&
		 pos!=my->videoStream->GetPos())
		{
		  // we must seek
		  int pkey = my->videoStream->GetPrevKeyFrame(pos);
		  int nkey = my->videoStream->GetPrevKeyFrame(pos);
		  if (pos==pkey)
		    {
		      // frame is a keyframe
		      my->videoStream->Seek(pkey);
		    }
		  else
		    {
		      // frame isnt a keyframe
		      if (!(my->videoStream->GetPos()<=pos&&
			    my->videoStream->GetPos()>=pkey))
			{
			  // current position is not  better than any key
			  my->videoStream->Seek(pkey);
			}
		    }
		  
		  // drop non keyframes
		  int drop = pos - my->videoStream->GetPos();
		  for (int i=0;i!=drop;++i)
		    {
		      //std::cout << "drop " << my->videoStream->GetPos() << std::endl;
		      my->videoStream->ReadFrame();
		      avm::CImage* image = my->videoStream->GetFrame();
		      image->Release();
		    }
		}
	      
	      //std::cout << "decode: " << my->videoStream->GetPos() << std::endl;	  
	      if(!my->videoStream->Eof())
		{
		  // decode frame
		  int error = my->videoStream->ReadFrame();

		  // get pointer to internal frame
		  if(error!=-1)
		    {
		      avm::CImage* image = my->videoStream->GetFrame();

		      // convert any format to bgra
		      my->im->Convert(image);
		      
		      // release pointer to internal frame
		      image->Release();
		    }
		  else
		    {
		      std::cerr << " error while read " << std::endl;
		    }
		}
	    }
	      
	  // resize output
	  FrameBufferAttributes attribs;
	  attribs.xsize=my->w;
	  attribs.ysize=my->h;
	  framebuffer_changeAttributes(inst->out_result,&attribs);
	      
	  //std::cout << " width= " << my->w <<" height= " << my->h << std::endl;
	  //std::cout << " width= " << my->im->m_iWidth <<" height= " << my->im->m_iHeight << std::endl;
	  
	  int size = my->w * my->h; 
	  uint32_t* from=reinterpret_cast<uint32_t*>(my->im->Data());
	  uint32_t* to=inst->out_result->data;
	  std::copy(from,from+size,to);

	  if(my->videoStream->GetLength()!=0)
	    {
	      inst->out_position->number=(double)my->videoStream->GetPos()/(double)my->videoStream->GetLength();
	    }
	  else
	    {
	      inst->out_position->number=1.0;
	    }
	  return;
	}
    }  
     
  // set error dummy
  FrameBufferAttributes attribs;
  attribs.xsize=1;
  attribs.ysize=1;
  framebuffer_changeAttributes(inst->out_result,&attribs);
  // set black background
  *(inst->out_result->data)=0x00000000;
  inst->out_position->number=0.0;
}
