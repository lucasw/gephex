#ifndef INCLUDED_CHECKBOX_NUMBER_VIEW_H
#define INCLUDED_CHECKBOX_NUMBER_VIEW_H

#include "gui/typeview.h"

namespace gui
{

  class CheckBoxNumberViewConstructor : public TypeViewConstructor
  {
  public:
    CheckBoxNumberViewConstructor();
    virtual TypeView* construct(QWidget* parent, const ParamMap& params) const;
  };

}

#endif
