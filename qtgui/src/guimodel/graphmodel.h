#ifndef INCLUDED_MODEL_CONTROL_WRAPPER_CONTROLLER_H
#define INCLUDED_MODEL_CONTROL_WRAPPER_CONTROLLER_H

#include <string>

#include "point.h"

#include "interfaces/imodelcontrolreceiver.h"
#include "interfaces/imoduleconstructiondumbreceiver.h"
#include "interfaces/imoduledatareceiver.h"

namespace utils {
  class Buffer;
}

namespace gui
{

  class IGraphView;

  class GraphModel :
    public IModuleConstructionDumbReceiver,
    public IModuleDataReceiver
  {
  private:

    GraphModel(const GraphModel&); // not impl.
    GraphModel& operator=(const GraphModel&); // not impl.
  
  public: 
    GraphModel(IModelControlReceiver& receiver);

    void registerGraphView(IGraphView& _view);
	
    virtual void moveModule(int id,const Point& pos);

    virtual void moduleAdded(const std::string& moduleClassName,int modID);
    virtual void modulesConnected(int moduleID1,int outputIndex,
				  int moduleID2,int inputIndex);  
    virtual void modulesDisconnected( int moduleID,int inputIndex);
    virtual void moduleDeleted(int moduleID);
    virtual void moduleDataSet(int nodeID,int type,const utils::Buffer&);
    virtual void moduleDataUnSet(int nodeID,int type);

    virtual void syncModuleStarted();
    virtual void syncModuleFinished();
    virtual void syncDataStarted();
    virtual void syncDataFinished();


  private:
    IModelControlReceiver* m_receiver;
    IGraphView* view;
  };

}
#endif
