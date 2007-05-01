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

#include "picswitch.h"

#include <cassert>

#include <QtGui/qtoolbutton.h>

namespace gui
{

PicSwitch::PicSwitch(QWidget* parent,
		     const QPixmap& pm1,
		     const QPixmap& pm2)
: QToolButton(parent), current(0)
{
	this->setFixedSize(18,18);
	pics.push_back(pm1);
	pics.push_back(pm2);

	setIcon(QIcon(pm1));

	connect(this,SIGNAL(clicked()),this,SLOT(pixmapClicked()));
}
	
void PicSwitch::setPic(int index)
{
	current = index;
	assert( index == 0 || index == 1);
	setIcon(QIcon(pics[index]));
}

void PicSwitch::pixmapClicked()
{
	emit clicked(current);
}

} // end of namespace
