#include "videowallcontrollwidget.h"

#include <iostream>

#include <qlayout.h>
#include <qabstractlayout.h>

namespace gui

{

  VideoWallCommand::VideoWallCommand(int xPos,int yPos,
				     int boxSize,
				     SignalType signalType,QColor color)
    :	m_xPos(xPos),m_yPos(yPos),m_boxSize(boxSize),
	m_signalType(signalType),m_color(color)
  {
  }

  std::ostream& operator<< (std::ostream& s,const VideoWallCommand& cmd)
  {
    //TODO stings an echte commandos anpassen :)
    switch (cmd.m_signalType)
      {
      case VideoWallCommand::VIDEO:
	s << "blk " << cmd.m_boxSize << " " << cmd.m_xPos 
	  << " " << cmd.m_yPos << "\n";
	break;
      case VideoWallCommand::MONOCOLOR:
	s << "co " << cmd.m_color.red() << " " << cmd.m_color.red() 
	  << " " << cmd.m_color.red();

	for (int x=cmd.m_xPos;x<cmd.m_xPos+cmd.m_boxSize-1;++x)
	  {
	    for (int y=cmd.m_yPos;y<cmd.m_yPos+cmd.m_boxSize-1;++y)
	      {
		s << " mon " << x << " " << y;
	      }
	  }
	break;
      }

    return s;
  }


  VideoWallControllDialog::VideoWallControllDialog(QWidget* parent,
						   const char* name)
    : QDialog(parent,name),screenButtons(16),colorPixmap(16)
  {
    // add  MonitorButtons
    QHBoxLayout* topLayout=new QHBoxLayout();
    QVBoxLayout* rowLayout=new QVBoxLayout();

    QSpacerItem* top=new QSpacerItem(10,10,QSizePolicy::Minimum);
    QSpacerItem* bottom=new QSpacerItem(10,10,QSizePolicy::Minimum);
    QSpacerItem* left=new QSpacerItem(10,10,QSizePolicy::Minimum);
    QSpacerItem* right=new QSpacerItem(10,10,QSizePolicy::Minimum);
    QGridLayout* gridLayout = new QGridLayout(this,4,4);
    topLayout->addItem(top);
    topLayout->addLayout(rowLayout);
    rowLayout->addItem(left);
    rowLayout->addLayout(gridLayout);
    rowLayout->addItem(right);
    topLayout->addItem(bottom);
    for (int x=0;x<4;++x)
      {
	for (int y=0;y<4;++y)
	  {
	    QButton* button = new QButton(this,"screen button",0);
	    screenButtons[x+4*y] = button;
				// add to Layout
	    gridLayout->addWidget(button,x,y);
	  }
      }

    doneButton = new QPushButton( this, "DoneButton" );
    //doneButton->setGeometry( QRect( 160, 30, 60, 26 ) );
    //doneButton->setProperty( "text", tr( "Done" ) );
    rowLayout->addWidget(doneButton);

    // connect signals
    connect( doneButton, SIGNAL( clicked() ), this, SLOT( accept() ) );

    recalc();
  }

  VideoWallControllDialog::~VideoWallControllDialog()
  {

  }

  std::list<VideoWallCommand>
  VideoWallControllDialog::videoWallControllDialog(QWidget* parent,
						   const char* name)
  {
    VideoWallControllDialog dialog(parent,name);
    dialog.exec();
    return dialog.commands;
  }

  void VideoWallControllDialog::recalc()
  {
    std::vector<VideoWallCommand::SignalType> videoSrc(16); // video or color
    std::vector<QColor> screenColor(16); // if color what
    //vector<std::list<VideoWallCommand>::iterator> refMap(16);

    for (std::list<VideoWallCommand>::iterator cmd=commands.begin();
	 cmd!=commands.end();++cmd)
      {
	for (int x=cmd->m_xPos;x<cmd->m_xPos+cmd->m_boxSize-1;++x)
	  {
	    for (int y=cmd->m_yPos;y<cmd->m_yPos+cmd->m_boxSize-1;++y)
	      {
		videoSrc[x+4*y]=cmd->m_signalType;
		screenColor[x+4*y]=cmd->m_color;
	      }
	  }
      }

    // now set the widgets
    for (int screenNr=0;screenNr<16;++screenNr)
      {
	QPixmap* pixmap;
	switch (videoSrc[screenNr])
	  {	
	  case (VideoWallCommand::VIDEO):
	    pixmap=&videoPixmap;
	    break;
	  case (VideoWallCommand::MONOCOLOR):
	    pixmap=&colorPixmap[screenNr];
	    pixmap->fill(screenColor[screenNr]);
	    break;
	  }
	screenButtons[screenNr]->setPixmap(*pixmap);
      }
  }

}
