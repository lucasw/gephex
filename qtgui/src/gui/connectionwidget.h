#ifndef INCLUDED_CONNECTION_WIDGET_H
#define INCLUDED_CONNECTION_WIDGET_H


#include <qpoint.h>

class QWidget;

namespace gui
{

class InputPlugWidget;
class OutputPlugWidget;

class ConnectionWidget
{

private:
  InputPlugWidget& in;
  OutputPlugWidget& out;

public:
	ConnectionWidget( InputPlugWidget&, OutputPlugWidget&);

	const InputPlugWidget& getInPlug() const { return in; }	
	const OutputPlugWidget& getOutPlug() const { return out; }

	InputPlugWidget& getInPlug() { return in; }	
	OutputPlugWidget& getOutPlug() { return out; }

  bool isInside(QWidget* rel, const QPoint& pos) const;
  void draw(QWidget* rel, QPainter& painter) const;

  
};

} // end of namespace gui
#endif
