#ifndef INCLUDED_IVISIBLE_ELEMENT_H
#define INCLUDED_IVISIBLE_ELEMENT_H

#include <qwidget.h>

namespace gui {
  class IVisibleElement : public QWidget
  { 
  public:
    virtual int numberOfInputs() const = 0;
    virtual int numberOfOutputs() const = 0;
    virtual void inputPos(int index, int& x, int& y) const = 0;
    virtual void outputPos(int index, int& x, int& y) const = 0;
  };
#endif
