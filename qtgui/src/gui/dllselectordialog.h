#ifndef INCLUDED_DLL_SELECTOR_DIALOG_H
#define INCLUDED_DLL_SELECTOR_DIALOG_H

#include <qvariant.h>
#include <qdialog.h>

#include "interfaces/imoduleclassnamereceiver.h"
#include "guimodel/imoduleclassview.h"

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QListBox;
class QListBoxItem;
class QPushButton;

class IModuleClassLoaderControlReceiver;

namespace gui
{

class DllSelectorDialog : public QDialog,
			  public IModuleClassNameReceiver,
			  public IModuleClassView
{ 
    Q_OBJECT

public:
    DllSelectorDialog( QWidget* parent, const char* name, WFlags fl,
		       IModuleClassLoaderControlReceiver& mclcr,
		       bool loadAll);
    ~DllSelectorDialog();

  void moduleClassLoaded(const std::string& moduleClassName,
			 const ModuleInfo& mi);

  void moduleClassUnloaded(const std::string& moduleClassName);
  
  void moduleClassNameExists(const std::string& moduleClassName);

private slots:
	void loadModuleClass();
	void unloadModuleClass();


private:
    QLabel* TextLabel1;
    QPushButton* loadButton;
    QListBox* entladene;
    QListBox* geladene;
    QPushButton* unloadButton;
    QLabel* TextLabel3;
    QPushButton* doneButton;

    IModuleClassLoaderControlReceiver& m_loader;

  bool loadAll;

};

} // end of namespace gui

#endif
