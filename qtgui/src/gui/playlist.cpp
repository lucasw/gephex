#include "playlist.h"

#include <map>
#include <sstream>
#include <iostream> //just for debugging

#include <qheader.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
//#include <qtooltip.h>

#include "interfaces/isequencercontrolreceiver.h"
#include "guimodel/iscenesequencer.h"
#include "askforstringdialog.h"

namespace gui
{
  struct SequenceInfo
  {
    SequenceInfo(const std::string& name_, int length_, QListBoxItem* item_)
      : name(name_), length(length_), item(item_) {}

    std::string name;
    int length;
    QListBoxItem* item;
  };
  namespace 
  {
    std::string buildLabel(const std::string& name, int length)
    {
      std::ostringstream out;
      out << name << " (" << length/1000. << ")";
      out.flush();
      return out.str();
    }

    typedef std::map<int,SequenceInfo> SequenceMap;
    SequenceMap::iterator getItemByPos(QListBox* m_list,
				       SequenceMap& sequences,
				       int pos)
    {
      QListBoxItem* current = m_list->item(pos);
      SequenceMap::iterator it = sequences.begin();
      for (; it != sequences.end(); ++it)
	{
	  if (it->second.item == current)
	    break;
	}

      return it;
    }
  }

  class SequenceList
  {
  private:
    QListBox* m_list;
    typedef std::map<int,SequenceInfo> SequenceMap;
    SequenceMap m_sequences;

  public:
    SequenceList(QWidget* parent)
      : m_list(new QListBox(parent, "SequenceList"))
    {
    }

    QWidget* getWidget()
    {
      return m_list;
    }
    
    void insertSequence(int id, const std::string& name, int length, int pos)
    {
      std::string label = buildLabel(name, length);
      
      QListBoxText* text = new QListBoxText(0,label.c_str());
      SequenceInfo newInfo(name, length, text);

      m_sequences.insert(SequenceMap::value_type(id, newInfo));

      m_list->insertItem(text,pos);
    }
    
    void deleteSequence(int id)
    {
      SequenceMap::iterator it = m_sequences.find(id);

      if (it == m_sequences.end())
	  throw std::runtime_error("wrong id at deleteSequence()");

      delete it->second.item; //TODO: is this the right way to remove the item?
      m_sequences.erase(it);
    }

    void changeSequenceLength(int id, int newLen)
    {
      SequenceMap::iterator it = m_sequences.find(id);

      if (it == m_sequences.end())
	{
	  throw std::runtime_error("wrong id at deleteSequence()");
	}

      it->second.length = newLen;

      std::string newLabel = buildLabel(it->second.name, newLen);

      QListBoxItem* newItem = new QListBoxText(0, newLabel.c_str());
      m_list->insertItem(newItem, it->second.item);
      delete it->second.item;

      it->second.item = newItem;
    }

    void moveSequence(int id, int newPos)
    {
      SequenceMap::iterator it = m_sequences.find(id);

      if (it == m_sequences.end())
	{
	  throw std::runtime_error("wrong id at deleteSequence()");
	}

      m_list->takeItem(it->second.item); //TODO

      m_list->insertItem(it->second.item, newPos);
    }

    // does nothing if there is no current item
    void deleteCurrent()
    {
      int index = m_list->currentItem();

      if (index == -1)
	return;

      SequenceMap::iterator it = getItemByPos(m_list,m_sequences,index);

      if (it == m_sequences.end())
	throw std::runtime_error("no such item at deleteCurrent()");

      deleteSequence(it->first);
    }

    // does nothing if there is no current item
    void changeLengthOfCurrent(int newLength)
    {
      int index = m_list->currentItem();

      if (index == -1)
	return;

      SequenceMap::iterator it = getItemByPos(m_list,m_sequences,index);

      if (it == m_sequences.end())
	throw std::runtime_error("no such item at changeLengthOfCurrent()");

      changeSequenceLength(it->first, newLength);
    }

  };

Playlist::Playlist( QWidget* parent, ISequencerControlReceiver& scr,
		    ISceneSequencer& ss_)
  : QDialog( parent, "Playlist", false, 0 ), m_scr(&scr), m_ss(&ss_),
    m_sequenceList(new SequenceList(this))
{    
  
  resize( 320, 240 ); 
  setCaption( "Playlist" );

  QVBoxLayout* playlistLayout = new QVBoxLayout( this ); 
  playlistLayout->setSpacing( 6 );
  playlistLayout->setMargin( 11 );

  playlistLayout->addWidget( m_sequenceList->getWidget() );

  QHBoxLayout* buttonLayout = new QHBoxLayout; 
  buttonLayout->setSpacing( 6 );
  buttonLayout->setMargin( 0 );

  deleteButton = new QPushButton( this, "deleteButton" );
  deleteButton->setText("Delete");
  buttonLayout->addWidget( deleteButton );
  QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Preferred,
					 QSizePolicy::Minimum );
  buttonLayout->addItem( spacer );

  lengthButton = new QPushButton( this, "lengthButton" );
  lengthButton->setSizePolicy(QSizePolicy( (QSizePolicy::SizeType)1,
					   (QSizePolicy::SizeType)0,
					   lengthButton->sizePolicy().hasHeightForWidth() ) );

  lengthButton->setText( "Change Length" );
  buttonLayout->addWidget( lengthButton );
  QSpacerItem* spacer_2 = new QSpacerItem(20,20,
					  QSizePolicy::MinimumExpanding,
					  QSizePolicy::Minimum );
  buttonLayout->addItem( spacer_2 );

  doneButton = new QPushButton( this, "doneButton" );
  doneButton->setText( "Done" );
  buttonLayout->addWidget( doneButton );
  playlistLayout->addLayout( buttonLayout );

    // signals and slots connections
  connect( doneButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
  connect( deleteButton, SIGNAL( clicked() ), 
	   this, SLOT( deleteClicked() ) );
  connect( lengthButton, SIGNAL( clicked() ),
	   this, SLOT( changeLengthClicked() ) );
}

  Playlist::~Playlist()
  {
  }

  void Playlist::sceneInserted(int id, int pos,const std::string& content,
			       int length)
  {
    m_sequenceList->insertSequence(id,content,length,pos);
  }

  void Playlist::sceneDeleted(int id)
  {
    m_sequenceList->deleteSequence(id);
  }

  void Playlist::sceneLengthChanged(int id, int newLen)
  {
    m_sequenceList->changeSequenceLength(id, newLen);
  }

  void Playlist::sceneMoved(int id, int newPos)
  {
    m_sequenceList->moveSequence(id,newPos);
  }


  void Playlist::editSequenceChanged( const std::string& sequenceID )
  {
    emit editPlaylistChanged( sequenceID );
  }

  void Playlist::started(  )
  {
  }

  void Playlist::stopped(  )
  {
  }

  void Playlist::paused(  )
  {
  }
 
  void Playlist::time( int currentTime )
  {
  }

  void Playlist::changeLengthClicked()
  {
    std::string 
      sLength = AskForStringDialog::open(0,
					 "Change length",
					 "Enter new length in secs");
    std::istringstream is(sLength);
    double length;
    is >> length;
    if (!is)
      {
	//TODO
	//length = 5000;
      }

    try
      {
	m_sequenceList->changeLengthOfCurrent(static_cast<int>(length*1000.));
      }
    catch (std::runtime_error& e)
      {
	qWarning(e.what()); //TODO
      }
  }

  void Playlist::deleteClicked()
  {
    try 
      {
	m_sequenceList->deleteCurrent();
      }
    catch (std::runtime_error& e)
      {
	qWarning(e.what()); //TODO
      }
  }

}
