#include "comboboxstringview.h"

#include <qcombobox.h>
#include <qlayout.h>

#include "utils/structreader.h"
#include "utils/stringtokenizer.h"

namespace gui
{

  class ComboboxStringView : public gui::TypeView
  {
    Q_OBJECT		
  public:
    ComboboxStringView(QWidget* parent,
		       const ParamMap& params)
      : TypeView(parent, params)
    {
      
      m_box = new QComboBox(false, this, "blah");
		
      QVBoxLayout* layout = new QVBoxLayout(this);
      layout->addWidget(m_box);

      utils::StructReader sr(params);

      try {
	std::string values = sr.getStringValue("values");
			
	utils::StringTokenizer tok(values);
	int index = 0;
	for (std::string token = tok.next(",");
	     token != ""; token = tok.next(","), ++index)
	  {
	    m_box->insertItem(token.c_str(), index);
	    m_values[token] = index;
	  }
      }
      catch(...)
	{
	}
		
	  this->resize(m_box->sizeHint());
      connect(m_box, SIGNAL(activated(const QString&)),
	      this,SLOT(comboboxChanged(const QString&)));
    }

    void valueChange(const utils::Buffer& newValue)
    {
      std::string str = reinterpret_cast<const char*>(newValue.getPtr());
      std::map<std::string, int>::const_iterator
	it = m_values.find(str.c_str());
			
      if (it == m_values.end())
	{
	  throw std::runtime_error("Invalid combobox value: '" + str + "'");
	}
			
      m_box->setCurrentItem(it->second);
    }


public slots:
void comboboxChanged(const QString& s)
    {
      const unsigned char* str 
	= reinterpret_cast<const unsigned char*>(s.latin1());

      emit valueChanged(utils::Buffer(str,strlen(s.latin1())+1));
    }

  private:
    std::map<std::string, int> m_values;
    QComboBox* m_box;
  };

  // constructor

  ComboboxStringViewConstructor::ComboboxStringViewConstructor()
    : TypeViewConstructor("Combobox", "combo_box")
  {
  }

  TypeView*
  ComboboxStringViewConstructor::construct(QWidget* parent,
					   const ParamMap& params) const
  {
    return new ComboboxStringView(parent, params);
  }

}

#include "comboboxstringview_moc.cpp"
