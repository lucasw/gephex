#include "nodewidget.h"

#include <iostream>
#include <cassert>

#include <qlabel.h>
#include <qlayout.h>
#include <qpainter.h>
#include <qtooltip.h>

#include "nodeproperty.h"

#include "guimodel/moduleinfo.h"
#include "guimodel/xpm.h"

#include "utils/stringtokenizer.h"
#include "utils/structreader.h"
#include "utils/buffer.h"

#include "inputplugwidget.h"
#include "outputplugwidget.h"

#include "base/keyboardmanager.h"
#include "base/ikeylistener.h"
#include "base/key.h"

#include "interfaces/imodelcontrolreceiver.h"
#include "interfaces/ierrorreceiver.h"

namespace gui
{

  class FixedValueKeyListener : public IKeyListener
  {
  public:
    FixedValueKeyListener(IModelControlReceiver& model,
			  int moduleID, int inputIndex,
			  const utils::Buffer& inputValue)
      : m_model(model), m_moduleID(moduleID), m_inputIndex(inputIndex),
	m_inputValue(inputValue)
    {
    }

    virtual ~FixedValueKeyListener() {}
    virtual void keyPressed(const Key& key) {
      m_model.setInputValue(m_moduleID, m_inputIndex, m_inputValue);
    }
    virtual void keyReleased(const Key& key) {}

  private:
    IModelControlReceiver& m_model;
    int m_moduleID;
    int m_inputIndex;
    utils::Buffer m_inputValue;
  };

  class ToggleValueKeyListener : public IKeyListener
  {
  public:
    ToggleValueKeyListener(IModelControlReceiver& model,
			   int moduleID, int inputIndex,
			   const utils::Buffer& inputValue1,
			   const utils::Buffer& inputValue2)

      : m_model(model), m_moduleID(moduleID), m_inputIndex(inputIndex),
	m_inputValue1(inputValue1), m_inputValue2(inputValue2),
	m_state(true)
    {
    }

    virtual ~ToggleValueKeyListener() {}

    virtual void keyPressed(const Key& key) {
      if (m_state)
	m_model.setInputValue(m_moduleID, m_inputIndex, m_inputValue1);
      else
	m_model.setInputValue(m_moduleID, m_inputIndex, m_inputValue2);

      m_state = !m_state;
    }
    virtual void keyReleased(const Key& key) {}

  private:
    IModelControlReceiver& m_model;
    int m_moduleID;
    int m_inputIndex;
    utils::Buffer m_inputValue1;
    utils::Buffer m_inputValue2;
    bool m_state;
  };

  typedef std::list<utils::AutoPtr<IKeyListener> > KeyListenerList;
  static void insertKeyListeners(KeyListenerList& ll,
				 const std::string& keys,
				 const std::string& toggle_keys,
				 KeyboardManager& kbManager,
				 int moduleID, int inputIndex,
				 IModelControlReceiver& model,
				 IErrorReceiver& log)
  {
    utils::StringTokenizer st(keys);
    std::string token = st.next(";");
    while (token != "")
      {
	utils::StringTokenizer stIntern(token);

	std::string keyName = stIntern.next("[");
	std::string keyValue = stIntern.next("[]");

	//std::cout << "Parsed key '" << keyName << "[" << keyValue << "]'"
	//  << std::endl;

	gui::Key k(keyName);
	utils::Buffer
	  value(reinterpret_cast<const unsigned char*>(keyValue.c_str()),
		keyValue.length() + 1);

	utils::AutoPtr<IKeyListener> 
	  kl (new FixedValueKeyListener(model, moduleID, inputIndex,
					value));

	ll.push_back(kl);

	kbManager.registerListener(*kl, k);
	
	token = st.next(";");
      }

    utils::StringTokenizer stt(toggle_keys);
    token = stt.next(";");
    while (token != "")
      {
	utils::StringTokenizer stIntern(token);

	std::string keyName = stIntern.next("[");
	std::string keyValue1 = stIntern.next("[,");
	std::string keyValue2 = stIntern.next(",]");

	//std::cout << "Parsed toggle_key '" << keyName 
	//	  << "[" << keyValue1 << "," << keyValue2<< "]'"
	//	  << std::endl;

	try {
	gui::Key k(keyName);
	utils::Buffer
	  value1(reinterpret_cast<const unsigned char*>(keyValue1.c_str()),
		keyValue1.length() + 1);

	utils::Buffer
	  value2(reinterpret_cast<const unsigned char*>(keyValue2.c_str()),
		 keyValue2.length() + 1);

	utils::AutoPtr<IKeyListener> 
	  kl (new ToggleValueKeyListener(model, moduleID, inputIndex,
					 value1, value2));

	ll.push_back(kl);

	kbManager.registerListener(*kl, k);
	}
	catch(std::runtime_error& e) {
		//TODO we need a logger here!:
		//nWidget->displayErrorMessage(e.what());
		log.error(e.what());
		std::cerr << e.what() << std::endl;
	}

	token = stt.next(";");
      }
  }

