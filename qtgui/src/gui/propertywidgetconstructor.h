#ifndef INCLUDED_PROPERTY_WIDGET_CONSTR_H
#define INCLUDED_PROPERTY_WIDGET_CONSTR_H

#include <string>
#include <map>
#include "iwidgetconstructor.h"

class IModelControlReceiver;

namespace gui
{

  class PropertyWidgetFactory;
  class ControlValueDispatcher;
  class PropertyWidget;

  /**
   * Diese Klasse wird benutzt um PropertyWidgets für die
   * PropertyView zu erzeugen.
   */

class PropertyWidgetConstr : public IWidgetConstructor
{
public:
  PropertyWidgetConstr(const std::string& widgetType,
			    const std::map<std::string, std::string>& params,
			    int nodeID,int inIndex, int controlID,
			    const PropertyWidgetFactory& factory,
			    ControlValueDispatcher& cvd,
				IModelControlReceiver&);

  virtual ~PropertyWidgetConstr();

  virtual QWidget* constructWidget(QWidget* parent) const;

  virtual void destroyWidget(QWidget* w) const;

private:
  std::string m_widgetType;
  const std::map<std::string, std::string>& m_params;
  int m_nodeID;
  int m_inputIndex;
  int m_controlID;
  const PropertyWidgetFactory& m_factory;
  ControlValueDispatcher& m_dispatcher;
  IModelControlReceiver& mcr;
  PropertyWidget* w;
};

} // end of namespace gui

#endif
