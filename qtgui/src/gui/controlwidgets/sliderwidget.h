#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

//#include <qslider.h>
class QSlider; //TODO
#include "gui/controlwidget.h"

namespace gui
{

  class SliderWidget : public gui::ControlWidget
  {
    Q_OBJECT
  public:
    SliderWidget(QWidget* parent, Qt::Orientation orient,
		 const std::string& name,int controlID,
		 int nodeID,int inIndex);

    virtual void controlValueChanged(int nodeID,int intputIndex,
				     const utils::Buffer& newValue);
private slots:
void intValueChanged(int newVal);
  private:
    QSlider* slider;
    bool itWasMe;
  };

  class VSliderWidgetConstructor:public ControlWidgetConstructor
  {
  public:
    VSliderWidgetConstructor();
    virtual ControlWidget* construct(QWidget* parent,
				     const std::string& name, int controlID,
				     int nodeID, int inputIndex);
  };

  class HSliderWidgetConstructor:public ControlWidgetConstructor
  {
  public:
    HSliderWidgetConstructor();
    virtual ControlWidget* construct(QWidget* parent,
				     const std::string& name, int controlID,
				     int nodeID, int inputIndex);
  };

}

#endif
