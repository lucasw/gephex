#ifndef INCLUDED_DLL_SELECTOR_DIALOG_H
#define INCLUDED_DLL_SELECTOR_DIALOG_H

#include <map>
#include <list>

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

  void clear();

  void syncStarted();
  void syncFinished();

signals:
	void status(const std::string& s);

	void closed();

protected slots:
  virtual void done( int r );
  virtual void accept() ;
  virtual void reject() ;

private slots:
	void loadModuleClass();
	void unloadModuleClass();
#if (QT_VERSION < 0x030100)
	void setShown( bool _show ) {
		if (_show)
			show();
		else
			hide();
	}
#endif

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
  int m_num_module_classes;
  int m_num_loaded_classes;

  std::map<std::string, bool> m_loaded;
  std::list<std::string> m_classes;

};

} // end of namespace gui

#endif
