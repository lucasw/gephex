#ifndef INCLUDED_SEQUENCEWIDGET_H_
#define INCLUDED_SEQUENCEWIDGET_H_

#include <list>
#include <string>
#include <map>

#include <qwidget.h>
#include <qpainter.h>


#include "utils/autoptr.h"

class QHeader;
class QBoxLayout;

namespace gui
{

  class SceneWidget;

  class SequenceWidget : public QWidget
  {
    Q_OBJECT
	
  public:
    SequenceWidget(QWidget* parent = 0, const char* name = 0, WFlags fl= 0);
    virtual ~SequenceWidget();

    virtual void started();
    virtual void paused();
    virtual void stopped();

    virtual void sceneInserted(int id, int pos,const std::string& content,
							   int length);	
    virtual void sceneDeleted(int id);
    virtual void sceneLengthChanged(int id, int newLen);
    virtual void sceneMoved(int id, int newPos);

    virtual void time(int currentTime);

    // Length of the next appended scene
    //void setSceneLength(int sceneLength);

    // returns the length of sequence
    int getLength() const;

public slots:
	void sceneSizeChanged(int section, int oldSize, int newSize);
	void sceneIndexChanged(int section, int fromIndex, int toIndex);

	void sceneClicked(int section);

	void scenePopupActivated(int action);
	

  protected:
    virtual void paintEvent(QPaintEvent*);

    signals:
    void userChangedSceneLength(int id,int newTime);
	void userDeletedScene(int id);

	
private:
	typedef utils::AutoPtr<SceneWidget> SceneWidgetPtr;
	typedef std::list<SceneWidgetPtr> SceneList;
	typedef std::map<int,int> SceneMap;	

	QHeader* buildHeader();
	void updateHeader();

    QPainter painter;
    SceneList m_scenes;

    //int m_sceneLength; // laenge der naechsten angehaengten szene
    int oldX;

    QPainter mainPainter;

	QHeader* header;

	QBoxLayout* headerLayout;
	
	SceneMap section2scene;

	enum {SCENE_PROPERTIES, SCENE_KILL}; //TODO: bad idea

    int currentSceneID;

  };

}

#endif
