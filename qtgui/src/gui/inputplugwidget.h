#ifndef INCLUDED_INPUT_PLUG_WIDGET_H
#define INCLUDED_INPUT_PLUG_WIDGET_H

#include "plugwidget.h"

namespace gui
{

  class OutputPlugWidget;

class InputPlugWidget : public gui::PlugWidget
  {
    Q_OBJECT
  private:
    const OutputPlugWidget* connectedTo;
    bool inPropertyDialog;
	
  protected:
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

  public:
    InputPlugWidget(QWidget* parent, const char* name,
		    const QPixmap& free_, const QPixmap& busy_,  
		    std::string _name, std::string _type,
		    int _index, int _ID, bool _inPropertyDialog);

    void setVisible();
    void setInvisible();
    bool isVisible() const;

    signals:
    void connectionRequestFromInput(const InputPlugWidget*, const QPoint& to);
    void beenRightClicked( InputPlugWidget*);

    void underMouse(const InputPlugWidget*);
	// TODO:
	// somehow qt seems not to no about signals inherited from the superclass
    //	void beginLineDraw();
    //    void redrawLine(const QPoint& from, const QPoint& to);

    //    void wannaBeAProperty(int);
  };

} // end of namespace gui

#endif

