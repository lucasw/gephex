#include "fontselectorwidget.h"

#include "utils/stringtokenizer.h"
#include <sstream>
#include "qlayout.h"
#include "qfontdialog.h"
#include "qtooltip.h"
#include "qpushbutton.h"

namespace gui
{

  static QFont string2Font(const std::string& b)
  {
    if (b == "")
      return QFont("Courier",14);

    std::string name;
    int weight;
    bool italic;
    bool underline;
    int size;

		
    utils::StringTokenizer st(b.substr(1));
    name = st.next("}");

    std::istringstream is(b.substr(st.getPos()+1));

    is >> size; //ignore width
    is >> size;
    size *= -1;
		
    is >> weight;
    switch(weight)
      {
      case 300: //Light
	weight = 25; //:= WF_LIGHT
	break;
      case 400: //Normal
	weight = 50; //:= WF_NORMAL
	break;
      case 600: //DemiBold
	weight = 63; //:= WF_DEMIBOLD
	break;
      case 700: //Bold
	weight = 75; //:= WF_BOLD
	break;
      case 900: //Black
	weight = 87; //:= WF_BLACK
	break;
      default:
	weight = 50; //normal
	break;
      }

    is >> italic;
    is >> underline;

    QFont font(name.c_str(),size,weight,italic);
    font.setUnderline(underline);
    return font;
  }

  static std::string font2String(const QFont& font)
  {
    std::string name = font.family().latin1();
    int weight = font.weight();
    bool italic = font.italic();
    bool underline = font.underline();
    int size = font.pointSize();
    size = size*(-1);
    std::ostringstream os("");
		
    os << "{";
    os << name;
    os << "} ";
    os << "0"; //width, for now 0...
    os << " "; //module needs negative size val
    os << size;
    os << " ";
    switch(weight)
      {
      case 25: //Light
	os << 300; //:= WF_LIGHT
	break;
      case 50: //Normal
	os << 400; //:= WF_NORMAL
	break;
      case 63: //DemiBold
	os << 600; //:= WF_DEMIBOLD
	break;
      case 75: //Bold
	os << 700; //:= WF_BOLD
	break;
      case 87: //Black
	os << 900; //:= WF_BLACK
	break;
      default:
	os << 400; //normal
	break;
      }
    os << " ";
    if(italic)
      {
	os <<"true";
      }
    else
      {
	os <<"false";
      }
    os << " ";
    if(underline)
      {
	os <<"true";
      }
    else
      {
	os <<"false";
      }
		
    return os.str();			
  }


  PropertyFontSelectorWidget::PropertyFontSelectorWidget(QWidget* parent,
							 const char* name,
							 WFlags fl,
							 int nodeID,
							 int inputIndex,
							 int controlID,
							 const std::map<std::string,std::string>& params,
							 IModelControlReceiver& mo)
    : PropertyWidget(parent, name, fl, nodeID, inputIndex, controlID,mo,params),
      name(""), size(0), weight(0), italic(false), underline(false)
  {	
    QHBoxLayout* l = new QHBoxLayout(this);
    select = new QPushButton("Select",this);
    select->setMinimumSize(40, 33);
    //select->setMaximumSize(60, 20);
    //select->resize(40, 20);	
    select->show();
    l->addWidget(select);
		
    connect(select, SIGNAL(clicked()), this, SLOT(fontSelectRequest()));
  }
	
  utils::Buffer PropertyFontSelectorWidget::getValue() const
  {
    return utils::Buffer(reinterpret_cast<const unsigned char*>(current.c_str()),current.length()+1);
  }

	
	
  void PropertyFontSelectorWidget::fontSelectRequest()
  {
    //std::string fullMask = fileMaskName + " (" + fileMask + ")";
    QFont defaultFont = string2Font(current);
    bool ok;
    QFont font = QFontDialog::getFont( &ok, defaultFont, this );
		
    if(ok)
      {			
	current = font2String(font);
	setValue(getValue());
      }
    else
      {
	//user cancelled, do nothing, leave default vals
      }
  }

  void PropertyFontSelectorWidget::controlValueChanged(int nodeID,
						       int intputIndex,
						       const utils::Buffer& newValue)
  {
    //TODO shouldnt newValue be used????
    QFont f = string2Font(current);
    std::ostringstream os;
    os << f.family().latin1() << " " << f.pointSize();
			
    select->setText(os.str().c_str());			
    QToolTip::add(this,current.c_str());
  }

  // constructor

  PropertyFontSelectorWidgetConstructor::PropertyFontSelectorWidgetConstructor():
    PropertyWidgetConstructor("typ_FontType","font_selector","font_selector")
  {
  }
	

  PropertyWidget*
  PropertyFontSelectorWidgetConstructor::construct(QWidget* parent,
						   const std::string& name,
						   int controlID, int nodeID,
						   int inputIndex,
						   const std::map<std::string,std::string>& params,
						   IModelControlReceiver& mo)
  {
    return new PropertyFontSelectorWidget(parent,"font_selector",0,nodeID,
					  inputIndex,controlID,params,mo);
  }



}
