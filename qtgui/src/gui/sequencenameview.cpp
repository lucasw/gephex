#include "sequencenameview.h"

#include <cassert>
#include <stdexcept>
#include <sstream>

#include <qpopupmenu.h>

#include "base/treeview.h"
#include "base/treeviewitem.h"

#include "base/askforstringdialog.h"
#include "interfaces/isequencercontrolreceiver.h"

#include "guimodel/iscenesequencer.h"

namespace gui
{


  class SequencerTopItem : public TreeViewItem
  {
  public:
    SequencerTopItem(ISequencerControlReceiver& seq)
      :  m_seq(seq) {}

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,"Sequenzen");
    }

    virtual QPopupMenu* getPropertyMenu()
    {
      QPopupMenu *popme = new QPopupMenu(0, "TopPop");

      popme->insertItem("New Sequence",NEW_SEQUENCE);

      return popme;      
    }

    virtual void propertySelected(int id)
    {
      switch(id)
	{
	case NEW_SEQUENCE:
	  {
	    std::string newName = AskForStringDialog::open(0, "New Sequence",
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

    enum { NEW_SEQUENCE };
  };


  class SequenceItem : public TreeViewItem
  {
  public:
    SequenceItem(const std::string& id,
		 const std::string& name,
		 ISequencerControlReceiver& seq,
		 ISceneSequencer& playlist)
      : m_id(id), m_name(name), m_seq(seq), m_playlist(&playlist){}

    virtual ~SequenceItem() {}

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,m_name.c_str());
    }

    virtual void leftButtonClicked( const Point& pos, int column )
    {
      this->propertySelected(EDIT_SEQUENCE);
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

      popme->insertItem("Edit Sequence",EDIT_SEQUENCE);
      popme->insertItem("Rename Sequence",
			RENAME_SEQUENCE);
      popme->insertItem("Remove Sequence",KILL_SEQUENCE);
      popme->insertItem("Save Sequence",SAVE_SEQUENCE);
      popme->insertItem("Put into Playlist",PUT_INTO_PLAYLIST);

      return popme;
    }

    virtual void propertySelected(int id)
    {
      switch(id)
	{
	case EDIT_SEQUENCE:
	  m_seq.changeSequence(m_id);
	  break;
	case RENAME_SEQUENCE:
	  {
	    std::string newName = AskForStringDialog::open(0,
							   "Rename Sequence",
							   "Enter new name");

	    m_seq.renameSequence(m_id, newName);	  
	  }
	  break;
	case KILL_SEQUENCE:
	  {
	    m_seq.deleteSequence(m_id);
	  }
	  break;
	case SAVE_SEQUENCE:
	  {
	    m_seq.saveSequence(m_id);
	  }
	  break;
	case PUT_INTO_PLAYLIST:
	  {
	    std::string 
	      sLength = AskForStringDialog::open(0,
						 "Put into Playlist",
						 "Enter length in secs");
	    std::istringstream is(sLength);
	    double length;
	    is >> length;
	    if (!is)
	      {
		//TODO
		//length = 5000;
	      }

	    m_playlist->appendScene(m_id,length*1000);
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

    ISceneSequencer* m_playlist;

    enum {EDIT_SEQUENCE, RENAME_SEQUENCE, KILL_SEQUENCE,
	  SAVE_SEQUENCE, PUT_INTO_PLAYLIST};

  };


  SequenceNameViewObject::SequenceNameViewObject(QObject* parent,
						 SequenceNameView& view)
    : QObject(parent), m_view(view)
  {
  }


  void SequenceNameViewObject::editSequenceChanged( const std::string& sequenceID )
  {
    m_view.markEditSequence(sequenceID);
  }

  SequenceNameView::SequenceNameView(QWidget* parent,
				     ISequencerControlReceiver& sequencer,
				     ISceneSequencer& playlist)
    : stupidObject(0,*this),
      m_seq(sequencer), m_topItem( new SequencerTopItem(sequencer) ),
      editSequence(0), m_playlist(&playlist)
  {
    std::vector<std::string> cols;
    cols.push_back("Name");
    cols.push_back("Status");
    m_treeView = new TreeView(parent,"Sequencen",cols);
    m_treeView->insertItem(*m_topItem,0);
  }

  SequenceNameView::~SequenceNameView()
  {
  }

  QWidget* SequenceNameView::widget()
  {
    return m_treeView->widget();
  }

  SequenceNameViewObject* SequenceNameView::signalObject()
  {
    return &stupidObject;
  }

  void SequenceNameView::sequenceExists(const std::string& id,
					const std::string &name)
  {
    SequenceMap::const_iterator it = m_sequences.find(id);
	
    if (it == m_sequences.end())
      {
	SequenceItemPtr tmp(new SequenceItem(id,name,m_seq,*m_playlist));
	
	m_sequences[id] = tmp;
	m_treeView->insertItem(*tmp,&*m_topItem);
      }
    else
      {
	//TODO: why does the sequence already exist?
      }

  }

  void SequenceNameView::sequenceNoLongerExists(const std::string& id)
  {
    SequenceMap::iterator it = m_sequences.find(id);
	
    if (it == m_sequences.end())
      {
	throw std::runtime_error("Sequence doesnt exist at "
				 "SequenceNameView::sequenceNoLongerExists()");
      }

    m_treeView->removeItem(*it->second);
    m_sequences.erase(it);
  }

  void SequenceNameView::sequenceRenamed(const std::string& id,
					 const std::string& newName)
  {
    SequenceMap::iterator it = m_sequences.find(id);

    if (it == m_sequences.end())
      {
	throw std::runtime_error("bla blub");
      }

    it->second->setName(newName);
  }

  void SequenceNameView::markEditSequence(const std::string& sequenceID)
  {
    SequenceMap::iterator it = m_sequences.find(sequenceID);

    if (it == m_sequences.end())
      {
	throw std::runtime_error("bla blub");
      }

    if (editSequence)
      editSequence->setStatus("");

    editSequence = it->second;

    editSequence->setStatus("e");

  }

}
