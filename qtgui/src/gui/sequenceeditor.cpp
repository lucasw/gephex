#include "sequenceeditor.h"

#include <qframe.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qscrollview.h>

#include "sequencewidget.h" 
#include "interfaces/isequencercontrolreceiver.h"

#include "guimodel/iscenesequencer.h"


namespace gui
{

  static const char* const image0_data[] = { 
    "32 32 3 1",
    ". c None",
    "# c #006666",
    "a c #009933",
    "................................",
    "................................",
    "...#............................",
    "...###..........................",
    "...#aa##........................",
    "...#aaaa##......................",
    "...#aaaaaa##....................",
    "...#aaaaaaaa##..................",
    "...#aaaaaaaaaa##................",
    "...#aaaaaaaaaaaa##..............",
    "...#aaaaaaaaaaaaaa##............",
    "...#aaaaaaaaaaaaaaaa##..........",
    "...#aaaaaaaaaaaaaaaaaa##........",
    "...#aaaaaaaaaaaaaaaaaaaa##......",
    "...#aaaaaaaaaaaaaaaaaaaaaa##....",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa##..",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa##..",
    "...#aaaaaaaaaaaaaaaaaaaaaa##....",
    "...#aaaaaaaaaaaaaaaaaaaa##......",
    "...#aaaaaaaaaaaaaaaaaa##........",
    "...#aaaaaaaaaaaaaaaa##..........",
    "...#aaaaaaaaaaaaaa##............",
    "...#aaaaaaaaaaaa##..............",
    "...#aaaaaaaaaa##................",
    "...#aaaaaaaa##..................",
    "...#aaaaaa##....................",
    "...#aaaa##......................",
    "...#aa##........................",
    "...###..........................",
    "...#............................",
    "................................",
    "................................"};

  static const char* const image1_data[] = { 
    "32 32 3 1",
    ". c None",
    "# c #660000",
    "a c #990033",
    "................................",
    "................................",
    "................................",
    "...##########################...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...#aaaaaaaaaaaaaaaaaaaaaaaa#...",
    "...##########################...",
    "................................",
    "................................",
    "................................"};

  static const char* const image2_data[] = { 
    "32 32 3 1",
    ". c None",
    "# c #000000",
    "a c #ffffff",
    "................................",
    "................................",
    "................................",
    ".....#########...#########......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#aaaaaaa#...#aaaaaaa#......",
    ".....#########...#########......",
    "................................",
    "................................",
    "................................"};

  static const char* const loop_image_data[] = { 
    "32 32 3 1",
    ". c None",
    "# c #000000",
    "c c #000000",
    "d c #7f7f7f"
    "................................",
    "................................",
    "................................",
    "................................",
    "................................",
    "............d...................",
    "...........dc...................",
    "..........dcc...................",
    "........dcccc...................",
    "......dcccccc...................",
    "....dccccccccd..................",
    "...dcccccccccccccccccccd........",
    "..ccccccccccccccccccccccc.......",
    "....................dcccccd.....",
    ".....................dcccccd....",
    "......................ccccccd...",
    "......................dccccccd..",
    ".......................dcccccc..",
    "......................dccccccd..",
    "......................ccccccd...",
    ".....................dcccccd....",
    "....................dcccccd.....",
    "..cccccccccccccccccccccccd......",
    "..dccccccccccccccccccccd........",
    "................................",
    "................................",
    "................................",
    "................................",
    "................................",
    "................................",
    "................................",
    "................................"};


