#include "modelcontrolsendernet.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "interfaces/imodelcontrolreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModelControlSenderNet::ModelControlSenderNet()
	 : m_rec(0) {}

void ModelControlSenderNet::registerModelControlReceiver(IModelControlReceiver& r)
{
	m_rec = &r;
}

void ModelControlSenderNet::dataReceived(const std::string& command,const utils::Buffer& buf)
{
	if (!m_rec) 
	{
		std::cerr << "Receiver not set at "
		 "ModelControlSenderNet::commandReceived()" 
		  << std::endl;
		return;
	}

	utils::IBufferStream bs(buf);
	if (command == "0000")
	 {
		utils::String moduleClassName;
		bs  >> moduleClassName;
		m_rec->addModule( moduleClassName );
	 }
	else 	if (command == "0001")
	 {
		int moduleID1;
		int outputIndex;
		int moduleID2;
		int inputIndex;
		bs  >> moduleID1 >> outputIndex >> moduleID2 >> inputIndex;
		m_rec->connectModules( moduleID1, outputIndex, moduleID2, inputIndex );
	 }
	else 	if (command == "0002")
	 {
		int moduleID;
		int inputIndex;
		bs  >> moduleID >> inputIndex;
		m_rec->disconnectModules( moduleID, inputIndex );
	 }
	else 	if (command == "0003")
	 {
		int moduleID;
		bs  >> moduleID;
		m_rec->deleteModule( moduleID );
	 }
	else 	if (command == "0004")
	 {
		int moduleID;
		int type;
		utils::Buffer buf;
		bs  >> moduleID >> type >> buf;
		m_rec->setModuleData( moduleID, type, buf );
	 }
	else 	if (command == "0005")
	 {
		int moduleID;
		int type;
		bs  >> moduleID >> type;
		m_rec->unSetModuleData( moduleID, type );
	 }
	else 	if (command == "0006")
	 {
		utils::String name;
		bs  >> name;
		m_rec->newGraph( name );
	 }
	else 	if (command == "0007")
	 {
		utils::String graphID;
		utils::String newName;
		bs  >> graphID >> newName;
		m_rec->renameGraph( graphID, newName );
	 }
	else 	if (command == "0008")
	 {
		utils::String graphID;
		utils::String newName;
		bs  >> graphID >> newName;
		m_rec->copyGraph( graphID, newName );
	 }
	else 	if (command == "0009")
	 {
		utils::String graphID;
		bs  >> graphID;
		m_rec->saveGraph( graphID );
	 }
	else 	if (command == "0010")
	 {
		utils::String graphID;
		bs  >> graphID;
		m_rec->deleteGraph( graphID );
	 }
	else 	if (command == "0011")
	 {
		m_rec->synchronize(  );
	 }
	else 	if (command == "0012")
	 {
		utils::String graphID;
		utils::String snapID;
		bs  >> graphID >> snapID;
		m_rec->changeRenderedGraph( graphID, snapID );
	 }
	else 	if (command == "0013")
	 {
		utils::String graphID;
		utils::String snapID;
		bs  >> graphID >> snapID;
		m_rec->changeEditGraph( graphID, snapID );
	 }
	else 	if (command == "0014")
	 {
		utils::String graphID;
		utils::String newSnapName;
		bs  >> graphID >> newSnapName;
		m_rec->newControlValueSet( graphID, newSnapName );
	 }
	else 	if (command == "0015")
	 {
		utils::String graphID;
		utils::String snapID;
		utils::String newSnapName;
		bs  >> graphID >> snapID >> newSnapName;
		m_rec->renameControlValueSet( graphID, snapID, newSnapName );
	 }
	else 	if (command == "0016")
	 {
		utils::String graphID;
		utils::String snapID;
		utils::String newSnapName;
		bs  >> graphID >> snapID >> newSnapName;
		m_rec->copyControlValueSet( graphID, snapID, newSnapName );
	 }
	else 	if (command == "0017")
	 {
		utils::String graphID;
		utils::String snapID;
		bs  >> graphID >> snapID;
		m_rec->deleteControlValueSet( graphID, snapID );
	 }
	else 	if (command == "0018")
	 {
		int moduleID;
		int inputIndex;
		utils::Buffer buf;
		bs  >> moduleID >> inputIndex >> buf;
		m_rec->setInputValue( moduleID, inputIndex, buf );
	 }
	else 	if (command == "0019")
	 {
		int moduleID;
		int inputIndex;
		bs  >> moduleID >> inputIndex;
		m_rec->syncInputValue( moduleID, inputIndex );
	 }
	 else
	 {
		std::ostringstream stream;
		stream << "Laenge: " << command.length() << std::endl;
		stream << "Received invalid command: <" 
			<< command << "> at ModelControl";
		stream << std::endl << "Haeh?" << std::endl;
		stream.flush();
		throw std::runtime_error(stream.str().c_str());
	 }

}

