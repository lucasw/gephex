/****************************************************************************
** Form implementation generated from reading ui file './aboutdialog.ui'
**
** Created: Tue Dec 16 01:19:32 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.1   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "./aboutdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtextview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

static const char* const image0_data[] = { 
"40 40 8 1",
"# c #000200",
"a c #8e908d",
"b c #970d17",
". c #9ea09d",
"c c #c0121d",
"d c #e5171d",
"e c #eb2121",
"f c #ff0000",
"........................................",
"#######################################.",
"#######################################.",
"#######################################a",
"#######################################a",
"##########bbbbbbbbbbbbbbbbbb###########a",
"##########bbbbbbbbbbbbbbbbbb###########a",
"##########bbbbbccccccccccccc###########a",
"##########bbbccddddddddddddd###########a",
"##########bbbcdddddddddddddd###########a",
"##########bbcddeeeeeeeeeeeed###########a",
"####bbbbbb######dddeee######ccbbbb#####a",
"####bbbbbb######ccddee######cbbbbb#####a",
"####bbbbbc######bbcdee######bbbbbc#####a",
"####bbbccd######bbcdee######bbbccd#####a",
"####bbbcdd######bbcdde######bbbcdd#####a",
"####bbcdde######bbcdde######bbcdde#####a",
"####bbcddedcbbbbbbcdeedcbbbbbbcdee#####a",
"####bbcddedcbbbbbbcdeedcbbbbbbcdee#####a",
"####bbcddeddccccccddeeddccccccddee#####a",
"####bbcdeeeddddddddeeeeddddddddeee#####a",
"####bbcdeeeeeeeeeeeeffeeeeeeeeeeee#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffffffffffffffffffffffffe#####a",
"####bbcdeffeeeeeeeeefffeeeeeeeeeee#####a",
"####bbcdee######dddeef######dddeee#####a",
"####bbcdde######ccddee######ccddee#####a",
"####bbcdde######bbcdee######bbcdee#####a",
"####bbcdde######bbcdee######bbcdee#####a",
"####bbcdde######bbcdde######bbcdde#####a",
"####bbcddd######bbcddd######bbcddd#####a",
"#######################################a",
"#######################################a",
"#######################################a",
"#######################################a",
".aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};


/*
 *  Constructs a AboutDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
AboutDialog::AboutDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl ),
      image0( (const char **) image0_data )
{
    if ( !name )
	setName( "AboutDialog" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setIcon( image0 );
    setSizeGripEnabled( TRUE );
    AboutDialogLayout = new QVBoxLayout( this, 11, 6, "AboutDialogLayout"); 

    above_layout = new QHBoxLayout( 0, 0, 6, "above_layout"); 

    logo_layout = new QVBoxLayout( 0, 0, 6, "logo_layout"); 

    logo_pixmap = new QLabel( this, "logo_pixmap" );
    logo_pixmap->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, logo_pixmap->sizePolicy().hasHeightForWidth() ) );
    logo_pixmap->setPixmap( image0 );
    logo_pixmap->setScaledContents( TRUE );
    logo_layout->addWidget( logo_pixmap );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum );
    logo_layout->addItem( spacer );
    above_layout->addLayout( logo_layout );

    about_label = new QLabel( this, "about_label" );
    about_label->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)3, 0, 0, about_label->sizePolicy().hasHeightForWidth() ) );
    about_label->setFocusPolicy( QLabel::ClickFocus );
    about_label->setFrameShape( QLabel::NoFrame );
    about_label->setTextFormat( QLabel::RichText );
    about_label->setAlignment( int( QLabel::AlignTop | QLabel::AlignLeft ) );
    above_layout->addWidget( about_label );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    above_layout->addItem( spacer_2 );
    AboutDialogLayout->addLayout( above_layout );

    gplview = new QTextView( this, "gplview" );
    gplview->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, gplview->sizePolicy().hasHeightForWidth() ) );
    AboutDialogLayout->addWidget( gplview );

    ok_layout = new QHBoxLayout( 0, 0, 6, "ok_layout"); 
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    ok_layout->addItem( spacer_3 );

    ok_button = new QPushButton( this, "ok_button" );
    ok_button->setAutoDefault( TRUE );
    ok_button->setDefault( TRUE );
    ok_layout->addWidget( ok_button );
    AboutDialogLayout->addLayout( ok_layout );
    languageChange();
    resize( QSize(458, 524).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( ok_button, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
AboutDialog::~AboutDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void AboutDialog::languageChange()
{
    setCaption( tr( "About" ) );
    about_label->setText( tr( "<qt>\n"
"<h2>  About GePhex </h2>\n"
"\n"
"  This  is Gephex %s [build time %s - %s]. <br>\n"
"  GePhex is an interactive visual effect software. <br>\n"
"  Please visit our hompage at\n"
"  <a href=\"http://www.gephex.org\">www.gephex.org</a>.\n"
"\n"
"<h3>Authors</h3>\n"
"\n"
"<ul>\n"
"   <li>Martin Bayer (martin@gephex.org)</li>\n"
"   <li>Philipp Promesberger (coma@gephex.org)</li>\n"
"   <li>Georg Seidel (georg@gephex.org) </li>\n"
"</ul>\n"
"\n"
"<h3>Credits</h3>\n"
"\n"
" <ul>\n"
"  <li> trolltech (<a href=http://www.trolltech.com> www.trolltech.com </a>) for providing this nice gui toolkit </li>\n"
"  <li> effecTV (<a href=http://effectv.sourceforge.net> effectv.sf.net </a>) for the cool effects </li>\n"
"  <li> sourceforge (<a href=http://www.sourceforge.net> www.sf.net</a>) for the free hosting services </li>\n"
"\n"
"</qt>" ) );
    ok_button->setText( tr( "&Leave" ) );
}

