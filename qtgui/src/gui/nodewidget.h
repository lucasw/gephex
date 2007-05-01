/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#ifndef _INCLUDED_NODEWIDGET_H_
#define _INCLUDED_NODEWIDGET_H_

#include <vector>
#include <string>
#include <list>

#include <QtGui/qwidget.h>
#include <QtGui/qpixmap.h>

#include "utils/autoptr.h"

#include "base/picmanager.h"

class IModelControlReceiver;
class IErrorReceiver;

namespace gui
{
  class OutputPlugWidget;
  class InputPlugWidget;
  class ModuleInfo;

  class NodeProperty;
  class ControlValueDispatcher;
  class IPropertyDescription;

  class IKeyListener;
  class KeyboardManager;

  class NodeWidget : public QWidget
  {

    Q_OBJECT
  private:
    typedef std::vector<utils::AutoPtr<OutputPlugWidget> > OutputVector;
    typedef std::vector<utils::AutoPtr<InputPlugWidget> > InputVektor;
    OutputVector outputs;
    InputVektor inputs;

    int id;
    const PicManager& m_pictures;

    std::string modName;
    std::string m_group;
    QPixmap* m_icon;

    std::vector<QPixmap> pictures; //pointer to the backgroundpics n stuff the node is using

    bool dragMode;
    QPoint clickedPos;
    utils::AutoPtr<IPropertyDescription> m_properties;
    double m_time;

    KeyboardManager* m_kbManager;

    typedef std::list<utils::AutoPtr<IKeyListener> > KeyListenerList;
    KeyListenerList m_keyListeners;

    IErrorReceiver& m_log;
    //private slots:
    //void moveInputToProperties(int);

  protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void paintEvent(QPaintEvent*);

    signals:
    void clickedLeft(NodeWidget*);
    void beenRightClicked(NodeWidget*, const QPoint& );
    void moved(NodeWidget*, const QPoint& where);
    void released(NodeWidget*,const QPoint& where);
    void mouseOverNode(const NodeWidget*);

    // die folgenden signale werden von den inputs/outputs durchgesschleift
    void redrawLine(const QPoint& from, const QPoint& to);
    void connectionRequestFromInput(const InputPlugWidget*, const QPoint& to);
    void connectionRequestFromOutput(const OutputPlugWidget*,const QPoint& to);
    void openPopup(InputPlugWidget*);
    void mouseOverInputPlug(const InputPlugWidget*);
    void mouseOverOutputPlug(const OutputPlugWidget*);
  
    void error(const std::string& errorText);

  public:
    NodeWidget(QWidget* parent, Qt::WFlags fl,
	       int id,const ModuleInfo& _info, 
	       const PicManager& picz,
               const utils::AutoPtr<ControlValueDispatcher>&,
               IModelControlReceiver&,
	       KeyboardManager* kbManager,
               IErrorReceiver& log,
	       const std::string& media_path);
    ~NodeWidget();

    std::vector<OutputPlugWidget*> getOutputs() const;
    std::vector<InputPlugWidget*> getInputs() const;

    int getID() const { return id; }
    std::string group() const { return m_group; }
    std::string moduleClassName() const { return modName; }

    const OutputPlugWidget* isAtOutput(const QPoint& p) const;
    const InputPlugWidget* isAtInput(const QPoint& p) const;
    
    void setTime(double t);
    double getTime() const;

    QPixmap* icon(){return m_icon;}
    
    const IPropertyDescription& getProperties() const;
    

 public slots:
 // schleifen nur signale von inputs/outputs durch
    void redrawLine_(const QPoint& from, const QPoint& to);
    void connectionRequestFromInput_(const InputPlugWidget*, const QPoint& to);
    void connectionRequestFromOutput_(const OutputPlugWidget*,
				      const QPoint& to);
    void openPopup_( InputPlugWidget*);
    void mouseOverInputPlug_(const InputPlugWidget*);
    void mouseOverOutputPlug_(const OutputPlugWidget*);
	
  };


} // end namespace gui

#endif
