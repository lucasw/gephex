#ifndef INCLUDED_TYPE_VIEW_H
#define INCLUDED_TYPE_VIEW_H

#include <string>
#include <map>

//#include <qframe.h>
#include <qwidget.h>

#include "utils/buffer.h"

namespace gui
{

  class TypeView : public QWidget
  {
    Q_OBJECT
  public:
    typedef std::map<std::string, std::string> ParamMap;
    TypeView(QWidget* parent, const ParamMap& params);

    virtual ~TypeView();
  
    virtual void valueChange(const utils::Buffer& newValue) = 0;

    signals:

    void valueChanged(const utils::Buffer& newValue);

  private:
    ParamMap m_params;
  };

  class TypeViewConstructor
  {
  public:
    typedef TypeView::ParamMap ParamMap;

    TypeViewConstructor(const std::string& name,
			const std::string& viewID);

    virtual ~TypeViewConstructor();

    const std::string& getName();
    const std::string& getViewID();

    virtual TypeView* construct(QWidget* parent,
				const ParamMap&) const= 0;

  private:
    const std::string m_name;
    const std::string m_viewID;

  };
 
}

#endif
