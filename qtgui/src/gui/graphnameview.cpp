#include "graphnameview.h"

#include <cassert>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>

#include <qpopupmenu.h>
#include <qmessagebox.h>

#include "interfaces/imodelcontrolreceiver.h"

#include "guimodel/iscenesequencer.h"

#include "base/askforstringdialog.h"

#include "base/treeviewitem.h"


namespace gui
{

  class GraphTopItem : public TreeViewItem
  {
  public:
    GraphTopItem(IModelControlReceiver& model)
      :  m_model(model) {}

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,"Graphen");
    }

    virtual QPopupMenu* getPropertyMenu()
    {
      QPopupMenu *popme = new QPopupMenu(0, "TopPop");

      popme->insertItem("New Graph",NEW_GRAPH);

      return popme;      
    }

    virtual void propertySelected(int id)
    {
      switch(id)
	{
	case NEW_GRAPH:
	  {
      bool retry=true;
      while(retry)
      {
  	    const std::string newName = AskForStringDialog::open(0, "New Graph",
  						   "Enter a name");
        if (checkNamePolicy(newName))
        {
	        m_model.newGraph(newName);
          retry=false;
        }
        else
        {
          switch (QMessageBox::warning (0,"ungueltiger Name","Ein Name muss 1-20 Zeichen langsein und darf keine Leerzeichen oder Sonderzeichenenthalten",
                QMessageBox::Retry | QMessageBox::Default,
                QMessageBox::Abort | QMessageBox::Escape))
          {
            case QMessageBox::Abort:
            {
             retry=false;
             break;
            }
            case QMessageBox::Retry:
            {
             break;
            }
          }
        }
      }
	  } break;
	default:
	  assert("so ein mist!");
	}
    }

  private:
    IModelControlReceiver& m_model;

    enum { NEW_GRAPH };
  };

  class FolderItem : public TreeViewItem
  {
  public:
    FolderItem(const std::string& name)
      : m_name(name) {}

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,m_name.c_str());
    }

  private:
    std::string m_name;
  };

  class GraphItem : public TreeViewItem
  {
  public:
    GraphItem(const std::string& graphID,
	      const std::string& graphName,
	      IModelControlReceiver& model)
      :      m_graphID(graphID), m_graphName(graphName), m_model(model),
	     m_numberOfSnaps(0) {}

    virtual ~GraphItem() {}

    // must be called when a snapshot is added to this graph
    void snapAdded()
    {
      m_numberOfSnaps++;
    }

    // must be called when a snapshot is removed from this graph
    void snapRemoved()
    {
      m_numberOfSnaps--;
    }

    int numberOfSnaps() const
    {
      return m_numberOfSnaps;
    }

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,m_graphName.c_str());
    }

    virtual QPopupMenu* getPropertyMenu()
    {
      QPopupMenu *popme = new QPopupMenu(0, "GraphPopup");

      popme->insertItem("Save Graph",SAVE_GRAPH);
      popme->insertItem("Copy Graph",COPY_GRAPH);
      popme->insertItem("Rename Graph",RENAME_GRAPH);
      popme->insertItem("Remove Graph",KILL_GRAPH);
      popme->insertItem("New Snapshot",NEW_SNAPSHOT);

      return popme;
    }


    std::string graphID() const
    {
      return m_graphID;
    }

    std::string graphName() const
    {
      return m_graphName;
    }

    void setName(const std::string& newName)
    {
      m_graphName = newName;
      m_textListener->textChanged(0,newName.c_str());
    }

    void setStatus(const std::string& newStatus)
    {
      m_textListener->textChanged(1,newStatus.c_str());
    }

    virtual void GraphItem::propertySelected(int id)
    {
      switch(id)
	{
	case NEW_SNAPSHOT:
	  {
	    std::string newName = AskForStringDialog::open(0, "New Snapshot",
							   "Enter a name");
	    m_model.newControllValueSet(m_graphID, newName);
	  }
	  break;
	case SAVE_GRAPH:
	  {
	    m_model.saveGraph(m_graphID);
	  } break;
	case KILL_GRAPH:
	  {
	    m_model.deleteGraph(m_graphID);
	  } break;
	case RENAME_GRAPH:
	{
	  std::string newName = AskForStringDialog::open(0, "Rename Graph",
							 "Enter new name");
	  m_model.renameGraph(m_graphID, newName);
	} break;
	case COPY_GRAPH:
	{
	  std::string newName = AskForStringDialog::open(0, "Copy Graph",
							 "Enter name of copy");
	  m_model.copyGraph(m_graphID, newName);
	} break;
	default:
	  assert(!"MIST!");
	}
    }
  
  private:
    std::string m_graphID;
    std::string m_graphName;

    IModelControlReceiver& m_model;

    int m_numberOfSnaps;

    enum {NEW_GRAPH, NEW_SNAPSHOT,
	  SAVE_GRAPH, KILL_GRAPH,RENAME_GRAPH, COPY_GRAPH};

  };


  class SnapItem : public TreeViewItem
  {
  public:
    SnapItem(const std::string& graphID,
	     const std::string& snapID,
	     const std::string& graphName,
	     const std::string& snapName,
	     IModelControlReceiver& model,
	     ISceneSequencer& sequencer)
      : m_graphID(graphID), m_snapID(snapID),
	m_graphName(graphName), m_snapName(snapName),
	m_model(model), m_sequencer(&sequencer) {}

    virtual ~SnapItem() {}

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,m_snapName.c_str());
    }

    virtual void leftButtonClicked( const Point& pos, int column )
    {
      this->propertySelected(EDIT_GRAPH);
      this->propertySelected(RENDER_GRAPH);
    }

    virtual QPopupMenu* getPropertyMenu()
    {
      QPopupMenu *popme = new QPopupMenu(0, "pop");
      popme->insertItem("Edit this Graph",EDIT_GRAPH);
      popme->insertItem("Render this Graph",RENDER_GRAPH);
      popme->insertItem("Rename Snapshot",
			RENAME_SNAPSHOT);
      popme->insertItem("Copy Snapshot",COPY_SNAPSHOT);
      popme->insertItem("Remove Snapshot",KILL_SNAPSHOT);
      popme->insertItem("Put into Sequencer",PUT_INTO_SEQUENCER);      

      return popme;
    }

    std::string graphID() const
    {
      return m_graphID;
    }

    std::string snapID() const
    {
      return m_snapID;
    }

    std::string graphName() const
    {
      return m_graphName;
    }

    std::string snapName() const
    {
      return m_snapName;
    }

    void setNames(const std::string& newGraphName,
		  const std::string& newSnapName)
    {
      m_graphName = newGraphName;
      m_snapName = newSnapName;
      m_textListener->textChanged(0,newSnapName.c_str());
    }

    void setStatus(const std::string& newStatus)
    {
      m_textListener->textChanged(1,newStatus.c_str());
    }

    void SnapItem::propertySelected(int id)
    {
      switch(id)
	{
	case EDIT_GRAPH:
	  {
	    m_model.changeEditGraph(m_graphID, m_snapID);
	  } break;
	case RENDER_GRAPH:
	  {
	    m_model.changeRenderedGraph(m_graphID, m_snapID);
	  }
	  break;
	case PUT_INTO_SEQUENCER:
	  {
	    std::string 
	      sLength = AskForStringDialog::open(0,
						 "Put into Sequencer",
						 "Enter length in secs");
	    std::istringstream is(sLength);
	    double length;
	    is >> length;
	    if (!is)
	      {
		//TODO
		//length = 5000;
	      }

	    std::string command = m_graphID + ":" + m_snapID;
	    m_sequencer->appendScene(command, length*1000);
	  }
	  break;
	case RENAME_SNAPSHOT:
	  {
	    std::string 
	      newName = AskForStringDialog::open(0, "Rename Snapshot",
						 "Enter new name");
	    m_model.renameControllValueSet(m_graphID, m_snapID, newName);
	  } break;
	case KILL_SNAPSHOT:
	  {
	    m_model.deleteControllValueSet(m_graphID, m_snapID);
	  } break;
	case COPY_SNAPSHOT:
	  {
	    std::string 
	      newName = AskForStringDialog::open(0, "Copy Snapshot",
						 "Enter a name for the copy");

	    m_model.copyControllValueSet(m_graphID, m_snapID, newName);
	  } break;
	default:
	  assert(!"MIST!");
      }
    }

  private:
    std::string m_graphID;
    std::string m_snapID;
    std::string m_graphName;
    std::string m_snapName;
    IModelControlReceiver& m_model;
    ISceneSequencer* m_sequencer;

    enum {PUT_INTO_SEQUENCER,RENAME_SNAPSHOT, KILL_SNAPSHOT, COPY_SNAPSHOT,
	  EDIT_GRAPH, RENDER_GRAPH};


  };

  GraphNameViewObject::GraphNameViewObject(QObject* parent,
					   GraphNameView& view)
    : QObject(parent), m_view(view)
  {
  }

  void GraphNameViewObject::editGraphChanged( const std::string& graphID,
					      const std::string& snapID )
  {
    m_view.markEditGraph(graphID, snapID);
  }

  void GraphNameViewObject::renderedGraphChanged( const std::string& graphID )
  {
    m_view.markRenderedGraph(graphID);
  }

  GraphNameView::GraphNameView(QWidget* parent,
			       IModelControlReceiver& model,
			       ISceneSequencer& sequencer)
    :  stupidObject(0,*this), editSnap(0), renderedGraph(0),
       m_model(model), m_topItem(new GraphTopItem(model) ),
       m_sequencer(&sequencer)
  {
    std::vector<std::string> cols;
    cols.push_back("Name");
    cols.push_back("Status");
    m_treeView = new TreeView(parent,"Graphen",cols);
    m_treeView->insertItem(*m_topItem,0);
  }

  GraphNameView::~GraphNameView()
  {
  }

  QObject* GraphNameView::signalObject()
  {
    return &stupidObject;
  }

  QWidget* GraphNameView::widget()
  {
    return m_treeView->widget();
  }

  void GraphNameView::graphExists(const std::string& graphID,
				  const std::string& snapID,
				  const std::string& graphName,
				  const std::string& snapName)
  {
    GraphMap::const_iterator it = m_graphs.find(graphID);
    SnapMap::const_iterator 
      it2 = m_snaps.find(std::make_pair(graphID, snapID));

    if (it2 != m_snaps.end())
      {
	throw std::runtime_error("Snap already exists!");
      }

    if (it == m_graphs.end())
      {
	GraphItemPtr tmp( new GraphItem(graphID,graphName,m_model) );

	m_graphs[graphID] = tmp;
	m_treeView->insertItem(*tmp,&*m_topItem);

	it = m_graphs.find(graphID);
      }


    assert(it != m_graphs.end());

    SnapItemPtr tmp( new SnapItem(graphID,snapID,
				  graphName,snapName,m_model,*m_sequencer) );

    m_snaps[std::make_pair(graphID,snapID)] = tmp;
    m_treeView->insertItem(*tmp,&*it->second);
    it->second->snapAdded();
  }

  void GraphNameView::graphNoLongerExists(const std::string& graphID,
					  const std::string& snapID)
  {
    GraphMap::iterator it = m_graphs.find(graphID);
    SnapMap::iterator it2 = m_snaps.find(std::make_pair(graphID,snapID));
	
    if (it == m_graphs.end() || it2 == m_snaps.end())
      {
	throw std::runtime_error("Graph '" + graphID + ":" + snapID + "' doesnt exist at "
				 "GraphNameView::graphNoLongerExists()");
      }

	if (editSnap->snapName() == it2->second->snapName())
		editSnap = SnapItemPtr(0);

    m_treeView->removeItem(*it2->second);
    m_snaps.erase(it2);
    it->second->snapRemoved();

    // remove graph if it has no snaps left
    if (it->second->numberOfSnaps() == 0)
    {
	  if (renderedGraph->graphName() == it->second->graphName())
		  renderedGraph = GraphItemPtr(0);

      m_treeView->removeItem(*it->second);
      m_graphs.erase(it);
    }
  }


  void GraphNameView::graphRenamed(const std::string& graphID,
				   const std::string& snapID,
				   const std::string& newGraphName,
				   const std::string& newSnapName)
  {
    GraphMap::iterator it = m_graphs.find(graphID);
    SnapMap::iterator it2 = m_snaps.find(std::make_pair(graphID,snapID));

    if (it == m_graphs.end() || it2 == m_snaps.end())
      {
	throw std::runtime_error("Graph doesnt exist at "
				 "GraphNameView::graphRenamed()");
      }

    it->second->setName(newGraphName);
    it2->second->setNames(newGraphName,newSnapName);
  }

  void GraphNameView::markEditGraph( const std::string& graphID,
				     const std::string& snapID )
  {
    SnapMap::const_iterator 
      it = m_snaps.find(std::make_pair(graphID, snapID));

    if (it == m_snaps.end())
      {
	throw std::runtime_error("Snap doesnt!");
      }

    if (editSnap != 0)
      editSnap->setStatus("");

    editSnap = it->second;

    editSnap->setStatus("e");
  }

  void GraphNameView::markRenderedGraph( const std::string& graphID )
  {
    GraphMap::const_iterator it = m_graphs.find(graphID);

    if (it == m_graphs.end())
	throw std::runtime_error("Graph doesnt!");

    if (renderedGraph != 0)
      renderedGraph->setStatus("");
    
    renderedGraph = it->second;
    
    renderedGraph->setStatus("r");
  }

  bool checkNamePolicy (const std::string& name)
  {
    // length
    const unsigned int maxNameLength=20;
    const unsigned int minNameLength=1;

    // allowed characters in name
    const std::string allowedCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

    if (name.length()>maxNameLength||name.length()<minNameLength)
    {
      // violation of the length rule in the name policy
      return false;
    }

    for(std::string::const_iterator it=name.begin();it!=name.end();++it)
    {
      std::string::const_iterator it2 = std::find(allowedCharacters.begin(),allowedCharacters.end(),*it);
      if (it2==allowedCharacters.end())
        {
          // this character is not allowed
          return false;
        }
    }

    return true;
  }


}
