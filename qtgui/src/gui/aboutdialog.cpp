
#include "aboutdialog.h"

#include <string>

#include <qlabel.h>
//#include <qlayout.h>
//#include <qvariant.h>
//#include <qtooltip.h>
//#include <qwhatsthis.h>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

AboutDialog::AboutDialog( QWidget* parent/*, const char* name, bool modal, WFlags fl */)
    : QDialog( parent, "about", false, 0)
{    
    resize( 200, 100 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 200, 100 ) );
    setCaption( "About" );

    QLabel* textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 50, 40, 110, 20 ) ); 
	std::string msg = "GePhex ";
	msg += VERSION;
    textLabel1->setText( msg.c_str() );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
AboutDialog::~AboutDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

