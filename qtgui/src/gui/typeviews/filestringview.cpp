#include "filestringview.h"

#include <sstream>

#include <qlayout.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qtooltip.h>

#include "utils/structreader.h"

namespace gui
{

  class FileStringView: public gui::TypeView
  {
    Q_OBJECT
			
  public:
    FileStringView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_fileDialog(0)
    {
      utils::StructReader sr(params);
    
	  std::string fullMask = "";
	  
	  for (int i = 1; ; ++i)
	  {
		  std::ostringstream os;
		  os << "file_mask" << i;

		  std::string fileMask = sr.getStringValue(os.str(), "_");
		  std::string fileMaskName = sr.getStringValue(os.str() + "_name", "_");

		  if (fileMask == "_")
			  break;

		  m_fullMask += fileMaskName + " ( " + fileMask + " );;";
	  }      	  

      QHBoxLayout* l = new QHBoxLayout(this);
      m_select = new QPushButton("Select",this);
      m_select->setMinimumSize(40, 33);
      //select->setMaximumSize(60, 20);
      //select->resize(40, 20);	
      m_select->show();
      l->addWidget(m_select);

      connect(m_select, SIGNAL(clicked()), this, SLOT(selectFile()));
    }

    virtual ~FileStringView() {}
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      const char* dumm = reinterpret_cast<const char*>(newValue.getPtr());

      m_select->setText(dumm);
      QToolTip::add(this, dumm);

      m_current = dumm;
    }

private slots:
  void userSelectedFile(const QString& name)
  {
	if (name.length() != 0)
	{
	  utils::Buffer
	    b(reinterpret_cast<const unsigned char*>(name.latin1()),
	      name.length()+1);

	  emit valueChanged(b);
	}
  }

void selectFile()
    {
	  if (m_fileDialog)
		  delete m_fileDialog;      

	  m_fileDialog = new QFileDialog("Choose File", m_fullMask.c_str(), this);
	  m_fileDialog->setDir(m_current.c_str());

	  connect(m_fileDialog, SIGNAL(fileSelected(const QString&)), 
		      this, SLOT(userSelectedFile(const QString&)));

	  m_fileDialog->show();	        
    }

  private:
    QButton* m_select;
    std::string m_current;
    std::string m_fullMask;    
	QFileDialog* m_fileDialog;

  };
	
  // constructor

  FileStringViewConstructor::FileStringViewConstructor()
    : TypeViewConstructor("Datei Auswahl", "file_selector")
  {
  }

  TypeView* FileStringViewConstructor::construct(QWidget* parent,
						 const ParamMap& params) const
  {
    return new FileStringView(parent, params);
  }

}

#include "filestringview_moc.cpp"
