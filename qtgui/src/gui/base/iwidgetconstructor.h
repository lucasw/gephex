#ifndef INCLUDED_WIDGET_CONSTRUCTOR_H
#define INCLUDED_WIDGET_CONSTRUCTOR_H

class QWidget;

namespace gui
{

  /**
   * Erlaubt die verz�gerte Konstruktion eines Widgets. Ein Objekt des Typs 
   * IWidgetConstructor enth�lt alle Informationen die n�tig sind um ein Widget
   * zu erzeugen.
   */
  class IWidgetConstructor
  {
  public:

    /**
     * Baut ein QWidget.
     * @param parent Der Parent des konstruierten Widgets.
     * @return ein neu erzeugtes Widget.
     */
    virtual QWidget* constructWidget(QWidget* parent) const = 0;

    /**
     * Zerst�rt das Widget wieder. Darf nicht delete aufrufen!
	 * Die Methode ist dazu gedacht, eventuelle Registrierungen
	 * etc. des Widgets wieder r�ckg�ngig zu machen.
	 * delete wird in der PropertyView aufgerufen.
	 * @param w ein Pointer auf das von dem Constructor mit
	 *    constructWidget erzeugte Widget.
     */
    virtual void destroyWidget(QWidget* w) const = 0;
  };

} // end of namepsace gui

#endif
