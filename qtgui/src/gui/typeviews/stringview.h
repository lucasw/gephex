#ifndef INCLUDED_STRING_VIEW_H
#define INCLUDED_STRING_VIEW_H

#include "gui/typeview.h"

namespace gui
{
  class StringViewConstructor
    : public TypeViewConstructor
  {
  public:
    StringViewConstructor();
    virtual TypeView* construct(QWidget* parent,
				const ParamMap& params) const;
  };
}

#endif
