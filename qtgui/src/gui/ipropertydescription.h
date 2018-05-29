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
 * der Wert der Eigenschaft angezeigt bzw. ver�ndert werden kann.
 * Typischerweise git es genau ein Widget mit dem der Wert einer Eigenschaft 
 * angezeigt wird.
 */
class PropertyEntry
{
public:

	/**
	 * Erzeugt einen Neuen PropertyEntry.
	 * @param name Der Name der Eigenschaft.
	 * @param widgetCtors Liste von Konstruktoren f�r die Widgets der 
	 * Eigenschaft. 
	 */
	PropertyEntry(const std::string& name,
		      const std::list<const IWidgetConstructor*>& widgetCtors)
	  : m_name(name), m_widgetCtors(widgetCtors)
	{
	}

	/**
	 * Gibt den Namen der Eigenschaft zur�ck. Z.B. "Schriftart".
	 * @return Der Name der Eigenschaft.
	 */
	std::string getName() const
	{
		return m_name;
	}

	/**
	 * Gibt Konstruktoren f�r die Widgets einer Eigenschaft zur�ck.
	 * In den meisten F�llen hat die Liste genau 1 Element.
	 * @return Liste von Konstruktoren f�r die Widgets dieser Eigenschaft.
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
	 * Gibt eine Beschreibung von Eigenschaften zur�ck.
	 * @return Eine Liste von PropertyEntries.
	 */
	virtual std::list<PropertyEntry> getEntries() const = 0;
};

}

#endif
