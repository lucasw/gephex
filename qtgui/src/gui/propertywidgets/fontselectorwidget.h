#ifndef FONTSELECTORWIDGET_H
#define FONTSELECTORWIDGET_H

#include <map>

#include "gui/propertywidget.h"
class QPushButton;

namespace gui
{


	class PropertyFontSelectorWidget: public gui::PropertyWidget
	{
		Q_OBJECT
			
	public:
		PropertyFontSelectorWidget(QWidget* parent, const char* name, WFlags fl,
			int nodeID, int inIndex, int controlID,
			const std::map<std::string,std::string>& params,
			IModelControlReceiver& mo);
		//QString& getCurrentSelection(){ return current; }
		
		virtual utils::Buffer getValue() const;
		
		virtual void controlValueChanged(int nodeID,int intputIndex,
			const utils::Buffer& newValue);

	private:
		QPushButton* select;
		std::string  current;
		std::string name;
		int size;
		int weight;
		bool italic;
		bool underline;

	private slots:
		void fontSelectRequest();
	};

class PropertyFontSelectorWidgetConstructor:public PropertyWidgetConstructor
{
	public:
	PropertyFontSelectorWidgetConstructor();
	virtual PropertyWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex,const std::map<std::string,std::string>& ,IModelControlReceiver& mo);
};
	



}

#endif
