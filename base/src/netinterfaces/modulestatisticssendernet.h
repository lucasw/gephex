#ifndef INCLUDED_MODULESTATISTICS_SENDER_NET_H
#define INCLUDED_MODULESTATISTICS_SENDER_NET_H

#include <string>

#include "interfaces/imodulestatisticssender.h"

#include "net/itaginterpreter.h"

class ModuleStatisticsSenderNet : public IModuleStatisticsSender,
			      public net::ITagInterpreter<std::string>
{
public:
        ModuleStatisticsSenderNet();
	
	virtual void registerModuleStatisticsReceiver(IModuleStatisticsReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IModuleStatisticsReceiver* m_rec;
};

#endif
