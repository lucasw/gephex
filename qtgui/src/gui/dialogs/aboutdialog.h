/****************************************************************************
** Form interface generated from reading ui file './aboutdialog.ui'
**
** Created: Tue Dec 16 01:19:32 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.1   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QTextView;
class QPushButton;

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~AboutDialog();

    QLabel* logo_pixmap;
    QLabel* about_label;
    QTextView* gplview;
    QPushButton* ok_button;

protected:
    QVBoxLayout* AboutDialogLayout;
    QHBoxLayout* above_layout;
    QVBoxLayout* logo_layout;
    QHBoxLayout* ok_layout;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // ABOUTDIALOG_H
