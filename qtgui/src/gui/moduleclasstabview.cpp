#include "moduleclasstabview.h"

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <qcombobox.h>
#include <qhbuttongroup.h>

#include "guimodel/moduleinfo.h"
#include "guimodel/xpm.h"
#include "modulebutton.h"
#include "uebertab.h"

namespace gui
{


/**
* Implements a second view on the moduleclasses
* consisting of tabs and toolbuttons
*/
  ModuleClassTabView::ModuleClassTabView(QWidget* parent)
: QTabWidget(parent), m_id(-1)
{
	setMaximumSize(2400, 80);
	/*connect(this, SIGNAL(currentChanged(QWidget*)), 
			this, SLOT(getIdOfChanged(QWidget*)));*/
}

ModuleClassTabView::~ModuleClassTabView()
{
}

void ModuleClassTabView::moduleClassLoaded(const std::string& moduleClassName,
					const ModuleInfo& minfo)
{				
	utils::AutoPtr<ModuleInfo> mi ( new ModuleInfo(minfo) );
	infos[moduleClassName] = mi; 

	std::string group = mi->getGroup();
	const char* bla = mi->getName().c_str();
	
	Uebertab* currentGroup = 0;
	std::map<std::string,Uebertab*>::const_iterator
		it = m_groups.find(group);

	
	if (it == m_groups.end())
	{
		currentGroup = new Uebertab(this); //m_menu has to be tabwidget
		//m_menu->insertItem(group.c_str(),currentGroup);
		this->addTab(currentGroup, group.c_str());
		m_groups[group] = currentGroup;
		
		connect(currentGroup,SIGNAL(selected(int)),
			this,SLOT(moduleClassSelected(int)));
		//currentGroup->show();
	}
	else
	{
		currentGroup = it->second;
		
	}
	
	//m_buttons[moduleClassName] = currentGroup;
	

	++m_id;

	//int id = currentGroup->insertItem(QPixmap(mi->getIcon().getPtr()),
	//			    bla, mClassID2Name.size()-1);
	
	ModuleButton* mb1 = new ModuleButton(m_id, currentGroup->buttonGroup(), bla);
	mb1->setMaximumSize(40,40);
	//mb1->setTextLabel(bla);
	mb1->setPixmap(QPixmap(mi->getIcon().getPtr()));
	//mb1->setToolTip(bla);
	mb1->show();
	
//	mb1->setController(m_controller);

	
	//currentGroup->insertItem(mb1, m_id);
	
	mClassID2Name.push_back(moduleClassName);

	m_buttons[moduleClassName] = mb1;
	m_itemIDs[moduleClassName] = m_id;	
}

void ModuleClassTabView::moduleClassUnloaded(const std::string& moduleClassName)
{
	std::map<std::string,int>::iterator 
	  it = m_itemIDs.find(moduleClassName);

	if (it == m_itemIDs.end())
		throw std::runtime_error("Fehler bei moduleClassUnloaded()");

	int id = it->second;
	m_itemIDs.erase(it);

/*	std::map<std::string,QPopupMenu*>::iterator 
	  jt = menues.find(moduleClassName);
	if (jt == menues.end())
		throw std::runtime_error("Fehler bei moduleClassUnloaded()");

	QPopupMenu* menu = jt->second;
	menues.erase(jt);

	ModuleInfoMap::iterator kt = infos.find(moduleClassName);
	if (kt == infos.end())
	  throw std::runtime_error("Fehler bei moduleClassUnloaded()");
	
	infos.erase(kt);

	menu->removeItem(id)*/;
}

void ModuleClassTabView::moduleClassSelected(int mClassID)
{
	emit selectModuleClass(mClassID2Name[mClassID]);
}

const ModuleInfo& 
ModuleClassTabView::getModuleInfo(const std::string& moduleClassName) const
{
	ModuleInfoMap::const_iterator it = infos.find(moduleClassName);

	if (it == infos.end())
	{
		throw std::runtime_error("ModulClassName unbekannt!");
	}

	return *it->second;
}

//TODO: DUMMY!
void ModuleClassTabView::getIdOfChanged(QWidget*)
{

}

} // end of namespace gui
