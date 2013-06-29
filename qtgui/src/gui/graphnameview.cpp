/* This source file is a part of the GePhex Project.

  Copyright (C) 2001-2003 

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

#include "graphnameview.h"

#include <sstream>

#include <cassert>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include <QtGui/qmenu.h>
#include <QtGui/qmessagebox.h>

#include "interfaces/imodelcontrolreceiver.h"
#include "interfaces/ierrorreceiver.h"

#include "base/askforstringdialog.h"

#include "base/treeviewitem.h"

#include "utils/stringtokenizer.h"

namespace gui
{
  static bool checkNamePolicy (const std::string& name);

  class FolderItem : public QObject, public TreeViewItem
  {
    Q_OBJECT
  public:
    enum Permission {NONE = 0, DENY_RENAME = 1, DENY_REMOVE = 2};

    FolderItem(IModelControlReceiver& model, 
               const std::string graphID,
               const std::string& path,
               const std::string& displayName, int mask = NONE)
      : m_model(model), m_graphID(graphID), m_path(path), 
      m_name(displayName), m_mask(mask) {}

    std::string getPath() const
    {
      return m_path;
    }

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0, m_name);
    }

    virtual QMenu* getPropertyMenu()
    {
      QMenu* popme = new QMenu("TopPop");

      QAction* newAc = new QAction("New Graph", popme);

      popme->addAction(newAc);

      connect(newAc, SIGNAL(triggered()), this, SLOT(newGraphSlot()));

      return popme;      
    }

  protected slots:

    void newGraphSlot()
    {
      bool retry=true;
      while(retry)
	{
	  const std::string 
	    newName = AskForStringDialog::open(0, "New Graph",
					       "Enter a name");
	  if (checkNamePolicy(newName))
	    {
	      std::string name("");
	      if (m_path != "")
		name = m_path + "/";
	      name += newName;
	      m_model.newGraph(name);
	      retry = false;
	    }
	  else
	    {
	      switch (QMessageBox::warning (0,"invalid name",
					    "A name must be between 1 "
					    "and 20 characters long."
					    "It must not contain "
					    "spaces or special "
					    "characters",
					    QMessageBox::Retry 
					    | QMessageBox::Default,
					    QMessageBox::Abort
					    | QMessageBox::Escape))
		{
		case QMessageBox::Abort: retry=false; break;            
		case QMessageBox::Retry: break;            
		}
	    }
	}
    }

  private:
    IModelControlReceiver& m_model;
    std::string m_graphID;
    std::string m_path;
    std::string m_name;

    int m_mask;

  };

  class GraphItem : public QObject, public TreeViewItem
  {
    Q_OBJECT
  public:
    GraphItem(const std::string& graphID,
	      const std::string& path,
	      const std::string& graphName,
	      IModelControlReceiver& model)
      :      m_graphID(graphID),
             m_path(path),
             m_graphName(graphName),
             m_model(model),
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

    virtual QMenu* getPropertyMenu()
    {
      QMenu *popme = new QMenu("GraphPopup");

      QAction* saveAc = new QAction("Save Graph",   popme);
      QAction* copyAc = new QAction("Copy Graph",     popme);
      QAction* renaAc = new QAction("Rename Graph",   popme);
      QAction* killAc = new QAction("Remove Graph",   popme);
      QAction* newAc  = new QAction("New Snapshot", popme);
      
      popme->addAction(saveAc);
      popme->addAction(copyAc);
      popme->addAction(renaAc);
      popme->addAction(killAc);
      popme->addAction(newAc);

      connect(saveAc, SIGNAL(triggered()), this, SLOT(saveGraphSlot()));
      connect(copyAc, SIGNAL(triggered()), this, SLOT(copyGraphSlot()));
      connect(renaAc, SIGNAL(triggered()), this, SLOT(renameGraphSlot()));
      connect(killAc, SIGNAL(triggered()), this, SLOT(killGraphSlot()));
      connect(newAc,  SIGNAL(triggered()), this, SLOT(newSnapshotSlot()));

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

protected slots:
   void saveGraphSlot()
    {
      m_model.saveGraph(m_graphID);
    }

   void copyGraphSlot()
    {
      bool retry=true;
      while(retry)
	{
	  const std::string newName = 
	    AskForStringDialog::open(0, "New Graph",
				     "Enter the name of the copy");
	  if (checkNamePolicy(newName))
	    {
	      m_model.copyGraph(m_graphID, newName);
	      retry=false;
	    }
	  else
	    {
	      switch (QMessageBox::warning (0,"invalid name",
					    "Only names with max 20 characters"
					    " and without space or other "
					    "special characters are possible",
					    QMessageBox::Retry |
					     QMessageBox::Default,
					    QMessageBox::Abort |
					     QMessageBox::Escape))
		{
		case QMessageBox::Abort: retry=false; break;            
		case QMessageBox::Retry: break;            
		}
	    }
	}
    }

   void renameGraphSlot()
    {
      bool retry=true;
      while(retry)
	{
	  const std::string newName = 
	    AskForStringDialog::open(0, "New Graph",
				     "Enter new name");
	  if (checkNamePolicy(newName))
	    {
	      m_model.renameGraph(m_graphID, newName);
	      retry=false;
	    }
	  else
	    {
	      switch (QMessageBox::warning (0,"invalid name",
					    "Only names with max 20 characters"
					    " and without space or other "
					    "special characters are possible",
					    QMessageBox::Retry |
					     QMessageBox::Default,
					    QMessageBox::Abort |
					     QMessageBox::Escape))
		{
		case QMessageBox::Abort: retry=false; break;            
		case QMessageBox::Retry: break;            
		}
	    }
	}
    }

   void killGraphSlot()
    {
      m_model.deleteGraph(m_graphID);
    }

   void newSnapshotSlot()
    {
      std::string newName = AskForStringDialog::open(0, "New Snapshot",
						     "Enter a name");
      m_model.newControlValueSet(m_graphID, newName);
    }
	  
  private:
    std::string m_graphID;
    std::string m_path;
    std::string m_graphName;

    IModelControlReceiver& m_model;

    int m_numberOfSnaps;

  };


  class SnapItem : public QObject, public TreeViewItem
  {
    Q_OBJECT
  public:
    SnapItem(const std::string& graphID,
	     const std::string& snapID,
	     const std::string& graphName,
	     const std::string& snapName,
	     IModelControlReceiver& model,	     
	     GraphNameViewObject& stupidObject)
      : m_graphID(graphID), m_snapID(snapID),
	m_graphName(graphName), m_snapName(snapName),
	m_model(model), m_stupidObject(stupidObject) {}

    virtual ~SnapItem() {}

    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l)
    {
      TreeViewItem::setColumnTextChangeListener(l);
      l.textChanged(0,m_snapName.c_str());
    }

    virtual void onActivate( int /*column*/ )
    {
      this->editSlot();
      this->renderSlot();
    }

    virtual QMenu* getPropertyMenu()
    {
      QMenu *popme = new QMenu("pop");

      QAction* editAc = new QAction("Edit this Graph",   popme);
      QAction* rendAc = new QAction("Render this Graph", popme);
      QAction* renaAc = new QAction("Rename Snapshot",   popme);
      QAction* copyAc = new QAction("Copy Snapshot",     popme);
      QAction* killAc = new QAction("Remove Snapshot",   popme);

      popme->addAction(editAc);
      popme->addAction(rendAc);
      popme->addAction(renaAc);
      popme->addAction(copyAc);
      popme->addAction(killAc);

      connect(editAc, SIGNAL(triggered()), this, SLOT(editSlot()));
      connect(rendAc, SIGNAL(triggered()), this, SLOT(renderSlot()));
      connect(renaAc, SIGNAL(triggered()), this, SLOT(renameSlot()));
      connect(copyAc, SIGNAL(triggered()), this, SLOT(copySlot()));
      connect(killAc, SIGNAL(triggered()), this, SLOT(killSlot()));

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

protected slots:
    void editSlot()
    {
      m_stupidObject.undisplayProperties_();
      m_model.changeEditGraph(m_graphID, m_snapID);
    }

    void renderSlot()
    {
      m_model.changeRenderedGraph(m_graphID, m_snapID);
    }

    void renameSlot()
    {
      std::string 
	newName = AskForStringDialog::open(0, "Rename Snapshot",
					   "Enter new name");
      m_model.renameControlValueSet(m_graphID, m_snapID, newName);
    }

    void killSlot()
    {
      m_model.deleteControlValueSet(m_graphID, m_snapID);
    }

    void copySlot()
    {
      std::string 
	newName = AskForStringDialog::open(0, "Copy Snapshot",
					   "Enter a name for the copy");

      m_model.copyControlValueSet(m_graphID, m_snapID, newName);
    }

  private:
    std::string m_graphID;
    std::string m_snapID;
    std::string m_graphName;
    std::string m_snapName;
    IModelControlReceiver& m_model;
    
    GraphNameViewObject& m_stupidObject;

    enum {RENAME_SNAPSHOT, KILL_SNAPSHOT, COPY_SNAPSHOT,
	  EDIT_GRAPH, RENDER_GRAPH};


  };

  GraphNameViewObject::GraphNameViewObject(QObject* parent,
					   GraphNameView& view)
    : QObject(parent), m_view(view)
  {
  }
  GraphNameViewObject::~GraphNameViewObject()
  {
    //    fprintf(stderr, "Dtor GraphNameViewObject\n");
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

  void GraphNameViewObject::undisplayProperties_()
  {
    emit undisplayProperties();
  }

  GraphNameView::GraphNameView(QWidget* parent,
			       IModelControlReceiver& model,
                               IErrorReceiver& log)
    :  stupidObject(0,*this), editSnap(0), renderedGraph(0),
       m_model(model), m_topItem(new FolderItem(model, "_", "", "Graphs", 
                                                FolderItem::DENY_REMOVE 
                                                | FolderItem::DENY_RENAME) ),
       m_log(log)
  {
    std::vector<std::string> cols;
    cols.push_back("Name");
    cols.push_back("State");
    m_treeView = new TreeView(parent, "Graphs", cols);
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

  /**
   * Extracts the first part and the last component of a full path.
   * For example, if fullPath = "/one/two/three/four"
   *  then path will be "/one/two/three" (without trailing slash!),
   *  and last will be "four".
   *
   * If fullPath ends with a "/" the result is the same.
   *
   * If fullPath has only one or zero components ("/one/" or "/"), then
   * path will be "" and last will be "one" or "/".
   */
  void extractPath(const std::string& fullPath,
		   std::string& path,
		   std::string& last)
  {
    utils::StringTokenizer sr(fullPath);

    path = "";
    last = "";

    std::string token = sr.next("/");
    while (token != "")
      {		  
        std::string new_token = sr.next("/");
        if (new_token == "")
          last = token; 
        else
          path = path + "/" + token;

        token = new_token;
      }
  }

  TreeViewItem* GraphNameView::getFolder(const std::string& path)
  {
    if (path == "/")
      return &*m_topItem;	  

    FolderNameMap::const_iterator it = m_folderNames.find(path);
    if (it == m_folderNames.end())
      return 0;

    std::string graphID = it->second;

    FolderMap::const_iterator it2 = m_folders.find(graphID);
    if (it2 == m_folders.end())
      return 0;

    return &*it2->second;
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
	m_log.error("Snap already exists!");
        return;
      }

    bool folder = false;

    if (it == m_graphs.end())
      {
        std::string folderName;
        std::string fileName;
        extractPath(graphName, folderName, fileName);

        TreeViewItem* parent = getFolder(folderName + "/");
        if (parent == 0)
          {
            m_log.error("graphNameExists: Could not find folder '" 
                                     + folderName + "/'");
            return;
          }		
        if (graphName[graphName.length()-1] == '/') // create a folder
          {
            folder = true;						
            FolderItemPtr tmp (new FolderItem(m_model, graphID, 
                                              folderName + "/" + fileName,
                                              "%" + fileName + "%"));

            m_folders[graphID] = tmp;
            m_folderNames[graphName] = graphID;
						
            m_treeView->insertItem(*tmp, parent);
          }
        else                // create a graph
          {
            folder = false;
            GraphItemPtr tmp( new GraphItem(graphID,
					    folderName+"/",
					    fileName,
					    m_model) );
            m_graphs[graphID] = tmp;
            m_treeView->insertItem(*tmp, parent);
            it = m_graphs.find(graphID);
          }				
      }


    if (!folder)
      {
        assert(it != m_graphs.end());

        SnapItemPtr tmp( new SnapItem(graphID,snapID,
                                      graphName,snapName,m_model,
                                      stupidObject) );

        m_snaps[std::make_pair(graphID,snapID)] = tmp;
        m_treeView->insertItem(*tmp,&*it->second);
        it->second->snapAdded();
      }
  }

  void GraphNameView::graphNoLongerExists(const std::string& graphID,
					  const std::string& snapID)
  {
    if (m_graphs.find(graphID) == m_graphs.end() || snapID == "") //folder
      {
        FolderMap::iterator it = m_folders.find(graphID);
        if (it == m_folders.end())
          {
            m_log.error("Folder '" + graphID 
                        + "' doesnt exist at "
                        "GraphNameView::graphNoLongerExists()");
            return;
          }

        std::string path = it->second->getPath();
        m_treeView->removeItem(*it->second);

        m_folders.erase(it);

        FolderNameMap::iterator it2 = m_folderNames.find(path + "/");
        if (it2 == m_folderNames.end())
          {
            m_log.error("Foldername '" + path + "' doesnt exist at "
                        "GraphNameView::graphNoLongerExists()");
            return;
          }
            
        m_folderNames.erase(it2);
      }

    if (snapID != "") //graph
      {
        GraphMap::iterator it = m_graphs.find(graphID);
        SnapMap::iterator it2 = m_snaps.find(std::make_pair(graphID,snapID));
		  
        if (it == m_graphs.end() || it2 == m_snaps.end())
          {
            m_log.error("Graph '" + graphID + ":" 
                        + snapID + "' doesnt exist at "
                        "GraphNameView::graphNoLongerExists()");
            return;
          }
		  
        if (editSnap && editSnap->snapName() == it2->second->snapName())
          editSnap = SnapItemPtr(0);
		  
        m_treeView->removeItem(*it2->second);
        m_snaps.erase(it2);
        it->second->snapRemoved();
		  
        // remove graph if it has no snaps left
        if (it->second->numberOfSnaps() == 0)
          {
            if (renderedGraph &&
                renderedGraph->graphName() == it->second->graphName())
              {
                renderedGraph = GraphItemPtr(0);
              }
            
            m_treeView->removeItem(*it->second);
            m_graphs.erase(it);
          }
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
	m_log.error("Graph doesnt exist at "
				 "GraphNameView::graphRenamed()");
        return;
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
	m_log.error("Snap doesnt!");
        return;
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
      {
        m_log.error("Graph doesn't exist at markRenderedGraph!");
        return;
      }

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
    const std::string allowedCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz1234567890";

    if (name.length()>maxNameLength||name.length()<minNameLength)
      {
        // violation of the length rule in the name policy
        return false;
      }

    for(std::string::const_iterator it=name.begin();it!=name.end();++it)
      {
        std::string::const_iterator it2 = std::find(allowedCharacters.begin(),
                                                    allowedCharacters.end(),
						    *it);
        if (it2==allowedCharacters.end())
          {
            // this character is not allowed
            return false;
          }
      }

    return true;
  }

}

#include "graphnameview_moc_cpp.cpp"

