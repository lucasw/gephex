#include "frei0rwrapper.h"

#include <sstream>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "../../../types/src/framebuffertype/framebuffertype.h"
#include "../../../types/src/numbertype/numbertype.h"
#include "../engine/dllutils.h"

#include "frei0r.xpm"

#include "c_moduletables.h"

static const int XSIZE = 320;
static const int YSIZE = 240;

struct f0r_wrapper_t
{
  f0r_wrapper_t(int plugin_type_)
    : plugin_type(plugin_type_), funs(0), f0r_instance(0) {}

  int plugin_type;
  frei0r_funs_t* funs;
  f0r_instance_t f0r_instance;

  FrameBufferType* outf;

  std::vector<void*> input_params;

  int width;
  int height;
};


void* f0rwrapper_newInstance (frei0r_funs_t* funs, int num_inputs,
                              int plugin_type)
{
  f0r_wrapper_t* wr = new f0r_wrapper_t(plugin_type);

  wr->f0r_instance = funs->construct(XSIZE, YSIZE);
  wr->funs = funs;
  wr->input_params.resize(num_inputs);
  wr->width  = XSIZE;
  wr->height = YSIZE;

  return wr;
}

void f0rwrapper_deleteInstance (void* instance)
{
  f0r_wrapper_t* wr = (f0r_wrapper_t*) instance;

  if (wr->f0r_instance)
    wr->funs->destruct(wr->f0r_instance);

  delete wr;
}

int f0rwrapper_setInput (void* instance,int index,void* typePointer)
{
  f0r_wrapper_t* wr = (f0r_wrapper_t*) instance;

  wr->input_params[index] = typePointer;

  return 1;
}

int f0rwrapper_setOutput (void* instance,int index,void* typePointer)
{
  assert(index == 0);

  f0r_wrapper_t* wr = (f0r_wrapper_t*) instance;

  FrameBufferType* fb = (FrameBufferType*) typePointer;
  
  wr->outf = fb;

  return 1;
}

void f0rwrapper_update (void* instance)
{
  f0r_wrapper_t* wr = (f0r_wrapper_t*) instance;

  FrameBufferType* in = 0;

  FrameBufferAttributes attribs;

  if (wr->plugin_type == F0R_PLUGIN_TYPE_SOURCE)
    {
      attribs.xsize = trim_int(((NumberType*) wr->input_params[0])->number,
                               8, 4096);

      attribs.ysize = trim_int(((NumberType*) wr->input_params[1])->number,
                               8, 4096);
    }
  else if (wr->plugin_type == F0R_PLUGIN_TYPE_FILTER)
    {
      in = (FrameBufferType*) wr->input_params[0];
      framebuffer_getAttributes(in, &attribs);
    }

  // TODO: check for multiples of 8
  if (attribs.xsize != wr->width || attribs.ysize != wr->height)
    {
      wr->funs->destruct(wr->f0r_instance);
      wr->f0r_instance = wr->funs->construct(attribs.xsize, attribs.ysize);

      assert(wr->f0r_instance); // TODO

      wr->width  = attribs.xsize;
      wr->height = attribs.ysize;
    }

  framebuffer_getAttributes(wr->outf, &attribs);
  attribs.xsize = wr->width;
  attribs.ysize = wr->height;  
  framebuffer_changeAttributes(wr->outf, &attribs);

  int offset = (wr->plugin_type == F0R_PLUGIN_TYPE_SOURCE) ? 2 : 1;

  for (int i = offset; i < wr->input_params.size()-1; ++i)
    {
      wr->funs->set_param_value(wr->f0r_instance, wr->input_params[i],
                                i-offset);
    }

  double time = *((double*) wr->input_params[wr->input_params.size()-1]);

  wr->funs->update(wr->f0r_instance, time,
		   in ? in->framebuffer : 0,
		   wr->outf->framebuffer);
}


void create_f0r_wrapper(CModuleFunctionTable& fTable)
{
  fTable.newInstance = (newInstanceT) f0rwrapper_newInstance;
  fTable.deleteInstance = f0rwrapper_deleteInstance;

  fTable.setOutput  = f0rwrapper_setOutput;
  fTable.setInput   = f0rwrapper_setInput;
  fTable.update     = f0rwrapper_update;
  fTable.parseInput = 0;
  fTable.strongDependenciesCalculated = 0;
  fTable.getInputAttributes           = 0;
  fTable.getPatchLayout               = 0;
  fTable.getSpec                      = 0;
  fTable.getInfo                      = 0;
}


std::string frei0r_create_spec(const f0r_plugin_info_t& f0r_info)
{
  std::ostringstream os;
  // return "mod_spec { name=[mod_gradnormmodule] number_of_inputs=[3] number_of_outputs=[1] deterministic=[true] }";

  int num_inputs = frei0r_num_inputs(f0r_info);

  os << "mod_spec { name=[mod_" << f0r_info.name
     << "] number_of_inputs=[" << num_inputs
     << "] number_of_outputs=[1] deterministic=[true] } ";

  return os.str();
}

static std::string quote_spaces(const std::string& s)
{
  std::string ret;
  ret.resize(s.length());

  for (int i = 0; i < s.length(); ++i)
    {
      char c = s[i];
      ret[i] = ((c == ' ') ? '_' : c);
    }

  return ret;
}

