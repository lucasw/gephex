#include "graphmodel.h"

#include "igraphview.h"

#include "utils/buffer.h"
#include "utils/bufferstream.h"

namespace gui
{
  // the type of data for IModelControlReceiver->setModuleData().
  // 0 is used for the position. 1 to 1023 are free. 1024 ... are
  // used for controls.
  namespace datatype
  {    
    enum { POINT = 0 };
  }

  namespace
  {
    utils::Buffer point2Buffer(const Point& p)
    {
      utils::Buffer ob(32);
      utils::OBufferStream os(ob);
      os << p;
      os.flush();
      return ob;
    }
  }

  GraphModel::GraphModel(IModelControlReceiver& receiver)
    : m_receiver(&receiver), view(0)
  {
  }

  void GraphModel::registerGraphView(IGraphView& _view)
  {
    view = &_view;
  }

  void GraphModel::moveModule(int id,const Point& pos)
  {
    m_receiver->setModuleData(id,datatype::POINT,
			      point2Buffer(pos));
  }

  void GraphModel::moduleAdded(const std::string& moduleClassName,int modID)
  {
    view->moduleAdded(moduleClassName,modID);
  }

  void GraphModel::modulesConnected(int moduleID1,int outputIndex,
				    int moduleID2,int inputIndex)
  {
    view->modulesConnected(moduleID1,outputIndex,moduleID2,inputIndex);
  }

  void GraphModel::modulesDisconnected( int moduleID,int inputIndex)
  {
    view->modulesDisconnected(moduleID,inputIndex);
  }

  void GraphModel::moduleDeleted(int moduleID)
  {
    view->moduleDeleted(moduleID);
  }

  void GraphModel::moduleDataSet(int nodeID,int type,const utils::Buffer& b)
  {
    /*std::cout << "moduleDataSet: " << "nodeID = " << nodeID
      << ", type = " << type << ", buf = " << b.getPtr() 
      << std::endl;*/
    if (type != datatype::POINT)
      return;
	  
    int x,y;
    utils::IBufferStream is(b);
	  
    is >> x >> y;
	  
    view->moduleMoved(nodeID,Point(x,y));
  }

  void GraphModel::moduleDataUnSet(int nodeID,int type)
  {
    /*std::cout << "moduleDataUnSet: " << "nodeID = " << nodeID
      << ", type = " << type << std::endl;*/
  }

  void GraphModel::syncModuleStarted()
  {
    // TODO
  }

  void GraphModel::syncModuleFinished()
  {
    //TODO
  }
  
  void GraphModel::syncDataStarted()
  {
    //TODO
  }
  
  void GraphModel::syncDataFinished()
  {
    //TODO
  }

}
