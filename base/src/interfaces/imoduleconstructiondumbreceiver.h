#ifndef INCLUDED_IMODULECONSTRUCTIONDUMBRECEIVER_H
#define INCLUDED_IMODULECONSTRUCTIONDUMBRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IModuleConstructionDumbReceiver
{
public:
  /**
   * F�gt dem Laufzeitsystem ein neues Modul des Typs moduleClassID hinzu.
   * @param moduleClassID Bestimmt die Art des Moduls das hinzugef�gt wird.
   * @param modID Eine eindeutige ID f�r das neue Modul.
   */
	virtual void moduleAdded( const std::string& moduleClassName, int modID ) = 0;

  /**
   * Verkn�pft den Eingang eines Moduls mit dem Ausgang eines anderen.
   * @param moduleID1 Die ID des Quellmoduls
   * @param outputIndex Der Index des Ausgangs des Quellmoduls
   * @param moduleID2 Die ID des Zielmoduls
   * @param inputIndex Der Index des eingangs des Zielmoduls
   * @exception runtime_error Wird geworfen wenn eine moduleID
   *            ung�ltig ist, die out/inputIndex ung�ltig ist oder der
   *            Typ des Ausgangs nicht mit dem des Eingangs �bereinstimmt.
   */
	virtual void modulesConnected( int moduleID1, int outputIndex, int moduleID2, int inputIndex ) = 0;

  /**
   * L�st die Verkn�pfung eines Eingangs von dem zu moduleID geh�rigen Modul.
   * @param moduleID Das Modul von dem ein Eingang gel�scht werden soll
   * @param inputIndex Der index des Eingangs
   * @exception runtime_error Wird geworfen wenn moduleID oder inputIndex
   *       ung�ltig ist.
   */
	virtual void modulesDisconnected( int moduleID, int inputIndex ) = 0;

  /**
   * L�scht ein Modul.
   * @param moduleID Das Modul das gel�scht wird
   */
	virtual void moduleDeleted( int moduleID ) = 0;

  /**
   * Teilt dem Receiver mit, dass die folgenden Aufrufe nur zur
   * Synchronisation dienen.
   *
   */
	virtual void syncModuleStarted(  ) = 0;

  /**
   * Teilt dem Receiver mit, dass die Synchronisation beendet ist.
   *
   */
	virtual void syncModuleFinished(  ) = 0;

};
#endif
