#include "unboundednumberview.h"

#include <sstream>

#include <utils/structreader.h>
#include <utils/buffer.h>

#include <qvalidator.h>

#include <qlineedit.h>


namespace gui
{

  class UnboundedNumberView: public gui::TypeView
  {
    Q_OBJECT
  public:
    UnboundedNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params)
    {
      m_lineEdit = new QLineEdit("", this, 0);

      m_lineEdit->setValidator(new QDoubleValidator(this));

      connect(m_lineEdit, SIGNAL(returnPressed()),
	      this, SLOT(lineeditChanged()));
    }
		
    virtual ~UnboundedNumberView() {}
		
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      std::string doof = reinterpret_cast<const char*>(newValue.getPtr());
      std::istringstream is(doof);
      double value;
      is >> value;
      std::ostringstream os;
      os.precision(3);
      os << value;

      m_lineEdit->setText(os.str().c_str());
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

  UnboundedNumberViewConstructor::UnboundedNumberViewConstructor()
    : TypeViewConstructor("Zahlen Eingabefeld", "unboundednumber_selector")
  {
  }

  TypeView* UnboundedNumberViewConstructor::construct(QWidget* parent,
						      const ParamMap& params)
    const
  {
    return new UnboundedNumberView(parent, params);
  }
}

#include "unboundednumberview_moc.cpp"
