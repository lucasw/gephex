#ifndef VIDEOWALLSELECTORWIDGET_H
#define VIDEOWALLSELECTORWIDGET_H

#include <map>
#include "gui/propertywidget.h"
class QButton;

namespace gui
{


	class VideoWallPropertyWidget: public gui::PropertyWidget
	{
		Q_OBJECT
			
	public:
		VideoWallPropertyWidget(QWidget* parent, const char* name, WFlags fl,
			int nodeID, int inIndex, int controlID,
			const std::map<std::string,std::string>& params,
			IModelControlReceiver& mo);
		
		virtual ~VideoWallPropertyWidget();

		virtual utils::Buffer getValue() const;
		
		virtual void controlValueChanged(int nodeID,int intputIndex,
			const utils::Buffer& newValue);

		
	private:
		QButton* select;
		std::string  current;
	private slots:
		void editRequest();
	};

class PropertyVideoWallWidgetConstructor:public PropertyWidgetConstructor
{
	public:
	PropertyVideoWallWidgetConstructor();
	virtual PropertyWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex,const std::map<std::string,std::string>& ,IModelControlReceiver& mo);
};
	


}

#endif
