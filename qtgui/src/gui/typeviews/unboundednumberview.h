#ifndef INCLUDED_UNBOUNDED_NUMBER_VIEW_H
#define INCLUDED_UNBOUNDED_NUMBER_VIEW_H

#include "gui/typeview.h"

namespace gui
{
  class UnboundedNumberViewConstructor
    : public TypeViewConstructor
  {
  public:
    UnboundedNumberViewConstructor();
    virtual TypeView* construct(QWidget* parent,
				const ParamMap& params) const;
  };
}

#endif
