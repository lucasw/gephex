#ifndef INCLUDED_PLUG_WIDGET_H
#define INCLUDED_PLUG_WIDGET_H

#include <string>

#include <qwidget.h>
#include <qpixmap.h>

namespace gui
{
  
  class PlugWidget : public QWidget
  {
    Q_OBJECT
  private:
    QColor color;
    const std::string name;
    const std::string type;
    const int index;
    const int ID;

  protected:
    bool lineDrawMode;
    const QPixmap freePic;	
    const QPixmap busyPic;

  public:
    PlugWidget(QWidget* parent, const char* name, 
	       std::string _name, std::string _type, int _index, int _ID, 
	       const QPixmap& free_, const QPixmap& busy_);

    std::string getType() const { return type; }
    int getIndex() const { return index; }
    int getID() const { return ID; }
    std::string getName() const { return name; }
    void setPixmap(bool which);

  protected:
    virtual void mousePressEvent(QMouseEvent*);
       
    signals:
    void beginLineDraw();
    void redrawLine(const QPoint& from, const QPoint& to);
  };


} // end of namespace gui

#endif

