#include "playlistnameview.h"

#include <cassert>
#include <stdexcept>

#include <qpopupmenu.h>

#include "base/treeview.h"
#include "base/treeviewitem.h"

#include "base/askforstringdialog.h"
#include "interfaces/isequencercontrolreceiver.h"

namespace gui
{


  class PlaylistTopItem : public TreeViewItem
  {
  public:
    PlaylistTopItem(ISequencerControlReceiver& seq)
      :  m_seq(seq) {}

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,"Playlists");
    }

    virtual QPopupMenu* getPropertyMenu()
    {
      QPopupMenu *popme = new QPopupMenu(0, "TopPop");

      popme->insertItem("New Playlist",NEW_PLAYLIST);

      return popme;      
    }

    virtual void propertySelected(int id)
    {
      switch(id)
	{
	case NEW_PLAYLIST:
	  {
	    std::string newName = AskForStringDialog::open(0, "New Playlist",
							   "Enter a name");
	    m_seq.createSequence(newName);
	  }
	  break;
	default:
	  assert("so ein mist!");
	}
    }

  private:

    ISequencerControlReceiver& m_seq;

    enum { NEW_PLAYLIST };
  };


  class PlaylistItem : public TreeViewItem
  {
  public:
    PlaylistItem(const std::string& id,
		 const std::string& name,
		 ISequencerControlReceiver& seq)
      : m_id(id), m_name(name), m_seq(seq) {}

    virtual ~PlaylistItem() {}

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,m_name.c_str());
    }

    virtual void leftButtonClicked( const Point& pos, int column )
    {
      this->propertySelected(EDIT_PLAYLIST);
    }

    std::string name() const
    {
      return m_name;
    }

    std::string id() const
    {
      return m_id;
    }

    void setName(const std::string& name)
    {
      m_name = name;
      m_textListener->textChanged(0,name.c_str());
    }

    void setStatus(const std::string& status)
    {
      m_textListener->textChanged(1,status.c_str());
    }

    virtual QPopupMenu* getPropertyMenu()
    {
      QPopupMenu *popme = new QPopupMenu(0, "pop"); //TODO: wird das deleted?

      popme->insertItem("Edit Playlist",EDIT_PLAYLIST);
      popme->insertItem("Rename Playlist",
			RENAME_PLAYLIST);
      popme->insertItem("Remove Playlist",KILL_PLAYLIST);
      popme->insertItem("Save Playlist",SAVE_PLAYLIST);

      return popme;
    }

    virtual void propertySelected(int id)
    {
      switch(id)
	{
	case EDIT_PLAYLIST:
	  m_seq.changeSequence(m_id);
	  break;
	case RENAME_PLAYLIST:
	  {
	    std::string newName = AskForStringDialog::open(0,
							   "Rename Playlist",
							   "Enter new name");

	    m_seq.renameSequence(m_id, newName);	  
	  }
	  break;
	case KILL_PLAYLIST:
	  {
	    m_seq.deleteSequence(m_id);
	  }
	  break;
	case SAVE_PLAYLIST:
	  {
	    m_seq.saveSequence(m_id);
	  }
	  break;
	default:
	  assert(!"MIST!");
	}
    }


  private:
    std::string m_id;
    std::string m_name;

    ISequencerControlReceiver& m_seq;

    enum {EDIT_PLAYLIST, RENAME_PLAYLIST, KILL_PLAYLIST,
	  SAVE_PLAYLIST};

  };


  PlaylistNameViewObject::PlaylistNameViewObject(QObject* parent,
						 PlaylistNameView& view)
    : QObject(parent), m_view(view)
  {
  }


  void PlaylistNameViewObject::editPlaylistChanged( const std::string& id )
  {
    m_view.markEditPlaylist(id);
  }

  PlaylistNameView::PlaylistNameView(QWidget* parent,
				     ISequencerControlReceiver& sequencer)
    : stupidObject(0,*this),
      m_seq(sequencer), m_topItem( new PlaylistTopItem(sequencer) ),
      editPlaylist(0)
  {
    std::vector<std::string> cols;
    cols.push_back("Name");
    cols.push_back("Status");
    m_treeView = new TreeView(parent,"Sequencen",cols);
    m_treeView->insertItem(*m_topItem,0);
  }

  PlaylistNameView::~PlaylistNameView()
  {
  }

  QWidget* PlaylistNameView::widget()
  {
    return m_treeView->widget();
  }

  PlaylistNameViewObject* PlaylistNameView::signalObject()
  {
    return &stupidObject;
  }

  void PlaylistNameView::sequenceExists(const std::string& id,
					const std::string &name)
  {
    PlaylistMap::const_iterator it = m_playlists.find(id);
	
    if (it == m_playlists.end())
      {
	PlaylistItemPtr tmp(new PlaylistItem(id,name,m_seq));
	
	m_playlists[id] = tmp;
	m_treeView->insertItem(*tmp,&*m_topItem);
      }
    else
      {
	//TODO: why does the sequence already exist?
      }

  }

  void PlaylistNameView::sequenceNoLongerExists(const std::string& id)
  {
    PlaylistMap::iterator it = m_playlists.find(id);
	
    if (it == m_playlists.end())
      {
	throw std::runtime_error("Sequence doesnt exist at "
				 "PlaylistNameView::sequenceNoLongerExists()");
      }

    m_treeView->removeItem(*it->second);
    m_playlists.erase(it);
  }

  void PlaylistNameView::sequenceRenamed(const std::string& id,
					 const std::string& newName)
  {
    PlaylistMap::iterator it = m_playlists.find(id);

    if (it == m_playlists.end())
      {
	throw std::runtime_error("bla blub");
      }

    it->second->setName(newName);
  }

  void PlaylistNameView::markEditPlaylist(const std::string& sequenceID)
  {
    PlaylistMap::iterator it = m_playlists.find(sequenceID);

    if (it == m_playlists.end())
      {
	throw std::runtime_error("bla blub");
      }

    if (editPlaylist)
      editPlaylist->setStatus("");

    editPlaylist = it->second;

    editPlaylist->setStatus("e");
  }

}

