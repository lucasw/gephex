#ifndef INCLUDED_OUTPUT_PLUG_WIDGET_H
#define INCLUDED_OUTPUT_PLUG_WIDGET_H

#include <vector>

#include "plugwidget.h"

namespace gui
{
  class InputPlugWidget;

  class OutputPlugWidget : public gui::PlugWidget
  {
    Q_OBJECT
  private:
    std::vector<const InputPlugWidget*> connectedTo;
    
  protected:
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

  public:
    OutputPlugWidget(QWidget* parent, const char* name, 
		     const QPixmap& free_, const QPixmap& busy_,
		     std::string _name, std::string _type,
		     int _index, int _ID);

    signals:
    void connectionRequestFromOutput(const OutputPlugWidget*,const QPoint& to);

    void underMouse(const OutputPlugWidget*);
	// TODO:
	// somehow qt seems not to no about signals inherited from the superclass
    //	void beginLineDraw();
    //    void redrawLine(const QPoint& from, const QPoint& to);
  };

} // end of namespace gui

#endif


