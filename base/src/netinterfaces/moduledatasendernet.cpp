#include "moduledatasendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/imoduledatareceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleDataSenderNet::ModuleDataSenderNet()
	 : m_rec(0) {}

void ModuleDataSenderNet::registerModuleDataReceiver(IModuleDataReceiver& r)
{
	m_rec = &r;
}

void ModuleDataSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ModuleDataSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		int modID;
		int type;
		utils::Buffer buf;
		bs  >> modID >> type >> buf;
		m_rec->moduleDataSet( modID, type, buf );
	 }
	else 	if (command == "0001")
	 {
		int modID;
		int type;
		bs  >> modID >> type;
		m_rec->moduleDataUnSet( modID, type );
	 }
	else 	if (command == "0002")
	 {
		m_rec->syncDataStarted(  );
	 }
	else 	if (command == "0003")
	 {
		m_rec->syncDataFinished(  );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ModuleData";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

