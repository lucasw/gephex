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

	virtual void exceptionThrown(const std::string& text);
};

}
#endif
