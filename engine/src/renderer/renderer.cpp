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

#include "renderer.h"

#if (ENGINE_VERBOSITY > 0)
#include <iostream>
#endif

#include <stdexcept>
#include <cassert>

#include "runtimesystem.h"

#include "modulefactory.h"
#include "typefactory.h"

#include "interfaces/irendererstatusreceiver.h"
#include "interfaces/icontrolvaluereceiver.h"
#include "interfaces/ismartcontrolvaluereceiver.h"
#include "interfaces/imodulestatisticsreceiver.h"
#include "interfaces/imodulestatisticssmartreceiver.h"

#include "utils/ilogger.h"

namespace renderer
{

  class ControlValueReceiverWrapper : public IControlValueReceiver
  {
  public:

    ControlValueReceiverWrapper(ISmartControlValueReceiver* rec,
				const std::string& graphID)
      : m_receiver(rec), m_graphID(graphID) {}

    virtual ~ControlValueReceiverWrapper() {}
	
    void controlValueChanged(int moduleID, int inputIndex,
			     const utils::Buffer& buf)
    {
      m_receiver->controlValueChanged(m_graphID,moduleID,
				      inputIndex, buf);
    }

    virtual void syncInputValuesStarted() 
    {
      m_receiver->syncInputValuesStarted(m_graphID);
    }

    virtual void syncInputValuesFinished() 
    {
      m_receiver->syncInputValuesFinished(m_graphID);
    }



  private:
    ISmartControlValueReceiver* m_receiver;
    std::string m_graphID;
  };

  class ModuleStatisticsReceiverWrapper : public IModuleStatisticsReceiver
  {
  public:

    ModuleStatisticsReceiverWrapper(IModuleStatisticsSmartReceiver* rec,
				    const std::string& graphID)
      : m_receiver(rec), m_graphID(graphID) {}

    virtual ~ModuleStatisticsReceiverWrapper() {}
	
		
    virtual void modExecTimeSignal(int nodeID, double execTime)
    {
      m_receiver->modExecTimeSignal(m_graphID,nodeID, execTime);
    }

  private:
    IModuleStatisticsSmartReceiver* m_receiver;
    std::string m_graphID;
  };


  Renderer::Renderer(utils::AutoPtr<utils::ILogger>& logger)
    : isStarted(false), activeGraph(0),  cvr(0), msr(0),
      rendererStatusReceiver(0), moduleFactory(new ModuleFactory()),
      typeFactory(new TypeFactory()), m_logger(logger)
  {
  }

  Renderer::~Renderer() 
  {
  }

  void Renderer::registerSmartControlValueReceiver(ISmartControlValueReceiver& r)
  {
    cvr = &r;
  }

  void Renderer::registerModuleStatisticsSmartReceiver(IModuleStatisticsSmartReceiver& r)
  {
    msr = &r;
  }

  void Renderer::registerRendererStatusReceiver(IRendererStatusReceiver& r)
  {
    rendererStatusReceiver=&r;
  }

  void Renderer::newGraphCreated(const std::string& graphID)
  {
    RuntimeSystemMap::const_iterator it = graphs.find(graphID);
    if (it!=graphs.end())
      throw std::runtime_error("name already exists "
			       "(Renderer::newGraphCreated)");
    graphs[graphID] 
      = utils::AutoPtr<RuntimeSystem>(new RuntimeSystem(*moduleFactory,
							*typeFactory, m_logger));

  }

  /*  void Renderer::graphRenamed(const std::string& graphID,
			      const std::string& newGraphName)
  {
    RuntimeSystemMap::iterator it = graphs.find(graphID);
    if (it == graphs.end())
      throw std::runtime_error("name doesnt exist (Renderer::graphRenamed)");

    graphs[newGraphName] = it->second;
    graphs.erase(it);

    if (graphID == activeGraphName)
      activeGraphName = newGraphName;
  }
  */
  void Renderer::graphChanged(const std::string& graphID)
  {
    RuntimeSystemMap::const_iterator it = graphs.find(graphID);
    if (it == graphs.end())
      throw std::runtime_error("name doesnt exist(Renderer::graphChanged)");

    if (rendererStatusReceiver!=0)
      rendererStatusReceiver->renderedGraphChanged(graphID);

    activeGraph = it->second;
    activeGraphName = graphID;
  }

  void Renderer::graphDeleted(const std::string& graphID)
  {
	  RuntimeSystemMap::iterator it = graphs.find(graphID);

	  if (it == graphs.end())
	    {
	      m_logger->error("Renderer::graphDeleted",
			      "Graph with id = '" + graphID +
			      "' does not exist.");
	      return;
	    }

	  if (activeGraphName == graphID)
	  {
            activeGraph = utils::AutoPtr<RuntimeSystem>(0);
            activeGraphName = "";
	  }

	  graphs.erase(it);
  }

