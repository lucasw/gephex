#ifndef COMBOBOXWIDGET_H
#define COMBOBOXWIDGET_H
#include <map>

#include "gui/propertywidget.h"
class QComboBox;

namespace gui
{

	class PropertyComboBoxWidget: public gui::PropertyWidget
	{
		Q_OBJECT
	private:
		QComboBox* box;
		bool itWasMe;
		std::map<std::string,int> m_values;
		
	public:
		PropertyComboBoxWidget(QWidget* parent, const char* name, WFlags fl,
			int nodeID, int inIndex, int controlID,
			const std::map<std::string,std::string>& params,
			IModelControlReceiver& mo);
		
		virtual utils::Buffer getValue() const;

		
		virtual void controlValueChanged(int nodeID,int intputIndex,
			const utils::Buffer& newValue);
		
	public slots:
		void postNewString(const QString&);
		
	};

class PropertyComboBoxWidgetConstructor:public PropertyWidgetConstructor
{
	public:
	PropertyComboBoxWidgetConstructor();
	virtual PropertyWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex,const std::map<std::string,std::string>& ,IModelControlReceiver& mo);
};
	
}

#endif
