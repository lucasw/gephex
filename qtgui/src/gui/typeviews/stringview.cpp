#include "stringview.h"

#include <iostream>
#include <sstream>

#include <qvalidator.h>
#include <qlineedit.h>

#include <utils/structreader.h>
#include <utils/buffer.h>

namespace gui
{

  class StringView: public gui::TypeView
  {
    Q_OBJECT
  public:
    StringView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params)
    {
      m_lineEdit = new QLineEdit("", this, 0);

      connect(m_lineEdit, SIGNAL(returnPressed()),
	      this, SLOT(lineeditChanged()));
    }
		
    virtual ~StringView() {}
		
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      int len = newValue.getLen();
      const char* raw;
      if (len <= 0)
        {
          raw = "";
          len = 1;
        }
      else
        {
          raw = reinterpret_cast<const char*>(newValue.getPtr());
        }

      if (raw[len-1] != 0)
        {
          std::cout << "ignoring string with missing termination\n";
          return;
        }
      std::string doof( raw, len );

      m_lineEdit->setText(doof.c_str());
    }

public slots:
    void lineeditChanged()
    {
      const char* text = m_lineEdit->text().latin1();

      //      std::cout << "Lineedit text = '" << text << "'" << std::endl;
      utils::Buffer 
	b = utils::Buffer(reinterpret_cast<const unsigned char*>(text),
			  strlen(text)+1);

      emit valueChanged(b);
    }
		
  private:
    QLineEdit* m_lineEdit;
  };

  // constructor

  StringViewConstructor::StringViewConstructor()
    : TypeViewConstructor("text input", "line_edit")
  {
  }

  TypeView* StringViewConstructor::construct(QWidget* parent,
					     const ParamMap& params) const
  {
    return new StringView(parent, params);
  }
}

#include "stringview_moc.cpp"
