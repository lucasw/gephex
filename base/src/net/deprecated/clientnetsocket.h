#ifndef INCLUDED_CLIENT_NETSOCKET_H
#define INCLUDED_CLIENT_NETSOCKET_H

#include "inetsocket.h"

#include "utils/autoptr.h"

namespace net
{

  class IDataListener;
  class ISocket;


  /**
   * Die Klasse Netstream kapselt die gesamte Netzwerkfunktionalität.
   * Sie ist dafür ausgelegt nichtblockierend zu arbeiten (-> keine Threads).
   * Sie kann prinzipiell in zwei Modi arbeiten: serverMode und clientMode.
   * Im ServerMode wartet sie an einem bestimmten Port auf connections.
   * Im Clientmode ist es möglich mit connectTo zu einem anderen Rechner
   * in Verbindung zu treten.
   */
  class ClientNetSocket : public INetSocket {
  private:
    IDataListener* dListener;

    utils::AutoPtr<ISocket> m_socket;

    std::string m_remoteHost;
    int m_remotePort;

  public:
    ClientNetSocket(const std::string& remoteHost, int remotePort,
		    bool useUDP = false);

    virtual ~ClientNetSocket();

    void setDataListener(IDataListener& listener);

    /** 
     * Versucht eine Verbindung aufzubauen. Wenn isConnected() == true
     * passiert nix. Wenn die Verbindung nicht aufgebaut werden kann
     * wird eine Exception geworfen //TODO!!!!!
     */
    void buildConnection() throw(std::runtime_error);

    /**
     * Schau ob Daten angekommen sind. Wenn ja wird der DataListener
     * aufgerufen.
     * @param timeout Zeit in ms die der Aufruf blockiert.
     */
    void run();
	
    void disconnect();
    bool isConnected();

    virtual int send(const utils::Buffer& buf);
  };

}

#endif
