/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

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

#include "frei0r_module_class.h"

#include "frei0r_module.h"
#include "moduleinfoutils.h"

#include "frei0r.xpm"
#include "../../../types/src/framebuffertype/framebuffertype.h"
#include "../../../types/src/numbertype/numbertype.h"
#include "../engine/dllutils.h"

#include "c_moduletables.h"

#include <sstream>
#include <cstring>
#include <iostream>


#include "renderer/typefactory.h" //TODO: not allowed
#include "interfaces/itype.h"
#include "utils/structreader.h"
#include "nameresolver.h"

#include "frei0r.h"

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

static const int XSIZE = 320;
static const int YSIZE = 240;





void create_f0r_wrapper(CModuleFunctionTable& fTable);

std::string frei0r_create_spec(const f0r_plugin_info_t&);

std::string
frei0r_create_in_param_spec(const f0r_plugin_info_t& f0r_info,
                            const frei0r_funs_t* frei0r, int input,
                            std::vector<f0r_param_info_t>& param_infos);

std::string frei0r_create_out_spec();


std::vector<char>
frei0r_create_info(const f0r_plugin_info_t& f0r_info,
                   const std::vector<f0r_param_info_t>& param_infos);

void frei0r_check_plugin_info(const f0r_plugin_info_t& f0r_info);

