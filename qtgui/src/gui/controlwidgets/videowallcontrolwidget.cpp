#include "videowallcontrolwidget.h"

#include <qbutton.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qcolor.h>
#include <qcolordialog.h>
#include <string>
#include <sstream>

namespace gui
{
  VideoWallControlWidget::VideoWallControlWidget( QWidget* parent, 
						  const std::string& name,
						  int controlID,
						  int nodeID,int inIndex)
    : ControlWidget( parent, name, controlID, nodeID, inIndex)
  {
    //if ( !name )
    //setName( "videoWallControlWidget" );
    resize( 468, 345 ); 
    //setProperty( "caption", tr( "Form1" ) );
		
    //set up a rect of 6x6 pushbuttons to represent our monitors
    int xindex=0, yindex=0;
    for(int x=20;  xindex<6; x+=50, xindex++)
      {
	for(int y=20; yindex<6; x+=50, yindex++)
	  {
	    std::string name = "mon" +xindex+yindex;
	    monitors[xindex][yindex] = new QPushButton(this, name.c_str());
	    monitors[xindex][yindex]->setGeometry(QRect( x, y, 51, 51));
	    monitors[xindex][yindex]->setProperty("text", tr(""));
	    //monitors[xindex][yindex]->setToggleType(QButton::Toggle);
	    monitors[xindex][yindex]->setToggleButton(TRUE);
	  }
			
      }
		
    QWidget* privateLayoutWidget = new QWidget( this, "Layout6" );
    privateLayoutWidget->setGeometry( QRect( 350, 20, 84, 300 ) ); 
    Layout6 = new QVBoxLayout( privateLayoutWidget ); 
    Layout6->setSpacing( 6 );
    Layout6->setMargin( 0 );
		
    Layout3 = new QVBoxLayout; 
    Layout3->setSpacing( 6 );
    Layout3->setMargin( 0 );
		
    colorChangeButton = new QPushButton( privateLayoutWidget,
					 "colorChangeButton" );

    colorChangeButton->setProperty( "text", tr( "Set Color" ) );
    Layout3->addWidget( colorChangeButton );
		
    srcSetButton = new QPushButton( privateLayoutWidget, "srcSetButton" );
    srcSetButton->setProperty( "text", tr( "Set Src" ) );
    Layout3->addWidget( srcSetButton );
    Layout6->addLayout( Layout3 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum,
					   QSizePolicy::Expanding );
    Layout6->addItem( spacer );
		
    Layout4 = new QVBoxLayout; 
    Layout4->setSpacing( 6 );
    Layout4->setMargin( 0 );
		
    undoButton = new QPushButton( privateLayoutWidget, "undoButton" );
    undoButton->setProperty( "text", tr( "Undo" ) );
    Layout4->addWidget( undoButton );
		
    applyButton = new QPushButton( privateLayoutWidget, "applyButton" );
    applyButton->setProperty( "text", tr( "Apply" ) );
    Layout4->addWidget( applyButton );
    Layout6->addLayout( Layout4 );
		
    connect(colorChangeButton, SIGNAL(clicked()),
	    this, SLOT(colorSelectRequest()));

    connect(srcSetButton, SIGNAL(clicked()), this, SLOT(srcSetRequest()));
    connect(applyButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(undoButton, SIGNAL(clicked()), this, SLOT(undo()));
  }
	
  /*  
   *  Destroys the object and frees any allocated resources
   */
  VideoWallControlWidget::~VideoWallControlWidget()
  {
    // no need to delete child widgets, Qt does it all for us
  }
	
  /**
   *	Depending on which monitors are selected, we send a string
   *    indicating the color-change for those.
   *	The String will be generated in the format:
   *	monitors x1 y1 x2 y1.... color r g b
   *	for the videowallcontrol-module to be handled conveniently
   */
  void VideoWallControlWidget::colorSelectRequest()
  {
    if(!itWasMe)
      {
	//TODO: default color
	QColor tmp = QColorDialog::getColor ( QColor(128, 128, 128), this,
					      "ColorSelector") ;
			
	if (tmp.isValid())
	  {
	    std::ostringstream os("color ");
	    int r,g,b;
	    //values on videowall range from 0-63
	    r = tmp.red()/4;
	    g = tmp.green()/4;
	    b = tmp.blue()/4;
				
	    os << r;
	    os << " ";
	    os << g;
	    os << " ";
	    os << b;
	    os << " ";
				
	    //Loop through monitors, the ones toggled are concatenated
	    //to string
	    for(int x=0; x<6; ++x)
	      {
		for(int y=0; y<6; ++y)
		  {
		    if(monitors[x][y]->state() == QButton::On)
		      {
			monitors[x][y]->toggle();//setState(QButton::Off);
			// this will be discarded on apply and undo button hit
			// and be reassigned on confirmation from engine
			monitors[x][y]->setBackgroundColor(tmp); 
			os<<x;
			os<<" ";
			os<<y;
			os<<" ";
		      }
						
		  }
					
	      }
	    std::string data = os.str();
	    valueChanged(utils::Buffer(reinterpret_cast<const unsigned char*>(data.c_str()),
				       data.length()+1));
	    //Save the string, wait for apply hit to send to engine
	    // (or undo to undo)
	  }
      }
    else
      {
	itWasMe = false;
      }
  }
	
  void VideoWallControlWidget::srcSetRequest()
  {
    if(!itWasMe)
      {
	std::ostringstream os("src ");
	for(int x=0; x<6; ++x)
	  {
	    for(int y=0; y<6; ++y)
	      {
		if(monitors[x][y]->state() == QButton::On)
		  {
		    monitors[x][y]->toggle();//setState(QButton::Off);
		    // this will be discarded on apply and undo button hit and
		    // be reassigned on confirmation from engine
		    // TODO: make pixmap to be displayed when src-signal is
		    // shown on monitor
		    //monitors[x][y]->setPixmap(tmp); 
		    os<<x;
		    os<<" ";
		    os<<y;
		    os<<" ";
		  }
					
	      }
				
	  }
	std::string data = os.str();
	valueChanged(utils::Buffer(reinterpret_cast<const unsigned char*>(data.c_str()),
				   data.length()+1));
      }
    else
      {
	itWasMe = false;
      }

		
    //Save string, wait for userconfirmation to send to engine
  }
	
  /*void VideoWallControlWidget::apply()
    {
    if(!itWasMe)
    {
			
    }
    else
    {	
    itWasMe = false;
    }
    }
	
    void VideoWallControlWidget::undo()
    {
		
    }
  */
  /*for(x=0; x<NUM_MONITORS; ++x)
    {
    for(y=0; y<NUM_MONITORS; ++y)
    {
    if(videowallcontrol->monitors[x][y].showsPic == 1)
    {
    sprintf(buffer+base, "src %d %d ", x, y);
    base+=8;
    }
    else
    {
    sprintf(buffer+base, "color %d %d %u %u %u ", x, y,
    videowallcontrol->monitors[x][y].r,
    videowallcontrol->monitors[x][y].b,
    videowallcontrol->monitors[x][y].g);
					
    base+=16;
    if(videowallcontrol->monitors[x][y].r>=10) ++base;
    if(videowallcontrol->monitors[x][y].g>=10) ++base;
    if(videowallcontrol->monitors[x][y].b>=10) ++base;

    }
    }
    }*/
  void VideoWallControlWidget::controlValueChanged(int nodeID,int intputIndex,const utils::Buffer& newValue)
  {
    /* String comes in the form <color r g b|src> monitors x1 y1 x2 y2...*/
    itWasMe = true;
    int r,g,b,x,y;
    std::istringstream is(reinterpret_cast<const char*>(newValue.getPtr()));
    int size = newValue.getLen();
    std::string command;
    is >> command;
    while(strcmp(command.c_str(), "0") != 0)
      {
			
	if(strcmp(command.c_str(), "color") == 0)
	  {
	    is >> x >> y >> r >> g >> b;
	    monitors[x][y]->setBackgroundColor(QColor(r*4, g*4, b*4));
	  }
	else if(strcmp(command.c_str(), "src") == 0)
	  {
	    is >> x >> y;
	    //monitors[x][y]->setPixmap("blablapixmap");
	  }
	is >> command;
      }
		
  }

  VideoWallControlWidgetConstructor::VideoWallControlWidgetConstructor():
    ControlWidgetConstructor("typ_VideoWallControlType","Videowandsteuerung",
			     "vwctrl")
  { 
  }
		
  ControlWidget*
  VideoWallControlWidgetConstructor::construct(QWidget* parent,
					       const std::string& name,
					       int controlID,
					       int nodeID, int inputIndex)
  {
    return new VideoWallControlWidget(parent,name,controlID,nodeID,inputIndex);
  }

	
	
}

/*mon03 = new QPushButton( this, "mon03" );
  mon03->setGeometry( QRect( 170, 20, 51, 51 ) ); 
  mon03->setProperty( "text", tr( "" ) );

  mon04 = new QPushButton( this, "mon04" );
  mon04->setGeometry( QRect( 220, 20, 51, 51 ) ); 
  mon04->setProperty( "text", tr( "" ) );
  
  mon02 = new QPushButton( this, "mon02" );
  mon02->setGeometry( QRect( 120, 20, 51, 51 ) ); 
  mon02->setProperty( "text", tr( "" ) );
	
  mon00 = new QPushButton( this, "mon00" );
  mon00->setGeometry( QRect( 20, 20, 51, 51 ) ); 
  mon00->setProperty( "text", tr( "" ) );
	  
  mon05 = new QPushButton( this, "mon05" );
  mon05->setGeometry( QRect( 270, 20, 51, 51 ) ); 
  mon05->setProperty( "text", tr( "" ) );
		
  mon14 = new QPushButton( this, "mon14" );
  mon14->setGeometry( QRect( 220, 70, 51, 51 ) ); 
  mon14->setProperty( "text", tr( "" ) );
		  
  mon01 = new QPushButton( this, "mon01" );
  mon01->setGeometry( QRect( 70, 20, 51, 51 ) ); 
  mon01->setProperty( "text", tr( "" ) );
			
  mon15 = new QPushButton( this, "mon15" );
  mon15->setGeometry( QRect( 270, 70, 51, 51 ) ); 
  mon15->setProperty( "text", tr( "" ) );
			  
  mon11 = new QPushButton( this, "mon11" );
  mon11->setGeometry( QRect( 70, 70, 51, 51 ) ); 
  mon11->setProperty( "text", tr( "" ) );
				
  mon13 = new QPushButton( this, "mon13" );
  mon13->setGeometry( QRect( 170, 70, 51, 51 ) ); 
  mon13->setProperty( "text", tr( "" ) );
				  
  mon10 = new QPushButton( this, "mon10" );
  mon10->setGeometry( QRect( 20, 70, 51, 51 ) ); 
  mon10->setProperty( "text", tr( "" ) );
					
  mon31 = new QPushButton( this, "mon31" );
  mon31->setGeometry( QRect( 70, 170, 51, 51 ) ); 
  mon31->setProperty( "text", tr( "" ) );
					  
  mon40 = new QPushButton( this, "mon40" );
  mon40->setGeometry( QRect( 20, 220, 51, 51 ) ); 
  mon40->setProperty( "text", tr( "" ) );
						
  mon43 = new QPushButton( this, "mon43" );
  mon43->setGeometry( QRect( 170, 220, 51, 51 ) ); 
  mon43->setProperty( "text", tr( "" ) );
						  
  mon51 = new QPushButton( this, "mon51" );
  mon51->setGeometry( QRect( 70, 270, 51, 51 ) ); 
  mon51->setProperty( "text", tr( "" ) );
							
  mon41 = new QPushButton( this, "mon41" );
  mon41->setGeometry( QRect( 70, 220, 51, 51 ) ); 
  mon41->setProperty( "text", tr( "" ) );
							  
  mon55 = new QPushButton( this, "mon55" );
  mon55->setGeometry( QRect( 270, 270, 51, 51 ) ); 
  mon55->setProperty( "text", tr( "" ) );
								
  mon50 = new QPushButton( this, "mon50" );
  mon50->setGeometry( QRect( 20, 270, 51, 51 ) ); 
  mon50->setProperty( "text", tr( "" ) );
								  
  mon35 = new QPushButton( this, "mon35" );
  mon35->setGeometry( QRect( 270, 170, 51, 51 ) ); 
  mon35->setProperty( "text", tr( "" ) );
									
  mon22 = new QPushButton( this, "mon22" );
  mon22->setGeometry( QRect( 120, 120, 51, 51 ) ); 
  mon22->setProperty( "text", tr( "" ) );
									  
  mon21 = new QPushButton( this, "mon21" );
  mon21->setGeometry( QRect( 70, 120, 51, 51 ) ); 
  mon21->setProperty( "text", tr( "" ) );

  mon30 = new QPushButton( this, "mon30" );
  mon30->setGeometry( QRect( 20, 170, 51, 51 ) ); 
  mon30->setProperty( "text", tr( "" ) );

  mon20 = new QPushButton( this, "mon20" );
  mon20->setGeometry( QRect( 20, 120, 51, 51 ) ); 
  mon20->setProperty( "text", tr( "" ) );

  mon25 = new QPushButton( this, "mon25" );
  mon25->setGeometry( QRect( 270, 120, 51, 51 ) ); 
  mon25->setProperty( "text", tr( "" ) );

  mon24 = new QPushButton( this, "mon24" );
  mon24->setGeometry( QRect( 220, 120, 51, 51 ) ); 
  mon24->setProperty( "text", tr( "" ) );

  mon33 = new QPushButton( this, "mon33" );
  mon33->setGeometry( QRect( 170, 170, 51, 51 ) ); 
  mon33->setProperty( "text", tr( "" ) );

  mon23 = new QPushButton( this, "mon23" );
  mon23->setGeometry( QRect( 170, 120, 51, 51 ) ); 
  mon23->setProperty( "text", tr( "" ) );

  mon32 = new QPushButton( this, "mon32" );
  mon32->setGeometry( QRect( 120, 170, 51, 51 ) ); 
  mon32->setProperty( "text", tr( "" ) );

  mon34 = new QPushButton( this, "mon34" );
  mon34->setGeometry( QRect( 220, 170, 51, 51 ) ); 
  mon34->setProperty( "text", tr( "" ) );

  mon44 = new QPushButton( this, "mon44" );
  mon44->setGeometry( QRect( 220, 220, 51, 51 ) ); 
  mon44->setProperty( "text", tr( "" ) );

  mon42 = new QPushButton( this, "mon42" );
  mon42->setGeometry( QRect( 120, 220, 51, 51 ) ); 
  mon42->setProperty( "text", tr( "" ) );

  mon53 = new QPushButton( this, "mon53" );
  mon53->setGeometry( QRect( 170, 270, 51, 51 ) ); 
  mon53->setProperty( "text", tr( "" ) );

  mon45 = new QPushButton( this, "mon45" );
  mon45->setGeometry( QRect( 270, 220, 51, 51 ) ); 
  mon45->setProperty( "text", tr( "" ) );

  mon52 = new QPushButton( this, "mon52" );
  mon52->setGeometry( QRect( 120, 270, 51, 51 ) ); 
  mon52->setProperty( "text", tr( "" ) );

  mon54 = new QPushButton( this, "mon54" );
  mon54->setGeometry( QRect( 220, 270, 51, 51 ) ); 
  mon54->setProperty( "text", tr( "" ) );

  mon12 = new QPushButton( this, "mon12" );
  mon12->setGeometry( QRect( 120, 70, 51, 51 ) ); 
  mon12->setProperty( "text", tr( "" ) );*/
