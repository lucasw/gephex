#include "runtimesystem.h"

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

#include <stdexcept>
#include <list>
#include <cassert>

#include <algorithm>

#include "interfaces/imodule.h"
#include "interfaces/itype.h"
#include "interfaces/icontrolvaluereceiver.h"
#include "interfaces/imodulestatisticsreceiver.h"

#include "modulefactory.h"

#include "utils/buffer.h"
#include "utils/timing.h"

namespace renderer
{
  static const int AVG_LEN = 20;
	
  /**
   * This class manages a module. It has the ownership of the module
   * and contains some other (statistical and internal) data.
   */
  class ModuleControlBlock
  {
  private:
    IModule* m_module;
    bool m_active;
    int m_activationCount;
    std::list<int> m_times;
    int m_lastTime;
    std::vector<bool> m_inputHasChanged;
	int m_lastUpdated;
		
		
    ModuleControlBlock(const ModuleControlBlock&); //nicht impl.
    const ModuleControlBlock& operator=(const ModuleControlBlock&); //nicht impl.
  public:
    /**
     * Creates a new ModuleContrlBlock.
     * @param module The module that is managed by this class.
     */
    ModuleControlBlock(IModule* module)
      : m_module(module), m_active(false), m_activationCount(0),
	m_times(AVG_LEN), m_lastTime(0),
	m_inputHasChanged(module->getInputs().size(), true),
	m_lastUpdated(-1)
    {
    }
		
    ~ModuleControlBlock() {
      delete m_module;
    }
		
    IModule* module() {
      return m_module; 
    }
		
    void setChanged(int input)
    {
      assert(input >= 0 && input < (int) m_inputHasChanged.size());
      m_inputHasChanged[input] = 1;
    }
		
    bool hasChanged(int input) const
    {
      assert(input >= 0 && input < (int) m_inputHasChanged.size());
      return m_inputHasChanged[input];
    }
		
    bool hasChanged() const
    {
      std::vector<bool>::const_iterator 
	it = std::max_element(m_inputHasChanged.begin(),
			      m_inputHasChanged.end());
			
      if (it == m_inputHasChanged.end())
	return false;
			
      return *it;
    }
		
    /**
     * Wurde setActive() seit dem letzten Aufruf von reset() schon
     * aufgerufen?
     */
    bool isActive() const { 
      return m_active; 
    }
		
    /**
     * Markiert das Modul als reseted (und damit als nicht aktiv).
     * The changed attributes of all inputs are set to false;
     */
    void reset() {
      m_active = false;

      for (std::vector<bool>::iterator it = m_inputHasChanged.begin();
	   it != m_inputHasChanged.end(); ++it)
	{
	  *it = false;
	}
    }

    /**
     * Markiert das Modul als aktiv (und damit als nicht reseted).	 
     */
    void activate() {
      if (m_activationCount >= AVG_LEN)
	m_times.pop_front();
			
      m_times.push_back(m_lastTime);
      ++m_activationCount;
      m_lastTime = 0;
      m_active = true; 
    }

    void addTime(int t)	{
      m_lastTime += t;
    }
		
    int lastTime() const {
      return m_lastTime;
    }
		
    double avgTime() const {
      int num = m_times.size();
			
      if (num == 0)
	return 0;
			
      int aTime = 0;
      for (std::list<int>::const_iterator i = m_times.begin(); 
	   i != m_times.end(); ++i)
	{
	  aTime += *i;
	}
      return aTime / (double) num;
    }

	/**
	 * returns the framecount, when the module was last updated
	 */
	int lastUpdated() const
	{
	return m_lastUpdated;
	}

	/**
	* sets the time when the module was last updated
	*/
	void updated(int frameCount)
	{
		m_lastUpdated = frameCount;
	}

  };
	
  RuntimeSystem::RuntimeSystem (const IModuleFactory& factory,
				const ITypeFactory& tFactory)
    :  m_modules(), m_sinks(), m_time(0), frameCount(0),
       moduleFactory(factory), typeFactory(tFactory)
  {
  }
	