  SequenceEditor::SequenceEditor( QWidget* parent,const char* name,
				  WFlags fl,ISequencerControlReceiver& scr_,
				  ISceneSequencer& ss_)
    : QWidget( parent, name, fl ), scr(&scr_), ss(&ss_)
  {
    QPixmap image0( ( const char** ) image0_data );
    QPixmap image1( ( const char** ) image1_data );
    QPixmap image2( ( const char** ) image2_data );
    QPixmap loop_image( ( const char** ) loop_image_data );

    QSpacerItem* spacer1 = new QSpacerItem( 20, 4, QSizePolicy::Minimum,
					    QSizePolicy::Minimum );    
    QSpacerItem* spacer2 = new QSpacerItem( 20, 4, QSizePolicy::Minimum,
					    QSizePolicy::Minimum );

    QSpacerItem* spacer3 = new QSpacerItem( 20, 4, QSizePolicy::Minimum,
					    QSizePolicy::Minimum );
    QSpacerItem* spacer4 = new QSpacerItem( 20, 0, QSizePolicy::Minimum,
					    QSizePolicy::Expanding );
    
    playButton = new QToolButton( this, "playButton" );
    playButton->setProperty( "sizePolicy",
			     QSizePolicy( (QSizePolicy::SizeType)0,
					  (QSizePolicy::SizeType)0,
					  playButton->sizePolicy().hasHeightForWidth() ) );

    playButton->setProperty( "minimumSize", QSize( 30, 16 ) );
    playButton->setProperty( "text", tr( "" ) );
    playButton->setProperty( "pixmap", image0 );

    stopButton = new QToolButton( this, "stopButton" );
    stopButton->setProperty( "sizePolicy",
			     QSizePolicy( (QSizePolicy::SizeType)0,
					  (QSizePolicy::SizeType)0,
					  stopButton->sizePolicy().hasHeightForWidth() ) );

    stopButton->setProperty( "minimumSize", QSize( 30, 16 ) );
    stopButton->setProperty( "text", tr( "" ) );
    stopButton->setProperty( "pixmap", image1 );

    pauseButton = new QToolButton( this, "pauseButton" );
    pauseButton->setProperty( "sizePolicy",
			      QSizePolicy( (QSizePolicy::SizeType)0,
					   (QSizePolicy::SizeType)0,
					   pauseButton->sizePolicy().hasHeightForWidth() ) );
    
    pauseButton->setProperty( "minimumSize", QSize( 30, 16 ) );
    pauseButton->setProperty( "text", tr( "" ) );
    pauseButton->setProperty( "pixmap", image2 );

    QScrollView* sequenceScroller = new QScrollView(this);	

    sequencerWindow = new SequenceWidget( sequenceScroller->viewport(),
					  "sequencerWindow");

	sequencerWindow->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

    sequenceScroller->addChild(sequencerWindow);

    QHBoxLayout* topLayout = new QHBoxLayout(this);
	
    QVBoxLayout* subLayout = new QVBoxLayout();
    subLayout->addItem(spacer1);
    subLayout->addWidget(playButton);
    subLayout->addItem(spacer2);
    subLayout->addWidget(stopButton);
    subLayout->addItem(spacer3);
    subLayout->addWidget(pauseButton);
    subLayout->addItem(spacer4);
    topLayout->addLayout(subLayout);
    topLayout->addWidget(sequenceScroller);

    connect(playButton, SIGNAL( clicked() ), this, SLOT( start() ));
    connect(stopButton, SIGNAL( clicked() ), this, SLOT( stop() ));
    connect(pauseButton, SIGNAL( clicked() ),this, SLOT( pause() ));

    connect(sequencerWindow, SIGNAL( userChangedSceneLength(int,int) ),
	    this, SLOT( changeSceneLength(int,int) ) );
    
    connect(sequencerWindow, SIGNAL( userDeletedScene(int) ),
	    this, SLOT( deleteScene(int) ) );

    playButton->setEnabled(true);
    stopButton->setEnabled(false);
    pauseButton->setEnabled(false);
  }

  SequenceEditor::~SequenceEditor()
  {
  }

  void SequenceEditor::sceneInserted(int id, int pos,
			const std::string& content,int length)
  {
	sequencerWindow->sceneInserted(id,pos,content,length);
  }

  void SequenceEditor::sceneDeleted(int id)
  {
	sequencerWindow->sceneDeleted(id);
  }

  void SequenceEditor::sceneLengthChanged(int id, int newLen)
  {
	  sequencerWindow->sceneLengthChanged(id, newLen);
  }

  void SequenceEditor::sceneMoved(int id, int newPos)
  {
	  sequencerWindow->sceneMoved(id,newPos);
  }

  void SequenceEditor::editSequenceChanged( const std::string& sequenceID )
  {
    emit newEditSequence( sequenceID );
  }

  void SequenceEditor::started()
  {
    playButton->setEnabled(false);
    stopButton->setEnabled(true);
    pauseButton->setEnabled(true);
  }

  void SequenceEditor::stopped()
  {
    playButton->setEnabled(true);
    stopButton->setEnabled(false);
    pauseButton->setEnabled(false);
  }

  void SequenceEditor::paused()
  {
    playButton->setEnabled(true);
    stopButton->setEnabled(true);
    pauseButton->setEnabled(false);
  }

  void SequenceEditor::time(int currentTime)
  {
    sequencerWindow->time(currentTime);
  }

  /*void SequenceEditor::setSceneLength(int sceneLength)
  {
    sequencerWindow->setSceneLength(sceneLength);
  }*/

  int SequenceEditor::getLength() const
  {
    return sequencerWindow->getLength();
  }

  void SequenceEditor::start()
  {
    scr->start();
  }
  
  void SequenceEditor::stop()
  {
    scr->stop();
  }

  void SequenceEditor::pause()
  {
    scr->pause();
  }

  void SequenceEditor::changeSceneLength(int id, int newLength)
  {
	  ss->changeSceneLength(id, newLength);
  }

  void SequenceEditor::deleteScene(int id)
  {
	  ss->deleteScene(id);
  }
}
