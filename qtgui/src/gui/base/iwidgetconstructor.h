/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#ifndef INCLUDED_WIDGET_CONSTRUCTOR_H
#define INCLUDED_WIDGET_CONSTRUCTOR_H

class QWidget;

namespace gui
{

  /**
   * Erlaubt die verzögerte Konstruktion eines Widgets. Ein Objekt des Typs 
   * IWidgetConstructor enthält alle Informationen die nötig sind um ein Widget
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
     * Zerstört das Widget wieder. Darf nicht delete aufrufen!
	 * Die Methode ist dazu gedacht, eventuelle Registrierungen
	 * etc. des Widgets wieder rückgängig zu machen.
	 * delete wird in der PropertyView aufgerufen.
	 * @param w ein Pointer auf das von dem Constructor mit
	 *    constructWidget erzeugte Widget.
     */
    virtual void destroyWidget(QWidget* w) const = 0;
  };

} // end of namepsace gui

#endif
