#ifndef LINEEDITWIDGET_H
#define LINEEDITWIDGET_H

#include "gui/controlwidget.h"
class QLineEdit;

namespace gui
{

	class LineEditWidget:public gui::ControlWidget
	{
		Q_OBJECT
		public:
			LineEditWidget(QWidget* parent, const std::string& name, int controlID,
		   		int nodeID,int inIndex);
			virtual void controlValueChanged(int nodeID,int intputIndex,
				   const utils::Buffer& newValue);
		public slots:
			void postNewString();
	  private:
   		 	QLineEdit* textEdit;
			bool itWasMe;
	};

class LineEditWidgetConstructor:public ControlWidgetConstructor
{
	public:
	LineEditWidgetConstructor();
	virtual ControlWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex);
};

}

#endif
