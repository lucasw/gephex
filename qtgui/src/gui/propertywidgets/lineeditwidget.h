#ifndef LINEEDITWIDGET_H
#define LINEEDITWIDGET_H

#include <map>
#include "gui/propertywidget.h"
class QLineEdit;

namespace gui
{

	class PropertyLineEditWidget: public gui::PropertyWidget
	{
		Q_OBJECT
	public:
		PropertyLineEditWidget(QWidget* parent, const char* name, WFlags fl,
			int nodeID, int inIndex, int controlID,
			const std::map<std::string,std::string>& params,
			IModelControlReceiver& mo);
		
		virtual ~PropertyLineEditWidget()	{}
		
		virtual utils::Buffer getValue() const;
		
		virtual void controlValueChanged(int nodeID,int intputIndex,
			const utils::Buffer& newValue);

	public slots:
		void textChanged_();
		
	private:
		QLineEdit* lineEdit;
		bool valueChanged;
	};
	
 class PropertyLineEditWidgetConstructor:public PropertyWidgetConstructor
{
	public:
	PropertyLineEditWidgetConstructor();
	virtual PropertyWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex,const std::map<std::string,std::string>& ,IModelControlReceiver& mo);
};

}

#endif
