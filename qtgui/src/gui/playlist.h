#ifndef INCLUDED_PLAYLIST_H
#define INCLUDED_PLAYLIST_H

#include <qdialog.h>

#include "interfaces/isequencerstatusreceiver.h"
#include "guimodel/iscenechangelistener.h"

#include "utils/autoptr.h"

class QPushButton;

class ISequencerControlReceiver;

namespace gui
{

  class ISceneSequencer;
  class SequenceList;

class Playlist : public QDialog,
		 public ISequencerStatusReceiver,
		 public ISceneChangeListener
{ 
    Q_OBJECT

public:
    Playlist( QWidget* parent, ISequencerControlReceiver& scr,
	      ISceneSequencer& ss_);

    ~Playlist();

  //from iscenechangelistener
  virtual void sceneInserted(int id, int pos,const std::string& content,
			     int length);	
  virtual void sceneDeleted(int id);
  virtual void sceneLengthChanged(int id, int newLen);
  virtual void sceneMoved(int id, int newPos);
  

  virtual void editSequenceChanged( const std::string& sequenceID );
  virtual void started();
  virtual void paused();
  virtual void stopped();    
  virtual void time(int currentTime);


public slots:
    virtual void changeLengthClicked();
    virtual void deleteClicked();

  signals:
    void editPlaylistChanged( const std::string& playlistID );

private:
  ISequencerControlReceiver* m_scr;
  ISceneSequencer* m_ss;

  utils::AutoPtr<SequenceList> m_sequenceList;
  QPushButton* deleteButton;
  QPushButton* lengthButton;
  QPushButton* doneButton;
};

}

#endif // PLAYLIST_H

