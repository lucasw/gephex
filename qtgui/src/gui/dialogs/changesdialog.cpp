/****************************************************************************
** Form implementation generated from reading ui file './changesdialog.ui'
**
** Created: Tue Dec 16 01:19:33 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.1   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "./changesdialog.h"

#include <qvariant.h>
#include <qtextbrowser.h>
#include <qpushbutton.h>
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
 *  Constructs a ChangesDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ChangesDialogBase::ChangesDialogBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl ),
      image0( (const char **) image0_data )
{
    if ( !name )
	setName( "ChangesDialogBase" );
    setIcon( image0 );
    setSizeGripEnabled( TRUE );
    ChangesDialogBaseLayout = new QVBoxLayout( this, 11, 6, "ChangesDialogBaseLayout"); 

    changes_view = new QTextBrowser( this, "changes_view" );
    ChangesDialogBaseLayout->addWidget( changes_view );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( spacer );

    ok_button = new QPushButton( this, "ok_button" );
    ok_button->setAutoDefault( TRUE );
    ok_button->setDefault( TRUE );
    Layout1->addWidget( ok_button );
    ChangesDialogBaseLayout->addLayout( Layout1 );
    languageChange();
    resize( QSize(470, 343).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( ok_button, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ChangesDialogBase::~ChangesDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ChangesDialogBase::languageChange()
{
    setCaption( tr( "Changes" ) );
    ok_button->setText( tr( "&Leave" ) );
}

