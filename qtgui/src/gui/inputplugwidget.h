#ifndef INCLUDED_INPUT_PLUG_WIDGET_H
#define INCLUDED_INPUT_PLUG_WIDGET_H

#include <map>
#include <string>

#include "plugwidget.h"

namespace gui
{

  class OutputPlugWidget;

class InputPlugWidget : public gui::PlugWidget
  {
    Q_OBJECT

  public:
    typedef std::map<std::string, std::string> ParamMap;
    InputPlugWidget(QWidget* parent, const char* name,
		    const QPixmap& free_, const QPixmap& busy_,  
		    std::string _name, std::string _type,
		    const ParamMap& params,
		    int _index, int _ID, bool _inPropertyDialog);

    void setVisible();
    void setInvisible();
    bool isVisible() const;

    const ParamMap& getParams() const;

    signals:
    void connectionRequestFromInput(const InputPlugWidget*, const QPoint& to);
    void beenRightClicked( InputPlugWidget*);

    void underMouse(const InputPlugWidget*);
	// TODO:
	// somehow qt seems not to no about signals inherited from the superclass
    //	void beginLineDraw();
    //    void redrawLine(const QPoint& from, const QPoint& to);

    //    void wannaBeAProperty(int);
	
  protected:
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

  private:
    const OutputPlugWidget* connectedTo;
    bool inPropertyDialog;
    ParamMap m_params;
  };

} // end of namespace gui

#endif

