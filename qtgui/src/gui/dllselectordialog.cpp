#include "dllselectordialog.h"

#include <qlabel.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>

#include "guimodel/moduleinfo.h"
#include "interfaces/imoduleclassloadercontrolreceiver.h"

#include <stdexcept>

namespace gui
{


DllSelectorDialog::DllSelectorDialog( QWidget* parent, const char* name,
				      WFlags fl,
				      IModuleClassLoaderControlReceiver& mclcr,
				      bool loadAll_)
  : QDialog( parent, name, false, fl ), m_loader(mclcr), loadAll(loadAll_)
{
    if ( !name )
	setName( "DllSelectorDialog" );
    resize( 442, 349 ); 
    setProperty( "caption", tr( "Module Laden/Entladen" ) );
    setProperty( "sizeGripEnabled", QVariant( TRUE, 0 ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 20, 10, 140, 20 ) ); 
    TextLabel1->setProperty( "text", tr( "Geladene Module" ) );

    loadButton = new QPushButton( this, "loadButton" );
    loadButton->setGeometry( QRect( 200, 110, 40, 26 ) ); 
    loadButton->setProperty( "text", tr( "<-" ) );

    entladene = new QListBox( this, "entladene" );
    entladene->setGeometry( QRect( 260, 30, 160, 300 ) ); 

    geladene = new QListBox( this, "Geladene" );
    geladene->setGeometry( QRect( 20, 30, 160, 300 ) ); 

    unloadButton = new QPushButton( this, "unloadButton" );
    unloadButton->setGeometry( QRect( 200, 60, 40, 26 ) ); 
    unloadButton->setProperty( "text", tr( "->" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 260, 10, 140, 20 ) ); 
    TextLabel3->setProperty( "text", tr( "entladene Module" ) );

    doneButton = new QPushButton( this, "doneButton" );
    doneButton->setGeometry( QRect( 190, 300, 60, 26 ) ); 
    doneButton->setProperty( "text", tr( "Done" ) );

    // signals and slots connections
    connect( doneButton, SIGNAL( clicked() ), this, SLOT( accept() ) );

	connect( loadButton,   SIGNAL( clicked() ), this, SLOT( loadModuleClass() ) );
	connect( unloadButton, SIGNAL( clicked() ), this, SLOT( unloadModuleClass() ) );
}


DllSelectorDialog::~DllSelectorDialog()
{
}

void DllSelectorDialog::loadModuleClass()
{
	int id = entladene->currentItem();	

	if (id != -1)
	{
		std::string name = entladene->text(id).latin1();
		m_loader.loadModuleClass(name);
	}
}

void DllSelectorDialog::unloadModuleClass()
{
	int id = geladene->currentItem();	

	if (id != -1)
	{
		std::string name = geladene->text(id).latin1();
		m_loader.unloadModuleClass(name);
	}	
}

void DllSelectorDialog::moduleClassLoaded(const std::string& moduleClassName,
										  const ModuleInfo& mi)
{
	QListBoxItem* item = entladene->findItem(moduleClassName.c_str());

	if (item == 0)
	{
		throw std::runtime_error("Mist ist passiert. "
				"Und zwar bei DllSelectorDialog::moduleClassLoaded().");
	}

	delete item;

	geladene->insertItem(moduleClassName.c_str());

	std::string msg = "Loading ";
	emit status(msg + mi.getGroup() + ":" + mi.getName());
}

void DllSelectorDialog::moduleClassUnloaded(const std::string& moduleClassName)
{
	QListBoxItem* item = geladene->findItem(moduleClassName.c_str());

	if (item == 0)
	{
		throw std::runtime_error("Mist ist passiert. "
				"Und zwar bei DllSelectorDialog::moduleClassUnloaded().");
	}

	delete item;

	entladene->insertItem(moduleClassName.c_str());
}

void DllSelectorDialog::moduleClassNameExists(const std::string& moduleClassName)
{
	entladene->insertItem(moduleClassName.c_str());

	if (loadAll)
	  m_loader.loadModuleClass(moduleClassName);
}

} // end of namespace gui
