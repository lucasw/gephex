#ifndef INCLUDED_FILE_PROTOCOL_H
#define INCLUDED_FILE_PROTOCOL_H

#include <string>
#include <stdexcept>

#include "icommandlistener.h"

namespace net 
{

class INetProtocol;

/**
 * Definiert ein einfaches Dateiuebertragungsprotokoll. Setzt auf INetProtocol
 * auf. Dateien werden in Bloecke zerhackt, verschickt und am anderen Ende
 * wieder zusammengesetzt.
 * Wenn eine Datei empfangen wurde wird die commandReceived() Methode 
 * eines ICommandInterpreters aufgerufen. Das Kommando ist "frec" und
 * data ist der Dateiname.
 * Um eine Datei empfangen zu koennen muessen alle Pakete mit dem
 * Kommande "file" an das FileProtocol weitergeleitet werden.
 * Dazu kann er z.B. einfach in einen CommandMux eingehaengt werden.
 * Beispielcode:
 * <code>
 * CommandMux cmux;
 * NetProtocol np(cmux);
 * NetStream ns(12345, np, false);
 * np.setSender(ns);
 *
 * FileProtocol fp(np,cmux);
 *
 * cmux.addCommandListener(fp);
 * </code>
 */
class FileProtocol : public ICommandListener
{
private:

	FileProtocol(const FileProtocol&); // not impl.
	const FileProtocol& operator=(const FileProtocol&); // not impl.
public:
  /**
   * Erzeugt eine neues FileProtocol.
   * @param np Das INetProtocol, ueber das die Dateien verschickt
   *           werden.
   * @param fileReceiver Der ICommandInterpreter, der benachrichtigt
   *                     wird wenn eine Datei angekommen ist.
   */
  FileProtocol(INetProtocol& np, ICommandInterpreter& fileReceiver);

  
  virtual ~FileProtocol();

  /**
   * Verschickt eine Datei.
   * @param filename Der Name der Datei.
   * @exception std::runtime_error Wird geworfen wenn die Datei nicht
   *                      geoeffnet werden kann oder wenn beim lesen
   *                      aus der Datei ein Fehler auftritt.
   */
  virtual void send(const std::string& filename)
    throw (std::runtime_error);

  /**
   * Mit dieser Nachricht wird dem FileProtocol mitgeteilt, dass ein
   * weiterer Teil der Datei angekommen ist.
   */
  virtual void commandReceived(const std::string& command,
			       const utils::Buffer& buf);

  /**
   * Gibt "file" zurueck.
   */
  virtual std::string getCommand() const;

private:
  INetProtocol* m_netProtocol;
  ICommandInterpreter* m_fileReceiver;
};

} //end of namespace

#endif

