#include "uebertab.h"

#include <qlayout.h>
#include <qhbuttongroup.h>

Uebertab::Uebertab(QTabWidget* parent)
: QTabBar(parent)
{
	QVBoxLayout* furz = new QVBoxLayout(this);
	daGroup = new QHButtonGroup(this);
	furz->addWidget(daGroup);
	/*daGroup->setAlignment(AlignLeft);
	daGroup->setAlignment(AlignTop);
	this->setMaximumSize(2000, 60);*/
}

Uebertab::~Uebertab()
{}

QHButtonGroup* Uebertab::buttonGroup()
{
	return daGroup;
}

int Uebertab::insertItem(QToolButton* button, int id)
{
	return daGroup->insert(button, id);
}