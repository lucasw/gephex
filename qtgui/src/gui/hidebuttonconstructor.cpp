#include "hidebuttonconstructor.h"

#include "hidebutton.h"

namespace gui
{

  HideButtonConstructor::HideButtonConstructor(InputPlugWidget& in)
    : m_in(&in)
  {
  }
  
  QWidget* HideButtonConstructor::constructWidget(QWidget* parent) const
  {
    return new HideButton(parent,*m_in);
  }
  
  void HideButtonConstructor::destroyWidget(QWidget* w) const
  {
    HideButton* hb = dynamic_cast<HideButton*>(w);

    //delete hb;
  }

} // end of namespace gui
