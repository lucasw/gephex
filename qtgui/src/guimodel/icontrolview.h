#ifndef INCLUDED_ICONTROL_VIEW_H
#define INCLUDED_ICONTROL_VIEW_H

#include <map>
#include <string>

namespace gui
{

  class Point;

  class IControlView
  {
  public:
    typedef std::map<std::string, std::string> ParamMap;

    virtual ~IControlView() {}

    virtual void controlAdded(int controlID, const std::string& name,
			      int nodeID,int inputIndex, 
			      const std::string& widgetType,
			      const ParamMap& params) = 0;

    virtual void controlMoved(int controlID, const Point& p) = 0;
    virtual void controlDeleted(int controlID) = 0;

    virtual void controlRenamed(int controlID, const std::string& name) = 0;
  };

}

#endif
