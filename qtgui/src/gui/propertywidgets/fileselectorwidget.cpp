#include "fileselectorwidget.h"

#include "utils/structreader.h"

#include "qlayout.h"
#include "qpushbutton.h"
#include "qfiledialog.h"
#include "qtooltip.h"

namespace gui
{

  PropertyFileSelectorWidget::PropertyFileSelectorWidget(QWidget* parent,
							 const char* name,
							 WFlags fl,
							 int nodeID,
							 int inputIndex,
							 int controlID,
							 const std::map<std::string,std::string>& params,
							 IModelControlReceiver& mo)
    :PropertyWidget(parent, name, fl, nodeID, inputIndex, controlID,mo,params)
  {
    utils::StructReader sr(params);
    
	fileMask = sr.getStringValue("file_mask","*.*");
	fileMaskName = sr.getStringValue("file_mask_name","All");
    	
    QHBoxLayout* l = new QHBoxLayout(this);
    select = new QPushButton("Select",this);
    select->setMinimumSize(40, 33);
    //select->setMaximumSize(60, 20);
    //select->resize(40, 20);	
    select->show();
    l->addWidget(select);
		
    connect(select, SIGNAL(clicked()), this, SLOT(fileSelectRequest()));
  }
	
  utils::Buffer PropertyFileSelectorWidget::getValue() const
  {
    return utils::Buffer(reinterpret_cast<const unsigned char*>(current.c_str()),
			 current.length()+1);
  }
	
  void PropertyFileSelectorWidget::fileSelectRequest()
  {
    std::string fullMask = fileMaskName + " (" + fileMask + ")";	
    QString name = QFileDialog::getOpenFileName( current.c_str(), fullMask.c_str(), this );
    if (name.length() != 0)
      {
	current = name.latin1();
	setValue(getValue());
      }
    else
      current = "";
  }

  PropertyFileSelectorWidget::~PropertyFileSelectorWidget()
  {
    //		std::cout << "MIST" << std::endl;
  }


  void PropertyFileSelectorWidget::controlValueChanged(int nodeID,
						       int intputIndex,
						       const utils::Buffer& newValue)
  {
    const char* dumm = reinterpret_cast<const char*>(newValue.getPtr());

    select->setText(dumm);
    current = dumm;
    std::string toolTipText = dumm;
    QToolTip::add(this,toolTipText.c_str());
  }

  // constructor

  PropertyFileSelectorWidgetConstructor::PropertyFileSelectorWidgetConstructor():
    PropertyWidgetConstructor("typ_StringType","file_selector","file_selector")
  {
  }
	

  PropertyWidget*
  PropertyFileSelectorWidgetConstructor::construct(QWidget* parent,
						   const std::string& name,
						   int controlID, int nodeID,
						   int inputIndex,
						   const std::map<std::string,std::string>& params,
						   IModelControlReceiver& mo)
  {
    return new PropertyFileSelectorWidget(parent,"file_selector",0,nodeID,
					  inputIndex,controlID,params,mo);
  }

}
