#include "controlvaluedispatcher.h"

#include <sstream>
#include <stdexcept>
#include <cassert>

#include "interfaces/imodelcontrolreceiver.h"
#include "utils/buffer.h"

namespace gui
{

  ControlValueDispatcher::ControlValueDispatcher(IModelControlReceiver& model)
	  : m_model(&model)
  {
  }

  ControlValueDispatcher::~ControlValueDispatcher()
  {
  }

  void ControlValueDispatcher::registerValueReceiver(int nodeID,int inputIndex,
						    IControlValueReceiver& r)
  {
    std::list<IControlValueReceiver*>& l = this->find(nodeID,inputIndex);
	m_model->syncInputValue(nodeID,inputIndex);
    l.push_back(&r);
  }

  void ControlValueDispatcher::unregisterValueReceiver(int nodeID,
						       int inputIndex,
						       IControlValueReceiver&r)
  {
    std::list<IControlValueReceiver*>& l = this->find(nodeID,inputIndex);
	
    l.remove(&r);
  }
  
  void ControlValueDispatcher::controlValueChanged(int nodeID,int inputIndex,
						   const utils::Buffer& b)
  {
    std::list<IControlValueReceiver*>& l = this->find(nodeID,inputIndex);
    
    for (std::list<IControlValueReceiver*>::iterator it = l.begin();
	 it != l.end(); ++it)
      {
		 IControlValueReceiver* rec = *it;
		 rec->controlValueChanged(nodeID,inputIndex,b);
      }
  }


  std::list<IControlValueReceiver*>& ControlValueDispatcher::find(int nodeID, 
								  int inIndex)
  {
    std::map<std::pair<int,int>, std::list<IControlValueReceiver*> >::iterator
      it = receivers.find(std::make_pair(nodeID,inIndex));

    if (it == receivers.end())
      {
	receivers[std::make_pair(nodeID,inIndex)] 
	  = std::list<IControlValueReceiver*>();

	it = receivers.find(std::make_pair(nodeID,inIndex));
      }

    assert(it != receivers.end());

    return it->second;
  }

  void ControlValueDispatcher::syncInputValuesStarted()
  {
    //TODO
  }

	void ControlValueDispatcher::syncInputValuesFinished()
  {
    //TODO
  }


}
