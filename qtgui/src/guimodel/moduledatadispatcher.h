#ifndef INCLUDED_MODULE_DATA_DISPATCHER_H
#define INCLUDED_MODULE_DATA_DISPATCHER_H

#include "interfaces/imoduledatareceiver.h"

namespace gui
{

class ModuleDataDispatcher : public IModuleDataReceiver
{
public:
	ModuleDataDispatcher(IModuleDataReceiver& zero_,
						 IModuleDataReceiver& high_);

  virtual void moduleDataSet(int modID, int type, const utils::Buffer&);

  virtual void moduleDataUnSet(int modID, int type);

  virtual void syncDataStarted();
  virtual void syncDataFinished();

private:
	IModuleDataReceiver& zero;
	IModuleDataReceiver& high;
};

}

#endif
