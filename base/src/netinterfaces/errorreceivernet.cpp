#include "errorreceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ErrorReceiverNet::ErrorReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ErrorReceiverNet::~ErrorReceiverNet()
{}

void ErrorReceiverNet::error( const std::string& text )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(text);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

void ErrorReceiverNet::warning( const std::string& text )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(text);
	bs.flush();
	m_tagger->setTag( "0001" );
	m_tagger->send( temp_buf_ );

}

void ErrorReceiverNet::log( const std::string& text )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(text);
	bs.flush();
	m_tagger->setTag( "0002" );
	m_tagger->send( temp_buf_ );

}

