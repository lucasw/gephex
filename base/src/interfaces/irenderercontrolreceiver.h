#ifndef INCLUDED_IRENDERERCONTROLRECEIVER_H
#define INCLUDED_IRENDERERCONTROLRECEIVER_H
#include <string>

namespace utils {
	class Buffer;
}

 /**
  * TODO: descr. of the interface
  */

class IRendererControlReceiver
{
public:
  /**
   *
   */  
	virtual void start(  ) = 0;

  /**
   *
   */
	virtual void stop(  ) = 0;

   /**
     * Daten an ein Modul schicken.
     * @param moduleID Modul, das die Daten empfangen soll
     * @param inputIndex
     * @param data Daten, die das Modul empfangen soll
     */
	virtual void setInputValue( const std::string& graphName, int nodeID, int inputIndex, const utils::Buffer& buf ) = 0;

  /**
   * Veranlasst den Renderer dazu, dem ControlValueReceiver
   * den Wert eines Inputs mitzuteilen.
   * @param nodeID     Das Modul dessen Input synchronisiert werden soll
   * @param inputIndex Der Input des Moduls
   */
	virtual void syncInputValue( const std::string& graphName, int nodeID, int inputIndex ) = 0;

  /**
   *
   */
	virtual void synchronizeInputValues( const std::string& graphName ) = 0;

};
#endif
