#ifndef INCLUDED_LABEL_WDIGET_H
#define INCLUDED_LABEL_WDIGET_H

#include <string>

#include <QtGui/qlabel.h>

namespace gui
{

  class LabelWidget : public QLabel
  {
    Q_OBJECT
  public:
    LabelWidget(QWidget* parent, int id, const std::string& text);

    int id() const;

  protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent* e);

  signals:
    void moved(LabelWidget*, const QPoint&);
    void released(LabelWidget*, const QPoint&);

    void beenRightClicked(LabelWidget*, const QPoint& );

  private:
    int m_id;
    bool dragMode;
    QPoint clickedPos;
  };
}

#endif

