#include "checkboxnumberview.h"

#include <sstream>
#include <cmath>
#include <vector>

#include <qlayout.h>
#include <qvbuttongroup.h>
#include <qcheckbox.h>
//#include <qmessagebox.h>

#include "utils/structreader.h"
#include "utils/stringtokenizer.h"


/**
 *
 * CheckBox
 *
 */
namespace gui
{


  class CheckBoxNumberView : public gui::TypeView
  {
    Q_OBJECT
			
  public:
    CheckBoxNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_value(0)
    {
      utils::StructReader sr(params);	  
      
	  QVBoxLayout* l = new QVBoxLayout(this);
      m_group = new QVButtonGroup(this);	  
	  l->addWidget(m_group);

	  // parameter aus params angucken
      try {
        std::string values = sr.getStringValue("values");
		  
        utils::StringTokenizer tok(values);
        int index = 0;
        for (std::string token = tok.next(",");
             token != ""; token = tok.next(","), ++index)
          {
            QCheckBox* cb = new QCheckBox(token.c_str(), m_group, "cb");
			QFont f = cb->font();
			f.setPointSize(8);
			cb->setFont(f);
            m_group->insert(cb, index);
          }
      }
      catch(...)
	  {
	  }
	  
	  /*QSize min  = m_group->minimumSize();
	  QSize max  = m_group->maximumSize();
	  QSize pref = m_group->sizeHint();
	  std::ostringstream os;
	  os << "width     = " << m_group->width() << "\t height     = " << m_group->height() << "\n";
	  os << "minWidth  = " << min.width()      << "\t minHeight  = " << min.height() << "\n";
	  os << "maxWidth  = " << max.width()      << "\t maxHeight  = " << max.height() << "\n";
	  os << "prefWidth = " << pref.width()     << "\t prefHeight = " << pref.height() << "\n";
	  QMessageBox::information( 0, "Info", os.str().c_str() );*/
      
      
	  this->resize(m_group->sizeHint());
	  
	  
      connect(m_group, SIGNAL(clicked(int)), this, SLOT(boxToggled(int)));
	  
      m_group->show();
    }
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
      double raw;
      is >> raw;
	
	  int new_value = (int) floor(raw+0.5);

	  if (m_value != new_value)
	  {
		  m_value = new_value;
		  
		  for (int i = 0; i < m_group->count(); ++i)
		  {
			  QCheckBox* cb = dynamic_cast<QCheckBox*>(m_group->find(i));
			  if (m_value & (1 << i))		
				  cb->setChecked(true);      
			  else
				  cb->setChecked(false);
		  }
	  }
    }
		
private slots:
void boxToggled(int index)
    {
      std::ostringstream os;			
      QCheckBox* cb = dynamic_cast<QCheckBox*>(m_group->find(index));
      if (cb->isChecked())
        {
          m_value |= (1 << index);
        }
      else
        {
          m_value &= ~(1 << index);
        }
      
      os << m_value;

      utils::Buffer 
        b(reinterpret_cast<const unsigned char*>(os.str().c_str()),
          os.str().length()+1);
      emit valueChanged(b);
    }

  private:
    QVButtonGroup* m_group;
    int m_value;
  };

  // constructor

  CheckBoxNumberViewConstructor::CheckBoxNumberViewConstructor():
    TypeViewConstructor("check box", "check_box")
  {
  }
	

  TypeView* CheckBoxNumberViewConstructor::construct(QWidget* parent,
                                                     const ParamMap& params)
    const
  {
    return new CheckBoxNumberView(parent, params);
  }

}

#include "checkboxnumberview_moc.cpp"

