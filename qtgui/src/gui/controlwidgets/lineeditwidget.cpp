#include "lineeditwidget.h"

#include "qlayout.h"
#include "qlineedit.h"
#include "utils/buffer.h"

namespace gui
{

  LineEditWidget::LineEditWidget(QWidget* parent, const std::string& name,
				 int controlID,int nodeID,int inIndex):
    ControlWidget(parent, name,controlID, nodeID, inIndex), itWasMe(false)
  {
    this->resize(100, 40);

    textEdit = new QLineEdit(this, name.c_str());
	
    QBoxLayout* layout = new QBoxLayout(this,QBoxLayout::TopToBottom,10);
    layout->addWidget(textEdit);

    connect(textEdit,SIGNAL(returnPressed()),
	    this,SLOT(postNewString()));
  }


  void LineEditWidget::postNewString()
  {
    if (!itWasMe)
      {
	QString s = textEdit->text();
	const unsigned char* str 
	  = reinterpret_cast<const unsigned char*>(s.latin1());
	
	valueChanged(utils::Buffer(str,strlen(s.latin1())+1));
      }
    else
      {
	itWasMe = false;
      }
  }

  void LineEditWidget::controlValueChanged(int nodeID,int intputIndex,
					   const utils::Buffer& newValue)
  {
    itWasMe = true;
    textEdit->setText(reinterpret_cast<const char*>(newValue.getPtr()));
  }

  // constructor klass

  LineEditWidgetConstructor::LineEditWidgetConstructor():
    ControlWidgetConstructor("typ_StringType","Eingabefeld","line_edit")
  {
  }
		
  ControlWidget* LineEditWidgetConstructor::construct(QWidget* parent,
						      const std::string& name,
						      int controlID,
						      int nodeID,
						      int inputIndex)
  {
    return new LineEditWidget(parent,name,controlID,nodeID,inputIndex);
  }



}
