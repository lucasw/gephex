#include "moduleclassnamesendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/imoduleclassnamereceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleClassNameSenderNet::ModuleClassNameSenderNet()
	 : m_rec(0) {}

void ModuleClassNameSenderNet::registerModuleClassNameReceiver(IModuleClassNameReceiver& r)
{
	m_rec = &r;
}

void ModuleClassNameSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ModuleClassNameSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String name;
		bs  >> name;
		m_rec->moduleClassNameExists( name );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ModuleClassName";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

