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

#include "gephex_module_class.h"

#include "gephex_module.h"
#include "moduleinfoutils.h"

#include "renderer/typefactory.h" //TODO: not allowed
#include "interfaces/itype.h"
#include "utils/structreader.h"

#include "nameresolver.h"

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

extern "C" 
{
  void moduleLog(int level, const char* sender, const char* msg);
};

CModuleClass::CModuleClass(const CModuleFunctionTable& ft,
			   NameResolver& resolver)
  : m_functionTable( ft ) 
{
  // initialize  the plugin
  if (ft.init(moduleLog) == 0)
    {
      throw std::runtime_error("init of module plugin failed");
    }

  const std::string moduleSpec = ft.getSpec();
  const utils::StructReader spec(moduleSpec);

  int numInputs;
  try
    {
      numInputs = spec.getIntValue("number_of_inputs");
    }
  catch (...)
    {
      throw std::runtime_error("number_of_inputs not defined");
    }

  
  int numOutputs ;
  try
    {
      numOutputs = spec.getIntValue("number_of_outputs");
    }
  catch (...)
    {
      throw std::runtime_error("number_of_outputs not defined");
    }

  const bool isDeterministic = spec.getBoolValue("deterministic", false);

  // process inputs
  std::vector<int> inputs(numInputs);


  std::vector<utils::Buffer> 
    defaultVals(numInputs,
		utils::Buffer(reinterpret_cast<const unsigned char*>(""),1));
  std::vector<std::string> inputNames(numInputs);
  std::vector<std::string> inputIDs(numInputs);
  
  std::vector<bool> isConst(numInputs);
  std::vector<bool> isStrong(numInputs);
  std::vector<const TypeAttributes*> fixedAttributes(numInputs);
  
  for (int i = 0; i < numInputs; ++i)
    {
      const std::string inSpec ( ft.getInputSpec(i) );
      const utils::StructReader inputSpec(inSpec);
      try
	{
	  std::string defaultVal = inputSpec.getStringValue("default");
	  defaultVals[i] 
	    = utils::Buffer(reinterpret_cast<const unsigned char*>(defaultVal.c_str()),
			    defaultVal.length()+1);
	}
      catch(...) {}
      
      try
	{
	  inputNames[i] = inputSpec.getStringValue("type");
	}
      catch (...)
	{
	  throw std::runtime_error("type nicht angegeben");
	}
      
      try
	{
	  inputIDs[i] = inputSpec.getStringValue("id");
	}
      catch (...)
	{
	  throw std::runtime_error("id nicht angegeben");
	}
      
#if (ENGINE_VERBOSITY > 2)
      std::cout << "inputNames[" << i << "] = \"" 
		<< inputNames[i] << '"' << std::endl;
#endif
      
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
			
      try 
	{
	  isConst[i] = (inputSpec.getBoolValue("const"));
	}
      catch (...)
	{
	  throw std::runtime_error("const nicht angegeben");
	}
      
      try 
	{
	  isStrong[i] = (inputSpec.getBoolValue("strong_dependency"));
	}
      catch (...)
	{
	  throw std::runtime_error("strong_dependency nicht angegeben");
	}
      
      try
	{
	  fixedAttributes[i] 
	    = static_cast<TypeAttributes*>(ft.getInputAttributes(i));
	}
      catch (...)
	{
	  throw std::runtime_error("darf net sein");
	}
    }
  
  // Create the default inputs,
  m_defaultInputValues.resize( numInputs );




  
  // process outputs
  std::vector<int> outputs(numOutputs);
  std::vector<std::string> outputNames(numOutputs);
  std::vector<std::string> outputIDs(numOutputs);
  for (int j = 0; j < numOutputs; ++j)
    {
      const std::string outSpec( ft.getOutputSpec(j) );
      const utils::StructReader outputSpec(outSpec);			
      try
	{
	  outputNames[j] = outputSpec.getStringValue("type");
	}
      catch (...)
	{
	  throw std::runtime_error("type nicht angegeben");
	}
      
      try
	{
	  outputIDs[j] = outputSpec.getStringValue("id");
	}
      catch (...)
	{
	  throw std::runtime_error("id nicht angegeben");
	}
      
      try
	{
	  outputs[j] = resolver.getObjectID(outputNames[j]);
	}
      catch(std::runtime_error&)
	{
	  std::string msg = "Unbekannter Typ: \"";
	  msg += outputNames[j] + '"';
	  throw std::runtime_error(msg.c_str());
	}
    }
      		
  m_attributes.inputs = inputs;
  m_attributes.outputs = outputs;
  m_attributes.isConstInput = isConst;
  m_attributes.isStrongDependency = isStrong;
  m_attributes.isDeterministic = isDeterministic;
  m_attributes.fixedAttributes = fixedAttributes;
	
  try
    {
      m_name = spec.getStringValue("name");
    }
  catch (...)
    {
      throw std::runtime_error("no module name specified");
    }

  // construct module info string
  const int bufLen ( ft.getInfo(0,0) );
  std::vector<char> data(bufLen);
  const int len = ft.getInfo(&data[0],bufLen);
  if (len == 0)
    {
      throw std::runtime_error("getInfo failed!");
    }
  
  m_info = dllloader::ModuleInfo::enrichInfo(&data[0], bufLen, m_name,
				  inputNames, outputNames);

  m_spec = utils::AutoPtr<ModuleClassSpec>(new ModuleClassSpec(m_name,
					      m_attributes.inputs,
					      defaultVals,
					      inputIDs,
					      m_attributes.outputs,
					      outputIDs));

}

const std::string& CModuleClass::name() const
{
  return m_name;
}

const utils::Buffer& CModuleClass::info() const
{
  return m_info;
}

const ModuleClassSpec& CModuleClass::spec() const
{
  return *m_spec;
}

CModuleClass::~CModuleClass()
{
}


IModule* CModuleClass::buildInstance(const ITypeFactory& tFactory) const
{
  void* instance = m_functionTable.newInstance();

  if (instance == 0)
    {
      throw std::runtime_error("Ungute Sache vorgefallen.");
    }

  if (m_defaultInputValues.size() > 0 && m_defaultInputValues[0] == 0)
    {
      for (unsigned int i = 0; i < m_defaultInputValues.size(); ++i)
	{
	  IType* tmp = tFactory.buildNew(m_attributes.inputs[i]);

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
  
  return new CModule(instance,(CModuleVTable&)m_functionTable,m_attributes,
		     tFactory,m_defaultInputValues, m_name);
}
