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

#ifndef INCLUDED_PROPERTY_VIEW_H
#define INCLUDED_PROPERTY_VIEW_H

#include <list>
#include <QtGui/QWidget>


class QTableWidget;
class QHBoxLayout;

/**
 * Diese Klasse zeigt Eigenschaften von Objekten (z.B. NodeWidgets) an.
 * Sie baut anhand einer Beschreibung (IPropertyDescription) eine
 * Eigenschafts-Tabelle zusammen. (Tabelle ist aber kein muss, 
 * ist Implementierungssache)
 * Die Tabelle wird jedesmal neu erzeugt, wenn die Eigenschaften für ein Objekt
 * angezeigt werden.
 *
 * Wenn man für ein Objekt Eigenschaften in einer PropertyView anzeigen will
 * sollte man wie folgt vorgehen:
 *
 *  -Für die Widgets, die in den Eigenschaften angezeigt werden sollen
 *   (z.B. FontSelector, ColorSelector...)
 *   Konstruktor-Klassen erstellen (IWidgetConstructor subclassen)
 *   Es sollte eigtl. eine Konstruktorklasse für alle PropertyWidgets 
 *   ausreichen, da alle dieselben Informationen zur Erzeugung brauchen.
 *
 *  -Für jede Eigenschaft einen PropertyEntry erstellen
 *
 *  -IPropertyDescription subclassen und die Liste der PropertyEntries
 *   mit getEntries() zurückgeben.
 *
 *  -Eine Instanz dieser Subklasse an die PropertyView per displayProperties()
 *   übergeben.
 *
 * Das klingt jetzt ziemlich umständlich. Ist es auch. Dafür ist das Ganze 
 * aber (hoffentlich) recht allgemein verwendbar, also auch für Eigenschaften 
 * von Controls, ganzen Graphen und so weiter und so fort.
 * Ausserdem muss sich die PropertyView nicht um so Sachen wie Änderungen der 
 * Controls etc. kümmern, das ist alles in den Widgets, die von den 
 * Konstruktor-Klassen erzeugt werden, gekapselt.
 *
 * Genaugenommen hat die PropertyView gar keine Abhängigkeiten zum Model oder
 * zur übrigen Gui, könnte sogar ausgelagert werden...
 * Sagts halt mal was ihr davon denkts.
 */

namespace gui
{

  class IPropertyDescription;
  class IWidgetConstructor;

  class PropertyView : public QWidget
    {
    public:
      /**
       * Erzeugt eine neue PropertyView.
       * @param parent Das Vater Widget der View.
       */
      PropertyView(QWidget* parent);

      ~PropertyView();

      /**
       * Zeigt die Eigenschaften an die in desc beschrieben sind.
       * Die entsprechenden Widgets werden mithilfe der IWidgetConstructor 
       * Objekte erzeugt. 
       * Die Widgets werden wieder gelöscht, wenn displayProperties()
       * das nächste Mal aufgerufen wird.
       * @param desc Eine Beschreibung der Eigenschaften eines Objekts.
       */
      void displayProperties(const IPropertyDescription& desc);

      void undisplayProperties();

    private:
      QTableWidget* table;
      QHBoxLayout* m_layout;

      std::list<std::pair<const IWidgetConstructor*,QWidget*> > widgetCtors;

      void deleteTable();
    };

}

#endif
