
#ifndef VIDEOWALLCONTROLLWIDGET_H
#define VIDEOWALLCONTROLLWIDGET_H

#include <string>
#include <vector>
#include <list>
#include <iosfwd>


#include "qdialog.h"
#include "qcolor.h"
#include "qbutton.h"
#include "qpushbutton.h"
#include "qpixmap.h"
#include "propertywidget.h"

namespace gui
{

class VideoWallCommand
{
public:	
	enum SignalType {VIDEO,MONOCOLOR};
  VideoWallCommand(int xPos,int yPos,int boxSize,SignalType signalType,QColor color);

//private:
  int m_xPos;
	int m_yPos; // (4,3) border, (x,y) upperLeft screen 0<=x<=3 0<=y<=3

  int m_boxSize; //1=1x1 2=2x2 3=3x3 4=4x4
	SignalType m_signalType;
	QColor m_color;
};

std::ostream& operator<< (std::ostream& s,const VideoWallCommand& cmd);



class VideoWallControllDialog : public QDialog  {
   Q_OBJECT
public: 
  VideoWallControllDialog(QWidget* parent, const char* name);

	virtual ~VideoWallControllDialog();
  void recalc();
  static std::list<VideoWallCommand> videoWallControllDialog(QWidget* parent, const char* name);
private:
  std::list<VideoWallCommand> commands;
  std::vector<QButton*> screenButtons; // 0..15 from left to rightand top to bottom

	std::vector<QPixmap> colorPixmap; // Color PixMap for all screens
  QPixmap videoPixmap; // Pixmap with Symbol for Videoplayback

  QPushButton* doneButton;
};



}
#endif
