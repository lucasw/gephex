#include "logwindow.h"

namespace gui
{
	LogWindow::LogWindow(QWidget* parent)
		: QTextView(parent,"LogFenster")
	{
	}

	void LogWindow::error(const std::string& text)
	{
	  std::string msg = "@error@ " + text;
	  append(msg.c_str());
	}

	void LogWindow::warning(const std::string& text)
	{
	  std::string msg = "@warning@ " + text;
	  append(msg.c_str());
	}

	void LogWindow::log(const std::string& text)
	{
	  std::string msg = "@log@ " + text;
	  append(msg.c_str());
	}
}
