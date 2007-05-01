/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#ifndef _INCLUDED_MODULE_BUTTON_H_
#define _INCLUDED_MODULE_BUTTON_H_

#include <QtGui/qtoolbutton.h>
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
	ModuleButton(int id, QWidget* parent, Qt::WFlags fl=0);
	
	void setController(Controller*);


signals:
	void activated(int id);

};

#endif
