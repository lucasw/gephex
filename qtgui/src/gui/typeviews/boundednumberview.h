#ifndef INCLUDED_BOUNDED_NUMBER_VIEW_H
#define INCLUDED_BOUNDED_NUMBER_VIEW_H

#include <map>
#include "gui/typeview.h"

namespace gui
{
  class BoundedNumberViewConstructor : public TypeViewConstructor
  {
  public:
    BoundedNumberViewConstructor();
    virtual TypeView* construct(QWidget* parent, const ParamMap&) const;
  };


}

#endif
