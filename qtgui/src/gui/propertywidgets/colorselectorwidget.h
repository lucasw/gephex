#ifndef COLORSELECTORWIDGET_H
#define COLORSELECTORWIDGET_H

#include <map>

#include "gui/propertywidget.h"

class QButton;

namespace gui
{

	class PropertyColorSelectorWidget: public gui::PropertyWidget
	{
		Q_OBJECT
			
	public:
		PropertyColorSelectorWidget(QWidget* parent, const char* name, WFlags fl,
			int nodeID, int inIndex, int controlID,
			const std::map<std::string,std::string>& params,
			IModelControlReceiver& mo);
		
		virtual ~PropertyColorSelectorWidget();

		virtual utils::Buffer getValue() const;

		virtual void controlValueChanged(int nodeID,int intputIndex,
			const utils::Buffer& newValue);

		
	private:
		QButton* select;
		std::string  current;
	private slots:
		void colorSelectRequest();
	};

class PropertyColorSelectorWidgetConstructor:public PropertyWidgetConstructor
{
	public:
	PropertyColorSelectorWidgetConstructor();
	virtual PropertyWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex,const std::map<std::string,std::string>& ,IModelControlReceiver& mo);
};
	
}

#endif
