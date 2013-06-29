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

#ifndef INCLUDED_IPROPERTY_DESCRIPTION_H
#define INCLUDED_IPROPERTY_DESCRIPTION_H

#include <string>
#include <list>

namespace gui
{

class IWidgetConstructor;


/**
 * Beschreibt eine Eigenschaft eines Objekts.
 * Ein Entry besteht aus einem Namen und einem oder mehreren Widgets mit denen
 * der Wert der Eigenschaft angezeigt bzw. verändert werden kann.
 * Typischerweise git es genau ein Widget mit dem der Wert einer Eigenschaft 
 * angezeigt wird.
 */
class PropertyEntry
{
public:

	/**
	 * Erzeugt einen Neuen PropertyEntry.
	 * @param name Der Name der Eigenschaft.
	 * @param widgetCtors Liste von Konstruktoren für die Widgets der 
	 * Eigenschaft. 
	 */
	PropertyEntry(const std::string& name,
		      const std::list<const IWidgetConstructor*>& widgetCtors)
	  : m_name(name), m_widgetCtors(widgetCtors)
	{
	}

	/**
	 * Gibt den Namen der Eigenschaft zurück. Z.B. "Schriftart".
	 * @return Der Name der Eigenschaft.
	 */
	std::string getName() const
	{
		return m_name;
	}

	/**
	 * Gibt Konstruktoren für die Widgets einer Eigenschaft zurück.
	 * In den meisten Fällen hat die Liste genau 1 Element.
	 * @return Liste von Konstruktoren für die Widgets dieser Eigenschaft.
	 */
	const std::list<const IWidgetConstructor*>& getWidgetCtors() const
	{
		return m_widgetCtors;
	}

private:
	std::string m_name;
	const std::list<const IWidgetConstructor*>& m_widgetCtors;
};


/**
 * Dient zur Beschreibung der Eigenschaften eines Objekts. 
 * Die Klasse PropertyView kann daraus einen Dialog bauen.
 */
class IPropertyDescription
{
public:

	/**
	 * Gibt eine Beschreibung von Eigenschaften zurück.
	 * @return Eine Liste von PropertyEntries.
	 */
	virtual std::list<PropertyEntry> getEntries() const = 0;
};

}

#endif
