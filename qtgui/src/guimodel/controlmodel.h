#ifndef INCLUDED_CONTROL_MODEL_H_
#define INCLUDED_CONTROL_MODEL_H_

#include <string>
#include <map>


#include "point.h"

#include "interfaces/imoduledatareceiver.h"

#include "utils/autoptr.h"


namespace utils {
  class Buffer;
}

class IModelControlReceiver;

namespace gui
{

  class IControlView;
  class IControlConnectView;
  class ControlElement;
  class Point;

  class ControlModel : public IModuleDataReceiver
  {
  public:
    typedef std::map<std::string, std::string> ParamMap;
    ControlModel(IModelControlReceiver& );
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

    //--------------------------------------------------------------------

    virtual void moduleDataSet(int moduleID, int type,
			       const utils::Buffer& buf);

    virtual void moduleDataUnSet(int moduleID, int type);

    virtual void syncDataStarted();
    virtual void syncDataFinished();

  private:
    int lastControlID;
    typedef std::map<int,utils::AutoPtr<ControlElement> > ControlMap;
    ControlMap controls; 
    IControlView* view;
    IControlConnectView* connectView;
    IModelControlReceiver* mcr;
  };

}

#endif
