#include "askforstringdialog.h"

#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

namespace gui
{

AskForStringDialog::AskForStringDialog(QWidget* parent,  const std::string& caption, const std::string& text )
    : QDialog( parent, "diag" , true)
{
    resize( 227, 60 ); 
    setProperty( "caption", tr( caption.c_str() ) );

    LineEdit1 = new QLineEdit( this, "LineEdit1" );
    LineEdit1->setGeometry( QRect( 10, 30, 120, 22 ) ); 

    TextLabel = new QLabel( this, "TextLabel" );
    TextLabel->setGeometry( QRect( 10, 7, 180, 13 ) ); 
    TextLabel->setProperty( "text", tr( text.c_str() ) );

    DoneButton = new QPushButton( this, "DoneButton" );
    DoneButton->setGeometry( QRect( 160, 30, 60, 26 ) ); 
    DoneButton->setProperty( "text", tr( "Done" ) );

    // signals and slots connections    
	connect( DoneButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( LineEdit1, SIGNAL( returnPressed() ), this, SLOT( accept() ) );
}


AskForStringDialog::~AskForStringDialog()
{
}

std::string AskForStringDialog::open(QWidget* parent,
									 const std::string& caption,
									 const std::string& text)
{
	AskForStringDialog dialog(parent, caption, text);

	//dialog.show();

	dialog.exec();

	return dialog.LineEdit1->text().latin1();
}

}