  RuntimeSystem::~RuntimeSystem ()
  {
		
  }
	
  RuntimeSystem::ModuleControlBlockPtr RuntimeSystem::getControlBlock(IModule* mod)
  {
    ControlBlockMap::iterator i = m_modules.find(mod->getID());
    if (i == m_modules.end()) 
      throw std::runtime_error("modulecontrollBlock does not exist "
			       "(RuntimeSystem::getControllBlock)");
		
    return i->second;
  }
	
  void RuntimeSystem::addModule(const std::string& moduleClassName,
				int moduleID)
  {
    IModule* newModule = moduleFactory.buildNewModule(moduleClassName,
						      typeFactory);
    newModule->setID(moduleID);
		
    ModuleControlBlockPtr newBlock ( new ModuleControlBlock(newModule) );
		
    m_modules[moduleID] = newBlock;
		
    // no output => module is a sink
    if (newModule->getOutputs().size() == 0) 
      m_sinks.push_front(newBlock);
		
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Added new Module (id " << moduleID << ") of Class " 
	      << moduleClassName << std::endl;
#endif
  }
	
  void RuntimeSystem::connect(int i1,int outputNumber,int i2,int inputNumber)
  {
    ControlBlockMap::const_iterator it1 = m_modules.find(i1);
    ControlBlockMap::const_iterator it2 = m_modules.find(i2);
    if (it1 == m_modules.end() || it2 == m_modules.end())
      {
	throw std::runtime_error("Modul nicht vorhanden.");
      }
		
    IModule* m1 = it1->second->module();
    IModule* m2 = it2->second->module();
		
    int t1 = m1->getOutputs()[outputNumber]->getType();
    int t2 = m2->getInputs()[inputNumber]->getType();
		
    if (t1 != t2)
      {
	throw std::runtime_error("Typen sind ungleich!");
      }
		
    IModule::IOutputPtr out = m1->getOutputs()[outputNumber];
    IModule::IInputPtr in = m2->getInputs()[inputNumber];
		
    utils::AutoPtr<IOutputPlug> plug = out->plugIn(*in);
    in->plugIn(plug);
		
    it2->second->setChanged(inputNumber);

#if (ENGINE_VERBOSITY > 0)
    std::cout << "Connected output #" << outputNumber 
	      << " of module #" << i1 << " with input #" << inputNumber
	      << " of module #" << i2 << std::endl;
#endif
  }
	
  void RuntimeSystem::disconnect(int moduleID,int inputNumber)
  {
    ControlBlockMap::iterator i = m_modules.find(moduleID);
    if (i == m_modules.end())
      throw std::runtime_error("module does not exist "
			       "(RuntimeSystem::disconnect)");
		
    IModule* m = i->second->module();
		
    //TODO: input number is unchecked
    IModule::IInputPtr in = m->getInputs()[inputNumber];

    in->unPlug();

    i->second->hasChanged(inputNumber);
  }
	
	
  namespace
  {
    // wird aufgerufen nachdem das zu block gehoerende modul
    // vollständig berechnet wurde
    // setzt auch die verbundenen inputs auf changed
    void sendInputValues(RuntimeSystem::ModuleControlBlockPtr block,
			 IControlValueReceiver* cvr,
			 const RuntimeSystem::ControlBlockMap& blocks,
			 int frameCount)
    {
      //  int moduleID = m->getID();
      IModule* m = block->module();
      const std::vector<IModule::IOutputPtr>& outs = m->getOutputs();
		
      for (std::vector<IModule::IOutputPtr>::const_iterator 
	     it = outs.begin(); it != outs.end(); ++it)
	{
	  IModule::IOutputPtr current = *it;
	  std::list<IInput*> ins = current->getConnectedInputs();
			
	  for (std::list<IInput*>::const_iterator jz = ins.begin(); 
	       jz != ins.end(); ++jz)
	    {
	      IInput* in = *jz;
	      const IType* t = in->getData();
	      utils::Buffer buf;
	      bool success = t->serialize(buf);
	      int moduleID = in->getModule()->getID();
	      int inputIndex = in->getIndex();
				
	      RuntimeSystem::ControlBlockMap::const_iterator 
		kt = blocks.find(moduleID);
				
	      assert(kt != blocks.end());
				
	      RuntimeSystem::ModuleControlBlockPtr b = kt->second;
	      b->setChanged(inputIndex);
	      
	      //TODO: catch exceptions!!!!!
	      if (success && cvr != 0 /*&& (frameCount & 7) == 7*/)
		{
		  cvr->controlValueChanged(moduleID, inputIndex, buf);
		}
	    }
	}
    }
  }
	
