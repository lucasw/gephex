#ifndef _INCLUDED_NODEWIDGET_H_
#define _INCLUDED_NODEWIDGET_H_

#include <vector>
#include <string>
#include <list>

#include <qwidget.h>
#include <qpixmap.h>

#include "utils/autoptr.h"

class IModelControlReceiver;
class IErrorReceiver;

namespace gui
{
  class OutputPlugWidget;
  class InputPlugWidget;
  class ModuleInfo;

  class NodeProperty;
  class ControlValueDispatcher;
  class IPropertyDescription;

  class IKeyListener;
  class KeyboardManager;

  class NodeWidget : public QWidget
  {

    Q_OBJECT
  private:
    typedef std::vector<utils::AutoPtr<OutputPlugWidget> > OutputVector;
    typedef std::vector<utils::AutoPtr<InputPlugWidget> > InputVektor;
    OutputVector outputs;
    InputVektor inputs;

    int id;
    std::string modName;

    std::vector<QPixmap> pictures; //pointer to the backgroundpics n stuff the node is using

    bool dragMode;
    QPoint clickedPos;
    utils::AutoPtr<IPropertyDescription> m_properties;
    double m_time;

    KeyboardManager& m_kbManager;

    typedef std::list<utils::AutoPtr<IKeyListener> > KeyListenerList;
    KeyListenerList m_keyListeners;

	IErrorReceiver& m_log;
    //private slots:
//void moveInputToProperties(int);

  protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void paintEvent(QPaintEvent*);

    signals:
    void clickedLeft(NodeWidget*);
    void beenRightClicked(NodeWidget*, const QPoint& );
    void moved(NodeWidget*, const QPoint& where);
    void released(NodeWidget*,const QPoint& where);

    // die folgenden signale werden von den inputs/outputs durchgesschleift
    void beginLineDraw();
    void redrawLine(const QPoint& from, const QPoint& to);
    void connectionRequestFromInput(const InputPlugWidget*, const QPoint& to);
    void connectionRequestFromOutput(const OutputPlugWidget*,const QPoint& to);
    void openPopup(InputPlugWidget*);
    void mouseOverInputPlug(const InputPlugWidget*);
    void mouseOverOutputPlug(const OutputPlugWidget*);
  
	void error(const std::string& errorText);

  public:
    NodeWidget(QWidget* parent,const char* name, WFlags fl,
	       int id,const ModuleInfo& _info, 
	       const std::vector<QPixmap>& picz,
	       ControlValueDispatcher&, IModelControlReceiver&,
	       KeyboardManager& kbManager,
		   IErrorReceiver& log);
    ~NodeWidget();

    std::vector<OutputPlugWidget*> getOutputs() const;
    std::vector<InputPlugWidget*> getInputs() const;

    int getID() const { return id; }
    std::string moduleClassName() const { return modName; }

    const OutputPlugWidget* isAtOutput(const QPoint& p) const;
    const InputPlugWidget* isAtInput(const QPoint& p) const;
    
    void setTime(double t);
    double getTime() const;
    
    const IPropertyDescription& getProperties() const;
    
    enum {NODE_WIDGET_PIC=0,INPUTPLUG_WIDGET_FREE_PIC = 1,
	  INPUTPLUG_WIDGET_BUSY_PIC = 2,OUTPUTPLUG_WIDGET_FREE_PIC = 3,
	  OUTPUTPLUG_WIDGET_BUSY_PIC = 4};
	

 public slots:
 // schleifen nur signale von inputs/outputs durch
    void beginLineDraw_();
    void redrawLine_(const QPoint& from, const QPoint& to);
    void connectionRequestFromInput_(const InputPlugWidget*, const QPoint& to);
    void connectionRequestFromOutput_(const OutputPlugWidget*,
				      const QPoint& to);
    void openPopup_( InputPlugWidget*);
    void mouseOverInputPlug_(const InputPlugWidget*);
    void mouseOverOutputPlug_(const OutputPlugWidget*);
	
  };


} // end namespace gui

#endif
