#ifndef _INCLUDED_MODULE_BUTTON_H_
#define _INCLUDED_MODULE_BUTTON_H_

#include <qtoolbutton.h>
#include <string>

class Controller;

class ModuleButton: public QToolButton{
Q_OBJECT
private:
	int id;
	Controller* m_controller;

protected:
	virtual void mousePressEvent ( QMouseEvent * ); 

public:
	ModuleButton(int id, QWidget* parent, const char* name=0, WFlags fl=0);
	
	void setController(Controller*);


signals:
	void activated(int id);

};

#endif