  bool Renderer::run()
  {
    if (activeGraph != 0 && isStarted)
      {
	/*if (activeGraph==0)
	  {
	    stop();
	    throw std::runtime_error("no active graph(Renderer::run)");
	  }*/
	ControlValueReceiverWrapper wrapper(cvr,activeGraphName);
	ModuleStatisticsReceiverWrapper wrapper2(msr,activeGraphName);
	activeGraph->update(&wrapper,&wrapper2);
      }

    return true;
  }

  void Renderer::start()
  {
    /*if (activeGraph==0)
      {
	stop();
	throw std::runtime_error("no active graph(Renderer::start)");
      }*/
    if (rendererStatusReceiver != 0)
      rendererStatusReceiver->started();

    isStarted = true;

#if (ENGINE_VERBOSITY > 0)
    std::cout << "renderer start called" << std::endl;
#endif
  }

  void Renderer::stop()
  {
    if (rendererStatusReceiver != 0)
      rendererStatusReceiver->stopped();

    isStarted = false;
  }

  utils::AutoPtr<RuntimeSystem> 
  Renderer::find(const std::string& graphID) const
  {
    RuntimeSystemMap::const_iterator it = graphs.find(graphID);
    if (it == graphs.end())
      throw std::runtime_error("unknown GraphName(Renderer::find)");

    return it->second;
  }

  void Renderer::moduleClassLoaded(const std::string& moduleClassName,
				   const IModuleClass& moduleClass)
  {
    moduleFactory->registerModuleClass(moduleClassName,moduleClass);
  }

  void Renderer::moduleClassUnloaded(const std::string& moduleClassName)
  {
    moduleFactory->unregisterModuleClass(moduleClassName);
  }

  void Renderer::typeClassLoaded(int typeClassID,const ITypeClass& typeClass)
  {
    typeFactory->registerTypeClass(typeClassID,typeClass);
  }

  void Renderer::typeClassUnloaded(int typeClassID)
  {
    //TODO
  }

  void Renderer::moduleAdded(const std::string& graphID,
			     const std::string& moduleClassName, int moduleID)
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Renderer::moduleAdded: "<< "graphID:" << graphID 
	      << " moduleClassName: " << moduleClassName << " moduleID: " 
	      << moduleID << std::endl;
#endif
    find(graphID)->addModule(moduleClassName,moduleID);
  }

  void Renderer::modulesConnected(const std::string& graphID, int moduleID1,
				  int outputIndex,int moduleID2,int inputIndex)
  {
#if (ENGINE_VERBOSITY > 0)
    std::cout << "Renderer::modulesConnected: "<< "graphID" << graphID 
	      << " moduleID1: " << moduleID1 << " outputIndex: " 
	      << outputIndex << " moduleID2:" << moduleID2 
	      << " inputIndex: " << inputIndex << std::endl;
#endif

    find(graphID)->connect(moduleID1,outputIndex,moduleID2,inputIndex);
  }

  void Renderer::modulesDisconnected(const std::string& graphID,
				     int moduleID,int inputIndex)
  {
    find(graphID)->disconnect(moduleID,inputIndex);
  }

  void Renderer::moduleDeleted(const std::string& graphID, int moduleID)
  {
    find(graphID)->deleteModule(moduleID);
  }

  void Renderer::setInputValue(const std::string& graphID,
			       int nodeID,int inputIndex,
			       const utils::Buffer& buf)
  {
    ControlValueReceiverWrapper wrapper(cvr,graphID);
    find(graphID)->setInputValue(nodeID,inputIndex,buf,&wrapper);
  }

  void Renderer::syncInputValue(const std::string& graphID,
				int nodeID, int inputIndex)
  {
    ControlValueReceiverWrapper wrapper(cvr,graphID);
    find(graphID)->syncInputValue(nodeID, inputIndex, &wrapper);
  }

  void Renderer::synchronize()
  {
  	if (rendererStatusReceiver!=0)
	{
      rendererStatusReceiver->renderedGraphChanged(activeGraphName);
	  if (isStarted)
		  rendererStatusReceiver->started();
	  else
		  rendererStatusReceiver->stopped();
	}
  }

  void Renderer::synchronizeInputValues(const std::string& graphID)
  {
    cvr->syncInputValuesStarted(graphID);

    ControlValueReceiverWrapper wrapper(cvr,graphID);
    find(graphID)->synchronizeInputValues(&wrapper);

    cvr->syncInputValuesFinished(graphID);
  }

}
