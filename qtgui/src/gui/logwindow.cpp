#include "logwindow.h"

namespace gui
{
	LogWindow::LogWindow(QWidget* parent)
		: QTextView(parent,"LogFenster")
	{
	}

	void LogWindow::exceptionThrown(const std::string& text)
	{
		append(text.c_str());
	}
}
