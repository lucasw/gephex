#ifndef INCLUDED_UEBER_TAB_H
#define INCLUDED_UEBER_TAB_H

#include <qtabbar.h>
#include <qtoolbutton.h>
#include <qtabwidget.h>

class QHButtonGroup;

class Uebertab : public QTabBar
{
private:
	QHButtonGroup* daGroup;
	
public:
	
	/**
	* This class is a derivate of the tabbar provided by qt.
	* It simply holds an automatic layout to group the buttons.
	* @param parent Parent Widget...
	*/
	Uebertab(QTabWidget* parent);
	~Uebertab();
	/**
	* Add a new button to the tab and group it automatically
	*/
	int insertItem(QToolButton*, int);
	QHButtonGroup* buttonGroup();
};


#endif