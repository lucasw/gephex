#include "moduleconstructiondumbsendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/imoduleconstructiondumbreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleConstructionDumbSenderNet::ModuleConstructionDumbSenderNet()
	 : m_rec(0) {}

void ModuleConstructionDumbSenderNet::registerModuleConstructionDumbReceiver(IModuleConstructionDumbReceiver& r)
{
	m_rec = &r;
}

void ModuleConstructionDumbSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ModuleConstructionDumbSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String moduleClassName;
		int modID;
		bs  >> moduleClassName >> modID;
		m_rec->moduleAdded( moduleClassName, modID );
	 }
	else 	if (command == "0001")
	 {
		int moduleID1;
		int outputIndex;
		int moduleID2;
		int inputIndex;
		bs  >> moduleID1 >> outputIndex >> moduleID2 >> inputIndex;
		m_rec->modulesConnected( moduleID1, outputIndex, moduleID2, inputIndex );
	 }
	else 	if (command == "0002")
	 {
		int moduleID;
		int inputIndex;
		bs  >> moduleID >> inputIndex;
		m_rec->modulesDisconnected( moduleID, inputIndex );
	 }
	else 	if (command == "0003")
	 {
		int moduleID;
		bs  >> moduleID;
		m_rec->moduleDeleted( moduleID );
	 }
	else 	if (command == "0004")
	 {
		m_rec->syncModuleStarted(  );
	 }
	else 	if (command == "0005")
	 {
		m_rec->syncModuleFinished(  );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ModuleConstructionDumb";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

