#include "fontview.h"


#include <sstream>

#include <qlayout.h>
#include <qfontdialog.h>
#include <qtooltip.h>
#include <qpushbutton.h>

#include "utils/stringtokenizer.h"

namespace gui
{
	
	class FontView : public gui::TypeView
	{
		Q_OBJECT
			
	public:
		
		FontView(QWidget* parent, const ParamMap& params)
			: TypeView(parent, params), m_current("")
		{	
			QHBoxLayout* l = new QHBoxLayout(this);
			m_select = new QPushButton("Select",this);
			m_select->setMinimumSize(40, 33);
			//m_select->setMaximumSize(60, 20);
			//m_select->resize(40, 20);	
			m_select->show();
			l->addWidget(m_select);
			
			connect(m_select, SIGNAL(clicked()), this, SLOT(selectFont()));
		}
		
		~FontView() {}
		
		virtual void valueChange(const utils::Buffer& newValue)
		{
			m_current = reinterpret_cast<const char*>(newValue.getPtr());
			
			QFont f = string2Font(m_current);
			std::ostringstream os;
			os << f.family().latin1() << " " << f.pointSize();
			
			m_select->setText(os.str().c_str());			
			QToolTip::add(this, m_current.c_str());
		}
		
		
	public slots:	
		void selectFont()
		{
			//std::string fullMask = fileMaskName + " (" + fileMask + ")";
			QFont defaultFont = string2Font(m_current);
			bool ok;
			QFont font = QFontDialog::getFont( &ok, defaultFont, this );
			
			if(ok)
			{			
				std::string s = font2String(font);
				utils::Buffer
					bu(reinterpret_cast<const unsigned char*>(s.c_str()), s.length()+1);
				
				emit valueChanged(bu);
			}
			else
			{
				//user cancelled, do nothing, leave default vals
			}
		}
		
	private:
		QButton* m_select;
		std::string m_current;

		static QFont string2Font(const std::string& b)
		{
			if (b == "")
				return QFont("",0);
			
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
		
	};
	
	FontViewConstructor::FontViewConstructor()
		: TypeViewConstructor("font dialog", "font_selector")
	{
	}
	
	
	TypeView*
		FontViewConstructor::construct(QWidget* parent,
		const ParamMap& params) const
	{
		return new FontView(parent, params);
	}
	
}

#include "fontview_moc.cpp"
