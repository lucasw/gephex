#include "videowallselectorwidget.h"

#include "qlayout.h"
#include "qpushbutton.h"
#include <sstream>
#include <list>

namespace gui

{

	
  VideoWallPropertyWidget::VideoWallPropertyWidget(QWidget* parent,
						   const char* name,
						   WFlags fl,
						   int nodeID,
						   int inputIndex,
						   int controlID,
						   const std::map<std::string,std::string>& params,
						   IModelControlReceiver& mo)
    :PropertyWidget(parent, name, fl, nodeID, inputIndex, controlID,mo,params)
  {
		
    QHBoxLayout* l = new QHBoxLayout(this);
    select = new QPushButton("Edit",this);
    select->setMinimumSize(40, 33);
    //select->setMaximumSize(60, 20);
    //select->resize(40, 20);	
    select->show();
    l->addWidget(select);
		
    connect(select, SIGNAL(clicked()), this, SLOT(editRequest()));
  }
	
  utils::Buffer VideoWallPropertyWidget::getValue() const
  {
    return utils::Buffer(reinterpret_cast<const unsigned char*>(current.c_str()),
			 current.length()+1);
  }
	
  void VideoWallPropertyWidget::editRequest()
  {
    // TODO
    /*
      std::list<VideoWallCommand> cmds=VideoWallControllDialog::videoWallControllDialog(this,"Steuerung");

      std::ostringstream os("");
      for(std::list<VideoWallCommand>::const_iterator it=cmds.begin();it!=cmds.end();++it)
      {
      os << (*it) << " ";
      }
			
      current = os.str();
      setValue(getValue());
    */
  }

  VideoWallPropertyWidget::~VideoWallPropertyWidget()
  {
    //		std::cout << "MIST" << std::endl;
  }

  void VideoWallPropertyWidget::controlValueChanged(int nodeID,int intputIndex,
						    const utils::Buffer& newValue)
  {
    std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    /* TODO
       double r,g,b;
			
       is >> r >> g >> b;
       //      std::cout << "(" << r << "," << g << "," << b << ")" << std::endl;
			
       QColor newColor(r*255,g*255,b*255);
       select->setPalette(QPalette(newColor));

       QToolTip::add(this,newValue.getPtr());
    */
  }

  // constructor

  PropertyVideoWallWidgetConstructor::PropertyVideoWallWidgetConstructor():
    PropertyWidgetConstructor("typ_StringType","videowall_edit",
			      "videowall_edit")
  {
  }
	

  PropertyWidget*
  PropertyVideoWallWidgetConstructor::construct(QWidget* parent,
						const std::string& name,
						int controlID, int nodeID,
						int inputIndex,
						const std::map<std::string,std::string>& params,
						IModelControlReceiver& mo)
  {
    return new VideoWallPropertyWidget(parent,"videowall_edit",0,nodeID,
				       inputIndex,controlID,params,mo);
  }

}
