#include "moduleclassinfosendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/imoduleclassinforeceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleClassInfoSenderNet::ModuleClassInfoSenderNet()
	 : m_rec(0) {}

void ModuleClassInfoSenderNet::registerModuleClassInfoReceiver(IModuleClassInfoReceiver& r)
{
	m_rec = &r;
}

void ModuleClassInfoSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ModuleClassInfoSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String moduleClassName;
		utils::Buffer buf;
		bs  >> moduleClassName >> buf;
		m_rec->moduleClassLoaded( moduleClassName, buf );
	 }
	else 	if (command == "0001")
	 {
		utils::String moduleClassID;
		bs  >> moduleClassID;
		m_rec->moduleClassUnloaded( moduleClassID );
	 }
	else 	if (command == "0002")
	 {
		m_rec->syncStarted(  );
	 }
	else 	if (command == "0003")
	 {
		m_rec->syncFinished(  );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ModuleClassInfo";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

