#include "dllselectordialog.h"

#include <sstream>
#include <stdexcept>

#include <qlabel.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qmessagebox.h>

#include "guimodel/moduleinfo.h"
#include "interfaces/imoduleclassloadercontrolreceiver.h"


namespace gui
{


  DllSelectorDialog::DllSelectorDialog(QWidget* parent, const char* name,
                                       WFlags fl,
                                       IModuleClassLoaderControlReceiver& mclcr,
                                       bool loadAll_)
    : QDialog( parent, name, false, fl ), m_loader(mclcr), loadAll(loadAll_),
      m_num_module_classes(0), m_num_loaded_classes(0)
  {
    if ( !name )
      setName( "DllSelectorDialog" );
    resize( 442, 349 ); 
    setProperty( "caption", tr( "Load/Unload Plugins" ) );
    setProperty( "sizeGripEnabled", QVariant( TRUE, 0 ) );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 20, 10, 140, 20 ) ); 
    TextLabel1->setProperty( "text", tr( "Loaded Plugins" ) );

    loadButton = new QPushButton( this, "loadButton" );
    loadButton->setGeometry( QRect( 200, 110, 40, 26 ) ); 
    loadButton->setProperty( "text", tr( "<-" ) );

    entladene = new QListBox( this, "loaded" );
    entladene->setGeometry( QRect( 260, 30, 160, 300 ) ); 

    geladene = new QListBox( this, "Loaded" );
    geladene->setGeometry( QRect( 20, 30, 160, 300 ) ); 

    unloadButton = new QPushButton( this, "unloadButton" );
    unloadButton->setGeometry( QRect( 200, 60, 40, 26 ) ); 
    unloadButton->setProperty( "text", tr( "->" ) );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 260, 10, 140, 20 ) ); 
    TextLabel3->setProperty( "text", tr( "Unloaded Plugins" ) );

    doneButton = new QPushButton( this, "doneButton" );
    doneButton->setGeometry( QRect( 190, 300, 60, 26 ) ); 
    doneButton->setProperty( "text", tr( "Done" ) );

    // signals and slots connections
    connect(doneButton,   SIGNAL(clicked()), this, SLOT(accept()));
    connect(loadButton,   SIGNAL(clicked()), this, SLOT(loadModuleClass()));
    connect(unloadButton, SIGNAL(clicked()), this, SLOT(unloadModuleClass()));
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
                                 "Und zwar bei DllSelectorDialog::"
                                 "moduleClassLoaded().");
      }

    delete item;

    ++m_num_loaded_classes;
    geladene->insertItem(moduleClassName.c_str());

    int rest = m_num_module_classes - m_num_loaded_classes;
    std::ostringstream os;
    os << "Loading " << mi.getGroup() << ":" 
       << mi.getName() << " (Remaining: " << rest<< ")";
    emit status(os.str());

    m_loaded.insert(std::make_pair(moduleClassName, true));
  }

  void
  DllSelectorDialog::moduleClassUnloaded(const std::string& moduleClassName)
  {
    QListBoxItem* item = geladene->findItem(moduleClassName.c_str());

    if (item == 0)
      {
        throw std::runtime_error("Mist ist passiert. "
                                 "Und zwar bei DllSelectorDialog::"
                                 "moduleClassUnloaded().");
      }

    --m_num_loaded_classes;
    delete item;

    entladene->insertItem(moduleClassName.c_str());

    std::map<std::string, bool>::iterator it = m_loaded.find(moduleClassName);
    if (it == m_loaded.end())
      {
        QMessageBox::information(0, "Error", "Mist hier");
      }
    else
      {
        m_loaded.erase(it);
      }
  }

  void
  DllSelectorDialog::moduleClassNameExists(const std::string& moduleClassName)
  {
    ++m_num_module_classes;
    entladene->insertItem(moduleClassName.c_str());
    m_classes.push_back(moduleClassName);
  }

  void DllSelectorDialog::clear()
  {
    entladene->clear();
    geladene->clear();
    m_loaded.clear();
    m_classes.clear();
    m_num_module_classes = 0;
    m_num_loaded_classes = 0;
  }

  void DllSelectorDialog::syncStarted()
  {
    clear();
  }

  void DllSelectorDialog::syncFinished()
  {
    if (loadAll)
      {
        for (std::list<std::string>::const_iterator it = m_classes.begin();
             it != m_classes.end(); ++it)
          {
            if (m_loaded.find(*it) == m_loaded.end())
              m_loader.loadModuleClass(*it);
          }
      }
  }

  void DllSelectorDialog::done( int r )
  {
    emit closed();
    QDialog::done(r);
  }

  void DllSelectorDialog::accept()
  {
    emit closed();
    QDialog::accept();
  }

  void DllSelectorDialog::reject()
  {
    emit closed();
    QDialog::reject();
  }

} // end of namespace gui
