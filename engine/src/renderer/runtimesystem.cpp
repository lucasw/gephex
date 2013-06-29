/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

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

#include "runtimesystem.h"

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

#include <stdexcept>
#include <stack>
#include <cassert>

#include <algorithm>

#include <iostream>
#include <sstream>

#include "interfaces/imodule.h"
#include "interfaces/itype.h"
#include "interfaces/icontrolvaluereceiver.h"
#include "interfaces/imodulestatisticsreceiver.h"

#include "modulefactory.h"

#include "utils/buffer.h"
#include "utils/timing.h"
#include "utils/ilogger.h"

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
    /**
     * Pointer to the module instance. The object is managed by the
     * ModuleControlBlock
     */
    IModule* m_module;
      
    /**
     * This flag is used by the renderer algorithm, to indicate that the
     * is already on the stack and that means it is a parent node of the
     * current one 
     */
    bool m_active;
    int m_activationCount;
    std::list<int> m_times;
    int m_lastTime;
      
    /**
     * every input has a flag that is set to true if the input was changed.
     */
    std::vector<bool> m_inputHasChanged;

    /**
     * Time the module was last updated. -1 indicates a never updated module
     */
    int m_lastUpdated;
    
    // not implemented methods
    ModuleControlBlock(const ModuleControlBlock&);
    const ModuleControlBlock& operator=(const ModuleControlBlock&);

  public:
    /**
     * Creates a new ModuleContrlBlock.
     * @param module Pointer to the module. It is now managed by this class.
     */
    ModuleControlBlock(IModule* module)
      : m_module(module), m_active(false), m_activationCount(0),
	m_times(AVG_LEN), m_lastTime(0),
	m_inputHasChanged(module->getInputs().size(), true),
	m_lastUpdated(-1)
    {
    }

		
    /**
     * Destroys the ModuleControlBlock and its Module
     */
    ~ModuleControlBlock() 
    {
      delete m_module;
    }

		
    /**
     * Get a pointer to the managed module
     * \returns pointer to the module
     */
    IModule* module() 
    {
      return m_module; 
    }

		
    /**
     * Sets the changed flag for one input of the module
     * \param input index of the input. [0 .. #inputs-1]
     */
    void setChanged(int input)
    {
      if (!(input >= 0 && input < (int) m_inputHasChanged.size()))
        {
          std::cerr << "Wrong input at setChanged!\n";
          return; 
        }
      m_inputHasChanged[input] = 1;
    }
	
	
    /**
     * Query the status of one changed flag
     * \param input index of the input. [0 .. #inputs-1]
     */
    bool hasChanged(int input) const
    {
      if (!(input >= 0 && input < (int) m_inputHasChanged.size()))
        {
          std::cerr << "Wrong input at setChanged!\n";
          return false; 
        }
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
    bool isActive() const 
    { 
      return m_active; 
    }
	
    
    /**
     * Markiert das Modul als reseted (und damit als nicht aktiv).
     * The changed attributes of all inputs are set to false;
     */
    void reset() 
    {
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
    void activate() 
    {
      if (m_activationCount >= AVG_LEN)
	m_times.pop_front();
			
      m_times.push_back(m_lastTime);
      ++m_activationCount;
      m_lastTime = 0;
      m_active = true; 
    }

    
    void addTime(int t)
    {
      m_lastTime += t;
    }
	
    
    int lastTime() const 
    {
      return m_lastTime;
    }

		
    double avgTime() const 
    {
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
     * \returns the framecount, when the module was last updated
     */
    int lastUpdated() const
    {
      return m_lastUpdated;
    }


    /**
     * sets the time when the module was last updated
     * \param frameCount last update time
     */
    void updated(int frameCount)
    {
      m_lastUpdated = frameCount;
    }
    
  };

  RuntimeSystem::RuntimeSystem (const IModuleFactory& factory,
                                const ITypeFactory& tFactory,
                                utils::AutoPtr<utils::ILogger>& logger)
    :  m_modules(), m_sinks(), m_time(0), frameCount(0),
       moduleFactory(factory), typeFactory(tFactory), m_logger(logger)
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
    
    // no output or notdeterministic => module is a sink
    if (( newModule->getOutputs().size() == 0 ) ||
	( !newModule->isDeterministic()) ) 
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
	throw std::runtime_error("module does not exist.");
      }
		
    IModule* m1 = it1->second->module();
    IModule* m2 = it2->second->module();
	
    if (outputNumber < 0 ||
        static_cast<unsigned int>(outputNumber) >= m1->getOutputs().size())
      throw std::runtime_error("Invalid output at RuntimeSystem::connect.");

    if (inputNumber < 0 ||
        static_cast<unsigned int>(inputNumber) >= m2->getInputs().size())
      throw std::runtime_error("Invalid input at RuntimeSystem::connect.");

    int t1 = m1->getOutputs()[outputNumber]->getType();
    int t2 = m2->getInputs()[inputNumber]->getType();
		
    if (t1 != t2)
      {
	throw std::runtime_error("Type mismatch!");
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
                         int /*frameCount*/)
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
				  
              int moduleID = in->getModule()->getID();
              int inputIndex = in->getIndex();
				  
              RuntimeSystem::ControlBlockMap::const_iterator 
                kt = blocks.find(moduleID);
				  
              assert(kt != blocks.end());
				  
              RuntimeSystem::ModuleControlBlockPtr b = kt->second;
              b->setChanged(inputIndex);			  			
            }
			  
        }
      const std::vector<IModule::IInputPtr>& ins = m->getInputs();
      for (std::vector<IModule::IInputPtr>::const_iterator it = ins.begin();
           it != ins.end(); ++it)
        {
          IModule::IInputPtr current = *it;
          int inputIndex = current->getIndex();

          if (!block->hasChanged(inputIndex))
            continue;

          const IType* t = current->getData();
          utils::Buffer buf;
          bool success = t->serialize(buf);
          //TODO: catch exceptions!!!!!
          if (success && cvr != 0 /*&& (frameCount & 7) == 7*/)
            {
              int moduleID = current->getModule()->getID();				 
              cvr->controlValueChanged(moduleID, inputIndex, buf);
            }
        }
		  
    }
	  
  }
	
  void RuntimeSystem::update(IControlValueReceiver* cvr,
			     IModuleStatisticsReceiver* msr)
  {	
    std::stack<ModuleControlBlockPtr> stack;
    
    // push the sinks (modules with no output) on the stack
    for (std::list<ModuleControlBlockPtr>::iterator sink = m_sinks.begin();
	 sink != m_sinks.end(); ++sink)
      {
	(*sink)->activate();
	stack.push(*sink);
      }

#if (ENGINE_VERBOSITY > 2)
    std::cout << " ***** update begins\n";
    std::cout << "Pushed all m_sinks onto the stack." << std::endl;
    std::cout << "Number of m_sinks: " << m_sinks.size() << std::endl;
#endif
		
    while (!stack.empty())
      {
	ModuleControlBlockPtr block = stack.top();
			
	IModule* m = block->module();
			
	assert (block->isActive());

#if (ENGINE_VERBOSITY > 3)
        std::cout << "On Stack: " << m->getID() << "\n";
#endif
			
	IInput* dep = m->dependencies();
			
	// is there a not satisfied dependency left?
	if (dep != 0)
	  {
	    IModule* temp = dep->getConnectedModule();
	
	    // is the input connected to an other module?
	    if (temp != 0)
              {
#if (ENGINE_VERBOSITY > 3)
                std::cout << "   Following connection to " << temp->getID()
                          << "\n";
#endif    
		// check that module
		ModuleControlBlockPtr current = getControlBlock(temp);
		
		// 1. in case the module is on the stack we detected a cycle
		// the solution is to use the old value of that output
		// 2. the module is already updatet in this cycle
		// we dont want do update it again
		if (current->isActive()||(current->lastUpdated()==frameCount))
		  {
		    // it could be that the value changed (conservative)
		    block->setChanged(dep->getIndex());
#if (ENGINE_VERBOSITY > 3)
                    std::cout << "     [already done]" << temp->getID()
                              << "\n";
#endif    
		  }
		else
		  {
#if (ENGINE_VERBOSITY > 3)
                    std::cout << "     [pushed on stack]" << temp->getID()
                              << "\n";
#endif
		    // we must update this module
		    current->activate();
		    stack.push(current);		    
		  }
              }
	  }
	else
	  {
	    // all dependencies are satisfied

	    // is a update necessary?
	    if (!m->isDeterministic() || block->hasChanged())
	      {
#if (ENGINE_VERBOSITY > 3)
                std::cout << "   Updating...\n";
#endif    
		// lets update the module
		unsigned long startTime = utils::Timing::getTimeInMillis();
		//TODO: if an exception is caught, remove the module!
		try {
                  m->update();
		}
		catch (std::exception& e){
                  std::ostringstream os;
                  os << "error at update: " << e.what() << "\n"
                     << "module id = " << m->getID() << "\n"
                     << "module class = " << m->module_class_name() << "\n";

                  m_logger->error("Runtimesystem", os.str());
		}
		catch (...) {
                  std::ostringstream os;
                  os << "error at update\n"
                     << "module id = " << m->getID() << "\n"
                     << "module class = " << m->module_class_name() << "\n";

                  m_logger->error("Runtimesystem", os.str());
		}
		unsigned long stopTime = utils::Timing::getTimeInMillis();
		block->addTime(stopTime-startTime);
			
		// should we send the statistic data?
		// is there a receiver?
		// is it the right time?
		if (msr != 0 && (frameCount & 7) == 7)
		  {
		    // send statistic data
		    msr->modExecTimeSignal(m->getID(),block->avgTime());
		  }

		// send the changes values to the controlValueReceiver
		// and set them there to changed
		sendInputValues(block,cvr,m_modules,frameCount);
	      }
            else
              {
#if (ENGINE_VERBOSITY > 3)
                std::cout << "   Skipping update (deterministic and no "
                          << "needed input changed)...\n";
#endif    
              }
		
	    // this module is now updated
	    stack.pop(); 
	    block->reset();
	    block->updated(frameCount);
	  }
      }
		
    // all sinks are uptodate we can finish now
    // increase the timestamp
    ++frameCount;

#if (ENGINE_VERBOSITY > 2)
    std::cout << "**** update finished" << std::endl;
#endif
  }
	

  void RuntimeSystem::deleteModule(int moduleID)
  {
    // get the control block for the moduleid
    ControlBlockMap::iterator it = m_modules.find(moduleID);
    
    if (it == m_modules.end())
      {
	// a module with that id doesnt exist
	throw std::runtime_error("Module does not exist at "
				 "RuntimeSystem::deleteModule()");
      }

    // a module with that id must exist
    assert(it != m_modules.end());

    ModuleControlBlockPtr block = it->second;  
    IModule* n = block->module();

    // disconnect all modules that are connected to an output
    for (ControlBlockMap::iterator i = m_modules.begin(); 
	 i != m_modules.end(); ++i)
      {
	// is this possible?
	// if (i->second == 0) continue;
	assert(i->second != 0);

	ModuleControlBlockPtr block = i->second;
	IModule* m = block->module();	

	// check all inputs of that module
	for (unsigned int j = 0; j < m->getInputs().size(); ++j)
	  {
	    IModule::IInputPtr in = m->getInputs()[j];

	    // is it connected?
	    if (in->getConnectedModule() == n) 
	      {
		// yes, the unplug it
		in->unPlug();
		// and signal change
		block->hasChanged(j);
	      }
	  }
      }

    // disconnect all modules that are connected to an input
    for (unsigned int j = 0; j < n->getInputs().size(); ++j)
      {
	IModule::IInputPtr in = n->getInputs()[j];

	if (in->getConnectedModule() != 0)
	  in->unPlug();
      }
		
    // remove the module from the sink list	  

    if (n->getOutputs().size() == 0 || !n->isDeterministic())
	m_sinks.remove(block);

    // remove it from the module set
    // the module control block should be deleted here by its autoptr
    m_modules.erase(it);
		
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Deleted Module # " << moduleID << std::endl;
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
	throw std::runtime_error("Module does not exist at "
				 "RuntimeSystem::setInputValue()");
      }

		
    ModuleControlBlockPtr block = it->second;
    IModule* n = block->module();

    if (inputIndex < 0 ||
        static_cast<unsigned int>(inputIndex) >= n->getInputs().size())
      {
	throw std::runtime_error("Input does not exist at "
				 "RuntimeSystem::setInputValue()");
      }


    block->setChanged(inputIndex);
		
		
    IModule::IInputPtr in = n->getInputs()[inputIndex];
		
    in->setValue(buf);
		
    if (cvr != 0)
      cvr->controlValueChanged(moduleID,inputIndex,buf);
  }


  namespace
  {
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
  }
		
  void RuntimeSystem::syncInputValue(int moduleID, int inputIndex,
				     IControlValueReceiver* cvr) const
  {
    if (!cvr)
      return;
		
    ControlBlockMap::const_iterator 
      it = m_modules.find(moduleID);
    if (it == m_modules.end())
      {
	throw std::runtime_error("Module does not exist at "
				 "RuntimeSystem::syncInputValue()");
      }
		
    DoSync sync(cvr);
		
    ModuleControlBlockPtr block = it->second;
		
    IModule* n = block->module();
		
    IModule::IInputPtr in = n->getInputs()[inputIndex];
		
    sync(in);
  }
	

  namespace
  {
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
  }
  
  void RuntimeSystem::synchronizeInputValues(IControlValueReceiver* cvr) const
  {
    std::for_each(m_modules.begin(), m_modules.end(), DoAllSync(cvr));
  }
	
} // end of namespace renderer
