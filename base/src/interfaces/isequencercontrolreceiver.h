#ifndef INCLUDED_ISEQUENCERCONTROLRECEIVER_H
#define INCLUDED_ISEQUENCERCONTROLRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class ISequencerControlReceiver
{
public:
  /**
   * Neue Sequenz anlegen (per name)
   **/
	virtual void createSequence( const std::string& sequenceName ) = 0;

  /**
   *
   */
	virtual void saveSequence( const std::string& id ) = 0;

  /**
   * Aktive Sequenz ändern
   **/
	virtual void changeSequence( const std::string& id ) = 0;

  /**
   *
   */
	virtual void deleteSequence( const std::string& id ) = 0;

  /**
   *
   */   
	virtual void renameSequence( const std::string& id, const std::string& newName ) = 0;

  /**
   *	Sequenz starten
   */
	virtual void start(  ) = 0;

  /**
   *
   */
	virtual void pause(  ) = 0;

  /**
   *
   */
	virtual void stop(  ) = 0;

  /**
   *	Graph zu Sequenz hinzufügen..
   */
	virtual void addAction( const std::string& command, int time ) = 0;

  /**
   *
   */
	virtual void changeActionTime( int id, int newTime ) = 0;

  /**
   *	Graph aus sequenz löschen
   */
	virtual void deleteAction( int id ) = 0;

};
#endif
