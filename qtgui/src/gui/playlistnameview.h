#ifndef INCLUDED_PLAYLISTNAME_VIEW_H
#define INCLUDED_PLAYLISTNAME_VIEW_H

#include <map>

#include <qobject.h>

#include "interfaces/isequencenamereceiver.h"

#include "utils/autoptr.h"

class QWidget;
class ISequencerControlReceiver;

namespace gui
{

  class TreeView;
  class PlaylistTopItem;
  class PlaylistItem;
  class PlaylistNameView;


  class PlaylistNameViewObject : public QObject
  {
    Q_OBJECT
  public:
    PlaylistNameViewObject(QObject* parent, PlaylistNameView& view);
	

public slots:

    /**
     * Is called when the model changes the edit sequence
     */
    void editPlaylistChanged( const std::string& sequenceID );

  private:
    PlaylistNameView& m_view;
  };

  class PlaylistNameView : public ISequenceNameReceiver
  {
  public:
    PlaylistNameView(QWidget* parent,ISequencerControlReceiver& sequencer);

    virtual ~PlaylistNameView();

    QWidget* widget();
    PlaylistNameViewObject* signalObject();

    virtual void sequenceExists(const std::string& id,const std::string& name);

    virtual void sequenceNoLongerExists(const std::string& id);

    virtual void sequenceRenamed(const std::string& id,
				 const std::string& newName);

    void markEditPlaylist(const std::string& sequenceID);

  private:
    typedef utils::AutoPtr<PlaylistItem> PlaylistItemPtr;
    typedef std::map<std::string,PlaylistItemPtr> PlaylistMap;
    TreeView* m_treeView;

    PlaylistMap m_playlists;

    PlaylistNameViewObject stupidObject;

    ISequencerControlReceiver& m_seq;

    typedef utils::AutoPtr<PlaylistTopItem> TopItemPtr;
    TopItemPtr m_topItem;

    PlaylistItemPtr editPlaylist;
  };
			
}

#endif
