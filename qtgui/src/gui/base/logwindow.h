#ifndef INCLUDED_LOG_WINDOW_H
#define INCLUDED_LOG_WINDOW_H

#include <qtextview.h>

#include "interfaces/ierrorreceiver.h"

namespace gui
{

class LogWindow : public QTextView,
  public IErrorReceiver
{
public:
	LogWindow(QWidget* parent);

	virtual void error(const std::string& text);
	virtual void warning(const std::string& text);
	virtual void log(const std::string& text);
};

}
#endif
