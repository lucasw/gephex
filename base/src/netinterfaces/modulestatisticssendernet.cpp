#include "modulestatisticssendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/imodulestatisticsreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleStatisticsSenderNet::ModuleStatisticsSenderNet()
	 : m_rec(0) {}

void ModuleStatisticsSenderNet::registerModuleStatisticsReceiver(IModuleStatisticsReceiver& r)
{
	m_rec = &r;
}

void ModuleStatisticsSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ModuleStatisticsSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		int nodeID;
		double execTime;
		bs  >> nodeID >> execTime;
		m_rec->modExecTimeSignal( nodeID, execTime );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ModuleStatistics";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

