#ifndef INCLUDED_HIDE_BUTTON_H
#define INCLUDED_HIDE_BUTTON_H

#include <qcheckbox.h>

namespace gui
{

  class InputPlugWidget;

  class HideButton : public QCheckBox
  {
    Q_OBJECT
  public:
    HideButton(QWidget* parent, InputPlugWidget& in);
    
private slots:
  void hasBeenToggled(bool);


  private:
    InputPlugWidget* m_in;
  };

} // end of namespace gui

#endif
