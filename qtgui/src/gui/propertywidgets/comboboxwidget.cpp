#include "comboboxwidget.h"

#include "qcombobox.h"
#include "qlayout.h"
#include "utils/structreader.h"
#include "utils/stringtokenizer.h"

namespace gui
{


  PropertyComboBoxWidget::PropertyComboBoxWidget(QWidget* parent,
						 const char* name, WFlags fl,
						 int nodeID, int inIndex,
						 int controlID,
						 const std::map<std::string,std::string>& params,
						 IModelControlReceiver& mo)
    : PropertyWidget(parent,name,fl,nodeID,inIndex,controlID,mo,params),
      itWasMe(false)
  {
    //this->resize(100, 50);
		
    box = new QComboBox(false, this, name);
		
    QBoxLayout* layout = new QBoxLayout(this,QBoxLayout::TopToBottom,10);
    layout->addWidget(box);
		
    utils::StructReader sr(params);
		
    try {
      std::string values = sr.getStringValue("values");
			
      utils::StringTokenizer tok(values);
      int index = 0;
      for (std::string token = tok.next(",");
	   token != ""; token = tok.next(","), ++index)
	{
	  box->insertItem(token.c_str(), index);
	  m_values[token] = index;
	}
    }
    catch(...)
      {
      }
		
    connect(box,SIGNAL(activated(const QString&)),
	    this,SLOT(postNewString(const QString&)));
		
  }
	
  void PropertyComboBoxWidget::postNewString(const QString& s)
  {
    if (!itWasMe)
      {
	const unsigned char* str 
	  = reinterpret_cast<const unsigned char*>(s.latin1());

	setValue(utils::Buffer(str,strlen(s.latin1())+1));
      }
    else
      {
	itWasMe = false;
      }
  }

  utils::Buffer PropertyComboBoxWidget::getValue() const
  {
    std::string val = box->currentText().latin1();
    return utils::Buffer(reinterpret_cast<const unsigned char*>(val.c_str()),
			 val.length()+1);
  }
		
  void PropertyComboBoxWidget::controlValueChanged(int nodeID,int intputIndex,
						   const utils::Buffer& newValue)
  {
    itWasMe = true;
    std::string str = reinterpret_cast<const char*>(newValue.getPtr());
    std::map<std::string,int>::const_iterator
      it = m_values.find(str.c_str());
			
    if (it == m_values.end())
      {
	throw std::runtime_error("Invalid combobox value: '" + str + "'");
      }
			
    box->setCurrentItem(it->second);
  }

  // constructor

  PropertyComboBoxWidgetConstructor::PropertyComboBoxWidgetConstructor():
    PropertyWidgetConstructor("typ_StringType","ComboBox","combo_box")
  {
  }
	

  PropertyWidget* PropertyComboBoxWidgetConstructor::construct(QWidget* parent, const std::string& name, int controlID,
							       int nodeID, int inputIndex,const std::map<std::string,std::string>& params ,IModelControlReceiver& mo)
  {
    return new PropertyComboBoxWidget(parent,"ComboBox",0,nodeID,inputIndex,controlID,params,mo);
  }

}
