/****************************************************************************
** Form interface generated from reading ui file './changesdialog.ui'
**
** Created: Tue Dec 16 01:19:33 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.1   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CHANGESDIALOGBASE_H
#define CHANGESDIALOGBASE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTextBrowser;
class QPushButton;

class ChangesDialogBase : public QDialog
{
    Q_OBJECT

public:
    ChangesDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ChangesDialogBase();

    QTextBrowser* changes_view;
    QPushButton* ok_button;

protected:
    QVBoxLayout* ChangesDialogBaseLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // CHANGESDIALOGBASE_H
