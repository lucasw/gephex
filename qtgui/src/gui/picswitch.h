#ifndef INCLUDED_PIC_SWITCH_H
#define INCLUDED_PIC_SWITCH_H

#include <vector>

#include <qwidget.h>
#include <qpixmap.h>

class QToolButton;

namespace gui
{

class PicSwitch : public QWidget
{
	Q_OBJECT
public:
	PicSwitch(QWidget* parent, const char* name,const QPixmap& pm1, const QPixmap& pm2);
	
public slots:
	void setPic(int index);

private slots:
	void pixmapClicked();

signals:
	void clicked(int index);

private:
	std::vector<QPixmap> pics;
	QToolButton* button;
	int current;

};

} // end of namespace
#endif
