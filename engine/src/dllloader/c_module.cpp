#include "c_module.h"

#include <stdexcept>
#include <ctime>

#include "c_input.h"
#include "c_output.h"

#include "c_moduletables.h"
#include "interfaces/itype.h"
#include "interfaces/itypefactory.h"

class UpdateStrategy
{
protected:
  int state;
	
public:
  UpdateStrategy() : state(0) {}
  virtual ~UpdateStrategy() {};
  virtual void dependencies(std::list<IInput*>&l, void* instance,
			    std::vector<IModule::IInputPtr>& inputs,
			    const CModuleVTable& mvt) = 0;
	
  virtual UpdateStrategy* clone() const = 0;
	
};

class InputStrategy : public UpdateStrategy
{
public:
  InputStrategy() : UpdateStrategy() {};
  void dependencies(std::list<IInput*>&l,void* instance,
		    std::vector<IModule::IInputPtr>& inputs,
		    const CModuleVTable& mvt);
	
	
  UpdateStrategy* clone() const { return new InputStrategy(); }
};

class SimpleStrategy : public UpdateStrategy
{
public:
  SimpleStrategy() : UpdateStrategy() {};
	
  void dependencies(std::list<IInput*>&,void* m_instance,
		    std::vector<IModule::IInputPtr>& ins,
		    const CModuleVTable& mvt);
	
  UpdateStrategy* clone() const { return new SimpleStrategy(); }
};

class DependencyStrategy : public UpdateStrategy
{
public:
  DependencyStrategy() : UpdateStrategy() {};
	
  void dependencies(std::list<IInput*>&,void* m_instance,
		    std::vector<IModule::IInputPtr>& ins,
		    const CModuleVTable& mvt);
	
  UpdateStrategy* clone() const { return new DependencyStrategy(); }
};


void InputStrategy::dependencies(std::list<IInput*>& ,void* ,
				 std::vector<IModule::IInputPtr>& ,
				 const CModuleVTable& )
{
  // do nothing because there are no inputs
}


void SimpleStrategy::dependencies(std::list<IInput*>&l,void*,
				  std::vector<IModule::IInputPtr>& inputs,
				  const CModuleVTable&)
{
  switch(state)
    {
    case(0): // tell renderer to render all inputs 
      for (std::vector<IModule::IInputPtr>::iterator it = inputs.begin();
	   it!=inputs.end();++it)
	{
	  l.push_back(&**it);
	}
      state=1;
      break;
    case(1): // now all data is uptodate 
      for (std::vector<IModule::IInputPtr>::iterator it = inputs.begin();
	   it!=inputs.end();++it)
	{ //  update the inputs
	  (*it)->update();
	}
      //doUpdate(instance,inputs,outputs,mvt);
      state = 0;
      break;
    default:
      throw std::runtime_error("Mist");
    }
}

void DependencyStrategy::dependencies(std::list<IInput*>&l,void* instance,
				      std::vector<IModule::IInputPtr>& inputs,
				      const CModuleVTable& mvt)
{
  switch(state)
    {
    case(0):
      for (std::vector<IModule::IInputPtr>::iterator it = inputs.begin(); 
	   it!=inputs.end(); ++it)
	{
	  if ((*it)->isStrongDependency())
	    {
	      l.push_back(&**it);
				// std::cout << "strong: pushed " << i << std::endl;
	    }
	}
      state=1;
      break;
    case(1):
      {
	// update all inputs send by last state
	for (std::vector<IModule::IInputPtr>::iterator it = inputs.begin(); 
	     it!=inputs.end(); ++it)
	  {
	    if ((*it)->isStrongDependency())
	      {
		(*it)->update();
	      }
	  }
			
			
	int* neededInputs = 0;
	mvt.strongDependenciesCalculated(instance,&neededInputs);
	if (neededInputs != 0)
	  {
	    for (unsigned int i = 0; i < inputs.size(); ++i)
	      {
		if (!inputs[i]->isStrongDependency() && neededInputs[i] == 1)
		  {
		    l.push_back(&*inputs[i]);
		    //  std::cout << "needed: pushed " << i << std::endl;
		  }
	      }
	  }
	state=2;
	break;
      }
    case(2):
      { // update inputs for last state
	int* neededInputs = 0;
	mvt.strongDependenciesCalculated(instance,&neededInputs);
	if (neededInputs != 0)
	  {
	    for (unsigned int i = 0; i < inputs.size(); ++i)
	      {
		if (!inputs[i]->isStrongDependency() && neededInputs[i] == 1)
		  {
		    inputs[i]->update();
		  }
	      }
	  }
      }
      //doUpdate(instance,inputs,outputs,mvt);
      state = 0;
      break;
    default:
      throw std::runtime_error("Mist");
    }
}

