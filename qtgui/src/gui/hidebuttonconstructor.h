#ifndef INCLUDED_HIDE_BUTTON_CONSTRUCTOR_H
#define INCLUDED_HIDE_BUTTON_CONSTRUCTOR_H

#include "base/iwidgetconstructor.h"

namespace gui
{

  class InputPlugWidget;

class HideButtonConstructor : public IWidgetConstructor
{
public:
  HideButtonConstructor(InputPlugWidget& in);
  
  virtual QWidget* constructWidget(QWidget* parent) const;
  
  virtual void destroyWidget(QWidget* w) const;

private:
  InputPlugWidget* m_in;
};

} // end of namespace gui

#endif
