#ifndef _INCLUDED_IGRAPHVIEW_H__
#define _INCLUDED_IGRAPHVIEW_H__

namespace gui
{

class Point;

class IGraphView
{

public:
	virtual ~IGraphView() {}

	virtual void moduleAdded(const std::string& moduleClassName,int modID) = 0;
	
	virtual void modulesConnected(int moduleID1,int outputIndex,
								int moduleID2,int inputIndex) = 0;
	virtual void modulesDisconnected( int moduleID,int inputIndex) = 0;
	
	virtual void moduleDeleted(int moduleID) = 0;

	virtual void moduleMoved(int moduleID, const Point&) = 0;
};

}


#endif
