#ifndef INCLUDED_MODELCONTROLRECEIVERNET_H
#define INCLUDED_MODELCONTROLRECEIVERNET_H

#include "interfaces/imodelcontrolreceiver.h"

namespace net {
	template <typename Key>
	class ITagger;
}

class ModelControlReceiverNet : public IModelControlReceiver
{
private:
	net::ITagger<std::string>* m_tagger;

public:
	ModelControlReceiverNet(net::ITagger<std::string>& tagger);

	virtual ~ModelControlReceiverNet();

	void addModule( const std::string& moduleClassName );

	void connectModules( int moduleID1, int outputIndex, int moduleID2, int inputIndex );

	void disconnectModules( int moduleID, int inputIndex );

	void deleteModule( int moduleID );

	void setModuleData( int moduleID, int type, const utils::Buffer& buf );

	void unSetModuleData( int moduleID, int type );

	void setEditGraphData( int type, const utils::Buffer& buf );

	void unSetEditGraphData( int type );

	void newGraph( const std::string& name );

	void renameGraph( const std::string& graphID, const std::string& newName );

	void copyGraph( const std::string& graphID, const std::string& newName );

	void saveGraph( const std::string& graphID );

	void deleteGraph( const std::string& graphID );

	void synchronize(  );

	void changeRenderedGraph( const std::string& graphID, const std::string& snapID );

	void changeEditGraph( const std::string& graphID, const std::string& snapID );

	void newControlValueSet( const std::string& graphID, const std::string& newSnapName );

	void renameControlValueSet( const std::string& graphID, const std::string& snapID, const std::string& newSnapName );

	void copyControlValueSet( const std::string& graphID, const std::string& snapID, const std::string& newSnapName );

	void deleteControlValueSet( const std::string& graphID, const std::string& snapID );

	void setInputValue( int moduleID, int inputIndex, const utils::Buffer& buf );

	void syncInputValue( int moduleID, int inputIndex );

};
#endif
