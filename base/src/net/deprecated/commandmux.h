#ifndef COMMAND_MUX_H
#define COMMAND_MUX_H

#include <map>
#include <string>
#include <stdexcept>

#include "icommandinterpreter.h"

namespace net
{

class ICommandListener;

/**
 * Verteilt eintreffende Befehle an registrierte Objekte. Für jeden Befehl
 * kann genau ein ICommandListener registriert werden. Dessen
 * commandReceived() Methode wird aufgerufen wenn der CommandMux
 * mittels commandReceived() einen Befehl erhält. Zusätzlich kann noch
 * ein DefaultListener gesetzt werden, der immer dann aufgerufen wird,
 * wenn kein zuständiger ICommandListener gefunden wird.
 */
class CommandMux : public ICommandInterpreter 
{
public:
  CommandMux();
  virtual ~CommandMux();

  /**
   * Registriert einen neuen ICommandListener.
   * @param ic Der ICommandListener der für die Bearbeitung des Befehls
   *           ic.getCommand() zuständig sein soll.
   * @exception std::runtime_error wird geworfen wenn für den Befehl
   *                               ic.getCommand() bereits ein Listener
   *                               registriert ist.
   */
  void addCommandListener(ICommandListener& cl) throw (std::runtime_error);

  /**
   * Setzt den Default-ICommandListener. Der wird aufgerufen, wenn für
   * einen Befehl kein passender ICommandListener gefunden wird.
   * Überschreibt einfach den alten Defaultlistener, falls vorhanden.
   * @param ic Der ICommandListener der für die Bearbeitung eines
   *           unbekannten Befehls zuständig sein soll.
   */
  void setDefaultCommandListener(ICommandInterpreter& cl);

  /**
   * //TODO
   */
  ICommandInterpreter* getDefaultCommandListener() const;

  /**
   * Entfernt einen ICommandListener. 
   * Wenn er nicht existiert (d.h. nie mit addCommandListener() registriert
   * wurde) passiert nix.
   * @param ic Der Listener der entfernt werden soll.
   */
  void removeCommandListener(ICommandListener& cl);

  /**
   * Über einen Aufruf dieser Methode ein neuer
   * Befehl an den CommandMux weitergeleitet. Der sucht daraufhin einen
   * entsprechenden ICommandListener und ruft den auf. Der Aufruf ist
   * blockieren, kehrt also erst zurück, wenn der Listener fertig ist.
   * @param command Der Befehl
   * @param data Die Parameter bzw. Daten für den Befehl.
   */
  virtual void commandReceived(const std::string& command,
	  const utils::Buffer&);

private:
  std::map<std::string,ICommandListener*> listener;

  ICommandInterpreter* defaultListener;
};

} //end of namespace
#endif
