#include "picswitch.h"

#include <cassert>

#include <qtoolbutton.h>

namespace gui
{

PicSwitch::PicSwitch(QWidget* parent, const char* name,const QPixmap& pm1, const QPixmap& pm2)
: QWidget(parent,name,0), button(new QToolButton(this)), current(0)
{
	this->resize(18,18);
	pics.push_back(pm1);
	pics.push_back(pm2);

	button->setPixmap(pm1);

	button->resize(18,18);

	connect(button,SIGNAL(clicked()),this,SLOT(pixmapClicked()));
	
	this->setFixedSize(18,18);
}
	
void PicSwitch::setPic(int index)
{
	current = index;
	assert( index == 0 || index == 1);
	button->setPixmap(pics[index]);
}

void PicSwitch::pixmapClicked()
{
	emit clicked(current);
}

} // end of namespace
