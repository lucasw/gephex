#ifndef INCLUDED_SEQUENCE_EDITOR_H
#define INCLUDED_SEQUENCE_EDITOR_H

#include <string>
#include <list>

#include "interfaces/isequenceupdatereceiver.h"
#include "interfaces/isequencerstatusreceiver.h"
//#include "interfaces/isequencercontrolsender.h"
#include "guimodel/iscenechangelistener.h"

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QFrame;
class QToolButton;
class ISequencerControlReceiver;


namespace gui
{

  class SequenceWidget;
  class ISceneSequencer;

  class SequenceEditor : public QWidget, 
			 public ISceneChangeListener,
			 public ISequencerStatusReceiver
  { 
    Q_OBJECT
  public:
    SequenceEditor( QWidget* parent, const char* name, WFlags fl,
		    ISequencerControlReceiver& scr_, ISceneSequencer& ss_);
    ~SequenceEditor();
    
    virtual void editSequenceChanged( const std::string& sequenceID );
    virtual void started();
    virtual void paused();
    virtual void stopped();    
    virtual void time(int currentTime);

    // Length of the next appended scene
    //void setSceneLength(int sceneLength);

    // returns the length of the current sequence
    int getLength() const;


    //from iscenechangelistener
    virtual void sceneInserted(int id, int pos,const std::string& content,
							   int length);	
    virtual void sceneDeleted(int id);
    virtual void sceneLengthChanged(int id, int newLen);
    virtual void sceneMoved(int id, int newPos);


private slots:
    void start();
    void stop();
    void pause();

    void changeSceneLength(int id, int newLength);
    void deleteScene(int id);

    signals:
    /**
     * This signal is emitted when the model tells the sequence editor,
     * that the edit sequence has changed.
     */
    void newEditSequence( const std::string& );

  private:
    QToolButton* playButton;
    QToolButton* stopButton;
    QToolButton* pauseButton;
    QFrame* sequencerFrame;
    SequenceWidget* sequencerWindow;
    ISequencerControlReceiver* scr;	
    ISceneSequencer* ss;
    
  };

}

#endif // SequenceEditor_H

