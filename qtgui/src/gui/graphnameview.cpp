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

#include <cassert>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>

#include <qpopupmenu.h>
#include <qmessagebox.h>

#include "interfaces/imodelcontrolreceiver.h"
#include "interfaces/ierrorreceiver.h"

#include "base/askforstringdialog.h"

#include "base/treeviewitem.h"

#include "utils/stringtokenizer.h"

namespace gui
{
  static bool checkNamePolicy (const std::string& name);

  class FolderItem : public TreeViewItem
  {
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

    virtual QPopupMenu* getPropertyMenu()
    {
      QPopupMenu *popme = new QPopupMenu(0, "TopPop");

      popme->insertItem("New Graph",NEW_GRAPH);
      //popme->insertItem("New Folder",NEW_FOLDER);

      /*if (!(m_mask & DENY_RENAME))
        popme->insertItem("Rename",RENAME_FOLDER);

      if (!(m_mask & DENY_REMOVE))
        popme->insertItem("Remove",REMOVE_FOLDER);*/

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
                    m_model.newGraph(m_path + "/" + newName);
                    retry=false;
                  }
                else
                  {
                    switch (QMessageBox::warning (0,"ungueltiger Name",
                                                  "Ein Name muss 1-20 Zeichen langsein und darf keine Leerzeichen oder Sonderzeichenenthalten",
                                                  QMessageBox::Retry | QMessageBox::Default,
                                                  QMessageBox::Abort | QMessageBox::Escape))
                      {
                      case QMessageBox::Abort: retry=false; break;            
                      case QMessageBox::Retry: break;            
                      }
                  }
              }
	  } break;
        /*case NEW_FOLDER:
	  {
            bool retry=true;
            while(retry)
              {
                const std::string newName = AskForStringDialog::open(0, "New Folder",
                                                                     "Enter a name");
                if (checkNamePolicy(newName))
                  {
                    m_model.newGraph(m_path + "/" + newName + "/");
                    retry=false;
                  }
                else
                  {
                    switch (QMessageBox::warning (0,"ungueltiger Name","Ein Name muss 1-20 Zeichen langsein und darf keine Leerzeichen oder Sonderzeichenenthalten",
                                                  QMessageBox::Retry | QMessageBox::Default,
                                                  QMessageBox::Abort | QMessageBox::Escape))
                      {
                      case QMessageBox::Abort: retry=false; break;
                      case QMessageBox::Retry: break;
                      }
                  }
              }
	  } break;
        case RENAME_FOLDER:
	  {
            if (m_mask & DENY_RENAME)
              break;
            bool retry=true;
            while(retry)
              {
                const std::string newName = AskForStringDialog::open(0, "New Name",
                                                                     "Enter a name");
                if (checkNamePolicy(newName))
                  {
                    m_model.renameGraph(m_graphID, m_path + "/" + newName + "/");
                    retry=false;
                  }
                else
                  {
                    switch (QMessageBox::warning (0,"ungueltiger Name","Ein Name muss 1-20 Zeichen langsein und darf keine Leerzeichen oder Sonderzeichenenthalten",
                                                  QMessageBox::Retry | QMessageBox::Default,
                                                  QMessageBox::Abort | QMessageBox::Escape))
                      {
                      case QMessageBox::Abort: retry=false; break;
                      case QMessageBox::Retry: break;
                      }
                  }
              }
	  } break;
        case REMOVE_FOLDER:	  
          if (!(m_mask & DENY_REMOVE))		  
            m_model.deleteGraph(m_graphID);
	  break;*/
	default:
	  assert("so ein mist!");
	}
    }

  private:
    IModelControlReceiver& m_model;
    std::string m_graphID;
    std::string m_path;
    std::string m_name;

    int m_mask;

    enum { NEW_GRAPH/*, NEW_FOLDER, REMOVE_FOLDER, RENAME_FOLDER*/ };
  };

  class GraphItem : public TreeViewItem
  {
  public:
    GraphItem(const std::string& graphID,
	      const std::string& path,
	      const std::string& graphName,
	      IModelControlReceiver& model)
      :      m_graphID(graphID),m_path(path), m_graphName(graphName), m_model(model),
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
                    switch (QMessageBox::warning (0,"invalid name","Only names with max 20 characters and without space or other special characters are possible",
						  QMessageBox::Retry | QMessageBox::Default,
                                                  QMessageBox::Abort | QMessageBox::Escape))
                      {
                      case QMessageBox::Abort: retry=false; break;            
                      case QMessageBox::Retry: break;            
                      }
                  }
              }
          } break;
	case COPY_GRAPH:
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
                    switch (QMessageBox::warning (0,"invalid name","Only names with max 20 characters and without space or other special characters are possible",
						  QMessageBox::Retry | QMessageBox::Default,
                                                  QMessageBox::Abort | QMessageBox::Escape))
                      {
                      case QMessageBox::Abort: retry=false; break;            
                      case QMessageBox::Retry: break;            
                      }
                  }
              }
	  } break;
	default:
	  assert(!"MIST!");
	}
    }
  
  private:
    std::string m_graphID;
    std::string m_graphName;
    std::string m_path;


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
        m_stupidObject.undisplayProperties_();
	    m_model.changeEditGraph(m_graphID, m_snapID);
	  } break;
	case RENDER_GRAPH:
	  {
	    m_model.changeRenderedGraph(m_graphID, m_snapID);
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
       m_model(model), m_topItem(new FolderItem(model, "_", "", "Graphen", 
                                                FolderItem::DENY_REMOVE 
                                                | FolderItem::DENY_RENAME) ),
       m_log(log)
  {
    std::vector<std::string> cols;
    cols.push_back("Name");
    cols.push_back("Status");
    m_treeView = new TreeView(parent,"Graphen",cols);
    m_treeView->insertItem(*m_topItem,0);	
  }

  GraphNameView::~GraphNameView()
  {
    //    fprintf(stderr, "Dtor GraphNameView\n");
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
   * If fillPath has only one or zero components ("/one/" or "/"), then
   * path will be "" and last will be "one" or "/".
   */
  void extractPath(const std::string& fullPath, std::string& path, std::string& last)
  {
    utils::StringTokenizer sr(fullPath);

    /*if (fullPath[fullPath.length()-1] == '/')
      {
      path = fullPath.substr(0, fullPath.length()-1);
      last = "";
      return;
      }*/

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
            GraphItemPtr tmp( new GraphItem(graphID,folderName+"/", fileName, m_model) );
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
            if (renderedGraph && renderedGraph->graphName() == it->second->graphName())
              renderedGraph = GraphItemPtr(0);
			  
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
    const std::string allowedCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

    if (name.length()>maxNameLength||name.length()<minNameLength)
      {
        // violation of the length rule in the name policy
        return false;
      }

    for(std::string::const_iterator it=name.begin();it!=name.end();++it)
      {
        std::string::const_iterator it2 = std::find(allowedCharacters.begin(),
			                                        allowedCharacters.end(),*it);
        if (it2==allowedCharacters.end())
          {
            // this character is not allowed
            return false;
          }
      }

    return true;
  }


}
