#ifndef INCLUDED_FILE_STRING_VIEW_H
#define INCLUDED_FILE_STRING_VIEW_H

#include "gui/typeview.h"

namespace gui
{
  class FileStringViewConstructor : public TypeViewConstructor
  {
  public:
    FileStringViewConstructor();
    virtual TypeView* construct(QWidget* parent,
				const ParamMap& params) const;

  };

}

#endif
