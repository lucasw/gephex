#ifndef FILESELECTORWIDGET_H
#define FILESELECTORWIDGET_H

#include <map>

#include "gui/propertywidget.h"
class QButton;

namespace gui
{

	class PropertyFileSelectorWidget: public gui::PropertyWidget
	{
		Q_OBJECT
			
	public:
		PropertyFileSelectorWidget(QWidget* parent, const char* name, WFlags fl,
			int nodeID, int inIndex, int controlID,
			const std::map<std::string,std::string>& params,
			IModelControlReceiver& mo);
		
		virtual ~PropertyFileSelectorWidget();
		
		virtual utils::Buffer getValue() const;
		
		virtual void controlValueChanged(int nodeID,int intputIndex,
			const utils::Buffer& newValue);

		
	private:
		QButton* select;
		std::string  current;
		std::string fileMask;
		std::string fileMaskName;
	private slots:
		void fileSelectRequest();
	};
	
class PropertyFileSelectorWidgetConstructor:public PropertyWidgetConstructor
{
	public:
	PropertyFileSelectorWidgetConstructor();
	virtual PropertyWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex,const std::map<std::string,std::string>& ,IModelControlReceiver& mo);
};

}

#endif
