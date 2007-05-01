/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

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

#ifndef INCLUDED_GRAPHNAME_VIEW_H
#define INCLUDED_GRAPHNAME_VIEW_H

#include <map>

#include <QtCore/QObject>

#include "base/treeview.h"

#include "interfaces/igraphnamereceiver.h"

#include "utils/autoptr.h"

class QWidget;
class IModelControlReceiver;
class IErrorReceiver;

namespace gui
{

  class FolderItem;
  class GraphItem;
  class SnapItem;
  class GraphNameView;
  class TreeView;

  class GraphNameViewObject : public QObject
  {
    Q_OBJECT
  public:
    GraphNameViewObject(QObject* parent, GraphNameView& view);
    ~GraphNameViewObject();

 public slots:

    /**
     * Is called when the model tells that the edit Graph changed
     */
    void editGraphChanged( const std::string& graphID,
			   const std::string& snapID );

    /**
     * Is called when the model tells that the rendered Graph changed
     */
    void renderedGraphChanged( const std::string& graphID );

    void undisplayProperties_();

  signals:
    void undisplayProperties();


  private:
    GraphNameView& m_view;
  };

  class GraphNameView : public IGraphNameReceiver
  {
  public:
    GraphNameView(QWidget* parent, IModelControlReceiver& gModel,
                  IErrorReceiver& log);

    virtual ~GraphNameView();

    QObject* signalObject();
    QWidget* widget();

    virtual void graphExists(const std::string& graphID,
			     const std::string& snapID,
			     const std::string& graphName,
			     const std::string& snapName);

    virtual void graphNoLongerExists(const std::string& graphID,
				     const std::string& snapID);

    virtual void graphRenamed(const std::string& graphID,
			      const std::string& snapID,
			      const std::string& newGraphName,
			      const std::string& newSnapName);

    void markEditGraph( const std::string& graphID,
			const std::string& snapID );

    void markRenderedGraph( const std::string& graphID );


  private:

    TreeViewItem* getFolder(const std::string& path);

    typedef utils::AutoPtr<GraphItem> GraphItemPtr;
    typedef utils::AutoPtr<FolderItem> FolderItemPtr;
    typedef utils::AutoPtr<SnapItem> SnapItemPtr;

    typedef std::map<std::string,GraphItemPtr> GraphMap;
    typedef std::map<std::string,FolderItemPtr> FolderMap;
    typedef std::map<std::string,std::string> FolderNameMap;
    typedef std::map<std::pair<std::string,std::string>,SnapItemPtr> SnapMap;

    TreeView* m_treeView;
    GraphMap m_graphs;

    FolderNameMap m_folderNames;
    FolderMap m_folders;
    SnapMap m_snaps;

    GraphNameViewObject stupidObject;

    SnapItemPtr editSnap;
    GraphItemPtr renderedGraph;

    IModelControlReceiver& m_model;

    typedef utils::AutoPtr<FolderItem> TopItemPtr;
    TopItemPtr m_topItem;

    IErrorReceiver& m_log;
  };
			
}

#endif
