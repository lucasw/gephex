#ifndef COMBOBOXWIDGET_H
#define COMBOBOXWIDGET_H

#include "gui/controlwidget.h"
class QComboBox;

namespace gui
{

	class ComboBoxWidget:public gui::ControlWidget
	{
		Q_OBJECT
  		public:
    		ComboBoxWidget(QWidget* parent, const std::string& name, int controlID,
				   int nodeID,int inIndex);

			virtual void controlValueChanged(int nodeID,int intputIndex,
				   const utils::Buffer& newValue);
		public slots:
			void postNewString(const QString&);
  		private:
    		QComboBox* box;
			bool itWasMe;
	};

class ComboBoxWidgetConstructor:public ControlWidgetConstructor
{
	public:
	ComboBoxWidgetConstructor();
	virtual ControlWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex);
};

}

#endif
