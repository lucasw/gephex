#include "enginecontrolreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
EngineControlReceiverNet::EngineControlReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

EngineControlReceiverNet::~EngineControlReceiverNet()
{}

void EngineControlReceiverNet::disconnect(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void EngineControlReceiverNet::shutDown(  )
{
	utils::Buffer temp_buf_((unsigned char*) "",1);
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

