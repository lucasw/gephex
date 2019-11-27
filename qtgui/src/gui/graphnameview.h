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
#include "base/treeviewitem.h"

#include "interfaces/igraphnamereceiver.h"

#include "utils/autoptr.h"

class QWidget;
class IModelControlReceiver;
class IErrorReceiver;

namespace gui {
class GraphNameView;
class TreeView;

class FolderItem : public QObject, public TreeViewItem {
  Q_OBJECT
public:
  enum Permission { NONE = 0, DENY_RENAME = 1, DENY_REMOVE = 2 };

  FolderItem(IModelControlReceiver &model, const std::string graphID,
             const std::string &path, const std::string &displayName,
             int mask = NONE);

  std::string getPath() const;
  virtual void setColumnTextChangeListener(ColumnTextChangeListener &l);
  virtual QMenu *getPropertyMenu();

protected slots:
  void newGraphSlot();

private:
  IModelControlReceiver &m_model;
  std::string m_graphID;
  std::string m_path;
  std::string m_name;

  int m_mask;
};

class GraphItem : public QObject, public TreeViewItem {
  Q_OBJECT
public:
  GraphItem(const std::string &graphID, const std::string &path,
            const std::string &graphName, IModelControlReceiver &model);

  virtual ~GraphItem();

  // must be called when a snapshot is added to this graph
  void snapAdded();
  // must be called when a snapshot is removed from this graph
  void snapRemoved();
  int numberOfSnaps() const;

  virtual void setColumnTextChangeListener(ColumnTextChangeListener &l);
  virtual QMenu *getPropertyMenu();
  std::string graphID() const;
  std::string graphName() const;
  void setName(const std::string &newName);
  void setStatus(const std::string &newStatus);

protected slots:
  void saveGraphSlot();
  void copyGraphSlot();
  void renameGraphSlot();
  void killGraphSlot();
  void newSnapshotSlot();

private:
  std::string m_graphID;
  std::string m_path;
  std::string m_graphName;
  IModelControlReceiver &m_model;
  int m_numberOfSnaps;
};

class GraphNameViewObject;

class SnapItem : public QObject, public TreeViewItem {
  Q_OBJECT
public:
  SnapItem(const std::string &graphID, const std::string &snapID,
           const std::string &graphName, const std::string &snapName,
           IModelControlReceiver &model, GraphNameViewObject &stupidObject);

  virtual ~SnapItem();
  virtual void setColumnTextChangeListener(ColumnTextChangeListener &l);
  virtual void onActivate(int /*column*/);
  virtual QMenu *getPropertyMenu();

  std::string graphID() const;
  std::string snapID() const;
  std::string graphName() const;
  std::string snapName() const;
  void setNames(const std::string &newGraphName,
                const std::string &newSnapName);

  void setStatus(const std::string &newStatus);

protected slots:
  void editSlot();
  void renderSlot();
  void renameSlot();
  void killSlot();
  void copySlot();

private:
  std::string m_graphID;
  std::string m_snapID;
  std::string m_graphName;
  std::string m_snapName;
  IModelControlReceiver &m_model;
  GraphNameViewObject &m_stupidObject;

  enum {
    RENAME_SNAPSHOT,
    KILL_SNAPSHOT,
    COPY_SNAPSHOT,
    EDIT_GRAPH,
    RENDER_GRAPH
  };
};

class GraphNameViewObject : public QObject {
  Q_OBJECT
public:
  GraphNameViewObject(QObject *parent, GraphNameView &view);
  ~GraphNameViewObject();

public slots:

  /**
   * Is called when the model tells that the edit Graph changed
   */
  void editGraphChanged(const std::string &graphID, const std::string &snapID);

  /**
   * Is called when the model tells that the rendered Graph changed
   */
  void renderedGraphChanged(const std::string &graphID);

  void undisplayProperties_();

signals:
  void undisplayProperties();

private:
  GraphNameView &m_view;
};

class GraphNameView : public IGraphNameReceiver {
public:
  GraphNameView(QWidget *parent, IModelControlReceiver &gModel,
                IErrorReceiver &log);

  virtual ~GraphNameView();

  QObject *signalObject();
  QWidget *widget();

  virtual void graphExists(const std::string &graphID,
                           const std::string &snapID,
                           const std::string &graphName,
                           const std::string &snapName);

  virtual void graphNoLongerExists(const std::string &graphID,
                                   const std::string &snapID);

  virtual void graphRenamed(const std::string &graphID,
                            const std::string &snapID,
                            const std::string &newGraphName,
                            const std::string &newSnapName);

  void markEditGraph(const std::string &graphID, const std::string &snapID);

  void markRenderedGraph(const std::string &graphID);

private:
  TreeViewItem *getFolder(const std::string &path);

  typedef utils::AutoPtr<GraphItem> GraphItemPtr;
  typedef utils::AutoPtr<FolderItem> FolderItemPtr;
  typedef utils::AutoPtr<SnapItem> SnapItemPtr;

  typedef std::map<std::string, GraphItemPtr> GraphMap;
  typedef std::map<std::string, FolderItemPtr> FolderMap;
  typedef std::map<std::string, std::string> FolderNameMap;
  typedef std::map<std::pair<std::string, std::string>, SnapItemPtr> SnapMap;

  TreeView *m_treeView;
  GraphMap m_graphs;

  FolderNameMap m_folderNames;
  FolderMap m_folders;
  SnapMap m_snaps;

  GraphNameViewObject stupidObject;

  SnapItemPtr editSnap;
  GraphItemPtr renderedGraph;

  IModelControlReceiver &m_model;

  typedef utils::AutoPtr<FolderItem> TopItemPtr;
  TopItemPtr m_topItem;

  IErrorReceiver &m_log;
};

} // namespace gui

#endif
