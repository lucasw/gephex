#include "propertywidgetconstructor.h"

#include <stdexcept>

#include "propertywidget.h"
#include "guimodel/controlvaluedispatcher.h"

namespace gui
{
  
  PropertyWidgetConstr::PropertyWidgetConstr(const TypeViewConstructor* con,
					     const std::map<std::string,
					     std::string>& params,
					     int nodeID,int inIndex,
					     int controlID,
					     const utils::AutoPtr<ControlValueDispatcher>& dispatcher,
					     IModelControlReceiver& mcr_)
    : m_viewConstructor(con), m_params(params),
      m_nodeID(nodeID), m_inputIndex(inIndex), m_controlID(controlID),
      m_dispatcher(dispatcher), mcr(mcr_)
  {
    /*    w = m_factory.createPropertyWidget(0,m_params,
				       m_widgetType,m_nodeID,
				       m_inputIndex,
				       m_controlID,rcr);*/
  }

  PropertyWidgetConstr::~PropertyWidgetConstr()
  {
    //    delete w;
  }

  QWidget* PropertyWidgetConstr::constructWidget(QWidget* parent) const
  {
    PropertyWidget* w = new PropertyWidget(parent,"", 0,
					   m_nodeID, m_inputIndex,
					   m_controlID, mcr, m_params,
					   *m_viewConstructor);

    //    w->reparent(parent, QPoint(0,0));

    m_dispatcher->registerValueReceiver(m_nodeID, m_inputIndex, *w);

    return w;
  }

  void PropertyWidgetConstr::destroyWidget(QWidget* w_) const
  {
    PropertyWidget* pw = dynamic_cast<PropertyWidget*>(w_);

    if (pw == 0)
      throw std::runtime_error("Error at "
			       "PropertyWidgetConstr::destroyWidget()");

    m_dispatcher->unregisterValueReceiver(m_nodeID, m_inputIndex, *pw);

    //delete pw;
    //    w->reparent(0, QPoint(0,0));
    //    w->parent()->removeChild(w);
    //    delete w;
  }

} // end of namespace gui



