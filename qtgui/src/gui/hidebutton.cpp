#include "hidebutton.h"

#include "inputplugwidget.h"

namespace gui
{

HideButton::HideButton(QWidget* parent, InputPlugWidget& in)
  : QCheckBox(parent,"oller knopf"), m_in(&in)
{
  this->setToggleButton(true);

  connect(this,SIGNAL(toggled(bool)),this,SLOT(hasBeenToggled(bool)));

  if (m_in->isVisible())
    this->setChecked(false);
  else
    this->setChecked(true);

}

  void HideButton::hasBeenToggled(bool state)
  {
    if (state)
      {
	m_in->setVisible();
	//	this->setChecked(false);
      }
    else
      {
	m_in->setInvisible();
	//	this->setChecked(true);
      }
  }

} // end of namespace gui

