#include "moduledatareceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleDataReceiverNet::ModuleDataReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ModuleDataReceiverNet::~ModuleDataReceiverNet()
{}

void ModuleDataReceiverNet::moduleDataSet( int modID, int type, const utils::Buffer& buf )
{
	utils::Buffer temp_buf_(48);
	utils::OBufferStream bs(temp_buf_);
	bs << modID << ' '  << type << ' '  << buf;
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void ModuleDataReceiverNet::moduleDataUnSet( int modID, int type )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << modID << ' '  << type;
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void ModuleDataReceiverNet::syncDataStarted(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

void ModuleDataReceiverNet::syncDataFinished(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0003" );
	m_tagger->send( temp_buf_ );

}

