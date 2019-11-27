#ifndef INCLUDED_MOUSE_OVER_H
#define INCLUDED_MOUSE_OVER_H

#include <QtCore/qobject.h>

class QWidget;

namespace gui {
class MouseOverImpl : public QObject {
  Q_OBJECT
public:
  MouseOverImpl(QWidget *parent);

signals:
  void mouseOver(QWidget *);

protected:
  bool eventFilter(QObject *o, QEvent *e);

private:
  QWidget *m_parent;
};

/**
 * Objects of this class  emit a signal once the mouse is
 * over their parent widget.
 *
 * The reason this class is necessary is that a widget
 * composed of child widgets might not receive a
 * mouseMoveEvent, because the children consume it.
 * So it is not (easily) possible for the widget to
 * check wether it is under the mouse.
 *
 * To use it, just create a new MouseOver object and
 * set the parent to the widget for which you want the
 * mouseOver signals.
 */
class MouseOver : public QObject {
  Q_OBJECT
public:
  MouseOver(QWidget *parent);

signals:
  void mouseOver(QWidget *);

private slots:
  void mouseOverParent(QWidget *);

private:
  MouseOverImpl *m_impl;
};

} // namespace gui
#endif