  void RuntimeSystem::update(IControlValueReceiver* cvr,
			     IModuleStatisticsReceiver* msr)
  {	
    std::list<ModuleControlBlockPtr> stack;
		
    for (std::list<ModuleControlBlockPtr>::iterator sink = m_sinks.begin();
	 sink != m_sinks.end(); ++sink)
      {
	(*sink)->activate();
	stack.push_front(*sink);
      }

#if (ENGINE_VERBOSITY > 2)
    std::cout << "Pushed all m_sinks onto the stack." << std::endl;
    std::cout << "Number of m_sinks: " << m_sinks.size() << std::endl;
#endif
		
    while (!stack.empty())
      {
	ModuleControlBlockPtr block = stack.front();
			
	IModule* m = block->module();
			
	assert (block->isActive());
			
	std::list<IInput*> l;
	m->dependencies(l);
			
	// alle module die m benötigt auf den stack
	if (!l.empty())
	  {
	    for (std::list<IInput*>::iterator i = l.begin(); i != l.end(); ++i)
	      {
		IModule* temp = (*i)->getConnectedModule();
					
		//TODO: wenn der input nicht verbunden ist???
		if (temp == 0)
		  {
		    continue;
		  }
					
		ModuleControlBlockPtr current = getControlBlock(temp);
		// nur module hinzufügen die noch nicht im stack sind
		// und noch nicht in diesem frame gerechnet wurden
		if (!current->isActive() && current->lastUpdated() != frameCount)
		  {
		    current->activate();
		    stack.push_front(current);
		  }
		else
		  {
		    // current ist schon im stack		    
		    // there must be a cycle, update the input
		    block->setChanged((*i)->getIndex());
		  }
	      }
	  }
	else // m does not need any more inputs
	  {
		
	    if (!m->isDeterministic() || block->hasChanged())
	      {
		//call update for all needed inputs
		//updateInputs(block, frameCount);
			
		unsigned long t1 = utils::Timing::getTimeInMillis();
		m->update();

		// check patched outputs
		//TODO: this seems to be a bug, the same is already done in CModule::update()!
		// commented it out
/*		const std::vector<IModule::IOutputPtr>& outs = m->getOutputs();
		for (int i = 0; i < outs.size(); ++i)
		  {
		    IInput* patchedInput = outs[i]->getPatchedInput();
				
		    IOutput* out = &*outs[i];
		    if (patchedInput != 0)
		      {
			out->setPatchedInput(patchedInput);
		      }
		    else
		      out->unPatch();
		  }*/

		unsigned long t2 = utils::Timing::getTimeInMillis();
		block->addTime(t2-t1);
			
		if (msr != 0 && (frameCount & 7) == 7)
		  {
		    //sende statistik-daten
		    msr->modExecTimeSignal(m->getID(),block->avgTime());
		  }
		// die geänderten werte an die controlValueReceiver senden
		// und die verbundenen inputs auf changed setzen
		sendInputValues(block,cvr,m_modules,frameCount);
	      }
		
	    stack.pop_front();
	    block->reset();
		block->updated(frameCount);
	  }
	}
		
    ++frameCount;
#if (ENGINE_VERBOSITY > 2)
    std::cout << "finished with updating" << std::endl;
#endif
  }
	
