#ifndef DIALWIDGET_H
#define DIALWIDGET_H

#include "gui/controlwidget.h"

class QDial;

namespace gui
{

  class DialWidget : public gui::ControlWidget
	{
		Q_OBJECT
  		public:
   			DialWidget(QWidget* parent, const std::string& name,  int controlID, int nodeID,int inIndex);
			virtual void controlValueChanged(int nodeID,int intputIndex,const utils::Buffer& newValue);
		private slots:
			void intValueChanged(int newVal);
  		private:
    		QDial* dial;
			bool itWasMe;
    		//QFrame* surrounder;	
  	};

class DialWidgetConstructor:public ControlWidgetConstructor
{
	public:
	DialWidgetConstructor();
	virtual ControlWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex);
};

}

#endif
