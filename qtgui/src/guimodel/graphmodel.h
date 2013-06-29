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
