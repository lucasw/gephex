#include "moduleclassnamereceivernet.h"

#include "net/itagger.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/bufferutils.h"
ModuleClassNameReceiverNet::ModuleClassNameReceiverNet(net::ITagger<std::string>& tagger)
	: m_tagger(&tagger)
{}

ModuleClassNameReceiverNet::~ModuleClassNameReceiverNet()
{}

void ModuleClassNameReceiverNet::moduleClassNameExists( const std::string& name )
{
	utils::Buffer temp_buf_(16);
	utils::OBufferStream bs(temp_buf_);
	bs << utils::String(name);
	bs.flush();
	m_tagger->setTag( "0000" );
	m_tagger->send( temp_buf_ );

}