  void RuntimeSystem::deleteModule(int id)
  {
    ControlBlockMap::iterator it = m_modules.find(id);
    if (it == m_modules.end())
      {
	throw std::runtime_error("Modul nicht vorhanden "
				 "RuntimeSystem::deleteModule()");
      }
		
    ModuleControlBlockPtr block = it->second;  
    IModule* n = block->module();

    // disconnect all modules that are connected to an ouput of the
    // deleted module
    for (ControlBlockMap::iterator i = m_modules.begin(); 
	 i != m_modules.end(); ++i)
      {
	if (i->second == 0) continue;
	ModuleControlBlockPtr block = i->second;
	IModule* m = block->module();
	for (unsigned int j = 0; j < m->getInputs().size(); ++j)
	  {
	    IModule::IInputPtr in = m->getInputs()[j];
	    if (in->getConnectedModule() == n) 
	      {
		in->unPlug();
		block->hasChanged(j);
	      }
	  }
      }

    // disconnect all modules that are connected to an input of
    // the deleted module
    for (unsigned int j = 0; j < n->getInputs().size(); ++j)
      {
	IModule::IInputPtr in = n->getInputs()[j];

	if (in->getConnectedModule() != 0)
	  in->unPlug();
      }
		
    if (n->getOutputs().size() == 0)
      {
	m_sinks.remove(block); 
      }
		
    m_modules.erase(it);
		
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Deleted Module # " << id << std::endl;
#endif
  }
	
  void RuntimeSystem::setInputValue(int moduleID,int inputIndex,
				    const utils::Buffer& buf,
				    IControlValueReceiver* cvr)
  {
    ControlBlockMap::const_iterator 
      it = m_modules.find(moduleID);
    if (it == m_modules.end())
      {
	throw std::runtime_error("Modul nicht vorhanden "
				 "RuntimeSystem::setInputValue()");
      }
		
    ModuleControlBlockPtr block = it->second;
    block->setChanged(inputIndex);
		
    IModule* n = block->module();
		
    IModule::IInputPtr in = n->getInputs()[inputIndex];
		
    in->setValue(buf);
		
    if (cvr != 0)
      cvr->controlValueChanged(moduleID,inputIndex,buf);
  }
	
  struct DoSync
  {
    DoSync(IControlValueReceiver* cvr_) : cvr(cvr_) {};
    void operator()(const IModule::IInputPtr& in)
    {
      utils::Buffer b;
      bool success = in->getData()->serialize(b);

      if (success)
	cvr->controlValueChanged(in->getModule()->getID(),
				 in->getIndex(),b);
    }
		
  private:
    IControlValueReceiver* cvr;
  };
	
  struct DoAllSync
  {
    DoAllSync(IControlValueReceiver* cvr_) : cvr(cvr_) {};
    void operator()(const std::pair<int,RuntimeSystem::ModuleControlBlockPtr>& p)
    {
      if (cvr)
	{
	  RuntimeSystem::ModuleControlBlockPtr block = p.second;
				
	  IModule* n = block->module();
				
	  std::for_each(n->getInputs().begin(), n->getInputs().end(),
			DoSync(cvr));
	}
    }
  private:
    IControlValueReceiver* cvr;
  };
	
  void RuntimeSystem::syncInputValue(int moduleID, int inputIndex,
				     IControlValueReceiver* cvr) const
  {
    if (!cvr)
      return;
		
    ControlBlockMap::const_iterator 
      it = m_modules.find(moduleID);
    if (it == m_modules.end())
      {
	throw std::runtime_error("Modul nicht vorhanden "
				 "RuntimeSystem::syncInputValue()");
      }
		
    DoSync sync(cvr);
		
    ModuleControlBlockPtr block = it->second;
		
    IModule* n = block->module();
		
    IModule::IInputPtr in = n->getInputs()[inputIndex];
		
    sync(in);
  }
	
  void RuntimeSystem::synchronizeInputValues(IControlValueReceiver* cvr) const
  {
    std::for_each(m_modules.begin(), m_modules.end(), DoAllSync(cvr));
  }
	
} // end of namespace renderer
