#ifndef INCLUDED_IMODELCONTROLRECEIVER_H
#define INCLUDED_IMODELCONTROLRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModelControlReceiver
{
public:
	/**
	* Fügt dem Laufzeitsystem ein neues Modul des Typs moduleClassID hinzu.
	* @param moduleClassName Bestimmt die Art des Moduls das hinzugefügt wird.
	* @param modID Eine eindeutige ID für das neue Modul.
	*/
	virtual void addModule( const std::string& moduleClassName ) = 0;

	/**
	* Verknüpft den Eingang eines Moduls mit dem Ausgang eines anderen.
	* @param moduleID1 Die ID des Quellmoduls
	* @param outputIndex Der Index des Ausgangs des Quellmoduls
	* @param moduleID2 Die ID des Zielmoduls
	* @param inputIndex Der Index des eingangs des Zielmoduls
	* @exception runtime_error Wird geworfen wenn eine moduleID
	*            ungültig ist, die out/inputIndex ungültig ist oder der
	*            Typ des Ausgangs nicht mit dem des Eingangs übereinstimmt.
	*/
	virtual void connectModules( int moduleID1, int outputIndex, int moduleID2, int inputIndex ) = 0;

	/**
	* Löst die Verknüpfung eines Eingangs von dem zu moduleID gehörigen Modul.
	* @param moduleID Das Modul von dem ein Eingang gelöscht werden soll
	* @param inputIndex Der index des Eingangs
	* @exception runtime_error Wird geworfen wenn moduleID oder inputIndex
	*       ungültig ist.
	*/
	virtual void disconnectModules( int moduleID, int inputIndex ) = 0;

	/**
	* Löscht ein Modul.
	* @param moduleID Das Modul das gelöscht wird
	*/
	virtual void deleteModule( int moduleID ) = 0;

	/**
	*
	*/
	virtual void setModuleData( int moduleID, int type, const utils::Buffer& buf ) = 0;

	/**
	*
	*/
	virtual void unSetModuleData( int moduleID, int type ) = 0;

        /**
         */
	virtual void setEditGraphData( int type, const utils::Buffer& buf ) = 0;

        /**
         */
	virtual void unSetEditGraphData( int type ) = 0;

	/**
	* legt neuen gr an, alter graph bleibt aktiv
	*/
	virtual void newGraph( const std::string& name ) = 0;

	/**
	*
	*/
	virtual void renameGraph( const std::string& graphID, const std::string& newName ) = 0;

	/**
	*
	*/
	virtual void copyGraph( const std::string& graphID, const std::string& newName ) = 0;

	/**
	*
	*/
	virtual void saveGraph( const std::string& graphID ) = 0;

	/**
	*
	*/
	virtual void deleteGraph( const std::string& graphID ) = 0;

	/**
	* Veranlasst das Model dazu alle Receiver zu synchronisieren.
	* Dazu wird zuerst syncStarted() der Receiver aufgerufen.
	* Dann wird den Receivern über moduleAdded(), modulesConnected(),...
	* Aufrufe der gesamte bestehende Graph mitgeteilt.
	* Beendet wird die Synchronisation mit syncFinished().
	*/
	virtual void synchronize(  ) = 0;

	/**
	*
	*/	
	virtual void changeRenderedGraph( const std::string& graphID, const std::string& snapID ) = 0;

	/**
	*
	*/
	virtual void changeEditGraph( const std::string& graphID, const std::string& snapID ) = 0;

	/**
	*
	*/	
	virtual void newControlValueSet( const std::string& graphID, const std::string& newSnapName ) = 0;

	/**
	*
	*/
	virtual void renameControlValueSet( const std::string& graphID, const std::string& snapID, const std::string& newSnapName ) = 0;

	/**
	*
	*/
	virtual void copyControlValueSet( const std::string& graphID, const std::string& snapID, const std::string& newSnapName ) = 0;

	/**
	*
	*/
	virtual void deleteControlValueSet( const std::string& graphID, const std::string& snapID ) = 0;

	/**
	*
	*/	
	virtual void setInputValue( int moduleID, int inputIndex, const utils::Buffer& buf ) = 0;

	/**
	*
	*/
	virtual void syncInputValue( int moduleID, int inputIndex ) = 0;

};
#endif