  static void removeKeyListeners(KeyListenerList& ll,
				 KeyboardManager& kbManager)
  {
    for (KeyListenerList::const_iterator it = ll.begin();
	     it != ll.end(); ++it)
      {
	    kbManager.removeListener(*(*it));
      }
  }




  NodeWidget::NodeWidget(QWidget* parent,const char* name,
			 WFlags fl,int _id,const ModuleInfo& _info,
			 const std::vector<QPixmap>& picz,
			 const utils::AutoPtr<ControlValueDispatcher>& dispatcher, 
			 IModelControlReceiver& mcr,
			 KeyboardManager* kbManager,
			 IErrorReceiver& log,
			 const std::string& media_path)
    : QWidget(parent,name,fl), id(_id), pictures(picz), dragMode(false),
      m_time(0), m_kbManager(kbManager), m_log(log)
  {
    setFixedSize(50, 50);
    setBackgroundPixmap(pictures[NODE_WIDGET_PIC]);
	
    this->setMouseTracking(true);

    modName = _info.getName();
    m_group = _info.getGroup();
    m_icon = new QPixmap(_info.getIcon().getPtr());
    QToolTip::add(this, (m_group + ":" + modName).c_str());

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* inputLayout = new QVBoxLayout();
    QVBoxLayout* midLayout = new QVBoxLayout();
    QVBoxLayout* outputLayout = new QVBoxLayout();

    for(unsigned int i=0;i < _info.getInputs().size(); ++i)
      {
	utils::StructReader sr(_info.getInputs()[i].params);

        if (m_kbManager)
          {
            std::string keys = sr.getStringValue("keys", "");
            std::string toggle_keys = sr.getStringValue("toggle_keys", "");

            insertKeyListeners(m_keyListeners, keys, toggle_keys, *m_kbManager,
                               id, i, mcr, m_log);
          }

	bool inPropertyDialog = sr.getBoolValue("hidden", false);
		
	utils::AutoPtr<InputPlugWidget> 
	  newInput (new InputPlugWidget(this, 0, 
					pictures[INPUTPLUG_WIDGET_FREE_PIC],
					pictures[INPUTPLUG_WIDGET_BUSY_PIC],
					_info.getInputs()[i].name,
					_info.getInputs()[i].type,
					_info.getInputs()[i].params,
					i,id,inPropertyDialog));
		
	inputs.push_back(newInput);
		
	inputLayout->addWidget(&*inputs[i]);

	if(inPropertyDialog)
	  {	
	    inputs[i]->hide();
	  }
	else
	  {
	    inputs[i]->show();
	  }
		
	connect(&*inputs[i], SIGNAL(beginLineDraw()), this, 
		SLOT(beginLineDraw_()));

	connect(&*inputs[i], SIGNAL(redrawLine(const QPoint&,const QPoint&)),
		this, SLOT(redrawLine_(const QPoint&,const QPoint&)));

	connect(&*inputs[i],
		SIGNAL(connectionRequestFromInput(const InputPlugWidget*,
						  const QPoint&)),
		this, SLOT(connectionRequestFromInput_(const InputPlugWidget*,
						       const QPoint&)));

	connect(&*inputs[i], SIGNAL(beenRightClicked( InputPlugWidget*)), 
		this, SLOT(openPopup_( InputPlugWidget*)));

	connect(&*inputs[i], SIGNAL(underMouse(const InputPlugWidget*)), 
		this, SLOT(mouseOverInputPlug_(const InputPlugWidget*)));

	//	connect(inputs[i], SIGNAL(wannaBeAProperty(int)), 
	//		this, SLOT(moveInputToProperties(int)));
      }
	
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(midLayout);
	
    for(unsigned int j=0;j<_info.getOutputs().size();j++)
      {
	utils::AutoPtr<OutputPlugWidget> 
	  newOutput(new OutputPlugWidget(this, 0,
					 pictures[OUTPUTPLUG_WIDGET_FREE_PIC],
					 pictures[OUTPUTPLUG_WIDGET_BUSY_PIC],
					 _info.getOutputs()[j].name,
					 _info.getOutputs()[j].type, j,id));
	outputs.push_back(newOutput);
	outputLayout->addWidget(&*outputs[j]);
	outputs[j]->show();
		
	connect(&*outputs[j], SIGNAL(beginLineDraw()),
		this, SLOT(beginLineDraw_()));
	connect(&*outputs[j], SIGNAL(redrawLine(const QPoint&,const QPoint&)),
		this, SLOT(redrawLine_(const QPoint&,const QPoint&)));
		
	connect(&*outputs[j], 
		SIGNAL(connectionRequestFromOutput(const OutputPlugWidget*,
						   const QPoint&)),
		this,
		SLOT(connectionRequestFromOutput_(const OutputPlugWidget*,
						  const QPoint&)));

	connect(&*outputs[j], SIGNAL(underMouse(const OutputPlugWidget*)), 
		this, SLOT(mouseOverOutputPlug_(const OutputPlugWidget*)));
      }
	
    mainLayout->addLayout(outputLayout);
	
    m_properties = 
      utils::AutoPtr<IPropertyDescription>(new NodeProperty(_info,
							    inputs,
							    dispatcher,
							    mcr,
							    media_path));
  }

