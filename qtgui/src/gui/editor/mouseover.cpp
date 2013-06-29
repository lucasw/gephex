#include "mouseover.h"

#include <QtGui/qwidget.h>
#include <QtGui/qapplication.h>
#include <QtGui/QMouseEvent>

namespace gui
{

  static bool is_child(QObject* parent, QObject* child)
  {
    if (parent == 0 || child == 0)
      return false;

    if (parent == child)
      return true;

    return is_child(parent, child->parent());
  }

  class MouseOverImpl : public QObject
  {
    Q_OBJECT
  public:
    MouseOverImpl(QWidget* parent)
      : QObject(parent), m_parent(parent)
    {
      qApp->installEventFilter(this);
    }

  signals:
    void mouseOver(QWidget*);
 
  protected:
    bool eventFilter(QObject* o, QEvent* e)
    {
      if ( e->type() == QEvent::MouseMove &&
           is_child(m_parent, o) )
        {

// dynamic cast does not work with vc6 here although
// rtti is turned on.
// perhaps the qt2.3 noncommercial library was compiled
// without rtti?
#if (defined _MSC_VER) && (_MSC_VER <= 1200)
          QMouseEvent* me = static_cast<QMouseEvent*>(e);
#else
          QMouseEvent* me = dynamic_cast<QMouseEvent*>(e);
#endif

          QWidget* grandfather = m_parent->parentWidget();

          if (grandfather == 0)
            return false;

          QPoint mouse_pos = grandfather->mapFromGlobal(me->globalPos());

          QRect rect = m_parent->frameGeometry();
          
          if (rect.contains(mouse_pos))
            emit mouseOver(m_parent);
        }
      
      return false;
    }

  private:
    QWidget* m_parent;
  };

  MouseOver::MouseOver(QWidget* parent)
    : QObject(parent), m_impl(new MouseOverImpl(parent))
  {
    connect(m_impl, SIGNAL(mouseOver(QWidget*)),
            this, SLOT(mouseOverParent(QWidget*)));
  }

  void MouseOver::mouseOverParent(QWidget* w)
  {
    emit mouseOver(w);
  }

}

#include "mouseover_moc_cpp.cpp"