//----------------------------------------------------------------------------

CModule::CModule(void* instance,
		 CModuleVTable& vtable,
		 const CModuleAttributes& attributes,
		 const ITypeFactory& tfactory_,
		 const std::vector<ITypePtr>& defaultInputTypes)
  : IModule(-1), m_instance(instance), m_vtable(&vtable),
    inputs(attributes.inputs.size()),outputs(attributes.outputs.size()),
    _isDeterministic(attributes.isDeterministic)
				 
{
  for (unsigned int i = 0; i < attributes.inputs.size(); ++i)
    {
      inputs[i] 
	= IInputPtr( new CInput(attributes.inputs[i],
				attributes.isConstInput[i],
				attributes.isStrongDependency[i],*this,i,
				tfactory_,attributes.fixedAttributes[i],
				*defaultInputTypes[i], *m_vtable, m_instance));
    }
	
  for (unsigned int j = 0; j < attributes.outputs.size(); ++j)
    {
      IType* type = tfactory_.buildNew(attributes.outputs[j]);
		
      outputs[j] = IOutputPtr(new COutput(*this,attributes.outputs[j],type,
		                      j,*m_vtable,m_instance));		      
    }
	
  if (attributes.inputs.size() == 0)
    {
      us = UpdateStrategyPtr(new InputStrategy());
    }
  else if (m_vtable->strongDependenciesCalculated == 0)
    {
      us = UpdateStrategyPtr(new SimpleStrategy());
    }
  else
    {
      us = UpdateStrategyPtr(new DependencyStrategy());
    }
	
}

CModule::~CModule()
{
  m_vtable->deleteInstance(m_instance);	
}

const std::vector<CModule::IInputPtr>& CModule::getInputs() const
{
  return inputs;
}

const std::vector<CModule::IOutputPtr>& CModule::getOutputs() const
{
  return outputs;
}

bool CModule::isDeterministic() const
{
  return _isDeterministic;
}

void CModule::dependencies(std::list<IInput*>& l)
{
  us->dependencies(l,m_instance,inputs,*m_vtable);
}

void CModule::update()
{	
  // Das patchlayout des Moduls abfragen:
  if (m_vtable->getPatchLayout != 0)
  {
      int* out2in;
	  
      m_vtable->getPatchLayout(m_instance, &out2in);
	  
      //Alle gepatchten outputs updaten
      for (int i = 0; i < outputs.size(); ++i)
	  {
		  int patchedInputIndex = out2in[i];
		  COutput* out = static_cast<COutput*>(&*outputs[i]);
		  assert(out == dynamic_cast<COutput*>(&*outputs[i]));
		  
		  if (patchedInputIndex != -1)
		  {
			  out->setPatchedInput(&*inputs[patchedInputIndex]);
		  }
		  else
		  {
			  //out->setPatchedInput(0);
			  out->unPatch();
		  }
		  
	  }
  }
  
  // Modul updaten
  m_vtable->update(m_instance);
}

void CModule::parseInput(const char* data,int len)
{
  m_vtable->parseInput(m_instance, data,len);
}


//----------------------------------------------------------------------------
