#ifndef NET_PROTOCOL_H
#define NET_PROTOCOL_H

#include <map>
#include <string>
#include <stdexcept>

#include "inetprotocol.h"
#include "idatalistener.h"

namespace utils {
  class Buffer;
}

namespace net
{

class ICommandInterpreter;
class ISender;

/**
 * Kapselt das Protokoll mit dem Daten zwischen Engine und GUI bzw. Konsole
 * ausgetauscht werden. Dabei werden die Daten in einen Header verpackt,
 * der im wesentlichen einen Befehl und die Länge der Daten enthält.
 * Eine Instanz von NetProtocol braucht einen ICommandInterpreter, an
 * den sie die empfangenen Befehle weiterversendet.
 * Daten erhält sie über dataReceived() z.B. direkt vom Netzwerk.
 * Diese Methode verarbeitet die Daten und ruft den ICommandInterpreter
 * auf, falls schon (mind. 1) ganzes Paket da ist. Der Aufruf von
 * dataReceived() ist blockierend.
 * Zum versenden der Nachrichten verwendet das NetProtocol ein Objekt der
 * Klasse ISender.
 */
class NetProtocol : public INetProtocol, public IDataListener
{
public:
  NetProtocol();
  NetProtocol(ICommandInterpreter&);

  virtual ~NetProtocol();

  void setCommandInterpreter(ICommandInterpreter& interpreter);

  /**
   * Setzt den Sender über den Befehle verschickt werden. Muss aufgerufen
   * werden bevor sendCommand() aufgerufen wird.
   * @param sender Der Sender über den die in Pakete verpackten Daten
   *               gesendet werden.
   */
  void setSender(ISender& sender);

  /**
   * Schickt einen Befehl raus. Dazu wird der über setSender() eingestellte
   * ISender verwendet.
   */
  virtual void sendCommand(const char command[4],const utils::Buffer&);

  /**
   * Leitet angekommene Daten an das NetProtocol weiter.
   * Falls ein ganzes Paket empfangen wurde wird der ICommandInterpreter
   * aufgerufen. Die Methode ist blockierend und wartet bis der
   * ICommandInterpreter fertig ist.
   * @param data Die angekommenen Daten
   * @param len Die Länge der Daten in Bytes
   */
  virtual void dataReceived(const utils::Buffer& buf);

private:
  ISender* m_sender;
  ICommandInterpreter* m_commandInterpreter;

  unsigned char* bufferBegin;
  unsigned char* bufferPos;
  unsigned char* bufferEnd;


  void read(const unsigned char*& dataPos,const unsigned char* dataEnd,
	    int bytesToRead, int& bytesLeft);
};

} //end of namespace

#endif