int frei0r_num_inputs(const f0r_plugin_info& f0r_info);


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
  f0r_wrapper_t* wr = reinterpret_cast<f0r_wrapper_t*>(instance);

  // the common attribs for all inputs and outputs
  FrameBufferAttributes attribs; 
  unsigned int offset;

  switch (wr->plugin_type)
    {
    case F0R_PLUGIN_TYPE_SOURCE:
      {
	attribs.xsize =
	  trim_int(reinterpret_cast<NumberType*>(wr->input_params[0])->number,
		   8,
		   4096);
      
	attribs.ysize =
	  trim_int(reinterpret_cast<NumberType*>(wr->input_params[1])->number,
		   8,
		   4096);
	offset=2;
	break;
      }
    case F0R_PLUGIN_TYPE_FILTER:
      {
	FrameBufferType* in1 =
	  reinterpret_cast<FrameBufferType*>(wr->input_params[0]);
	
	framebuffer_getAttributes(in1, &attribs);
	offset=1;
	break;
      }
    case F0R_PLUGIN_TYPE_MIXER2:
      {
	assert(wr->input_params.size()>2);
	FrameBufferType* in1 =
	  reinterpret_cast<FrameBufferType*>(wr->input_params[0]);
	FrameBufferAttributes in1_attribs;
	assert(in1);
	framebuffer_getAttributes(in1, &in1_attribs);
	
	FrameBufferType* in2 =
	  reinterpret_cast<FrameBufferType*>(wr->input_params[1]);
	FrameBufferAttributes in2_attribs;
	assert(in2);
	framebuffer_getAttributes(in2, &in2_attribs);
	
	attribs.xsize= std::max(in1_attribs.xsize, in2_attribs.xsize);
	attribs.ysize= std::max(in1_attribs.ysize, in2_attribs.ysize);
      
	// TODO create a copy of inputs and resize to max
	framebuffer_changeAttributes(in1, &attribs);
	framebuffer_changeAttributes(in2, &attribs);
	
	offset=2;
	break;
      }
    case F0R_PLUGIN_TYPE_MIXER3:
      {
	FrameBufferType* in1 =
	  reinterpret_cast<FrameBufferType*>(wr->input_params[0]);
	FrameBufferAttributes in1_attribs;
	framebuffer_getAttributes(in1, &in1_attribs);
	
	FrameBufferType* in2 =
	  reinterpret_cast<FrameBufferType*>(wr->input_params[1]);
	FrameBufferAttributes in2_attribs;      
	framebuffer_getAttributes(in2, &in2_attribs);
	
	FrameBufferType* in3 =
	  reinterpret_cast<FrameBufferType*>(wr->input_params[2]);
	FrameBufferAttributes in3_attribs;      
	framebuffer_getAttributes(in3, &in3_attribs);
	
	attribs.xsize= std::max(in1_attribs.xsize,
				std::max(in2_attribs.xsize,
					 in3_attribs.xsize));
	attribs.ysize= std::max(in1_attribs.ysize,
				std::max(in2_attribs.ysize,
					 in3_attribs.ysize));
      
	// TODO create a copy of inputs and resize to max
	framebuffer_changeAttributes(in1, &attribs);
	framebuffer_changeAttributes(in2, &attribs);
	framebuffer_changeAttributes(in3, &attribs);

	offset=3;
	break;
      }
    default:
      throw std::runtime_error("unknown frei0r effect type");
    }

  // TODO: check for multiples of 8
  if (attribs.xsize != wr->width || attribs.ysize != wr->height)
    {
      wr->funs->destruct(wr->f0r_instance);
      wr->f0r_instance = wr->funs->construct(attribs.xsize, attribs.ysize);

      if (wr->f0r_instance == 0)
	throw std::runtime_error("frei0r construct returned 0");

      wr->width  = attribs.xsize;
      wr->height = attribs.ysize;
    }

  framebuffer_getAttributes(wr->outf, &attribs);
  attribs.xsize = wr->width;
  attribs.ysize = wr->height;  
  framebuffer_changeAttributes(wr->outf, &attribs);

  for (unsigned int i = offset; i < wr->input_params.size()-1; ++i)
    {
      wr->funs->set_param_value(wr->f0r_instance, wr->input_params[i],
                                i-offset);
    }

  double time = *((double*) wr->input_params[wr->input_params.size()-1]);

  // TODO convert inputs to rgba if plugin uses rgba
  
  switch (wr->plugin_type)
    {
    case F0R_PLUGIN_TYPE_SOURCE:
      {
	if (wr->funs->update != 0)
	  {
	    wr->funs->update(wr->f0r_instance,
			     time,
			     0,
			     wr->outf->framebuffer);
	  }
	else
	  {
	    wr->funs->update2(wr->f0r_instance,
			      time,
			      0,
			    0,
			      0,
			      wr->outf->framebuffer);
	  }
	break;
      }
    case F0R_PLUGIN_TYPE_FILTER:
      {
	if (wr->funs->update != 0)
	  {
	    wr->funs->update(wr->f0r_instance,
			     time,
			     reinterpret_cast<FrameBufferType*>
			       (wr->input_params[0])->framebuffer,
			     wr->outf->framebuffer);
	  }
	else
	  {
	    wr->funs->update2(wr->f0r_instance,
			      time,
			      reinterpret_cast<FrameBufferType*>
			        (wr->input_params[0])->framebuffer,
			      0,
			      0,
			      wr->outf->framebuffer);
	  }
	break;
      }
    case F0R_PLUGIN_TYPE_MIXER2:
      {
	wr->funs->update2(wr->f0r_instance,
			  time,
			  reinterpret_cast<FrameBufferType*>
			    (wr->input_params[0])->framebuffer,
			  reinterpret_cast<FrameBufferType*>
			    (wr->input_params[1])->framebuffer,
			  0,
			  wr->outf->framebuffer);
	break;
      }
    case F0R_PLUGIN_TYPE_MIXER3:
      {
	wr->funs->update2(wr->f0r_instance,
			  time,
			  reinterpret_cast<FrameBufferType*>
			    (wr->input_params[0])->framebuffer,
			  reinterpret_cast<FrameBufferType*>
			    (wr->input_params[1])->framebuffer,
			  reinterpret_cast<FrameBufferType*>
			    (wr->input_params[2])->framebuffer,
			  wr->outf->framebuffer);
	break;
      }
    default:
      throw std::runtime_error("unknown frei0r effect type");
    }

  // TODO convert output to bgra if plugin uses rgba
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
                            const frei0r_funs_t* frei0r, int input,
                            std::vector<f0r_param_info_t>& param_infos)
{
//return "input_spec { type=typ_FrameBufferType id=b const=true strong_dependency=true  } ";
  int index = -1;
  std::string param_name;
  std::ostringstream os;
  os << "input_spec { type=";

  switch (f0r_info.plugin_type)
    {
    case F0R_PLUGIN_TYPE_SOURCE:
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
      break;
    case F0R_PLUGIN_TYPE_FILTER:
      if (input == 0)
        {
          param_name = "input";
	  
          os << "typ_FrameBufferType; id=frei0r_" << param_name
             << " const=true strong_dependency=true }";

          return os.str();
        }
      index = input - 1;
      break;
    case F0R_PLUGIN_TYPE_MIXER2:
      if (input == 0 || input == 1)
        {
          param_name = "input";
	  
          os << "typ_FrameBufferType; id=frei0r_" << param_name <<input
             << " const=true strong_dependency=true }";

          return os.str();
        }
      index = input - 2;
      break;
    case F0R_PLUGIN_TYPE_MIXER3:
      if (input >= 0 && input < 3)
        {
          param_name = "input";
	  
          os << "typ_FrameBufferType; id=frei0r_" << param_name << input
             << " const=true strong_dependency=true }";

          return os.str();
        }
      index = input - 3;
      break;
    default:
      throw std::runtime_error("unknown frei0r effect type");
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
    case F0R_PARAM_STRING:
      os << "typ_StringType"; break;
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


  switch(f0r_info.plugin_type)
    {
    case F0R_PLUGIN_TYPE_SOURCE:
      {
	std::string properties = "{widget_type=number_selector "
	  "lower_bound=8 step_size=8 higher_bound=4096 hidden=true}";
	
	os << " Width" << properties << " Height" << properties;
	break;
      }
    case F0R_PLUGIN_TYPE_FILTER:
      {
	os << " Image ";
	break;
      }
    case F0R_PLUGIN_TYPE_MIXER2:
      {
	os << " Image1 Image2 ";
	break;
      }
    case F0R_PLUGIN_TYPE_MIXER3:
      {
	os << " Image1 Image2 Image3 ";
	break;
      }
    default:
      throw std::runtime_error("unknown frei0r effect type");
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
      f0r_info.plugin_type != F0R_PLUGIN_TYPE_FILTER &&
      f0r_info.plugin_type != F0R_PLUGIN_TYPE_MIXER2 &&
      f0r_info.plugin_type != F0R_PLUGIN_TYPE_MIXER3)
    throw std::runtime_error("Invalid frei0r effect type");

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
    case F0R_PLUGIN_TYPE_MIXER2:
      // +2 for input frames, +1 for time
      return 2 + f0r_info.num_params + 1;
    case F0R_PLUGIN_TYPE_MIXER3:
      // +3 for input frames, +1 for time
      return 3 + f0r_info.num_params + 1;
    default:
      throw std::runtime_error("unknown frei0r effect type");
    }
}



