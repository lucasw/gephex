#include "filestringview.h"

#include "utils/structreader.h"

#include <qlayout.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qtooltip.h>

namespace gui
{

  class FileStringView: public gui::TypeView
  {
    Q_OBJECT
			
  public:
    FileStringView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params)
    {
      utils::StructReader sr(params);
    
      m_fileMask = sr.getStringValue("file_mask","*.*");
      m_fileMaskName = sr.getStringValue("file_mask_name","All");
    	
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
void selectFile()
    {
      std::string fullMask = m_fileMaskName + " (" + m_fileMask + ")";	
      QString name = QFileDialog::getOpenFileName( m_current.c_str(),
						   fullMask.c_str(),
						   this );
      if (name.length() != 0)
	{
	  utils::Buffer
	    b(reinterpret_cast<const unsigned char*>(name.latin1()),
	      name.length()+1);

	  emit valueChanged(b);
	}
    }

  private:
    QButton* m_select;
    std::string m_current;
    std::string m_fileMask;
    std::string m_fileMaskName;

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
