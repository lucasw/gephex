#ifndef INCLUDED_COMBOBOX_STRING_VIEW_H
#define INCLUDED_COMBOBOX_STRING_VIEW_H
#include <map>

#include "gui/typeview.h"

namespace gui
{

  class ComboboxStringViewConstructor : public TypeViewConstructor
  {
  public:
    ComboboxStringViewConstructor();
    virtual TypeView* construct(QWidget* parent,
				const ParamMap& params) const;
  
  };
	
}

#endif
