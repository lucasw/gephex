#ifndef INCLUDED_IMODULECONSTRUCTIONSMARTRECEIVER_H
#define INCLUDED_IMODULECONSTRUCTIONSMARTRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleConstructionSmartReceiver
{
public:
  /**
   * Fügt dem Laufzeitsystem ein neues Modul des Typs moduleClassID hinzu.
   * @param moduleClassID Bestimmt die Art des Moduls das hinzugefügt wird.
   * @param modID Eine eindeutige ID für das neue Modul.
   */
	virtual void moduleAdded( const std::string& graphName, const std::string& moduleClassName, int modID ) = 0;

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
	virtual void modulesConnected( const std::string& graphName, int moduleID1, int outputIndex, int moduleID2, int inputIndex ) = 0;

  /**
   * Löst die Verknüpfung eines Eingangs von dem zu moduleID gehörigen Modul.
   * @param moduleID Das Modul von dem ein Eingang gelöscht werden soll
   * @param inputIndex Der index des Eingangs
   * @exception runtime_error Wird geworfen wenn moduleID oder inputIndex
   *       ungültig ist.
   */
	virtual void modulesDisconnected( const std::string& graphName, int moduleID, int inputIndex ) = 0;

  /**
   * Löscht ein Modul.
   * @param moduleID Das Modul das gelöscht wird
   */
	virtual void moduleDeleted( const std::string& graphName, int moduleID ) = 0;

  /**
   *
   */
	virtual void newGraphCreated( const std::string& graphName ) = 0;

  /**
   *
   */
	virtual void graphChanged( const std::string& graphName ) = 0;

  /**
   *
   */
	virtual void graphDeleted( const std::string& graphName ) = 0;

};
#endif