namespace
{
  // Default functions
  int Dinit(void (*)(int,const char*, const char*))
  {
    return 1;
  }
	
  void DshutDown()
  {
  }
	
  void DparseInput(void*,const char*,int)
  {
    throw std::runtime_error("Operation parseInput() not supported by this"
			     "module!");
  }
	
  void* DgetInputAttributes(int)
  {
    return 0;
  }
}

Frei0rModuleClass::Frei0rModuleClass(const frei0r_funs_t& frei0r,
				     NameResolver& resolver)
  : m_frei0r(frei0r)
{
	if (!m_frei0r.init())
	  throw std::runtime_error("init0r failed");

	f0r_plugin_info_t inf0r;
	m_frei0r.get_plugin_info(&inf0r);
	/*std::string name = std::string("mod_") + inf0r.name;*/

	create_f0r_wrapper(m_functionTable);
	
	if (m_functionTable.newInstance == 0 ||
	    m_functionTable.deleteInstance == 0 ||
	    m_functionTable.update == 0)
	  throw std::runtime_error("symbol missing");
		
	if (m_functionTable.init == 0)
	  m_functionTable.init = Dinit;
	
	if (m_functionTable.shutDown == 0)
	  m_functionTable.shutDown = DshutDown;
	
	if (m_functionTable.parseInput == 0)
	  m_functionTable.parseInput = DparseInput;
	
	if (m_functionTable.getInputAttributes == 0)
	  m_functionTable.getInputAttributes = DgetInputAttributes;

	
	if (m_frei0r.init() == 0)
	  {
	    throw std::runtime_error("init0r of frei0r plugin failed");
	  }

	int numInputs;
	int numOutputs ;
	std::string moduleSpec;
	bool isDeterministic;

	f0r_plugin_info_t f0r_info;
	m_frei0r.get_plugin_info(&f0r_info);
	frei0r_check_plugin_info(f0r_info);

        // remember this for later
        m_frei0r_plugin_type = f0r_info.plugin_type;

        numInputs = frei0r_num_inputs(f0r_info);
	
	numOutputs = 1;
	isDeterministic = false;
	
	moduleSpec = frei0r_create_spec(f0r_info);

	utils::StructReader spec(moduleSpec);

	numInputs = spec.getIntValue("number_of_inputs");
	numOutputs = spec.getIntValue("number_of_outputs");
	isDeterministic = spec.getBoolValue("deterministic", false);
	
	std::vector<int> inputs(numInputs);
	m_defaultInputValues.resize(numInputs);
	std::vector<utils::Buffer> 
	  defaultVals(numInputs,
		      utils::Buffer(reinterpret_cast<const unsigned char*>(""),1));
	std::vector<std::string> inputNames(numInputs);
	std::vector<std::string> inputIDs(numInputs);
	
	std::vector<bool> isConst(numInputs);
	std::vector<bool> isStrong(numInputs);
	std::vector<const TypeAttributes*> fixedAttributes(numInputs);
	
	std::vector<f0r_param_info_t> f0r_param_infos;
	
	for (int i = 0; i < numInputs; ++i)
	  {
	    std::string inSpec;
	    std::string param_name;
	    inSpec = frei0r_create_in_param_spec(f0r_info, &m_frei0r, i,
						 f0r_param_infos);
	    
	    utils::StructReader inputSpec(inSpec);
	    
	    inputNames[i] = inputSpec.getStringValue("type");
	    inputIDs[i] = inputSpec.getStringValue("id");
	    
	    try 
	      {
		inputs[i] = resolver.getObjectID(inputNames[i]);
	      }
	    catch(std::runtime_error& e)
	      {
		std::string msg = "Unbekannter Typ: \"";
		msg += inputNames[i];
		msg += '"';
		msg += " beim Laden von ";
		msg += spec.getStringValue("name");
		throw std::runtime_error(msg.c_str());
	      }

	    isConst[i] = (inputSpec.getBoolValue("const"));
	    isStrong[i] = (inputSpec.getBoolValue("strong_dependency"));
	    fixedAttributes[i] 
	      = static_cast<TypeAttributes*>(m_functionTable.getInputAttributes(i));
	  }
	    
	std::vector<int> outputs(numOutputs);
	std::vector<std::string> outputNames(numOutputs);
	std::vector<std::string> outputIDs(numOutputs);
	for (int j = 0; j < numOutputs; ++j)
	  {
	    utils::StructReader outputSpec(frei0r_create_out_spec());
	    outputNames[j] = outputSpec.getStringValue("type");
	    outputIDs[j] = outputSpec.getStringValue("id");
	    outputs[j] = resolver.getObjectID(outputNames[j]);
	  }
	
	m_attributes.inputs = inputs;
	m_attributes.outputs = outputs;
	m_attributes.isConstInput = isConst;
	m_attributes.isStrongDependency = isStrong;
	m_attributes.isDeterministic = isDeterministic;
	m_attributes.fixedAttributes = fixedAttributes;
	
	m_name = spec.getStringValue("name");
	
	std::vector<char> data = frei0r_create_info(f0r_info,
						    f0r_param_infos);
	int bufLen = data.size();	
	
	m_info = dllloader::ModuleInfo::enrichInfo(&data[0],
						   bufLen,
						   m_name,
						   inputNames,
						   outputNames);
  
	m_spec =
	  utils::AutoPtr<ModuleClassSpec>(new ModuleClassSpec(m_name,
							      m_attributes.inputs,
							    defaultVals,
							    inputIDs,
							    m_attributes.outputs,
							    outputIDs));
}

