#ifndef INCLUDED_PROPERTYWIDGETFACTORY_H
#define INCLUDED_PROPERTYWIDGETFACTORY_H

#include <string>
#include <list>
#include <map>

class QWidget;

class IModelControlReceiver;

namespace gui
{

  class PropertyWidget;
	class PropertyWidgetConstructor;

  class NodeProperty;

  class PropertyWidgetInfo
  {
  public:
    explicit PropertyWidgetInfo(const std::string& name)
      : m_name(name) {}

    std::string getName() const { return m_name; }

  private:
    std::string m_name;
  };

  /**
   * Diese Klasse erzeugt die Propertywidgets die in ein NodeProperty
   * geschmissen werden können
   */
  class PropertyWidgetFactory
  {
  public:
    PropertyWidgetFactory();
    ~PropertyWidgetFactory();

    /**
     * Ein neues Propertywidget mit einem bestimmten Typ erzeugen.
     */
    PropertyWidget* createPropertyWidget(QWidget* parent,
					 const std::map<std::string,
					                std::string>& params,
					 const std::string& propertyType,
					 int nodeID, int inputIndex,
					 int controlID, IModelControlReceiver& rcr) const;

    /**
     * Liste der möglichen Properties für einen Typ zurückgeben.
     */
    const std::list<PropertyWidgetInfo>&
    getCompatibleWidgetTypes(const std::string& type) const;

		/**
		 * Register a Factory for a special PropertyWidget
		 */
		void registerPropertyWidgetConstructor(PropertyWidgetConstructor*);


  private:
    std::map<std::string,std::list<PropertyWidgetInfo> > propertyMapper;
    std::map<std::string,PropertyWidgetConstructor*> ID2ConstrMapper;
  };

} // end of namespace gui
#endif
