/****************************************************************************
** Form interface generated from reading ui file 'videowallcontrolwidget.ui'
**
** Created: Wed May 22 20:53:00 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef VIDEOWALLCONTROLWIDGET_H
#define VIDEOWALLCONTROLWIDGET_H

//#include <buffer.h>
#include <qvariant.h>
#include <qwidget.h>
#include "gui/controlwidget.h"
#include "utils/buffer.h"
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QButton;
class QPushButton;

namespace gui
{
	class VideoWallControlWidget : public ControlWidget
	{ 
		Q_OBJECT
			
	public:
		VideoWallControlWidget(QWidget* parent, 
			const std::string& name, int controlID,
			int nodeID,int inIndex);
		~VideoWallControlWidget();
		virtual void controlValueChanged(int nodeID,int intputIndex,const utils::Buffer& newValue);
		
	private slots:
		//void monitorValueChanged(int xindex, int yindex, const utils::Buffer);
		void colorSelectRequest();
		void srcSetRequest();
		//void apply();
		//void undo();
		
	private:
		QPushButton* monitors[6][6];
		QPushButton* colorChangeButton;
		QPushButton* srcSetButton;
		QPushButton* undoButton;
		QPushButton* applyButton;
		bool itWasMe;
		std::string commandLine;
		
	protected:
		QVBoxLayout* Layout6;
		QVBoxLayout* Layout3;
		QVBoxLayout* Layout4;
	};

	class VideoWallControlWidgetConstructor: public ControlWidgetConstructor
	{
	public:
		VideoWallControlWidgetConstructor();
		virtual ControlWidget* construct(QWidget* parent, const std::string& name, int controlID,
						     int nodeID, int inputIndex);
	};
	
}

#endif // VIDEOWALLCONTROLWIDGET_H

/*QPushButton* mon03;
QPushButton* mon04;
QPushButton* mon02;
QPushButton* mon00;
QPushButton* mon05;
QPushButton* mon14;
QPushButton* mon01;
QPushButton* mon15;
QPushButton* mon11;
QPushButton* mon13;
QPushButton* mon10;
QPushButton* mon31;
QPushButton* mon40;
QPushButton* mon43;
QPushButton* mon51;
QPushButton* mon41;
QPushButton* mon55;
QPushButton* mon50;
QPushButton* mon35;
QPushButton* mon22;
QPushButton* mon21;
QPushButton* mon30;
QPushButton* mon20;
QPushButton* mon25;
QPushButton* mon24;
QPushButton* mon33;
QPushButton* mon23;
QPushButton* mon32;
QPushButton* mon34;
QPushButton* mon44;
QPushButton* mon42;
QPushButton* mon53;
QPushButton* mon45;
QPushButton* mon52;
QPushButton* mon54;
QPushButton* mon12;*/