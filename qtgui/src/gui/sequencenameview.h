#ifndef INCLUDED_SEQUENCENAME_VIEW_H
#define INCLUDED_SEQUENCENAME_VIEW_H

#include <map>

#include <qobject.h>

#include "interfaces/isequencenamereceiver.h"

#include "utils/autoptr.h"

class QWidget;
class ISequencerControlReceiver;

namespace gui
{

  class TreeView;
  class SequencerTopItem;
  class SequenceItem;
  class SequenceNameView;
  class ISceneSequencer;


  class SequenceNameViewObject : public QObject
  {
    Q_OBJECT
  public:
    SequenceNameViewObject(QObject* parent, SequenceNameView& view);
	

public slots:

    /**
     * Is called when the model changes the edit sequence
     */
    void editSequenceChanged( const std::string& sequenceID );

  private:
    SequenceNameView& m_view;
  };

  class SequenceNameView : public ISequenceNameReceiver
  {
  public:
    SequenceNameView(QWidget* parent,ISequencerControlReceiver& sequencer,
		     ISceneSequencer& playlist);

    virtual ~SequenceNameView();

    QWidget* widget();
    SequenceNameViewObject* signalObject();

    virtual void sequenceExists(const std::string& id,const std::string& name);

    virtual void sequenceNoLongerExists(const std::string& id);

    virtual void sequenceRenamed(const std::string& id,
				 const std::string& newName);

    void markEditSequence(const std::string& sequenceID);

  private:
    typedef utils::AutoPtr<SequenceItem> SequenceItemPtr;
    typedef std::map<std::string,SequenceItemPtr> SequenceMap;
    TreeView* m_treeView;

    SequenceMap m_sequences;

    SequenceNameViewObject stupidObject;

    ISequencerControlReceiver& m_seq;

    typedef utils::AutoPtr<SequencerTopItem> TopItemPtr;
    TopItemPtr m_topItem;

    SequenceItemPtr editSequence;
    
    ISceneSequencer* m_playlist;
  };
			
}

#endif
