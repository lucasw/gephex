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
    l.push_back(&r);

    m_model->syncInputValue(nodeID,inputIndex);
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

  void ControlValueDispatcher::clear()
  {
    receivers.clear();
  }
}

