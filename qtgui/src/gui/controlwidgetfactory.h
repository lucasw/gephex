#ifndef INCLUDED_CONTROLWIDGETFACTORY_H
#define INCLUDED_CONTROLWIDGETFACTORY_H

#include <string>
#include <list>
#include <map>

class QWidget;

namespace gui
{

class ControlWidget;
class ControlWidgetConstructor;


class ControlWidgetInfo
{
public:
	ControlWidgetInfo(const std::string& identifier,
			  const std::string& description)
	  : m_identifier(identifier), m_description(description) {}
	
	std::string getIdentifier() const { return m_identifier; }
	std::string getDescription() const { return m_description; }
	
 private:
	std::string m_identifier;
	std::string m_description;
};

/**
 * Diese Klasse erzeugt die Controlwidgets die an die InputPlugs gehängt
 * werden können.
 */
class ControlWidgetFactory
{
public:
  ControlWidgetFactory();

  /**
   * Ein neues Controlwidget mit einem bestimmten Typ erzeugen.
   */	
  ControlWidget* createControlWidget(QWidget* parent,
				     const std::string& name,
				     const std::string& widgetID,
				     int nodeID,int inIndex,
				     int controlID) const;
  
  void registerControlWidgetConstructor(ControlWidgetConstructor*);
  
  /**
   * Liste der möglichen Controls für einen Typ zurückgeben.
   * @exception TODO
   */
  std::list<ControlWidgetInfo> 
    getCompatibleControls(const std::string& type) const;
  
 private:
  std::map<std::string,std::list<ControlWidgetInfo> > controlMapper;
  // id -> constructor
  std::map<std::string,ControlWidgetConstructor*> m_constructorMap;

};

}

#endif