const std::string& Frei0rModuleClass::name() const
{
  return m_name;
}

const utils::Buffer& Frei0rModuleClass::info() const
{
  return m_info;
}

const ModuleClassSpec& Frei0rModuleClass::spec() const
{
  return *m_spec;
}

Frei0rModuleClass::~Frei0rModuleClass()
{
  // call the destructor method of plugin
}


IModule* Frei0rModuleClass::buildInstance(const ITypeFactory& tFactory) const

{
  void* instance;

  typedef void* (*harr_t)(const void*, int, int);
  harr_t harr = (harr_t) m_functionTable.newInstance;
  
  instance = harr(&m_frei0r, m_defaultInputValues.size(),
		  m_frei0r_plugin_type);

  if (instance == 0)
    {
      throw std::runtime_error("Ungute Sache vorgefallen.");
    }

  // Create the default inputs, if any 
  if (m_defaultInputValues.size() > 0 && m_defaultInputValues[0] == 0)
    {
#if (ENGINE_VERBOSITY > 0)
      std::cout << "Creating default values for inputs" << std::endl;
#endif
      for (unsigned int i = 0; i < m_defaultInputValues.size(); ++i)
	{

	  IType* tmp(tFactory.buildNew(m_attributes.inputs[i]));

	  //TODO
	  const TypeAttributes* attr = m_attributes.fixedAttributes[i];
	    if (attr != 0 && !tmp->equalAttributes(*attr))
	      {
		//throw std::runtime_error("Type conversion of default"
		//			 "inputs not implemented yet");
                
                // can throw
		tmp->convert(*tmp, *attr);
	      }
	    m_defaultInputValues[i] = tmp;
	}
    }

  return new frei0r_module(instance,
			   (CModuleVTable&)m_functionTable,
			   m_attributes,
			   tFactory,
			   m_defaultInputValues,
			   m_name,
			   m_frei0r
			   );
}
