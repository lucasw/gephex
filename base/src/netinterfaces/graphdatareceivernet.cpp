#include "graphdatareceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
GraphDataReceiverNet::GraphDataReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

GraphDataReceiverNet::~GraphDataReceiverNet()
{}

void GraphDataReceiverNet::graphDataSet( int type, const utils::Buffer& buf )
{
	utils::Buffer temp_buf_(32);
	utils::OBufferStream bs(temp_buf_);
	bs << type << ' '  << buf;
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void GraphDataReceiverNet::graphDataUnSet( int type )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << type;
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void GraphDataReceiverNet::syncGraphDataStarted(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

void GraphDataReceiverNet::syncGraphDataFinished(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0003" );
	m_tagger->send( temp_buf_ );

}