std::string
frei0r_create_in_param_spec(const f0r_plugin_info_t& f0r_info,
                            frei0r_funs_t* frei0r, int input,
                            std::vector<f0r_param_info_t>& param_infos)
{
//return "input_spec { type=typ_FrameBufferType id=b const=true strong_dependency=true  } ";
  int index = -1;
  std::string param_name;
  std::ostringstream os;
  os << "input_spec { type=";

  if (f0r_info.plugin_type == F0R_PLUGIN_TYPE_SOURCE)
    {
      if (input == 0 || input == 1)
        {
          param_name = (input == 0) ? "width" : "height";
          int default_value = (input == 0) ? XSIZE : YSIZE;

          os << "typ_NumberType; id=frei0r_" << param_name
             << " const=true strong_dependency=true default=" 
             << default_value << "}";
          return os.str();
        }
      index = input - 2;
    }
  else if (f0r_info.plugin_type == F0R_PLUGIN_TYPE_FILTER)
    {
      if (input == 0)
        {
          param_name = "input";

          os << "typ_FrameBufferType; id=frei0r_" << param_name
             << " const=true strong_dependency=true }";

          return os.str();
        }
      index = input - 1;
    }

  // the last input is time
  if (index == f0r_info.num_params)
    {
      param_name="time";

      os << "typ_NumberType "
         << "id=frei0r_"<< param_name << " const=true strong_dependency=true } ";

      return os.str();
    }

  assert(index >= 0 && index < f0r_info.num_params);

  f0r_param_info_t pinfo;
  frei0r->get_param_info(&pinfo, index);
  param_infos.push_back(pinfo);
  
  switch (pinfo.type)
    {
    case F0R_PARAM_BOOL:
      os << "typ_NumberType"; break;
    case F0R_PARAM_DOUBLE:
      os << "typ_NumberType"; break;
    case F0R_PARAM_COLOR:
      os << "typ_RGBType"; break;
    case F0R_PARAM_POSITION:
      os << "typ_PositionType"; break;
    default:
      throw std::runtime_error("Invalid frei0r parameter type");
    }

  param_name = quote_spaces(pinfo.name);
  os << " id=[" << param_name << "] const=true strong_dependency=true } ";
    
  return os.str();
}

std::string frei0r_create_out_spec()
{
  return "output_spec { type=typ_FrameBufferType id=frei0r_output } ";
}


std::vector<char>
frei0r_create_info(const f0r_plugin_info_t& f0r_info,
                   const std::vector<f0r_param_info_t>& param_infos)
{
  std::ostringstream os;
  int num_inputs = frei0r_num_inputs(f0r_info);
  //  static const char* INFO = "info { name=[Gradientnorm] group=[Filter] inputs=[3 Image Lightness{lower_bound=[0] step_size=[0.01] higher_bound=[1] hidden=[true] help=[lightness] } Algorithm{widget_type=[combo_box] values=[sobel,roberts-cross] hidden=[true] help=[sobel is slower and smoother, roberts-cross is quick and dirty] } ] outputs=[1 Image ] type=xpm } ";

  os << "info { name=[" << f0r_info.name
     << "] group=[Frei0r] inputs=["
     << num_inputs;

  if (f0r_info.plugin_type == F0R_PLUGIN_TYPE_SOURCE)
    {
      std::string properties = "{widget_type=number_selector "
        "lower_bound=8 step_size=8 higher_bound=4096 hidden=true}";

      os << " Width" << properties << " Height" << properties;
    }
  else if (f0r_info.plugin_type == F0R_PLUGIN_TYPE_FILTER)
    {
      os << " Image ";
    }

  for (int i = 0; i < f0r_info.num_params; ++i)
    {
      std::string properties;
      switch(param_infos[i].type)
        {
        case F0R_PARAM_BOOL:
          properties = "{widget_type=radio_button}"; break;
        case F0R_PARAM_DOUBLE:
          properties = "{widget_type=number_selector}"; break;
        default:
          properties = "";
        }
      os << quote_spaces(param_infos[i].name) << properties << " ";
    }

  std::string time_properties = "{widget_type=unboundednumber_selector}";
  os << " Time" << time_properties << " ] outputs=[1 Output] type=xpm } ";

  //  std::cout << "INFO = " << os.str() << "\n";
  char* tmpBuf;
  int reqLen = 1 + os.str().length() + getSizeOfXPM(frei0r_xpm);

  std::vector<char> buf;
  buf.resize(reqLen);

  char* offset;
  int i;
  int lines = getNumberOfStringsXPM(frei0r_xpm);
  tmpBuf = (char*) malloc(reqLen);
  if (tmpBuf == 0)
    {
      throw std::runtime_error("Could not allocate memory in getInfo\n");
    }
  memcpy(tmpBuf,os.str().c_str(),os.str().length()+1);
  offset = tmpBuf + os.str().length() + 1;
  for (i = 0; i < lines; ++i)
    {
      char* source = frei0r_xpm[i];
      memcpy(offset,source,strlen(source)+1);
      offset += strlen(source) + 1;
    }                       
  memcpy(&buf[0],tmpBuf,reqLen);
  free(tmpBuf);

  return buf;
}


void frei0r_check_plugin_info(const f0r_plugin_info_t& f0r_info)
{
  if (f0r_info.plugin_type != F0R_PLUGIN_TYPE_SOURCE &&
      f0r_info.plugin_type != F0R_PLUGIN_TYPE_FILTER)
    throw std::runtime_error("Invalid plugin_type");

  if (f0r_info.frei0r_version != 1)
    throw std::runtime_error("Invalid frei0r version");
}

int frei0r_num_inputs(const f0r_plugin_info& f0r_info)
{
  switch (f0r_info.plugin_type)
    {
    case F0R_PLUGIN_TYPE_SOURCE:
      // +2 for size, +1 for time
      return 2 + f0r_info.num_params + 1;
    case F0R_PLUGIN_TYPE_FILTER:
      // +1 for input frame, +1 for time
      return 1 + f0r_info.num_params + 1;
    default:
      throw std::runtime_error("Argl0r");
    }
}