  NodeWidget::~NodeWidget()     
  {
    if (m_kbManager)
      removeKeyListeners(m_keyListeners, *m_kbManager);
    delete m_icon;
  }

  void NodeWidget::mouseMoveEvent(QMouseEvent* e)
  {
    if(dragMode){
      emit moved(this, mapToParent(e->pos()-clickedPos));
    }

    emit mouseOverNode(this);
  }

  void NodeWidget::mousePressEvent(QMouseEvent* e)
  {
    clickedPos = e->pos();
    if(e->button() == LeftButton){
      dragMode = true;
      emit clickedLeft(this);
    }
    else if (e->button() == RightButton)
      {
	emit beenRightClicked(this, e->pos());
      }
  }

  void NodeWidget::mouseReleaseEvent(QMouseEvent* e)
  {
    if (dragMode)
      {
	dragMode = false;
	emit released(this,mapToParent(e->pos()-clickedPos));
      }
  }

  void NodeWidget::paintEvent(QPaintEvent* /*e*/)
  {
    QPainter p(this);
    p.drawPixmap (5,5, *icon());
    //p.drawText(10/*abs(50-modName.length())/2*/, 28, modName.c_str());
  }

  void NodeWidget::setTime(double t)
  {
    m_time = t;
  }

  double NodeWidget::getTime() const
  {
    return m_time;
  }

  const IPropertyDescription& NodeWidget::getProperties() const
  {
    return *m_properties;
  }

  void NodeWidget::beginLineDraw_()
  {
    emit beginLineDraw();
  }

  void NodeWidget::redrawLine_(const QPoint& from, const QPoint& to)
  {
    emit redrawLine(from,to);
  }

  void NodeWidget::connectionRequestFromInput_(const InputPlugWidget* in,
					       const QPoint& to)
  {
    emit connectionRequestFromInput(in,to);
  }

  void NodeWidget::connectionRequestFromOutput_(const OutputPlugWidget* out,
					       const QPoint& to)
  {
    emit connectionRequestFromOutput(out,to);
  }

  void NodeWidget::openPopup_(InputPlugWidget* in)
  {
    emit openPopup(in);
  }

  void NodeWidget::mouseOverInputPlug_(const InputPlugWidget* in)
  {
    emit mouseOverInputPlug(in);
  }

  void NodeWidget::mouseOverOutputPlug_(const OutputPlugWidget* out)
  {
    emit mouseOverOutputPlug(out);
  }


  std::vector<OutputPlugWidget*> NodeWidget::getOutputs() const 
  {
    std::vector<OutputPlugWidget*> temp;
    for (OutputVector::const_iterator it = outputs.begin();
	 it != outputs.end(); ++it)
      {
	temp.push_back(it->c_ptr());
      }
    return temp;
  }

  std::vector<InputPlugWidget*> NodeWidget::getInputs() const 
  {
    std::vector<InputPlugWidget*> temp;
    for (InputVektor::const_iterator it = inputs.begin();
	 it != inputs.end(); ++it)
      {
	temp.push_back(it->c_ptr());
      }
    return temp;
  }



  const OutputPlugWidget* NodeWidget::isAtOutput(const QPoint& p) const
  {
    for (unsigned int i = 0; i < outputs.size(); ++i)
      {
	if(outputs[i]->geometry().contains(p - this->pos()))
	  {
	    return &*outputs[i];
	  }
      }
    return 0;
  }


  const InputPlugWidget* NodeWidget::isAtInput(const QPoint& p) const
  {
    for (unsigned int i = 0; i < inputs.size(); ++i)
      {
	if(inputs[i]->geometry().contains(p-this->pos()))
	  {
	    return &*inputs[i];
	  }
      }
    return 0;
  }

} // end of namespace gui
