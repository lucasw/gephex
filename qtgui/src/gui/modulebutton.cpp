#include "modulebutton.h"

ModuleButton::ModuleButton(int _id, QWidget *parent, const char *name, WFlags fl)
:QToolButton(parent, name), id(_id), m_controller(0)
{}


void ModuleButton::mousePressEvent(QMouseEvent* e){
/*	if(e->button()==LeftButton)
	{
		if (m_controller != 0)
			m_controller->selectModuleType(id);	
	}*/
	emit activated(id);
	QToolButton::mousePressEvent(e);
}

void ModuleButton::setController(Controller* c)
{
	m_controller = c;
}