#ifndef INCLUDED_INETSOCKET_H
#define INCLUDED_INETSOCKET_H

#include <string>
#include <stdexcept>

#include "isender.h"

namespace net
{

  class IDataListener;

  /**
   *  This class provides a high level interface for network sockets.
   */
  class INetSocket : public ISender
  {
  public:

    /**
     * TODO
     */
    virtual void setDataListener(IDataListener& listener) = 0;

    /** 
     * Versucht eine Verbindung aufzubauen. Wenn isConnected() == true
     * passiert nix. Wenn die Verbindung nicht aufgebaut werden kann
     * wird eine Exception geworfen //TODO!!!!!
     * Ob die Methode blockiert hängt von der konkreten Implementierung ab.
     */
    virtual void buildConnection() throw(std::runtime_error) = 0;

    /**
     *
     */
    //    virtual int send(const utils::Buffer& buf) throw(std::runtime_error);


    /**
     * Schau ob Daten angekommen sind. Wenn ja wird der DataListener
     * aufgerufen.
     * Ob die Methode blockiert hängt von der konkreten Implementierung ab.
     */
    virtual void run() = 0;
	
    virtual void disconnect() = 0;
    virtual bool isConnected() = 0;
  };

} // end of namespace net

#endif
