#ifndef ASKFORSTRINGDIALOG_H
#define ASKFORSTRINGDIALOG_H

#include <string>
//#include <qvariant.h>
#include <qdialog.h>

class QLabel;
class QLineEdit;
class QPushButton;

namespace gui
{

class AskForStringDialog : public QDialog
{ 
    Q_OBJECT

public:
    AskForStringDialog( QWidget* parent, const std::string& caption, const std::string& text );
    ~AskForStringDialog();

	static std::string open(QWidget* parent, const std::string& caption,
		const std::string& text);

private:
    QLineEdit* LineEdit1;
    QLabel* TextLabel;
    QPushButton* DoneButton;

};

}

#endif

