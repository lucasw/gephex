#include "comboboxwidget.h"

#include "qcombobox.h"
#include "qlayout.h"

#include "utils/buffer.h"

namespace gui
{

  //TODO: seems to be completely nonfunctional. remove?
  ComboBoxWidget::ComboBoxWidget(QWidget* parent, const std::string& name,
				 int controlID,int nodeID,int inIndex):
    ControlWidget(parent, name,controlID, nodeID, inIndex), itWasMe(false)
  {
    this->resize(100, 50);

    box = new QComboBox(false, this, name.c_str());
	
    QBoxLayout* layout = new QBoxLayout(this,QBoxLayout::TopToBottom,10);
    layout->addWidget(box);

    connect(box,SIGNAL(activated(const QString&)),
	    this,SLOT(postNewString(const QString&)));
  }

  void ComboBoxWidget::postNewString(const QString& s)
  {
    if (!itWasMe)
      {
	const unsigned char* str = 
	  reinterpret_cast<const unsigned char*>(s.latin1());
	valueChanged(utils::Buffer(str,strlen(s.latin1())+1));
      }
    else
      {
	itWasMe = false;
      }
  }

  void ComboBoxWidget::controlValueChanged(int nodeID,int intputIndex,
					   const utils::Buffer& newValue)
  {
    itWasMe = true;
    //    textEdit->setText(newValue.getPtr());
  }

  // constructor klass

  ComboBoxWidgetConstructor::ComboBoxWidgetConstructor():
    ControlWidgetConstructor("typ_StringType","ComboBox","combobox")
  {
  }
		
  ControlWidget* ComboBoxWidgetConstructor::construct(QWidget* parent,
						      const std::string& name,
						      int controlID,
						      int nodeID,
						      int inputIndex)
  {
    return new ComboBoxWidget(parent,name,controlID,nodeID,inputIndex);
  }


}
