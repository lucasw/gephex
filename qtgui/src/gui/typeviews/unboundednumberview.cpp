#include "unboundednumberview.h"

#include <sstream>
#include <cmath>

#include <qvalidator.h>
#include <qlineedit.h>

#include <utils/structreader.h>
#include <utils/buffer.h>

namespace gui
{

  class UnboundedNumberView: public gui::TypeView
  {
    Q_OBJECT
  public:
    UnboundedNumberView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params), m_value(-1.0)
    {
	  utils::StructReader sr(params);
      m_lineEdit = new QLineEdit("", this, 0);

	  int precision = sr.getIntValue("precision", 6);
	  std::string display_format = sr.getStringValue("display_format",
		                                             "auto");

      m_lineEdit->setValidator(new QDoubleValidator(this));

	  m_os.precision(precision);
	  if (display_format == "fixed")
		  m_os.setf(std::ios::fixed, std::ios::floatfield);
	  else if (display_format == "scientific")
		  m_os.setf(std::ios::scientific, std::ios::floatfield);
	  // else don't set -> automatic mode

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

	  if (fabs(value - m_value) > 0.00001)
	  {
		  m_value = value;
		  m_os.str("");		  
		  m_os << value;
		  
		  m_lineEdit->setText(m_os.str().c_str());
	  }
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
	double m_value;
	std::ostringstream m_os;
  };

  // constructor

  UnboundedNumberViewConstructor::UnboundedNumberViewConstructor()
    : TypeViewConstructor("number input", "unboundednumber_selector")
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
