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

#ifndef INCLUDED_CONTROL_MODEL_H_
#define INCLUDED_CONTROL_MODEL_H_

#include <string>
#include <map>


#include "point.h"

#include "interfaces/imoduledatareceiver.h"
#include "interfaces/igraphdatareceiver.h"

#include "utils/autoptr.h"

class IErrorReceiver;

namespace utils {
  class Buffer;
}

class IModelControlReceiver;

namespace gui
{

  class IControlView;
  class IControlConnectView;
  class ControlElement;
  class LabelElement;
  class Point;

  class ControlModel : public IModuleDataReceiver,
                       public IGraphDataReceiver
  {
  public:
    typedef std::map<std::string, std::string> ParamMap;
    ControlModel(IModelControlReceiver&,
                 IErrorReceiver& log);
    virtual ~ControlModel();

    void registerControlView(IControlView&);
    void registerControlConnectView(IControlConnectView&);

    virtual void addControl(const Point& pos, const std::string& name,
			    int nodeID, int inputIndex,
			    const std::string& widgetType,
			    const ParamMap& params);
	
    virtual void delControl(int controlID);

    virtual void moveControl(int controlID, const Point& pos);

    virtual void renameControl(int controlID, const std::string& name);

    virtual void addLabel(const Point& pos, const std::string& text);
    virtual void moveLabel(int labelID, const Point& pos);
    virtual void delLabel(int labelID);

    //--------------------------------------------------------------------

    virtual void moduleDataSet(int moduleID, int type,
			       const utils::Buffer& buf);

    virtual void moduleDataUnSet(int moduleID, int type);

    virtual void syncDataStarted();
    virtual void syncDataFinished();

    virtual void graphDataSet(int type, const utils::Buffer& buf);

    virtual void graphDataUnSet(int type);

    virtual void syncGraphDataStarted();
    virtual void syncGraphDataFinished();

  private:
    int lastControlID;
    int lastLabelID;
    typedef std::map<int,utils::AutoPtr<ControlElement> > ControlMap;
    typedef std::map<int,utils::AutoPtr<LabelElement> > LabelMap;
    ControlMap controls; 
    LabelMap labels;
    IControlView* view;
    IControlConnectView* connectView;
    IModelControlReceiver* mcr;
    IErrorReceiver& m_log;
  };

}

#endif
