#include "moduledatadispatcher.h"

namespace gui
{

	ModuleDataDispatcher::ModuleDataDispatcher(IModuleDataReceiver& zero_,
						 IModuleDataReceiver& high_)
		: zero(zero_), high(high_)
	{
	}

  void ModuleDataDispatcher::moduleDataSet(int modID, int type,
		const utils::Buffer& b)
  {
	  if (type < 1024)
		  zero.moduleDataSet(modID,type,b);
	  else
		  high.moduleDataSet(modID,type,b);
  }

  void ModuleDataDispatcher::moduleDataUnSet(int modID, int type)
  {
	  if (type < 1024)
		  zero.moduleDataUnSet(modID,type);
	  else
		  high.moduleDataUnSet(modID,type);
  }

  void ModuleDataDispatcher::syncDataStarted()
  {
    zero.syncDataStarted();
    high.syncDataStarted();
  }

  void ModuleDataDispatcher::syncDataFinished()
  {
    zero.syncDataFinished();
    high.syncDataFinished();
    //TODO
  }

} // end of namespace gui
