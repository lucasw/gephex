#include "nodewidget.h"

#include <cassert>

#include <qlabel.h>
#include <qlayout.h>

#include "nodeproperty.h"

#include "guimodel/moduleinfo.h"
#include "guimodel/xpm.h"

#include "utils/structreader.h"

#include "inputplugwidget.h"
#include "outputplugwidget.h"

namespace gui
{

  NodeWidget::NodeWidget(QWidget* parent,const char* name,
			 WFlags fl,int _id,const ModuleInfo& _info,
			 const std::vector<QPixmap>& picz,
			 ControlValueDispatcher& dispatcher, 
			 IModelControlReceiver& mcr)
    : QWidget(parent,name,fl), id(_id), pictures(picz), dragMode(false),
      m_time(0)
  {
    setFixedSize(50, 50);
    setBackgroundPixmap(pictures[NODE_WIDGET_PIC]);
	
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* inputLayout = new QVBoxLayout();
    QVBoxLayout* midLayout = new QVBoxLayout();
    QVBoxLayout* outputLayout = new QVBoxLayout();
	
    modName = _info.getName();

    for(unsigned int i=0;i < _info.getInputs().size(); ++i)
      {
	utils::StructReader sr(_info.getInputs()[i].params);
	bool inPropertyDialog;	
	try 
	  {
	    inPropertyDialog = sr.getBoolValue("hidden");
	  }
	catch (...)
	  {
	    inPropertyDialog = false;
	  }
		
	utils::AutoPtr<InputPlugWidget> 
	  newInput (new InputPlugWidget(this, 0, 
					pictures[INPUTPLUG_WIDGET_FREE_PIC],
					pictures[INPUTPLUG_WIDGET_BUSY_PIC],
					_info.getInputs()[i].name,
					_info.getInputs()[i].type,
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
							    mcr));
  }

  NodeWidget::~NodeWidget()     
  {
  }

  void NodeWidget::mouseMoveEvent(QMouseEvent* e)
  {
    if(dragMode){
      emit moved(this, mapToParent(e->pos()-clickedPos));
    }
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
	
    drawText(10/*abs(50-modName.length())/2*/, 28, modName.c_str());
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
