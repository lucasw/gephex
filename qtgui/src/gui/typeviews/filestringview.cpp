#include "filestringview.h"

#include <sstream>

#include <qlayout.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qtooltip.h>
#include <qmessagebox.h>

#include "utils/structreader.h"

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
  void userSelectedFile(const QString& name_)
  {
  }

void selectFile()
    {
	std::string path;
    int pos = m_current.find_last_of("/");
	//if (pos == std::string::npos)
		//pos = m_current.find_last_of("\\");

	if (pos != std::string::npos)
		path = m_current.substr(0, pos);

	QStringList files = QFileDialog::getOpenFileNames (m_fullMask.c_str(), 
							 path.c_str(), 
							 this, "file selector",
							 "choose Files");

      QString name;

//      QStringList::const_iterator it=files.begin();
	  QStringList::Iterator it=files.begin();
      
      if (it!=files.end())
	{
	  name+=*it++;
	}

      while(it!=files.end())
	{
	  name+= "," + *it++;
	}
      
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
    std::string m_fullMask;    
  };
	
  // constructor

  FileStringViewConstructor::FileStringViewConstructor()
    : TypeViewConstructor("file dialog", "file_selector")
  {
  }

  TypeView* FileStringViewConstructor::construct(QWidget* parent,
						 const ParamMap& params) const
  {
    return new FileStringView(parent, params);
  }

}

#include "filestringview_moc.cpp"
