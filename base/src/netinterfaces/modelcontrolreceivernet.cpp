#include "modelcontrolreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModelControlReceiverNet::ModelControlReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ModelControlReceiverNet::~ModelControlReceiverNet()
{}

void ModelControlReceiverNet::addModule( const std::string& moduleClassName )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(moduleClassName);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::connectModules( int moduleID1, int outputIndex, int moduleID2, int inputIndex )
{
	utils::Buffer temp_buf_(64);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID1 << ' '  << outputIndex << ' '  << moduleID2 << ' '  << inputIndex;
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::disconnectModules( int moduleID, int inputIndex )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID << ' '  << inputIndex;
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::deleteModule( int moduleID )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID;
	bs.flush();
	m_tagger->setTag( "0003" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::setModuleData( int moduleID, int type, const utils::Buffer& buf )
{
	utils::Buffer temp_buf_(48);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID << ' '  << type << ' '  << buf;
	bs.flush();
	m_tagger->setTag( "0004" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::unSetModuleData( int moduleID, int type )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID << ' '  << type;
	bs.flush();
	m_tagger->setTag( "0005" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::setEditGraphData( int type, const utils::Buffer& buf )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << type << ' '  << buf;
	bs.flush();
	m_tagger->setTag( "0006" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::unSetEditGraphData( int type )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << type;
	bs.flush();
	m_tagger->setTag( "0007" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::newGraph( const std::string& name )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(name);
	bs.flush();
	m_tagger->setTag( "0008" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::renameGraph( const std::string& graphID, const std::string& newName )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(newName);
	bs.flush();
	m_tagger->setTag( "0009" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::copyGraph( const std::string& graphID, const std::string& newName )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(newName);
	bs.flush();
	m_tagger->setTag( "0010" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::saveGraph( const std::string& graphID )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID);
	bs.flush();
	m_tagger->setTag( "0011" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::deleteGraph( const std::string& graphID )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID);
	bs.flush();
	m_tagger->setTag( "0012" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::synchronize(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0013" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::changeRenderedGraph( const std::string& graphID, const std::string& snapID )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID);
	bs.flush();
	m_tagger->setTag( "0014" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::changeEditGraph( const std::string& graphID, const std::string& snapID )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID);
	bs.flush();
	m_tagger->setTag( "0015" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::newControlValueSet( const std::string& graphID, const std::string& newSnapName )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(newSnapName);
	bs.flush();
	m_tagger->setTag( "0016" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::renameControlValueSet( const std::string& graphID, const std::string& snapID, const std::string& newSnapName )
{
	utils::Buffer temp_buf_(48);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID) << ' '  << utils::String(newSnapName);
	bs.flush();
	m_tagger->setTag( "0017" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::copyControlValueSet( const std::string& graphID, const std::string& snapID, const std::string& newSnapName )
{
	utils::Buffer temp_buf_(48);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID) << ' '  << utils::String(newSnapName);
	bs.flush();
	m_tagger->setTag( "0018" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::deleteControlValueSet( const std::string& graphID, const std::string& snapID )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(graphID) << ' '  << utils::String(snapID);
	bs.flush();
	m_tagger->setTag( "0019" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::setInputValue( int moduleID, int inputIndex, const utils::Buffer& buf )
{
	utils::Buffer temp_buf_(48);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID << ' '  << inputIndex << ' '  << buf;
	bs.flush();
	m_tagger->setTag( "0020" );
	m_tagger->send( temp_buf_ );

}

void ModelControlReceiverNet::syncInputValue( int moduleID, int inputIndex )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << moduleID << ' '  << inputIndex;
	bs.flush();
	m_tagger->setTag( "0021" );
	m_tagger->send( temp_buf_ );

}

