#ifndef INCLUDE_DIAL_NUMBER_VIEW_H
#define INCLUDE_DIAL_NUMBER_VIEW_H

#include "gui/typeview.h"

namespace gui
{
  class DialNumberViewConstructor : public TypeViewConstructor
  {
  public:
    DialNumberViewConstructor();
    virtual TypeView* construct(QWidget* parent, const ParamMap&) const;
  };
}

#endif
